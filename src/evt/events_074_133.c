#include "msg.h"
#include "eventselect_api.h"
#include "event_text.h"
#include "msg_localized_data.h"
#include "songs.h"
#include "msg_types.h"
#include <stddef.h>
#include "types.h"

#ifdef VERSION_US
#include "event_074_text.inc"

static const MessageScriptEntry sEvent074Script[20] = {
    { 0, 3, 2, 1, { 0, 0, 0 }, gEventTextUs_08F7F66C, 0, 300 },
    { 2, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F7F6DE, 0, 310 },
    { 10, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F7F748, MSG_SCRIPT_FLAG_SILHOUETTE, 340 },
    { 1, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08F7F798, 0, 380 },
    { 10, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F7F7B2, MSG_SCRIPT_FLAG_SILHOUETTE, 420 },
    { 6, 2, 2, 1, { 0, 0, 0 }, gEventTextUs_08F7F832, 0, 430 },
    { 6, 2, 2, 1, { 0, 0, 0 }, gEventTextUs_08F7F862, 0, 460 },
    { 10, 3, 0, 1, { 0, 0, 0 }, gEventTextUs_08F7F8B8, 0, 600 },
    { 6, 0, 2, 1, { 0, 0, 0 }, gEventTextUs_08F7F934, 0, 610 },
    { 6, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F7F9A2, 0, 620 },
    { 10, 3, 0, 1, { 0, 0, 0 }, gEventTextUs_08F7FA14, 0, 630 },
    { 10, 3, 4, 1, { 0, 0, 0 }, gEventTextUs_08F7FA86, 0, 640 },
    { 10, 10, 0, 1, { 0, 0, 0 }, gEventTextUs_08F7FABE, 0, 690 },
    { 6, 1, 2, 1, { 0, 0, 0 }, gEventTextUs_08F7FACC, 0, 700 },
    { 10, 1, 0, 1, { 0, 0, 0 }, gEventTextUs_08F7FAFA, 0, 710 },
    { 0, 7, 2, 1, { 0, 0, 0 }, gEventTextUs_08F7FB64, 0, 720 },
    { 2, 0, 0, 1, { 0, 0, 0 }, gEventTextUs_08F7FBAC, 0, 730 },
    { 10, 7, 0, 1, { 0, 0, 0 }, gEventTextUs_08F7FC08, 0, 740 },
    { 6, 2, 2, 1, { 0, 0, 0 }, gEventTextUs_08F7FCA0, 0, 750 },
    { 10, 4, 0, 1, { 0, 0, 0 }, gEventTextUs_08F7FCEA, MSG_SCRIPT_FLAG_END, 760 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent074Script[20] = {
    { 0, 3, 2, 3, { 0, 0, 0 }, gEventTextJp_08F730F4, 0, 300 },
    { 2, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F730A8, 0, 310 },
    { 10, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F73090, MSG_SCRIPT_FLAG_SILHOUETTE, 340 },
    { 1, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08F73088, 0, 380 },
    { 10, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7304C, MSG_SCRIPT_FLAG_SILHOUETTE, 420 },
    { 6, 2, 2, 3, { 0, 0, 0 }, gEventTextJp_08F73034, 0, 430 },
    { 6, 2, 2, 3, { 0, 0, 0 }, gEventTextJp_08F73008, 0, 460 },
    { 10, 3, 0, 3, { 0, 0, 0 }, gEventTextJp_08F72FB8, 0, 600 },
    { 6, 0, 2, 3, { 0, 0, 0 }, gEventTextJp_08F72F84, 0, 610 },
    { 6, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F72F38, 0, 620 },
    { 10, 3, 0, 3, { 0, 0, 0 }, gEventTextJp_08F72EF0, 0, 630 },
    { 10, 3, 4, 3, { 0, 0, 0 }, gEventTextJp_08F72EC8, 0, 640 },
    { 10, 10, 0, 3, { 0, 0, 0 }, gEventTextJp_08F72EBC, 0, 690 },
    { 6, 1, 2, 3, { 0, 0, 0 }, gEventTextJp_08F72EAC, 0, 700 },
    { 10, 1, 0, 3, { 0, 0, 0 }, gEventTextJp_08F72E6C, 0, 710 },
    { 0, 7, 2, 3, { 0, 0, 0 }, gEventTextJp_08F72E24, 0, 720 },
    { 2, 0, 0, 3, { 0, 0, 0 }, gEventTextJp_08F72DF4, 0, 730 },
    { 10, 7, 0, 3, { 0, 0, 0 }, gEventTextJp_08F72DB0, 0, 740 },
    { 6, 2, 2, 3, { 0, 0, 0 }, gEventTextJp_08F72D78, 0, 750 },
    { 10, 4, 0, 3, { 0, 0, 0 }, gEventTextJp_08F72D54, MSG_SCRIPT_FLAG_END, 760 },
};

#include "event_074_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent074Script[20] = {
    { 0, 3, 2, 1, { 0, 0, 0 }, &gUnkEu_09F67918, 0, 300 },
    { 2, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6792C, 0, 310 },
    { 10, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67940, MSG_SCRIPT_FLAG_SILHOUETTE, 340 },
    { 1, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67954, 0, 380 },
    { 10, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67968, MSG_SCRIPT_FLAG_SILHOUETTE, 420 },
    { 6, 2, 2, 1, { 0, 0, 0 }, &gUnkEu_09F6797C, 0, 430 },
    { 6, 2, 2, 1, { 0, 0, 0 }, &gUnkEu_09F67990, 0, 460 },
    { 10, 3, 0, 1, { 0, 0, 0 }, &gUnkEu_09F679A4, 0, 600 },
    { 6, 0, 2, 1, { 0, 0, 0 }, &gUnkEu_09F679B8, 0, 610 },
    { 6, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F679CC, 0, 620 },
    { 10, 3, 0, 1, { 0, 0, 0 }, &gUnkEu_09F679E0, 0, 630 },
    { 10, 3, 4, 1, { 0, 0, 0 }, &gUnkEu_09F679F4, 0, 640 },
    { 10, 10, 0, 1, { 0, 0, 0 }, &gUnkEu_09F67A08, 0, 690 },
    { 6, 1, 2, 1, { 0, 0, 0 }, &gUnkEu_09F67A1C, 0, 700 },
    { 10, 1, 0, 1, { 0, 0, 0 }, &gUnkEu_09F67A30, 0, 710 },
    { 0, 7, 2, 1, { 0, 0, 0 }, &gUnkEu_09F67A44, 0, 720 },
    { 2, 0, 0, 1, { 0, 0, 0 }, &gUnkEu_09F67A58, 0, 730 },
    { 10, 7, 0, 1, { 0, 0, 0 }, &gUnkEu_09F67A6C, 0, 740 },
    { 6, 2, 2, 1, { 0, 0, 0 }, &gUnkEu_09F67A80, 0, 750 },
    { 10, 4, 0, 1, { 0, 0, 0 }, &gUnkEu_09F67A94, MSG_SCRIPT_FLAG_END, 760 },
};
#endif

static const EventCameraKeyframe sEvent074Camera[3] = {
    { -65536, 30720, 20480, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, NULL },
    { -65436, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 80, { 0, 0 }, NULL },
    { -65286, 30720, 20480, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 150, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent074SoundCues[3] = {
    { SONG_BGM_PINOCCHIO_FIELD, 0, 0, 0 },
    { SONG_SND_349, 641, 0, 0 },
    { SONG_BGM_PINOCCHIO_FIELD, 994, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent074Track0[20] = {
    { 4, 130, { 0, 0 }, 20480, 35840, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 3, 145, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 1, 175, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 205, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 1, 342, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 2, 390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 405, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 36, 751, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 825, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 855, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 12, 999, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 32868, NULL, NULL },
};

static const EventCharaKeyframe sEvent074Track1[22] = {
    { 146, 0, { 0, 0 }, 40960, 28160, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 142, 135, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 175, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 142, 235, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 309, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 164, 311, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 342, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 144, 390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 143, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 729, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 164, 731, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 143, 870, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 152, 999, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 32868, NULL, NULL },
};

static const EventCharaKeyframe sEvent074Track2[16] = {
    { 114, 0, { 0, 0 }, 25600, 23040, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 114, 125, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 135, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 155, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 110, 165, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 175, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 195, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 342, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 379, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 136, 381, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 405, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 113, 410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 112, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 121, 999, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 32868, NULL, NULL },
};

static const EventCharaKeyframe sEvent074Track3[10] = {
    { 229, 431, { 0, 0 }, 256000, 256000, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 232, 432, { 0, 0 }, 20480, 35840, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 234, 460, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, EventCharaHop, NULL },
    { 233, 470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaHop, NULL },
    { 229, 741, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 229, 751, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 229, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 230, 810, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 233, 825, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, EventCharaHop, NULL },
    { 229, 1000, { 0, 0 }, 256000, 256000, 0, 0, { 0, 0 }, 32770, NULL, NULL },
};

static const EventCharaKeyframe sEvent074Track4[11] = {
    { 236, 465, { 0, 0 }, 256000, 256000, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 236, 456, { 0, 0 }, 69120, 53760, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 251, 570, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 239, 573, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 239, 641, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 239, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateGlowNoseTask },
    { 258, 691, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 240, 761, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 240, 766, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 237, 770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 243, 890, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 32836, NULL, NULL },
};

static const EventCharaTrack sEvent074Tracks[5] = {
    { sEvent074Track0, 0, { 0, 0, 0 } },
    { sEvent074Track1, 2, { 0, 0, 0 } },
    { sEvent074Track2, 1, { 0, 0, 0 } },
    { sEvent074Track3, 8, { 0, 0, 0 } },
    { sEvent074Track4, 9, { 0, 0, 0 } },
};

const EventSequenceDef gEvent074 = {
    5,
    { 0, 0, 0 },
    sEvent074Tracks,
    sEvent074Camera,
    sEvent074Script,
    sEvent074SoundCues,
    NULL,
    999,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    1,
    255,
    255,
};

#ifdef VERSION_US
#include "event_075_text.inc"
static const MessageScriptEntry sEvent075Script[22] = {
    { 6, 2, 2, 1, { 0, 0, 0 }, gEventTextUs_08F80AFC, 0, 110 },
    { 17, 0, 0, 1, { 0, 0, 0 }, gEventTextUs_08F80B10, 0, 210 },
    { 6, 2, 2, 1, { 0, 0, 0 }, gEventTextUs_08F80BA0, 0, 220 },
    { 17, 0, 0, 1, { 0, 0, 0 }, gEventTextUs_08F80C2A, 0, 230 },
    { 1, 5, 2, 1, { 0, 0, 0 }, gEventTextUs_08F80C5C, 0, 370 },
    { 2, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08F80CAE, 0, 390 },
    { 17, 2, 0, 1, { 0, 0, 0 }, gEventTextUs_08F80CE6, 0, 400 },
    { 0, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F80D44, 0, 410 },
    { 0, 5, 4, 1, { 0, 0, 0 }, gEventTextUs_08F80D8C, 0, 412 },
    { 17, 2, 0, 1, { 0, 0, 0 }, gEventTextUs_08F80DE6, 0, 430 },
    { 17, 2, 4, 1, { 0, 0, 0 }, gEventTextUs_08F80E6C, 0, 432 },
    { 0, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F80EFC, 0, 470 },
    { 17, 0, 0, 1, { 0, 0, 0 }, gEventTextUs_08F80F3A, 0, 480 },
    { 6, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F80FE4, 0, 490 },
    { 17, 2, 0, 1, { 0, 0, 0 }, gEventTextUs_08F8105A, 0, 500 },
    { 0, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8109A, 0, 580 },
    { 1, 0, 2, 1, { 0, 0, 0 }, gEventTextUs_08F810E2, 0, 590 },
    { 17, 0, 0, 1, { 0, 0, 0 }, gEventTextUs_08F8114C, 0, 600 },
    { 17, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08F8121C, 0, 604 },
    { 6, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F812D0, 0, 620 },
    { 0, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F81334, 0, 660 },
    { 0, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F813A6, MSG_SCRIPT_FLAG_END, 662 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent075Script[24] = {
    { 6, 2, 2, 3, { 0, 0, 0 }, gEventTextJp_08F74440, 0, 110 },
    { 17, 0, 0, 3, { 0, 0, 0 }, gEventTextJp_08F74400, 0, 210 },
    { 6, 2, 2, 3, { 0, 0, 0 }, gEventTextJp_08F743B0, 0, 220 },
    { 17, 0, 0, 3, { 0, 0, 0 }, gEventTextJp_08F74390, 0, 230 },
    { 1, 5, 2, 3, { 0, 0, 0 }, gEventTextJp_08F74364, 0, 370 },
    { 2, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F74334, 0, 390 },
    { 17, 2, 0, 3, { 0, 0, 0 }, gEventTextJp_08F742FC, 0, 400 },
    { 0, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F742CC, 0, 410 },
    { 0, 5, 4, 3, { 0, 0, 0 }, gEventTextJp_08F7429C, 0, 412 },
    { 17, 2, 0, 3, { 0, 0, 0 }, gEventTextJp_08F74250, 0, 430 },
    { 17, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08F741FC, 0, 432 },
    { 0, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F741EC, 0, 470 },
    { 17, 0, 0, 3, { 0, 0, 0 }, gEventTextJp_08F7418C, 0, 480 },
    { 6, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F74140, 0, 490 },
    { 17, 2, 0, 3, { 0, 0, 0 }, gEventTextJp_08F74114, 0, 500 },
    { 0, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F740F0, 0, 580 },
    { 1, 0, 2, 3, { 0, 0, 0 }, gEventTextJp_08F740C0, 0, 590 },
    { 17, 0, 0, 3, { 0, 0, 0 }, gEventTextJp_08F740A0, 0, 600 },
    { 17, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F74058, 0, 602 },
    { 17, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F74008, 0, 604 },
    { 6, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F73FF0, 0, 620 },
    { 6, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F73FD8, 0, 625 },
    { 0, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F73F98, 0, 660 },
    { 0, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F73F6C, MSG_SCRIPT_FLAG_END, 662 },
};

#include "event_075_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent075Script[22] = {
    { 6, 2, 2, 1, { 0, 0, 0 }, &gUnkEu_09F67AA8, 0, 110 },
    { 17, 0, 0, 1, { 0, 0, 0 }, &gUnkEu_09F67ABC, 0, 210 },
    { 6, 2, 2, 1, { 0, 0, 0 }, &gUnkEu_09F67AD0, 0, 220 },
    { 17, 0, 0, 1, { 0, 0, 0 }, &gUnkEu_09F67AE4, 0, 230 },
    { 1, 5, 2, 1, { 0, 0, 0 }, &gUnkEu_09F67AF8, 0, 370 },
    { 2, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67B0C, 0, 390 },
    { 17, 2, 0, 1, { 0, 0, 0 }, &gUnkEu_09F67B20, 0, 400 },
    { 0, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67B34, 0, 410 },
    { 0, 5, 4, 1, { 0, 0, 0 }, &gUnkEu_09F67B48, 0, 412 },
    { 17, 2, 0, 1, { 0, 0, 0 }, &gUnkEu_09F67B5C, 0, 430 },
    { 17, 2, 4, 1, { 0, 0, 0 }, &gUnkEu_09F67B70, 0, 432 },
    { 0, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67B84, 0, 470 },
    { 17, 0, 0, 1, { 0, 0, 0 }, &gUnkEu_09F67B98, 0, 480 },
    { 6, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67BAC, 0, 490 },
    { 17, 2, 0, 1, { 0, 0, 0 }, &gUnkEu_09F67BC0, 0, 500 },
    { 0, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67BD4, 0, 580 },
    { 1, 0, 2, 1, { 0, 0, 0 }, &gUnkEu_09F67BE8, 0, 590 },
    { 17, 0, 0, 1, { 0, 0, 0 }, &gUnkEu_09F67BFC, 0, 600 },
    { 17, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F67C10, 0, 604 },
    { 6, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67C24, 0, 620 },
    { 0, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67C38, 0, 660 },
    { 0, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F67C4C, MSG_SCRIPT_FLAG_END, 662 },
};
#endif

static const EventCameraKeyframe sEvent075Camera[7] = {
    { -65496, 30464, 46592, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65286, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65241, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_BLACK | CAMERA_MODE_KEEP, 45, { 0, 0 }, NULL },
    { -65221, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65220, 81408, 76032, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 0, { 0, 0 }, NULL },
    { -65176, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_BLACK | CAMERA_MODE_KEEP, 45, { 0, 0 }, NULL },
    { -65136, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent075SoundCues[6] = {
    { SONG_BGM_PINOCCHIO_FIELD, 0, 0, 0 },
    { SONG_BGM_PINOCCHIO_FIELD, 250, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT4, 430, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT4, 605, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_PINOCCHIO_FIELD, 622, 0, 0 },
    { SONG_BGM_PINOCCHIO_FIELD, 775, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent075Track0[23] = {
    { 7, 0, { 0, 0 }, 9728, 51200, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 7, 80, { 0, 0 }, 13568, 59136, 0, 2, { 0, 0 }, 67, NULL, NULL },
    { 2, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 408, { 0, 0 }, 74496, 77568, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 32, 433, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 15, 459, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 501, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 540, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 4, 560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 575, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 579, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 31, 581, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 630, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 15, 648, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 661, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 31, 663, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 691, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 1, 693, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 696, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 12, 750, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 36, NULL, NULL },
    { 12, 760, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 32868, NULL, NULL },
};

static const EventCharaKeyframe sEvent075Track1[15] = {
    { 112, 20, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 117, 21, { 0, 0 }, 9728, 51200, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 117, 100, { 0, 0 }, 5632, 62464, 0, 112, { 0, 0 }, 3, NULL, NULL },
    { 113, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 369, { 0, 0 }, 75264, 87040, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 126, 371, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 589, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 126, 591, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 110, 705, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 113, 725, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 785, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 121, 800, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 36, NULL, NULL },
    { 121, 900, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 32868, NULL, NULL },
};

static const EventCharaKeyframe sEvent075Track2[13] = {
    { 144, 20, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 144, 21, { 0, 0 }, 9728, 51200, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 149, 110, { 0, 0 }, 20736, 55296, 0, 144, { 0, 0 }, 67, NULL, NULL },
    { 144, 205, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 389, { 0, 0 }, 87040, 77824, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 164, 391, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 702, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 145, 708, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 718, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 153, 740, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 152, 820, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 36, NULL, NULL },
    { 152, 920, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 32868, NULL, NULL },
};

static const EventCharaKeyframe sEvent075Track3[8] = {
    { 229, 115, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 230, 116, { 0, 0 }, 13568, 59136, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 233, 140, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 100, EventCharaHop, NULL },
    { 231, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 229, 622, { 0, 0 }, 80640, 81408, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 231, 665, { 0, 0 }, 80640, 81408, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 234, 690, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, EventCharaHop, NULL },
    { 234, 999, { 0, 0 }, 256000, 256000, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent075Track4[6] = {
    { 341, 111, { 0, 0 }, 54528, 47616, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 341, 162, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 343, 209, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 341, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 342, 430, { 0, 0 }, 87040, 87040, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 342, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent075Tracks[5] = {
    { sEvent075Track0, 0, { 0, 0, 0 } },
    { sEvent075Track1, 1, { 0, 0, 0 } },
    { sEvent075Track2, 2, { 0, 0, 0 } },
    { sEvent075Track3, 8, { 0, 0, 0 } },
    { sEvent075Track4, 18, { 0, 0, 0 } },
};

const EventSequenceDef gEvent075 = {
    5,
    { 0, 0, 0 },
    sEvent075Tracks,
    sEvent075Camera,
    sEvent075Script,
    sEvent075SoundCues,
    NULL,
    780,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_076_text.inc"
static const MessageScriptEntry sEvent076Script[31] = {
    { 10, 10, 1, 1, { 0, 0, 0 }, gEventTextUs_08F82080, 0, 300 },
    { 6, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08F82088, 0, 460 },
    { 1, 4, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8213E, 0, 470 },
    { 10, 7, 1, 1, { 0, 0, 0 }, gEventTextUs_08F82170, 0, 480 },
    { 0, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F82186, 0, 490 },
    { 10, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F821EC, 0, 500 },
    { 6, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08F82232, 0, 560 },
    { 10, 8, 1, 1, { 0, 0, 0 }, gEventTextUs_08F82256, 0, 570 },
    { 2, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F82270, 0, 580 },
    { 2, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F822D6, 0, 582 },
    { 2, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F8236A, 0, 584 },
    { 2, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08F823D4, 0, 586 },
    { 10, 8, 1, 1, { 0, 0, 0 }, gEventTextUs_08F82404, 0, 720 },
    { 10, 2, 4, 1, { 0, 0, 0 }, gEventTextUs_08F8243E, 0, 722 },
    { 10, 2, 4, 1, { 0, 0, 0 }, gEventTextUs_08F82502, 0, 724 },
    { 10, 8, 4, 1, { 0, 0, 0 }, gEventTextUs_08F82562, 0, 726 },
    { 6, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F825C0, 0, 740 },
    { 2, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F82610, 0, 750 },
    { 1, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8265A, 0, 760 },
    { 10, 11, 3, 1, { 0, 0, 0 }, gEventTextUs_08F82694, 0, 770 },
    { 1, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F826A0, 0, 780 },
    { 1, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F8271E, 0, 782 },
    { 0, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08F827B2, 0, 800 },
    { 10, 11, 1, 1, { 0, 0, 0 }, gEventTextUs_08F827E8, 0, 810 },
    { 10, 5, 4, 1, { 0, 0, 0 }, gEventTextUs_08F82818, 0, 812 },
    { 6, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8287A, 0, 830 },
    { 10, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08F828E0, 0, 840 },
    { 6, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08F82978, 0, 850 },
    { 0, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08F829B2, 0, 900 },
    { 1, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F829D8, 0, 910 },
    { 6, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08F82A18, MSG_SCRIPT_FLAG_END, 920 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent076Script[31] = {
    { 10, 10, 1, 3, { 0, 0, 0 }, gEventTextJp_08F72EBC, 0, 300 },
    { 6, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08F756C4, 0, 460 },
    { 1, 4, 1, 3, { 0, 0, 0 }, gEventTextJp_08F756AC, 0, 470 },
    { 10, 7, 1, 3, { 0, 0, 0 }, gEventTextJp_08F75698, 0, 480 },
    { 0, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F75664, 0, 490 },
    { 10, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F75640, 0, 500 },
    { 6, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08F75620, 0, 560 },
    { 10, 8, 1, 3, { 0, 0, 0 }, gEventTextJp_08F75614, 0, 570 },
    { 2, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F755E8, 0, 580 },
    { 2, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F75594, 0, 582 },
    { 2, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F75544, 0, 584 },
    { 2, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F75524, 0, 586 },
    { 10, 8, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7550C, 0, 720 },
    { 10, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08F754AC, 0, 722 },
    { 10, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08F7546C, 0, 724 },
    { 10, 8, 4, 3, { 0, 0, 0 }, gEventTextJp_08F75420, 0, 726 },
    { 6, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F753F8, 0, 740 },
    { 2, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F753D0, 0, 750 },
    { 1, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F753B8, 0, 760 },
    { 10, 11, 3, 3, { 0, 0, 0 }, gEventTextJp_08F753B0, 0, 770 },
    { 1, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7535C, 0, 780 },
    { 1, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F75300, 0, 782 },
    { 0, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08F752E8, 0, 800 },
    { 10, 11, 1, 3, { 0, 0, 0 }, gEventTextJp_08F752D0, 0, 810 },
    { 10, 5, 4, 3, { 0, 0, 0 }, gEventTextJp_08F752A0, 0, 812 },
    { 6, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F75274, 0, 830 },
    { 10, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F75230, 0, 840 },
    { 6, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F75200, 0, 850 },
    { 0, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F751F4, 0, 900 },
    { 1, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F751E4, 0, 910 },
    { 6, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08F751C8, MSG_SCRIPT_FLAG_END, 920 },
};

#include "event_076_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent076Script[31] = {
    { 10, 10, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67E2C, 0, 300 },
    { 6, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67E40, 0, 460 },
    { 1, 4, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67E54, 0, 470 },
    { 10, 7, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67E68, 0, 480 },
    { 0, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67E7C, 0, 490 },
    { 10, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67E90, 0, 500 },
    { 6, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67EA4, 0, 560 },
    { 10, 8, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67EB8, 0, 570 },
    { 2, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67ECC, 0, 580 },
    { 2, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F67EE0, 0, 582 },
    { 2, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F67EF4, 0, 584 },
    { 2, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F67F08, 0, 586 },
    { 10, 8, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67F1C, 0, 720 },
    { 10, 2, 4, 1, { 0, 0, 0 }, &gUnkEu_09F67F30, 0, 722 },
    { 10, 2, 4, 1, { 0, 0, 0 }, &gUnkEu_09F67F44, 0, 724 },
    { 10, 8, 4, 1, { 0, 0, 0 }, &gUnkEu_09F67F58, 0, 726 },
    { 6, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67F6C, 0, 740 },
    { 2, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67F80, 0, 750 },
    { 1, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67F94, 0, 760 },
    { 10, 11, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67FA8, 0, 770 },
    { 1, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67FBC, 0, 780 },
    { 1, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F67FD0, 0, 782 },
    { 0, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67FE4, 0, 800 },
    { 10, 11, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67FF8, 0, 810 },
    { 10, 5, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6800C, 0, 812 },
    { 6, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F68020, 0, 830 },
    { 10, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F68034, 0, 840 },
    { 6, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F68048, 0, 850 },
    { 0, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6805C, 0, 900 },
    { 1, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F68070, 0, 910 },
    { 6, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F68084, MSG_SCRIPT_FLAG_END, 920 },
};
#endif

static const EvSoundCue sEvent076SoundCues[6] = {
    { SONG_BGM_PINOCCHIO_FIELD, 0, 0, 0 },
    { SONG_SND_349, 501, 0, 0 },
    { SONG_BGM_EVENT2, 851, 0, 0 },
    { SONG_EV_RUMBLE, 852, 0, 0 },
    { SONG_EV_FLASH02, 1050, 0, 0 },
    { SONG_EV_RUMBLE, 1083, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent076Camera[5] = {
    { -65136, 44800, 93696, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65086, 57344, 91136, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -64685, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64486, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_MEDIUM | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64456, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_KEYFRAME_FLAG_SHAKE_MEDIUM | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 30, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent076Track0[9] = {
    { 4, 301, { 0, 0 }, 9472, 114944, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 14, 406, { 0, 0 }, 47360, 95232, 0, 4, { 0, 0 }, 99, NULL, NULL },
    { 4, 410, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 4, 795, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 36, 802, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 851, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 27, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 30, 901, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 29, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent076Track1[13] = {
    { 114, 301, { 0, 0 }, 10496, 117504, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 120, 445, { 0, 0 }, 62976, 92672, 0, 114, { 0, 0 }, 99, NULL, NULL },
    { 114, 449, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 114, 458, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 469, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 131, 471, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateSmokeTask },
    { 114, 759, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 126, 761, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 779, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 126, 783, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 851, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 134, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 134, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent076Track2[11] = {
    { 146, 301, { 0, 0 }, 9216, 116736, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 153, 429, { 0, 0 }, 49920, 85760, 0, 146, { 0, 0 }, 99, NULL, NULL },
    { 146, 433, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 146, 453, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 579, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 164, 587, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 749, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 164, 751, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 851, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 162, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 162, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent076Track3[11] = {
    { 231, 410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 231, 411, { 0, 0 }, 47360, 95232, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 234, 430, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, EventCharaHop, NULL },
    { 232, 440, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 231, 459, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 234, 461, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaHop, NULL },
    { 231, 559, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 234, 561, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaHop, NULL },
    { 231, 851, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 231, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 231, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent076Track4[25] = {
    { 237, 0, { 0, 0 }, 41984, 80640, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 246, 80, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 100, NULL, NULL },
    { 237, 82, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 237, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateQuestionTask },
    { 240, 165, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 240, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 252, 200, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 240, 204, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 240, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateQuestionTask },
    { 237, 285, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 255, 320, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 237, 501, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 238, 559, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateGlowNoseTask },
    { 238, 587, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 238, 719, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 238, 721, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 238, 769, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 238, 801, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 238, 809, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 256, 811, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 238, 851, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 256, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 238, 921, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 247, 930, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 100, NULL, NULL },
    { 247, 1000, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 32804, NULL, NULL },
};

static const EventCharaTrack sEvent076Tracks[5] = {
    { sEvent076Track0, 0, { 0, 0, 0 } },
    { sEvent076Track1, 1, { 0, 0, 0 } },
    { sEvent076Track2, 2, { 0, 0, 0 } },
    { sEvent076Track3, 8, { 0, 0, 0 } },
    { sEvent076Track4, 9, { 0, 0, 0 } },
};

const EventSequenceDef gEvent076 = {
    5,
    { 0, 0, 0 },
    sEvent076Tracks,
    sEvent076Camera,
    sEvent076Script,
    sEvent076SoundCues,
    NULL,
    1090,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    77,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_077_text.inc"
static const MessageScriptEntry sEvent077Script[3] = {
    { 0, 2, 2, 1, { 0, 0, 0 }, gEventTextUs_08F8380C, 0, 100 },
    { 10, 11, 0, 1, { 0, 0, 0 }, gEventTextUs_08F83840, 0, 150 },
    { 0, 3, 2, 1, { 0, 0, 0 }, gEventTextUs_08F83868, MSG_SCRIPT_FLAG_END, 170 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent077Script[3] = {
    { 0, 2, 2, 3, { 0, 0, 0 }, gEventTextJp_08F7626C, 0, 100 },
    { 10, 11, 0, 3, { 0, 0, 0 }, gEventTextJp_08F76248, 0, 150 },
    { 0, 3, 2, 3, { 0, 0, 0 }, gEventTextJp_08F76238, MSG_SCRIPT_FLAG_END, 170 },
};

#include "event_077_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent077Script[3] = {
    { 0, 2, 2, 1, { 0, 0, 0 }, &gUnkEu_09F67C60, 0, 100 },
    { 10, 11, 0, 1, { 0, 0, 0 }, &gUnkEu_09F67C74, 0, 150 },
    { 0, 3, 2, 1, { 0, 0, 0 }, &gUnkEu_09F67C88, MSG_SCRIPT_FLAG_END, 170 },
};
#endif

static const EventCameraKeyframe sEvent077Camera[1] = {
    { -65485, 104448, 98304, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent077SoundCues[1] = {
    { SONG_BGM_EVENT2, 0, EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent077Track1[6] = {
    { 20, 1, { 0, 0 }, 96000, 112640, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 4, 78, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 85, NULL, NULL },
    { 2, 90, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 85, NULL, NULL },
    { 3, 169, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 85, NULL, NULL },
    { 3, 171, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 80, NULL, CreateExclamationTask },
    { 18, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32853, NULL, NULL },
};

static const EventCharaKeyframe sEvent077Track0[1] = {
    { 934, 999, { 0, 0 }, 0, 12800, 0, 0, { 0, 0 }, 32770, NULL, NULL },
};

static const EventCharaTrack sEvent077Tracks[2] = {
    { sEvent077Track0, 96, { 0, 0, 0 } },
    { sEvent077Track1, 0, { 0, 0, 0 } },
};

const EventSequenceDef gEvent077 = {
    2,
    { 0, 0, 0 },
    sEvent077Tracks,
    sEvent077Camera,
    sEvent077Script,
    sEvent077SoundCues,
    NULL,
    280,
    0,
    1,
    0,
    0,
    0,
    0,
    152,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_078_text.inc"
static const MessageScriptEntry sEvent078Script[6] = {
    { 10, 8, 0, 1, { 0, 0, 0 }, gEventTextUs_08F83A24, 0, 100 },
    { 0, 2, 2, 1, { 0, 0, 0 }, gEventTextUs_08F83A50, 0, 110 },
    { 10, 11, 0, 1, { 0, 0, 0 }, gEventTextUs_08F83A7A, 0, 120 },
    { 0, 2, 2, 1, { 0, 0, 0 }, gEventTextUs_08F83A84, 0, 130 },
    { 10, 2, 0, 1, { 0, 0, 0 }, gEventTextUs_08F83AD8, 0, 140 },
    { 10, 14, 4, 1, { 0, 0, 0 }, gEventTextUs_08F83AEC, MSG_SCRIPT_FLAG_END, 142 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent078Script[6] = {
    { 10, 8, 0, 3, { 0, 0, 0 }, gEventTextJp_08F764DC, 0, 100 },
    { 0, 2, 2, 3, { 0, 0, 0 }, gEventTextJp_08F764C8, 0, 110 },
    { 10, 11, 0, 3, { 0, 0, 0 }, gEventTextJp_08F764BC, 0, 120 },
    { 0, 2, 2, 3, { 0, 0, 0 }, gEventTextJp_08F76494, 0, 130 },
    { 10, 2, 0, 3, { 0, 0, 0 }, gEventTextJp_08F76488, 0, 140 },
    { 10, 14, 4, 3, { 0, 0, 0 }, gEventTextJp_08F76474, MSG_SCRIPT_FLAG_END, 142 },
};

#include "event_078_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent078Script[6] = {
    { 10, 8, 0, 1, { 0, 0, 0 }, &gUnkEu_09F67C9C, 0, 100 },
    { 0, 2, 2, 1, { 0, 0, 0 }, &gUnkEu_09F67CB0, 0, 110 },
    { 10, 11, 0, 1, { 0, 0, 0 }, &gUnkEu_09F67CC4, 0, 120 },
    { 0, 2, 2, 1, { 0, 0, 0 }, &gUnkEu_09F67CD8, 0, 130 },
    { 10, 2, 0, 1, { 0, 0, 0 }, &gUnkEu_09F67CEC, 0, 140 },
    { 10, 14, 4, 1, { 0, 0, 0 }, &gUnkEu_09F67D00, MSG_SCRIPT_FLAG_END, 142 },
};
#endif

static const EventCameraKeyframe sEvent078Camera[8] = {
    { -65376, 104448, 98304, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65366, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_SMALL | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65346, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65336, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_SMALL | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65316, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65256, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_MEDIUM | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65186, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_KEYFRAME_FLAG_SHAKE_MEDIUM | CAMERA_MODE_KEEP, 30, { 0, 0 }, NULL },
    { -64936, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent078SoundCues[9] = {
    { SONG_BGM_EVENT2, 0, 0, 0 },
    { SONG_EV_RUMBLE, 160, 0, 0 },
    { SONG_EV_RUMBLE, 161, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_EV_RUMBLE, 190, 0, 0 },
    { SONG_EV_RUMBLE, 191, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_EV_RUMBLE, 220, 0, 0 },
    { SONG_EV_RUMBLE, 225, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_EV_FLASH02, 250, 0, 0 },
    { SONG_BGM_EVENT2, 255, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent078Track0[1] = {
    { 20, 30, { 0, 0 }, 96000, 112640, 0, 0, { 0, 0 }, 33106, NULL, NULL },
};

static const EventCharaKeyframe sEvent078Track1[3] = {
    { 942, 245, { 0, 0 }, 0, 12800, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 943, 299, { 0, 0 }, 0, 12800, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 942, 500, { 0, 0 }, 0, 12800, 0, 0, { 0, 0 }, 32770, NULL, NULL },
};

static const EventCharaTrack sEvent078Tracks[2] = {
    { sEvent078Track0, 0, { 0, 0, 0 } },
    { sEvent078Track1, 97, { 0, 0, 0 } },
};

const EventSequenceDef gEvent078 = {
    2,
    { 0, 0, 0 },
    sEvent078Tracks,
    sEvent078Camera,
    sEvent078Script,
    sEvent078SoundCues,
    NULL,
    400,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    80,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
static const MessageScriptEntry sEvent079Script[6] = {
    { 10, 8, 3, 1, { 0, 0, 0 }, gEventTextUs_08F83A24, 0, 250 },
    { 0, 2, 2, 1, { 0, 0, 0 }, gEventTextUs_08F83A50, 0, 320 },
    { 10, 11, 1, 1, { 0, 0, 0 }, gEventTextUs_08F83A7A, 0, 340 },
    { 0, 2, 2, 1, { 0, 0, 0 }, gEventTextUs_08F83A84, 0, 420 },
    { 10, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08F83AD8, 0, 630 },
    { 10, 14, 4, 1, { 0, 0, 0 }, gEventTextUs_08F83AEC, MSG_SCRIPT_FLAG_END, 635 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent079Script[6] = {
    { 10, 8, 3, 3, { 0, 0, 0 }, gEventTextJp_08F764DC, 0, 250 },
    { 0, 2, 2, 3, { 0, 0, 0 }, gEventTextJp_08F764C8, 0, 320 },
    { 10, 11, 1, 3, { 0, 0, 0 }, gEventTextJp_08F764BC, 0, 340 },
    { 0, 2, 2, 3, { 0, 0, 0 }, gEventTextJp_08F76798, 0, 420 },
    { 10, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F76488, 0, 630 },
    { 10, 14, 4, 3, { 0, 0, 0 }, gEventTextJp_08F76474, MSG_SCRIPT_FLAG_END, 635 },
};

#include "event_079_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent079Script[6] = {
    { 10, 8, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67C9C, 0, 250 },
    { 0, 2, 2, 1, { 0, 0, 0 }, &gUnkEu_09F67CB0, 0, 320 },
    { 10, 11, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67CC4, 0, 340 },
    { 0, 2, 2, 1, { 0, 0, 0 }, &gUnkEu_09F67CD8, 0, 420 },
    { 10, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67CEC, 0, 630 },
    { 10, 14, 4, 1, { 0, 0, 0 }, &gUnkEu_09F67D00, MSG_SCRIPT_FLAG_END, 635 },
};
#endif

static const EventCameraKeyframe sEvent079Camera[2] = {
    { -65535, 34304, 30720, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -63536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent079SoundCues[1] = {
    { 65535, 0, EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent079Track0[21] = {
    { 241, 50, { 0, 0 }, 37376, 36864, 0, 0, { 0, 0 }, 322, NULL, NULL },
    { 241, 80, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 238, 110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 244, 140, { 0, 0 }, 31232, 38144, 0, 236, { 0, 0 }, 259, NULL, NULL },
    { 238, 190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 238, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 241, 210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 250, 220, { 0, 0 }, 34304, 37632, 0, 239, { 0, 0 }, 323, NULL, NULL },
    { 241, 335, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 259, 342, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 241, 352, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 238, 362, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 238, 470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 238, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 256, NULL, CreateBalloonTask },
    { 238, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 247, 710, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 260, NULL, NULL },
    { 253, 770, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 324, NULL, NULL },
    { 247, 820, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 324, NULL, NULL },
    { 253, 890, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 260, NULL, NULL },
    { 247, 920, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 324, NULL, NULL },
    { 247, 2000, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 33028, NULL, NULL },
};

static const EventCharaTrack sEvent079Tracks[1] = {
    { sEvent079Track0, 9, { 0, 0, 0 } },
};

const EventSequenceDef gEvent079 = {
    1,
    { 0, 0, 0 },
    sEvent079Tracks,
    sEvent079Camera,
    sEvent079Script,
    sEvent079SoundCues,
    NULL,
    920,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    80,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_080_text.inc"
static const MessageScriptEntry sEvent080Script[14] = {
    { 6, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F841B8, 0, 230 },
    { 10, 5, 3, 1, { 0, 0, 0 }, gEventTextUs_08F841F4, 0, 240 },
    { 10, 5, 4, 1, { 0, 0, 0 }, gEventTextUs_08F84250, 0, 242 },
    { 10, 2, 4, 1, { 0, 0, 0 }, gEventTextUs_08F84282, 0, 244 },
    { 10, 2, 4, 1, { 0, 0, 0 }, gEventTextUs_08F842EC, 0, 246 },
    { 0, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08F84348, 0, 250 },
    { 1, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F843B6, 0, 260 },
    { 10, 5, 3, 1, { 0, 0, 0 }, gEventTextUs_08F84414, 0, 270 },
    { 6, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F84434, 0, 280 },
    { 10, 11, 3, 1, { 0, 0, 0 }, gEventTextUs_08F84464, 0, 290 },
    { 6, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8447A, 0, 300 },
    { 6, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F844B4, 0, 302 },
    { 0, 4, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8452E, 0, 310 },
    { 10, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08F84552, MSG_SCRIPT_FLAG_END, 320 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent080Script[14] = {
    { 6, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F76E98, 0, 230 },
    { 10, 5, 3, 3, { 0, 0, 0 }, gEventTextJp_08F76E68, 0, 240 },
    { 10, 5, 4, 3, { 0, 0, 0 }, gEventTextJp_08F76E40, 0, 242 },
    { 10, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08F76E0C, 0, 244 },
    { 10, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08F76DCC, 0, 246 },
    { 0, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F76DA4, 0, 250 },
    { 1, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F76D78, 0, 260 },
    { 10, 5, 3, 3, { 0, 0, 0 }, gEventTextJp_08F76D68, 0, 270 },
    { 6, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F76D50, 0, 280 },
    { 10, 11, 3, 3, { 0, 0, 0 }, gEventTextJp_08F76D44, 0, 290 },
    { 6, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F76D18, 0, 300 },
    { 6, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F76CCC, 0, 302 },
    { 0, 4, 1, 3, { 0, 0, 0 }, gEventTextJp_08F76CB0, 0, 310 },
    { 10, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F76C84, MSG_SCRIPT_FLAG_END, 320 },
};

#include "event_080_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent080Script[14] = {
    { 6, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67D14, 0, 230 },
    { 10, 5, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67D28, 0, 240 },
    { 10, 5, 4, 1, { 0, 0, 0 }, &gUnkEu_09F67D3C, 0, 242 },
    { 10, 2, 4, 1, { 0, 0, 0 }, &gUnkEu_09F67D50, 0, 244 },
    { 10, 2, 4, 1, { 0, 0, 0 }, &gUnkEu_09F67D64, 0, 246 },
    { 0, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67D78, 0, 250 },
    { 1, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67D8C, 0, 260 },
    { 10, 5, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67DA0, 0, 270 },
    { 6, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67DB4, 0, 280 },
    { 10, 11, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67DC8, 0, 290 },
    { 6, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67DDC, 0, 300 },
    { 6, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F67DF0, 0, 302 },
    { 0, 4, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67E04, 0, 310 },
    { 10, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67E18, MSG_SCRIPT_FLAG_END, 320 },
};
#endif

static const EventCameraKeyframe sEvent080Camera[2] = {
    { -65436, 45568, 95488, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64986, 40704, 98048, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent080SoundCues[3] = {
    { SONG_BGM_PINOCCHIO_FIELD, 0, 0, 0 },
    { SONG_EV_DL_JUMP, 259, 0, 0 },
    { SONG_BGM_PINOCCHIO_FIELD, 545, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent080Track0[12] = {
    { 21, 130, { 0, 0 }, 46080, 95488, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 22, 145, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 155, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 249, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 31, 251, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 351, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 12, 360, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 36, NULL, NULL },
    { 13, 370, { 0, 0 }, 0, 0, 0, 192, { 0, 0 }, 36, NULL, NULL },
    { 12, 999, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 36, NULL, NULL },
    { 2, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent080Track1[9] = {
    { 123, 135, { 0, 0 }, 49920, 100608, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 124, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 110, 155, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 113, 259, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 130, 261, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 113, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 121, 999, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 36, NULL, NULL },
    { 113, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent080Track2[7] = {
    { 158, 140, { 0, 0 }, 36864, 94208, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 159, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 165, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 143, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 152, 999, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 36, NULL, NULL },
    { 143, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent080Track3[10] = {
    { 238, 0, { 0, 0 }, 81408, 81920, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 247, 125, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 36, NULL, NULL },
    { 238, 128, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 238, 145, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 250, 160, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 241, 289, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 259, 291, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 241, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 241, 390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 238, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent080Track4[8] = {
    { 229, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 229, 161, { 0, 0 }, 46080, 95488, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 233, 180, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, EventCharaHop, NULL },
    { 230, 188, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 229, 321, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 232, 330, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 234, 350, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, EventCharaHop, NULL },
    { 229, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32770, NULL, NULL },
};

static const EventCharaTrack sEvent080Tracks[5] = {
    { sEvent080Track0, 0, { 0, 0, 0 } },
    { sEvent080Track1, 1, { 0, 0, 0 } },
    { sEvent080Track2, 2, { 0, 0, 0 } },
    { sEvent080Track3, 9, { 0, 0, 0 } },
    { sEvent080Track4, 8, { 0, 0, 0 } },
};

const EventSequenceDef gEvent080 = {
    5,
    { 0, 0, 0 },
    sEvent080Tracks,
    sEvent080Camera,
    sEvent080Script,
    sEvent080SoundCues,
    NULL,
    550,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_081_text.inc"
static const MessageScriptEntry sEvent081Script[4] = {
    { 2, 0, 2, 1, { 0, 0, 0 }, gEventTextUs_08F84E24, 0, 300 },
    { 0, 2, 2, 1, { 0, 0, 0 }, gEventTextUs_08F84E6C, 0, 310 },
    { 1, 0, 0, 1, { 0, 0, 0 }, gEventTextUs_08F84EB4, 0, 320 },
    { 0, 1, 2, 1, { 0, 0, 0 }, gEventTextUs_08F84F12, MSG_SCRIPT_FLAG_END, 330 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent081Script[4] = {
    { 2, 0, 2, 3, { 0, 0, 0 }, gEventTextJp_08F776D4, 0, 300 },
    { 0, 2, 2, 3, { 0, 0, 0 }, gEventTextJp_08F776A4, 0, 310 },
    { 1, 0, 0, 3, { 0, 0, 0 }, gEventTextJp_08F77670, 0, 320 },
    { 0, 1, 2, 3, { 0, 0, 0 }, gEventTextJp_08F7763C, MSG_SCRIPT_FLAG_END, 330 },
};

#include "event_081_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent081Script[4] = {
    { 2, 0, 2, 1, { 0, 0, 0 }, &gUnkEu_09F682A0, 0, 300 },
    { 0, 2, 2, 1, { 0, 0, 0 }, &gUnkEu_09F682B4, 0, 310 },
    { 1, 0, 0, 1, { 0, 0, 0 }, &gUnkEu_09F682C8, 0, 320 },
    { 0, 1, 2, 1, { 0, 0, 0 }, &gUnkEu_09F682DC, MSG_SCRIPT_FLAG_END, 330 },
};
#endif

static const EventCameraKeyframe sEvent081Camera[1] = {
    { -64537, 33792, 32768, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent081SoundCues[1] = {
    { SONG_BGM_EVENT1, 0, EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent081Track0[16] = {
    { 12, 0, { 0, 0 }, 71168, 23040, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 12, 120, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 36, NULL, NULL },
    { 2, 124, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 2, 135, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 145, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 0, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 155, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 9, 205, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 4, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 0, 260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 335, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 19, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent081Track1[18] = {
    { 152, 0, { 0, 0 }, 72192, 15872, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 152, 190, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 36, NULL, NULL },
    { 144, 194, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 144, 188, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 143, 195, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 199, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 299, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 164, 301, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 311, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 331, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 157, 395, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 158, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent081Track2[18] = {
    { 121, 0, { 0, 0 }, 90880, 21504, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 121, 160, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 36, NULL, NULL },
    { 121, 164, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 112, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 175, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 195, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 215, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 245, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 112, 265, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 319, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 126, 321, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 341, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 110, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 122, 395, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 123, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent081Track3[3] = {
    { 472, 348, { 0, 0 }, 78848, 20480, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 474, 505, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 260, NULL, NULL },
    { 472, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33029, NULL, NULL },
};

static const EventCharaKeyframe sEvent081Track4[3] = {
    { 472, 340, { 0, 0 }, 79872, 13312, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 474, 500, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 260, NULL, NULL },
    { 472, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33029, NULL, NULL },
};

static const EventCharaKeyframe sEvent081Track5[3] = {
    { 472, 346, { 0, 0 }, 89600, 21504, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 474, 508, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 260, NULL, NULL },
    { 472, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33029, NULL, NULL },
};

static const EventCharaKeyframe sEvent081Track6[3] = {
    { 472, 388, { 0, 0 }, 78848, 20480, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 474, 505, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 260, NULL, NULL },
    { 472, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33029, NULL, NULL },
};

static const EventCharaKeyframe sEvent081Track7[3] = {
    { 472, 380, { 0, 0 }, 79872, 13312, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 474, 500, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 260, NULL, NULL },
    { 472, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33029, NULL, NULL },
};

static const EventCharaKeyframe sEvent081Track8[3] = {
    { 472, 386, { 0, 0 }, 89600, 21504, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 474, 508, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 260, NULL, NULL },
    { 472, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33029, NULL, NULL },
};

static const EventCharaTrack sEvent081Tracks[9] = {
    { sEvent081Track0, 0, { 0, 0, 0 } },
    { sEvent081Track1, 2, { 0, 0, 0 } },
    { sEvent081Track2, 1, { 0, 0, 0 } },
    { sEvent081Track3, 40, { 0, 0, 0 } },
    { sEvent081Track4, 40, { 0, 0, 0 } },
    { sEvent081Track5, 40, { 0, 0, 0 } },
    { sEvent081Track6, 40, { 0, 0, 0 } },
    { sEvent081Track7, 40, { 0, 0, 0 } },
    { sEvent081Track8, 40, { 0, 0, 0 } },
};

const EventSequenceDef gEvent081 = {
    9,
    { 0, 0, 0 },
    sEvent081Tracks,
    sEvent081Camera,
    sEvent081Script,
    sEvent081SoundCues,
    NULL,
    560,
    0,
    1,
    0,
    0,
    0,
    0,
    121,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_082_text.inc"
static const MessageScriptEntry sEvent082Script[3] = {
    { 0, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F85A48, 0, 100 },
    { 2, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08F85A54, 0, 180 },
    { 6, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F85A68, MSG_SCRIPT_FLAG_END, 200 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent082Script[3] = {
    { 0, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F78204, 0, 100 },
    { 2, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F781F8, 0, 180 },
    { 6, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F781B4, MSG_SCRIPT_FLAG_END, 200 },
};

#include "event_082_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent082Script[3] = {
    { 0, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6814C, 0, 100 },
    { 2, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F68160, 0, 180 },
    { 6, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F68174, MSG_SCRIPT_FLAG_END, 200 },
};
#endif

static const EventCameraKeyframe sEvent082Camera[6] = {
    { -65416, 30720, 32768, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65316, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_MEDIUM | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65206, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_MEDIUM | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65206, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_LARGE | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65186, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_KEYFRAME_FLAG_SHAKE_LARGE | CAMERA_MODE_KEEP, 20, { 0, 0 }, NULL },
    { -64537, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent082SoundCues[5] = {
    { SONG_BGM_EVENT1, 0, 0, 0 },
    { SONG_EV_RUMBLE, 120, 0, 0 },
    { SONG_EV_RUMBLE, 300, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_EV_FLASH02, 330, 0, 0 },
    { SONG_BGM_EVENT1, 331, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent082Track0[6] = {
    { 21, 80, { 0, 0 }, 34816, 40960, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 22, 90, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 29, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 29, 330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 29, 350, { 0, 0 }, 69120, 28160, -10240, 4, { 0, 0 }, 32867, NULL, NULL },
};

static const EventCharaKeyframe sEvent082Track1[6] = {
    { 123, 84, { 0, 0 }, 37376, 47360, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 124, 94, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 134, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 134, 330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 134, 350, { 0, 0 }, 66560, 33280, -12800, 114, { 0, 0 }, 32867, NULL, NULL },
};

static const EventCharaKeyframe sEvent082Track2[6] = {
    { 158, 88, { 0, 0 }, 22016, 38400, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 159, 98, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 162, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 162, 330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 162, 350, { 0, 0 }, 69120, 25600, -7680, 146, { 0, 0 }, 32867, NULL, NULL },
};

static const EventCharaTrack sEvent082Tracks[3] = {
    { sEvent082Track0, 0, { 0, 0, 0 } },
    { sEvent082Track1, 1, { 0, 0, 0 } },
    { sEvent082Track2, 2, { 0, 0, 0 } },
};

const EventSequenceDef gEvent082 = {
    3,
    { 0, 0, 0 },
    sEvent082Tracks,
    sEvent082Camera,
    sEvent082Script,
    sEvent082SoundCues,
    NULL,
    530,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    86,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_083_text.inc"
static const MessageScriptEntry sEvent083Script[5] = {
    { 1, 1, 0, 1, { 0, 0, 0 }, gEventTextUs_08F85EB4, 0, 100 },
    { 2, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08F85F10, 0, 481 },
    { 0, 7, 1, 1, { 0, 0, 0 }, gEventTextUs_08F85F30, 0, 500 },
    { 6, 1, 2, 1, { 0, 0, 0 }, gEventTextUs_08F85F5E, 0, 540 },
    { 2, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8603E, MSG_SCRIPT_FLAG_YES_NO | MSG_SCRIPT_FLAG_END, 580 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent083Script[5] = {
    { 1, 1, 0, 3, { 0, 0, 0 }, gEventTextJp_08F786D4, 0, 100 },
    { 2, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F786C0, 0, 481 },
    { 0, 7, 1, 3, { 0, 0, 0 }, gEventTextJp_08F786B0, 0, 500 },
    { 6, 1, 2, 3, { 0, 0, 0 }, gEventTextJp_08F78658, 0, 540 },
    { 2, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F78640, MSG_SCRIPT_FLAG_YES_NO | MSG_SCRIPT_FLAG_END, 580 },
};

#include "event_083_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent083Script[5] = {
    { 1, 1, 0, 1, { 0, 0, 0 }, &gUnkEu_09F68098, 0, 100 },
    { 2, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F680AC, 0, 481 },
    { 0, 7, 1, 1, { 0, 0, 0 }, &gUnkEu_09F680C0, 0, 500 },
    { 6, 1, 2, 1, { 0, 0, 0 }, &gUnkEu_09F680D4, 0, 540 },
    { 2, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F680E8, MSG_SCRIPT_FLAG_YES_NO | MSG_SCRIPT_FLAG_END, 580 },
};
#endif

static const EventCameraKeyframe sEvent083Camera[2] = {
    { -65416, 33792, 35840, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64537, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent083SoundCues[2] = {
    { SONG_BGM_EVENT1, 0, 0, 0 },
    { SONG_BGM_EVENT1, 599, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent083Track0[4] = {
    { 2, 200, { 0, 0 }, 35072, 36864, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 2, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 2, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 32, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent083Track1[4] = {
    { 136, 101, { 0, 0 }, 40448, 42752, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 112, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 112, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent083Track2[9] = {
    { 144, 200, { 0, 0 }, 26112, 39168, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 144, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 144, 460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 143, 465, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 164, 482, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 164, 581, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent083Track3[3] = {
    { 229, 510, { 0, 0 }, 24832, 45056, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 229, 520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 231, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent083Tracks[4] = {
    { sEvent083Track0, 0, { 0, 0, 0 } },
    { sEvent083Track1, 1, { 0, 0, 0 } },
    { sEvent083Track2, 2, { 0, 0, 0 } },
    { sEvent083Track3, 8, { 0, 0, 0 } },
};

const EventSequenceDef gEvent083 = {
    4,
    { 0, 0, 0 },
    sEvent083Tracks,
    sEvent083Camera,
    sEvent083Script,
    sEvent083SoundCues,
    NULL,
    600,
    0,
    1,
    0,
    0,
    0,
    0,
    121,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_084_text.inc"
static const MessageScriptEntry sEvent084Script[3] = {
    { 6, 1, 2, 1, { 0, 0, 0 }, gEventTextUs_08F8645C, 0, 100 },
    { 0, 7, 1, 1, { 0, 0, 0 }, gEventTextUs_08F864D2, 0, 180 },
    { 2, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F86542, MSG_SCRIPT_FLAG_YES_NO | MSG_SCRIPT_FLAG_END, 200 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent084Script[3] = {
    { 6, 1, 2, 3, { 0, 0, 0 }, gEventTextJp_08F78AF0, 0, 100 },
    { 0, 7, 1, 3, { 0, 0, 0 }, gEventTextJp_08F78ABC, 0, 180 },
    { 2, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F78640, MSG_SCRIPT_FLAG_YES_NO | MSG_SCRIPT_FLAG_END, 200 },
};

#include "event_084_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent084Script[3] = {
    { 6, 1, 2, 1, { 0, 0, 0 }, &gUnkEu_09F680FC, 0, 100 },
    { 0, 7, 1, 1, { 0, 0, 0 }, &gUnkEu_09F68110, 0, 180 },
    { 2, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F68124, MSG_SCRIPT_FLAG_YES_NO | MSG_SCRIPT_FLAG_END, 200 },
};
#endif

static const EventCameraKeyframe sEvent084Camera[2] = {
    { -65416, 33792, 35840, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64537, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent084SoundCues[2] = {
    { SONG_BGM_EVENT1, 0, 0, 0 },
    { SONG_BGM_EVENT1, 219, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent084Track0[2] = {
    { 2, 200, { 0, 0 }, 35072, 36864, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 2, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent084Track1[2] = {
    { 114, 101, { 0, 0 }, 40448, 42752, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 114, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent084Track2[2] = {
    { 144, 200, { 0, 0 }, 26112, 39168, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 164, 201, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent084Track3[2] = {
    { 231, 510, { 0, 0 }, 24832, 45056, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 231, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent084Tracks[4] = {
    { sEvent084Track0, 0, { 0, 0, 0 } },
    { sEvent084Track1, 1, { 0, 0, 0 } },
    { sEvent084Track2, 2, { 0, 0, 0 } },
    { sEvent084Track3, 8, { 0, 0, 0 } },
};

const EventSequenceDef gEvent084 = {
    4,
    { 0, 0, 0 },
    sEvent084Tracks,
    sEvent084Camera,
    sEvent084Script,
    sEvent084SoundCues,
    NULL,
    220,
    0,
    1,
    0,
    0,
    0,
    0,
    121,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_085_text.inc"
static const MessageScriptEntry sEvent085Script[1] = {
    { 0, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08F86778, MSG_SCRIPT_FLAG_END, 230 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent085Script[1] = {
    { 0, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F78CF0, MSG_SCRIPT_FLAG_END, 230 },
};

#include "event_085_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent085Script[1] = {
    { 0, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F68138, MSG_SCRIPT_FLAG_END, 230 },
};
#endif

static const EventCameraKeyframe sEvent085Camera[1] = {
    { -64537, 33792, 32768, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent085SoundCues[1] = {
    { SONG_BGM_EVENT1, 0, EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent085Track0[9] = {
    { 12, 0, { 0, 0 }, 71168, 23040, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 12, 90, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 36, NULL, NULL },
    { 2, 93, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 2, 135, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 145, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 0, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 19, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent085Track2[10] = {
    { 152, 0, { 0, 0 }, 72192, 14592, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 152, 150, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 36, NULL, NULL },
    { 144, 153, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 144, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 143, 205, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 215, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 245, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 157, 255, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 158, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent085Track1[10] = {
    { 121, 0, { 0, 0 }, 89600, 20480, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 121, 128, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 36, NULL, NULL },
    { 121, 131, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 112, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 111, 175, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 113, 185, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 122, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 123, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent085Tracks[3] = {
    { sEvent085Track0, 0, { 0, 0, 0 } },
    { sEvent085Track1, 1, { 0, 0, 0 } },
    { sEvent085Track2, 2, { 0, 0, 0 } },
};

const EventSequenceDef gEvent085 = {
    3,
    { 0, 0, 0 },
    sEvent085Tracks,
    sEvent085Camera,
    sEvent085Script,
    sEvent085SoundCues,
    NULL,
    300,
    0,
    1,
    0,
    0,
    0,
    0,
    121,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_086_text.inc"
static const MessageScriptEntry sEvent086Script[14] = {
    { 0, 6, 1, 1, { 0, 0, 0 }, gEventTextUs_08F86C70, 0, 400 },
    { 2, 0, 2, 1, { 0, 0, 0 }, gEventTextUs_08F86CEE, 0, 460 },
    { 6, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F86D2C, 0, 650 },
    { 0, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F86D8A, 0, 680 },
    { 6, 3, 2, 1, { 0, 0, 0 }, gEventTextUs_08F86E16, 0, 690 },
    { 6, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F86E92, 0, 692 },
    { 0, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F86EE8, 0, 700 },
    { 6, 0, 2, 1, { 0, 0, 0 }, gEventTextUs_08F86F0C, 0, 710 },
    { 6, 3, 4, 1, { 0, 0, 0 }, gEventTextUs_08F86F90, 0, 712 },
    { 6, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F87022, 0, 714 },
    { 0, 4, 1, 1, { 0, 0, 0 }, gEventTextUs_08F87098, 0, 730 },
    { 0, 4, 4, 1, { 0, 0, 0 }, gEventTextUs_08F870E6, 0, 732 },
    { 0, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08F8717A, 0, 734 },
    { 6, 3, 2, 1, { 0, 0, 0 }, gEventTextUs_08F871F8, MSG_SCRIPT_FLAG_END, 750 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent086Script[14] = {
    { 0, 6, 1, 3, { 0, 0, 0 }, gEventTextJp_08F795D8, 0, 400 },
    { 2, 0, 2, 3, { 0, 0, 0 }, gEventTextJp_08F795B8, 0, 460 },
    { 6, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F79578, 0, 650 },
    { 0, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F79538, 0, 680 },
    { 6, 3, 2, 3, { 0, 0, 0 }, gEventTextJp_08F79508, 0, 690 },
    { 6, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F794D8, 0, 692 },
    { 0, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F794C8, 0, 700 },
    { 6, 0, 2, 3, { 0, 0, 0 }, gEventTextJp_08F79474, 0, 710 },
    { 6, 3, 4, 3, { 0, 0, 0 }, gEventTextJp_08F7941C, 0, 712 },
    { 6, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F793C0, 0, 714 },
    { 0, 4, 1, 3, { 0, 0, 0 }, gEventTextJp_08F793A8, 0, 730 },
    { 0, 4, 4, 3, { 0, 0, 0 }, gEventTextJp_08F79358, 0, 732 },
    { 0, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F7931C, 0, 734 },
    { 6, 3, 2, 3, { 0, 0, 0 }, gEventTextJp_08F792F8, MSG_SCRIPT_FLAG_END, 750 },
};

#include "event_086_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent086Script[14] = {
    { 0, 6, 1, 1, { 0, 0, 0 }, &gUnkEu_09F68188, 0, 400 },
    { 2, 0, 2, 1, { 0, 0, 0 }, &gUnkEu_09F6819C, 0, 460 },
    { 6, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F681B0, 0, 650 },
    { 0, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F681C4, 0, 680 },
    { 6, 3, 2, 1, { 0, 0, 0 }, &gUnkEu_09F681D8, 0, 690 },
    { 6, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F681EC, 0, 692 },
    { 0, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F68200, 0, 700 },
    { 6, 0, 2, 1, { 0, 0, 0 }, &gUnkEu_09F68214, 0, 710 },
    { 6, 3, 4, 1, { 0, 0, 0 }, &gUnkEu_09F68228, 0, 712 },
    { 6, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6823C, 0, 714 },
    { 0, 4, 1, 1, { 0, 0, 0 }, &gUnkEu_09F68250, 0, 730 },
    { 0, 4, 4, 1, { 0, 0, 0 }, &gUnkEu_09F68264, 0, 732 },
    { 0, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F68278, 0, 734 },
    { 6, 3, 2, 1, { 0, 0, 0 }, &gUnkEu_09F6828C, MSG_SCRIPT_FLAG_END, 750 },
};
#endif

static const EventCameraKeyframe sEvent086Camera[9] = {
    { -65536, 78592, 68352, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, NULL },
    { -65286, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 150, { 0, 0 }, NULL },
    { -65281, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65216, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_BLACK | CAMERA_MODE_KEEP, 60, { 0, 0 }, NULL },
    { -65166, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_BLACK | CAMERA_MODE_KEEP, 50, { 0, 0 }, NULL },
    { -65075, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64956, 37888, 43264, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 60, { 0, 0 }, NULL },
    { -64876, 78592, 68352, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 60, { 0, 0 }, NULL },
    { -64537, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent086SoundCues[2] = {
    { SONG_BGM_EVENT4, 692, 0, 0 },
    { SONG_BGM_EVENT4, 795, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent086Track0[6] = {
    { 69, 0, { 0, 0 }, 82944, 75776, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 69, 316, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateDownTask },
    { 2, 470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 679, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 36, 699, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent086Track1[11] = {
    { 146, 0, { 0, 0 }, 78848, 82432, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 169, 316, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateDownTask },
    { 146, 401, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 415, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 425, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 440, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 459, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 165, 470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 142, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 691, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 142, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent086Track2[4] = {
    { 114, 0, { 0, 0 }, 91648, 82432, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 137, 316, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateDownTask },
    { 114, 691, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 113, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent086Track3[6] = {
    { 231, 580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 231, 621, { 0, 0 }, 81920, 76288, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 234, 649, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, EventCharaHop, NULL },
    { 231, 681, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 229, 686, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 229, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent086Tracks[4] = {
    { sEvent086Track0, 0, { 0, 0, 0 } },
    { sEvent086Track1, 2, { 0, 0, 0 } },
    { sEvent086Track2, 1, { 0, 0, 0 } },
    { sEvent086Track3, 8, { 0, 0, 0 } },
};

const EventSequenceDef gEvent086 = {
    4,
    { 0, 0, 0 },
    sEvent086Tracks,
    sEvent086Camera,
    sEvent086Script,
    sEvent086SoundCues,
    NULL,
    800,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_087_text.inc"
static const MessageScriptEntry sEvent087Script[18] = {
    { 2, 3, 2, 1, { 0, 0, 0 }, gEventTextUs_08F878EC, 0, 260 },
    { 1, 1, 0, 1, { 0, 0, 0 }, gEventTextUs_08F8798A, 0, 280 },
    { 1, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08F879DE, 0, 282 },
    { 2, 3, 2, 1, { 0, 0, 0 }, gEventTextUs_08F87A4E, 0, 300 },
    { 1, 4, 0, 1, { 0, 0, 0 }, gEventTextUs_08F87A78, 0, 315 },
    { 11, 0, 0, 1, { 0, 0, 0 }, gEventTextUs_08F87A8C, MSG_SCRIPT_FLAG_SILHOUETTE, 330 },
    { 1, 5, 3, 1, { 0, 0, 0 }, gEventTextUs_08F87AC2, 0, 650 },
    { 11, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F87AE0, 0, 700 },
    { 11, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F87B46, 0, 702 },
    { 11, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F87BBE, 0, 740 },
    { 11, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F87C10, 0, 742 },
    { 11, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08F87C3C, 0, 780 },
    { 11, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F87CDE, 0, 782 },
    { 1, 4, 2, 1, { 0, 0, 0 }, gEventTextUs_08F87D5C, 0, 800 },
    { 11, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08F87D7C, 0, 810 },
    { 0, 0, 2, 1, { 0, 0, 0 }, gEventTextUs_08F87DF6, 0, 820 },
    { 11, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F87E22, 0, 830 },
    { 0, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08F87E56, MSG_SCRIPT_FLAG_END, 880 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent087Script[19] = {
    { 2, 3, 2, 3, { 0, 0, 0 }, gEventTextJp_08F79FC0, 0, 260 },
    { 1, 1, 0, 3, { 0, 0, 0 }, gEventTextJp_08F79FA0, 0, 280 },
    { 1, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F79F5C, 0, 282 },
    { 2, 3, 2, 3, { 0, 0, 0 }, gEventTextJp_08F79F48, 0, 300 },
    { 1, 4, 0, 3, { 0, 0, 0 }, gEventTextJp_08F79F3C, 0, 315 },
    { 11, 0, 0, 3, { 0, 0, 0 }, gEventTextJp_08F79F1C, MSG_SCRIPT_FLAG_SILHOUETTE, 330 },
    { 1, 5, 3, 3, { 0, 0, 0 }, gEventTextJp_08F79F04, 0, 650 },
    { 11, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F79ECC, 0, 700 },
    { 11, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F79E98, 0, 702 },
    { 11, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F79E74, 0, 740 },
    { 11, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F79E54, 0, 742 },
    { 11, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F79DFC, 0, 780 },
    { 11, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F79DB4, 0, 782 },
    { 1, 4, 2, 3, { 0, 0, 0 }, gEventTextJp_08F79D9C, 0, 800 },
    { 11, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F79D68, 0, 810 },
    { 0, 0, 2, 3, { 0, 0, 0 }, gEventTextJp_08F79D4C, 0, 820 },
    { 11, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F79D38, 0, 830 },
    { 11, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08F79D24, 0, 832 },
    { 0, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F781F8, MSG_SCRIPT_FLAG_END, 880 },
};

#include "event_087_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent087Script[18] = {
    { 2, 3, 2, 1, { 0, 0, 0 }, &gUnkEu_09F66950, 0, 260 },
    { 1, 1, 0, 1, { 0, 0, 0 }, &gUnkEu_09F66964, 0, 280 },
    { 1, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F66978, 0, 282 },
    { 2, 3, 2, 1, { 0, 0, 0 }, &gUnkEu_09F6698C, 0, 300 },
    { 1, 4, 0, 1, { 0, 0, 0 }, &gUnkEu_09F669A0, 0, 315 },
    { 11, 0, 0, 1, { 0, 0, 0 }, &gUnkEu_09F669B4, MSG_SCRIPT_FLAG_SILHOUETTE, 330 },
    { 1, 5, 3, 1, { 0, 0, 0 }, &gUnkEu_09F669C8, 0, 650 },
    { 11, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F669DC, 0, 700 },
    { 11, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F669F0, 0, 702 },
    { 11, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F66A04, 0, 740 },
    { 11, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F66A18, 0, 742 },
    { 11, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F66A2C, 0, 780 },
    { 11, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F66A40, 0, 782 },
    { 1, 4, 2, 1, { 0, 0, 0 }, &gUnkEu_09F66A54, 0, 800 },
    { 11, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F66A68, 0, 810 },
    { 0, 0, 2, 1, { 0, 0, 0 }, &gUnkEu_09F66A7C, 0, 820 },
    { 11, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F66A90, 0, 830 },
    { 0, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66AA4, MSG_SCRIPT_FLAG_END, 880 },
};
#endif

static const EvSoundCue sEvent087SoundCues[6] = {
    { 65535, 0, 0, 0 },
    { SONG_EV_DL_JUMP, 313, 0, 0 },
    { SONG_SND_347, 490, 0, 0 },
    { SONG_EV_DL_JUMP, 649, 0, 0 },
    { SONG_BGM_HALLOWEEN_FIELD, 700, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT2, 833, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent087Camera[3] = {
    { -65536, 30720, 20480, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, NULL },
    { -65205, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 80, { 0, 0 }, NULL },
    { -64537, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EventBgEffectEntry sEvent087BgEffects[6] = {
    { 331, 0, 0, 0, 0 },
    { 332, 0, 0, 0, 0x4 },
    { 488, 0, 0, 0, 0 },
    { 640, 0, 0, 0, 0x1 },
    { 680, 0, 0, 0, 0x2 },
    { 701, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent087Track0[22] = {
    { 4, 0, { 0, 0 }, -9728, 43264, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 9, 150, { 0, 0 }, 20480, 25344, 0, 4, { 0, 0 }, 67, NULL, NULL },
    { 4, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 0, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 0, 190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 0, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 1, 331, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 1, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 2, 390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 435, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 27, 640, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 28, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 4, 819, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 34, 835, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 27, 990, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32832, NULL, CreateExclamationTask },
};

static const EventCharaKeyframe sEvent087Track1[11] = {
    { 288, 490, { 0, 0 }, 256000, 256000, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 295, 640, { 0, 0 }, 37888, 22016, 0, 0, { 0, 0 }, 1026, NULL, NULL },
    { 294, 681, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 295, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaFadeIn, NULL },
    { 288, 743, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 289, 748, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 296, 775, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 289, 779, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 292, 809, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 288, 831, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 292, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent087Track2[31] = {
    { 112, 0, { 0, 0 }, -6400, 52224, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 119, 150, { 0, 0 }, 25600, 30464, 0, 114, { 0, 0 }, 67, NULL, NULL },
    { 114, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 111, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 113, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 110, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 110, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 261, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 110, 270, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 279, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 126, 283, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 309, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 130, 316, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 331, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 110, 390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 415, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 110, 430, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 110, 470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 133, 640, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 114, 641, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 133, 738, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaHopHigh, NULL },
    { 114, 799, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 131, 801, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateSmokeTask },
    { 114, 835, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 133, 990, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32832, NULL, CreateExclamationTask },
};

static const EventCharaKeyframe sEvent087Track3[27] = {
    { 144, 20, { 0, 0 }, -17920, 45824, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 151, 150, { 0, 0 }, 12288, 26368, 0, 146, { 0, 0 }, 67, NULL, NULL },
    { 143, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 143, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 143, 190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 145, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 143, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 259, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 164, 261, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 299, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 164, 301, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 331, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 144, 390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 425, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 440, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 475, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 161, 640, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 161, 734, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 146, 835, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 161, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32832, NULL, CreateExclamationTask },
};

static const EventCharaKeyframe sEvent087Track4[3] = {
    { 477, 833, { 0, 0 }, 256000, 256000, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 475, 853, { 0, 0 }, 40448, 32768, 0, 0, { 0, 0 }, 16642, NULL, NULL },
    { 472, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33029, NULL, NULL },
};

static const EventCharaKeyframe sEvent087Track5[3] = {
    { 477, 838, { 0, 0 }, 256000, 256000, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 475, 858, { 0, 0 }, 38656, 24832, 0, 0, { 0, 0 }, 16642, NULL, NULL },
    { 472, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33029, NULL, NULL },
};

static const EventCharaKeyframe sEvent087Track6[3] = {
    { 477, 843, { 0, 0 }, 256000, 256000, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 475, 863, { 0, 0 }, 33792, 20224, 0, 0, { 0, 0 }, 16642, NULL, NULL },
    { 472, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33029, NULL, NULL },
};

static const EventCharaKeyframe sEvent087Track7[3] = {
    { 477, 848, { 0, 0 }, 256000, 256000, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 475, 868, { 0, 0 }, 13824, 16896, 0, 0, { 0, 0 }, 16706, NULL, NULL },
    { 472, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33093, NULL, NULL },
};

static const EventCharaKeyframe sEvent087Track8[11] = {
    { 477, 853, { 0, 0 }, 256000, 256000, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 475, 873, { 0, 0 }, 6656, 22272, 0, 0, { 0, 0 }, 16706, NULL, NULL },
    { 472, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33093, NULL, NULL },
    { 477, 858, { 0, 0 }, 256000, 256000, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 476, 878, { 0, 0 }, -7168, 41472, 0, 0, { 0, 0 }, 16706, NULL, NULL },
    { 476, 845, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 324, NULL, NULL },
    { 473, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33093, NULL, NULL },
    { 477, 803, { 0, 0 }, 256000, 256000, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 476, 804, { 0, 0 }, -6400, 50176, 0, 0, { 0, 0 }, 16706, NULL, NULL },
    { 476, 860, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 324, NULL, NULL },
    { 473, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33093, NULL, NULL },
};

static const EventCharaTrack sEvent087Tracks[9] = {
    { sEvent087Track0, 0, { 0, 0, 0 } },
    { sEvent087Track1, 13, { 0, 0, 0 } },
    { sEvent087Track2, 1, { 0, 0, 0 } },
    { sEvent087Track3, 2, { 0, 0, 0 } },
    { sEvent087Track4, 40, { 0, 0, 0 } },
    { sEvent087Track5, 40, { 0, 0, 0 } },
    { sEvent087Track6, 40, { 0, 0, 0 } },
    { sEvent087Track7, 40, { 0, 0, 0 } },
    { sEvent087Track8, 40, { 0, 0, 0 } },
};

const EventSequenceDef gEvent087 = {
    9,
    { 0, 0, 0 },
    sEvent087Tracks,
    sEvent087Camera,
    sEvent087Script,
    sEvent087SoundCues,
    sEvent087BgEffects,
    950,
    0,
    1,
    0,
    0,
    0,
    0,
    122,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_088_text.inc"
static const MessageScriptEntry sEvent088Script[12] = {
    { 1, 4, 1, 1, { 0, 0, 0 }, gEventTextUs_08F89184, 0, 100 },
    { 11, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F891F8, 0, 110 },
    { 11, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8926C, 0, 130 },
    { 0, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F892FE, 0, 160 },
    { 11, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F89324, 0, 180 },
    { 11, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F893A0, 0, 200 },
    { 6, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8940A, 0, 510 },
    { 0, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8943C, 0, 530 },
    { 1, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8946C, 0, 560 },
    { 11, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08F894F2, 0, 590 },
    { 1, 5, 3, 1, { 0, 0, 0 }, gEventTextUs_08F89534, 0, 650 },
    { 11, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8953E, MSG_SCRIPT_FLAG_END, 710 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent088Script[12] = {
    { 1, 4, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7B494, 0, 100 },
    { 11, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7B448, 0, 110 },
    { 11, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7B3EC, 0, 130 },
    { 0, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7B3C4, 0, 160 },
    { 11, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7B390, 0, 180 },
    { 11, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7B360, 0, 200 },
    { 6, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7B34C, 0, 510 },
    { 0, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7B328, 0, 530 },
    { 1, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7B2F0, 0, 560 },
    { 11, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7B2D0, 0, 590 },
    { 1, 5, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7B2C4, 0, 650 },
    { 11, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7B290, MSG_SCRIPT_FLAG_END, 710 },
};

#include "event_088_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent088Script[12] = {
    { 1, 4, 1, 1, { 0, 0, 0 }, &gUnkEu_09F66860, 0, 100 },
    { 11, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66874, 0, 110 },
    { 11, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66888, 0, 130 },
    { 0, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6689C, 0, 160 },
    { 11, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F668B0, 0, 180 },
    { 11, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F668C4, 0, 200 },
    { 6, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F668D8, 0, 510 },
    { 0, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F668EC, 0, 530 },
    { 1, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66900, 0, 560 },
    { 11, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F66914, 0, 590 },
    { 1, 5, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66928, 0, 650 },
    { 11, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6693C, MSG_SCRIPT_FLAG_END, 710 },
};
#endif

static const EventCameraKeyframe sEvent088Camera[1] = {
    { -65485, 30720, 20480, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventBgEffectEntry sEvent088BgEffects[5] = {
    { 592, 0, 0, 0, 0 },
    { 593, 0, 0, 0, 0x4 },
    { 620, 0, 0, 0, 0 },
    { 700, 0, 0, 0, 0x2 },
    { 760, 0, 0, 0, 0x8008 },
};

static const EvSoundCue sEvent088SoundCues[4] = {
    { SONG_BGM_HALLOWEEN_FIELD, 0, 0, 0 },
    { SONG_SND_347, 624, 0, 0 },
    { SONG_EV_DL_JUMP, 649, 0, 0 },
    { SONG_BGM_HALLOWEEN_FIELD, 925, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent088Track0[3] = {
    { 4, 30, { 0, 0 }, 24832, 30464, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 4, 915, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 9, 9999, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 32836, NULL, NULL },
};

static const EventCharaKeyframe sEvent088Track1[12] = {
    { 114, 1, { 0, 0 }, 36608, 28160, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 131, 110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateSmokeTask },
    { 114, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 110, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 127, 558, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 128, 610, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 129, 618, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 640, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 133, 715, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaHopHigh, NULL },
    { 114, 920, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 119, 9999, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 32836, NULL, NULL },
};

static const EventCharaKeyframe sEvent088Track2[6] = {
    { 144, 250, { 0, 0 }, 23808, 19968, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 145, 540, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 810, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 930, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 151, 9999, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 32836, NULL, NULL },
};

static const EventCharaKeyframe sEvent088Track3[17] = {
    { 288, 101, { 0, 0 }, 30976, 22784, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 288, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 288, 199, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 298, 201, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 288, 210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 288, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 289, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 296, 300, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 290, 340, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 296, 450, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 288, 624, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 294, 660, { 0, 0 }, 42240, 24832, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 295, 715, { 0, 0 }, 42240, 24832, 0, 0, { 0, 0 }, 2, EventCharaFadeIn, NULL },
    { 288, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 288, 740, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 289, 770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 296, 9999, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 32836, NULL, NULL },
};

static const EventCharaKeyframe sEvent088Track4[11] = {
    { 231, 440, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8258, NULL, NULL },
    { 231, 441, { 0, 0 }, 24832, 30464, 0, 0, { 0, 0 }, 16450, NULL, NULL },
    { 234, 470, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, EventCharaHop, NULL },
    { 231, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 229, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 229, 591, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 229, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 231, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 229, 840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 233, 860, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, EventCharaHop, NULL },
    { 231, 999, { 0, 0 }, 102400, 102400, 0, 0, { 0, 0 }, 32834, NULL, NULL },
};

static const EventCharaTrack sEvent088Tracks[5] = {
    { sEvent088Track0, 0, { 0, 0, 0 } },
    { sEvent088Track1, 1, { 0, 0, 0 } },
    { sEvent088Track2, 2, { 0, 0, 0 } },
    { sEvent088Track3, 13, { 0, 0, 0 } },
    { sEvent088Track4, 8, { 0, 0, 0 } },
};

const EventSequenceDef gEvent088 = {
    5,
    { 0, 0, 0 },
    sEvent088Tracks,
    sEvent088Camera,
    sEvent088Script,
    sEvent088SoundCues,
    sEvent088BgEffects,
    930,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    1,
    255,
    255,
};

#ifdef VERSION_US
#include "event_089_text.inc"
static const MessageScriptEntry sEvent089Script[26] = {
    { 11, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F89E84, 0, 320 },
    { 19, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F89F08, 0, 340 },
    { 2, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F89F96, 0, 360 },
    { 19, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F89FC2, 0, 380 },
    { 0, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8A03A, 0, 400 },
    { 19, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8A058, 0, 420 },
    { 19, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F8A0E6, 0, 422 },
    { 19, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F8A188, 0, 424 },
    { 0, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8A224, 0, 460 },
    { 19, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8A262, 0, 490 },
    { 19, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F8A304, 0, 492 },
    { 19, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F8A3A8, 0, 494 },
    { 0, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8A446, 0, 530 },
    { 19, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8A460, 0, 570 },
    { 11, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8A494, 0, 610 },
    { 1, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8A532, 0, 620 },
    { 19, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8A584, 0, 630 },
    { 19, 2, 4, 1, { 0, 0, 0 }, gEventTextUs_08F8A5C0, 0, 632 },
    { 19, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08F8A648, 0, 634 },
    { 0, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8A682, 0, 650 },
    { 19, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8A6B4, 0, 660 },
    { 11, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8A74E, 0, 670 },
    { 0, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8A76E, 0, 680 },
    { 11, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8A790, 0, 690 },
    { 0, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8A7A4, 0, 700 },
    { 11, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8A83E, MSG_SCRIPT_FLAG_END, 710 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent089Script[27] = {
    { 11, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7C440, 0, 320 },
    { 19, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7C3F4, 0, 340 },
    { 2, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7C3E4, 0, 360 },
    { 19, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7C398, 0, 380 },
    { 0, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7C388, 0, 400 },
    { 19, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7C330, 0, 420 },
    { 19, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F7C2D8, 0, 422 },
    { 19, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F7C28C, 0, 424 },
    { 0, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7C264, 0, 460 },
    { 19, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7C210, 0, 490 },
    { 19, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F7C1BC, 0, 492 },
    { 19, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F7C16C, 0, 494 },
    { 0, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7C15C, 0, 530 },
    { 19, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7C144, 0, 570 },
    { 11, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7C0F0, 0, 610 },
    { 1, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7C0C4, 0, 620 },
    { 19, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7C094, 0, 630 },
    { 19, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08F7C058, 0, 632 },
    { 19, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F7C028, 0, 634 },
    { 0, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7C00C, 0, 650 },
    { 19, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7BFEC, 0, 660 },
    { 19, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F7BFAC, 0, 662 },
    { 11, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7BFA0, 0, 670 },
    { 0, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7BF84, 0, 680 },
    { 11, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7BF78, 0, 690 },
    { 0, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7BF44, 0, 700 },
    { 11, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7BF18, MSG_SCRIPT_FLAG_END, 710 },
};

#include "event_089_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent089Script[26] = {
    { 11, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66CAC, 0, 320 },
    { 19, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66CC0, 0, 340 },
    { 2, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F66CD4, 0, 360 },
    { 19, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66CE8, 0, 380 },
    { 0, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F66CFC, 0, 400 },
    { 19, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66D10, 0, 420 },
    { 19, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F66D24, 0, 422 },
    { 19, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F66D38, 0, 424 },
    { 0, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F66D4C, 0, 460 },
    { 19, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66D60, 0, 490 },
    { 19, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F66D74, 0, 492 },
    { 19, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F66D88, 0, 494 },
    { 0, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F66D9C, 0, 530 },
    { 19, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F66DB0, 0, 570 },
    { 11, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66DC4, 0, 610 },
    { 1, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F66DD8, 0, 620 },
    { 19, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66DEC, 0, 630 },
    { 19, 2, 4, 1, { 0, 0, 0 }, &gUnkEu_09F66E00, 0, 632 },
    { 19, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F66E14, 0, 634 },
    { 0, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F66E28, 0, 650 },
    { 19, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66E3C, 0, 660 },
    { 11, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66E50, 0, 670 },
    { 0, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F66E64, 0, 680 },
    { 11, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66E78, 0, 690 },
    { 0, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F66E8C, 0, 700 },
    { 11, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66EA0, MSG_SCRIPT_FLAG_END, 710 },
};
#endif

static const EventCameraKeyframe sEvent089Camera[3] = {
    { -65506, 79872, 65280, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65286, 61952, 65280, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 70, { 0, 0 }, NULL },
    { -64537, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent089SoundCues[3] = {
    { 65535, 0, 0, 0 },
    { SONG_BGM_EVENT3, 340, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT3, 725, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent089Track0[18] = {
    { 7, 0, { 0, 0 }, 103168, 64768, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 7, 220, { 0, 0 }, 66304, 69120, 0, 2, { 0, 0 }, 3, NULL, NULL },
    { 4, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 370, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 399, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 27, 401, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 4, 430, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 34, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 27, 529, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 30, 551, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 609, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 629, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 669, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 715, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 0, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 9, 900, { 0, 0 }, 103168, 64768, 0, 4, { 0, 0 }, 67, NULL, NULL },
    { 4, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent089Track1[12] = {
    { 117, 60, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 117, 61, { 0, 0 }, 103168, 64768, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 117, 240, { 0, 0 }, 75520, 70400, 0, 112, { 0, 0 }, 3, NULL, NULL },
    { 114, 609, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 113, 619, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 126, 621, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 669, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 716, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 110, 723, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 733, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 119, 908, { 0, 0 }, 103168, 64768, 0, 114, { 0, 0 }, 67, NULL, NULL },
    { 114, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent089Track2[14] = {
    { 149, 70, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 149, 71, { 0, 0 }, 103168, 67328, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 149, 250, { 0, 0 }, 70144, 75008, 0, 144, { 0, 0 }, 3, NULL, NULL },
    { 146, 325, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 359, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 165, 361, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 609, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 145, 619, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 669, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 712, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 142, 718, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 723, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 151, 900, { 0, 0 }, 103168, 67328, 0, 146, { 0, 0 }, 67, NULL, NULL },
    { 146, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent089Track3[14] = {
    { 290, 0, { 0, 0 }, 89600, 65280, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 290, 230, { 0, 0 }, 48384, 69120, 0, 288, { 0, 0 }, 3, NULL, NULL },
    { 288, 240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 288, 319, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 292, 321, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 288, 609, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 292, 613, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 288, 669, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 289, 681, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 288, 709, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 298, 711, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 288, 718, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 290, 930, { 0, 0 }, 103168, 67328, 0, 288, { 0, 0 }, 67, NULL, NULL },
    { 288, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent089Track4[12] = {
    { 407, 180, { 0, 0 }, 58112, 65280, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 409, 190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 408, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 406, 540, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 409, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 409, 560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 407, 621, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 407, 625, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 406, 629, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 406, 631, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateSmokeTask },
    { 406, 660, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 406, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent089Tracks[5] = {
    { sEvent089Track0, 0, { 0, 0, 0 } },
    { sEvent089Track1, 1, { 0, 0, 0 } },
    { sEvent089Track2, 2, { 0, 0, 0 } },
    { sEvent089Track3, 13, { 0, 0, 0 } },
    { sEvent089Track4, 29, { 0, 0, 0 } },
};

const EventSequenceDef gEvent089 = {
    5,
    { 0, 0, 0 },
    sEvent089Tracks,
    sEvent089Camera,
    sEvent089Script,
    sEvent089SoundCues,
    NULL,
    730,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_090_text.inc"
static const MessageScriptEntry sEvent090Script[22] = {
    { 11, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8B5A4, 0, 440 },
    { 18, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8B60C, 0, 560 },
    { 11, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8B638, 0, 570 },
    { 18, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8B6C4, 0, 580 },
    { 0, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8B6D8, 0, 650 },
    { 18, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8B708, 0, 690 },
    { 18, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08F8B75E, 0, 692 },
    { 11, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8B80E, 0, 710 },
    { 18, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8B86A, 0, 730 },
    { 0, 7, 2, 1, { 0, 0, 0 }, gEventTextUs_08F8B8C2, 0, 745 },
    { 11, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8B8E4, 0, 760 },
    { 12, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8B918, MSG_SCRIPT_FLAG_SILHOUETTE, 780 },
    { 18, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8B942, 0, 920 },
    { 11, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8B96C, 0, 1030 },
    { 12, 1, 2, 1, { 0, 0, 0 }, gEventTextUs_08F8B992, 0, 1040 },
    { 12, 1, 2, 1, { 0, 0, 0 }, gEventTextUs_08F8B9CE, 0, 1130 },
    { 12, 0, 2, 1, { 0, 0, 0 }, gEventTextUs_08F8BA5C, 0, 1160 },
    { 12, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F8BACE, 0, 1162 },
    { 12, 0, 2, 1, { 0, 0, 0 }, gEventTextUs_08F8BB58, 0, 1190 },
    { 12, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08F8BBC2, 0, 1200 },
    { 11, 2, 0, 1, { 0, 0, 0 }, gEventTextUs_08F8BC52, 0, 1340 },
    { 0, 2, 2, 1, { 0, 0, 0 }, gEventTextUs_08F8BCA0, MSG_SCRIPT_FLAG_END, 1390 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent090Script[22] = {
    { 11, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7D500, 0, 440 },
    { 18, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7D4F0, 0, 560 },
    { 11, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7D4A0, 0, 570 },
    { 18, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7D494, 0, 580 },
    { 0, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7D478, 0, 650 },
    { 18, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7D43C, 0, 690 },
    { 18, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F7D3E0, 0, 692 },
    { 11, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7D3B8, 0, 710 },
    { 18, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7D37C, 0, 730 },
    { 0, 7, 2, 3, { 0, 0, 0 }, gEventTextJp_08F7D35C, 0, 745 },
    { 11, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7D34C, 0, 760 },
    { 12, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7D32C, MSG_SCRIPT_FLAG_SILHOUETTE, 780 },
    { 18, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7D318, 0, 920 },
    { 11, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7D2FC, 0, 1030 },
    { 12, 1, 2, 3, { 0, 0, 0 }, gEventTextJp_08F7D2E4, 0, 1040 },
    { 12, 1, 2, 3, { 0, 0, 0 }, gEventTextJp_08F7D29C, 0, 1130 },
    { 12, 0, 2, 3, { 0, 0, 0 }, gEventTextJp_08F7D260, 0, 1160 },
    { 12, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F7D210, 0, 1162 },
    { 12, 0, 2, 3, { 0, 0, 0 }, gEventTextJp_08F7D1D0, 0, 1190 },
    { 12, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F7D180, 0, 1200 },
    { 11, 2, 0, 3, { 0, 0, 0 }, gEventTextJp_08F7D150, 0, 1340 },
    { 0, 2, 2, 3, { 0, 0, 0 }, gEventTextJp_08F7D134, MSG_SCRIPT_FLAG_END, 1390 },
};

#include "event_090_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent090Script[22] = {
    { 11, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F66EB4, 0, 440 },
    { 18, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66EC8, 0, 560 },
    { 11, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F66EDC, 0, 570 },
    { 18, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66EF0, 0, 580 },
    { 0, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66F04, 0, 650 },
    { 18, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F66F18, 0, 690 },
    { 18, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F66F2C, 0, 692 },
    { 11, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F66F40, 0, 710 },
    { 18, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66F54, 0, 730 },
    { 0, 7, 2, 1, { 0, 0, 0 }, &gUnkEu_09F66F68, 0, 745 },
    { 11, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F66F7C, 0, 760 },
    { 12, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66F90, MSG_SCRIPT_FLAG_SILHOUETTE, 780 },
    { 18, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66FA4, 0, 920 },
    { 11, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F66FB8, 0, 1030 },
    { 12, 1, 2, 1, { 0, 0, 0 }, &gUnkEu_09F66FCC, 0, 1040 },
    { 12, 1, 2, 1, { 0, 0, 0 }, &gUnkEu_09F66FE0, 0, 1130 },
    { 12, 0, 2, 1, { 0, 0, 0 }, &gUnkEu_09F66FF4, 0, 1160 },
    { 12, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F67008, 0, 1162 },
    { 12, 0, 2, 1, { 0, 0, 0 }, &gUnkEu_09F6701C, 0, 1190 },
    { 12, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F67030, 0, 1200 },
    { 11, 2, 0, 1, { 0, 0, 0 }, &gUnkEu_09F67044, 0, 1340 },
    { 0, 2, 2, 1, { 0, 0, 0 }, &gUnkEu_09F67058, MSG_SCRIPT_FLAG_END, 1390 },
};
#endif

static const EvSoundCue sEvent090SoundCues[5] = {
    { SONG_BGM_HALLOWEEN_FIELD, 0, 0, 0 },
    { SONG_BGM_HALLOWEEN_FIELD, 770, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT_UNREST, 781, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BTL_MON_HIT03, 790, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 1635, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent090Camera[12] = {
    { -65386, 96000, 24576, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64887, 96000, 61952, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 160, { 0, 0 }, NULL },
    { -64746, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64736, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_MEDIUM | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64716, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64706, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -64615, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64286, 90368, 100352, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 30, { 0, 0 }, NULL },
    { -64197, 93696, 90880, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -64126, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -63907, 97792, 77312, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -63906, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_BLACK | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 30, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent090Track0[21] = {
    { 4, 220, { 0, 0 }, 87296, 84224, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 9, 339, { 0, 0 }, 102656, 70912, 0, 4, { 0, 0 }, 67, NULL, NULL },
    { 4, 590, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 744, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 34, 778, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 35, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 820, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 27, 880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 4, 930, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 936, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 940, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 945, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 12, 1000, { 0, 0 }, 92928, 98816, 0, 2, { 0, 0 }, 3, NULL, NULL },
    { 2, 1343, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 12, 1375, { 0, 0 }, 81408, 103168, 0, 2, { 0, 0 }, 3, NULL, NULL },
    { 2, 1379, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 1389, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 31, 1391, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 1405, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 1415, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 12, 1999, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 32804, NULL, NULL },
};

static const EventCharaKeyframe sEvent090Track1[21] = {
    { 570, 220, { 0, 0 }, 107264, 64000, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 570, 270, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 573, 320, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 573, 441, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 573, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 573, 581, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 571, 651, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 572, 685, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 573, 691, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 573, 755, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 573, 820, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 568, 880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 568, 890, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 568, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 568, 909, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 568, 921, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 568, 1130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 573, 1139, { 0, 0 }, 105728, 78080, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 573, 1460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 574, 1530, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 573, 1139, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent090Track2[20] = {
    { 289, 220, { 0, 0 }, 95744, 84480, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 296, 326, { 0, 0 }, 115456, 69632, 0, 289, { 0, 0 }, 67, NULL, NULL },
    { 289, 340, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 289, 709, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 292, 735, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 288, 745, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 289, 755, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 288, 820, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 288, 880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 288, 890, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 289, 925, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 288, 935, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 291, 990, { 0, 0 }, 98304, 102400, 0, 288, { 0, 0 }, 3, NULL, NULL },
    { 288, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 290, 1029, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 36, NULL, NULL },
    { 298, 1045, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 288, 1339, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 298, 1341, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 288, 1410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 291, 1999, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 32804, NULL, NULL },
};

static const EventCharaKeyframe sEvent090Track3[12] = {
    { 114, 220, { 0, 0 }, 92928, 91648, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 119, 360, { 0, 0 }, 107008, 77568, 0, 114, { 0, 0 }, 67, NULL, NULL },
    { 114, 370, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 110, 820, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 133, 880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 110, 940, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 113, 950, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 112, 955, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 112, 970, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 121, 1030, { 0, 0 }, 104192, 93952, 0, 112, { 0, 0 }, 3, NULL, NULL },
    { 112, 1415, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 121, 1999, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 32804, NULL, NULL },
};

static const EventCharaKeyframe sEvent090Track4[14] = {
    { 146, 220, { 0, 0 }, 79360, 86272, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 151, 350, { 0, 0 }, 91648, 74752, 0, 146, { 0, 0 }, 67, NULL, NULL },
    { 146, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 820, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 161, 880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 146, 935, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 940, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 945, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 960, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 152, 990, { 0, 0 }, 89600, 92672, 0, 144, { 0, 0 }, 3, NULL, NULL },
    { 144, 1340, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 143, 1390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 1420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 152, 1999, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 32804, NULL, NULL },
};

static const EventCharaKeyframe sEvent090Track5[15] = {
    { 361, 799, { 0, 0 }, 256000, 256000, 0, 0, { 0, 0 }, 8258, NULL, NULL },
    { 361, 800, { 0, 0 }, 75264, 63232, 0, 0, { 0, 0 }, 16450, NULL, NULL },
    { 366, 820, { 0, 0 }, 104960, 66048, 0, 361, { 0, 0 }, 67, NULL, NULL },
    { 366, 825, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 366, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 366, 870, { 0, 0 }, 67072, 117248, 0, 361, { 0, 0 }, 3, NULL, NULL },
    { 362, 1041, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 367, 1131, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 369, 1159, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 362, 1189, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 363, 1191, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 361, 1195, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 361, 1199, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 365, 1201, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 366, 1999, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 32804, NULL, NULL },
};

static const EventCharaKeyframe sEvent090Track6[3] = {
    { 479, 790, { 0, 0 }, 75776, 65536, 0, 0, { 0, 0 }, 274, NULL, NULL },
    { 480, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 277, NULL, NULL },
    { 481, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33045, NULL, NULL },
};

static const EventCharaKeyframe sEvent090Track7[3] = {
    { 482, 790, { 0, 0 }, 75776, 65536, 0, 0, { 0, 0 }, 274, NULL, NULL },
    { 483, 798, { 0, 0 }, 75776, 65536, 0, 0, { 0, 0 }, 274, NULL, NULL },
    { 484, 999, { 0, 0 }, 75776, 57344, 0, 0, { 0, 0 }, 33026, NULL, NULL },
};

static const EventCharaTrack sEvent090Tracks[8] = {
    { sEvent090Track0, 0, { 0, 0, 0 } },
    { sEvent090Track1, 45, { 0, 0, 0 } },
    { sEvent090Track2, 13, { 0, 0, 0 } },
    { sEvent090Track3, 1, { 0, 0, 0 } },
    { sEvent090Track4, 2, { 0, 0, 0 } },
    { sEvent090Track5, 21, { 0, 0, 0 } },
    { sEvent090Track6, 41, { 0, 0, 0 } },
    { sEvent090Track7, 42, { 0, 0, 0 } },
};

const EventSequenceDef gEvent090 = {
    8,
    { 0, 0, 0 },
    sEvent090Tracks,
    sEvent090Camera,
    sEvent090Script,
    sEvent090SoundCues,
    NULL,
    1640,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_091_text.inc"
static const MessageScriptEntry sEvent091Script[11] = {
    { 11, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8D06C, 0, 240 },
    { 12, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8D0A6, 0, 280 },
    { 0, 2, 0, 1, { 0, 0, 0 }, gEventTextUs_08F8D152, 0, 300 },
    { 12, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8D16A, 0, 310 },
    { 0, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8D174, 0, 406 },
    { 12, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8D184, 0, 420 },
    { 12, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08F8D1B6, 0, 422 },
    { 12, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8D1FC, 0, 600 },
    { 12, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8D222, 0, 604 },
    { 11, 4, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8D29C, 0, 640 },
    { 12, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8D2D0, MSG_SCRIPT_FLAG_END, 660 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent091Script[11] = {
    { 11, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7E904, 0, 240 },
    { 12, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7E8AC, 0, 280 },
    { 0, 2, 0, 3, { 0, 0, 0 }, gEventTextJp_08F7E8A0, 0, 300 },
    { 12, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7E890, 0, 310 },
    { 0, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7E884, 0, 406 },
    { 12, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7E868, 0, 420 },
    { 12, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F7E844, 0, 422 },
    { 12, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7E82C, 0, 600 },
    { 12, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7E7DC, 0, 604 },
    { 11, 4, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7E7C4, 0, 640 },
    { 12, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7E7A0, MSG_SCRIPT_FLAG_END, 660 },
};

#include "event_091_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent091Script[11] = {
    { 11, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67080, 0, 240 },
    { 12, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67094, 0, 280 },
    { 0, 2, 0, 1, { 0, 0, 0 }, &gUnkEu_09F670A8, 0, 300 },
    { 12, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F670BC, 0, 310 },
    { 0, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F670D0, 0, 406 },
    { 12, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F670E4, 0, 420 },
    { 12, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F670F8, 0, 422 },
    { 12, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6710C, 0, 600 },
    { 12, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67120, 0, 604 },
    { 11, 4, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67134, 0, 640 },
    { 12, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67148, MSG_SCRIPT_FLAG_END, 660 },
};
#endif

static const EventCameraKeyframe sEvent091Camera[2] = {
    { -65485, 89600, 79872, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65236, 49664, 51200, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 150, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent091SoundCues[6] = {
    { SONG_BGM_EVENT_UNREST, 0, 0, 0 },
    { SONG_SND_348, 335, 0, 0 },
    { SONG_SND_348, 359, 0, 0 },
    { SONG_SND_348, 383, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 440, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT2, 604, EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent091Track0[7] = {
    { 4, 0, { 0, 0 }, 125184, 102656, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 14, 170, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 4, 173, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 4, 299, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 30, 399, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 27, 655, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent091Track1[10] = {
    { 289, 0, { 0, 0 }, 109312, 82944, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 297, 140, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 289, 144, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 289, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 288, 239, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 298, 242, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 288, 619, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 290, 640, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 298, 641, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 288, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent091Track2[4] = {
    { 114, 0, { 0, 0 }, 132608, 103424, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 120, 188, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 114, 192, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 114, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent091Track3[4] = {
    { 146, 0, { 0, 0 }, 123136, 109312, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 153, 228, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 146, 234, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 146, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent091Track4[7] = {
    { 362, 242, { 0, 0 }, 29440, 53760, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 370, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 370, 311, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 371, 419, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 365, 560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 361, 601, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 372, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent091Tracks[5] = {
    { sEvent091Track0, 0, { 0, 0, 0 } },
    { sEvent091Track1, 13, { 0, 0, 0 } },
    { sEvent091Track2, 1, { 0, 0, 0 } },
    { sEvent091Track3, 2, { 0, 0, 0 } },
    { sEvent091Track4, 21, { 0, 0, 0 } },
};

const EventSequenceDef gEvent091 = {
    5,
    { 0, 0, 0 },
    sEvent091Tracks,
    sEvent091Camera,
    sEvent091Script,
    sEvent091SoundCues,
    NULL,
    730,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    92,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_092_text.inc"
static const MessageScriptEntry sEvent092Script[1] = {
    { 12, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8D964, MSG_SCRIPT_FLAG_END, 100 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent092Script[1] = {
    { 12, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7EE7C, MSG_SCRIPT_FLAG_END, 100 },
};

#include "event_092_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent092Script[1] = {
    { 12, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6706C, MSG_SCRIPT_FLAG_END, 100 },
};
#endif

static const EventCameraKeyframe sEvent092Camera[1] = {
    { -65485, 94208, 153600, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent092SoundCues[1] = {
    { SONG_BGM_EVENT2, 0, EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent092Track0[1] = {
    { 20, 30, { 0, 0 }, 92160, 172032, 0, 0, { 0, 0 }, 32834, NULL, NULL },
};

static const EventCharaKeyframe sEvent092Track1[1] = {
    { 936, 30, { 0, 0 }, 78336, 58880, 0, 0, { 0, 0 }, 32770, NULL, NULL },
};

static const EventCharaTrack sEvent092Tracks[2] = {
    { sEvent092Track0, 0, { 0, 0, 0 } },
    { sEvent092Track1, 98, { 0, 0, 0 } },
};

const EventSequenceDef gEvent092 = {
    2,
    { 0, 0, 0 },
    sEvent092Tracks,
    sEvent092Camera,
    sEvent092Script,
    sEvent092SoundCues,
    NULL,
    200,
    0,
    1,
    0,
    0,
    0,
    0,
    155,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_093_text.inc"
static const MessageScriptEntry sEvent093Script[25] = {
    { 19, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8DA70, 0, 100 },
    { 19, 2, 4, 1, { 0, 0, 0 }, gEventTextUs_08F8DB00, 0, 102 },
    { 2, 0, 0, 1, { 0, 0, 0 }, gEventTextUs_08F8DB42, 0, 120 },
    { 0, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8DBBA, 0, 330 },
    { 19, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8DBE4, 0, 341 },
    { 18, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8DC76, 0, 350 },
    { 11, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8DC90, 0, 360 },
    { 0, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8DCFA, 0, 370 },
    { 0, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F8DD36, 0, 372 },
    { 19, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8DDC6, 0, 590 },
    { 19, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F8DE56, 0, 592 },
    { 18, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8DEE8, 0, 600 },
    { 19, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8DF2E, 0, 610 },
    { 19, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F8DFAE, 0, 612 },
    { 0, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8E058, 0, 630 },
    { 19, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8E0D6, 0, 641 },
    { 19, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F8E126, 0, 642 },
    { 11, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8E1C2, 0, 860 },
    { 0, 0, 0, 1, { 0, 0, 0 }, gEventTextUs_08F8E232, 0, 880 },
    { 11, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8E25C, 0, 890 },
    { 11, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8E286, 0, 940 },
    { 11, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8E2E8, 0, 960 },
    { 11, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F8E354, 0, 962 },
    { 0, 4, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8E3F2, 0, 980 },
    { 11, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8E436, MSG_SCRIPT_FLAG_END, 1000 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent093Script[25] = {
    { 19, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7F6BC, 0, 100 },
    { 19, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08F7F68C, 0, 102 },
    { 2, 0, 0, 3, { 0, 0, 0 }, gEventTextJp_08F7F658, 0, 120 },
    { 0, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7F640, 0, 330 },
    { 19, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7F5F8, 0, 341 },
    { 18, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7F5E8, 0, 350 },
    { 11, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7F5C0, 0, 360 },
    { 0, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7F590, 0, 370 },
    { 0, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F7F540, 0, 372 },
    { 19, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7F4F8, 0, 590 },
    { 19, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F7F4C8, 0, 592 },
    { 18, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7F4A8, 0, 600 },
    { 19, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7F468, 0, 610 },
    { 19, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F7F40C, 0, 612 },
    { 0, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7F3DC, 0, 630 },
    { 19, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7F3B0, 0, 641 },
    { 19, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F7F360, 0, 642 },
    { 11, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7F320, 0, 860 },
    { 0, 0, 0, 3, { 0, 0, 0 }, gEventTextJp_08F7F308, 0, 880 },
    { 11, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7F2EC, 0, 890 },
    { 11, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7F2B8, 0, 940 },
    { 11, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7F260, 0, 960 },
    { 11, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F7F22C, 0, 962 },
    { 0, 4, 1, 3, { 0, 0, 0 }, gEventTextJp_08F7F204, 0, 980 },
    { 11, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7F1AC, MSG_SCRIPT_FLAG_END, 1000 },
};

#include "event_093_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent093Script[25] = {
    { 19, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F66AB8, 0, 100 },
    { 19, 2, 4, 1, { 0, 0, 0 }, &gUnkEu_09F66ACC, 0, 102 },
    { 2, 0, 0, 1, { 0, 0, 0 }, &gUnkEu_09F66AE0, 0, 120 },
    { 0, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F66AF4, 0, 330 },
    { 19, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66B08, 0, 341 },
    { 18, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F66B1C, 0, 350 },
    { 11, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66B30, 0, 360 },
    { 0, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F66B44, 0, 370 },
    { 0, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F66B58, 0, 372 },
    { 19, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66B6C, 0, 590 },
    { 19, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F66B80, 0, 592 },
    { 18, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F66B94, 0, 600 },
    { 19, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66BA8, 0, 610 },
    { 19, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F66BBC, 0, 612 },
    { 0, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F66BD0, 0, 630 },
    { 19, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66BE4, 0, 641 },
    { 19, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F66BF8, 0, 642 },
    { 11, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66C0C, 0, 860 },
    { 0, 0, 0, 1, { 0, 0, 0 }, &gUnkEu_09F66C20, 0, 880 },
    { 11, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66C34, 0, 890 },
    { 11, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66C48, 0, 940 },
    { 11, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66C5C, 0, 960 },
    { 11, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F66C70, 0, 962 },
    { 0, 4, 1, 1, { 0, 0, 0 }, &gUnkEu_09F66C84, 0, 980 },
    { 11, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F66C98, MSG_SCRIPT_FLAG_END, 1000 },
};
#endif

static const EventCameraKeyframe sEvent093Camera[1] = {
    { -65485, 61440, 74496, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent093SoundCues[2] = {
    { SONG_BGM_EVENT3, 0, 0, 0 },
    { SONG_BGM_EVENT3, 1135, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent093Track0[20] = {
    { 4, 125, { 0, 0 }, 65536, 84736, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 3, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 3, 290, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 629, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 27, 643, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 670, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 0, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 34, 861, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 4, 870, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 0, 875, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 891, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 939, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateQuestionTask },
    { 4, 965, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 16, 978, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 0, 1025, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1040, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 14, 1180, { 0, 0 }, 102400, 68096, 0, 4, { 0, 0 }, 67, NULL, NULL },
    { 4, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent093Track1[4] = {
    { 288, 889, { 0, 0 }, 52480, 73984, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 298, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 292, 1090, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 288, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent093Track2[5] = {
    { 568, 0, { 0, 0 }, 66560, 71168, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 568, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 568, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 568, 1070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 568, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent093Track3[10] = {
    { 406, 99, { 0, 0 }, 60928, 76800, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 406, 104, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateSmokeTask },
    { 406, 130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 406, 601, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 407, 609, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 407, 611, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateSmokeTask },
    { 406, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 407, 655, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 409, 800, { 0, 0 }, 102400, 68096, 0, 407, { 0, 0 }, 67, NULL, NULL },
    { 406, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent093Track4[16] = {
    { 112, 380, { 0, 0 }, 75008, 71424, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 112, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 112, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 111, 710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 760, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 113, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 112, 835, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 111, 840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 845, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 111, 1025, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 1030, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 113, 1035, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 1045, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 120, 1170, { 0, 0 }, 102400, 68096, 0, 114, { 0, 0 }, 67, NULL, NULL },
    { 112, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent093Track6[1] = {
    { 575, 999, { 0, 0 }, 54784, 77824, 0, 0, { 0, 0 }, 33026, NULL, NULL },
};

static const EventCharaKeyframe sEvent093Track5[21] = {
    { 146, 104, { 0, 0 }, 73216, 83200, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 146, 106, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 145, 108, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 119, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 164, 121, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 145, 555, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 670, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 142, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 142, 835, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 145, 845, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 881, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 145, 885, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 142, 1025, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 1040, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 153, 1160, { 0, 0 }, 102400, 68096, 0, 146, { 0, 0 }, 67, NULL, NULL },
    { 146, 9990, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent093Tracks[7] = {
    { sEvent093Track0, 0, { 0, 0, 0 } },
    { sEvent093Track1, 13, { 0, 0, 0 } },
    { sEvent093Track2, 45, { 0, 0, 0 } },
    { sEvent093Track3, 29, { 0, 0, 0 } },
    { sEvent093Track4, 1, { 0, 0, 0 } },
    { sEvent093Track5, 2, { 0, 0, 0 } },
    { sEvent093Track6, 46, { 0, 0, 0 } },
};

const EventSequenceDef gEvent093 = {
    7,
    { 0, 0, 0 },
    sEvent093Tracks,
    sEvent093Camera,
    sEvent093Script,
    sEvent093SoundCues,
    NULL,
    1140,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_094_text.inc"
static const MessageScriptEntry sEvent094Script[7] = {
    { 2, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8F280, 0, 190 },
    { 8, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8F2B0, 0, 400 },
    { 8, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8F360, 0, 450 },
    { 0, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8F3D6, 0, 500 },
    { 8, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8F428, 0, 540 },
    { 0, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F8F480, 0, 750 },
    { 1, 5, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8F4A6, MSG_SCRIPT_FLAG_END, 770 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent094Script[7] = {
    { 2, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F80434, 0, 190 },
    { 8, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F803D8, 0, 400 },
    { 8, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F803A8, 0, 450 },
    { 0, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F80390, 0, 500 },
    { 8, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F80370, 0, 540 },
    { 0, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F80358, 0, 750 },
    { 1, 5, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8031C, MSG_SCRIPT_FLAG_END, 770 },
};

#include "event_094_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent094Script[7] = {
    { 2, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6D700, 0, 190 },
    { 8, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6D714, 0, 400 },
    { 8, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6D728, 0, 450 },
    { 0, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6D73C, 0, 500 },
    { 8, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6D750, 0, 540 },
    { 0, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6D764, 0, 750 },
    { 1, 5, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6D778, MSG_SCRIPT_FLAG_END, 770 },
};
#endif

static const EventCameraKeyframe sEvent094Camera[2] = {
    { -65536, 69120, 81408, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, NULL },
    { -64537, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 80, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent094SoundCues[2] = {
    { SONG_BGM_ALICE_FIELD, 0, 0, 0 },
    { SONG_BGM_ALICE_FIELD, 925, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent094Track0[17] = {
    { 4, 0, { 0, 0 }, 34048, 100096, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 9, 150, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 4, 401, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 451, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateQuestionTask },
    { 4, 453, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 27, 499, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 30, 541, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 620, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 1, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 1, 805, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 810, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 815, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 9, 999, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 32836, NULL, NULL },
};

static const EventCharaKeyframe sEvent094Track1[12] = {
    { 114, 0, { 0, 0 }, 31488, 106496, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 119, 150, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 114, 401, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 451, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateQuestionTask },
    { 114, 610, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 113, 630, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 112, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 113, 740, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 769, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 126, 771, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 850, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 119, 999, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 32836, NULL, NULL },
};

static const EventCharaKeyframe sEvent094Track2[14] = {
    { 146, 0, { 0, 0 }, 23808, 100096, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 151, 150, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 146, 189, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 165, 191, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 401, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 451, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateQuestionTask },
    { 146, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 630, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 850, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 860, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 151, 999, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 32836, NULL, NULL },
};

static const EventCharaKeyframe sEvent094Track3[20] = {
    { 264, 200, { 0, 0 }, 106240, 63232, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 266, 290, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 36, NULL, NULL },
    { 264, 293, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 264, 320, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 269, 340, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 264, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaHopLow, NULL },
    { 268, 365, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 268, 375, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 268, 385, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 268, 395, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 268, 405, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 268, 415, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 268, 425, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 268, 435, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 268, 445, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 268, 455, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 268, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 268, 580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 266, 740, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 100, NULL, NULL },
    { 264, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98373, NULL, NULL },
};

static const EventCharaTrack sEvent094Tracks[4] = {
    { sEvent094Track0, 0, { 0, 0, 0 } },
    { sEvent094Track1, 1, { 0, 0, 0 } },
    { sEvent094Track2, 2, { 0, 0, 0 } },
    { sEvent094Track3, 11, { 0, 0, 0 } },
};

const EventSequenceDef gEvent094 = {
    4,
    { 0, 0, 0 },
    sEvent094Tracks,
    sEvent094Camera,
    sEvent094Script,
    sEvent094SoundCues,
    NULL,
    930,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    1,
    255,
    255,
};

#ifdef VERSION_US
#include "event_095_text.inc"
static const MessageScriptEntry sEvent095Script[30] = {
    { 2, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8FF48, 0, 300 },
    { 1, 5, 3, 1, { 0, 0, 0 }, gEventTextUs_08F8FFD0, 0, 320 },
    { 8, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F90052, 0, 380 },
    { 5, 2, 2, 1, { 0, 0, 0 }, gEventTextUs_08F900B8, 0, 400 },
    { 4, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F90108, 0, 420 },
    { 4, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08F9013C, 0, 422 },
    { 5, 2, 2, 1, { 0, 0, 0 }, gEventTextUs_08F901C6, 0, 440 },
    { 4, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F9020E, 0, 460 },
    { 4, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08F90270, 0, 462 },
    { 8, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F902DA, 0, 480 },
    { 8, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F90376, 0, 482 },
    { 5, 2, 2, 1, { 0, 0, 0 }, gEventTextUs_08F903A8, 0, 500 },
    { 4, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08F90476, 0, 520 },
    { 4, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08F904E6, 0, 522 },
    { 0, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08F90584, 0, 630 },
    { 2, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08F905B0, 0, 750 },
    { 4, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F905C4, 0, 860 },
    { 0, 2, 2, 1, { 0, 0, 0 }, gEventTextUs_08F90636, 0, 880 },
    { 0, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08F90648, 0, 950 },
    { 4, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08F906EA, 0, 970 },
    { 4, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08F9077E, 0, 972 },
    { 0, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08F907E2, 0, 990 },
    { 4, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F907FC, 0, 1010 },
    { 4, 3, 4, 1, { 0, 0, 0 }, gEventTextUs_08F9085E, 0, 1012 },
    { 0, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08F908A4, 0, 1030 },
    { 0, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08F908B2, 0, 1190 },
    { 4, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08F908D0, 0, 1210 },
    { 2, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08F908F0, 0, 1230 },
    { 0, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08F90910, 0, 1270 },
    { 4, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F90976, MSG_SCRIPT_FLAG_END, 1300 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent095Script[30] = {
    { 2, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F81578, 0, 300 },
    { 1, 5, 3, 3, { 0, 0, 0 }, gEventTextJp_08F81548, 0, 320 },
    { 8, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F8150C, 0, 380 },
    { 5, 2, 2, 3, { 0, 0, 0 }, gEventTextJp_08F814DC, 0, 400 },
    { 4, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F814C4, 0, 420 },
    { 4, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F81480, 0, 422 },
    { 5, 2, 2, 3, { 0, 0, 0 }, gEventTextJp_08F81458, 0, 440 },
    { 4, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F81430, 0, 460 },
    { 4, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F81400, 0, 462 },
    { 8, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F813B8, 0, 480 },
    { 8, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F8139C, 0, 482 },
    { 5, 2, 2, 3, { 0, 0, 0 }, gEventTextJp_08F81348, 0, 500 },
    { 4, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F81314, 0, 520 },
    { 4, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F812CC, 0, 522 },
    { 0, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F812B4, 0, 630 },
    { 2, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F812AC, 0, 750 },
    { 4, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F81284, 0, 860 },
    { 0, 2, 2, 3, { 0, 0, 0 }, gEventTextJp_08F81278, 0, 880 },
    { 0, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F81220, 0, 950 },
    { 4, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F811D8, 0, 970 },
    { 4, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F811A4, 0, 972 },
    { 0, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F81190, 0, 990 },
    { 4, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F81160, 0, 1010 },
    { 4, 3, 4, 3, { 0, 0, 0 }, gEventTextJp_08F81138, 0, 1012 },
    { 0, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F81124, 0, 1030 },
    { 0, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F81114, 0, 1190 },
    { 4, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F81104, 0, 1210 },
    { 2, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F810F0, 0, 1230 },
    { 0, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F810C4, 0, 1270 },
    { 4, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F81098, MSG_SCRIPT_FLAG_END, 1300 },
};

#include "event_095_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent095Script[30] = {
    { 2, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6D804, 0, 300 },
    { 1, 5, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6D818, 0, 320 },
    { 8, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6D82C, 0, 380 },
    { 5, 2, 2, 1, { 0, 0, 0 }, &gUnkEu_09F6D840, 0, 400 },
    { 4, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6D854, 0, 420 },
    { 4, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6D868, 0, 422 },
    { 5, 2, 2, 1, { 0, 0, 0 }, &gUnkEu_09F6D87C, 0, 440 },
    { 4, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6D890, 0, 460 },
    { 4, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6D8A4, 0, 462 },
    { 8, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6D8B8, 0, 480 },
    { 8, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6D8CC, 0, 482 },
    { 5, 2, 2, 1, { 0, 0, 0 }, &gUnkEu_09F6D8E0, 0, 500 },
    { 4, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6D8F4, 0, 520 },
    { 4, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6D908, 0, 522 },
    { 0, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6D91C, 0, 630 },
    { 2, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6D930, 0, 750 },
    { 4, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6D944, 0, 860 },
    { 0, 2, 2, 1, { 0, 0, 0 }, &gUnkEu_09F6D958, 0, 880 },
    { 0, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6D96C, 0, 950 },
    { 4, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6D980, 0, 970 },
    { 4, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6D994, 0, 972 },
    { 0, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6D9A8, 0, 990 },
    { 4, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6D9BC, 0, 1010 },
    { 4, 3, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6D9D0, 0, 1012 },
    { 0, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6D9E4, 0, 1030 },
    { 0, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6D9F8, 0, 1190 },
    { 4, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6DA0C, 0, 1210 },
    { 2, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6DA20, 0, 1230 },
    { 0, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6DA34, 0, 1270 },
    { 4, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6DA48, MSG_SCRIPT_FLAG_END, 1300 },
};
#endif

static const EventCameraKeyframe sEvent095Camera[6] = {
    { -65436, 30720, 81920, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64996, 87040, 51200, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 100, { 0, 0 }, NULL },
    { -64876, 48640, 79872, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 60, { 0, 0 }, NULL },
    { -64776, 0, 0, 0, 0, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64636, 87040, 51200, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -64537, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent095SoundCues[4] = {
    { SONG_BGM_EVENT1, 0, 0, 0 },
    { SONG_BGM_EVENT1, 1031, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT2, 1210, 0, 0 },
    { SONG_EV_EV10_01, 1305, EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent095Track0[30] = {
    { 4, 0, { 0, 0 }, 25600, 92160, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 9, 99, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 4, 629, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 30, 640, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 13, 690, { 0, 0 }, 0, 0, 0, 64, { 0, 0 }, 116, NULL, NULL },
    { 14, 730, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 116, NULL, NULL },
    { 4, 733, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 116, NULL, NULL },
    { 4, 890, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 85, NULL, NULL },
    { 10, 910, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 52, NULL, NULL },
    { 14, 925, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 4, 949, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 30, 951, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 989, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 30, 991, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 1029, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 30, 1031, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 34, 1170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 4, 1189, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 30, 1231, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 1240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 1245, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 1250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 1, 1255, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 1310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 1, 1315, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 1320, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 1325, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 1330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 19, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent095Track1[7] = {
    { 222, 399, { 0, 0 }, 70144, 64000, 0, 0, { 0, 0 }, 82, NULL, NULL },
    { 228, 401, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 85, NULL, NULL },
    { 222, 439, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 85, NULL, NULL },
    { 228, 441, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 85, NULL, NULL },
    { 222, 499, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 85, NULL, NULL },
    { 228, 501, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 85, NULL, NULL },
    { 222, 1400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32853, NULL, NULL },
};

static const EventCharaKeyframe sEvent095Track2[10] = {
    { 114, 0, { 0, 0 }, 27904, 95488, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 119, 92, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 114, 890, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 85, NULL, NULL },
    { 114, 891, { 0, 0 }, 74752, 79360, 0, 0, { 0, 0 }, 82, NULL, NULL },
    { 120, 950, { 0, 0 }, 85760, 65024, 0, 114, { 0, 0 }, 83, NULL, NULL },
    { 114, 1191, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 133, 1231, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 114, 1340, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 122, 1350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 123, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent095Track3[11] = {
    { 146, 0, { 0, 0 }, 20480, 91392, 0, 0, { 0, 0 }, 82, NULL, NULL },
    { 151, 21, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 84, NULL, NULL },
    { 151, 91, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 146, 890, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 891, { 0, 0 }, 52224, 65536, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 153, 950, { 0, 0 }, 76032, 58880, 0, 146, { 0, 0 }, 67, NULL, NULL },
    { 146, 1191, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 161, 1231, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 146, 1345, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 157, 1355, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 158, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent095Track4[2] = {
    { 197, 1305, { 0, 0 }, 83456, 51712, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 200, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent095Track5[2] = {
    { 206, 1305, { 0, 0 }, 105984, 62464, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 209, 2500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent095Track6[4] = {
    { 213, 881, { 0, 0 }, 99840, 47360, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 213, 950, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 256, NULL, CreateQuestionTask },
    { 213, 1191, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 213, 1231, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33024, NULL, CreateExclamationTask },
};

static const EventCharaKeyframe sEvent095Track7[1] = {
    { 264, 2500, { 0, 0 }, 76800, 37888, 0, 0, { 0, 0 }, 32770, NULL, NULL },
};

static const EventCharaTrack sEvent095Tracks[8] = {
    { sEvent095Track0, 0, { 0, 0, 0 } },
    { sEvent095Track1, 7, { 0, 0, 0 } },
    { sEvent095Track2, 1, { 0, 0, 0 } },
    { sEvent095Track3, 2, { 0, 0, 0 } },
    { sEvent095Track4, 4, { 0, 0, 0 } },
    { sEvent095Track5, 5, { 0, 0, 0 } },
    { sEvent095Track6, 6, { 0, 0, 0 } },
    { sEvent095Track7, 11, { 0, 0, 0 } },
};

const EventSequenceDef gEvent095 = {
    8,
    { 0, 0, 0 },
    sEvent095Tracks,
    sEvent095Camera,
    sEvent095Script,
    sEvent095SoundCues,
    NULL,
    1450,
    0,
    1,
    0,
    0,
    0,
    0,
    120,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_096_text.inc"
static const MessageScriptEntry sEvent096Script[6] = {
    { 0, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F91734, 0, 300 },
    { 1, 5, 1, 1, { 0, 0, 0 }, gEventTextUs_08F91740, 0, 340 },
    { 2, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F9176A, 0, 380 },
    { 4, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F9179A, 0, 400 },
    { 1, 5, 3, 1, { 0, 0, 0 }, gEventTextUs_08F917DA, 0, 670 },
    { 0, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08F91812, MSG_SCRIPT_FLAG_END, 710 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent096Script[6] = {
    { 0, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F78204, 0, 300 },
    { 1, 5, 1, 3, { 0, 0, 0 }, gEventTextJp_08F82144, 0, 340 },
    { 2, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F8212C, 0, 380 },
    { 4, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F82108, 0, 400 },
    { 1, 5, 3, 3, { 0, 0, 0 }, gEventTextJp_08F820F8, 0, 670 },
    { 0, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F820EC, MSG_SCRIPT_FLAG_END, 710 },
};

#include "event_096_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent096Script[6] = {
    { 0, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6D78C, 0, 300 },
    { 1, 5, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6D7A0, 0, 340 },
    { 2, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6D7B4, 0, 380 },
    { 4, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6D7C8, 0, 400 },
    { 1, 5, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6D7DC, 0, 670 },
    { 0, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6D7F0, MSG_SCRIPT_FLAG_END, 710 },
};
#endif

static const EventCameraKeyframe sEvent096Camera[3] = {
    { -65126, 55040, 76800, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65056, 89600, 58880, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 30, { 0, 0 }, NULL },
    { -64936, 55040, 76800, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 70, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent096SoundCues[3] = {
    { SONG_BGM_EVENT1, 0, 0, 0 },
    { SONG_EV_EV10_01, 650, 0, 0 },
    { SONG_BGM_EVENT1, 915, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent096Track0[22] = {
    { 21, 150, { 0, 0 }, 50432, 79360, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 22, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 355, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 1, 365, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 370, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 405, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 1, 410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 415, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 435, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 9, 620, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 68, NULL, NULL },
    { 4, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 27, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 685, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 1, 695, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 709, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 31, 711, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 12, 999, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 32804, NULL, NULL },
};

static const EventCharaKeyframe sEvent096Track1[22] = {
    { 158, 155, { 0, 0 }, 37376, 78848, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 159, 175, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 355, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 365, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 143, 370, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 379, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 164, 381, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 405, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 143, 410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 415, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 425, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 602, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 151, 620, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 68, NULL, NULL },
    { 146, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 161, 711, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 715, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 143, 725, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 152, 810, { 0, 0 }, 16384, 94720, 0, 144, { 0, 0 }, 32771, NULL, NULL },
};

static const EventCharaKeyframe sEvent096Track2[22] = {
    { 123, 158, { 0, 0 }, 52736, 84480, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 124, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 113, 315, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 112, 325, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 111, 330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 339, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 125, 341, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 405, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 111, 410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 415, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 113, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 425, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 603, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 119, 620, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 68, NULL, NULL },
    { 114, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 133, 711, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 113, 715, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 112, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 111, 725, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 121, 820, { 0, 0 }, 20480, 97024, 0, 112, { 0, 0 }, 32771, NULL, NULL },
};

static const EventCharaKeyframe sEvent096Track3[1] = {
    { 219, 999, { 0, 0 }, 89600, 59136, 0, 0, { 0, 0 }, 32770, NULL, NULL },
};

static const EventCharaKeyframe sEvent096Track4[8] = {
    { 206, 450, { 0, 0 }, 82944, 50944, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 212, 620, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 206, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 209, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 206, 840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 206, 850, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 212, 883, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 212, 999, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 32772, NULL, NULL },
};

static const EventCharaKeyframe sEvent096Track5[9] = {
    { 206, 450, { 0, 0 }, 80128, 52736, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 212, 605, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 211, 635, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 206, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 209, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 206, 840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 206, 850, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 212, 910, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 212, 999, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 32772, NULL, NULL },
};

static const EventCharaKeyframe sEvent096Track6[7] = {
    { 206, 450, { 0, 0 }, 76800, 54528, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 212, 590, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 212, 620, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 206, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 209, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 206, 850, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 212, 999, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 32772, NULL, NULL },
};

static const EventCharaKeyframe sEvent096Track7[9] = {
    { 197, 450, { 0, 0 }, 103680, 63232, 0, 0, { 0, 0 }, 18, NULL, NULL },
    { 203, 620, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 20, NULL, NULL },
    { 197, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 21, NULL, NULL },
    { 200, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 21, NULL, NULL },
    { 197, 840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 21, NULL, NULL },
    { 199, 850, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 21, NULL, NULL },
    { 202, 878, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 20, NULL, NULL },
    { 203, 920, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 20, NULL, NULL },
    { 203, 999, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 32772, NULL, NULL },
};

static const EventCharaKeyframe sEvent096Track8[10] = {
    { 197, 450, { 0, 0 }, 100864, 65024, 0, 0, { 0, 0 }, 18, NULL, NULL },
    { 203, 605, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 20, NULL, NULL },
    { 203, 635, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 84, NULL, NULL },
    { 197, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 21, NULL, NULL },
    { 200, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 21, NULL, NULL },
    { 197, 840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 21, NULL, NULL },
    { 199, 850, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 21, NULL, NULL },
    { 202, 910, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 20, NULL, NULL },
    { 203, 940, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 20, NULL, NULL },
    { 203, 999, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 32772, NULL, NULL },
};

static const EventCharaKeyframe sEvent096Track9[9] = {
    { 197, 450, { 0, 0 }, 97536, 66560, 0, 0, { 0, 0 }, 18, NULL, NULL },
    { 203, 520, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 20, NULL, NULL },
    { 203, 590, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 20, NULL, NULL },
    { 202, 620, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 20, NULL, NULL },
    { 197, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 21, NULL, NULL },
    { 200, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 21, NULL, NULL },
    { 197, 850, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 21, NULL, NULL },
    { 203, 900, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 20, NULL, NULL },
    { 203, 999, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 32772, NULL, NULL },
};

static const EventCharaTrack sEvent096Tracks[10] = {
    { sEvent096Track0, 0, { 0, 0, 0 } },
    { sEvent096Track1, 2, { 0, 0, 0 } },
    { sEvent096Track2, 1, { 0, 0, 0 } },
    { sEvent096Track3, 6, { 0, 0, 0 } },
    { sEvent096Track4, 5, { 0, 0, 0 } },
    { sEvent096Track5, 5, { 0, 0, 0 } },
    { sEvent096Track6, 5, { 0, 0, 0 } },
    { sEvent096Track7, 4, { 0, 0, 0 } },
    { sEvent096Track8, 4, { 0, 0, 0 } },
    { sEvent096Track9, 4, { 0, 0, 0 } },
};

const EventSequenceDef gEvent096 = {
    10,
    { 0, 0, 0 },
    sEvent096Tracks,
    sEvent096Camera,
    sEvent096Script,
    sEvent096SoundCues,
    NULL,
    920,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_097_text.inc"
static const MessageScriptEntry sEvent097Script[21] = {
    { 0, 4, 1, 1, { 0, 0, 0 }, gEventTextUs_08F92A60, 0, 300 },
    { 5, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F92AE0, 0, 450 },
    { 0, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08F92B8A, 0, 470 },
    { 2, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F92C02, 0, 480 },
    { 1, 4, 1, 1, { 0, 0, 0 }, gEventTextUs_08F92C68, 0, 490 },
    { 5, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08F92C84, 0, 630 },
    { 5, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08F92CE4, 0, 632 },
    { 5, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08F92D06, 0, 750 },
    { 9, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F92D48, 0, 770 },
    { 9, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F92DD4, 0, 850 },
    { 9, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F92E72, 0, 852 },
    { 9, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F92EE6, 0, 854 },
    { 0, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F92FB2, 0, 870 },
    { 6, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F93022, 0, 900 },
    { 0, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F93118, 0, 1050 },
    { 9, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F93186, 0, 1070 },
    { 0, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08F931FE, 0, 1080 },
    { 9, 0, 2, 1, { 0, 0, 0 }, gEventTextUs_08F93208, 0, 1190 },
    { 9, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F93300, 0, 1192 },
    { 0, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F93378, 0, 1210 },
    { 9, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F93382, MSG_SCRIPT_FLAG_END, 1280 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent097Script[21] = {
    { 0, 4, 1, 3, { 0, 0, 0 }, gEventTextJp_08F83924, 0, 300 },
    { 5, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F838D8, 0, 450 },
    { 0, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F838B0, 0, 470 },
    { 2, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F83888, 0, 480 },
    { 1, 4, 1, 3, { 0, 0, 0 }, gEventTextJp_08F83868, 0, 490 },
    { 5, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8382C, 0, 630 },
    { 5, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F83818, 0, 632 },
    { 5, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F83808, 0, 750 },
    { 9, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F837D0, 0, 770 },
    { 9, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8377C, 0, 850 },
    { 9, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F83728, 0, 852 },
    { 9, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F836DC, 0, 854 },
    { 0, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F83694, 0, 870 },
    { 6, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F83640, 0, 900 },
    { 0, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F83614, 0, 1050 },
    { 9, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F835D4, 0, 1070 },
    { 0, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F835CC, 0, 1080 },
    { 9, 0, 2, 3, { 0, 0, 0 }, gEventTextJp_08F8357C, 0, 1190 },
    { 9, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F83544, 0, 1192 },
    { 0, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F83538, 0, 1210 },
    { 9, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F83504, MSG_SCRIPT_FLAG_END, 1280 },
};

#include "event_097_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent097Script[21] = {
    { 0, 4, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6DA5C, 0, 300 },
    { 5, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6DA70, 0, 450 },
    { 0, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6DA84, 0, 470 },
    { 2, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6DA98, 0, 480 },
    { 1, 4, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6DAAC, 0, 490 },
    { 5, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6DAC0, 0, 630 },
    { 5, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6DAD4, 0, 632 },
    { 5, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6DAE8, 0, 750 },
    { 9, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6DAFC, 0, 770 },
    { 9, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6DB10, 0, 850 },
    { 9, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6DB24, 0, 852 },
    { 9, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6DB38, 0, 854 },
    { 0, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6DB4C, 0, 870 },
    { 6, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6DB60, 0, 900 },
    { 0, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6DB74, 0, 1050 },
    { 9, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6DB88, 0, 1070 },
    { 0, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6DB9C, 0, 1080 },
    { 9, 0, 2, 1, { 0, 0, 0 }, &gUnkEu_09F6DBB0, 0, 1190 },
    { 9, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6DBC4, 0, 1192 },
    { 0, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6DBD8, 0, 1210 },
    { 9, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6DBEC, MSG_SCRIPT_FLAG_END, 1280 },
};
#endif

static const EventCameraKeyframe sEvent097Camera[4] = {
    { -64876, 57344, 45312, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64696, 61184, 38912, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 20, { 0, 0 }, NULL },
    { -64386, 51456, 40960, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 20, { 0, 0 }, NULL },
    { -55537, 57344, 45312, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 20, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent097SoundCues[5] = {
    { SONG_BGM_EVENT3, 0, 0, 0 },
    { SONG_SND_346, 640, 0, 0 },
    { SONG_SND_346, 821, 0, 0 },
    { SONG_SND_346, 1131, 0, 0 },
    { SONG_BGM_EVENT3, 1395, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent097Track0[10] = {
    { 221, 100, { 0, 0 }, 54016, 43264, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 223, 150, { 0, 0 }, 48896, 40704, 0, 221, { 0, 0 }, 67, NULL, NULL },
    { 221, 301, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 221, 430, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 221, 660, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 222, 670, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 222, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 222, 1140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 221, 1150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 221, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent097Track1[19] = {
    { 4, 0, { 0, 0 }, 96768, 64768, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 9, 150, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 4, 299, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 36, 469, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 30, 491, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 16, 620, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 4, 662, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 0, 665, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 670, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 0, 835, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 869, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 34, 901, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 34, 1049, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 34, 1051, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 1145, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 1150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent097Track2[13] = {
    { 114, 0, { 0, 0 }, 106752, 62976, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 119, 150, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 114, 489, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 126, 491, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 660, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 110, 665, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 670, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 110, 835, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 1140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 113, 1145, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 1150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent097Track3[13] = {
    { 146, 0, { 0, 0 }, 102400, 71168, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 151, 150, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 146, 479, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 165, 481, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 665, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 142, 670, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 675, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 142, 835, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 1140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 145, 1145, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 1150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent097Track4[13] = {
    { 231, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 231, 151, { 0, 0 }, 61952, 47360, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 234, 180, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, EventCharaHop, NULL },
    { 231, 660, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 231, 670, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 231, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 231, 880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 231, 885, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 229, 1071, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 229, 1075, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 231, 1140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 229, 1150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 229, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent097Track5[11] = {
    { 337, 640, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 337, 765, { 0, 0 }, 81920, 32768, 0, 0, { 0, 0 }, 258, EventCharaFadeIn, NULL },
    { 340, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 340, 820, { 0, 0 }, 81920, 32768, 0, 0, { 0, 0 }, 258, EventCharaFadeOut, NULL },
    { 337, 821, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 339, 1090, { 0, 0 }, 34048, 34048, 0, 0, { 0, 0 }, 258, EventCharaFadeIn, NULL },
    { 339, 1130, { 0, 0 }, 34048, 34048, 0, 0, { 0, 0 }, 258, EventCharaFadeOut, NULL },
    { 337, 1131, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 338, 1220, { 0, 0 }, 40704, 57088, 0, 0, { 0, 0 }, 66, EventCharaFadeIn, NULL },
    { 338, 1300, { 0, 0 }, 40704, 57088, 0, 0, { 0, 0 }, 66, EventCharaFadeOut, NULL },
    { 337, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32834, NULL, NULL },
};

static const EventCharaTrack sEvent097Tracks[6] = {
    { sEvent097Track0, 7, { 0, 0, 0 } },
    { sEvent097Track1, 0, { 0, 0, 0 } },
    { sEvent097Track2, 1, { 0, 0, 0 } },
    { sEvent097Track3, 2, { 0, 0, 0 } },
    { sEvent097Track4, 8, { 0, 0, 0 } },
    { sEvent097Track5, 17, { 0, 0, 0 } },
};

const EventSequenceDef gEvent097 = {
    6,
    { 0, 0, 0 },
    sEvent097Tracks,
    sEvent097Camera,
    sEvent097Script,
    sEvent097SoundCues,
    NULL,
    1400,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_098_text.inc"
static const MessageScriptEntry sEvent098Script[16] = {
    { 2, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F94210, 0, 170 },
    { 5, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F94274, 0, 200 },
    { 5, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9429A, 0, 450 },
    { 4, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F942AE, 0, 530 },
    { 0, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08F94306, 0, 540 },
    { 4, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F94314, 0, 560 },
    { 4, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F94398, 0, 700 },
    { 4, 2, 4, 1, { 0, 0, 0 }, gEventTextUs_08F943BE, 0, 710 },
    { 4, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08F943D6, 0, 910 },
    { 4, 2, 4, 1, { 0, 0, 0 }, gEventTextUs_08F943DE, 0, 913 },
    { 1, 5, 3, 1, { 0, 0, 0 }, gEventTextUs_08F94418, 0, 930 },
    { 4, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08F94422, 0, 950 },
    { 4, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08F9445E, 0, 952 },
    { 0, 0, 2, 1, { 0, 0, 0 }, gEventTextUs_08F9449C, 0, 1070 },
    { 2, 0, 2, 1, { 0, 0, 0 }, gEventTextUs_08F944CA, 0, 1090 },
    { 5, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F9451A, MSG_SCRIPT_FLAG_END, 1190 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent098Script[16] = {
    { 2, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F84890, 0, 170 },
    { 5, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8487C, 0, 200 },
    { 5, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8486C, 0, 450 },
    { 4, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F84848, 0, 530 },
    { 0, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8483C, 0, 540 },
    { 4, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F84800, 0, 560 },
    { 4, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F847F0, 0, 700 },
    { 4, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08F847DC, 0, 710 },
    { 4, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F847D4, 0, 910 },
    { 4, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08F847A0, 0, 913 },
    { 1, 5, 3, 3, { 0, 0, 0 }, gEventTextJp_08F84798, 0, 930 },
    { 4, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F84774, 0, 950 },
    { 4, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F84760, 0, 952 },
    { 0, 0, 2, 3, { 0, 0, 0 }, gEventTextJp_08F8474C, 0, 1070 },
    { 2, 0, 2, 3, { 0, 0, 0 }, gEventTextJp_08F8471C, 0, 1090 },
    { 5, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F84700, MSG_SCRIPT_FLAG_END, 1190 },
};

#include "event_098_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent098Script[16] = {
    { 2, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6DE44, 0, 170 },
    { 5, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6DE58, 0, 200 },
    { 5, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6DE6C, 0, 450 },
    { 4, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6DE80, 0, 530 },
    { 0, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6DE94, 0, 540 },
    { 4, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6DEA8, 0, 560 },
    { 4, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6DEBC, 0, 700 },
    { 4, 2, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6DED0, 0, 710 },
    { 4, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6DEE4, 0, 910 },
    { 4, 2, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6DEF8, 0, 913 },
    { 1, 5, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6DF0C, 0, 930 },
    { 4, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6DF20, 0, 950 },
    { 4, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6DF34, 0, 952 },
    { 0, 0, 2, 1, { 0, 0, 0 }, &gUnkEu_09F6DF48, 0, 1070 },
    { 2, 0, 2, 1, { 0, 0, 0 }, &gUnkEu_09F6DF5C, 0, 1090 },
    { 5, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6DF70, MSG_SCRIPT_FLAG_END, 1190 },
};
#endif

static const EvSoundCue sEvent098SoundCues[4] = {
    { SONG_BGM_EVENT1, 0, 0, 0 },
    { SONG_EV_FLASH02, 600, 0, 0 },
    { SONG_BGM_EVENT2, 1130, 0, 0 },
    { SONG_EV_FLASH02, 1230, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent098Camera[16] = {
    { -65076, 47872, 89088, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64975, 74752, 65792, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 60, { 0, 0 }, NULL },
    { -64956, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -64936, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -64876, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -64846, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 20, { 0, 0 }, NULL },
    { -64566, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64486, 55040, 79104, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -64436, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64426, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -64396, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -64336, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64326, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -64306, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -64136, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 30, { 0, 0 }, NULL },
    { -55537, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent098Track0[7] = {
    { 4, 1, { 0, 0 }, 32000, 93952, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 9, 40, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 4, 451, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 4, 1110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 27, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 4, 2200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent098Track2[14] = {
    { 146, 1, { 0, 0 }, 20992, 94208, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 151, 40, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 146, 90, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 142, 120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 145, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 169, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 165, 171, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 451, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 145, 1089, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 1091, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaToggleAnim, NULL },
    { 146, 1112, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 161, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 146, 2200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent098Track1[7] = {
    { 114, 1, { 0, 0 }, 31232, 101888, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 119, 40, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 114, 451, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 114, 1114, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 133, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 114, 2200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent098Track6[3] = {
    { 197, 201, { 0, 0 }, 90368, 73728, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 200, 341, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 197, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent098Track7[3] = {
    { 197, 207, { 0, 0 }, 100096, 70400, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 200, 341, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 197, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent098Track4[3] = {
    { 206, 201, { 0, 0 }, 67840, 58368, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 209, 341, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 206, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent098Track5[3] = {
    { 206, 208, { 0, 0 }, 71424, 64768, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 209, 341, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 206, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent098Track3[8] = {
    { 215, 460, { 0, 0 }, 88832, 66048, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 214, 510, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 219, 711, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 219, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateQuestionTask },
    { 219, 781, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 219, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 219, 911, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 218, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent098Track8[15] = {
    { 222, 1, { 0, 0 }, 38912, 90880, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 224, 40, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 222, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 221, 190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 221, 211, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 221, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 222, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 226, 380, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 222, 451, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 224, 520, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 68, NULL, NULL },
    { 222, 1091, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 221, 1100, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 221, 1105, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 225, 1180, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 221, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent098Tracks[9] = {
    { sEvent098Track0, 0, { 0, 0, 0 } },
    { sEvent098Track1, 1, { 0, 0, 0 } },
    { sEvent098Track2, 2, { 0, 0, 0 } },
    { sEvent098Track3, 6, { 0, 0, 0 } },
    { sEvent098Track4, 5, { 0, 0, 0 } },
    { sEvent098Track5, 5, { 0, 0, 0 } },
    { sEvent098Track6, 4, { 0, 0, 0 } },
    { sEvent098Track7, 4, { 0, 0, 0 } },
    { sEvent098Track8, 7, { 0, 0, 0 } },
};

const EventSequenceDef gEvent098 = {
    9,
    { 0, 0, 0 },
    sEvent098Tracks,
    sEvent098Camera,
    sEvent098Script,
    sEvent098SoundCues,
    NULL,
    1340,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    99,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_099_text.inc"
static const MessageScriptEntry sEvent099Script[1] = {
    { 0, 2, 2, 1, { 0, 0, 0 }, gEventTextUs_08F95258, MSG_SCRIPT_FLAG_END, 130 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent099Script[1] = {
    { 0, 2, 2, 3, { 0, 0, 0 }, gEventTextJp_08F8544C, MSG_SCRIPT_FLAG_END, 130 },
};

#include "event_099_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent099Script[1] = {
    { 0, 2, 2, 1, { 0, 0, 0 }, &gUnkEu_09F6DC00, MSG_SCRIPT_FLAG_END, 130 },
};
#endif

static const EventCameraKeyframe sEvent099Camera[2] = {
    { -65536, 30720, 43008, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, NULL },
    { -64536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 60, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent099SoundCues[3] = {
    { SONG_BGM_EVENT2, 1, 0, 0 },
    { SONG_EV_EV10_05, 131, 0, 0 },
    { SONG_BGM_BOSS1_WORLD, 180, EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent099Track0[2] = {
    { 18, 131, { 0, 0 }, 15360, 55296, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 13, 160, { 0, 0 }, 0, 0, 0, 64, { 0, 0 }, 32836, NULL, NULL },
};

static const EventCharaKeyframe sEvent099Track1[3] = {
    { 932, 131, { 0, 0 }, 21248, 32768, -9728, 0, { 0, 0 }, 2, NULL, NULL },
    { 933, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 932, 2200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent099Tracks[2] = {
    { sEvent099Track0, 0, { 0, 0, 0 } },
    { sEvent099Track1, 95, { 0, 0, 0 } },
};

const EventSequenceDef gEvent099 = {
    2,
    { 0, 0, 0 },
    sEvent099Tracks,
    sEvent099Camera,
    sEvent099Script,
    sEvent099SoundCues,
    NULL,
    160,
    0,
    1,
    0,
    0,
    0,
    0,
    150,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_100_text.inc"
static const MessageScriptEntry sEvent100Script[28] = {
    { 4, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F95410, 0, 200 },
    { 4, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08F95440, 0, 221 },
    { 0, 7, 2, 1, { 0, 0, 0 }, gEventTextUs_08F954C2, 0, 250 },
    { 4, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F954E8, 0, 280 },
    { 4, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08F9554E, 0, 300 },
    { 5, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F955B8, 0, 320 },
    { 5, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F955F0, 0, 330 },
    { 0, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08F9565C, 0, 368 },
    { 5, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F95666, 0, 390 },
    { 5, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F956EE, 0, 392 },
    { 5, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08F9578C, 0, 395 },
    { 0, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08F957BC, 0, 420 },
    { 0, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08F957CC, 0, 425 },
    { 4, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08F95812, 0, 455 },
    { 5, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F95840, 0, 480 },
    { 4, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F9588C, 0, 500 },
    { 4, 3, 4, 1, { 0, 0, 0 }, gEventTextUs_08F958E8, 0, 505 },
    { 5, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F95966, 0, 800 },
    { 0, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F95992, 0, 820 },
    { 5, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F959FA, 0, 840 },
    { 5, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F95ABE, 0, 842 },
    { 5, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08F95B5C, 0, 844 },
    { 5, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F95BC2, 0, 1000 },
    { 0, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F95BE6, 0, 1020 },
    { 0, 4, 4, 1, { 0, 0, 0 }, gEventTextUs_08F95C0A, 0, 1022 },
    { 2, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F95C4E, 0, 1050 },
    { 2, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08F95CAC, 0, 1052 },
    { 1, 4, 0, 1, { 0, 0, 0 }, gEventTextUs_08F95D2E, MSG_SCRIPT_FLAG_END, 1070 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent100Script[28] = {
    { 4, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F85D3C, 0, 200 },
    { 4, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F85CF0, 0, 221 },
    { 0, 7, 2, 3, { 0, 0, 0 }, gEventTextJp_08F85CC8, 0, 250 },
    { 4, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F85C90, 0, 280 },
    { 4, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F85C64, 0, 300 },
    { 5, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F85C48, 0, 320 },
    { 5, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F85C0C, 0, 330 },
    { 0, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F85C04, 0, 368 },
    { 5, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F85BD0, 0, 390 },
    { 5, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F85B98, 0, 392 },
    { 5, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F85B84, 0, 395 },
    { 0, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F85B74, 0, 420 },
    { 0, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F85B48, 0, 425 },
    { 4, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F85B30, 0, 455 },
    { 5, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F85AFC, 0, 480 },
    { 4, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F85AD8, 0, 500 },
    { 4, 3, 4, 3, { 0, 0, 0 }, gEventTextJp_08F85A9C, 0, 505 },
    { 5, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F85A84, 0, 800 },
    { 0, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F85A44, 0, 820 },
    { 5, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F859E4, 0, 840 },
    { 5, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F8598C, 0, 842 },
    { 5, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F85950, 0, 844 },
    { 5, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F85940, 0, 1000 },
    { 0, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F8592C, 0, 1020 },
    { 0, 4, 4, 3, { 0, 0, 0 }, gEventTextJp_08F85900, 0, 1022 },
    { 2, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F858D0, 0, 1050 },
    { 2, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F85888, 0, 1052 },
    { 1, 4, 0, 3, { 0, 0, 0 }, gEventTextJp_08F85860, MSG_SCRIPT_FLAG_END, 1070 },
};

#include "event_100_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent100Script[28] = {
    { 4, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6DC14, 0, 200 },
    { 4, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6DC28, 0, 221 },
    { 0, 7, 2, 1, { 0, 0, 0 }, &gUnkEu_09F6DC3C, 0, 250 },
    { 4, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6DC50, 0, 280 },
    { 4, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6DC64, 0, 300 },
    { 5, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6DC78, 0, 320 },
    { 5, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6DC8C, 0, 330 },
    { 0, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6DCA0, 0, 368 },
    { 5, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6DCB4, 0, 390 },
    { 5, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6DCC8, 0, 392 },
    { 5, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6DCDC, 0, 395 },
    { 0, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6DCF0, 0, 420 },
    { 0, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6DD04, 0, 425 },
    { 4, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6DD18, 0, 455 },
    { 5, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6DD2C, 0, 480 },
    { 4, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6DD40, 0, 500 },
    { 4, 3, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6DD54, 0, 505 },
    { 5, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6DD68, 0, 800 },
    { 0, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6DD7C, 0, 820 },
    { 5, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6DD90, 0, 840 },
    { 5, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6DDA4, 0, 842 },
    { 5, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6DDB8, 0, 844 },
    { 5, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6DDCC, 0, 1000 },
    { 0, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6DDE0, 0, 1020 },
    { 0, 4, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6DDF4, 0, 1022 },
    { 2, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6DE08, 0, 1050 },
    { 2, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6DE1C, 0, 1052 },
    { 1, 4, 0, 1, { 0, 0, 0 }, &gUnkEu_09F6DE30, MSG_SCRIPT_FLAG_END, 1070 },
};
#endif

static const EvSoundCue sEvent100SoundCues[4] = {
    { SONG_BGM_EVENT3, 1, 0, 0 },
    { SONG_EV_EV10_01, 301, 0, 0 },
    { SONG_EV_EV11_00, 506, 0, 0 },
    { SONG_BGM_EVENT3, 1070, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent100Camera[6] = {
    { -65506, 0, 0, 0, 0, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65286, 67328, 70144, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 60, { 0, 0 }, NULL },
    { -64986, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64736, 55808, 76800, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 70, { 0, 0 }, NULL },
    { -64446, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64436, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_BLACK | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 30, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent100Track0[13] = {
    { 4, 1, { 0, 0 }, 61440, 81920, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 4, 249, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 36, 301, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 358, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 27, 369, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 28, 421, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 423, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 426, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 801, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 850, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 34, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 4, 1050, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 2200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent100Track2[5] = {
    { 146, 836, { 0, 0 }, 47104, 81408, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 146, 1030, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 1049, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 164, 1053, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 2200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent100Track1[5] = {
    { 114, 1, { 0, 0 }, 55808, 84992, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 114, 840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 110, 1050, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 1069, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 131, 1071, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32768, NULL, CreateSmokeTask },
};

static const EventCharaKeyframe sEvent100Track6[9] = {
    { 197, 301, { 0, 0 }, 86016, 71168, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 200, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 197, 516, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 203, 528, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 197, 605, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 202, 625, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 202, 690, { 0, 0 }, 93696, 64000, 0, 199, { 0, 0 }, 67, NULL, NULL },
    { 199, 2200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 197, 2200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent100Track7[7] = {
    { 197, 308, { 0, 0 }, 97280, 70144, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 200, 368, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 197, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 202, 710, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 202, 730, { 0, 0 }, 93696, 64000, 0, 199, { 0, 0 }, 67, NULL, NULL },
    { 199, 2200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 197, 2200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent100Track4[10] = {
    { 206, 301, { 0, 0 }, 75520, 66816, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 209, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 206, 516, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 211, 528, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 206, 560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 212, 590, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 207, 594, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 211, 660, { 0, 0 }, 93696, 64000, 0, 208, { 0, 0 }, 67, NULL, NULL },
    { 208, 2200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 208, 2200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent100Track5[8] = {
    { 206, 308, { 0, 0 }, 78592, 60672, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 209, 368, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 206, 655, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 212, 685, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 207, 688, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 211, 705, { 0, 0 }, 93696, 64000, 0, 208, { 0, 0 }, 67, NULL, NULL },
    { 208, 2200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 206, 2200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent100Track3[14] = {
    { 215, 201, { 0, 0 }, 71424, 74752, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 214, 220, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 219, 281, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 216, 284, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 216, 321, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 215, 331, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 215, 395, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 215, 505, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 219, 520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 215, 523, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 216, 529, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 217, 600, { 0, 0 }, 93696, 64000, 0, 216, { 0, 0 }, 67, NULL, NULL },
    { 216, 2200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 215, 2200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent100Track8[7] = {
    { 222, 310, { 0, 0 }, 53248, 77568, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 224, 319, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 222, 393, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 221, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 222, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 221, 1050, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 221, 2200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent100Tracks[9] = {
    { sEvent100Track0, 0, { 0, 0, 0 } },
    { sEvent100Track1, 1, { 0, 0, 0 } },
    { sEvent100Track2, 2, { 0, 0, 0 } },
    { sEvent100Track3, 6, { 0, 0, 0 } },
    { sEvent100Track4, 5, { 0, 0, 0 } },
    { sEvent100Track5, 5, { 0, 0, 0 } },
    { sEvent100Track6, 4, { 0, 0, 0 } },
    { sEvent100Track7, 4, { 0, 0, 0 } },
    { sEvent100Track8, 7, { 0, 0, 0 } },
};

const EventSequenceDef gEvent100 = {
    9,
    { 0, 0, 0 },
    sEvent100Tracks,
    sEvent100Camera,
    sEvent100Script,
    sEvent100SoundCues,
    NULL,
    1150,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    65535,
    60,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_101_text.inc"
static const MessageScriptEntry sEvent101Script[12] = {
    { 2, 2, 2, 1, { 0, 0, 0 }, gEventTextUs_08F96C6C, 0, 300 },
    { 0, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08F96CCC, 0, 340 },
    { 2, 0, 2, 1, { 0, 0, 0 }, gEventTextUs_08F96D20, 0, 360 },
    { 0, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08F96D80, 0, 380 },
    { 1, 0, 0, 1, { 0, 0, 0 }, gEventTextUs_08F96DBC, 0, 400 },
    { 13, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08F96E26, 0, 630 },
    { 1, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F96E6C, 0, 650 },
    { 13, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08F96E78, 0, 670 },
    { 2, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F96EFE, 0, 850 },
    { 13, 4, 1, 1, { 0, 0, 0 }, gEventTextUs_08F96F60, 0, 870 },
    { 0, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F96FD2, 0, 1130 },
    { 1, 0, 0, 1, { 0, 0, 0 }, gEventTextUs_08F97006, MSG_SCRIPT_FLAG_END, 1150 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent101Script[12] = {
    { 2, 2, 2, 3, { 0, 0, 0 }, gEventTextJp_08F86C58, 0, 300 },
    { 0, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F86C34, 0, 340 },
    { 2, 0, 2, 3, { 0, 0, 0 }, gEventTextJp_08F86C04, 0, 360 },
    { 0, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F86BEC, 0, 380 },
    { 1, 0, 0, 3, { 0, 0, 0 }, gEventTextJp_08F86BAC, 0, 400 },
    { 13, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08F86B7C, 0, 630 },
    { 1, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F794C8, 0, 650 },
    { 13, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08F86B34, 0, 670 },
    { 2, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F86B1C, 0, 850 },
    { 13, 4, 1, 3, { 0, 0, 0 }, gEventTextJp_08F86AF0, 0, 870 },
    { 0, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F86ADC, 0, 1130 },
    { 1, 0, 0, 3, { 0, 0, 0 }, gEventTextJp_08F86AC0, MSG_SCRIPT_FLAG_END, 1150 },
};

#include "event_101_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent101Script[12] = {
    { 2, 2, 2, 1, { 0, 0, 0 }, &gUnkEu_09F5E264, 0, 300 },
    { 0, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E278, 0, 340 },
    { 2, 0, 2, 1, { 0, 0, 0 }, &gUnkEu_09F5E28C, 0, 360 },
    { 0, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E2A0, 0, 380 },
    { 1, 0, 0, 1, { 0, 0, 0 }, &gUnkEu_09F5E2B4, 0, 400 },
    { 13, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E2C8, 0, 630 },
    { 1, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E2DC, 0, 650 },
    { 13, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E2F0, 0, 670 },
    { 2, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E304, 0, 850 },
    { 13, 4, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E318, 0, 870 },
    { 0, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E32C, 0, 1130 },
    { 1, 0, 0, 1, { 0, 0, 0 }, &gUnkEu_09F5E340, MSG_SCRIPT_FLAG_END, 1150 },
};
#endif

static const EventCameraKeyframe sEvent101Camera[8] = {
    { -65536, 73472, 58624, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, NULL },
    { -65134, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 80, { 0, 0 }, NULL },
    { -64976, 56320, 44800, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -64936, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64906, 65792, 54016, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 30, { 0, 0 }, NULL },
    { -64591, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -60536, 73472, 58624, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -55537, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent101SoundCues[3] = {
    { SONG_BGM_EVENT1, 0, 0, 0 },
    { SONG_SND_350, 680, 0, 0 },
    { SONG_BGM_EVENT1, 1245, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent101Track0[16] = {
    { 4, 310, { 0, 0 }, 73472, 61184, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 3, 315, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 320, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 1, 325, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 32, 401, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 415, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 0, 425, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 430, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 950, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 0, 960, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 1115, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent101Track1[11] = {
    { 114, 1, { 0, 0 }, 81920, 61184, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 114, 399, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 126, 401, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 649, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 126, 651, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 849, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 970, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 110, 1110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 1149, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 127, 1151, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 128, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent101Track2[17] = {
    { 146, 150, { 0, 0 }, 69376, 67328, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 144, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 299, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 165, 301, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 359, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 170, 401, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 415, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 142, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 425, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 849, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 165, 851, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 930, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 142, 950, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 1100, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent101Track3[18] = {
    { 314, 410, { 0, 0 }, 4096, 27136, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 319, 520, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 100, NULL, NULL },
    { 315, 523, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 100, NULL, NULL },
    { 314, 590, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 315, 594, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 319, 620, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 100, NULL, NULL },
    { 315, 623, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 100, NULL, NULL },
    { 314, 629, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 324, 631, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 314, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 322, 770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 315, 790, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 100, NULL, NULL },
    { 316, 795, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 316, 880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 316, 890, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 317, 895, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 321, 999, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 316, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent101Track4[3] = {
    { 590, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 590, 720, { 0, 0 }, 62208, 48128, 0, 0, { 0, 0 }, 274, NULL, NULL },
    { 590, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33026, NULL, NULL },
};

static const EventCharaTrack sEvent101Tracks[5] = {
    { sEvent101Track0, 0, { 0, 0, 0 } },
    { sEvent101Track1, 1, { 0, 0, 0 } },
    { sEvent101Track2, 2, { 0, 0, 0 } },
    { sEvent101Track3, 15, { 0, 0, 0 } },
    { sEvent101Track4, 49, { 0, 0, 0 } },
};

const EventSequenceDef gEvent101 = {
    5,
    { 0, 0, 0 },
    sEvent101Tracks,
    sEvent101Camera,
    sEvent101Script,
    sEvent101SoundCues,
    NULL,
    1250,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    1,
    255,
    255,
};

#ifdef VERSION_US
#include "event_102_text.inc"
static const MessageScriptEntry sEvent102Script[19] = {
    { 23, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F97BE8, 0, 300 },
    { 0, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F97C06, 0, 340 },
    { 23, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F97C2E, 0, 400 },
    { 23, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08F97CE0, 0, 402 },
    { 23, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08F97D48, 0, 404 },
    { 0, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08F97DBA, 0, 420 },
    { 23, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F97DEC, 0, 450 },
    { 0, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F97E7E, 0, 520 },
    { 2, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F97ECA, 0, 540 },
    { 2, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F97F2A, 0, 542 },
    { 0, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08F97F92, 0, 670 },
    { 6, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08F97FDE, 0, 720 },
    { 1, 5, 1, 1, { 0, 0, 0 }, gEventTextUs_08F9800E, 0, 740 },
    { 6, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9804C, 0, 760 },
    { 23, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9808C, 0, 800 },
    { 23, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F98128, 0, 860 },
    { 23, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F981AE, 0, 960 },
    { 0, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F98250, 0, 1130 },
    { 2, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F982C6, MSG_SCRIPT_FLAG_END, 1160 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent102Script[19] = {
    { 23, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F87CA8, 0, 300 },
    { 0, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F87C94, 0, 340 },
    { 23, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F87C40, 0, 400 },
    { 23, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F87C18, 0, 402 },
    { 23, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F87BD8, 0, 404 },
    { 0, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F87BC0, 0, 420 },
    { 23, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F87B68, 0, 450 },
    { 0, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F87B3C, 0, 520 },
    { 2, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F87B10, 0, 540 },
    { 2, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F87AE4, 0, 542 },
    { 0, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F87AA4, 0, 670 },
    { 6, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F87A88, 0, 720 },
    { 1, 5, 1, 3, { 0, 0, 0 }, gEventTextJp_08F87A4C, 0, 740 },
    { 6, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F87A28, 0, 760 },
    { 23, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F879DC, 0, 800 },
    { 23, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8799C, 0, 860 },
    { 23, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F8793C, 0, 960 },
    { 0, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F878F4, 0, 1130 },
    { 2, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F878D8, MSG_SCRIPT_FLAG_END, 1160 },
};

#include "event_102_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent102Script[19] = {
    { 23, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E354, 0, 300 },
    { 0, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E368, 0, 340 },
    { 23, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E37C, 0, 400 },
    { 23, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5E390, 0, 402 },
    { 23, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5E3A4, 0, 404 },
    { 0, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E3B8, 0, 420 },
    { 23, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E3CC, 0, 450 },
    { 0, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E3E0, 0, 520 },
    { 2, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E3F4, 0, 540 },
    { 2, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5E408, 0, 542 },
    { 0, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E41C, 0, 670 },
    { 6, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E430, 0, 720 },
    { 1, 5, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E444, 0, 740 },
    { 6, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E458, 0, 760 },
    { 23, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E46C, 0, 800 },
    { 23, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E480, 0, 860 },
    { 23, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E494, 0, 960 },
    { 0, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E4A8, 0, 1130 },
    { 2, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E4BC, MSG_SCRIPT_FLAG_END, 1160 },
};
#endif

static const EventCameraKeyframe sEvent102Camera[3] = {
    { -64775, 48128, 38144, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64566, 35840, 29440, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 30, { 0, 0 }, NULL },
    { -64336, 48128, 38144, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 30, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent102SoundCues[2] = {
    { SONG_BGM_EVENT1, 0, 0, 0 },
    { SONG_BGM_EVENT1, 1245, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent102Track0[15] = {
    { 461, 350, { 0, 0 }, 36864, 35328, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 460, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 460, 460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 461, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 461, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 463, 520, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 461, 770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 460, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 460, 790, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 460, 810, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 463, 850, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 460, 870, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 462, 950, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 460, 970, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 461, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent102Track1[12] = {
    { 4, 10, { 0, 0 }, 81920, 57856, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 9, 150, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 4, 419, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 27, 451, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 34, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 34, 669, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 30, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 970, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 4, 1129, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 36, 1150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent102Track2[7] = {
    { 112, 10, { 0, 0 }, 90368, 57856, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 119, 150, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 114, 739, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 126, 741, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 970, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 1120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 114, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent102Track3[15] = {
    { 144, 10, { 0, 0 }, 77824, 64000, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 151, 150, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 146, 530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 142, 535, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 539, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 165, 543, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 142, 555, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 970, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 1120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 146, 1140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 142, 1145, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 1159, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 165, 1161, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent102Track4[8] = {
    { 231, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 231, 151, { 0, 0 }, 49152, 40960, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 234, 180, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, EventCharaHop, NULL },
    { 231, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 229, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 229, 770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 231, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 231, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent102Tracks[5] = {
    { sEvent102Track0, 38, { 0, 0, 0 } },
    { sEvent102Track1, 0, { 0, 0, 0 } },
    { sEvent102Track2, 1, { 0, 0, 0 } },
    { sEvent102Track3, 2, { 0, 0, 0 } },
    { sEvent102Track4, 8, { 0, 0, 0 } },
};

const EventSequenceDef gEvent102 = {
    5,
    { 0, 0, 0 },
    sEvent102Tracks,
    sEvent102Camera,
    sEvent102Script,
    sEvent102SoundCues,
    NULL,
    1250,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_103_text.inc"
static const MessageScriptEntry sEvent103Script[30] = {
    { 0, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F98DCC, 0, 140 },
    { 13, 4, 1, 1, { 0, 0, 0 }, gEventTextUs_08F98DE8, 0, 300 },
    { 13, 5, 4, 1, { 0, 0, 0 }, gEventTextUs_08F98E68, 0, 302 },
    { 1, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F98ECC, 0, 320 },
    { 2, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F98EF0, 0, 340 },
    { 14, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F98F2C, MSG_SCRIPT_FLAG_SILHOUETTE, 380 },
    { 14, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F98F90, 0, 560 },
    { 14, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F99022, 0, 580 },
    { 14, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F9908E, 0, 582 },
    { 13, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F99150, 0, 600 },
    { 14, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F99158, 0, 640 },
    { 14, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08F99202, 0, 642 },
    { 13, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08F99280, 0, 700 },
    { 13, 5, 1, 1, { 0, 0, 0 }, gEventTextUs_08F992E2, 0, 740 },
    { 14, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F9931E, 0, 910 },
    { 14, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9935C, 0, 1020 },
    { 14, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08F99404, 0, 1022 },
    { 13, 5, 3, 1, { 0, 0, 0 }, gEventTextUs_08F99476, 0, 1320 },
    { 0, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F994A4, 0, 1340 },
    { 13, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08F994EE, 0, 1510 },
    { 0, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F99532, 0, 1530 },
    { 1, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F99554, 0, 1550 },
    { 1, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08F995D0, 0, 1552 },
    { 13, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08F99640, 0, 1570 },
    { 13, 4, 4, 1, { 0, 0, 0 }, gEventTextUs_08F99666, 0, 1572 },
    { 13, 4, 4, 1, { 0, 0, 0 }, gEventTextUs_08F996D4, 0, 1574 },
    { 0, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9971C, 0, 1600 },
    { 0, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9973A, 0, 1700 },
    { 13, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08F997C2, 0, 1720 },
    { 0, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08F997FC, MSG_SCRIPT_FLAG_END, 1740 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent103Script[30] = {
    { 0, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F88DB4, 0, 140 },
    { 13, 4, 1, 3, { 0, 0, 0 }, gEventTextJp_08F88D80, 0, 300 },
    { 13, 5, 4, 3, { 0, 0, 0 }, gEventTextJp_08F88D58, 0, 302 },
    { 1, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F88D3C, 0, 320 },
    { 2, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F88D1C, 0, 340 },
    { 14, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F88CDC, MSG_SCRIPT_FLAG_SILHOUETTE, 380 },
    { 14, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F88C94, 0, 560 },
    { 14, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F88C58, 0, 580 },
    { 14, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F88C08, 0, 582 },
    { 13, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F88BFC, 0, 600 },
    { 14, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F88BA8, 0, 640 },
    { 14, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F88B64, 0, 642 },
    { 13, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08F88B20, 0, 700 },
    { 13, 5, 1, 3, { 0, 0, 0 }, gEventTextJp_08F88B08, 0, 740 },
    { 14, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F88AEC, 0, 910 },
    { 14, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F88A94, 0, 1020 },
    { 14, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F88A64, 0, 1022 },
    { 13, 5, 3, 3, { 0, 0, 0 }, gEventTextJp_08F88A54, 0, 1320 },
    { 0, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F88A3C, 0, 1340 },
    { 13, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F88A20, 0, 1510 },
    { 0, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F88A0C, 0, 1530 },
    { 1, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F889DC, 0, 1550 },
    { 1, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F88994, 0, 1552 },
    { 13, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F88978, 0, 1570 },
    { 13, 4, 4, 3, { 0, 0, 0 }, gEventTextJp_08F88934, 0, 1572 },
    { 13, 4, 4, 3, { 0, 0, 0 }, gEventTextJp_08F88908, 0, 1574 },
    { 0, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08F888F0, 0, 1600 },
    { 0, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F888A8, 0, 1700 },
    { 13, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F88894, 0, 1720 },
    { 0, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8885C, MSG_SCRIPT_FLAG_END, 1740 },
};

#include "event_103_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent103Script[30] = {
    { 0, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E4D0, 0, 140 },
    { 13, 4, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E4E4, 0, 300 },
    { 13, 5, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5E4F8, 0, 302 },
    { 1, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E50C, 0, 320 },
    { 2, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E520, 0, 340 },
    { 14, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E534, MSG_SCRIPT_FLAG_SILHOUETTE, 380 },
    { 14, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E548, 0, 560 },
    { 14, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E55C, 0, 580 },
    { 14, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5E570, 0, 582 },
    { 13, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E584, 0, 600 },
    { 14, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E598, 0, 640 },
    { 14, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5E5AC, 0, 642 },
    { 13, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E5C0, 0, 700 },
    { 13, 5, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E5D4, 0, 740 },
    { 14, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E5E8, 0, 910 },
    { 14, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E5FC, 0, 1020 },
    { 14, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5E610, 0, 1022 },
    { 13, 5, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E624, 0, 1320 },
    { 0, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E638, 0, 1340 },
    { 13, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E64C, 0, 1510 },
    { 0, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E660, 0, 1530 },
    { 1, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E674, 0, 1550 },
    { 1, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5E688, 0, 1552 },
    { 13, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E69C, 0, 1570 },
    { 13, 4, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5E6B0, 0, 1572 },
    { 13, 4, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5E6C4, 0, 1574 },
    { 0, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E6D8, 0, 1600 },
    { 0, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E6EC, 0, 1700 },
    { 13, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E700, 0, 1720 },
    { 0, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E714, MSG_SCRIPT_FLAG_END, 1740 },
};
#endif

static const EventCameraKeyframe sEvent103Camera[3] = {
    { -65376, 39168, 61952, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64186, 83200, 45824, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -55537, 69632, 47616, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent103SoundCues[7] = {
    { 65535, 0, 0, 0 },
    { SONG_BGM_EVENT_SILENCE, 300, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT_SILENCE, 370, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT_UNREST, 381, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT_UNREST, 1100, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_UNDERTHESEA, 1700, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_UNDERTHESEA, 1845, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent103Track0[21] = {
    { 316, 381, { 0, 0 }, 73984, 45056, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 316, 410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 316, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 314, 430, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 314, 599, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 324, 601, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 314, 710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 314, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 316, 1150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 314, 1160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 314, 1170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 314, 1310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 314, 1350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 314, 1360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 322, 1509, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 323, 1511, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 314, 1610, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 314, 1690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateQuestionTask },
    { 314, 1719, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 322, 1721, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 314, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent103Track1[7] = {
    { 4, 1, { 0, 0 }, 20992, 71680, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 9, 60, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 4, 1350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 9, 1490, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 4, 1529, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 36, 1531, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent103Track2[8] = {
    { 114, 1, { 0, 0 }, 24832, 76288, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 119, 60, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 114, 1350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 119, 1490, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 114, 1549, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 127, 1553, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 129, 1560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent103Track3[5] = {
    { 146, 1, { 0, 0 }, 14592, 71680, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 151, 60, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 146, 1350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 151, 1490, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 146, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent103Track4[14] = {
    { 354, 390, { 0, 0 }, 129792, 74496, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 358, 467, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 354, 478, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 358, 540, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 358, 750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 358, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 358, 920, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 354, 930, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 353, 950, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 357, 1010, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 357, 1040, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 353, 1041, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 357, 1410, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 353, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent103Tracks[5] = {
    { sEvent103Track0, 15, { 0, 0, 0 } },
    { sEvent103Track1, 0, { 0, 0, 0 } },
    { sEvent103Track2, 1, { 0, 0, 0 } },
    { sEvent103Track3, 2, { 0, 0, 0 } },
    { sEvent103Track4, 20, { 0, 0, 0 } },
};

const EventSequenceDef gEvent103 = {
    5,
    { 0, 0, 0 },
    sEvent103Tracks,
    sEvent103Camera,
    sEvent103Script,
    sEvent103SoundCues,
    NULL,
    1850,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_104_text.inc"
static const MessageScriptEntry sEvent104Script[16] = {
    { 14, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9A410, 0, 180 },
    { 14, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08F9A438, 0, 182 },
    { 13, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F9A482, 0, 200 },
    { 13, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08F9A504, 0, 202 },
    { 14, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9A59C, 0, 240 },
    { 22, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9A5C6, 0, 370 },
    { 1, 4, 0, 1, { 0, 0, 0 }, gEventTextUs_08F9A5D4, 0, 390 },
    { 14, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9A60C, 0, 410 },
    { 14, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9A6B0, 0, 680 },
    { 14, 2, 4, 1, { 0, 0, 0 }, gEventTextUs_08F9A6DC, 0, 682 },
    { 13, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F9A71A, 0, 700 },
    { 14, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9A73C, 0, 730 },
    { 14, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9A786, 0, 900 },
    { 14, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08F9A7AA, 0, 902 },
    { 14, 2, 4, 1, { 0, 0, 0 }, gEventTextUs_08F9A810, 0, 904 },
    { 14, 2, 4, 1, { 0, 0, 0 }, gEventTextUs_08F9A874, MSG_SCRIPT_FLAG_END, 906 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent104Script[16] = {
    { 14, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F89A5C, 0, 180 },
    { 14, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F89A1C, 0, 182 },
    { 13, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F899F4, 0, 200 },
    { 13, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F8999C, 0, 202 },
    { 14, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F89984, 0, 240 },
    { 22, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F89978, 0, 370 },
    { 1, 4, 0, 3, { 0, 0, 0 }, gEventTextJp_08F89954, 0, 390 },
    { 14, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8990C, 0, 410 },
    { 14, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F898EC, 0, 680 },
    { 14, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08F898D0, 0, 682 },
    { 13, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F898B0, 0, 700 },
    { 14, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F89888, 0, 730 },
    { 14, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F89870, 0, 900 },
    { 14, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F89840, 0, 902 },
    { 14, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08F89824, 0, 904 },
    { 14, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08F897E8, MSG_SCRIPT_FLAG_END, 906 },
};

#include "event_104_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent104Script[16] = {
    { 14, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E8CC, 0, 180 },
    { 14, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5E8E0, 0, 182 },
    { 13, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E8F4, 0, 200 },
    { 13, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5E908, 0, 202 },
    { 14, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E91C, 0, 240 },
    { 22, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E930, 0, 370 },
    { 1, 4, 0, 1, { 0, 0, 0 }, &gUnkEu_09F5E944, 0, 390 },
    { 14, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E958, 0, 410 },
    { 14, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E96C, 0, 680 },
    { 14, 2, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5E980, 0, 682 },
    { 13, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E994, 0, 700 },
    { 14, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E9A8, 0, 730 },
    { 14, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E9BC, 0, 900 },
    { 14, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5E9D0, 0, 902 },
    { 14, 2, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5E9E4, 0, 904 },
    { 14, 2, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5E9F8, MSG_SCRIPT_FLAG_END, 906 },
};
#endif

static const EventCameraKeyframe sEvent104Camera[3] = {
    { -64626, 45312, 35328, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64556, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_MEDIUM | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64486, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_KEYFRAME_FLAG_SHAKE_MEDIUM | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 20, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent104SoundCues[7] = {
    { SONG_BGM_EVENT_UNREST, 0, 0, 0 },
    { SONG_SND_346, 300, 0, 0 },
    { SONG_SND_350, 590, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 902, 0, 0 },
    { SONG_BGM_EVENT2, 904, 0, 0 },
    { SONG_EV_RUMBLE, 910, 0, 0 },
    { SONG_EV_RUMBLE, 945, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent104Track1[6] = {
    { 4, 1, { 0, 0 }, 81920, 61696, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 14, 80, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 4, 83, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 4, 305, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 4, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent104Track2[6] = {
    { 114, 1, { 0, 0 }, 85760, 68864, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 120, 100, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 114, 103, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 114, 389, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 131, 391, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateSmokeTask },
    { 114, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent104Track3[4] = {
    { 146, 1, { 0, 0 }, 97536, 61184, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 153, 125, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 146, 128, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 146, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent104Track0[15] = {
    { 316, 1, { 0, 0 }, 86272, 60416, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 321, 80, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 317, 83, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 316, 305, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 316, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 316, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 316, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 316, 575, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 316, 635, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 316, 660, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 4, NULL, NULL },
    { 316, 699, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 326, 701, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 316, 825, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 316, 890, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 316, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent104Track4[14] = {
    { 354, 140, { 0, 0 }, 36096, 35840, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 353, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 353, 241, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 359, 340, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 357, 360, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 68, NULL, NULL },
    { 357, 391, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 353, 392, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 357, 409, { 0, 0 }, 39936, 37120, 0, 353, { 0, 0 }, 4163, NULL, NULL },
    { 357, 672, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 355, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 356, 722, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 355, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 353, 906, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 360, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent104Track5[9] = {
    { 464, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 464, 391, { 0, 0 }, 24576, 37376, -2560, 0, { 0, 0 }, 66, EventCharaFadeIn, NULL },
    { 464, 409, { 0, 0 }, 35840, 35072, -2560, 464, { 0, 0 }, 67, NULL, NULL },
    { 464, 740, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 465, 770, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 466, 825, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 100, NULL, NULL },
    { 466, 840, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 36, NULL, NULL },
    { 464, 890, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 465, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent104Track6[3] = {
    { 590, 590, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 590, 635, { 0, 0 }, 36608, 31744, 0, 0, { 0, 0 }, 16658, NULL, NULL },
    { 590, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaTrack sEvent104Tracks[7] = {
    { sEvent104Track0, 15, { 0, 0, 0 } },
    { sEvent104Track1, 0, { 0, 0, 0 } },
    { sEvent104Track2, 1, { 0, 0, 0 } },
    { sEvent104Track3, 2, { 0, 0, 0 } },
    { sEvent104Track4, 20, { 0, 0, 0 } },
    { sEvent104Track5, 39, { 0, 0, 0 } },
    { sEvent104Track6, 49, { 0, 0, 0 } },
};

const EventSequenceDef gEvent104 = {
    7,
    { 0, 0, 0 },
    sEvent104Tracks,
    sEvent104Camera,
    sEvent104Script,
    sEvent104SoundCues,
    NULL,
    1100,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    105,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_105_text.inc"
static const MessageScriptEntry sEvent105Script[1] = {
    { 14, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08F9B350, MSG_SCRIPT_FLAG_END, 100 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent105Script[1] = {
    { 14, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F8A3A4, MSG_SCRIPT_FLAG_END, 100 },
};

#include "event_105_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent105Script[1] = {
    { 14, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E728, MSG_SCRIPT_FLAG_END, 100 },
};
#endif

static const EvSoundCue sEvent105SoundCues[1] = {
    { SONG_BGM_EVENT2, 0, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent105Camera[1] = {
    { -64626, 81920, 102400, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent105Track0[1] = {
    { 21, 459, { 0, 0 }, 81920, 122880, 0, 0, { 0, 0 }, 32834, NULL, NULL },
};

static const EventCharaKeyframe sEvent105Track1[1] = {
    { 937, 459, { 0, 0 }, 45312, 60928, 0, 0, { 0, 0 }, 32770, NULL, NULL },
};

static const EventCharaTrack sEvent105Tracks[2] = {
    { sEvent105Track0, 0, { 0, 0, 0 } },
    { sEvent105Track1, 99, { 0, 0, 0 } },
};

const EventSequenceDef gEvent105 = {
    2,
    { 0, 0, 0 },
    sEvent105Tracks,
    sEvent105Camera,
    sEvent105Script,
    sEvent105SoundCues,
    NULL,
    150,
    0,
    1,
    0,
    0,
    0,
    0,
    151,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_106_text.inc"
static const MessageScriptEntry sEvent106Script[20] = {
    { 22, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9B484, 0, 150 },
    { 13, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08F9B4E2, 0, 170 },
    { 13, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F9B554, 0, 172 },
    { 0, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9B5E6, 0, 200 },
    { 13, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08F9B682, 0, 240 },
    { 23, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F9B6B8, 0, 270 },
    { 23, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F9B702, 0, 272 },
    { 13, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9B748, 0, 370 },
    { 2, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9B7B6, 0, 390 },
    { 0, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9B80E, 0, 460 },
    { 0, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08F9B88A, 0, 462 },
    { 13, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F9B92C, 0, 490 },
    { 13, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F9B960, 0, 492 },
    { 13, 4, 1, 1, { 0, 0, 0 }, gEventTextUs_08F9B98A, 0, 590 },
    { 13, 5, 4, 1, { 0, 0, 0 }, gEventTextUs_08F9BA0E, 0, 592 },
    { 13, 5, 1, 1, { 0, 0, 0 }, gEventTextUs_08F9BA70, 0, 640 },
    { 13, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F9BABC, 0, 642 },
    { 13, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08F9BB64, 0, 680 },
    { 6, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9BC1A, 0, 870 },
    { 0, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9BC78, MSG_SCRIPT_FLAG_END, 910 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent106Script[20] = {
    { 22, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8AAE8, 0, 150 },
    { 13, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F8AAB8, 0, 170 },
    { 13, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F8AA60, 0, 172 },
    { 0, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8AA18, 0, 200 },
    { 13, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F8A9E8, 0, 240 },
    { 23, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F8A9BC, 0, 270 },
    { 23, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F8A994, 0, 272 },
    { 13, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8A958, 0, 370 },
    { 2, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8A934, 0, 390 },
    { 0, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8A8E4, 0, 460 },
    { 0, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F8A898, 0, 462 },
    { 13, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F8A87C, 0, 490 },
    { 13, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F8A864, 0, 492 },
    { 13, 4, 1, 3, { 0, 0, 0 }, gEventTextJp_08F8A828, 0, 590 },
    { 13, 5, 4, 3, { 0, 0, 0 }, gEventTextJp_08F8A7D4, 0, 592 },
    { 13, 5, 1, 3, { 0, 0, 0 }, gEventTextJp_08F8A784, 0, 640 },
    { 13, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F8A73C, 0, 642 },
    { 13, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F8A6E8, 0, 680 },
    { 6, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8A6B8, 0, 870 },
    { 0, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8A674, MSG_SCRIPT_FLAG_END, 910 },
};

#include "event_106_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent106Script[20] = {
    { 22, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E73C, 0, 150 },
    { 13, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E750, 0, 170 },
    { 13, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5E764, 0, 172 },
    { 0, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E778, 0, 200 },
    { 13, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E78C, 0, 240 },
    { 23, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E7A0, 0, 270 },
    { 23, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5E7B4, 0, 272 },
    { 13, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E7C8, 0, 370 },
    { 2, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E7DC, 0, 390 },
    { 0, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E7F0, 0, 460 },
    { 0, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5E804, 0, 462 },
    { 13, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E818, 0, 490 },
    { 13, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5E82C, 0, 492 },
    { 13, 4, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E840, 0, 590 },
    { 13, 5, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5E854, 0, 592 },
    { 13, 5, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E868, 0, 640 },
    { 13, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5E87C, 0, 642 },
    { 13, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E890, 0, 680 },
    { 6, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E8A4, 0, 870 },
    { 0, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E8B8, MSG_SCRIPT_FLAG_END, 910 },
};
#endif

static const EventCameraKeyframe sEvent106Camera[1] = {
    { -64626, 45056, 38144, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent106SoundCues[2] = {
    { SONG_BGM_EVENT4, 0, 0, 0 },
    { SONG_BGM_EVENT4, 965, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent106Track0[6] = {
    { 464, 210, { 0, 0 }, 44288, 40192, -2560, 0, { 0, 0 }, 66, NULL, NULL },
    { 464, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 464, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 464, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 464, 470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 464, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent106Track1[10] = {
    { 316, 210, { 0, 0 }, 48896, 43008, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 314, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 314, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 314, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 314, 369, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 322, 371, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 314, 470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 314, 610, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 316, 660, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 314, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent106Track2[8] = {
    { 4, 459, { 0, 0 }, 36608, 45312, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 30, 463, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateQuestionTask },
    { 4, 710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 4, 905, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 36, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent106Track3[1] = {
    { 112, 999, { 0, 0 }, 54784, 34560, 0, 0, { 0, 0 }, 32770, NULL, NULL },
};

static const EventCharaKeyframe sEvent106Track4[3] = {
    { 144, 389, { 0, 0 }, 36096, 35072, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 164, 391, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent106Track5[4] = {
    { 231, 620, { 0, 0 }, 32256, 41984, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 229, 860, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 233, 872, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaHop, NULL },
    { 229, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent106Tracks[6] = {
    { sEvent106Track0, 39, { 0, 0, 0 } },
    { sEvent106Track1, 15, { 0, 0, 0 } },
    { sEvent106Track2, 0, { 0, 0, 0 } },
    { sEvent106Track3, 1, { 0, 0, 0 } },
    { sEvent106Track4, 2, { 0, 0, 0 } },
    { sEvent106Track5, 8, { 0, 0, 0 } },
};

const EventSequenceDef gEvent106 = {
    6,
    { 0, 0, 0 },
    sEvent106Tracks,
    sEvent106Camera,
    sEvent106Script,
    sEvent106SoundCues,
    NULL,
    970,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_107_text.inc"
static const MessageScriptEntry sEvent107Script[4] = {
    { 2, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08F9C3E4, 0, 190 },
    { 1, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9C428, 0, 350 },
    { 0, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9C45C, 0, 550 },
    { 15, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9C4A4, MSG_SCRIPT_FLAG_END, 570 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent107Script[4] = {
    { 2, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F8B0E8, 0, 190 },
    { 1, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8B0D4, 0, 350 },
    { 0, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8B0C4, 0, 550 },
    { 15, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8B0A0, MSG_SCRIPT_FLAG_END, 570 },
};

#include "event_107_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent107Script[4] = {
    { 2, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5D968, 0, 190 },
    { 1, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5D97C, 0, 350 },
    { 0, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5D990, 0, 550 },
    { 15, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5D9A4, MSG_SCRIPT_FLAG_END, 570 },
};
#endif

static const EventCameraKeyframe sEvent107Camera[4] = {
    { -65536, 33024, 87296, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, NULL },
    { -65455, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 80, { 0, 0 }, NULL },
    { -65286, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -55537, 87040, 60160, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent107SoundCues[1] = {
    { SONG_BGM_ALADDIN_FIELD, 0, EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent107Track0[1] = {
    { 278, 9999, { 0, 0 }, 89600, 61696, 0, 0, { 0, 0 }, 32834, NULL, NULL },
};

static const EventCharaKeyframe sEvent107Track1[20] = {
    { 146, 1, { 0, 0 }, 15360, 98816, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 151, 90, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 146, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 146, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 165, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 143, 175, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 189, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 164, 191, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 143, 205, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 215, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 153, 520, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 146, 523, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 146, 530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 157, 540, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 158, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent107Track2[9] = {
    { 4, 1, { 0, 0 }, 8192, 107520, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 9, 90, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 4, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 4, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 14, 510, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 4, 513, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 4, 520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 19, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent107Track3[10] = {
    { 114, 1, { 0, 0 }, 0, 102400, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 119, 90, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 114, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 114, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 120, 510, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 114, 513, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 114, 520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 122, 530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 123, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent107Track4[2] = {
    { 475, 10, { 0, 0 }, 77824, 55296, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 472, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33093, NULL, NULL },
};

static const EventCharaKeyframe sEvent107Track5[2] = {
    { 475, 30, { 0, 0 }, 90112, 52992, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 472, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33029, NULL, NULL },
};

static const EventCharaKeyframe sEvent107Track6[2] = {
    { 475, 60, { 0, 0 }, 98304, 54016, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 472, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33029, NULL, NULL },
};

static const EventCharaKeyframe sEvent107Track7[2] = {
    { 475, 90, { 0, 0 }, 106752, 58368, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 472, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33029, NULL, NULL },
};

static const EventCharaKeyframe sEvent107Track8[2] = {
    { 475, 120, { 0, 0 }, 100608, 65024, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 473, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33029, NULL, NULL },
};

static const EventCharaTrack sEvent107Tracks[9] = {
    { sEvent107Track0, 12, { 0, 0, 0 } },
    { sEvent107Track1, 2, { 0, 0, 0 } },
    { sEvent107Track2, 0, { 0, 0, 0 } },
    { sEvent107Track3, 1, { 0, 0, 0 } },
    { sEvent107Track4, 40, { 0, 0, 0 } },
    { sEvent107Track5, 40, { 0, 0, 0 } },
    { sEvent107Track6, 40, { 0, 0, 0 } },
    { sEvent107Track7, 40, { 0, 0, 0 } },
    { sEvent107Track8, 40, { 0, 0, 0 } },
};

const EventSequenceDef gEvent107 = {
    9,
    { 0, 0, 0 },
    sEvent107Tracks,
    sEvent107Camera,
    sEvent107Script,
    sEvent107SoundCues,
    NULL,
    620,
    0,
    1,
    0,
    0,
    0,
    0,
    123,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_108_text.inc"
static const MessageScriptEntry sEvent108Script[16] = {
    { 1, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9CD50, 0, 240 },
    { 15, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9CD7E, 0, 270 },
    { 15, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9CDDC, 0, 350 },
    { 15, 2, 4, 1, { 0, 0, 0 }, gEventTextUs_08F9CE12, 0, 352 },
    { 21, 3, 1, 0, { 0, 0, 0 }, gEventTextUs_08F9CE4A, 0, 525 },
    { 21, 3, 4, 0, { 0, 0, 0 }, gEventTextUs_08F9CF76, 0, 527 },
    { 2, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9D004, 0, 750 },
    { 1, 3, 2, 1, { 0, 0, 0 }, gEventTextUs_08F9D014, 0, 770 },
    { 15, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F9D06C, 0, 800 },
    { 21, 0, 1, 0, { 0, 0, 0 }, gEventTextUs_08F9D0AA, 0, 840 },
    { 21, 3, 4, 0, { 0, 0, 0 }, gEventTextUs_08F9D120, 0, 842 },
    { 0, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F9D1C8, 0, 920 },
    { 15, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9D23E, 0, 940 },
    { 2, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9D2D4, 0, 970 },
    { 0, 4, 1, 1, { 0, 0, 0 }, gEventTextUs_08F9D364, 0, 1000 },
    { 15, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9D38C, MSG_SCRIPT_FLAG_END, 1020 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent108Script[17] = {
    { 1, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8BE10, 0, 240 },
    { 15, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8BDEC, 0, 270 },
    { 15, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8BDC4, 0, 350 },
    { 15, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08F8BDA4, 0, 352 },
    { 21, 3, 1, 1, { 0, 0, 0 }, gEventTextJp_08F8BD48, 0, 525 },
    { 21, 3, 4, 1, { 0, 0, 0 }, gEventTextJp_08F8BCF4, 0, 527 },
    { 2, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8BCE8, 0, 750 },
    { 1, 3, 2, 3, { 0, 0, 0 }, gEventTextJp_08F8BCAC, 0, 770 },
    { 15, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F8BC88, 0, 800 },
    { 21, 0, 1, 1, { 0, 0, 0 }, gEventTextJp_08F8BC30, 0, 840 },
    { 21, 3, 4, 1, { 0, 0, 0 }, gEventTextJp_08F8BC10, 0, 842 },
    { 21, 3, 4, 1, { 0, 0, 0 }, gEventTextJp_08F8BBC8, 0, 844 },
    { 0, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F8BB98, 0, 920 },
    { 15, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8BB3C, 0, 940 },
    { 2, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8BAEC, 0, 970 },
    { 0, 4, 1, 3, { 0, 0, 0 }, gEventTextJp_08F8BAD4, 0, 1000 },
    { 15, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8BAB0, MSG_SCRIPT_FLAG_END, 1020 },
};

#include "event_108_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent108Script[16] = {
    { 1, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5D828, 0, 240 },
    { 15, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5D83C, 0, 270 },
    { 15, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5D850, 0, 350 },
    { 15, 2, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5D864, 0, 352 },
    { 21, 3, 1, 0, { 0, 0, 0 }, &gUnkEu_09F5D878, 0, 525 },
    { 21, 3, 4, 0, { 0, 0, 0 }, &gUnkEu_09F5D88C, 0, 527 },
    { 2, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5D8A0, 0, 750 },
    { 1, 3, 2, 1, { 0, 0, 0 }, &gUnkEu_09F5D8B4, 0, 770 },
    { 15, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5D8C8, 0, 800 },
    { 21, 0, 1, 0, { 0, 0, 0 }, &gUnkEu_09F5D8DC, 0, 840 },
    { 21, 3, 4, 0, { 0, 0, 0 }, &gUnkEu_09F5D8F0, 0, 842 },
    { 0, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5D904, 0, 920 },
    { 15, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5D918, 0, 940 },
    { 2, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5D92C, 0, 970 },
    { 0, 4, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5D940, 0, 1000 },
    { 15, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5D954, MSG_SCRIPT_FLAG_END, 1020 },
};
#endif

static const EventCameraKeyframe sEvent108Camera[8] = {
    { -65181, 93184, 56064, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65081, 96000, 40960, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 20, { 0, 0 }, NULL },
    { -64996, 96000, 20736, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 30, { 0, 0 }, NULL },
    { -64796, 91136, 46080, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 40, { 0, 0 }, NULL },
    { -64726, 83712, 53504, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -64686, 88832, 53504, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 40, { 0, 0 }, NULL },
    { -64676, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -55537, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent108SoundCues[5] = {
    { SONG_BGM_ALADDIN_BATTLE, 0, 0, 0 },
    { SONG_BGM_ALADDIN_BATTLE, 410, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_VO_GE_EVENT00, 480, 0, 0 },
    { SONG_BGM_ALADDIN_FIELD, 750, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_ALADDIN_FIELD, 1115, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventBgEffectEntry sEvent108BgEffects[3] = {
    { 381, 0, 0, 0, 0 },
    { 500, 0, 0, 0, 0x4 },
    { 701, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent108Track9[3] = {
    { 743, 410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 743, 460, { 0, 0 }, 94720, 49664, -7680, 0, { 0, 0 }, 16658, NULL, NULL },
    { 743, 470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent108Track10[3] = {
    { 744, 865, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 744, 930, { 0, 0 }, 89088, 60160, -7680, 0, { 0, 0 }, 16658, NULL, NULL },
    { 744, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent108Track0[16] = {
    { 664, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8258, NULL, NULL },
    { 668, 460, { 0, 0 }, 94720, 47104, -7680, 0, { 0, 0 }, 16706, NULL, NULL },
    { 668, 490, { 0, 0 }, 94720, 47104, -23040, 664, { 0, 0 }, 4419, NULL, NULL },
    { 668, 523, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 262469, NULL, NULL },
    { 664, 530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 262405, NULL, NULL },
    { 666, 560, { 0, 0 }, 71168, 58112, -2560, 664, { 0, 0 }, 262147, NULL, NULL },
    { 664, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 262149, NULL, NULL },
    { 664, 580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 262213, NULL, NULL },
    { 670, 750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 664, 810, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 262213, NULL, NULL },
    { 664, 820, { 0, 0 }, 82944, 58368, -2560, 664, { 0, 0 }, 67, NULL, NULL },
    { 664, 830, { 0, 0 }, 91648, 60160, -2560, 664, { 0, 0 }, 67, NULL, NULL },
    { 664, 840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 262149, NULL, NULL },
    { 669, 850, { 0, 0 }, 91648, 60160, 0, 0, { 0, 0 }, 262146, NULL, NULL },
    { 664, 851, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 65602, NULL, NULL },
    { 664, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent108Track1[20] = {
    { 278, 160, { 0, 0 }, 88576, 58112, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 278, 260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 278, 272, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 282, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 270, 290, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 276, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 270, 540, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 270, 580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 282, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 286, 752, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 282, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 270, 790, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 270, 799, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 270, 801, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 270, 930, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 270, 950, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 270, 1010, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 270, 1050, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 282, 1060, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 283, 9999, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 32836, NULL, NULL },
};

static const EventCharaKeyframe sEvent108Track3[21] = {
    { 21, 160, { 0, 0 }, 95744, 64768, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 21, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 21, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 22, 290, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 0, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 585, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 0, 590, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 27, 760, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 0, 785, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 850, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 4, 919, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 34, 921, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 980, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 16, 995, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1050, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 0, 1055, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1060, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 9, 9999, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 32836, NULL, NULL },
};

static const EventCharaKeyframe sEvent108Track2[18] = {
    { 158, 160, { 0, 0 }, 77824, 64256, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 158, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 158, 285, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 159, 295, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 142, 555, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 590, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 142, 595, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 161, 760, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 850, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 146, 950, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 969, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 167, 971, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 1065, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 1070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 151, 9999, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 32836, NULL, NULL },
};

static const EventCharaKeyframe sEvent108Track4[18] = {
    { 123, 160, { 0, 0 }, 86272, 68096, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 123, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 123, 290, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 124, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 540, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 110, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 585, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 110, 590, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 133, 760, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 769, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 126, 771, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 110, 850, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 110, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 110, 1060, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 1065, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 119, 9999, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 32836, NULL, NULL },
};

static const EventCharaKeyframe sEvent108Track5[6] = {
    { 472, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8450, NULL, NULL },
    { 475, 170, { 0, 0 }, 96000, 45056, 0, 0, { 0, 0 }, 16642, NULL, NULL },
    { 472, 670, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 478, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 472, 691, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 472, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98565, NULL, NULL },
};

static const EventCharaKeyframe sEvent108Track6[6] = {
    { 472, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8450, NULL, NULL },
    { 475, 180, { 0, 0 }, 105728, 51456, 0, 0, { 0, 0 }, 16642, NULL, NULL },
    { 472, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 478, 710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 472, 711, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 472, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98565, NULL, NULL },
};

static const EventCharaKeyframe sEvent108Track7[6] = {
    { 472, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8450, NULL, NULL },
    { 475, 190, { 0, 0 }, 118272, 48384, 0, 0, { 0, 0 }, 16642, NULL, NULL },
    { 472, 710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 478, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 472, 731, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 472, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98565, NULL, NULL },
};

static const EventCharaKeyframe sEvent108Track8[6] = {
    { 472, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8450, NULL, NULL },
    { 475, 200, { 0, 0 }, 108288, 43008, 0, 0, { 0, 0 }, 16642, NULL, NULL },
    { 472, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 478, 750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 472, 751, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 472, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98565, NULL, NULL },
};

static const EventCharaTrack sEvent108Tracks[11] = {
    { sEvent108Track0, 59, { 0, 0, 0 } },
    { sEvent108Track1, 12, { 0, 0, 0 } },
    { sEvent108Track2, 2, { 0, 0, 0 } },
    { sEvent108Track3, 0, { 0, 0, 0 } },
    { sEvent108Track4, 1, { 0, 0, 0 } },
    { sEvent108Track5, 40, { 0, 0, 0 } },
    { sEvent108Track6, 40, { 0, 0, 0 } },
    { sEvent108Track7, 40, { 0, 0, 0 } },
    { sEvent108Track8, 40, { 0, 0, 0 } },
    { sEvent108Track9, 68, { 0, 0, 0 } },
    { sEvent108Track10, 68, { 0, 0, 0 } },
};

const EventSequenceDef gEvent108 = {
    11,
    { 0, 0, 0 },
    sEvent108Tracks,
    sEvent108Camera,
    sEvent108Script,
    sEvent108SoundCues,
    sEvent108BgEffects,
    1120,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    1,
    255,
    255,
};

#ifdef VERSION_US
#include "event_109_text.inc"
static const MessageScriptEntry sEvent109Script[22] = {
    { 2, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9E88C, 0, 250 },
    { 15, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F9E8F0, 0, 280 },
    { 15, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F9E9B2, 0, 282 },
    { 0, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08F9EA64, 0, 300 },
    { 21, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9EAC4, 0, 320 },
    { 21, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F9EAFE, 0, 322 },
    { 21, 4, 4, 1, { 0, 0, 0 }, gEventTextUs_08F9EB8E, 0, 324 },
    { 15, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F9EC3A, 0, 360 },
    { 21, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9ECA6, 0, 430 },
    { 15, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F9ED86, 0, 450 },
    { 15, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F9EDAA, 0, 452 },
    { 21, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9EE06, 0, 480 },
    { 21, 3, 4, 1, { 0, 0, 0 }, gEventTextUs_08F9EE96, 0, 482 },
    { 15, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08F9EF3C, 0, 630 },
    { 15, 3, 4, 1, { 0, 0, 0 }, gEventTextUs_08F9EFD0, 0, 632 },
    { 15, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08F9F070, 0, 634 },
    { 0, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08F9F124, 0, 650 },
    { 21, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9F1C4, 0, 670 },
    { 21, 3, 4, 1, { 0, 0, 0 }, gEventTextUs_08F9F27E, 0, 672 },
    { 15, 4, 1, 1, { 0, 0, 0 }, gEventTextUs_08F9F2E8, 0, 690 },
    { 21, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9F334, 0, 710 },
    { 15, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08F9F360, MSG_SCRIPT_FLAG_END, 740 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent109Script[22] = {
    { 2, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8D8BC, 0, 250 },
    { 15, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F8D864, 0, 280 },
    { 15, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F8D818, 0, 282 },
    { 0, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F8D7C8, 0, 300 },
    { 21, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8D790, 0, 320 },
    { 21, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F8D740, 0, 322 },
    { 21, 4, 4, 3, { 0, 0, 0 }, gEventTextJp_08F8D6F0, 0, 324 },
    { 15, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F8D6BC, 0, 360 },
    { 21, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8D684, 0, 430 },
    { 15, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F8D650, 0, 450 },
    { 15, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F8D618, 0, 452 },
    { 21, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8D5C4, 0, 480 },
    { 21, 3, 4, 3, { 0, 0, 0 }, gEventTextJp_08F8D594, 0, 482 },
    { 15, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F8D550, 0, 630 },
    { 15, 3, 4, 3, { 0, 0, 0 }, gEventTextJp_08F8D50C, 0, 632 },
    { 15, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F8D4B8, 0, 634 },
    { 0, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F8D464, 0, 650 },
    { 21, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8D410, 0, 670 },
    { 21, 3, 4, 3, { 0, 0, 0 }, gEventTextJp_08F8D3D8, 0, 672 },
    { 15, 4, 1, 3, { 0, 0, 0 }, gEventTextJp_08F8D3B4, 0, 690 },
    { 21, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8D398, 0, 710 },
    { 15, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8D35C, MSG_SCRIPT_FLAG_END, 740 },
};

#include "event_109_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent109Script[22] = {
    { 2, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5D9B8, 0, 250 },
    { 15, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5D9CC, 0, 280 },
    { 15, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5D9E0, 0, 282 },
    { 0, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5D9F4, 0, 300 },
    { 21, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DA08, 0, 320 },
    { 21, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5DA1C, 0, 322 },
    { 21, 4, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5DA30, 0, 324 },
    { 15, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5DA44, 0, 360 },
    { 21, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DA58, 0, 430 },
    { 15, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5DA6C, 0, 450 },
    { 15, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5DA80, 0, 452 },
    { 21, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DA94, 0, 480 },
    { 21, 3, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5DAA8, 0, 482 },
    { 15, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5DABC, 0, 630 },
    { 15, 3, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5DAD0, 0, 632 },
    { 15, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5DAE4, 0, 634 },
    { 0, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5DAF8, 0, 650 },
    { 21, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DB0C, 0, 670 },
    { 21, 3, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5DB20, 0, 672 },
    { 15, 4, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5DB34, 0, 690 },
    { 21, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DB48, 0, 710 },
    { 15, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DB5C, MSG_SCRIPT_FLAG_END, 740 },
};
#endif

static const EventCameraKeyframe sEvent109Camera[1] = {
    { -55537, 32768, 26624, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent109SoundCues[2] = {
    { SONG_BGM_ALADDIN_FIELD, 0, 0, 0 },
    { SONG_BGM_ALADDIN_FIELD, 885, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent109Track3[12] = {
    { 2, 10, { 0, 0 }, 86528, 16640, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 7, 200, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 2, 260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 265, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 299, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 30, 301, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 370, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 27, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 4, 750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 755, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 760, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 12, 9999, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 32804, NULL, NULL },
};

static const EventCharaKeyframe sEvent109Track4[13] = {
    { 112, 1, { 0, 0 }, 76032, 21248, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 117, 198, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 112, 210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 113, 215, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 110, 265, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 110, 370, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 133, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 110, 750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 755, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 113, 760, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 765, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 121, 9999, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 32804, NULL, NULL },
};

static const EventCharaKeyframe sEvent109Track2[17] = {
    { 144, 1, { 0, 0 }, 68352, 18176, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 149, 190, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 144, 210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 215, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 143, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 225, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 249, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 165, 251, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 370, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 161, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 146, 750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 142, 755, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 760, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 145, 765, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 152, 9999, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 32804, NULL, NULL },
};

static const EventCharaKeyframe sEvent109Track1[17] = {
    { 270, 10, { 0, 0 }, 77824, 12800, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 271, 200, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 270, 270, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 276, 290, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 270, 340, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 282, 370, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 287, 440, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 282, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 287, 620, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 282, 631, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 287, 633, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 282, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 286, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 270, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 270, 750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 270, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 272, 790, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 32804, NULL, NULL },
};

static const EventCharaKeyframe sEvent109Track0[14] = {
    { 664, 10, { 0, 0 }, 69376, 8704, -2560, 0, { 0, 0 }, 262146, NULL, NULL },
    { 666, 200, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 262148, NULL, NULL },
    { 664, 240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 262149, NULL, NULL },
    { 664, 319, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 262213, NULL, NULL },
    { 669, 323, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 262213, NULL, NULL },
    { 666, 326, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 664, 370, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 262213, NULL, NULL },
    { 673, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 673, 455, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 664, 481, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 262213, NULL, NULL },
    { 666, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 664, 770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 262213, NULL, NULL },
    { 664, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 262149, NULL, NULL },
    { 666, 9999, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 294948, NULL, NULL },
};

static const EventCharaTrack sEvent109Tracks[5] = {
    { sEvent109Track0, 59, { 0, 0, 0 } },
    { sEvent109Track1, 12, { 0, 0, 0 } },
    { sEvent109Track2, 2, { 0, 0, 0 } },
    { sEvent109Track3, 0, { 0, 0, 0 } },
    { sEvent109Track4, 1, { 0, 0, 0 } },
};

const EventSequenceDef gEvent109 = {
    5,
    { 0, 0, 0 },
    sEvent109Tracks,
    sEvent109Camera,
    sEvent109Script,
    sEvent109SoundCues,
    NULL,
    890,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_110_text.inc"
static const MessageScriptEntry sEvent110Script[13] = {
    { 1, 5, 2, 1, { 0, 0, 0 }, gEventTextUs_08FA00D4, 0, 100 },
    { 15, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA00FC, 0, 110 },
    { 15, 4, 2, 1, { 0, 0, 0 }, gEventTextUs_08FA0118, 0, 190 },
    { 2, 4, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA0134, 0, 350 },
    { 0, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA015C, 0, 370 },
    { 15, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA0196, 0, 380 },
    { 21, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA0210, 0, 390 },
    { 15, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA0236, 0, 900 },
    { 2, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA0248, 0, 920 },
    { 0, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA02B8, 0, 940 },
    { 15, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA0306, 0, 1120 },
    { 0, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA037C, 0, 1140 },
    { 0, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA03DA, MSG_SCRIPT_FLAG_END, 1200 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent110Script[13] = {
    { 1, 5, 2, 3, { 0, 0, 0 }, gEventTextJp_08F8E67C, 0, 100 },
    { 15, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8E66C, 0, 110 },
    { 15, 4, 2, 3, { 0, 0, 0 }, gEventTextJp_08F8E65C, 0, 190 },
    { 2, 4, 1, 3, { 0, 0, 0 }, gEventTextJp_08F8E64C, 0, 350 },
    { 0, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8E624, 0, 370 },
    { 15, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8E5E8, 0, 380 },
    { 21, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8E5D0, 0, 390 },
    { 15, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8E65C, 0, 900 },
    { 2, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8E59C, 0, 920 },
    { 0, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F8E574, 0, 940 },
    { 15, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8E548, 0, 1120 },
    { 0, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8E510, 0, 1140 },
    { 0, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8E4E8, MSG_SCRIPT_FLAG_END, 1200 },
};

#include "event_110_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent110Script[13] = {
    { 1, 5, 2, 1, { 0, 0, 0 }, &gUnkEu_09F5DDB4, 0, 100 },
    { 15, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DDC8, 0, 110 },
    { 15, 4, 2, 1, { 0, 0, 0 }, &gUnkEu_09F5DDDC, 0, 190 },
    { 2, 4, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5DDF0, 0, 350 },
    { 0, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DE04, 0, 370 },
    { 15, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DE18, 0, 380 },
    { 21, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DE2C, 0, 390 },
    { 15, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DE40, 0, 900 },
    { 2, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DE54, 0, 920 },
    { 0, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5DE68, 0, 940 },
    { 15, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DE7C, 0, 1120 },
    { 0, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DE90, 0, 1140 },
    { 0, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DEA4, MSG_SCRIPT_FLAG_END, 1200 },
};
#endif

static const EventCameraKeyframe sEvent110Camera[6] = {
    { -65406, 32256, 29696, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65276, 77824, 90368, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 40, { 0, 0 }, NULL },
    { -65056, 32256, 29696, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 40, { 0, 0 }, NULL },
    { -64816, 70912, 89600, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 40, { 0, 0 }, NULL },
    { -64536, 69632, 92672, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 60, { 0, 0 }, NULL },
    { -62536, 77312, 90112, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 30, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent110SoundCues[5] = {
    { SONG_BGM_ALADDIN_FIELD, 0, 0, 0 },
    { SONG_EV_DL_JUMP, 70, 0, 0 },
    { SONG_BGM_EVENT2, 190, 0, 0 },
    { SONG_BGM_EVENT2, 680, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT2, 1000, EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent110Track0[16] = {
    { 2, 1, { 0, 0 }, 28672, 30720, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 7, 40, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 2, 365, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 31, 375, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 701, { 0, 0 }, 45824, 124416, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 14, 800, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 4, 803, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 4, 810, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 939, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 34, 950, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1080, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 0, 1085, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 19, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent110Track1[12] = {
    { 112, 1, { 0, 0 }, 12032, 39168, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 117, 40, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 112, 70, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 112, 90, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaHopLow, CreateExclamationTask },
    { 112, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 701, { 0, 0 }, 33024, 122112, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 120, 790, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 114, 793, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 114, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 1080, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 122, 1175, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 123, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent110Track2[22] = {
    { 144, 1, { 0, 0 }, 36864, 26624, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 149, 40, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 144, 330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 143, 335, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 349, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 164, 351, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 143, 405, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 701, { 0, 0 }, 31488, 114176, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 153, 845, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 146, 848, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 146, 860, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 865, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 919, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 164, 921, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 1080, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 145, 1085, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 1160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 157, 1180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 158, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent110Track3[14] = {
    { 270, 1, { 0, 0 }, 20736, 34560, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 271, 40, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 270, 105, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 274, 260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 270, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 282, 701, { 0, 0 }, 40448, 116992, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 284, 785, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 284, 788, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 282, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 285, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 285, 1080, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 282, 1090, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 282, 1100, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 282, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent110Track4[10] = {
    { 664, 1, { 0, 0 }, 13056, 26624, -2560, 0, { 0, 0 }, 66, NULL, NULL },
    { 666, 40, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 262212, NULL, NULL },
    { 664, 391, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 262213, NULL, NULL },
    { 666, 400, { 0, 0 }, 22272, 30720, -10240, 664, { 0, 0 }, 266307, NULL, NULL },
    { 666, 450, { 0, 0 }, 60928, 54784, -7680, 664, { 0, 0 }, 266307, NULL, NULL },
    { 666, 480, { 0, 0 }, 54016, 97280, -2560, 664, { 0, 0 }, 262211, NULL, NULL },
    { 670, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 262213, NULL, NULL },
    { 664, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 262213, NULL, NULL },
    { 664, 1075, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 262213, NULL, NULL },
    { 665, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 294981, NULL, NULL },
};

static const EventCharaKeyframe sEvent110Track5[2] = {
    { 587, 480, { 0, 0 }, 77056, 97792, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 588, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent110Track6[7] = {
    { 475, 15, { 0, 0 }, 85504, 89344, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 472, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 478, 620, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 472, 621, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 472, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 475, 1020, { 0, 0 }, 89600, 94208, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 472, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33029, NULL, NULL },
};

static const EventCharaKeyframe sEvent110Track7[7] = {
    { 475, 21, { 0, 0 }, 84736, 106752, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 473, 620, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 478, 640, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 473, 641, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 473, 1010, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 475, 1030, { 0, 0 }, 100352, 94976, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 472, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33029, NULL, NULL },
};

static const EventCharaKeyframe sEvent110Track8[7] = {
    { 475, 28, { 0, 0 }, 67840, 103168, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 473, 640, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 478, 660, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 473, 661, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 322, NULL, NULL },
    { 472, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 475, 1040, { 0, 0 }, 85760, 87040, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 472, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33029, NULL, NULL },
};

static const EventCharaKeyframe sEvent110Track9[7] = {
    { 475, 34, { 0, 0 }, 68864, 93184, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 472, 660, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 478, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 472, 681, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 322, NULL, NULL },
    { 472, 1030, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 475, 1050, { 0, 0 }, 74496, 86272, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 472, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33029, NULL, NULL },
};

static const EventCharaKeyframe sEvent110Track10[7] = {
    { 475, 41, { 0, 0 }, 89600, 97024, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 472, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 478, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 472, 701, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 472, 1040, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 475, 1060, { 0, 0 }, 96000, 85760, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 472, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33029, NULL, NULL },
};

static const EventCharaKeyframe sEvent110Track11[3] = {
    { 928, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8258, NULL, NULL },
    { 927, 1070, { 0, 0 }, 51200, 76288, 0, 0, { 0, 0 }, 16722, NULL, NULL },
    { 928, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98370, NULL, NULL },
};

static const EventCharaTrack sEvent110Tracks[12] = {
    { sEvent110Track0, 0, { 0, 0, 0 } },
    { sEvent110Track1, 1, { 0, 0, 0 } },
    { sEvent110Track2, 2, { 0, 0, 0 } },
    { sEvent110Track3, 12, { 0, 0, 0 } },
    { sEvent110Track4, 59, { 0, 0, 0 } },
    { sEvent110Track5, 48, { 0, 0, 0 } },
    { sEvent110Track6, 40, { 0, 0, 0 } },
    { sEvent110Track7, 40, { 0, 0, 0 } },
    { sEvent110Track8, 40, { 0, 0, 0 } },
    { sEvent110Track9, 40, { 0, 0, 0 } },
    { sEvent110Track10, 40, { 0, 0, 0 } },
    { sEvent110Track11, 93, { 0, 0, 0 } },
};

const EventSequenceDef gEvent110 = {
    12,
    { 0, 0, 0 },
    sEvent110Tracks,
    sEvent110Camera,
    sEvent110Script,
    sEvent110SoundCues,
    NULL,
    1280,
    0,
    1,
    0,
    0,
    0,
    0,
    124,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_111_text.inc"
static const MessageScriptEntry sEvent111Script[29] = {
    { 0, 1, 0, 1, { 0, 0, 0 }, gEventTextUs_08FA16EC, 0, 160 },
    { 15, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA1738, 0, 180 },
    { 0, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA178E, 0, 270 },
    { 1, 5, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA17A2, 0, 290 },
    { 15, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA17D2, 0, 400 },
    { 16, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA180E, 0, 600 },
    { 16, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA185E, 0, 602 },
    { 16, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA18B2, 0, 604 },
    { 16, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA193C, 0, 650 },
    { 15, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA19A4, 0, 750 },
    { 16, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA1A30, 0, 850 },
    { 16, 2, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA1AD6, 0, 852 },
    { 0, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA1B74, 0, 870 },
    { 16, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA1B80, 0, 900 },
    { 16, 2, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA1C20, 0, 902 },
    { 16, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA1C90, 0, 904 },
    { 15, 4, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA1CEC, 0, 1050 },
    { 21, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA1D24, 0, 1070 },
    { 21, 4, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA1D7A, 0, 1072 },
    { 16, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA1DDA, 0, 1100 },
    { 15, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA1E28, 0, 1300 },
    { 0, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA1E80, 0, 1320 },
    { 0, 2, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA1F6E, 0, 1322 },
    { 0, 2, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA1FF0, 0, 1324 },
    { 15, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA2092, 0, 1350 },
    { 15, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA209E, 0, 1500 },
    { 1, 0, 0, 1, { 0, 0, 0 }, gEventTextUs_08FA211C, 0, 1520 },
    { 1, 2, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA2150, 0, 1522 },
    { 15, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA21B0, MSG_SCRIPT_FLAG_END, 1700 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent111Script[29] = {
    { 0, 1, 0, 3, { 0, 0, 0 }, gEventTextJp_08F90074, 0, 160 },
    { 15, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F90044, 0, 180 },
    { 0, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F781F8, 0, 270 },
    { 1, 5, 3, 3, { 0, 0, 0 }, gEventTextJp_08F90020, 0, 290 },
    { 15, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8FFF8, 0, 400 },
    { 16, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8FFDC, 0, 600 },
    { 16, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F8FFA0, 0, 602 },
    { 16, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F8FF74, 0, 604 },
    { 16, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8FF30, 0, 650 },
    { 15, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F8FEE0, 0, 750 },
    { 16, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8FE88, 0, 850 },
    { 16, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08F8FE34, 0, 852 },
    { 0, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F76238, 0, 870 },
    { 16, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8FDF0, 0, 900 },
    { 16, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08F8FDA4, 0, 902 },
    { 16, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F8FD60, 0, 904 },
    { 15, 4, 1, 3, { 0, 0, 0 }, gEventTextJp_08F8FD44, 0, 1050 },
    { 21, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8FD10, 0, 1070 },
    { 21, 4, 4, 3, { 0, 0, 0 }, gEventTextJp_08F8FCDC, 0, 1072 },
    { 16, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8FCB4, 0, 1100 },
    { 15, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F8FC84, 0, 1300 },
    { 0, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F8FC30, 0, 1320 },
    { 0, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08F8FBE0, 0, 1322 },
    { 0, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08F8FBA0, 0, 1324 },
    { 15, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8FB94, 0, 1350 },
    { 15, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8FB54, 0, 1500 },
    { 1, 0, 0, 3, { 0, 0, 0 }, gEventTextJp_08F8FB28, 0, 1520 },
    { 1, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08F8FB00, 0, 1522 },
    { 15, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F8FACC, MSG_SCRIPT_FLAG_END, 1700 },
};

#include "event_111_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent111Script[29] = {
    { 0, 1, 0, 1, { 0, 0, 0 }, &gUnkEu_09F5DB70, 0, 160 },
    { 15, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DB84, 0, 180 },
    { 0, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5DB98, 0, 270 },
    { 1, 5, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DBAC, 0, 290 },
    { 15, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DBC0, 0, 400 },
    { 16, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DBD4, 0, 600 },
    { 16, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5DBE8, 0, 602 },
    { 16, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5DBFC, 0, 604 },
    { 16, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DC10, 0, 650 },
    { 15, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5DC24, 0, 750 },
    { 16, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DC38, 0, 850 },
    { 16, 2, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5DC4C, 0, 852 },
    { 0, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5DC60, 0, 870 },
    { 16, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DC74, 0, 900 },
    { 16, 2, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5DC88, 0, 902 },
    { 16, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5DC9C, 0, 904 },
    { 15, 4, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5DCB0, 0, 1050 },
    { 21, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DCC4, 0, 1070 },
    { 21, 4, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5DCD8, 0, 1072 },
    { 16, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DCEC, 0, 1100 },
    { 15, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5DD00, 0, 1300 },
    { 0, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5DD14, 0, 1320 },
    { 0, 2, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5DD28, 0, 1322 },
    { 0, 2, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5DD3C, 0, 1324 },
    { 15, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DD50, 0, 1350 },
    { 15, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DD64, 0, 1500 },
    { 1, 0, 0, 1, { 0, 0, 0 }, &gUnkEu_09F5DD78, 0, 1520 },
    { 1, 2, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5DD8C, 0, 1522 },
    { 15, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DDA0, MSG_SCRIPT_FLAG_END, 1700 },
};
#endif

static const EventCameraKeyframe sEvent111Camera[12] = {
    { -65336, 70400, 92416, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65316, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -65296, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -65276, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -65256, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -65236, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -65086, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64856, 36352, 28672, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -64756, 68352, 92416, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -64336, 36352, 28672, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -63826, 72704, 97536, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -63686, 72704, 22528, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 150, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent111SoundCues[6] = {
    { SONG_BGM_ALADDIN_FIELD, 0, 0, 0 },
    { SONG_BGM_ALADDIN_FIELD, 200, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT_UNREST, 450, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT_UNREST, 1150, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_ALADDIN_FIELD, 1500, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_ALADDIN_FIELD, 1745, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent111Track0[11] = {
    { 21, 1, { 0, 0 }, 84992, 106240, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 21, 100, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 22, 120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 0, 135, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 27, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 4, 1319, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 30, 1326, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent111Track1[11] = {
    { 123, 1, { 0, 0 }, 75008, 106752, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 123, 105, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 124, 125, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 135, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 133, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 110, 305, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 1519, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 126, 1524, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent111Track2[11] = {
    { 155, 1, { 0, 0 }, 59392, 103424, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 158, 110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 159, 130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 161, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 145, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 1301, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 142, 1306, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 1311, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent111Track3[21] = {
    { 282, 1, { 0, 0 }, 69120, 101120, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 282, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 270, 185, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 282, 190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 282, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 286, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 282, 310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 270, 320, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 270, 340, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 270, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 270, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 270, 410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 270, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 282, 1300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 287, 1330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 287, 1340, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 275, 1360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 275, 1490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 270, 1530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 270, 1690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 270, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent111Track4[10] = {
    { 664, 1, { 0, 0 }, 56320, 95488, -2560, 0, { 0, 0 }, 66, NULL, NULL },
    { 664, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 262213, NULL, NULL },
    { 673, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 664, 650, { 0, 0 }, 59136, 97280, -2560, 0, { 0, 0 }, 262210, NULL, NULL },
    { 665, 950, { 0, 0 }, 59136, 97280, -2560, 0, { 0, 0 }, 262146, NULL, NULL },
    { 672, 1020, { 0, 0 }, 52480, 42496, -7680, 664, { 0, 0 }, 4419, NULL, NULL },
    { 672, 1110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 262469, NULL, NULL },
    { 672, 1120, { 0, 0 }, 52480, 42496, -5120, 664, { 0, 0 }, 4419, NULL, NULL },
    { 672, 1180, { 0, 0 }, 52480, 42496, -46080, 664, { 0, 0 }, 4419, NULL, NULL },
    { 664, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98370, NULL, NULL },
};

static const EventCharaKeyframe sEvent111Track5[7] = {
    { 588, 949, { 0, 0 }, 77056, 97792, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 588, 950, { 0, 0 }, 58112, 97280, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 589, 1020, { 0, 0 }, 52480, 42752, -7680, 586, { 0, 0 }, 4419, NULL, NULL },
    { 589, 1110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 262469, NULL, NULL },
    { 589, 1120, { 0, 0 }, 52480, 42752, -5120, 586, { 0, 0 }, 4419, NULL, NULL },
    { 589, 1180, { 0, 0 }, 52480, 42752, -46080, 586, { 0, 0 }, 4419, NULL, NULL },
    { 589, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98370, NULL, NULL },
};

static const EventCharaKeyframe sEvent111Track6[9] = {
    { 632, 500, { 0, 0 }, 22528, 33536, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 634, 560, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 632, 610, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 635, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 636, 1110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 632, 1120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 633, 1130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 637, 1230, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 633, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98309, NULL, NULL },
};

static const EventCharaTrack sEvent111Tracks[7] = {
    { sEvent111Track0, 0, { 0, 0, 0 } },
    { sEvent111Track1, 1, { 0, 0, 0 } },
    { sEvent111Track2, 2, { 0, 0, 0 } },
    { sEvent111Track3, 12, { 0, 0, 0 } },
    { sEvent111Track4, 59, { 0, 0, 0 } },
    { sEvent111Track5, 48, { 0, 0, 0 } },
    { sEvent111Track6, 56, { 0, 0, 0 } },
};

const EventSequenceDef gEvent111 = {
    7,
    { 0, 0, 0 },
    sEvent111Tracks,
    sEvent111Camera,
    sEvent111Script,
    sEvent111SoundCues,
    NULL,
    1750,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_112_text.inc"
static const MessageScriptEntry sEvent112Script[15] = {
    { 16, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA3218, 0, 180 },
    { 16, 2, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA329E, 0, 182 },
    { 0, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA3352, 0, 220 },
    { 16, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA3370, 0, 300 },
    { 21, 4, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA33AC, 0, 410 },
    { 15, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA33CC, 0, 600 },
    { 15, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA33D6, 0, 602 },
    { 16, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA3406, 0, 620 },
    { 0, 1, 2, 1, { 0, 0, 0 }, gEventTextUs_08FA342A, 0, 660 },
    { 15, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA34A6, 0, 750 },
    { 21, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA3540, 0, 770 },
    { 16, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA3592, 0, 980 },
    { 16, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA35D6, 0, 982 },
    { 16, 2, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA3684, 0, 984 },
    { 16, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA36F8, MSG_SCRIPT_FLAG_END, 1010 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent112Script[15] = {
    { 16, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F91210, 0, 180 },
    { 16, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08F911B4, 0, 182 },
    { 0, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F911A0, 0, 220 },
    { 16, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9116C, 0, 300 },
    { 21, 4, 1, 3, { 0, 0, 0 }, gEventTextJp_08F91158, 0, 410 },
    { 15, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9114C, 0, 600 },
    { 15, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F9112C, 0, 602 },
    { 16, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9111C, 0, 620 },
    { 0, 1, 2, 3, { 0, 0, 0 }, gEventTextJp_08F910F0, 0, 660 },
    { 15, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F910A4, 0, 750 },
    { 21, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F91074, 0, 770 },
    { 16, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F91048, 0, 980 },
    { 16, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F90FFC, 0, 982 },
    { 16, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08F90FAC, 0, 984 },
    { 16, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F90F64, MSG_SCRIPT_FLAG_END, 1010 },
};

#include "event_112_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent112Script[15] = {
    { 16, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E138, 0, 180 },
    { 16, 2, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5E14C, 0, 182 },
    { 0, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E160, 0, 220 },
    { 16, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E174, 0, 300 },
    { 21, 4, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E188, 0, 410 },
    { 15, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E19C, 0, 600 },
    { 15, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5E1B0, 0, 602 },
    { 16, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E1C4, 0, 620 },
    { 0, 1, 2, 1, { 0, 0, 0 }, &gUnkEu_09F5E1D8, 0, 660 },
    { 15, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E1EC, 0, 750 },
    { 21, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E200, 0, 770 },
    { 16, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E214, 0, 980 },
    { 16, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5E228, 0, 982 },
    { 16, 2, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5E23C, 0, 984 },
    { 16, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E250, MSG_SCRIPT_FLAG_END, 1010 },
};
#endif

static const EventCameraKeyframe sEvent112Camera[15] = {
    { -65306, 91392, 43520, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65086, 89600, 33536, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 20, { 0, 0 }, NULL },
    { -65076, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_MEDIUM | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65036, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65016, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_LARGE | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65006, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64906, 48896, 20736, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 20, { 0, 0 }, NULL },
    { -64856, 91392, 38656, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 20, { 0, 0 }, NULL },
    { -64756, 48896, 20736, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 20, { 0, 0 }, NULL },
    { -64516, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64506, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -64486, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -64466, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -64436, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 30, { 0, 0 }, NULL },
    { -64036, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent112SoundCues[5] = {
    { SONG_BGM_EVENT_UNREST, 0, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 260, 0, 0 },
    { SONG_BGM_EVENT2, 300, 0, 0 },
    { SONG_BTL_AR_PUNCHHIT, 450, 0, 0 },
    { SONG_BTL_MON_HIT06, 500, EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent112Track0[5] = {
    { 4, 1, { 0, 0 }, 52736, 71680, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 14, 90, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 4, 93, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 4, 100, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 19, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent112Track1[7] = {
    { 114, 1, { 0, 0 }, 49152, 78336, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 120, 110, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 114, 113, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 114, 120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 122, 130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 123, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent112Track2[7] = {
    { 146, 1, { 0, 0 }, 40960, 73728, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 153, 132, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 146, 135, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 146, 140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 157, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 158, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent112Track3[12] = {
    { 282, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 282, 231, { 0, 0 }, 69888, 30976, -15360, 0, { 0, 0 }, 66, NULL, NULL },
    { 279, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaDrop, NULL },
    { 280, 305, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 281, 310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 272, 350, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 100, NULL, NULL },
    { 272, 353, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 274, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 277, 480, { 0, 0 }, 45568, 19456, 0, 270, { 0, 0 }, 67, NULL, NULL },
    { 273, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 270, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 274, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent112Track4[5] = {
    { 664, 340, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 665, 420, { 0, 0 }, 91648, 40448, -2560, 0, { 0, 0 }, 262146, NULL, NULL },
    { 667, 520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 262149, NULL, NULL },
    { 665, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 262149, NULL, NULL },
    { 664, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 294981, NULL, NULL },
};

static const EventCharaKeyframe sEvent112Track5[3] = {
    { 743, 340, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 743, 390, { 0, 0 }, 91648, 40448, -7680, 0, { 0, 0 }, 16658, NULL, NULL },
    { 743, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent112Track6[2] = {
    { 588, 1, { 0, 0 }, 93440, 43008, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 588, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent112Track7[11] = {
    { 632, 1, { 0, 0 }, 101632, 47616, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 632, 190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 634, 210, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 632, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 632, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 633, 771, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 637, 950, { 0, 0 }, 61696, 33024, 0, 633, { 0, 0 }, 3, NULL, NULL },
    { 633, 990, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 632, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 632, 1010, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 635, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent112Tracks[8] = {
    { sEvent112Track0, 0, { 0, 0, 0 } },
    { sEvent112Track1, 1, { 0, 0, 0 } },
    { sEvent112Track2, 2, { 0, 0, 0 } },
    { sEvent112Track3, 12, { 0, 0, 0 } },
    { sEvent112Track4, 59, { 0, 0, 0 } },
    { sEvent112Track5, 68, { 0, 0, 0 } },
    { sEvent112Track6, 48, { 0, 0, 0 } },
    { sEvent112Track7, 56, { 0, 0, 0 } },
};

const EventSequenceDef gEvent112 = {
    8,
    { 0, 0, 0 },
    sEvent112Tracks,
    sEvent112Camera,
    sEvent112Script,
    sEvent112SoundCues,
    NULL,
    1150,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    113,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_113_text.inc"
static const MessageScriptEntry sEvent113Script[1] = {
    { 0, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA42A8, MSG_SCRIPT_FLAG_END, 250 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent113Script[1] = {
    { 0, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F91C24, MSG_SCRIPT_FLAG_END, 250 },
};

#include "event_113_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent113Script[1] = {
    { 0, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DEB8, MSG_SCRIPT_FLAG_END, 250 },
};
#endif

static const EventCameraKeyframe sEvent113Camera[3] = {
    { -65536, 146944, 75776, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, NULL },
    { -65336, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 100, { 0, 0 }, NULL },
    { -55537, 146944, 75776, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent113SoundCues[1] = {
    { SONG_BGM_EVENT2, 0, EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent113Track0[1] = {
    { 20, 10, { 0, 0 }, 179712, 106496, 0, 0, { 0, 0 }, 32834, NULL, NULL },
};

static const EventCharaKeyframe sEvent113Track1[1] = {
    { 940, 10, { 0, 0 }, 86528, 14080, 0, 0, { 0, 0 }, 32770, NULL, NULL },
};

static const EventCharaTrack sEvent113Tracks[2] = {
    { sEvent113Track0, 0, { 0, 0, 0 } },
    { sEvent113Track1, 101, { 0, 0, 0 } },
};

const EventSequenceDef gEvent113 = {
    2,
    { 0, 0, 0 },
    sEvent113Tracks,
    sEvent113Camera,
    sEvent113Script,
    sEvent113SoundCues,
    NULL,
    300,
    0,
    1,
    0,
    0,
    0,
    0,
    149,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_114_text.inc"
static const MessageScriptEntry sEvent114Script[31] = {
    { 1, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA4400, 0, 90 },
    { 2, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA4432, 0, 120 },
    { 21, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA4502, 0, 220 },
    { 21, 4, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA457A, 0, 222 },
    { 21, 3, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA46AC, 0, 224 },
    { 15, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA474A, 0, 430 },
    { 15, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA476C, 0, 500 },
    { 21, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA47A4, 0, 850 },
    { 15, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA47B6, 0, 880 },
    { 21, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA4844, 0, 910 },
    { 21, 2, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA487C, 0, 915 },
    { 15, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA48DA, 0, 970 },
    { 15, 3, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA494A, 0, 972 },
    { 15, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA4986, 0, 1050 },
    { 15, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA49C4, 0, 1052 },
    { 0, 4, 0, 1, { 0, 0, 0 }, gEventTextUs_08FA4A04, 0, 1080 },
    { 15, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA4A2A, 0, 1140 },
    { 0, 3, 0, 1, { 0, 0, 0 }, gEventTextUs_08FA4A66, 0, 1160 },
    { 15, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA4A7A, 0, 1190 },
    { 15, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA4B20, 0, 1192 },
    { 0, 5, 0, 1, { 0, 0, 0 }, gEventTextUs_08FA4BB8, 0, 1240 },
    { 15, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA4BC4, 0, 1450 },
    { 21, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA4BE2, 0, 1470 },
    { 21, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA4C84, 0, 1740 },
    { 21, 3, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA4CC6, 0, 1744 },
    { 15, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA4CF6, 0, 1810 },
    { 0, 3, 0, 1, { 0, 0, 0 }, gEventTextUs_08FA4D0C, 0, 1860 },
    { 21, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA4D28, 0, 1890 },
    { 21, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA4DDA, 0, 1892 },
    { 0, 4, 0, 1, { 0, 0, 0 }, gEventTextUs_08FA4E3C, 0, 1922 },
    { 15, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA4E62, MSG_SCRIPT_FLAG_END, 1960 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent114Script[31] = {
    { 1, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9255C, 0, 90 },
    { 2, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F92538, 0, 120 },
    { 21, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F92500, 0, 220 },
    { 21, 4, 4, 3, { 0, 0, 0 }, gEventTextJp_08F924A0, 0, 222 },
    { 21, 3, 4, 3, { 0, 0, 0 }, gEventTextJp_08F92444, 0, 224 },
    { 15, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F92434, 0, 430 },
    { 15, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F92418, 0, 500 },
    { 21, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9240C, 0, 850 },
    { 15, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F923B8, 0, 880 },
    { 21, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F92394, 0, 910 },
    { 21, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08F92368, 0, 915 },
    { 15, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9231C, 0, 970 },
    { 15, 3, 4, 3, { 0, 0, 0 }, gEventTextJp_08F922E8, 0, 972 },
    { 15, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F922B0, 0, 1050 },
    { 15, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F92278, 0, 1052 },
    { 0, 4, 0, 3, { 0, 0, 0 }, gEventTextJp_08F92268, 0, 1080 },
    { 15, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F92244, 0, 1140 },
    { 0, 3, 0, 3, { 0, 0, 0 }, gEventTextJp_08F753B0, 0, 1160 },
    { 15, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F92200, 0, 1190 },
    { 15, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F921C8, 0, 1192 },
    { 0, 5, 0, 3, { 0, 0, 0 }, gEventTextJp_08F921BC, 0, 1240 },
    { 15, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F921A8, 0, 1450 },
    { 21, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F92168, 0, 1470 },
    { 21, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F92140, 0, 1740 },
    { 21, 3, 4, 3, { 0, 0, 0 }, gEventTextJp_08F92120, 0, 1744 },
    { 15, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9210C, 0, 1810 },
    { 0, 3, 0, 3, { 0, 0, 0 }, gEventTextJp_08F92100, 0, 1860 },
    { 21, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F920A8, 0, 1890 },
    { 21, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F92074, 0, 1892 },
    { 0, 4, 0, 3, { 0, 0, 0 }, gEventTextJp_08F9205C, 0, 1922 },
    { 15, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F92034, MSG_SCRIPT_FLAG_END, 1960 },
};

#include "event_114_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent114Script[31] = {
    { 1, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5DECC, 0, 90 },
    { 2, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5DEE0, 0, 120 },
    { 21, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DEF4, 0, 220 },
    { 21, 4, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5DF08, 0, 222 },
    { 21, 3, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5DF1C, 0, 224 },
    { 15, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DF30, 0, 430 },
    { 15, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5DF44, 0, 500 },
    { 21, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DF58, 0, 850 },
    { 15, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5DF6C, 0, 880 },
    { 21, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5DF80, 0, 910 },
    { 21, 2, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5DF94, 0, 915 },
    { 15, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5DFA8, 0, 970 },
    { 15, 3, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5DFBC, 0, 972 },
    { 15, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5DFD0, 0, 1050 },
    { 15, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5DFE4, 0, 1052 },
    { 0, 4, 0, 1, { 0, 0, 0 }, &gUnkEu_09F5DFF8, 0, 1080 },
    { 15, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E00C, 0, 1140 },
    { 0, 3, 0, 1, { 0, 0, 0 }, &gUnkEu_09F5E020, 0, 1160 },
    { 15, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E034, 0, 1190 },
    { 15, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5E048, 0, 1192 },
    { 0, 5, 0, 1, { 0, 0, 0 }, &gUnkEu_09F5E05C, 0, 1240 },
    { 15, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E070, 0, 1450 },
    { 21, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E084, 0, 1470 },
    { 21, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E098, 0, 1740 },
    { 21, 3, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5E0AC, 0, 1744 },
    { 15, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5E0C0, 0, 1810 },
    { 0, 3, 0, 1, { 0, 0, 0 }, &gUnkEu_09F5E0D4, 0, 1860 },
    { 21, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E0E8, 0, 1890 },
    { 21, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5E0FC, 0, 1892 },
    { 0, 4, 0, 1, { 0, 0, 0 }, &gUnkEu_09F5E110, 0, 1922 },
    { 15, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5E124, MSG_SCRIPT_FLAG_END, 1960 },
};
#endif

static const EventCameraKeyframe sEvent114Camera[9] = {
    { -64936, 87808, 38912, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64926, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_HALF_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -64916, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_HALF_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -64876, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 20, { 0, 0 }, NULL },
    { -64811, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 60, { 0, 0 }, NULL },
    { -64751, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 60, { 0, 0 }, NULL },
    { -64536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -60536, 85760, 41472, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 40, { 0, 0 }, NULL },
    { -55537, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent114SoundCues[4] = {
    { 65535, 0, 0, 0 },
    { SONG_EV_WHITEOUT, 660, 0, 0 },
    { SONG_BGM_EVENT4, 855, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT4, 2095, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent114Track0[14] = {
    { 4, 510, { 0, 0 }, 95488, 54272, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 4, 560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 4, 1075, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 36, 1162, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 16, 1480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 27, 1580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 27, 1590, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1719, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 75, 1840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 76, 2055, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 2065, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent114Track1[11] = {
    { 112, 85, { 0, 0 }, 102400, 47360, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 125, 92, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 112, 770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 113, 775, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 131, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 925, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 113, 935, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent114Track2[7] = {
    { 144, 115, { 0, 0 }, 97280, 41216, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 164, 122, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 144, 805, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 145, 930, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent114Track3[24] = {
    { 282, 170, { 0, 0 }, 84736, 50176, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 287, 270, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 287, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 287, 440, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 282, 460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 282, 940, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 287, 985, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 282, 995, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 270, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 271, 1030, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 270, 1100, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 270, 1340, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 270, 1390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 270, 1410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 282, 1420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 282, 1490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 270, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 270, 1760, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 270, 1770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 282, 1910, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 270, 1920, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 270, 1980, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 270, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 272, 9999, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 32804, NULL, NULL },
};

static const EventCharaKeyframe sEvent114Track4[8] = {
    { 664, 510, { 0, 0 }, 75008, 44032, -2560, 0, { 0, 0 }, 262210, NULL, NULL },
    { 664, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 262213, NULL, NULL },
    { 673, 721, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 674, 912, { 0, 0 }, 75008, 44032, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 671, 1480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 675, 1742, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 671, 2050, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 671, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent114Track5[3] = {
    { 743, 660, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 743, 710, { 0, 0 }, 74752, 42496, 0, 0, { 0, 0 }, 16658, NULL, NULL },
    { 743, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent114Track6[3] = {
    { 744, 785, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 744, 835, { 0, 0 }, 75264, 33792, 0, 0, { 0, 0 }, 16658, NULL, NULL },
    { 744, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent114Track7[3] = {
    { 744, 1520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 744, 1570, { 0, 0 }, 92416, 38656, 0, 0, { 0, 0 }, 16658, NULL, NULL },
    { 744, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent114Track8[5] = {
    { 593, 1520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 595, 1670, { 0, 0 }, 92416, 38656, 0, 0, { 0, 0 }, 16658, NULL, NULL },
    { 595, 1719, { 0, 0 }, 92416, 46592, 0, 593, { 0, 0 }, 275, NULL, NULL },
    { 602, 1840, { 0, 0 }, 95488, 54272, 0, 0, { 0, 0 }, 274, NULL, NULL },
    { 593, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent114Track9[3] = {
    { 928, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8258, NULL, NULL },
    { 927, 560, { 0, 0 }, 71680, 24576, 0, 0, { 0, 0 }, 16722, NULL, NULL },
    { 928, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98370, NULL, NULL },
};

static const EventCharaTrack sEvent114Tracks[10] = {
    { sEvent114Track0, 0, { 0, 0, 0 } },
    { sEvent114Track1, 1, { 0, 0, 0 } },
    { sEvent114Track2, 2, { 0, 0, 0 } },
    { sEvent114Track3, 12, { 0, 0, 0 } },
    { sEvent114Track4, 59, { 0, 0, 0 } },
    { sEvent114Track5, 68, { 0, 0, 0 } },
    { sEvent114Track6, 68, { 0, 0, 0 } },
    { sEvent114Track7, 68, { 0, 0, 0 } },
    { sEvent114Track8, 51, { 0, 0, 0 } },
    { sEvent114Track9, 93, { 0, 0, 0 } },
};

const EventSequenceDef gEvent114 = {
    10,
    { 0, 0, 0 },
    sEvent114Tracks,
    sEvent114Camera,
    sEvent114Script,
    sEvent114SoundCues,
    NULL,
    2100,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_115_text.inc"
static const MessageScriptEntry sEvent115Script[8] = {
    { 0, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA5EEC, 0, 150 },
    { 2, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA5F10, 0, 170 },
    { 1, 5, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA5F80, 0, 190 },
    { 0, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA5FC4, 0, 220 },
    { 1, 5, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA603A, 0, 300 },
    { 0, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA6044, 0, 320 },
    { 6, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA605E, 0, 560 },
    { 2, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA609C, MSG_SCRIPT_FLAG_END, 630 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent115Script[8] = {
    { 0, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9346C, 0, 150 },
    { 2, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F93438, 0, 170 },
    { 1, 5, 1, 3, { 0, 0, 0 }, gEventTextJp_08F93414, 0, 190 },
    { 0, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F933D8, 0, 220 },
    { 1, 5, 1, 3, { 0, 0, 0 }, gEventTextJp_08F781F8, 0, 300 },
    { 0, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F933C4, 0, 320 },
    { 6, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F933A0, 0, 560 },
    { 2, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F93384, MSG_SCRIPT_FLAG_END, 630 },
};

#include "event_115_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent115Script[8] = {
    { 0, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F683B8, 0, 150 },
    { 2, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F683CC, 0, 170 },
    { 1, 5, 1, 1, { 0, 0, 0 }, &gUnkEu_09F683E0, 0, 190 },
    { 0, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F683F4, 0, 220 },
    { 1, 5, 1, 1, { 0, 0, 0 }, &gUnkEu_09F68408, 0, 300 },
    { 0, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6841C, 0, 320 },
    { 6, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F68430, 0, 560 },
    { 2, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F68444, MSG_SCRIPT_FLAG_END, 630 },
};
#endif

static const EventCameraKeyframe sEvent115Camera[2] = {
    { -65536, 32768, 32768, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_KEYFRAME_FLAG_SWAY, 0, { 0, 0 }, NULL },
    { -55537, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_KEYFRAME_FLAG_SWAY | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 80, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent115SoundCues[4] = {
    { SONG_BGM_PETERPAN_FIELD, 0, 0, 0 },
    { SONG_SND_387, 251, 0, 0 },
    { SONG_SND_387, 780, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_PETERPAN_FIELD, 1015, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent115Track0[8] = {
    { 1, 80, { 0, 0 }, 24064, 40960, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 2, 100, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 135, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 290, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 27, 302, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 9, 9999, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 32836, NULL, NULL },
};

static const EventCharaKeyframe sEvent115Track2[11] = {
    { 114, 80, { 0, 0 }, 36608, 42496, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 114, 105, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 189, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 126, 191, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 133, 330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 114, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 110, 740, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 119, 9999, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 32836, NULL, NULL },
};

static const EventCharaKeyframe sEvent115Track1[15] = {
    { 144, 80, { 0, 0 }, 32256, 33024, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 144, 100, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 169, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 164, 171, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 163, 330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 629, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 164, 631, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 143, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 740, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 151, 9999, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 32836, NULL, NULL },
};

static const EventCharaKeyframe sEvent115Track3[16] = {
    { 455, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 455, 251, { 0, 0 }, 69888, 14336, -10240, 0, { 0, 0 }, 2, NULL, NULL },
    { 456, 290, { 0, 0 }, 28928, 39168, -5632, 455, { 0, 0 }, 131, NULL, NULL },
    { 456, 330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 133, NULL, NULL },
    { 456, 340, { 0, 0 }, 24832, 32512, -5632, 455, { 0, 0 }, 131, NULL, NULL },
    { 456, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 128, EventCharaCircleSlow, NULL },
    { 456, 580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 133, NULL, NULL },
    { 456, 590, { 0, 0 }, 28928, 39168, -5632, 455, { 0, 0 }, 131, NULL, NULL },
    { 456, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 133, NULL, NULL },
    { 456, 630, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaJitter, NULL },
    { 456, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 133, NULL, NULL },
    { 456, 670, { 0, 0 }, 0, 0, 0, 1, { 0, 0 }, 132, NULL, NULL },
    { 456, 710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 197, NULL, NULL },
    { 458, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 197, NULL, NULL },
    { 458, 800, { 0, 0 }, 69888, 14336, -10240, 459, { 0, 0 }, 195, NULL, NULL },
    { 458, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32965, NULL, NULL },
};

static const EventCharaKeyframe sEvent115Track4[9] = {
    { 229, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 231, 501, { 0, 0 }, 24064, 40960, 0, 0, { 0, 0 }, 16450, NULL, NULL },
    { 234, 530, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, EventCharaHop, NULL },
    { 231, 540, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 229, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 229, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 233, 700, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, EventCharaHop, NULL },
    { 229, 701, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 229, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent115Tracks[5] = {
    { sEvent115Track0, 0, { 0, 0, 0 } },
    { sEvent115Track1, 2, { 0, 0, 0 } },
    { sEvent115Track2, 1, { 0, 0, 0 } },
    { sEvent115Track3, 37, { 0, 0, 0 } },
    { sEvent115Track4, 8, { 0, 0, 0 } },
};

const EventSequenceDef gEvent115 = {
    5,
    { 0, 0, 0 },
    sEvent115Tracks,
    sEvent115Camera,
    sEvent115Script,
    sEvent115SoundCues,
    NULL,
    1020,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    1,
    255,
    255,
};

#ifdef VERSION_US
#include "event_116_text.inc"
static const MessageScriptEntry sEvent116Script[31] = {
    { 0, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA6A94, 0, 260 },
    { 2, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA6B12, 0, 280 },
    { 1, 0, 2, 1, { 0, 0, 0 }, gEventTextUs_08FA6B58, 0, 310 },
    { 2, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA6B7E, 0, 360 },
    { 29, 0, 0, 1, { 0, 0, 0 }, gEventTextUs_08FA6BE0, MSG_SCRIPT_FLAG_SILHOUETTE, 400 },
    { 29, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA6C7C, 0, 540 },
    { 1, 4, 2, 1, { 0, 0, 0 }, gEventTextUs_08FA6CF6, 0, 560 },
    { 1, 2, 0, 1, { 0, 0, 0 }, gEventTextUs_08FA6D84, 0, 730 },
    { 0, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA6DBA, 0, 800 },
    { 0, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA6E00, 0, 802 },
    { 2, 3, 2, 1, { 0, 0, 0 }, gEventTextUs_08FA6E34, 0, 820 },
    { 29, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA6E58, 0, 830 },
    { 29, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA6ED6, 0, 834 },
    { 1, 4, 2, 1, { 0, 0, 0 }, gEventTextUs_08FA6F74, 0, 850 },
    { 0, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA6F9C, 0, 890 },
    { 0, 3, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA6FEE, 0, 892 },
    { 29, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA7026, 0, 920 },
    { 1, 1, 2, 1, { 0, 0, 0 }, gEventTextUs_08FA70BA, 0, 940 },
    { 29, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA711C, 0, 960 },
    { 29, 2, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA7182, 0, 962 },
    { 2, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA71EA, 0, 980 },
    { 29, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA7218, 0, 1000 },
    { 29, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA72B8, 0, 1002 },
    { 29, 2, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA7372, 0, 1004 },
    { 0, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA73AA, 0, 1080 },
    { 0, 3, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA73F2, 0, 1082 },
    { 2, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA7474, 0, 1210 },
    { 0, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA74B6, 0, 1230 },
    { 29, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA7546, 0, 1400 },
    { 29, 3, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA75D2, 0, 1402 },
    { 1, 4, 2, 1, { 0, 0, 0 }, gEventTextUs_08FA7636, MSG_SCRIPT_FLAG_END, 1420 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent116Script[31] = {
    { 0, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F94644, 0, 260 },
    { 2, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F94618, 0, 280 },
    { 1, 0, 2, 3, { 0, 0, 0 }, gEventTextJp_08F94600, 0, 310 },
    { 2, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F945E4, 0, 360 },
    { 29, 0, 0, 3, { 0, 0, 0 }, gEventTextJp_08F9459C, MSG_SCRIPT_FLAG_SILHOUETTE, 400 },
    { 29, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F94554, 0, 540 },
    { 1, 4, 2, 3, { 0, 0, 0 }, gEventTextJp_08F94520, 0, 560 },
    { 1, 2, 0, 3, { 0, 0, 0 }, gEventTextJp_08F944EC, 0, 730 },
    { 0, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F944B4, 0, 800 },
    { 0, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F9449C, 0, 802 },
    { 2, 3, 2, 3, { 0, 0, 0 }, gEventTextJp_08F94490, 0, 820 },
    { 29, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F94450, 0, 830 },
    { 29, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F943F4, 0, 834 },
    { 1, 4, 2, 3, { 0, 0, 0 }, gEventTextJp_08F943E0, 0, 850 },
    { 0, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F943CC, 0, 890 },
    { 0, 3, 4, 3, { 0, 0, 0 }, gEventTextJp_08F943B4, 0, 892 },
    { 29, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F94368, 0, 920 },
    { 1, 1, 2, 3, { 0, 0, 0 }, gEventTextJp_08F94338, 0, 940 },
    { 29, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F942E8, 0, 960 },
    { 29, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08F942BC, 0, 962 },
    { 2, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F942A4, 0, 980 },
    { 29, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9425C, 0, 1000 },
    { 29, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F94200, 0, 1002 },
    { 29, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08F941C4, 0, 1004 },
    { 0, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F94190, 0, 1080 },
    { 0, 3, 4, 3, { 0, 0, 0 }, gEventTextJp_08F94130, 0, 1082 },
    { 2, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F93384, 0, 1210 },
    { 0, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F940FC, 0, 1230 },
    { 29, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F940AC, 0, 1400 },
    { 29, 3, 4, 3, { 0, 0, 0 }, gEventTextJp_08F9407C, 0, 1402 },
    { 1, 4, 2, 3, { 0, 0, 0 }, gEventTextJp_08F94064, MSG_SCRIPT_FLAG_END, 1420 },
};

#include "event_116_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent116Script[31] = {
    { 0, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F68458, 0, 260 },
    { 2, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6846C, 0, 280 },
    { 1, 0, 2, 1, { 0, 0, 0 }, &gUnkEu_09F68480, 0, 310 },
    { 2, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F68494, 0, 360 },
    { 29, 0, 0, 1, { 0, 0, 0 }, &gUnkEu_09F684A8, MSG_SCRIPT_FLAG_SILHOUETTE, 400 },
    { 29, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F684BC, 0, 540 },
    { 1, 4, 2, 1, { 0, 0, 0 }, &gUnkEu_09F684D0, 0, 560 },
    { 1, 2, 0, 1, { 0, 0, 0 }, &gUnkEu_09F684E4, 0, 730 },
    { 0, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F684F8, 0, 800 },
    { 0, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6850C, 0, 802 },
    { 2, 3, 2, 1, { 0, 0, 0 }, &gUnkEu_09F68520, 0, 820 },
    { 29, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F68534, 0, 830 },
    { 29, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F68548, 0, 834 },
    { 1, 4, 2, 1, { 0, 0, 0 }, &gUnkEu_09F6855C, 0, 850 },
    { 0, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F68570, 0, 890 },
    { 0, 3, 4, 1, { 0, 0, 0 }, &gUnkEu_09F68584, 0, 892 },
    { 29, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F68598, 0, 920 },
    { 1, 1, 2, 1, { 0, 0, 0 }, &gUnkEu_09F685AC, 0, 940 },
    { 29, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F685C0, 0, 960 },
    { 29, 2, 4, 1, { 0, 0, 0 }, &gUnkEu_09F685D4, 0, 962 },
    { 2, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F685E8, 0, 980 },
    { 29, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F685FC, 0, 1000 },
    { 29, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F68610, 0, 1002 },
    { 29, 2, 4, 1, { 0, 0, 0 }, &gUnkEu_09F68624, 0, 1004 },
    { 0, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F68638, 0, 1080 },
    { 0, 3, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6864C, 0, 1082 },
    { 2, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F68660, 0, 1210 },
    { 0, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F68674, 0, 1230 },
    { 29, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F68688, 0, 1400 },
    { 29, 3, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6869C, 0, 1402 },
    { 1, 4, 2, 1, { 0, 0, 0 }, &gUnkEu_09F686B0, MSG_SCRIPT_FLAG_END, 1420 },
};
#endif

static const EventCameraKeyframe sEvent116Camera[1] = {
    { -55537, 32768, 32768, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SWAY | CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent116SoundCues[6] = {
    { 65535, 0, 0, 0 },
    { SONG_SND_387, 1, 0, 0 },
    { SONG_BGM_PETERPAN_FIELD, 420, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_EV_MAN_RMARBLEL, 460, 0, 0 },
    { SONG_SND_387, 1490, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_PETERPAN_FIELD, 1515, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent116Track0[29] = {
    { 4, 0, { 0, 0 }, -8960, 57344, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 9, 150, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 4, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 1, 235, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 259, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 32, 261, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 415, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 0, 430, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 440, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 4, 740, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 27, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 785, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 799, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 31, 801, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 831, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 833, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 891, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 27, 894, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 1010, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 1060, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 4, 1070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 34, 1081, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent116Track1[30] = {
    { 114, 0, { 0, 0 }, -4096, 63488, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 119, 150, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 114, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 110, 185, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 290, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 110, 295, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 309, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 126, 311, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 440, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 114, 559, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 131, 561, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateSmokeTask },
    { 114, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 114, 710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 110, 715, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 729, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 126, 731, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 127, 845, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 128, 851, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 129, 855, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 939, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 126, 941, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 1410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 127, 1415, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 128, 1421, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 129, 1425, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent116Track2[20] = {
    { 146, 0, { 0, 0 }, -17152, 57600, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 151, 150, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 146, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 279, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 281, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaToggleAnim, NULL },
    { 145, 340, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 359, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 164, 361, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 415, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 440, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 146, 819, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 170, 831, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 979, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 165, 981, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 1209, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 165, 1211, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent116Track3[16] = {
    { 455, 0, { 0, 0 }, -256, 53504, -5632, 0, { 0, 0 }, 66, NULL, NULL },
    { 458, 150, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 196, NULL, NULL },
    { 458, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 197, NULL, NULL },
    { 456, 320, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 133, NULL, NULL },
    { 456, 330, { 0, 0 }, 30976, 45568, -5632, 455, { 0, 0 }, 195, NULL, NULL },
    { 456, 370, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 192, EventCharaCircleFast, NULL },
    { 456, 399, { 0, 0 }, 19456, 46848, -5632, 455, { 0, 0 }, 131, NULL, NULL },
    { 456, 430, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 133, NULL, NULL },
    { 456, 460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 197, NULL, NULL },
    { 458, 1100, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 197, NULL, NULL },
    { 458, 1110, { 0, 0 }, 29952, 37632, -5632, 459, { 0, 0 }, 195, NULL, NULL },
    { 456, 1120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 133, NULL, NULL },
    { 456, 1200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 128, EventCharaJitter, NULL },
    { 456, 1210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 133, NULL, NULL },
    { 456, 1220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 197, NULL, NULL },
    { 458, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32965, NULL, NULL },
};

static const EventCharaKeyframe sEvent116Track4[9] = {
    { 299, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 299, 421, { 0, 0 }, 40704, 32768, -23040, 0, { 0, 0 }, 16386, NULL, NULL },
    { 301, 460, { 0, 0 }, 40704, 32768, 0, 299, { 0, 0 }, 3, NULL, NULL },
    { 299, 540, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 303, 821, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 304, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 299, 1240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 299, 1370, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 299, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent116Tracks[5] = {
    { sEvent116Track0, 0, { 0, 0, 0 } },
    { sEvent116Track1, 1, { 0, 0, 0 } },
    { sEvent116Track2, 2, { 0, 0, 0 } },
    { sEvent116Track3, 37, { 0, 0, 0 } },
    { sEvent116Track4, 14, { 0, 0, 0 } },
};

const EventSequenceDef gEvent116 = {
    5,
    { 0, 0, 0 },
    sEvent116Tracks,
    sEvent116Camera,
    sEvent116Script,
    sEvent116SoundCues,
    NULL,
    1520,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_117_text.inc"
static const MessageScriptEntry sEvent117Script[24] = {
    { 29, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA88A0, 0, 130 },
    { 42, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA88BC, 0, 320 },
    { 29, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA88E0, 0, 340 },
    { 29, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA896E, 0, 490 },
    { 42, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA8A0C, 0, 650 },
    { 42, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA8A7A, 0, 652 },
    { 29, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA8AB4, 0, 720 },
    { 29, 4, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA8AEC, 0, 722 },
    { 29, 4, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA8B96, 0, 724 },
    { 29, 4, 4, 1, { 0, 0, 0 }, gEventTextUs_08FA8BFC, 0, 726 },
    { 42, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA8C66, 0, 750 },
    { 29, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA8CC0, 0, 900 },
    { 42, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA8D46, 0, 920 },
    { 29, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA8D7A, 0, 940 },
    { 0, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA8E06, 0, 1040 },
    { 1, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA8E2E, 0, 1080 },
    { 42, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA8E4C, 0, 1140 },
    { 0, 7, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA8E5A, 0, 1180 },
    { 2, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA8EB8, 0, 1210 },
    { 1, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA8F5C, 0, 1240 },
    { 0, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA8FC4, 0, 1250 },
    { 0, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA901E, 0, 1400 },
    { 42, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08FA9090, 0, 1420 },
    { 2, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FA90B8, MSG_SCRIPT_FLAG_END, 1440 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent117Script[24] = {
    { 29, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F95C84, 0, 130 },
    { 42, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F95C68, 0, 320 },
    { 29, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F95C28, 0, 340 },
    { 29, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F95BD8, 0, 490 },
    { 42, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F95BAC, 0, 650 },
    { 42, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F95B90, 0, 652 },
    { 29, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08F95B78, 0, 720 },
    { 29, 4, 4, 3, { 0, 0, 0 }, gEventTextJp_08F95B24, 0, 722 },
    { 29, 4, 4, 3, { 0, 0, 0 }, gEventTextJp_08F95AD4, 0, 724 },
    { 29, 4, 4, 3, { 0, 0, 0 }, gEventTextJp_08F95A94, 0, 726 },
    { 42, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F95A6C, 0, 750 },
    { 29, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F95A2C, 0, 900 },
    { 42, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F95A10, 0, 920 },
    { 29, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F959C8, 0, 940 },
    { 0, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F959AC, 0, 1040 },
    { 1, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F95994, 0, 1080 },
    { 42, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F95984, 0, 1140 },
    { 0, 7, 3, 3, { 0, 0, 0 }, gEventTextJp_08F95964, 0, 1180 },
    { 2, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9591C, 0, 1210 },
    { 1, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F958EC, 0, 1240 },
    { 0, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F958B8, 0, 1250 },
    { 0, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08F95860, 0, 1400 },
    { 42, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9584C, 0, 1420 },
    { 2, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F957FC, MSG_SCRIPT_FLAG_END, 1440 },
};

#include "event_117_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent117Script[24] = {
    { 29, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F686C4, 0, 130 },
    { 42, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F686D8, 0, 320 },
    { 29, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F686EC, 0, 340 },
    { 29, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F68700, 0, 490 },
    { 42, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F68714, 0, 650 },
    { 42, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F68728, 0, 652 },
    { 29, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6873C, 0, 720 },
    { 29, 4, 4, 1, { 0, 0, 0 }, &gUnkEu_09F68750, 0, 722 },
    { 29, 4, 4, 1, { 0, 0, 0 }, &gUnkEu_09F68764, 0, 724 },
    { 29, 4, 4, 1, { 0, 0, 0 }, &gUnkEu_09F68778, 0, 726 },
    { 42, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6878C, 0, 750 },
    { 29, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F687A0, 0, 900 },
    { 42, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F687B4, 0, 920 },
    { 29, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F687C8, 0, 940 },
    { 0, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F687DC, 0, 1040 },
    { 1, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F687F0, 0, 1080 },
    { 42, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F68804, 0, 1140 },
    { 0, 7, 3, 1, { 0, 0, 0 }, &gUnkEu_09F68818, 0, 1180 },
    { 2, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6882C, 0, 1210 },
    { 1, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F68840, 0, 1240 },
    { 0, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F68854, 0, 1250 },
    { 0, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F68868, 0, 1400 },
    { 42, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6887C, 0, 1420 },
    { 2, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F68890, MSG_SCRIPT_FLAG_END, 1440 },
};
#endif

static const EventCameraKeyframe sEvent117Camera[2] = {
    { -65396, 30720, 27136, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SWAY, 0, { 0, 0 }, NULL },
    { -65366, 35072, 27136, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SWAY | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 30, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent117SoundCues[8] = {
    { SONG_BGM_PETERPAN_FIELD, 0, 0, 0 },
    { SONG_SND_387, 1, 0, 0 },
    { SONG_BGM_PETERPAN_FIELD, 650, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT_SILENCE, 900, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT_SILENCE, 1139, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_PETERPAN_FIELD, 1180, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_SND_387, 1520, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_PETERPAN_FIELD, 1545, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent117Track0[23] = {
    { 2, 150, { 0, 0 }, -7168, 11520, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 7, 310, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 2, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 2, 1010, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 1015, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 0, 1025, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1039, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 30, 1041, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 1155, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 1160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 1, 1165, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 1179, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 32, 1260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 32, 1390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 2, 1450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 1, 1455, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 1460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 1465, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 14, 9999, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 32804, NULL, NULL },
};

static const EventCharaKeyframe sEvent117Track1[26] = {
    { 112, 150, { 0, 0 }, -15360, 12288, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 117, 310, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 112, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 112, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 112, 1010, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 113, 1015, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 110, 1025, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 1079, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 126, 1081, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 1150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 113, 1155, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 1160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 111, 1165, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 1220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 113, 1225, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 1239, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 126, 1241, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 1405, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 113, 1410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 112, 1450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 111, 1455, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 1460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 113, 1465, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 1480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 120, 9999, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 32804, NULL, NULL },
};

static const EventCharaKeyframe sEvent117Track2[26] = {
    { 144, 150, { 0, 0 }, -3328, 5888, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 149, 310, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 144, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 144, 1010, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 143, 1015, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 145, 1025, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 1150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 145, 1155, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 1160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 143, 1165, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 1190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 143, 1195, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 1209, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 164, 1211, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 1405, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 143, 1410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 1439, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 164, 1441, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 1450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 143, 1455, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 1460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 145, 1465, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 1480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 153, 9999, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 32804, NULL, NULL },
};

static const EventCharaKeyframe sEvent117Track3[18] = {
    { 309, 1, { 0, 0 }, 256, 16640, -2560, 0, { 0, 0 }, 194, NULL, NULL },
    { 309, 100, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 196, NULL, NULL },
    { 310, 110, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 196, NULL, NULL },
    { 301, 140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 197, NULL, NULL },
    { 308, 163, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 228, NULL, NULL },
    { 309, 173, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 228, NULL, NULL },
    { 301, 183, { 0, 0 }, 39424, 36096, 0, 299, { 0, 0 }, 67, NULL, NULL },
    { 299, 660, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 305, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 306, 750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 299, 760, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 299, 890, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 299, 950, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 301, 980, { 0, 0 }, 0, 0, 0, 1, { 0, 0 }, 68, NULL, NULL },
    { 301, 985, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 302, 990, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 311, 1060, { 0, 0 }, -3328, 14336, -23040, 300, { 0, 0 }, 3, NULL, NULL },
    { 300, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent117Track4[4] = {
    { 682, 1, { 0, 0 }, 45312, 39168, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 682, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 682, 630, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 682, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent117Track5[6] = {
    { 455, 0, { 0, 0 }, 3840, 14336, -5632, 0, { 0, 0 }, 66, NULL, NULL },
    { 456, 110, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 196, NULL, NULL },
    { 456, 140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 197, NULL, NULL },
    { 456, 185, { 0, 0 }, 49664, 37888, -5632, 455, { 0, 0 }, 195, NULL, NULL },
    { 456, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 133, NULL, NULL },
    { 458, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32901, NULL, NULL },
};

static const EventCharaTrack sEvent117Tracks[6] = {
    { sEvent117Track0, 0, { 0, 0, 0 } },
    { sEvent117Track1, 1, { 0, 0, 0 } },
    { sEvent117Track2, 2, { 0, 0, 0 } },
    { sEvent117Track3, 14, { 0, 0, 0 } },
    { sEvent117Track4, 62, { 0, 0, 0 } },
    { sEvent117Track5, 37, { 0, 0, 0 } },
};

const EventSequenceDef gEvent117 = {
    6,
    { 0, 0, 0 },
    sEvent117Tracks,
    sEvent117Camera,
    sEvent117Script,
    sEvent117SoundCues,
    NULL,
    1550,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_118_text.inc"
static const MessageScriptEntry sEvent118Script[23] = {
    { 1, 3, 0, 1, { 0, 0, 0 }, gEventTextUs_08FAA2D8, 0, 120 },
    { 30, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAA314, MSG_SCRIPT_FLAG_SILHOUETTE, 150 },
    { 30, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAA34C, 0, 350 },
    { 30, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08FAA3B8, 0, 352 },
    { 1, 0, 0, 1, { 0, 0, 0 }, gEventTextUs_08FAA3FC, 0, 390 },
    { 2, 0, 2, 1, { 0, 0, 0 }, gEventTextUs_08FAA424, 0, 410 },
    { 0, 0, 0, 1, { 0, 0, 0 }, gEventTextUs_08FAA466, 0, 430 },
    { 30, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAA4E0, 0, 480 },
    { 30, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08FAA57C, 0, 482 },
    { 0, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FAA5FE, 0, 530 },
    { 2, 0, 2, 1, { 0, 0, 0 }, gEventTextUs_08FAA67A, 0, 550 },
    { 30, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAA6B2, 0, 580 },
    { 0, 3, 2, 1, { 0, 0, 0 }, gEventTextUs_08FAA728, 0, 850 },
    { 30, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAA736, 0, 940 },
    { 1, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FAA792, 0, 960 },
    { 30, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAA7AE, 0, 980 },
    { 29, 3, 0, 1, { 0, 0, 0 }, gEventTextUs_08FAA85E, 0, 1000 },
    { 42, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAA8CC, 0, 1100 },
    { 29, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAA8DA, 0, 1120 },
    { 30, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FAA90E, 0, 1140 },
    { 29, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAA984, 0, 1190 },
    { 30, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FAA992, 0, 1260 },
    { 30, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FAA9C0, MSG_SCRIPT_FLAG_END, 1500 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent118Script[23] = {
    { 1, 3, 0, 3, { 0, 0, 0 }, gEventTextJp_08F97208, 0, 120 },
    { 30, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F971F0, MSG_SCRIPT_FLAG_SILHOUETTE, 150 },
    { 30, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F971B4, 0, 350 },
    { 30, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F97194, 0, 352 },
    { 1, 0, 0, 3, { 0, 0, 0 }, gEventTextJp_08F97180, 0, 390 },
    { 2, 0, 2, 3, { 0, 0, 0 }, gEventTextJp_08F97150, 0, 410 },
    { 0, 0, 0, 3, { 0, 0, 0 }, gEventTextJp_08F97120, 0, 430 },
    { 30, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F970C8, 0, 480 },
    { 30, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F970A4, 0, 482 },
    { 0, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9704C, 0, 530 },
    { 2, 0, 2, 3, { 0, 0, 0 }, gEventTextJp_08F97034, 0, 550 },
    { 30, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F97000, 0, 580 },
    { 0, 3, 2, 3, { 0, 0, 0 }, gEventTextJp_08F96FF0, 0, 850 },
    { 30, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F96FBC, 0, 940 },
    { 1, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F88BFC, 0, 960 },
    { 30, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F96F68, 0, 980 },
    { 29, 3, 0, 3, { 0, 0, 0 }, gEventTextJp_08F96F38, 0, 1000 },
    { 42, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F96F2C, 0, 1100 },
    { 29, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F96EE4, 0, 1120 },
    { 30, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F96E9C, 0, 1140 },
    { 29, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F96E90, 0, 1190 },
    { 30, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F96E68, 0, 1260 },
    { 30, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F96E14, MSG_SCRIPT_FLAG_END, 1500 },
};

#include "event_118_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent118Script[23] = {
    { 1, 3, 0, 1, { 0, 0, 0 }, &gUnkEu_09F68AFC, 0, 120 },
    { 30, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F68B10, MSG_SCRIPT_FLAG_SILHOUETTE, 150 },
    { 30, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F68B24, 0, 350 },
    { 30, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F68B38, 0, 352 },
    { 1, 0, 0, 1, { 0, 0, 0 }, &gUnkEu_09F68B4C, 0, 390 },
    { 2, 0, 2, 1, { 0, 0, 0 }, &gUnkEu_09F68B60, 0, 410 },
    { 0, 0, 0, 1, { 0, 0, 0 }, &gUnkEu_09F68B74, 0, 430 },
    { 30, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F68B88, 0, 480 },
    { 30, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F68B9C, 0, 482 },
    { 0, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F68BB0, 0, 530 },
    { 2, 0, 2, 1, { 0, 0, 0 }, &gUnkEu_09F68BC4, 0, 550 },
    { 30, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F68BD8, 0, 580 },
    { 0, 3, 2, 1, { 0, 0, 0 }, &gUnkEu_09F68BEC, 0, 850 },
    { 30, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F68C00, 0, 940 },
    { 1, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F68C14, 0, 960 },
    { 30, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F68C28, 0, 980 },
    { 29, 3, 0, 1, { 0, 0, 0 }, &gUnkEu_09F68C3C, 0, 1000 },
    { 42, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F68C50, 0, 1100 },
    { 29, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F68C64, 0, 1120 },
    { 30, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F68C78, 0, 1140 },
    { 29, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F68C8C, 0, 1190 },
    { 30, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F68CA0, 0, 1260 },
    { 30, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F68CB4, MSG_SCRIPT_FLAG_END, 1500 },
};
#endif

static const EventCameraKeyframe sEvent118Camera[5] = {
    { -65321, 33024, 71424, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SWAY, 0, { 0, 0 }, NULL },
    { -64936, 41728, 63744, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SWAY | CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -64336, 86784, 69888, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SWAY | CAMERA_MODE_APPROACH, 120, { 0, 0 }, NULL },
    { -64036, 96256, 69888, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SWAY | CAMERA_MODE_APPROACH, 20, { 0, 0 }, NULL },
    { -55537, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SWAY | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent118SoundCues[8] = {
    { 65535, 0, 0, 0 },
    { SONG_BGM_EVENT3, 350, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT3, 600, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT_UNREST, 650, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT_UNREST, 1141, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT1, 1190, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_SND_384, 1191, 0, 0 },
    { SONG_EV_HUKUROUJUMP, 1205, EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent118Track0[28] = {
    { 4, 1, { 0, 0 }, 14848, 83712, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 9, 80, { 0, 0 }, 29440, 73728, 0, 4, { 0, 0 }, 67, NULL, NULL },
    { 4, 90, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 95, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 100, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 1, 105, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 2, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 1, 225, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 235, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 365, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 370, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 1, 375, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 32, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 1, 505, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 515, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 529, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 30, 531, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 555, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 19, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent118Track1[20] = {
    { 114, 1, { 0, 0 }, 14848, 91904, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 119, 80, { 0, 0 }, 29440, 81408, 0, 114, { 0, 0 }, 67, NULL, NULL },
    { 114, 90, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 110, 95, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 119, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 126, 121, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 114, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 110, 225, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 110, 365, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 389, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 126, 391, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 110, 505, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 122, 565, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 123, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent118Track2[19] = {
    { 146, 1, { 0, 0 }, 4608, 86784, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 151, 80, { 0, 0 }, 19712, 76032, 0, 146, { 0, 0 }, 67, NULL, NULL },
    { 146, 90, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 95, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 144, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 225, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 365, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 409, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 164, 411, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 505, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 549, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 165, 551, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 555, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 157, 565, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 158, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent118Track3[21] = {
    { 576, 160, { 0, 0 }, 90112, 45568, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 577, 300, { 0, 0 }, 49664, 65536, 0, 576, { 0, 0 }, 3, NULL, NULL },
    { 576, 349, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 578, 351, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateSmokeTask },
    { 576, 479, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 578, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateSmokeTask },
    { 576, 860, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 577, 920, { 0, 0 }, 73472, 73984, 0, 576, { 0, 0 }, 67, NULL, NULL },
    { 576, 930, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 576, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 576, 1070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 576, 1130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 578, 1150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 576, 1160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 576, 1191, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 579, 1195, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 580, 1230, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 100, EventCharaHop, NULL },
    { 581, 1259, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 100, EventCharaHopLow, NULL },
    { 582, 1450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 583, 1480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 585, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32832, NULL, CreateSmokeTask },
};

static const EventCharaKeyframe sEvent118Track4[9] = {
    { 681, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8258, NULL, NULL },
    { 681, 601, { 0, 0 }, 94208, 84480, 0, 0, { 0, 0 }, 16450, NULL, NULL },
    { 681, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 681, 1070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 681, 1080, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 682, 1200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 681, 1205, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 683, 1250, { 0, 0 }, 98304, 69888, -5120, 681, { 0, 0 }, 4227, NULL, NULL },
    { 683, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32901, NULL, NULL },
};

static const EventCharaKeyframe sEvent118Track5[7] = {
    { 299, 1010, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 301, 1011, { 0, 0 }, 89856, 82176, -25600, 0, { 0, 0 }, 16386, NULL, NULL },
    { 301, 1050, { 0, 0 }, 89856, 82176, -2560, 299, { 0, 0 }, 131, NULL, NULL },
    { 301, 1195, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 133, NULL, NULL },
    { 299, 1205, { 0, 0 }, 94208, 84224, 0, 299, { 0, 0 }, 3, NULL, NULL },
    { 307, 1250, { 0, 0 }, 98304, 69632, -5120, 299, { 0, 0 }, 4227, NULL, NULL },
    { 307, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32901, NULL, NULL },
};

static const EventCharaTrack sEvent118Tracks[6] = {
    { sEvent118Track0, 0, { 0, 0, 0 } },
    { sEvent118Track1, 1, { 0, 0, 0 } },
    { sEvent118Track2, 2, { 0, 0, 0 } },
    { sEvent118Track3, 47, { 0, 0, 0 } },
    { sEvent118Track4, 62, { 0, 0, 0 } },
    { sEvent118Track5, 14, { 0, 0, 0 } },
};

const EventSequenceDef gEvent118 = {
    6,
    { 0, 0, 0 },
    sEvent118Tracks,
    sEvent118Camera,
    sEvent118Script,
    sEvent118SoundCues,
    NULL,
    1550,
    0,
    1,
    0,
    0,
    0,
    0,
    158,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_119_text.inc"
static const MessageScriptEntry sEvent119Script[30] = {
    { 0, 4, 1, 1, { 0, 0, 0 }, gEventTextUs_08FABC64, 0, 100 },
    { 29, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08FABCA2, 0, 120 },
    { 29, 4, 4, 1, { 0, 0, 0 }, gEventTextUs_08FABD8E, 0, 122 },
    { 29, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FABE14, 0, 140 },
    { 42, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FABE9C, 0, 160 },
    { 29, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FABEFC, 0, 310 },
    { 29, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08FABF84, 0, 312 },
    { 42, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAC02E, 0, 460 },
    { 29, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FAC0B4, 0, 480 },
    { 29, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08FAC170, 0, 482 },
    { 29, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08FAC1DC, 0, 484 },
    { 0, 5, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAC252, 0, 500 },
    { 0, 0, 0, 1, { 0, 0, 0 }, gEventTextUs_08FAC272, 0, 600 },
    { 0, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08FAC30C, 0, 602 },
    { 0, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08FAC3B4, 0, 604 },
    { 0, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08FAC456, 0, 606 },
    { 42, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAC4DE, 0, 630 },
    { 29, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FAC504, 0, 650 },
    { 29, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08FAC51C, 0, 652 },
    { 29, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08FAC592, 0, 654 },
    { 29, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FAC602, 0, 810 },
    { 42, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAC67C, 0, 920 },
    { 29, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FAC692, 0, 960 },
    { 29, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FAC6DC, 0, 1000 },
    { 0, 3, 0, 1, { 0, 0, 0 }, gEventTextUs_08FAC76A, 0, 1340 },
    { 0, 0, 0, 1, { 0, 0, 0 }, gEventTextUs_08FAC79C, 0, 1700 },
    { 1, 3, 0, 1, { 0, 0, 0 }, gEventTextUs_08FAC7DC, 0, 1720 },
    { 1, 4, 0, 1, { 0, 0, 0 }, gEventTextUs_08FAC83E, 0, 1760 },
    { 2, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FAC848, 0, 1790 },
    { 1, 4, 0, 1, { 0, 0, 0 }, gEventTextUs_08FAC87A, MSG_SCRIPT_FLAG_END, 1810 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent119Script[30] = {
    { 0, 4, 1, 3, { 0, 0, 0 }, gEventTextJp_08F98A68, 0, 100 },
    { 29, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F98A1C, 0, 120 },
    { 29, 4, 4, 3, { 0, 0, 0 }, gEventTextJp_08F989F0, 0, 122 },
    { 29, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F989AC, 0, 140 },
    { 42, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F98988, 0, 160 },
    { 29, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F98944, 0, 310 },
    { 29, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F98900, 0, 312 },
    { 42, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F988B4, 0, 460 },
    { 29, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F98860, 0, 480 },
    { 29, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F98834, 0, 482 },
    { 29, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F987F4, 0, 484 },
    { 0, 5, 1, 3, { 0, 0, 0 }, gEventTextJp_08F987DC, 0, 500 },
    { 0, 0, 0, 3, { 0, 0, 0 }, gEventTextJp_08F9879C, 0, 600 },
    { 0, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F98744, 0, 602 },
    { 0, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F986F8, 0, 604 },
    { 0, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F986B4, 0, 606 },
    { 42, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F986A4, 0, 630 },
    { 29, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F98694, 0, 650 },
    { 29, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F98650, 0, 652 },
    { 29, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F98618, 0, 654 },
    { 29, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F985DC, 0, 810 },
    { 42, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F95984, 0, 920 },
    { 29, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F985BC, 0, 960 },
    { 29, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F98574, 0, 1000 },
    { 0, 3, 0, 3, { 0, 0, 0 }, gEventTextJp_08F98558, 0, 1340 },
    { 0, 0, 0, 3, { 0, 0, 0 }, gEventTextJp_08F98534, 0, 1700 },
    { 1, 3, 0, 3, { 0, 0, 0 }, gEventTextJp_08F9850C, 0, 1720 },
    { 1, 4, 0, 3, { 0, 0, 0 }, gEventTextJp_08F98500, 0, 1760 },
    { 2, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F984D8, 0, 1790 },
    { 1, 4, 0, 3, { 0, 0, 0 }, gEventTextJp_08F94064, MSG_SCRIPT_FLAG_END, 1810 },
};

#include "event_119_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent119Script[30] = {
    { 0, 4, 1, 1, { 0, 0, 0 }, &gUnkEu_09F688A4, 0, 100 },
    { 29, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F688B8, 0, 120 },
    { 29, 4, 4, 1, { 0, 0, 0 }, &gUnkEu_09F688CC, 0, 122 },
    { 29, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F688E0, 0, 140 },
    { 42, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F688F4, 0, 160 },
    { 29, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F68908, 0, 310 },
    { 29, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6891C, 0, 312 },
    { 42, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F68930, 0, 460 },
    { 29, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F68944, 0, 480 },
    { 29, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F68958, 0, 482 },
    { 29, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6896C, 0, 484 },
    { 0, 5, 1, 1, { 0, 0, 0 }, &gUnkEu_09F68980, 0, 500 },
    { 0, 0, 0, 1, { 0, 0, 0 }, &gUnkEu_09F68994, 0, 600 },
    { 0, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F689A8, 0, 602 },
    { 0, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F689BC, 0, 604 },
    { 0, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F689D0, 0, 606 },
    { 42, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F689E4, 0, 630 },
    { 29, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F689F8, 0, 650 },
    { 29, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F68A0C, 0, 652 },
    { 29, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F68A20, 0, 654 },
    { 29, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F68A34, 0, 810 },
    { 42, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F68A48, 0, 920 },
    { 29, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F68A5C, 0, 960 },
    { 29, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F68A70, 0, 1000 },
    { 0, 3, 0, 1, { 0, 0, 0 }, &gUnkEu_09F68A84, 0, 1340 },
    { 0, 0, 0, 1, { 0, 0, 0 }, &gUnkEu_09F68A98, 0, 1700 },
    { 1, 3, 0, 1, { 0, 0, 0 }, &gUnkEu_09F68AAC, 0, 1720 },
    { 1, 4, 0, 1, { 0, 0, 0 }, &gUnkEu_09F68AC0, 0, 1760 },
    { 2, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F68AD4, 0, 1790 },
    { 1, 4, 0, 1, { 0, 0, 0 }, &gUnkEu_09F68AE8, MSG_SCRIPT_FLAG_END, 1810 },
};
#endif

static const EventCameraKeyframe sEvent119Camera[2] = {
    { -64316, 41984, 62464, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SWAY, 0, { 0, 0 }, NULL },
    { -64236, 47104, 67584, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SWAY | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 60, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent119SoundCues[13] = {
    { 65535, 0, 0, 0 },
    { SONG_SND_387, 1, 0, 0 },
    { SONG_BGM_EVENT4, 500, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_EV_HUKUROUJUMP, 850, 0, 0 },
    { SONG_BGM_EVENT4, 1001, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_SND_387, 1020, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_PETERPAN_FIELD, 1100, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_SND_387, 1200, 0, 0 },
    { SONG_SND_387, 1650, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_SYS_PO_FALL, 1731, 0, 0 },
    { SONG_SND_354, 1750, 0, 0 },
    { SONG_SND_324, 1780, 0, 0 },
    { SONG_BGM_PETERPAN_FIELD, 1895, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent119Track0[13] = {
    { 4, 0, { 0, 0 }, 47872, 75008, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 4, 320, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 4, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 16, 505, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 601, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 30, 603, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1660, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 75, 1725, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 76, 1770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 0, 1775, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1811, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 37, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent119Track1[7] = {
    { 114, 0, { 0, 0 }, 54016, 70912, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 114, 1680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 113, 1685, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 1719, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 125, 1721, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 113, 1750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 137, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent119Track2[6] = {
    { 146, 0, { 0, 0 }, 38400, 78080, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 146, 1260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 142, 1265, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 1270, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 1811, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 166, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent119Track3[16] = {
    { 299, 0, { 0, 0 }, 32512, 65536, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 299, 130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 300, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 300, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 300, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 300, 560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateQuestionTask },
    { 299, 660, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 299, 790, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 299, 820, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 300, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 302, 850, { 0, 0 }, 40704, 61440, 0, 300, { 0, 0 }, 67, NULL, NULL },
    { 307, 860, { 0, 0 }, 40704, 61440, -2560, 299, { 0, 0 }, 4291, NULL, NULL },
    { 307, 1010, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 197, NULL, NULL },
    { 307, 1080, { 0, 0 }, 40704, 61440, -25600, 299, { 0, 0 }, 67, NULL, NULL },
    { 299, 0, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 299, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent119Track4[8] = {
    { 681, 0, { 0, 0 }, 40704, 61696, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 681, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 681, 850, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 683, 860, { 0, 0 }, 40704, 61696, -2560, 681, { 0, 0 }, 4291, NULL, NULL },
    { 683, 1010, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 197, NULL, NULL },
    { 683, 1080, { 0, 0 }, 40704, 61696, -25600, 681, { 0, 0 }, 67, NULL, NULL },
    { 681, 0, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 681, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent119Track5[12] = {
    { 455, 0, { 0, 0 }, 27392, 64512, -5632, 0, { 0, 0 }, 66, NULL, NULL },
    { 456, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 197, NULL, NULL },
    { 456, 1080, { 0, 0 }, 27392, 64512, -25600, 455, { 0, 0 }, 67, NULL, NULL },
    { 456, 1200, { 0, 0 }, 8192, 49408, -25600, 0, { 0, 0 }, 194, NULL, NULL },
    { 456, 1280, { 0, 0 }, 43520, 72448, -5632, 455, { 0, 0 }, 195, NULL, NULL },
    { 456, 1350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 197, NULL, NULL },
    { 456, 1370, { 0, 0 }, 40960, 72448, -10752, 455, { 0, 0 }, 131, NULL, NULL },
    { 456, 1550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 192, EventCharaCircleSlow, NULL },
    { 456, 1580, { 0, 0 }, 40960, 72448, -10752, 455, { 0, 0 }, 131, NULL, NULL },
    { 456, 1600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 197, NULL, NULL },
    { 458, 1680, { 0, 0 }, 8192, 49408, -25600, 459, { 0, 0 }, 131, NULL, NULL },
    { 456, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32965, NULL, NULL },
};

static const EventCharaKeyframe sEvent119Track6[6] = {
    { 260, 1730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8258, NULL, NULL },
    { 260, 1731, { 0, 0 }, 54016, 71168, -25600, 0, { 0, 0 }, 16386, NULL, NULL },
    { 260, 1750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaDrop, NULL },
    { 260, 1770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 263, 1800, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, EventCharaHop, NULL },
    { 263, 9999, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 32804, NULL, NULL },
};

static const EventCharaKeyframe sEvent119Track7[6] = {
    { 593, 1580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 595, 1581, { 0, 0 }, 45568, 61440, 0, 0, { 0, 0 }, 16658, NULL, NULL },
    { 595, 1630, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 272, NULL, CreateTinkerbellTask },
    { 595, 1660, { 0, 0 }, 45568, 66560, 0, 593, { 0, 0 }, 275, NULL, NULL },
    { 602, 1725, { 0, 0 }, 47872, 75008, 0, 0, { 0, 0 }, 274, NULL, NULL },
    { 593, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaTrack sEvent119Tracks[8] = {
    { sEvent119Track0, 0, { 0, 0, 0 } },
    { sEvent119Track1, 1, { 0, 0, 0 } },
    { sEvent119Track2, 2, { 0, 0, 0 } },
    { sEvent119Track3, 14, { 0, 0, 0 } },
    { sEvent119Track4, 62, { 0, 0, 0 } },
    { sEvent119Track5, 37, { 0, 0, 0 } },
    { sEvent119Track6, 10, { 0, 0, 0 } },
    { sEvent119Track7, 51, { 0, 0, 0 } },
};

const EventSequenceDef gEvent119 = {
    8,
    { 0, 0, 0 },
    sEvent119Tracks,
    sEvent119Camera,
    sEvent119Script,
    sEvent119SoundCues,
    NULL,
    1900,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_120_text.inc"
static const MessageScriptEntry sEvent120Script[24] = {
    { 1, 0, 0, 1, { 0, 0, 0 }, gEventTextUs_08FAD6F4, 0, 240 },
    { 6, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAD722, 0, 425 },
    { 6, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAD740, 0, 485 },
    { 6, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08FAD7EE, 0, 487 },
    { 6, 2, 4, 1, { 0, 0, 0 }, gEventTextUs_08FAD88A, 0, 489 },
    { 6, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FAD924, 0, 540 },
    { 0, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAD96E, 0, 560 },
    { 2, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAD9C2, 0, 580 },
    { 1, 1, 2, 1, { 0, 0, 0 }, gEventTextUs_08FADA62, 0, 610 },
    { 0, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FADAC4, 0, 790 },
    { 1, 3, 2, 1, { 0, 0, 0 }, gEventTextUs_08FADAD4, 0, 810 },
    { 6, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FADB1A, 0, 875 },
    { 6, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FADB5C, 0, 930 },
    { 6, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FADC04, 0, 990 },
    { 0, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FADC60, 0, 1020 },
    { 34, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FADCB0, 0, 1730 },
    { 34, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08FADDA8, 0, 1976 },
    { 34, 3, 4, 1, { 0, 0, 0 }, gEventTextUs_08FADE12, 0, 1978 },
    { 35, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FADEFC, MSG_SCRIPT_FLAG_SILHOUETTE, 1985 },
    { 34, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FADF32, 0, 2025 },
    { 34, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FADF78, 0, 2175 },
    { 34, 2, 4, 1, { 0, 0, 0 }, gEventTextUs_08FAE014, 0, 2177 },
    { 35, 0, 0, 1, { 0, 0, 0 }, gEventTextUs_08FAE060, 0, 2207 },
    { 34, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FAE0B8, MSG_SCRIPT_FLAG_END, 2237 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent120Script[24] = {
    { 1, 0, 0, 3, { 0, 0, 0 }, gEventTextJp_08F99C74, 0, 240 },
    { 6, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F99C64, 0, 425 },
    { 6, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F99C20, 0, 485 },
    { 6, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F99BD4, 0, 487 },
    { 6, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08F99B90, 0, 489 },
    { 6, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F99B68, 0, 540 },
    { 0, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F99B3C, 0, 560 },
    { 2, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F99AFC, 0, 580 },
    { 1, 1, 2, 3, { 0, 0, 0 }, gEventTextJp_08F99AD0, 0, 610 },
    { 0, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F99AC4, 0, 790 },
    { 1, 3, 2, 3, { 0, 0, 0 }, gEventTextJp_08F99A9C, 0, 810 },
    { 6, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F99A7C, 0, 875 },
    { 6, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F99A3C, 0, 930 },
    { 6, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F99A1C, 0, 990 },
    { 0, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F99A04, 0, 1020 },
    { 34, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F999AC, 0, 1730 },
    { 34, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F99980, 0, 1976 },
    { 34, 3, 4, 3, { 0, 0, 0 }, gEventTextJp_08F9992C, 0, 1978 },
    { 35, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9990C, MSG_SCRIPT_FLAG_SILHOUETTE, 1985 },
    { 34, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F998F0, 0, 2025 },
    { 34, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F998A4, 0, 2175 },
    { 34, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08F99880, 0, 2177 },
    { 35, 0, 0, 3, { 0, 0, 0 }, gEventTextJp_08F99850, 0, 2207 },
    { 34, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F99840, MSG_SCRIPT_FLAG_END, 2237 },
};

#include "event_120_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent120Script[24] = {
    { 1, 0, 0, 1, { 0, 0, 0 }, &gUnkEu_09F5F4AC, 0, 240 },
    { 6, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5F4C0, 0, 425 },
    { 6, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5F4D4, 0, 485 },
    { 6, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5F4E8, 0, 487 },
    { 6, 2, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5F4FC, 0, 489 },
    { 6, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5F510, 0, 540 },
    { 0, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5F524, 0, 560 },
    { 2, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5F538, 0, 580 },
    { 1, 1, 2, 1, { 0, 0, 0 }, &gUnkEu_09F5F54C, 0, 610 },
    { 0, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5F560, 0, 790 },
    { 1, 3, 2, 1, { 0, 0, 0 }, &gUnkEu_09F5F574, 0, 810 },
    { 6, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5F588, 0, 875 },
    { 6, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5F59C, 0, 930 },
    { 6, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5F5B0, 0, 990 },
    { 0, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5F5C4, 0, 1020 },
    { 34, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5F5D8, 0, 1730 },
    { 34, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5F5EC, 0, 1976 },
    { 34, 3, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5F600, 0, 1978 },
    { 35, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5F614, MSG_SCRIPT_FLAG_SILHOUETTE, 1985 },
    { 34, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5F628, 0, 2025 },
    { 34, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5F63C, 0, 2175 },
    { 34, 2, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5F650, 0, 2177 },
    { 35, 0, 0, 1, { 0, 0, 0 }, &gUnkEu_09F5F664, 0, 2207 },
    { 34, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5F678, MSG_SCRIPT_FLAG_END, 2237 },
};
#endif

static const EvSoundCue sEvent120SoundCues[5] = {
    { SONG_BGM_HERCULES_FIELD, 0, 0, 0 },
    { SONG_BGM_HERCULES_FIELD, 1300, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT_UNREST, 1500, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BTL_HA_IKARI, 1945, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 2450, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent120Camera[3] = {
    { -65536, 31232, 30976, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, NULL },
    { -65276, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 80, { 0, 0 }, NULL },
    { -55537, 31232, 21760, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent120Track0[24] = {
    { 4, 1, { 0, 0 }, 12288, 50176, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 9, 160, { 0, 0 }, 57088, 25600, 0, 4, { 0, 0 }, 67, NULL, NULL },
    { 4, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 0, 185, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 195, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 12, 320, { 0, 0 }, 34304, 32512, 0, 2, { 0, 0 }, 35, NULL, NULL },
    { 3, 325, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 34, 590, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 612, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 615, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 640, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 2, 880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 885, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1015, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 30, 1022, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1090, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 0, 1095, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1100, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 14, 1400, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 4, 9999, { 0, 0 }, 77056, 11264, 0, 0, { 0, 0 }, 98370, NULL, NULL },
};

static const EventCharaKeyframe sEvent120Track1[26] = {
    { 114, 1, { 0, 0 }, 21504, 51200, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 119, 80, { 0, 0 }, 38400, 41728, 0, 114, { 0, 0 }, 67, NULL, NULL },
    { 114, 100, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 110, 105, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 119, 150, { 0, 0 }, 31232, 37632, 0, 114, { 0, 0 }, 3, NULL, NULL },
    { 114, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateQuestionTask },
    { 114, 235, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 126, 242, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 119, 280, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 114, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 110, 555, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 590, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 127, 605, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 128, 792, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 129, 803, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 808, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 126, 812, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 890, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 110, 895, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 1035, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 110, 1040, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 1150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 120, 1405, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 114, 9999, { 0, 0 }, 77824, 12800, 0, 0, { 0, 0 }, 98370, NULL, NULL },
};

static const EventCharaKeyframe sEvent120Track2[21] = {
    { 146, 1, { 0, 0 }, 3840, 49408, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 151, 160, { 0, 0 }, 48640, 24832, 0, 146, { 0, 0 }, 67, NULL, NULL },
    { 146, 185, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 195, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 143, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 270, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 152, 330, { 0, 0 }, 36608, 26368, 0, 144, { 0, 0 }, 35, NULL, NULL },
    { 144, 340, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 145, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 572, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 164, 582, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 885, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 145, 1050, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 1060, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 143, 1070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 1080, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 1090, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 1135, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 153, 1410, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 146, 9999, { 0, 0 }, 79360, 10240, 0, 0, { 0, 0 }, 98370, NULL, NULL },
};

static const EventCharaKeyframe sEvent120Track3[20] = {
    { 231, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 231, 362, { 0, 0 }, 33792, 31232, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 234, 390, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, EventCharaHop, NULL },
    { 232, 410, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 231, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 234, 460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaHop, NULL },
    { 231, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 231, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 229, 820, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 231, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 231, 840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 234, 870, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaHop, NULL },
    { 231, 890, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 231, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 229, 950, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 231, 1025, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 229, 1030, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 230, 1050, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 233, 1080, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, EventCharaHop, NULL },
    { 229, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98370, NULL, NULL },
};

static const EventCharaKeyframe sEvent120Track4[6] = {
    { 348, 2044, { 0, 0 }, 66560, 43264, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 348, 2045, { 0, 0 }, 66560, 43264, 0, 0, { 0, 0 }, 16386, NULL, NULL },
    { 349, 2145, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 348, 2295, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 348, 2315, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 349, 9999, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 32836, NULL, NULL },
};

static const EventCharaKeyframe sEvent120Track5[13] = {
    { 396, 1499, { 0, 0 }, 68096, 49408, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 396, 1500, { 0, 0 }, 68096, 49408, 0, 0, { 0, 0 }, 16386, NULL, NULL },
    { 398, 1700, { 0, 0 }, 24832, 26112, 0, 396, { 0, 0 }, 3, NULL, NULL },
    { 396, 1725, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 395, 1760, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 395, 1890, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 395, 1910, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 401, 1945, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 401, 1990, { 0, 0 }, 256000, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 403, 1995, { 0, 0 }, 24832, 26112, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 395, 2005, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 395, 2425, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 396, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent120Track6[4] = {
    { 395, 1910, { 0, 0 }, 256000, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 401, 1945, { 0, 0 }, 24832, 26112, 0, 0, { 0, 0 }, 16386, NULL, NULL },
    { 402, 1990, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 395, 9999, { 0, 0 }, 256000, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent120Track7[3] = {
    { 404, 1910, { 0, 0 }, 256000, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 404, 1974, { 0, 0 }, 24832, 26112, 0, 0, { 0, 0 }, 16386, NULL, NULL },
    { 404, 9999, { 0, 0 }, 256000, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaTrack sEvent120Tracks[8] = {
    { sEvent120Track0, 0, { 0, 0, 0 } },
    { sEvent120Track1, 1, { 0, 0, 0 } },
    { sEvent120Track2, 2, { 0, 0, 0 } },
    { sEvent120Track3, 8, { 0, 0, 0 } },
    { sEvent120Track4, 19, { 0, 0, 0 } },
    { sEvent120Track5, 25, { 0, 0, 0 } },
    { sEvent120Track6, 26, { 0, 0, 0 } },
    { sEvent120Track7, 27, { 0, 0, 0 } },
};

const EventSequenceDef gEvent120 = {
    8,
    { 0, 0, 0 },
    sEvent120Tracks,
    sEvent120Camera,
    sEvent120Script,
    sEvent120SoundCues,
    NULL,
    2455,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    1,
    255,
    255,
};

#ifdef VERSION_US
#include "event_121_text.inc"
static const MessageScriptEntry sEvent121Script[34] = {
    { 45, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAF488, 0, 190 },
    { 0, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FAF522, 0, 220 },
    { 45, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAF582, 0, 250 },
    { 1, 0, 2, 1, { 0, 0, 0 }, gEventTextUs_08FAF620, 0, 280 },
    { 45, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAF632, 0, 310 },
    { 45, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08FAF648, 0, 312 },
    { 0, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FAF66C, 0, 342 },
    { 2, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FAF688, 0, 372 },
    { 0, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FAF6BE, 0, 402 },
    { 46, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAF75A, 0, 530 },
    { 45, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FAF7EC, 0, 560 },
    { 46, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAF846, 0, 590 },
    { 0, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08FAF8A0, 0, 675 },
    { 46, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAF8D0, 0, 760 },
    { 0, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FAF956, 0, 790 },
    { 0, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FAF974, 0, 810 },
    { 45, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAFA34, 0, 1030 },
    { 0, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FAFABC, 0, 1060 },
    { 45, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAFAE6, 0, 1120 },
    { 35, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FAFB8C, 0, 1170 },
    { 35, 0, 2, 1, { 0, 0, 0 }, gEventTextUs_08FAFBA6, 0, 1300 },
    { 45, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAFC08, 0, 1330 },
    { 45, 2, 4, 1, { 0, 0, 0 }, gEventTextUs_08FAFC34, 0, 1332 },
    { 46, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAFC92, 0, 1370 },
    { 0, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FAFD16, 0, 1410 },
    { 0, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAFD7A, 0, 1480 },
    { 35, 2, 2, 1, { 0, 0, 0 }, gEventTextUs_08FAFDAA, 0, 1540 },
    { 45, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAFDBE, 0, 1590 },
    { 45, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FAFE5C, 0, 1660 },
    { 45, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08FAFEC6, 0, 1662 },
    { 45, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08FAFF4E, 0, 1664 },
    { 45, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08FAFFCC, 0, 1666 },
    { 45, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB0062, 0, 1860 },
    { 45, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB00DA, MSG_SCRIPT_FLAG_END, 2060 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent121Script[34] = {
    { 45, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9B69C, 0, 190 },
    { 0, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9B678, 0, 220 },
    { 45, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9B634, 0, 250 },
    { 1, 0, 2, 3, { 0, 0, 0 }, gEventTextJp_08F76D44, 0, 280 },
    { 45, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9B624, 0, 310 },
    { 45, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F9B5F8, 0, 312 },
    { 0, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9B5E4, 0, 342 },
    { 2, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9B5CC, 0, 372 },
    { 0, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9B584, 0, 402 },
    { 46, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9B538, 0, 530 },
    { 45, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9B508, 0, 560 },
    { 46, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9B4E0, 0, 590 },
    { 0, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9B4CC, 0, 675 },
    { 46, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9B474, 0, 760 },
    { 0, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9B468, 0, 790 },
    { 0, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9B418, 0, 810 },
    { 45, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9B3DC, 0, 1030 },
    { 0, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9B3C0, 0, 1060 },
    { 45, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9B378, 0, 1120 },
    { 35, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9B368, 0, 1170 },
    { 35, 0, 2, 3, { 0, 0, 0 }, gEventTextJp_08F9B344, 0, 1300 },
    { 45, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9B330, 0, 1330 },
    { 45, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08F9B300, 0, 1332 },
    { 46, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9B2D8, 0, 1370 },
    { 0, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9B2C0, 0, 1410 },
    { 0, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9B2B0, 0, 1480 },
    { 35, 2, 2, 3, { 0, 0, 0 }, gEventTextJp_08F9B2A4, 0, 1540 },
    { 45, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9B274, 0, 1590 },
    { 45, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9B224, 0, 1660 },
    { 45, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F9B1D8, 0, 1662 },
    { 45, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F9B198, 0, 1664 },
    { 45, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F9B148, 0, 1666 },
    { 45, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9B130, 0, 1860 },
    { 45, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9B124, MSG_SCRIPT_FLAG_END, 2060 },
};

#include "event_121_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent121Script[34] = {
    { 45, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5F68C, 0, 190 },
    { 0, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5F6A0, 0, 220 },
    { 45, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5F6B4, 0, 250 },
    { 1, 0, 2, 1, { 0, 0, 0 }, &gUnkEu_09F5F6C8, 0, 280 },
    { 45, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5F6DC, 0, 310 },
    { 45, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5F6F0, 0, 312 },
    { 0, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5F704, 0, 342 },
    { 2, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5F718, 0, 372 },
    { 0, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5F72C, 0, 402 },
    { 46, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5F740, 0, 530 },
    { 45, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5F754, 0, 560 },
    { 46, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5F768, 0, 590 },
    { 0, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5F77C, 0, 675 },
    { 46, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5F790, 0, 760 },
    { 0, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5F7A4, 0, 790 },
    { 0, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5F7B8, 0, 810 },
    { 45, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5F7CC, 0, 1030 },
    { 0, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5F7E0, 0, 1060 },
    { 45, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5F7F4, 0, 1120 },
    { 35, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5F808, 0, 1170 },
    { 35, 0, 2, 1, { 0, 0, 0 }, &gUnkEu_09F5F81C, 0, 1300 },
    { 45, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5F830, 0, 1330 },
    { 45, 2, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5F844, 0, 1332 },
    { 46, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5F858, 0, 1370 },
    { 0, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5F86C, 0, 1410 },
    { 0, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5F880, 0, 1480 },
    { 35, 2, 2, 1, { 0, 0, 0 }, &gUnkEu_09F5F894, 0, 1540 },
    { 45, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5F8A8, 0, 1590 },
    { 45, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5F8BC, 0, 1660 },
    { 45, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5F8D0, 0, 1662 },
    { 45, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5F8E4, 0, 1664 },
    { 45, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5F8F8, 0, 1666 },
    { 45, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5F90C, 0, 1860 },
    { 45, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5F920, MSG_SCRIPT_FLAG_END, 2060 },
};
#endif

static const EventCameraKeyframe sEvent121Camera[3] = {
    { -63836, 49664, 35072, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -63436, 46848, 30720, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 70, { 0, 0 }, NULL },
    { -60536, 65024, 20736, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 200, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent121SoundCues[2] = {
    { SONG_BGM_HERCULES_FIELD, 0, 0, 0 },
    { SONG_BGM_HERCULES_FIELD, 2095, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent121Track0[33] = {
    { 4, 1, { 0, 0 }, 6400, 62464, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 9, 120, { 0, 0 }, 46592, 41728, 0, 4, { 0, 0 }, 67, NULL, NULL },
    { 4, 339, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 30, 362, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 387, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 30, 495, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 4, 670, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 30, 785, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 805, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 36, 1040, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 1190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 1240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 4, 1250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 0, 1255, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 1265, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 1375, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 1380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1385, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 0, 1390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1440, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 1445, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 0, 1450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1455, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 1460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 1610, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 1615, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1620, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 0, 1625, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 2070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 14, 5000, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 32868, NULL, NULL },
};

static const EventCharaKeyframe sEvent121Track1[21] = {
    { 114, 1, { 0, 0 }, 14848, 66560, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 119, 115, { 0, 0 }, 47104, 48384, 0, 114, { 0, 0 }, 67, NULL, NULL },
    { 114, 275, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 126, 282, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 1190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 1240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 114, 1250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 113, 1255, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 112, 1260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 111, 1265, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 1380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 113, 1385, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 1390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 110, 1615, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 1730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 110, 1735, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 1740, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 119, 1790, { 0, 0 }, 41984, 45568, 0, 114, { 0, 0 }, 3, NULL, NULL },
    { 110, 1795, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 2075, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 120, 5000, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 32868, NULL, NULL },
};

static const EventCharaKeyframe sEvent121Track2[24] = {
    { 146, 1, { 0, 0 }, 3840, 59392, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 151, 125, { 0, 0 }, 37632, 40448, 0, 146, { 0, 0 }, 67, NULL, NULL },
    { 146, 367, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 165, 375, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 1190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 1240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 146, 1250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 142, 1255, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 1260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 145, 1265, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 1383, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 143, 1388, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 1393, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 1625, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 1740, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 1745, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 1750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 143, 1755, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 1760, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 149, 1780, { 0, 0 }, 32512, 42752, 0, 144, { 0, 0 }, 3, NULL, NULL },
    { 149, 1800, { 0, 0 }, 35584, 47616, 0, 144, { 0, 0 }, 67, NULL, NULL },
    { 145, 1805, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 2090, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 153, 5000, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 32868, NULL, NULL },
};

static const EventCharaKeyframe sEvent121Track3[25] = {
    { 381, 100, { 0, 0 }, 54784, 36864, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 381, 110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 381, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 381, 305, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 385, 314, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 381, 540, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 381, 740, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 381, 840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 382, 850, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 382, 880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 382, 1010, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 382, 1080, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 382, 1090, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 381, 1100, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 381, 1190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 381, 1240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 381, 1655, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 385, 1668, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 381, 1690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 382, 1710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 384, 1800, { 0, 0 }, 35840, 29952, 0, 382, { 0, 0 }, 3, NULL, NULL },
    { 381, 1810, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 381, 2060, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 386, 2062, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 381, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent121Track4[12] = {
    { 388, 405, { 0, 0 }, 96256, 59904, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 390, 500, { 0, 0 }, 62976, 40192, 0, 388, { 0, 0 }, 3, NULL, NULL },
    { 388, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 387, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 387, 1190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 387, 1240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 387, 1610, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 388, 1720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 389, 1795, { 0, 0 }, 53248, 45824, 0, 387, { 0, 0 }, 3, NULL, NULL },
    { 388, 1805, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 388, 2065, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 391, 5000, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 32868, NULL, NULL },
};

static const EventCharaKeyframe sEvent121Track5[9] = {
    { 348, 1180, { 0, 0 }, 5888, 63488, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 349, 1270, { 0, 0 }, 34304, 48384, 0, 348, { 0, 0 }, 67, NULL, NULL },
    { 348, 1720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 348, 1730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 349, 1760, { 0, 0 }, 23808, 41728, 0, 348, { 0, 0 }, 3, NULL, NULL },
    { 348, 1790, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 349, 1840, { 0, 0 }, 41984, 37888, 0, 348, { 0, 0 }, 67, NULL, NULL },
    { 348, 2065, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 352, 5000, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 32868, NULL, NULL },
};

static const EventCharaTrack sEvent121Tracks[6] = {
    { sEvent121Track0, 0, { 0, 0, 0 } },
    { sEvent121Track1, 1, { 0, 0, 0 } },
    { sEvent121Track2, 2, { 0, 0, 0 } },
    { sEvent121Track3, 23, { 0, 0, 0 } },
    { sEvent121Track4, 24, { 0, 0, 0 } },
    { sEvent121Track5, 19, { 0, 0, 0 } },
};

const EventSequenceDef gEvent121 = {
    6,
    { 0, 0, 0 },
    sEvent121Tracks,
    sEvent121Camera,
    sEvent121Script,
    sEvent121SoundCues,
    NULL,
    2100,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_122_text.inc"
static const MessageScriptEntry sEvent122Script[16] = {
    { 2, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB1654, 0, 170 },
    { 1, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB16C6, 0, 200 },
    { 0, 2, 2, 1, { 0, 0, 0 }, gEventTextUs_08FB1780, 0, 260 },
    { 35, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB17C4, 0, 310 },
    { 2, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB1860, 0, 440 },
    { 1, 0, 0, 1, { 0, 0, 0 }, gEventTextUs_08FB18B2, 0, 470 },
    { 0, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB193E, 0, 500 },
    { 0, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB196E, 0, 780 },
    { 35, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB199A, 0, 830 },
    { 35, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08FB19EC, 0, 860 },
    { 0, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB1A40, 0, 940 },
    { 35, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB1AA4, 0, 970 },
    { 35, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB1B0E, 0, 1220 },
    { 0, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB1B52, 0, 1250 },
    { 0, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08FB1BC4, 0, 1252 },
    { 35, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB1C2E, MSG_SCRIPT_FLAG_END, 1440 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent122Script[16] = {
    { 2, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9CD20, 0, 170 },
    { 1, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9CCD0, 0, 200 },
    { 0, 2, 2, 3, { 0, 0, 0 }, gEventTextJp_08F9CCA8, 0, 260 },
    { 35, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9CC68, 0, 310 },
    { 2, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9CC40, 0, 440 },
    { 1, 0, 0, 3, { 0, 0, 0 }, gEventTextJp_08F9CC08, 0, 470 },
    { 0, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9CBF0, 0, 500 },
    { 0, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9CBD4, 0, 780 },
    { 35, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9CB94, 0, 830 },
    { 35, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F9CB7C, 0, 860 },
    { 0, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9CB64, 0, 940 },
    { 35, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9CB20, 0, 970 },
    { 35, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9CB0C, 0, 1220 },
    { 0, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9CADC, 0, 1250 },
    { 0, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F9CAA4, 0, 1252 },
    { 35, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9CA94, MSG_SCRIPT_FLAG_END, 1440 },
};

#include "event_122_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent122Script[16] = {
    { 2, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5F970, 0, 170 },
    { 1, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5F984, 0, 200 },
    { 0, 2, 2, 1, { 0, 0, 0 }, &gUnkEu_09F5F998, 0, 260 },
    { 35, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5F9AC, 0, 310 },
    { 2, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5F9C0, 0, 440 },
    { 1, 0, 0, 1, { 0, 0, 0 }, &gUnkEu_09F5F9D4, 0, 470 },
    { 0, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5F9E8, 0, 500 },
    { 0, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5F9FC, 0, 780 },
    { 35, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5FA10, 0, 830 },
    { 35, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5FA24, 0, 860 },
    { 0, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5FA38, 0, 940 },
    { 35, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5FA4C, 0, 970 },
    { 35, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5FA60, 0, 1220 },
    { 0, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5FA74, 0, 1250 },
    { 0, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5FA88, 0, 1252 },
    { 35, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5FA9C, MSG_SCRIPT_FLAG_END, 1440 },
};
#endif

static const EvSoundCue sEvent122SoundCues[3] = {
    { SONG_BGM_HERCULES_FIELD, 0, 0, 0 },
    { SONG_BGM_HERCULES_FIELD, 600, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT1, 880, EV_SOUND_FLAG_FADE_IN | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent122Camera[3] = {
    { -65326, 46592, 31232, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64986, 52224, 31232, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -60536, 73216, 38656, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 210, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent122Track0[21] = {
    { 2, 1, { 0, 0 }, 15104, 21504, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 12, 100, { 0, 0 }, 39424, 38912, 0, 2, { 0, 0 }, 99, NULL, NULL },
    { 3, 255, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 18, 325, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 24, 375, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 24, 390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 23, 401, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 495, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 32, 530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 535, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 7, 640, { 0, 0 }, 74752, 47360, 0, 2, { 0, 0 }, 67, NULL, NULL },
    { 2, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 1, 655, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 660, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 870, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 920, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 4, 935, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 27, 972, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1040, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 19, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent122Track1[32] = {
    { 112, 1, { 0, 0 }, 5376, 20736, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 121, 110, { 0, 0 }, 29952, 38144, 0, 112, { 0, 0 }, 99, NULL, NULL },
    { 112, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 113, 185, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 195, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 126, 202, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 113, 207, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 121, 239, { 0, 0 }, 45312, 46592, 0, 112, { 0, 0 }, 99, NULL, NULL },
    { 113, 244, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 270, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 122, 285, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 123, 395, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 124, 410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 455, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 110, 460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 465, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 126, 472, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 110, 535, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 540, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 113, 545, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 117, 670, { 0, 0 }, 88576, 61696, 0, 112, { 0, 0 }, 67, NULL, NULL },
    { 111, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 111, 685, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 113, 695, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 119, 740, { 0, 0 }, 79616, 56576, 0, 114, { 0, 0 }, 3, NULL, NULL },
    { 114, 870, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 920, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 114, 1280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 122, 1295, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 123, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent122Track2[25] = {
    { 146, 1, { 0, 0 }, 15872, 13312, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 152, 120, { 0, 0 }, 39168, 31744, 0, 144, { 0, 0 }, 99, NULL, NULL },
    { 144, 157, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 143, 162, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 167, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 164, 172, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 143, 245, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 270, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 154, 285, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 155, 385, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 156, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 437, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 164, 442, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 149, 725, { 0, 0 }, 85504, 49664, 0, 144, { 0, 0 }, 67, NULL, NULL },
    { 144, 735, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 740, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 745, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 142, 750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 870, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 920, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 146, 1280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 157, 1295, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 158, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent122Track3[4] = {
    { 344, 800, { 0, 0 }, 60672, 34048, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 348, 1110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 344, 1115, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 344, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent122Tracks[4] = {
    { sEvent122Track0, 0, { 0, 0, 0 } },
    { sEvent122Track1, 1, { 0, 0, 0 } },
    { sEvent122Track2, 2, { 0, 0, 0 } },
    { sEvent122Track3, 19, { 0, 0, 0 } },
};

const EventSequenceDef gEvent122 = {
    4,
    { 0, 0, 0 },
    sEvent122Tracks,
    sEvent122Camera,
    sEvent122Script,
    sEvent122SoundCues,
    NULL,
    1500,
    0,
    1,
    0,
    0,
    0,
    0,
    159,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_123_text.inc"
static const MessageScriptEntry sEvent123Script[3] = {
    { 0, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB2A18, 0, 300 },
    { 6, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB2A40, 0, 380 },
    { 0, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB2AB4, MSG_SCRIPT_FLAG_END, 420 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent123Script[3] = {
    { 0, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9DA24, 0, 300 },
    { 6, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9D9F4, 0, 380 },
    { 0, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9D9E8, MSG_SCRIPT_FLAG_END, 420 },
};

#include "event_123_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent123Script[3] = {
    { 0, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5F934, 0, 300 },
    { 6, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5F948, 0, 380 },
    { 0, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5F95C, MSG_SCRIPT_FLAG_END, 420 },
};
#endif

static const EvSoundCue sEvent123SoundCues[2] = {
    { SONG_BGM_EVENT1, 0, 0, 0 },
    { SONG_BGM_EVENT1, 515, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent123Camera[1] = {
    { -60536, 68096, 38656, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent123Track0[17] = {
    { 21, 150, { 0, 0 }, 61440, 40192, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 22, 165, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 0, 225, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 235, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 245, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 255, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 0, 265, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 299, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 30, 302, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 405, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 16, 415, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 495, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 505, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 1, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 12, 999, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 32868, NULL, NULL },
};

static const EventCharaKeyframe sEvent123Track1[11] = {
    { 123, 150, { 0, 0 }, 65792, 50176, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 124, 165, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 223, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 233, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 111, 243, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 253, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 111, 263, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 273, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 113, 390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 112, 520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 121, 999, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 32868, NULL, NULL },
};

static const EventCharaKeyframe sEvent123Track2[12] = {
    { 158, 150, { 0, 0 }, 75776, 43776, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 159, 165, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 142, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 143, 270, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 152, 999, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 32868, NULL, NULL },
};

static const EventCharaKeyframe sEvent123Track3[8] = {
    { 229, 334, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 231, 335, { 0, 0 }, 60672, 39936, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 234, 370, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, EventCharaHop, NULL },
    { 231, 372, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 233, 385, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaHop, NULL },
    { 229, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 233, 480, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 100, EventCharaHop, NULL },
    { 229, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32834, NULL, NULL },
};

static const EventCharaTrack sEvent123Tracks[4] = {
    { sEvent123Track0, 0, { 0, 0, 0 } },
    { sEvent123Track1, 1, { 0, 0, 0 } },
    { sEvent123Track2, 2, { 0, 0, 0 } },
    { sEvent123Track3, 8, { 0, 0, 0 } },
};

const EventSequenceDef gEvent123 = {
    4,
    { 0, 0, 0 },
    sEvent123Tracks,
    sEvent123Camera,
    sEvent123Script,
    sEvent123SoundCues,
    NULL,
    520,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_124_text.inc"
static const MessageScriptEntry sEvent124Script[27] = {
    { 46, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB324C, 0, 130 },
    { 35, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB3286, 0, 200 },
    { 46, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB32AE, 0, 240 },
    { 35, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB3322, 0, 280 },
    { 46, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB33B4, 0, 300 },
    { 0, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB33C0, 0, 410 },
    { 46, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB33FE, 0, 430 },
    { 35, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB340A, 0, 450 },
    { 0, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB34A8, 0, 520 },
    { 34, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB34C6, 0, 570 },
    { 46, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB352C, 0, 700 },
    { 34, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB3546, 0, 810 },
    { 34, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08FB3640, 0, 812 },
    { 35, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB36C0, 0, 900 },
    { 34, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB3700, 0, 960 },
    { 35, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB37B0, 0, 990 },
    { 34, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB37C4, 0, 1040 },
    { 0, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB384E, 0, 1200 },
    { 34, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB385A, 0, 1230 },
    { 46, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB38BC, 0, 1260 },
    { 34, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB3914, 0, 1350 },
    { 34, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08FB3998, 0, 1352 },
    { 34, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08FB39BA, 0, 1354 },
    { 0, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB3A68, 0, 1390 },
    { 46, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB3A8C, 0, 1650 },
    { 0, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB3AA0, 0, 1680 },
    { 34, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB3B28, MSG_SCRIPT_FLAG_END, 1720 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent124Script[27] = {
    { 46, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9E7D0, 0, 130 },
    { 35, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9E7C4, 0, 200 },
    { 46, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9E794, 0, 240 },
    { 35, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9E758, 0, 280 },
    { 46, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9E74C, 0, 300 },
    { 0, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9E730, 0, 410 },
    { 46, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9E724, 0, 430 },
    { 35, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9E6E0, 0, 450 },
    { 0, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9E6D0, 0, 520 },
    { 34, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9E69C, 0, 570 },
    { 46, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9E690, 0, 700 },
    { 34, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9E640, 0, 810 },
    { 34, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F9E620, 0, 812 },
    { 35, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9E608, 0, 900 },
    { 34, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9E5B4, 0, 960 },
    { 35, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9E5A0, 0, 990 },
    { 34, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9E57C, 0, 1040 },
    { 0, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08F781F8, 0, 1200 },
    { 34, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9E550, 0, 1230 },
    { 46, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9E520, 0, 1260 },
    { 34, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9E4D0, 0, 1350 },
    { 34, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F9E4BC, 0, 1352 },
    { 34, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F9E478, 0, 1354 },
    { 0, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9E46C, 0, 1390 },
    { 46, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9E458, 0, 1650 },
    { 0, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9E418, 0, 1680 },
    { 34, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9E400, MSG_SCRIPT_FLAG_END, 1720 },
};

#include "event_124_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent124Script[27] = {
    { 46, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5FC68, 0, 130 },
    { 35, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5FC7C, 0, 200 },
    { 46, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5FC90, 0, 240 },
    { 35, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5FCA4, 0, 280 },
    { 46, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5FCB8, 0, 300 },
    { 0, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5FCCC, 0, 410 },
    { 46, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5FCE0, 0, 430 },
    { 35, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5FCF4, 0, 450 },
    { 0, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5FD08, 0, 520 },
    { 34, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5FD1C, 0, 570 },
    { 46, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5FD30, 0, 700 },
    { 34, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5FD44, 0, 810 },
    { 34, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5FD58, 0, 812 },
    { 35, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5FD6C, 0, 900 },
    { 34, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5FD80, 0, 960 },
    { 35, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5FD94, 0, 990 },
    { 34, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5FDA8, 0, 1040 },
    { 0, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5FDBC, 0, 1200 },
    { 34, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5FDD0, 0, 1230 },
    { 46, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5FDE4, 0, 1260 },
    { 34, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5FDF8, 0, 1350 },
    { 34, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5FE0C, 0, 1352 },
    { 34, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5FE20, 0, 1354 },
    { 0, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5FE34, 0, 1390 },
    { 46, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5FE48, 0, 1650 },
    { 0, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5FE5C, 0, 1680 },
    { 34, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5FE70, MSG_SCRIPT_FLAG_END, 1720 },
};
#endif

static const EvSoundCue sEvent124SoundCues[5] = {
    { SONG_BGM_EVENT2, 0, 0, 0 },
    { SONG_BGM_EVENT2, 540, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT_UNREST, 571, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT_UNREST, 1360, 0, 0 },
    { SONG_BGM_EVENT2, 1390, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent124Camera[6] = {
    { -65535, 32768, 76032, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64831, 65280, 57088, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 100, { 0, 0 }, NULL },
    { -64443, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64406, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_MEDIUM | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64366, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_SMALL | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EventBgEffectEntry sEvent124BgEffects[4] = {
    { 1050, 0, 0, 0, 0 },
    { 1080, 0, 0, 0, 0x4 },
    { 1232, 0, 0, 0, 0x2 },
    { 1292, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent124Track0[24] = {
    { 4, 1, { 0, 0 }, 19456, 86784, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 14, 110, { 0, 0 }, 70912, 66560, 0, 4, { 0, 0 }, 99, NULL, NULL },
    { 4, 310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 315, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 320, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 14, 345, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 4, 348, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 4, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 0, 365, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 19, 460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 25, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 26, 575, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 702, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 707, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 1100, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 27, 1150, { 0, 0 }, 16384, 85248, 0, 4, { 0, 0 }, 67, NULL, NULL },
    { 4, 1115, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 1391, { 0, 0 }, 27136, 76800, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 14, 1465, { 0, 0 }, 60672, 61440, 0, 4, { 0, 0 }, 99, NULL, NULL },
    { 4, 1480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 1485, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 18, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent124Track1[15] = {
    { 114, 1, { 0, 0 }, 16640, 94464, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 120, 120, { 0, 0 }, 60928, 76544, 0, 114, { 0, 0 }, 99, NULL, NULL },
    { 114, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 110, 702, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 120, 760, { 0, 0 }, 52736, 69120, 0, 114, { 0, 0 }, 35, NULL, NULL },
    { 110, 765, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 1100, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 133, 1150, { 0, 0 }, 12288, 91136, 0, 114, { 0, 0 }, 67, NULL, NULL },
    { 114, 1391, { 0, 0 }, 33024, 87552, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 120, 1470, { 0, 0 }, 60416, 74496, 0, 114, { 0, 0 }, 99, NULL, NULL },
    { 114, 1490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 122, 1505, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 123, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent124Track2[15] = {
    { 146, 1, { 0, 0 }, 7424, 90112, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 153, 125, { 0, 0 }, 49152, 76544, 0, 146, { 0, 0 }, 99, NULL, NULL },
    { 146, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 142, 702, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 707, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 153, 750, { 0, 0 }, 46080, 66304, 0, 146, { 0, 0 }, 35, NULL, NULL },
    { 142, 755, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 1100, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 161, 1150, { 0, 0 }, 5376, 88064, 0, 146, { 0, 0 }, 67, NULL, NULL },
    { 146, 1391, { 0, 0 }, 21248, 82688, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 153, 1470, { 0, 0 }, 51200, 70656, 0, 146, { 0, 0 }, 99, NULL, NULL },
    { 146, 1490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 157, 1505, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 158, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent124Track3[7] = {
    { 346, 160, { 0, 0 }, 84480, 56576, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 347, 202, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 344, 825, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 344, 875, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 344, 1100, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 346, 1130, { 0, 0 }, 116736, 34560, 0, 344, { 0, 0 }, 3, NULL, NULL },
    { 344, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98309, NULL, NULL },
};

static const EventCharaKeyframe sEvent124Track4[6] = {
    { 392, 675, { 0, 0 }, 55552, 57088, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 387, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 394, 705, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 387, 1110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 394, 1170, { 0, 0 }, 48896, 58368, 0, 387, { 0, 0 }, 4163, NULL, NULL },
    { 393, 1620, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent124Track5[8] = {
    { 396, 572, { 0, 0 }, 103680, 86528, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 398, 685, { 0, 0 }, 76288, 65024, 0, 396, { 0, 0 }, 3, NULL, NULL },
    { 396, 760, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 396, 920, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 395, 1060, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 399, 1107, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 400, 1275, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 395, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent124Track6[3] = {
    { 922, 1100, { 0, 0 }, 256000, 57088, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 922, 1126, { 0, 0 }, 76288, 57088, 0, 0, { 0, 0 }, 16658, NULL, NULL },
    { 922, 9999, { 0, 0 }, 256000, 57088, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent124Track7[3] = {
    { 923, 1100, { 0, 0 }, 256000, 57088, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 923, 1165, { 0, 0 }, 76288, 65024, 0, 0, { 0, 0 }, 16658, NULL, NULL },
    { 923, 9999, { 0, 0 }, 256000, 57088, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaTrack sEvent124Tracks[8] = {
    { sEvent124Track0, 0, { 0, 0, 0 } },
    { sEvent124Track1, 1, { 0, 0, 0 } },
    { sEvent124Track2, 2, { 0, 0, 0 } },
    { sEvent124Track3, 19, { 0, 0, 0 } },
    { sEvent124Track4, 24, { 0, 0, 0 } },
    { sEvent124Track5, 25, { 0, 0, 0 } },
    { sEvent124Track6, 89, { 0, 0, 0 } },
    { sEvent124Track7, 90, { 0, 0, 0 } },
};

const EventSequenceDef gEvent124 = {
    8,
    { 0, 0, 0 },
    sEvent124Tracks,
    sEvent124Camera,
    sEvent124Script,
    sEvent124SoundCues,
    sEvent124BgEffects,
    1800,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    125,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_125_text.inc"
static const MessageScriptEntry sEvent125Script[1] = {
    { 34, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB4B20, MSG_SCRIPT_FLAG_END, 200 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent125Script[1] = {
    { 34, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9F510, MSG_SCRIPT_FLAG_END, 200 },
};

#include "event_125_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent125Script[1] = {
    { 34, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5FAB0, MSG_SCRIPT_FLAG_END, 200 },
};
#endif

static const EvSoundCue sEvent125SoundCues[1] = {
    { SONG_BGM_EVENT2, 0, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent125Camera[1] = {
    { -55537, 65536, 103168, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent125Track0[2] = {
    { 21, 1, { 0, 0 }, 55040, 116992, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 21, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent125Track1[2] = {
    { 395, 1, { 0, 0 }, 76032, 110848, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 395, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent125Tracks[2] = {
    { sEvent125Track0, 0, { 0, 0, 0 } },
    { sEvent125Track1, 25, { 0, 0, 0 } },
};

const EventSequenceDef gEvent125 = {
    2,
    { 0, 0, 0 },
    sEvent125Tracks,
    sEvent125Camera,
    sEvent125Script,
    sEvent125SoundCues,
    NULL,
    300,
    0,
    1,
    0,
    0,
    0,
    0,
    160,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_126_text.inc"
static const MessageScriptEntry sEvent126Script[21] = {
    { 0, 3, 0, 1, { 0, 0, 0 }, gEventTextUs_08FB4C7C, 0, 150 },
    { 45, 1, 2, 1, { 0, 0, 0 }, gEventTextUs_08FB4CD4, 0, 180 },
    { 45, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08FB4CEE, 0, 182 },
    { 2, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB4D14, 0, 210 },
    { 0, 2, 0, 1, { 0, 0, 0 }, gEventTextUs_08FB4D58, 0, 240 },
    { 46, 4, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB4DCA, 0, 300 },
    { 46, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08FB4E5C, 0, 302 },
    { 0, 0, 2, 1, { 0, 0, 0 }, gEventTextUs_08FB4EC8, 0, 490 },
    { 46, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB4F02, 0, 520 },
    { 6, 3, 0, 1, { 0, 0, 0 }, gEventTextUs_08FB4F28, 0, 600 },
    { 0, 0, 2, 1, { 0, 0, 0 }, gEventTextUs_08FB4F72, 0, 730 },
    { 35, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB4F86, 0, 750 },
    { 35, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB4F92, 0, 810 },
    { 0, 3, 2, 1, { 0, 0, 0 }, gEventTextUs_08FB4FCE, 0, 881 },
    { 0, 1, 2, 1, { 0, 0, 0 }, gEventTextUs_08FB501C, 0, 920 },
    { 0, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08FB5058, 0, 922 },
    { 0, 5, 2, 1, { 0, 0, 0 }, gEventTextUs_08FB50F4, 0, 1030 },
    { 0, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08FB518A, 0, 1032 },
    { 35, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB51C4, 0, 1360 },
    { 0, 1, 2, 1, { 0, 0, 0 }, gEventTextUs_08FB520E, 0, 1401 },
    { 35, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB5272, MSG_SCRIPT_FLAG_END, 1480 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent126Script[21] = {
    { 0, 3, 0, 3, { 0, 0, 0 }, gEventTextJp_08F9FB04, 0, 150 },
    { 45, 1, 2, 3, { 0, 0, 0 }, gEventTextJp_08F9B624, 0, 180 },
    { 45, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F9FAE4, 0, 182 },
    { 2, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9FACC, 0, 210 },
    { 0, 2, 0, 3, { 0, 0, 0 }, gEventTextJp_08F9FA88, 0, 240 },
    { 46, 4, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9FA40, 0, 300 },
    { 46, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08F9F9E8, 0, 302 },
    { 0, 0, 2, 3, { 0, 0, 0 }, gEventTextJp_08F9F9C8, 0, 490 },
    { 46, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9F9B4, 0, 520 },
    { 6, 3, 0, 3, { 0, 0, 0 }, gEventTextJp_08F9F994, 0, 600 },
    { 0, 0, 2, 3, { 0, 0, 0 }, gEventTextJp_08F9F988, 0, 730 },
    { 35, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9F980, 0, 750 },
    { 35, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9F970, 0, 810 },
    { 0, 3, 2, 3, { 0, 0, 0 }, gEventTextJp_08F9F94C, 0, 881 },
    { 0, 1, 2, 3, { 0, 0, 0 }, gEventTextJp_08F9F920, 0, 920 },
    { 0, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F9F8D8, 0, 922 },
    { 0, 5, 2, 3, { 0, 0, 0 }, gEventTextJp_08F9F8A8, 0, 1030 },
    { 0, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08F9F894, 0, 1032 },
    { 35, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08F9F874, 0, 1360 },
    { 0, 1, 2, 3, { 0, 0, 0 }, gEventTextJp_08F9F844, 0, 1401 },
    { 35, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08F9F834, MSG_SCRIPT_FLAG_END, 1480 },
};

#include "event_126_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent126Script[21] = {
    { 0, 3, 0, 1, { 0, 0, 0 }, &gUnkEu_09F5FAC4, 0, 150 },
    { 45, 1, 2, 1, { 0, 0, 0 }, &gUnkEu_09F5FAD8, 0, 180 },
    { 45, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5FAEC, 0, 182 },
    { 2, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5FB00, 0, 210 },
    { 0, 2, 0, 1, { 0, 0, 0 }, &gUnkEu_09F5FB14, 0, 240 },
    { 46, 4, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5FB28, 0, 300 },
    { 46, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5FB3C, 0, 302 },
    { 0, 0, 2, 1, { 0, 0, 0 }, &gUnkEu_09F5FB50, 0, 490 },
    { 46, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5FB64, 0, 520 },
    { 6, 3, 0, 1, { 0, 0, 0 }, &gUnkEu_09F5FB78, 0, 600 },
    { 0, 0, 2, 1, { 0, 0, 0 }, &gUnkEu_09F5FB8C, 0, 730 },
    { 35, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5FBA0, 0, 750 },
    { 35, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5FBB4, 0, 810 },
    { 0, 3, 2, 1, { 0, 0, 0 }, &gUnkEu_09F5FBC8, 0, 881 },
    { 0, 1, 2, 1, { 0, 0, 0 }, &gUnkEu_09F5FBDC, 0, 920 },
    { 0, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5FBF0, 0, 922 },
    { 0, 5, 2, 1, { 0, 0, 0 }, &gUnkEu_09F5FC04, 0, 1030 },
    { 0, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F5FC18, 0, 1032 },
    { 35, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F5FC2C, 0, 1360 },
    { 0, 1, 2, 1, { 0, 0, 0 }, &gUnkEu_09F5FC40, 0, 1401 },
    { 35, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F5FC54, MSG_SCRIPT_FLAG_END, 1480 },
};
#endif

static const EvSoundCue sEvent126SoundCues[3] = {
    { SONG_BGM_HERCULES_FIELD, 0, 0, 0 },
    { SONG_BGM_HERCULES_FIELD, 881, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_EV_CARDTHR, 1274, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent126Camera[3] = {
    { -64916, 43264, 67072, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64686, 72192, 48384, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 100, { 0, 0 }, NULL },
    { -55537, 81152, 43520, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent126Track0[18] = {
    { 4, 145, { 0, 0 }, 44800, 77568, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 27, 181, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 235, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 30, 301, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 315, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 445, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 4, 465, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 0, 470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 640, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 14, 700, { 0, 0 }, 69632, 60928, 0, 4, { 0, 0 }, 99, NULL, NULL },
    { 4, 876, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 30, 921, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 950, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 16, 1031, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 1285, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 72, 1340, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 76, 1397, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 36, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent126Track1[3] = {
    { 114, 650, { 0, 0 }, 30464, 76288, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 120, 720, { 0, 0 }, 67072, 66560, 0, 114, { 0, 0 }, 99, NULL, NULL },
    { 114, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent126Track2[9] = {
    { 144, 205, { 0, 0 }, 46336, 65536, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 164, 212, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 143, 655, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 660, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 665, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 685, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 153, 715, { 0, 0 }, 56832, 65792, 0, 146, { 0, 0 }, 99, NULL, NULL },
    { 146, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent126Track3[6] = {
    { 381, 175, { 0, 0 }, 37376, 70912, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 385, 185, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 381, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 382, 685, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 384, 725, { 0, 0 }, 56320, 55040, 0, 382, { 0, 0 }, 67, NULL, NULL },
    { 381, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent126Track4[5] = {
    { 229, 605, { 0, 0 }, 76288, 54528, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 233, 725, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaHop, NULL },
    { 229, 770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 229, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 231, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent126Track5[16] = {
    { 346, 780, { 0, 0 }, 83968, 54016, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 347, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 344, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 348, 840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 348, 850, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 349, 880, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 348, 1060, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 348, 1190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 348, 1260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 350, 1310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 348, 1370, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 349, 1400, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 348, 1425, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 351, 1460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 348, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 349, 5000, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 32836, NULL, NULL },
};

static const EventCharaKeyframe sEvent126Track6[6] = {
    { 388, 260, { 0, 0 }, 52480, 70912, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 387, 630, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 387, 635, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 388, 640, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 391, 710, { 0, 0 }, 67584, 49408, 0, 388, { 0, 0 }, 99, NULL, NULL },
    { 387, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent126Track7[6] = {
    { 593, 1273, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 593, 1274, { 0, 0 }, 83712, 44800, 0, 0, { 0, 0 }, 16658, NULL, NULL },
    { 593, 1288, { 0, 0 }, 74496, 51712, 0, 593, { 0, 0 }, 275, NULL, NULL },
    { 593, 1291, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 274, NULL, NULL },
    { 600, 1340, { 0, 0 }, 69632, 60928, 0, 0, { 0, 0 }, 338, NULL, NULL },
    { 593, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaTrack sEvent126Tracks[8] = {
    { sEvent126Track0, 0, { 0, 0, 0 } },
    { sEvent126Track1, 1, { 0, 0, 0 } },
    { sEvent126Track2, 2, { 0, 0, 0 } },
    { sEvent126Track3, 23, { 0, 0, 0 } },
    { sEvent126Track4, 8, { 0, 0, 0 } },
    { sEvent126Track5, 19, { 0, 0, 0 } },
    { sEvent126Track6, 24, { 0, 0, 0 } },
    { sEvent126Track7, 51, { 0, 0, 0 } },
};

const EventSequenceDef gEvent126 = {
    8,
    { 0, 0, 0 },
    sEvent126Tracks,
    sEvent126Camera,
    sEvent126Script,
    sEvent126SoundCues,
    NULL,
    1500,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifndef VERSION_EU
#ifdef VERSION_US
static const MessageScriptEntry sEvent127Script[7] = {
    { 0, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB612C, 0, 150 },
    { 31, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB60F0, 0, 180 },
    { 31, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08FB60B8, 0, 185 },
    { 31, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB608C, 0, 300 },
    { 0, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB6040, 0, 330 },
    { 31, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB6010, 0, 360 },
    { 31, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08FB5FDC, MSG_SCRIPT_FLAG_END, 360 },
};

#include "event_127_text.inc"
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent127Script[7] = {
    { 0, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA07C0, 0, 150 },
    { 31, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA0784, 0, 180 },
    { 31, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08FA074C, 0, 185 },
    { 31, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA0720, 0, 300 },
    { 0, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA06D4, 0, 330 },
    { 31, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA06A4, 0, 360 },
    { 31, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08FA0670, MSG_SCRIPT_FLAG_END, 360 },
};

#include "event_127_text.inc"
#endif
static const EventCameraKeyframe sEvent127Camera[1] = {
    { -55537, 66304, 66560, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent127SoundCues[1] = {
    { SONG_BGM_TOWN_FIELD, 0, EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent127Track0[7] = {
    { 4, 100, { 0, 0 }, 57344, 75008, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 27, 182, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 235, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 285, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 4, 325, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 30, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent127Track1[1] = {
    { 114, 9999, { 0, 0 }, 63744, 78592, 0, 0, { 0, 0 }, 32834, NULL, NULL },
};

static const EventCharaKeyframe sEvent127Track2[1] = {
    { 146, 9999, { 0, 0 }, 46848, 79616, 0, 0, { 0, 0 }, 32834, NULL, NULL },
};

static const EventCharaKeyframe sEvent127Track3[1] = {
    { 638, 9999, { 0, 0 }, 70144, 67328, 0, 0, { 0, 0 }, 32770, NULL, NULL },
};

static const EventCharaTrack sEvent127Tracks[4] = {
    { sEvent127Track0, 0, { 0, 0, 0 } },
    { sEvent127Track1, 1, { 0, 0, 0 } },
    { sEvent127Track2, 2, { 0, 0, 0 } },
    { sEvent127Track3, 57, { 0, 0, 0 } },
};

const EventSequenceDef gEvent127 = {
    4,
    { 0, 0, 0 },
    sEvent127Tracks,
    sEvent127Camera,
    sEvent127Script,
    sEvent127SoundCues,
    NULL,
    600,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifndef VERSION_EU
#ifdef VERSION_US
static const MessageScriptEntry sEvent128Script[4] = {
    { 32, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB6444, 0, 150 },
    { 0, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB6438, 0, 180 },
    { 32, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB63F8, 0, 210 },
    { 32, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08FB63A8, MSG_SCRIPT_FLAG_END, 240 },
};

#include "event_128_text.inc"
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent128Script[4] = {
    { 32, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA0AD8, 0, 150 },
    { 0, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA0ACC, 0, 180 },
    { 32, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA0A8C, 0, 210 },
    { 32, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08FA0A3C, MSG_SCRIPT_FLAG_END, 240 },
};

#include "event_128_text.inc"
#endif
static const EventCameraKeyframe sEvent128Camera[1] = {
    { -55537, 80384, 58368, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent128SoundCues[1] = {
    { SONG_BGM_TOWN_FIELD, 0, EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent128Track0[1] = {
    { 4, 9999, { 0, 0 }, 72960, 68096, 0, 0, { 0, 0 }, 32834, NULL, NULL },
};

static const EventCharaKeyframe sEvent128Track1[1] = {
    { 451, 9999, { 0, 0 }, 82432, 63232, 0, 0, { 0, 0 }, 32770, NULL, NULL },
};

static const EventCharaKeyframe sEvent128Track2[1] = {
    { 638, 9999, { 0, 0 }, 98304, 67840, 0, 0, { 0, 0 }, 32770, NULL, NULL },
};

static const EventCharaKeyframe sEvent128Track3[1] = {
    { 684, 9999, { 0, 0 }, 64512, 62464, 0, 0, { 0, 0 }, 32834, NULL, NULL },
};

static const EventCharaKeyframe sEvent128Track4[1] = {
    { 114, 9999, { 0, 0 }, 68352, 75264, 0, 0, { 0, 0 }, 32834, NULL, NULL },
};

static const EventCharaKeyframe sEvent128Track5[1] = {
    { 146, 9999, { 0, 0 }, 57088, 72448, 0, 0, { 0, 0 }, 32834, NULL, NULL },
};

static const EventCharaTrack sEvent128Tracks[6] = {
    { sEvent128Track0, 0, { 0, 0, 0 } },
    { sEvent128Track1, 36, { 0, 0, 0 } },
    { sEvent128Track2, 57, { 0, 0, 0 } },
    { sEvent128Track3, 63, { 0, 0, 0 } },
    { sEvent128Track4, 1, { 0, 0, 0 } },
    { sEvent128Track5, 2, { 0, 0, 0 } },
};

const EventSequenceDef gEvent128 = {
    6,
    { 0, 0, 0 },
    sEvent128Tracks,
    sEvent128Camera,
    sEvent128Script,
    sEvent128SoundCues,
    NULL,
    350,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_129_text.inc"
static const MessageScriptEntry sEvent129Script[12] = {
    { 2, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB65F0, 0, 200 },
    { 6, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB6636, 0, 330 },
    { 43, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB6678, 0, 400 },
    { 53, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB66EC, 0, 610 },
    { 53, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB6720, 0, 730 },
    { 43, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB67D0, 0, 760 },
    { 53, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB6850, 0, 790 },
    { 43, 4, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB68D4, 0, 990 },
    { 0, 7, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB68EA, 0, 1160 },
    { 1, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB6956, 0, 1230 },
    { 43, 4, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB69D2, 0, 1470 },
    { 2, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB6A54, MSG_SCRIPT_FLAG_END, 1720 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent129Script[12] = {
    { 2, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA1030, 0, 200 },
    { 6, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA1010, 0, 330 },
    { 43, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA0FC4, 0, 400 },
    { 53, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA0F84, 0, 610 },
    { 53, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA0F34, 0, 730 },
    { 43, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA0F04, 0, 760 },
    { 53, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA0EBC, 0, 790 },
    { 43, 4, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA0EA8, 0, 990 },
    { 0, 7, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA0E7C, 0, 1160 },
    { 1, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA0E30, 0, 1230 },
    { 43, 4, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA0DEC, 0, 1470 },
    { 2, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA0DA4, MSG_SCRIPT_FLAG_END, 1720 },
};

#include "event_129_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent129Script[12] = {
    { 2, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6715C, 0, 200 },
    { 6, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67170, 0, 330 },
    { 43, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67184, 0, 400 },
    { 53, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67198, 0, 610 },
    { 53, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F671AC, 0, 730 },
    { 43, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F671C0, 0, 760 },
    { 53, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F671D4, 0, 790 },
    { 43, 4, 1, 1, { 0, 0, 0 }, &gUnkEu_09F671E8, 0, 990 },
    { 0, 7, 3, 1, { 0, 0, 0 }, &gUnkEu_09F671FC, 0, 1160 },
    { 1, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67210, 0, 1230 },
    { 43, 4, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67224, 0, 1470 },
    { 2, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67238, MSG_SCRIPT_FLAG_END, 1720 },
};
#endif

static const EvSoundCue sEvent129SoundCues[6] = {
    { 65535, 0, 0, 0 },
    { SONG_EV_WOMAN2_DIRTL, 376, 0, 0 },
    { SONG_BGM_EVENT_SILENCE, 400, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_SND_351, 639, 0, 0 },
    { SONG_EV_WOMAN2_DIRTR, 946, 0, 0 },
    { SONG_BGM_EVENT_SILENCE, 1775, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent129Camera[5] = {
    { -65536, 31488, 63744, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, NULL },
    { -65306, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 80, { 0, 0 }, NULL },
    { -64536, 81152, 67072, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 100, { 0, 0 }, NULL },
    { -64036, 49408, 76800, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 100, { 0, 0 }, NULL },
    { -55537, 43264, 77568, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent129Track0[7] = {
    { 2, 1, { 0, 0 }, 11008, 62464, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 7, 130, { 0, 0 }, 32000, 74240, 0, 2, { 0, 0 }, 67, NULL, NULL },
    { 2, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 12, 1080, { 0, 0 }, 43008, 82176, 0, 2, { 0, 0 }, 99, NULL, NULL },
    { 2, 1530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 1, 1550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent129Track1[9] = {
    { 112, 1, { 0, 0 }, 4096, 64000, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 117, 140, { 0, 0 }, 21504, 74240, 0, 112, { 0, 0 }, 67, NULL, NULL },
    { 112, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 121, 1090, { 0, 0 }, 34560, 83456, 0, 112, { 0, 0 }, 99, NULL, NULL },
    { 112, 1225, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 125, 1232, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 112, 1535, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 111, 1550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent129Track2[13] = {
    { 144, 1, { 0, 0 }, 11264, 55296, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 149, 100, { 0, 0 }, 26624, 65280, 0, 144, { 0, 0 }, 67, NULL, NULL },
    { 144, 120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateQuestionTask },
    { 144, 195, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 164, 202, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 152, 1100, { 0, 0 }, 43520, 73728, 0, 144, { 0, 0 }, 99, NULL, NULL },
    { 144, 1540, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 143, 1560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 1715, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 164, 1722, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent129Track3[6] = {
    { 229, 1080, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 229, 1082, { 0, 0 }, 45056, 82688, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 233, 1112, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, EventCharaHop, NULL },
    { 229, 1120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 229, 1550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 229, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent129Track4[22] = {
    { 328, 305, { 0, 0 }, 91904, 70400, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 328, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 330, 380, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 328, 395, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 332, 402, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 328, 620, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 328, 635, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 335, 685, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 328, 722, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 328, 755, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 332, 762, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 328, 930, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 330, 960, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 328, 1050, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 330, 1130, { 0, 0 }, 56576, 88064, 0, 328, { 0, 0 }, 3, NULL, NULL },
    { 328, 1190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 329, 1260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 329, 1410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 329, 1440, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 328, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 330, 2000, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 328, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent129Track5[13] = {
    { 375, 300, { 0, 0 }, 69888, 81408, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 374, 310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 374, 430, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 380, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 380, 580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 380, 670, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 374, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 374, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 375, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 374, 840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 374, 860, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 376, 1500, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 374, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent129Tracks[6] = {
    { sEvent129Track0, 0, { 0, 0, 0 } },
    { sEvent129Track1, 1, { 0, 0, 0 } },
    { sEvent129Track2, 2, { 0, 0, 0 } },
    { sEvent129Track3, 8, { 0, 0, 0 } },
    { sEvent129Track4, 16, { 0, 0, 0 } },
    { sEvent129Track5, 22, { 0, 0, 0 } },
};

const EventSequenceDef gEvent129 = {
    6,
    { 0, 0, 0 },
    sEvent129Tracks,
    sEvent129Camera,
    sEvent129Script,
    sEvent129SoundCues,
    NULL,
    1780,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    1,
    255,
    255,
};

#ifdef VERSION_US
#include "event_130_text.inc"
static const MessageScriptEntry sEvent130Script[24] = {
    { 53, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB76E4, 0, 200 },
    { 0, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB7740, 0, 230 },
    { 0, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB7786, 0, 330 },
    { 53, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB7812, 0, 370 },
    { 53, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08FB782C, 0, 372 },
    { 53, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB7888, 0, 480 },
    { 53, 4, 4, 1, { 0, 0, 0 }, gEventTextUs_08FB7914, 0, 482 },
    { 2, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB797A, 0, 510 },
    { 0, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB79F4, 0, 540 },
    { 53, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB7A3E, 0, 740 },
    { 0, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB7AB8, 0, 770 },
    { 53, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB7ACA, 0, 800 },
    { 53, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB7AEA, 0, 880 },
    { 53, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB7B32, 0, 980 },
    { 53, 0, 2, 1, { 0, 0, 0 }, gEventTextUs_08FB7B98, 0, 1230 },
    { 44, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB7BFA, 0, 1260 },
    { 44, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB7C1C, 0, 1450 },
    { 53, 0, 2, 1, { 0, 0, 0 }, gEventTextUs_08FB7C9E, 0, 1480 },
    { 44, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB7CD2, 0, 1510 },
    { 53, 2, 2, 1, { 0, 0, 0 }, gEventTextUs_08FB7CFC, 0, 1540 },
    { 44, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB7D78, 0, 1720 },
    { 0, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB7DE8, 0, 2020 },
    { 1, 2, 2, 1, { 0, 0, 0 }, gEventTextUs_08FB7E0E, 0, 2050 },
    { 0, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB7E34, MSG_SCRIPT_FLAG_END, 2110 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent130Script[24] = {
    { 53, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA21C8, 0, 200 },
    { 0, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA2190, 0, 230 },
    { 0, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA2140, 0, 330 },
    { 53, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08F7D494, 0, 370 },
    { 53, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08FA20F0, 0, 372 },
    { 53, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA20A8, 0, 480 },
    { 53, 4, 4, 3, { 0, 0, 0 }, gEventTextJp_08FA207C, 0, 482 },
    { 2, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA2040, 0, 510 },
    { 0, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA2018, 0, 540 },
    { 53, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA1FDC, 0, 740 },
    { 0, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA1FD0, 0, 770 },
    { 53, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA1FC4, 0, 800 },
    { 53, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA1F98, 0, 880 },
    { 53, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA1F60, 0, 980 },
    { 53, 0, 2, 3, { 0, 0, 0 }, gEventTextJp_08FA1F34, 0, 1230 },
    { 44, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA1F1C, 0, 1260 },
    { 44, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA1EC0, 0, 1450 },
    { 53, 0, 2, 3, { 0, 0, 0 }, gEventTextJp_08FA1E9C, 0, 1480 },
    { 44, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA1E8C, 0, 1510 },
    { 53, 2, 2, 3, { 0, 0, 0 }, gEventTextJp_08FA1E3C, 0, 1540 },
    { 44, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA1DF0, 0, 1720 },
    { 0, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA1DD0, 0, 2020 },
    { 1, 2, 2, 3, { 0, 0, 0 }, gEventTextJp_08FA1DB8, 0, 2050 },
    { 0, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA1D98, MSG_SCRIPT_FLAG_END, 2110 },
};

#include "event_130_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent130Script[24] = {
    { 53, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6724C, 0, 200 },
    { 0, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67260, 0, 230 },
    { 0, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67274, 0, 330 },
    { 53, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67288, 0, 370 },
    { 53, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6729C, 0, 372 },
    { 53, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F672B0, 0, 480 },
    { 53, 4, 4, 1, { 0, 0, 0 }, &gUnkEu_09F672C4, 0, 482 },
    { 2, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F672D8, 0, 510 },
    { 0, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F672EC, 0, 540 },
    { 53, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67300, 0, 740 },
    { 0, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67314, 0, 770 },
    { 53, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67328, 0, 800 },
    { 53, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6733C, 0, 880 },
    { 53, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67350, 0, 980 },
    { 53, 0, 2, 1, { 0, 0, 0 }, &gUnkEu_09F67364, 0, 1230 },
    { 44, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67378, 0, 1260 },
    { 44, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6738C, 0, 1450 },
    { 53, 0, 2, 1, { 0, 0, 0 }, &gUnkEu_09F673A0, 0, 1480 },
    { 44, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F673B4, 0, 1510 },
    { 53, 2, 2, 1, { 0, 0, 0 }, &gUnkEu_09F673C8, 0, 1540 },
    { 44, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F673DC, 0, 1720 },
    { 0, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F673F0, 0, 2020 },
    { 1, 2, 2, 1, { 0, 0, 0 }, &gUnkEu_09F67404, 0, 2050 },
    { 0, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67418, MSG_SCRIPT_FLAG_END, 2110 },
};
#endif

static const EvSoundCue sEvent130SoundCues[5] = {
    { SONG_BGM_EVENT_SILENCE, 0, 0, 0 },
    { SONG_BGM_EVENT_SILENCE, 1100, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT_UNREST, 1140, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_SND_352, 1780, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 2175, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent130Camera[5] = {
    { -65535, 72448, 57600, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65116, 57600, 72704, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 150, { 0, 0 }, NULL },
    { -64386, 51712, 69632, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -63606, 65792, 61696, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -55537, 71936, 66048, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
};

static const EventBgEffectEntry sEvent130BgEffects[4] = {
    { 1780, 0, 0, 0, 0 },
    { 1810, 0, 0, 0, 0x4 },
    { 1860, 0, 0, 0, 0 },
    { 1990, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent130Track0[32] = {
    { 2, 1, { 0, 0 }, 82432, 63488, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 12, 80, { 0, 0 }, 55296, 80896, 0, 2, { 0, 0 }, 35, NULL, NULL },
    { 2, 82, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 87, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 225, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 34, 252, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 34, 302, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 34, 327, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 30, 332, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 765, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 30, 810, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 950, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateQuestionTask },
    { 4, 990, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 995, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 1, 1005, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 12, 1200, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 100, NULL, NULL },
    { 4, 1900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1901, { 0, 0 }, 101376, 88320, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 14, 1984, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 4, 1987, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 4, 2015, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 30, 2025, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 2070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 2075, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 2080, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 1, 2085, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 1, 2125, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 2155, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 12, 3000, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 32804, NULL, NULL },
};

static const EventCharaKeyframe sEvent130Track1[22] = {
    { 112, 1, { 0, 0 }, 87296, 62976, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 121, 100, { 0, 0 }, 58112, 88832, 0, 112, { 0, 0 }, 35, NULL, NULL },
    { 112, 102, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 113, 107, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 950, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateQuestionTask },
    { 114, 990, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 113, 995, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 111, 1005, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 121, 1210, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 100, NULL, NULL },
    { 114, 1900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 1901, { 0, 0 }, 94976, 94208, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 120, 1990, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 114, 1993, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 114, 2030, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 110, 2140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 2145, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 113, 2150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 2160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 121, 3000, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 32804, NULL, NULL },
};

static const EventCharaKeyframe sEvent130Track2[22] = {
    { 144, 1, { 0, 0 }, 90624, 59136, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 152, 130, { 0, 0 }, 66048, 80896, 0, 144, { 0, 0 }, 35, NULL, NULL },
    { 144, 132, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 145, 137, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 505, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 165, 512, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 950, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateQuestionTask },
    { 146, 990, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 142, 995, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 1005, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 152, 1200, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 100, NULL, NULL },
    { 146, 1900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 1901, { 0, 0 }, 110848, 88576, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 153, 2000, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 146, 2003, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 146, 2140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 145, 2145, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 2160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 152, 3000, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 32804, NULL, NULL },
};

static const EventCharaKeyframe sEvent130Track3[29] = {
    { 375, 40, { 0, 0 }, 38144, 70144, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 374, 50, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 375, 80, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 374, 130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 376, 160, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 374, 340, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 380, 371, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 374, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 374, 410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 375, 430, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 377, 460, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 375, 560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 375, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 375, 695, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 374, 705, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 374, 810, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 374, 860, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 375, 870, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 374, 960, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 376, 978, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 374, 1030, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 376, 1070, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 374, 1120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 375, 1280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 375, 1410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 375, 1750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 375, 1800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 375, 1850, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaFadeOut, NULL },
    { 375, 3000, { 0, 0 }, 128000, 128000, 0, 0, { 0, 0 }, 98370, NULL, NULL },
};

static const EventCharaKeyframe sEvent130Track4[14] = {
    { 410, 1100, { 0, 0 }, 128000, 128000, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 410, 1140, { 0, 0 }, 91904, 61440, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 412, 1190, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 410, 1412, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 412, 1432, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 410, 1445, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 415, 1452, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 416, 1479, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 410, 1560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 410, 1690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 410, 1722, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 414, 1800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 414, 1850, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaFadeOut, NULL },
    { 410, 3000, { 0, 0 }, 128000, 128000, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaTrack sEvent130Tracks[5] = {
    { sEvent130Track0, 0, { 0, 0, 0 } },
    { sEvent130Track1, 1, { 0, 0, 0 } },
    { sEvent130Track2, 2, { 0, 0, 0 } },
    { sEvent130Track3, 22, { 0, 0, 0 } },
    { sEvent130Track4, 30, { 0, 0, 0 } },
};

const EventSequenceDef gEvent130 = {
    5,
    { 0, 0, 0 },
    sEvent130Tracks,
    sEvent130Camera,
    sEvent130Script,
    sEvent130SoundCues,
    sEvent130BgEffects,
    2180,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_131_text.inc"
static const MessageScriptEntry sEvent131Script[38] = {
    { 44, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB92D0, 0, 100 },
    { 53, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB931E, 0, 130 },
    { 44, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB935C, 0, 160 },
    { 0, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB940E, 0, 250 },
    { 0, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB941E, 0, 370 },
    { 44, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FB9486, 0, 400 },
    { 44, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08FB9544, 0, 402 },
    { 43, 0, 0, 1, { 0, 0, 0 }, gEventTextUs_08FB95DC, 0, 430 },
    { 53, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB963A, 0, 630 },
    { 53, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB964E, 0, 720 },
    { 53, 2, 4, 1, { 0, 0, 0 }, gEventTextUs_08FB96B2, 0, 722 },
    { 43, 4, 0, 1, { 0, 0, 0 }, gEventTextUs_08FB971C, 0, 770 },
    { 6, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB972A, 0, 800 },
    { 43, 0, 0, 1, { 0, 0, 0 }, gEventTextUs_08FB9762, 0, 990 },
    { 43, 0, 0, 1, { 0, 0, 0 }, gEventTextUs_08FB97C6, 0, 1070 },
    { 43, 4, 4, 1, { 0, 0, 0 }, gEventTextUs_08FB984E, 0, 1072 },
    { 43, 4, 4, 1, { 0, 0, 0 }, gEventTextUs_08FB98E0, 0, 1074 },
    { 43, 0, 0, 1, { 0, 0, 0 }, gEventTextUs_08FB9916, 0, 1370 },
    { 43, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08FB99D4, 0, 1372 },
    { 43, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08FB9A76, 0, 1374 },
    { 43, 0, 0, 1, { 0, 0, 0 }, gEventTextUs_08FB9B00, 0, 1460 },
    { 53, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB9B44, 0, 1510 },
    { 44, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB9B56, 0, 1560 },
    { 44, 2, 4, 1, { 0, 0, 0 }, gEventTextUs_08FB9BEE, 0, 1562 },
    { 53, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB9C9A, 0, 1655 },
    { 53, 4, 2, 1, { 0, 0, 0 }, gEventTextUs_08FB9CB4, 0, 1720 },
    { 44, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB9CC2, 0, 2020 },
    { 44, 0, 4, 1, { 0, 0, 0 }, gEventTextUs_08FB9D3A, 0, 2022 },
    { 44, 2, 4, 1, { 0, 0, 0 }, gEventTextUs_08FB9DB0, 0, 2024 },
    { 43, 2, 0, 1, { 0, 0, 0 }, gEventTextUs_08FB9E3A, 0, 2050 },
    { 43, 2, 0, 1, { 0, 0, 0 }, gEventTextUs_08FB9E8E, 0, 2285 },
    { 0, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB9EAA, 0, 2465 },
    { 43, 3, 0, 1, { 0, 0, 0 }, gEventTextUs_08FB9F12, 0, 2525 },
    { 1, 4, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB9F44, 0, 2555 },
    { 43, 3, 0, 1, { 0, 0, 0 }, gEventTextUs_08FB9FAE, 0, 2585 },
    { 2, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FB9FCC, 0, 2615 },
    { 0, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FBA03A, 0, 2645 },
    { 43, 0, 0, 1, { 0, 0, 0 }, gEventTextUs_08FBA07C, MSG_SCRIPT_FLAG_END, 2670 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent131Script[38] = {
    { 44, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA3EFC, 0, 100 },
    { 53, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA3ED0, 0, 130 },
    { 44, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA3E74, 0, 160 },
    { 0, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA3E68, 0, 250 },
    { 0, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA3E3C, 0, 370 },
    { 44, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA3DF0, 0, 400 },
    { 44, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08FA3DA0, 0, 402 },
    { 43, 0, 0, 3, { 0, 0, 0 }, gEventTextJp_08FA3D8C, 0, 430 },
    { 53, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA3D80, 0, 630 },
    { 53, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA3D38, 0, 720 },
    { 53, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08FA3CF4, 0, 722 },
    { 43, 4, 0, 3, { 0, 0, 0 }, gEventTextJp_08FA3CE8, 0, 770 },
    { 6, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA3CCC, 0, 800 },
    { 43, 0, 0, 3, { 0, 0, 0 }, gEventTextJp_08FA3C9C, 0, 990 },
    { 43, 0, 0, 3, { 0, 0, 0 }, gEventTextJp_08FA3C4C, 0, 1070 },
    { 43, 4, 4, 3, { 0, 0, 0 }, gEventTextJp_08FA3BFC, 0, 1072 },
    { 43, 4, 4, 3, { 0, 0, 0 }, gEventTextJp_08FA3BCC, 0, 1074 },
    { 43, 0, 0, 3, { 0, 0, 0 }, gEventTextJp_08FA3B70, 0, 1370 },
    { 43, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08FA3B1C, 0, 1372 },
    { 43, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08FA3AC4, 0, 1374 },
    { 43, 0, 0, 3, { 0, 0, 0 }, gEventTextJp_08FA3AA4, 0, 1460 },
    { 53, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA3A94, 0, 1510 },
    { 44, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA3A3C, 0, 1560 },
    { 44, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08FA39F0, 0, 1562 },
    { 53, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA39E4, 0, 1655 },
    { 53, 4, 2, 3, { 0, 0, 0 }, gEventTextJp_08FA39D8, 0, 1720 },
    { 44, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA3984, 0, 2020 },
    { 44, 0, 4, 3, { 0, 0, 0 }, gEventTextJp_08FA3944, 0, 2022 },
    { 44, 2, 4, 3, { 0, 0, 0 }, gEventTextJp_08FA38EC, 0, 2024 },
    { 43, 2, 0, 3, { 0, 0, 0 }, gEventTextJp_08FA38D0, 0, 2050 },
    { 43, 2, 0, 3, { 0, 0, 0 }, gEventTextJp_08FA38C4, 0, 2285 },
    { 0, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA3894, 0, 2465 },
    { 43, 3, 0, 3, { 0, 0, 0 }, gEventTextJp_08FA3880, 0, 2525 },
    { 1, 4, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA3844, 0, 2555 },
    { 43, 3, 0, 3, { 0, 0, 0 }, gEventTextJp_08FA382C, 0, 2585 },
    { 2, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA37E4, 0, 2615 },
    { 0, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA37C0, 0, 2645 },
    { 43, 0, 0, 3, { 0, 0, 0 }, gEventTextJp_08FA37AC, MSG_SCRIPT_FLAG_END, 2670 },
};

#include "event_131_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent131Script[38] = {
    { 44, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6742C, 0, 100 },
    { 53, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67440, 0, 130 },
    { 44, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67454, 0, 160 },
    { 0, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67468, 0, 250 },
    { 0, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6747C, 0, 370 },
    { 44, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67490, 0, 400 },
    { 44, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F674A4, 0, 402 },
    { 43, 0, 0, 1, { 0, 0, 0 }, &gUnkEu_09F674B8, 0, 430 },
    { 53, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F674CC, 0, 630 },
    { 53, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F674E0, 0, 720 },
    { 53, 2, 4, 1, { 0, 0, 0 }, &gUnkEu_09F674F4, 0, 722 },
    { 43, 4, 0, 1, { 0, 0, 0 }, &gUnkEu_09F67508, 0, 770 },
    { 6, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6751C, 0, 800 },
    { 43, 0, 0, 1, { 0, 0, 0 }, &gUnkEu_09F67530, 0, 990 },
    { 43, 0, 0, 1, { 0, 0, 0 }, &gUnkEu_09F67544, 0, 1070 },
    { 43, 4, 4, 1, { 0, 0, 0 }, &gUnkEu_09F67558, 0, 1072 },
    { 43, 4, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6756C, 0, 1074 },
    { 43, 0, 0, 1, { 0, 0, 0 }, &gUnkEu_09F67580, 0, 1370 },
    { 43, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F67594, 0, 1372 },
    { 43, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F675A8, 0, 1374 },
    { 43, 0, 0, 1, { 0, 0, 0 }, &gUnkEu_09F675BC, 0, 1460 },
    { 53, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F675D0, 0, 1510 },
    { 44, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F675E4, 0, 1560 },
    { 44, 2, 4, 1, { 0, 0, 0 }, &gUnkEu_09F675F8, 0, 1562 },
    { 53, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F6760C, 0, 1655 },
    { 53, 4, 2, 1, { 0, 0, 0 }, &gUnkEu_09F67620, 0, 1720 },
    { 44, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67634, 0, 2020 },
    { 44, 0, 4, 1, { 0, 0, 0 }, &gUnkEu_09F67648, 0, 2022 },
    { 44, 2, 4, 1, { 0, 0, 0 }, &gUnkEu_09F6765C, 0, 2024 },
    { 43, 2, 0, 1, { 0, 0, 0 }, &gUnkEu_09F67670, 0, 2050 },
    { 43, 2, 0, 1, { 0, 0, 0 }, &gUnkEu_09F67684, 0, 2285 },
    { 0, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67698, 0, 2465 },
    { 43, 3, 0, 1, { 0, 0, 0 }, &gUnkEu_09F676AC, 0, 2525 },
    { 1, 4, 3, 1, { 0, 0, 0 }, &gUnkEu_09F676C0, 0, 2555 },
    { 43, 3, 0, 1, { 0, 0, 0 }, &gUnkEu_09F676D4, 0, 2585 },
    { 2, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F676E8, 0, 2615 },
    { 0, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F676FC, 0, 2645 },
    { 43, 0, 0, 1, { 0, 0, 0 }, &gUnkEu_09F67710, MSG_SCRIPT_FLAG_END, 2670 },
};
#endif

static const EvSoundCue sEvent131SoundCues[13] = {
    { SONG_BGM_HOLLOW_FIELD, 0, 0, 0 },
    { SONG_BGM_HOLLOW_FIELD, 430, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT_SILENCE, 990, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_SND_351, 1459, 0, 0 },
    { SONG_BGM_EVENT_SILENCE, 1515, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT_UNREST, 1560, 0, 0 },
    { SONG_SND_353, 1586, 0, 0 },
    { SONG_SND_353, 1695, EV_SOUND_FLAG_STOP, 0 },
    { SONG_BTL_GMIC_OK, 1701, 0, 0 },
    { SONG_SND_351, 1804, 0, 0 },
    { SONG_SND_352, 2119, 0, 0 },
    { SONG_SND_351, 2204, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 2795, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent131Camera[12] = {
    { -65276, 50176, 79616, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65096, 35840, 68864, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -63972, 62464, 82944, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -63861, 62464, 73728, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -63836, 62464, 77824, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 30, { 0, 0 }, NULL },
    { -63826, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -63806, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -63796, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_HALF_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -63776, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_HALF_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -63546, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -63249, 62464, 82944, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -55537, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EventBgEffectEntry sEvent131BgEffects[5] = {
    { 2119, 0, 0, 0, 0 },
    { 2120, 0, 60, 0, 0x14 },
    { 2150, 0, 0, 0, 0 },
    { 2270, 0, 0, 0, 0x2 },
    { 2330, 0, 0, 0, 0x8018 },
};

static const EventCharaKeyframe sEvent131Track0[15] = {
    { 2, 255, { 0, 0 }, 11776, 61184, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 12, 300, { 0, 0 }, 21760, 71424, 0, 2, { 0, 0 }, 99, NULL, NULL },
    { 2, 365, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 31, 432, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 2326, { 0, 0 }, 28160, 74240, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 12, 2400, { 0, 0 }, 55808, 89088, 0, 2, { 0, 0 }, 99, NULL, NULL },
    { 2, 2430, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 2435, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 2470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 2475, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 2710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 2715, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 2760, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 14, 5000, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 32868, NULL, NULL },
};

static const EventCharaKeyframe sEvent131Track1[11] = {
    { 112, 255, { 0, 0 }, 2816, 58880, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 121, 300, { 0, 0 }, 12032, 70144, 0, 112, { 0, 0 }, 99, NULL, NULL },
    { 112, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 112, 2316, { 0, 0 }, 26624, 82176, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 121, 2400, { 0, 0 }, 47104, 92160, 0, 112, { 0, 0 }, 99, NULL, NULL },
    { 112, 2550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 136, 2560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 112, 2740, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 113, 2745, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 2790, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 120, 5000, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 32868, NULL, NULL },
};

static const EventCharaKeyframe sEvent131Track2[11] = {
    { 144, 255, { 0, 0 }, 11264, 59392, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 152, 310, { 0, 0 }, 17664, 64512, 0, 144, { 0, 0 }, 99, NULL, NULL },
    { 144, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 2316, { 0, 0 }, 26112, 74752, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 152, 2400, { 0, 0 }, 46336, 87040, 0, 144, { 0, 0 }, 99, NULL, NULL },
    { 144, 2610, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 164, 2620, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 2720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 2730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 2800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 153, 5000, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 32868, NULL, NULL },
};

static const EventCharaKeyframe sEvent131Track3[7] = {
    { 229, 301, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 229, 302, { 0, 0 }, 21760, 70400, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 233, 330, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, EventCharaHop, NULL },
    { 229, 335, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 229, 2640, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 231, 2650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 231, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98370, NULL, NULL },
};

static const EventCharaKeyframe sEvent131Track4[17] = {
    { 410, 190, { 0, 0 }, 62464, 81152, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 412, 210, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 410, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 411, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 410, 580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 410, 1555, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 415, 1561, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 416, 1564, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 414, 1670, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 410, 2023, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 415, 2025, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 416, 2049, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 410, 2080, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 414, 2150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 410, 2180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 410, 2300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaFadeOut, NULL },
    { 410, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent131Track5[19] = {
    { 375, 205, { 0, 0 }, 45056, 89088, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 377, 225, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 68, NULL, NULL },
    { 375, 560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 374, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 374, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 374, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 375, 740, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 375, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 375, 1050, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 375, 1110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 374, 1130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 374, 1614, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 375, 1640, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 374, 1670, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 378, 1700, { 0, 0 }, 68608, 96768, 0, 374, { 0, 0 }, 115, NULL, NULL },
    { 374, 1705, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 85, NULL, NULL },
    { 379, 1790, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 379, 1820, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaFadeOut, NULL },
    { 375, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98370, NULL, NULL },
};

static const EventCharaKeyframe sEvent131Track6[21] = {
    { 329, 510, { 0, 0 }, 102400, 117760, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 331, 610, { 0, 0 }, 83968, 103168, 0, 329, { 0, 0 }, 3, NULL, NULL },
    { 329, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 329, 960, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 329, 1200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 329, 1330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 329, 1400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 331, 1440, { 0, 0 }, 77824, 101120, 0, 329, { 0, 0 }, 3, NULL, NULL },
    { 329, 1450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 21, NULL, NULL },
    { 334, 1710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 21, NULL, NULL },
    { 329, 1800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 21, NULL, NULL },
    { 336, 2026, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 21, NULL, NULL },
    { 329, 2045, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 334, 2100, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 329, 2200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 336, 2250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 329, 2251, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 331, 2282, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 329, 2770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 329, 2780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 333, 5000, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 32868, NULL, NULL },
};

static const EventCharaKeyframe sEvent131Track7[5] = {
    { 839, 1792, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8258, NULL, NULL },
    { 839, 1793, { 0, 0 }, 68864, 86016, 0, 0, { 0, 0 }, 16706, NULL, NULL },
    { 839, 1850, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 324, NULL, NULL },
    { 839, 1880, { 0, 0 }, 65536, 71680, 0, 0, { 0, 0 }, 4435, EventCharaFadeOut, NULL },
    { 839, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98370, NULL, NULL },
};

static const EventCharaKeyframe sEvent131Track8[4] = {
    { 925, 1586, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 924, 1670, { 0, 0 }, 58112, 59136, 0, 0, { 0, 0 }, 16658, NULL, NULL },
    { 924, 1705, { 0, 0 }, 68096, 85760, 0, 925, { 0, 0 }, 4371, NULL, NULL },
    { 924, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent131Track9[3] = {
    { 590, 1940, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 590, 1960, { 0, 0 }, 63232, 68352, 0, 0, { 0, 0 }, 16658, NULL, NULL },
    { 590, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaTrack sEvent131Tracks[10] = {
    { sEvent131Track0, 0, { 0, 0, 0 } },
    { sEvent131Track1, 1, { 0, 0, 0 } },
    { sEvent131Track2, 2, { 0, 0, 0 } },
    { sEvent131Track3, 8, { 0, 0, 0 } },
    { sEvent131Track4, 30, { 0, 0, 0 } },
    { sEvent131Track5, 22, { 0, 0, 0 } },
    { sEvent131Track6, 16, { 0, 0, 0 } },
    { sEvent131Track7, 78, { 0, 0, 0 } },
    { sEvent131Track8, 91, { 0, 0, 0 } },
    { sEvent131Track9, 49, { 0, 0, 0 } },
};

const EventSequenceDef gEvent131 = {
    10,
    { 0, 0, 0 },
    sEvent131Tracks,
    sEvent131Camera,
    sEvent131Script,
    sEvent131SoundCues,
    sEvent131BgEffects,
    2800,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_132_text.inc"
static const MessageScriptEntry sEvent132Script[14] = {
    { 44, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FBB6B8, 0, 180 },
    { 44, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FBB780, 0, 350 },
    { 44, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08FBB7E0, 0, 352 },
    { 44, 0, 1, 1, { 0, 0, 0 }, gEventTextUs_08FBB88C, 0, 420 },
    { 43, 0, 3, 1, { 0, 0, 0 }, gEventTextUs_08FBB946, 0, 450 },
    { 0, 5, 2, 1, { 0, 0, 0 }, gEventTextUs_08FBB98E, 0, 480 },
    { 43, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FBB9DC, 0, 530 },
    { 44, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FBBA5C, 0, 560 },
    { 43, 2, 3, 1, { 0, 0, 0 }, gEventTextUs_08FBBA70, 0, 580 },
    { 44, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FBBAAE, 0, 620 },
    { 44, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08FBBB5E, 0, 622 },
    { 44, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08FBBC10, 0, 670 },
    { 0, 2, 2, 1, { 0, 0, 0 }, gEventTextUs_08FBBCA8, 0, 720 },
    { 44, 2, 1, 1, { 0, 0, 0 }, gEventTextUs_08FBBCD0, MSG_SCRIPT_FLAG_END, 750 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent132Script[14] = {
    { 44, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA5628, 0, 180 },
    { 44, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA55EC, 0, 350 },
    { 44, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08FA5598, 0, 352 },
    { 44, 0, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA553C, 0, 420 },
    { 43, 0, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA5500, 0, 450 },
    { 0, 5, 2, 3, { 0, 0, 0 }, gEventTextJp_08FA54D0, 0, 480 },
    { 43, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA5478, 0, 530 },
    { 44, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA546C, 0, 560 },
    { 43, 2, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA545C, 0, 580 },
    { 44, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA540C, 0, 620 },
    { 44, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08FA53AC, 0, 622 },
    { 44, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA5350, 0, 670 },
    { 0, 2, 2, 3, { 0, 0, 0 }, gEventTextJp_08FA5340, 0, 720 },
    { 44, 2, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA530C, MSG_SCRIPT_FLAG_END, 750 },
};

#include "event_132_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent132Script[14] = {
    { 44, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67800, 0, 180 },
    { 44, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67814, 0, 350 },
    { 44, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F67828, 0, 352 },
    { 44, 0, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6783C, 0, 420 },
    { 43, 0, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67850, 0, 450 },
    { 0, 5, 2, 1, { 0, 0, 0 }, &gUnkEu_09F67864, 0, 480 },
    { 43, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67878, 0, 530 },
    { 44, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6788C, 0, 560 },
    { 43, 2, 3, 1, { 0, 0, 0 }, &gUnkEu_09F678A0, 0, 580 },
    { 44, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F678B4, 0, 620 },
    { 44, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F678C8, 0, 622 },
    { 44, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F678DC, 0, 670 },
    { 0, 2, 2, 1, { 0, 0, 0 }, &gUnkEu_09F678F0, 0, 720 },
    { 44, 2, 1, 1, { 0, 0, 0 }, &gUnkEu_09F67904, MSG_SCRIPT_FLAG_END, 750 },
};
#endif

static const EvSoundCue sEvent132SoundCues[5] = {
    { SONG_BGM_EVENT_UNREST, 0, 0, 0 },
    { SONG_EV_WOMAN2_DIRTR, 515, 0, 0 },
    { SONG_SND_351, 529, 0, 0 },
    { SONG_SND_375, 860, 0, 0 },
    { SONG_EV_FLASH02, 980, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent132Camera[5] = {
    { -65535, 32256, 71680, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65256, 56064, 65536, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 120, { 0, 0 }, NULL },
    { -64686, 66816, 58624, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -64556, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64526, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 30, { 0, 0 }, NULL },
};

static const EventBgEffectEntry sEvent132BgEffects[4] = {
    { 850, 0, 0, 0, 0 },
    { 860, 0, 0, 0, 0x4 },
    { 870, 6, 66560, 38144, 0x1 },
    { 1009, 0, 0, 0, 0x8002 },
};

static const EventCharaKeyframe sEvent132Track0[7] = {
    { 4, 1, { 0, 0 }, 28672, 93184, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 14, 80, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 4, 83, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 4, 475, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 16, 532, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 19, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent132Track1[6] = {
    { 114, 1, { 0, 0 }, 15104, 99328, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 120, 110, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 114, 113, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 114, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 122, 705, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 123, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent132Track2[6] = {
    { 146, 1, { 0, 0 }, 3840, 97792, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 153, 130, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 146, 133, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 146, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 157, 705, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 158, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent132Track3[8] = {
    { 329, 1, { 0, 0 }, 18432, 91648, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 333, 100, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 329, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 331, 520, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 329, 525, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 334, 565, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 329, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 334, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent132Track4[12] = {
    { 410, 230, { 0, 0 }, 70400, 66048, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 410, 240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 411, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 413, 320, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 411, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 410, 390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 410, 615, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 415, 621, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 416, 630, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 412, 650, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 410, 770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 414, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33797, NULL, NULL },
};

static const EventCharaTrack sEvent132Tracks[5] = {
    { sEvent132Track0, 0, { 0, 0, 0 } },
    { sEvent132Track1, 1, { 0, 0, 0 } },
    { sEvent132Track2, 2, { 0, 0, 0 } },
    { sEvent132Track3, 16, { 0, 0, 0 } },
    { sEvent132Track4, 30, { 0, 0, 0 } },
};

const EventSequenceDef gEvent132 = {
    5,
    { 0, 0, 0 },
    sEvent132Tracks,
    sEvent132Camera,
    sEvent132Script,
    sEvent132SoundCues,
    sEvent132BgEffects,
    1010,
    0,
    1,
    0,
    0,
    0,
    0,
    153,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_133_text.inc"
static const MessageScriptEntry sEvent133Script[11] = {
    { 43, 3, 3, 1, { 0, 0, 0 }, gEventTextUs_08FBC550, 0, 900 },
    { 43, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FBC55E, 0, 960 },
    { 53, 4, 1, 1, { 0, 0, 0 }, gEventTextUs_08FBC57E, 0, 990 },
    { 53, 1, 4, 1, { 0, 0, 0 }, gEventTextUs_08FBC5D8, 0, 992 },
    { 43, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FBC634, 0, 1020 },
    { 43, 4, 4, 1, { 0, 0, 0 }, gEventTextUs_08FBC6CA, 0, 1022 },
    { 53, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_08FBC732, 0, 1050 },
    { 43, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FBC7CA, 0, 1080 },
    { 2, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FBC7D8, 0, 1280 },
    { 0, 1, 3, 1, { 0, 0, 0 }, gEventTextUs_08FBC832, 0, 1310 },
    { 1, 3, 1, 1, { 0, 0, 0 }, gEventTextUs_08FBC888, MSG_SCRIPT_FLAG_END, 1340 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent133Script[11] = {
    { 43, 3, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA6060, 0, 900 },
    { 43, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA6050, 0, 960 },
    { 53, 4, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA6018, 0, 990 },
    { 53, 1, 4, 3, { 0, 0, 0 }, gEventTextJp_08FA5FE4, 0, 992 },
    { 43, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA5F94, 0, 1020 },
    { 43, 4, 4, 3, { 0, 0, 0 }, gEventTextJp_08FA5F64, 0, 1022 },
    { 53, 1, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA5F08, 0, 1050 },
    { 43, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA5EF4, 0, 1080 },
    { 2, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA5EBC, 0, 1280 },
    { 0, 1, 3, 3, { 0, 0, 0 }, gEventTextJp_08FA5E94, 0, 1310 },
    { 1, 3, 1, 3, { 0, 0, 0 }, gEventTextJp_08FA5E60, MSG_SCRIPT_FLAG_END, 1340 },
};

#include "event_133_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent133Script[11] = {
    { 43, 3, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67724, 0, 900 },
    { 43, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67738, 0, 960 },
    { 53, 4, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6774C, 0, 990 },
    { 53, 1, 4, 1, { 0, 0, 0 }, &gUnkEu_09F67760, 0, 992 },
    { 43, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F67774, 0, 1020 },
    { 43, 4, 4, 1, { 0, 0, 0 }, &gUnkEu_09F67788, 0, 1022 },
    { 53, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F6779C, 0, 1050 },
    { 43, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F677B0, 0, 1080 },
    { 2, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F677C4, 0, 1280 },
    { 0, 1, 3, 1, { 0, 0, 0 }, &gUnkEu_09F677D8, 0, 1310 },
    { 1, 3, 1, 1, { 0, 0, 0 }, &gUnkEu_09F677EC, MSG_SCRIPT_FLAG_END, 1340 },
};
#endif

static const EvSoundCue sEvent133SoundCues[7] = {
    { 65535, 0, 0, 0 },
    { SONG_EV_CARDFALL, 305, 0, 0 },
    { SONG_EV_WHITEOUT, 580, 0, 0 },
    { SONG_SND_351, 834, 0, 0 },
    { SONG_SND_351, 1019, 0, 0 },
    { SONG_BGM_EVENT4, 1060, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT4, 1505, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent133Camera[13] = {
    { -65535, 42240, 74752, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65385, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 100, { 0, 0 }, NULL },
    { -65256, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65036, 76032, 57600, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 150, { 0, 0 }, NULL },
    { -65026, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_HALF_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -64996, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_HALF_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -64956, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_HALF_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -64856, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 90, { 0, 0 }, NULL },
    { -64756, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 100, { 0, 0 }, NULL },
    { -64586, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64436, 78848, 55040, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 30, { 0, 0 }, NULL },
    { -64106, 38144, 81408, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 150, { 0, 0 }, NULL },
    { -60536, 76032, 57600, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 150, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent133Track0[10] = {
    { 21, 90, { 0, 0 }, 32000, 87808, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 22, 100, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 1305, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 36, 1342, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 1360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 1365, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 1370, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 1, 1375, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 1390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 7, 5000, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 32772, NULL, NULL },
};

static const EventCharaKeyframe sEvent133Track1[10] = {
    { 123, 100, { 0, 0 }, 44544, 87296, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 124, 110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 1282, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 110, 1287, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 1335, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 126, 1342, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 1380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 113, 1385, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 1400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 117, 5000, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 32772, NULL, NULL },
};

static const EventCharaKeyframe sEvent133Track2[10] = {
    { 158, 105, { 0, 0 }, 34048, 79616, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 159, 115, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 1250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 1255, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 1278, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 164, 1282, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 1375, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 143, 1380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 1395, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 149, 5000, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 32772, NULL, NULL },
};

static const EventCharaKeyframe sEvent133Track3[6] = {
    { 374, 675, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 374, 980, { 0, 0 }, 84224, 60160, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 380, 991, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 374, 1490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 376, 1530, { 0, 0 }, 81408, 62720, 0, 374, { 0, 0 }, 3, NULL, NULL },
    { 374, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent133Track4[12] = {
    { 334, 95, { 0, 0 }, 50688, 78080, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 329, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 329, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateQuestionTask },
    { 329, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 331, 350, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 329, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 336, 880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 329, 905, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 331, 950, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 329, 1015, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 334, 1021, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 329, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent133Track5[5] = {
    { 839, 299, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 839, 300, { 0, 0 }, 84480, 30464, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 839, 450, { 0, 0 }, 84480, 53248, 0, 839, { 0, 0 }, 259, NULL, NULL },
    { 839, 675, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 839, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33090, NULL, NULL },
};

static const EventCharaTrack sEvent133Tracks[6] = {
    { sEvent133Track0, 0, { 0, 0, 0 } },
    { sEvent133Track1, 1, { 0, 0, 0 } },
    { sEvent133Track2, 2, { 0, 0, 0 } },
    { sEvent133Track3, 22, { 0, 0, 0 } },
    { sEvent133Track4, 16, { 0, 0, 0 } },
    { sEvent133Track5, 78, { 0, 0, 0 } },
};

const EventSequenceDef gEvent133 = {
    6,
    { 0, 0, 0 },
    sEvent133Tracks,
    sEvent133Camera,
    sEvent133Script,
    sEvent133SoundCues,
    NULL,
    1510,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
