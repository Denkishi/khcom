#include "msg.h"
#include "eventselect_api.h"
#include "card_message_text.h"
#include "event_text.h"
#include "msg_localized_data.h"
#include "songs.h"
#include "msg_types.h"
#include <stddef.h>
#include "types.h"

#ifdef VERSION_US
#include "event_134_text.inc"

static const MessageScriptEntry sEvent134Script[22] = {
    { 0, 0, 3, 1, { 0, 0, 0 }, gEvent134Text00, 0, 830 },
    { 36, 0, 1, 1, { 0, 0, 0 }, gEvent134Text01, 0, 980 },
    { 0, 0, 3, 1, { 0, 0, 0 }, gEvent134Text02, 0, 1010 },
    { 0, 0, 3, 1, { 0, 0, 0 }, gEvent134Text03, 0, 1155 },
    { 36, 0, 1, 1, { 0, 0, 0 }, gEvent134Text04, 0, 1185 },
    { 0, 7, 3, 1, { 0, 0, 0 }, gEvent134Text05, 0, 1215 },
    { 36, 2, 1, 1, { 0, 0, 0 }, gEvent134Text06, 0, 1305 },
    { 36, 0, 4, 1, { 0, 0, 0 }, gEvent134Text07, 0, 1309 },
    { 36, 0, 4, 1, { 0, 0, 0 }, gEvent134Text08, 0, 1311 },
    { 0, 0, 3, 1, { 0, 0, 0 }, gEvent134Text09, 0, 1500 },
    { 36, 0, 1, 1, { 0, 0, 0 }, gEvent134Text10, 0, 1530 },
    { 0, 1, 3, 1, { 0, 0, 0 }, gEvent134Text11, 0, 1560 },
    { 36, 3, 1, 1, { 0, 0, 0 }, gEvent134Text12, 0, 1590 },
    { 0, 4, 3, 1, { 0, 0, 0 }, gEvent134Text13, 0, 1620 },
    { 36, 3, 1, 1, { 0, 0, 0 }, gEvent134Text14, 0, 1650 },
    { 36, 3, 4, 1, { 0, 0, 0 }, gEvent134Text15, 0, 1652 },
    { 0, 4, 3, 1, { 0, 0, 0 }, gEvent134Text16, 0, 1690 },
    { 0, 1, 4, 1, { 0, 0, 0 }, gEvent134Text17, 0, 1692 },
    { 36, 0, 1, 1, { 0, 0, 0 }, gEvent134Text18, 0, 1725 },
    { 62, 0, 3, 1, { 0, 0, 0 }, gEvent134Text19, 0, 1920 },
    { 62, 0, 3, 1, { 0, 0, 0 }, gEvent134Text20, 0, 1920 },
    { 62, 0, 3, 1, { 0, 0, 0 }, gEvent134Text21, MSG_SCRIPT_FLAG_END, 1920 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent134Script[22] = {
    { 0, 0, 3, 3, { 0, 0, 0 }, gEvent134Text00, 0, 830 },
    { 36, 0, 1, 3, { 0, 0, 0 }, gEvent134Text01, 0, 980 },
    { 0, 0, 3, 3, { 0, 0, 0 }, gEvent134Text02, 0, 1010 },
    { 0, 0, 3, 3, { 0, 0, 0 }, gEvent134Text03, 0, 1155 },
    { 36, 0, 1, 3, { 0, 0, 0 }, gEvent134Text04, 0, 1185 },
    { 0, 7, 3, 3, { 0, 0, 0 }, gEvent134Text05, 0, 1215 },
    { 36, 2, 1, 3, { 0, 0, 0 }, gEvent134Text06, 0, 1305 },
    { 36, 0, 4, 3, { 0, 0, 0 }, gEvent134Text07, 0, 1309 },
    { 36, 0, 4, 3, { 0, 0, 0 }, gEvent134Text08, 0, 1311 },
    { 0, 0, 3, 3, { 0, 0, 0 }, gEvent134Text09, 0, 1500 },
    { 36, 0, 1, 3, { 0, 0, 0 }, gEvent134Text10, 0, 1530 },
    { 0, 1, 3, 3, { 0, 0, 0 }, gEvent134Text11, 0, 1560 },
    { 36, 3, 1, 3, { 0, 0, 0 }, gEvent134Text12, 0, 1590 },
    { 0, 4, 3, 3, { 0, 0, 0 }, gEvent134Text13, 0, 1620 },
    { 36, 3, 1, 3, { 0, 0, 0 }, gEvent134Text14, 0, 1650 },
    { 36, 3, 4, 3, { 0, 0, 0 }, gEvent134Text15, 0, 1652 },
    { 0, 4, 3, 3, { 0, 0, 0 }, gEvent134Text16, 0, 1690 },
    { 0, 1, 4, 3, { 0, 0, 0 }, gEvent134Text17, 0, 1692 },
    { 36, 0, 1, 3, { 0, 0, 0 }, gEvent134Text18, 0, 1725 },
    { 62, 0, 3, 3, { 0, 0, 0 }, gEvent134Text19, 0, 1920 },
    { 62, 0, 3, 3, { 0, 0, 0 }, gEvent134Text20, 0, 1920 },
    { 62, 0, 3, 3, { 0, 0, 0 }, gEvent134Text21, MSG_SCRIPT_FLAG_END, 1920 },
};

#include "event_134_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent134Script[22] = {
    { 0, 0, 3, 1, { 0, 0, 0 }, &gEvent134Text00, 0, 830 },
    { 36, 0, 1, 1, { 0, 0, 0 }, &gEvent134Text01, 0, 980 },
    { 0, 0, 3, 1, { 0, 0, 0 }, &gEvent134Text02, 0, 1010 },
    { 0, 0, 3, 1, { 0, 0, 0 }, &gEvent134Text03, 0, 1155 },
    { 36, 0, 1, 1, { 0, 0, 0 }, &gEvent134Text04, 0, 1185 },
    { 0, 7, 3, 1, { 0, 0, 0 }, &gEvent134Text05, 0, 1215 },
    { 36, 2, 1, 1, { 0, 0, 0 }, &gEvent134Text06, 0, 1305 },
    { 36, 0, 4, 1, { 0, 0, 0 }, &gEvent134Text07, 0, 1309 },
    { 36, 0, 4, 1, { 0, 0, 0 }, &gEvent134Text08, 0, 1311 },
    { 0, 0, 3, 1, { 0, 0, 0 }, &gEvent134Text09, 0, 1500 },
    { 36, 0, 1, 1, { 0, 0, 0 }, &gEvent134Text10, 0, 1530 },
    { 0, 1, 3, 1, { 0, 0, 0 }, &gEvent134Text11, 0, 1560 },
    { 36, 3, 1, 1, { 0, 0, 0 }, &gEvent134Text12, 0, 1590 },
    { 0, 4, 3, 1, { 0, 0, 0 }, &gEvent134Text13, 0, 1620 },
    { 36, 3, 1, 1, { 0, 0, 0 }, &gEvent134Text14, 0, 1650 },
    { 36, 3, 4, 1, { 0, 0, 0 }, &gEvent134Text15, 0, 1652 },
    { 0, 4, 3, 1, { 0, 0, 0 }, &gEvent134Text16, 0, 1690 },
    { 0, 1, 4, 1, { 0, 0, 0 }, &gEvent134Text17, 0, 1692 },
    { 36, 0, 1, 1, { 0, 0, 0 }, &gEvent134Text18, 0, 1725 },
    { 62, 0, 3, 1, { 0, 0, 0 }, &gEvent134Text19, 0, 1920 },
    { 62, 0, 3, 1, { 0, 0, 0 }, &gEvent134Text20, 0, 1920 },
    { 62, 0, 3, 1, { 0, 0, 0 }, &gEvent134Text21, MSG_SCRIPT_FLAG_END, 1920 },
};
#endif

static const EventCameraKeyframe sEvent134Camera[3] = {
    { -65536, 109312, 65024, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, NULL },
    { -64636, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 80, { 0, 0 }, NULL },
    { -59636, 105216, 67328, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent134SoundCues[2] = {
    { SONG_BGM_WINNIETHEPOOH, 1, 0, 0 },
    { SONG_BG_POO, 2, EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent134Track0[29] = {
    { 2, 500, { 0, 0 }, 73472, 59648, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 7, 570, { 0, 0 }, 89344, 67328, 0, 2, { 0, 0 }, 67, NULL, NULL },
    { 2, 620, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 2, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 7, 770, { 0, 0 }, 100096, 71424, 0, 2, { 0, 0 }, 67, NULL, NULL },
    { 2, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 790, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 1030, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 0, 1035, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1060, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 0, 1065, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 1075, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 1080, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 1, 1110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 1115, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 1120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 1210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 34, 1340, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 34, 1470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 34, 1490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 1495, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 30, 1502, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 1615, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 36, 1660, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 1830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 1835, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 1860, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 7, 9999, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 32836, NULL, NULL },
};

static const EventCharaKeyframe sEvent134Track1[42] = {
    { 756, 1, { 0, 0 }, 110080, 67840, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 781, 130, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 68, NULL, NULL },
    { 756, 140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 765, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 764, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 765, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 756, 190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 766, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 766, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 755, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 756, 240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 757, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 758, 260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 783, 380, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 4, NULL, NULL },
    { 758, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 774, 410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 757, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 756, 590, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 757, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 758, 620, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 783, 670, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 4, NULL, NULL },
    { 758, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 774, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 775, 710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 774, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 758, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 773, 740, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 772, 860, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 759, 870, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 758, 880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 757, 890, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 756, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 781, 950, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 68, NULL, NULL },
    { 756, 1240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 798, 1300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 799, 1307, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 795, 1525, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 804, 1740, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 797, 1830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 755, 1840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 756, 1880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 781, 9999, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 32772, NULL, NULL },
};

static const EventCharaKeyframe sEvent134Track2[2] = {
    { 806, 475, { 0, 0 }, 146176, 59904, -5120, 0, { 0, 0 }, 2, NULL, NULL },
    { 806, 9999, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 33028, NULL, NULL },
};

static const EventCharaTrack sEvent134Tracks[3] = {
    { sEvent134Track0, 0, { 0, 0, 0 } },
    { sEvent134Track1, 70, { 0, 0, 0 } },
    { sEvent134Track2, 71, { 0, 0, 0 } },
};

const EventSequenceDef gEvent134 = {
    3,
    { 0, 0, 0 },
    sEvent134Tracks,
    sEvent134Camera,
    sEvent134Script,
    sEvent134SoundCues,
    NULL,
    1940,
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
    0,
};

#ifdef VERSION_US
#include "event_135_text.inc"
static const MessageScriptEntry sEvent135Script[1] = {
    { 36, 1, 1, 1, { 0, 0, 0 }, gEventTextUs_0900868C, MSG_SCRIPT_FLAG_END, 300 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent135Script[1] = {
    { 36, 1, 1, 3, { 0, 0, 0 }, gEvent135Text00, MSG_SCRIPT_FLAG_END, 300 },
};

#include "event_135_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent135Script[1] = {
    { 36, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F69614, MSG_SCRIPT_FLAG_END, 300 },
};
#endif

static const EventCameraKeyframe sEvent135Camera[2] = {
    { -65536, 105216, 67328, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, NULL },
    { -64636, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 80, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent135SoundCues[2] = {
    { SONG_BGM_WINNIETHEPOOH, 1, 0, 0 },
    { SONG_BG_POO, 2, EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent135Track0[5] = {
    { 2, 1, { 0, 0 }, 73472, 59648, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 7, 121, { 0, 0 }, 100096, 71424, 0, 2, { 0, 0 }, 67, NULL, NULL },
    { 2, 140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 145, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent135Track1[3] = {
    { 796, 160, { 0, 0 }, 110080, 67840, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 797, 1830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 756, 1880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent135Track2[2] = {
    { 806, 20, { 0, 0 }, 146176, 59904, -5120, 0, { 0, 0 }, 2, NULL, NULL },
    { 806, 9999, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 33028, NULL, NULL },
};

static const EventCharaTrack sEvent135Tracks[3] = {
    { sEvent135Track0, 0, { 0, 0, 0 } },
    { sEvent135Track1, 70, { 0, 0, 0 } },
    { sEvent135Track2, 71, { 0, 0, 0 } },
};

const EventSequenceDef gEvent135 = {
    3,
    { 0, 0, 0 },
    sEvent135Tracks,
    sEvent135Camera,
    sEvent135Script,
    sEvent135SoundCues,
    NULL,
    360,
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
    0,
};

#ifdef VERSION_US
#include "event_136_text.inc"
static const MessageScriptEntry sEvent136Script[18] = {
    { 47, 2, 3, 1, { 0, 0, 0 }, gEvent136Text00, 0, 120 },
    { 47, 1, 3, 1, { 0, 0, 0 }, gEvent136Text01, 0, 160 },
    { 0, 3, 1, 1, { 0, 0, 0 }, gEvent136Text02, 0, 180 },
    { 47, 1, 3, 1, { 0, 0, 0 }, gEvent136Text03, 0, 200 },
    { 47, 1, 4, 1, { 0, 0, 0 }, gEvent136Text04, 0, 202 },
    { 36, 1, 1, 1, { 0, 0, 0 }, gEvent136Text05, 0, 370 },
    { 47, 2, 3, 1, { 0, 0, 0 }, gEvent136Text06, 0, 420 },
    { 47, 1, 1, 1, { 0, 0, 0 }, gEvent136Text07, 0, 460 },
    { 47, 1, 4, 1, { 0, 0, 0 }, gEvent136Text08, 0, 462 },
    { 0, 0, 1, 1, { 0, 0, 0 }, gEvent136Text09, 0, 470 },
    { 36, 0, 3, 1, { 0, 0, 0 }, gEvent136Text10, 0, 500 },
    { 47, 2, 1, 1, { 0, 0, 0 }, gEvent136Text11, 0, 520 },
    { 47, 1, 1, 1, { 0, 0, 0 }, gEvent136Text12, 0, 670 },
    { 0, 0, 1, 1, { 0, 0, 0 }, gEvent136Text13, 0, 690 },
    { 47, 2, 3, 1, { 0, 0, 0 }, gEvent136Text14, 0, 795 },
    { 36, 0, 1, 1, { 0, 0, 0 }, gEvent136Text15, 0, 870 },
    { 47, 0, 3, 1, { 0, 0, 0 }, gEvent136Text16, 0, 890 },
    { 47, 0, 4, 1, { 0, 0, 0 }, gEvent136Text17, MSG_SCRIPT_FLAG_END, 892 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent136Script[18] = {
    { 47, 2, 3, 3, { 0, 0, 0 }, gEvent136Text00, 0, 120 },
    { 47, 1, 3, 3, { 0, 0, 0 }, gEvent136Text01, 0, 160 },
    { 0, 3, 1, 3, { 0, 0, 0 }, gEvent136Text02, 0, 180 },
    { 47, 1, 3, 3, { 0, 0, 0 }, gEvent136Text03, 0, 200 },
    { 47, 1, 4, 3, { 0, 0, 0 }, gEvent136Text04, 0, 202 },
    { 36, 1, 1, 3, { 0, 0, 0 }, gEvent136Text05, 0, 370 },
    { 47, 2, 3, 3, { 0, 0, 0 }, gEvent136Text06, 0, 420 },
    { 47, 1, 1, 3, { 0, 0, 0 }, gEvent136Text07, 0, 460 },
    { 47, 1, 4, 3, { 0, 0, 0 }, gEvent136Text08, 0, 462 },
    { 0, 0, 1, 3, { 0, 0, 0 }, gEvent136Text09, 0, 470 },
    { 36, 0, 3, 3, { 0, 0, 0 }, gEvent136Text10, 0, 500 },
    { 47, 2, 1, 3, { 0, 0, 0 }, gEvent136Text11, 0, 520 },
    { 47, 1, 1, 3, { 0, 0, 0 }, gEvent136Text12, 0, 670 },
    { 0, 0, 1, 3, { 0, 0, 0 }, gEvent136Text13, 0, 690 },
    { 47, 2, 3, 3, { 0, 0, 0 }, gEvent136Text14, 0, 795 },
    { 36, 0, 1, 3, { 0, 0, 0 }, gEvent136Text15, 0, 870 },
    { 47, 0, 3, 3, { 0, 0, 0 }, gEvent136Text16, 0, 890 },
    { 47, 0, 4, 3, { 0, 0, 0 }, gEvent136Text17, MSG_SCRIPT_FLAG_END, 892 },
};

#include "event_136_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent136Script[18] = {
    { 47, 2, 3, 1, { 0, 0, 0 }, &gEvent136Text00, 0, 120 },
    { 47, 1, 3, 1, { 0, 0, 0 }, &gEvent136Text01, 0, 160 },
    { 0, 3, 1, 1, { 0, 0, 0 }, &gEvent136Text02, 0, 180 },
    { 47, 1, 3, 1, { 0, 0, 0 }, &gEvent136Text03, 0, 200 },
    { 47, 1, 4, 1, { 0, 0, 0 }, &gEvent136Text04, 0, 202 },
    { 36, 1, 1, 1, { 0, 0, 0 }, &gEvent136Text05, 0, 370 },
    { 47, 2, 3, 1, { 0, 0, 0 }, &gEvent136Text06, 0, 420 },
    { 47, 1, 1, 1, { 0, 0, 0 }, &gEvent136Text07, 0, 460 },
    { 47, 1, 4, 1, { 0, 0, 0 }, &gEvent136Text08, 0, 462 },
    { 0, 0, 1, 1, { 0, 0, 0 }, &gEvent136Text09, 0, 470 },
    { 36, 0, 3, 1, { 0, 0, 0 }, &gEvent136Text10, 0, 500 },
    { 47, 2, 1, 1, { 0, 0, 0 }, &gEvent136Text11, 0, 520 },
    { 47, 1, 1, 1, { 0, 0, 0 }, &gEvent136Text12, 0, 670 },
    { 0, 0, 1, 1, { 0, 0, 0 }, &gEvent136Text13, 0, 690 },
    { 47, 2, 3, 1, { 0, 0, 0 }, &gEvent136Text14, 0, 795 },
    { 36, 0, 1, 1, { 0, 0, 0 }, &gEvent136Text15, 0, 870 },
    { 47, 0, 3, 1, { 0, 0, 0 }, &gEvent136Text16, 0, 890 },
    { 47, 0, 4, 1, { 0, 0, 0 }, &gEvent136Text17, MSG_SCRIPT_FLAG_END, 892 },
};
#endif

static const EvSoundCue sEvent136SoundCues[4] = {
    { SONG_BGM_WINNIETHEPOOH, 1, 0, 0 },
    { SONG_BG_POO, 2, 0, 0 },
    { SONG_BG_POO, 964, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_WINNIETHEPOOH, 965, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent136Camera[4] = {
    { -65306, 171008, 104704, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65113, 170752, 109568, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 40, { 0, 0 }, NULL },
    { -64796, 170752, 104704, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 40, { 0, 0 }, NULL },
    { -64537, 184832, 112640, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 40, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent136Track0[11] = {
    { 2, 470, { 0, 0 }, 173568, 106752, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 32, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 715, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 1, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 7, 795, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 2, 820, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 1, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent136Track1[20] = {
    { 811, 100, { 0, 0 }, 167168, 110848, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 811, 120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaHopLow, CreateExclamationTask },
    { 811, 125, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 812, 140, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 36, NULL, NULL },
    { 811, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 811, 430, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 813, 445, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 811, 448, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 811, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 811, 463, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 811, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 811, 530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 811, 660, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 811, 750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 811, 770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 810, 810, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 812, 850, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 100, NULL, NULL },
    { 810, 852, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 100, NULL, NULL },
    { 810, 860, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 811, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent136Track2[15] = {
    { 756, 220, { 0, 0 }, 177664, 104704, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 757, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 782, 280, { 0, 0 }, 0, 0, 0, 192, { 0, 0 }, 68, NULL, NULL },
    { 781, 335, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 68, NULL, NULL },
    { 756, 345, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 755, 425, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 761, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 756, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 782, 750, { 0, 0 }, 0, 0, 0, 64, { 0, 0 }, 4, NULL, NULL },
    { 781, 795, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 4, NULL, NULL },
    { 756, 796, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 781, 860, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 4, NULL, NULL },
    { 756, 870, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 755, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 755, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent136Tracks[3] = {
    { sEvent136Track0, 0, { 0, 0, 0 } },
    { sEvent136Track1, 72, { 0, 0, 0 } },
    { sEvent136Track2, 70, { 0, 0, 0 } },
};

const EventSequenceDef gEvent136 = {
    3,
    { 0, 0, 0 },
    sEvent136Tracks,
    sEvent136Camera,
    sEvent136Script,
    sEvent136SoundCues,
    NULL,
    970,
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
    1,
};

#ifdef VERSION_US
#include "event_137_text.inc"
static const MessageScriptEntry sEvent137Script[16] = {
    { 48, 0, 1, 1, { 0, 0, 0 }, gEvent137Text00, 0, 100 },
    { 36, 1, 3, 1, { 0, 0, 0 }, gEvent137Text01, 0, 120 },
    { 0, 1, 1, 1, { 0, 0, 0 }, gEvent137Text02, 0, 140 },
    { 48, 1, 1, 1, { 0, 0, 0 }, gEvent137Text03, 0, 160 },
    { 48, 0, 1, 1, { 0, 0, 0 }, gEvent137Text04, 0, 260 },
    { 48, 0, 4, 1, { 0, 0, 0 }, gEvent137Text05, 0, 262 },
    { 48, 0, 4, 1, { 0, 0, 0 }, gEvent137Text06, 0, 264 },
    { 48, 0, 4, 1, { 0, 0, 0 }, gEvent137Text07, 0, 266 },
    { 0, 0, 3, 1, { 0, 0, 0 }, gEvent137Text08, 0, 280 },
    { 48, 0, 1, 1, { 0, 0, 0 }, gEvent137Text09, 0, 300 },
    { 48, 1, 4, 1, { 0, 0, 0 }, gEvent137Text10, 0, 302 },
    { 36, 2, 3, 1, { 0, 0, 0 }, gEvent137Text11, 0, 400 },
    { 48, 1, 1, 1, { 0, 0, 0 }, gEvent137Text12, 0, 420 },
    { 36, 1, 3, 1, { 0, 0, 0 }, gEvent137Text13, 0, 440 },
    { 0, 4, 3, 1, { 0, 0, 0 }, gEvent137Text14, 0, 600 },
    { 48, 1, 1, 1, { 0, 0, 0 }, gEvent137Text15, MSG_SCRIPT_FLAG_END, 620 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent137Script[16] = {
    { 48, 0, 1, 3, { 0, 0, 0 }, gEvent137Text00, 0, 100 },
    { 36, 1, 3, 3, { 0, 0, 0 }, gEvent137Text01, 0, 120 },
    { 0, 1, 1, 3, { 0, 0, 0 }, gEvent137Text02, 0, 140 },
    { 48, 1, 1, 3, { 0, 0, 0 }, gEvent137Text03, 0, 160 },
    { 48, 0, 1, 3, { 0, 0, 0 }, gEvent137Text04, 0, 260 },
    { 48, 0, 4, 3, { 0, 0, 0 }, gEvent137Text05, 0, 262 },
    { 48, 0, 4, 3, { 0, 0, 0 }, gEvent137Text06, 0, 264 },
    { 48, 0, 4, 3, { 0, 0, 0 }, gEvent137Text07, 0, 266 },
    { 0, 0, 3, 3, { 0, 0, 0 }, gEvent137Text08, 0, 280 },
    { 48, 0, 1, 3, { 0, 0, 0 }, gEvent137Text09, 0, 300 },
    { 48, 1, 4, 3, { 0, 0, 0 }, gEvent137Text10, 0, 302 },
    { 36, 2, 3, 3, { 0, 0, 0 }, gEvent137Text11, 0, 400 },
    { 48, 1, 1, 3, { 0, 0, 0 }, gEvent137Text12, 0, 420 },
    { 36, 1, 3, 3, { 0, 0, 0 }, gEvent137Text13, 0, 440 },
    { 0, 4, 3, 3, { 0, 0, 0 }, gEvent137Text14, 0, 600 },
    { 48, 1, 1, 3, { 0, 0, 0 }, gEvent137Text15, MSG_SCRIPT_FLAG_END, 620 },
};

#include "event_137_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent137Script[16] = {
    { 48, 0, 1, 1, { 0, 0, 0 }, &gEvent137Text00, 0, 100 },
    { 36, 1, 3, 1, { 0, 0, 0 }, &gEvent137Text01, 0, 120 },
    { 0, 1, 1, 1, { 0, 0, 0 }, &gEvent137Text02, 0, 140 },
    { 48, 1, 1, 1, { 0, 0, 0 }, &gEvent137Text03, 0, 160 },
    { 48, 0, 1, 1, { 0, 0, 0 }, &gEvent137Text04, 0, 260 },
    { 48, 0, 4, 1, { 0, 0, 0 }, &gEvent137Text05, 0, 262 },
    { 48, 0, 4, 1, { 0, 0, 0 }, &gEvent137Text06, 0, 264 },
    { 48, 0, 4, 1, { 0, 0, 0 }, &gEvent137Text07, 0, 266 },
    { 0, 0, 3, 1, { 0, 0, 0 }, &gEvent137Text08, 0, 280 },
    { 48, 0, 1, 1, { 0, 0, 0 }, &gEvent137Text09, 0, 300 },
    { 48, 1, 4, 1, { 0, 0, 0 }, &gEvent137Text10, 0, 302 },
    { 36, 2, 3, 1, { 0, 0, 0 }, &gEvent137Text11, 0, 400 },
    { 48, 1, 1, 1, { 0, 0, 0 }, &gEvent137Text12, 0, 420 },
    { 36, 1, 3, 1, { 0, 0, 0 }, &gEvent137Text13, 0, 440 },
    { 0, 4, 3, 1, { 0, 0, 0 }, &gEvent137Text14, 0, 600 },
    { 48, 1, 1, 1, { 0, 0, 0 }, &gEvent137Text15, MSG_SCRIPT_FLAG_END, 620 },
};
#endif

static const EvSoundCue sEvent137SoundCues[4] = {
    { SONG_BGM_WINNIETHEPOOH, 0, 0, 0 },
    { SONG_BG_POO, 2, 0, 0 },
    { SONG_BG_POO, 824, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_WINNIETHEPOOH, 825, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent137Camera[1] = {
    { -65226, 237824, 121344, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent137Track0[10] = {
    { 4, 130, { 0, 0 }, 235008, 129536, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 0, 135, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 0, 175, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateQuestionTask },
    { 4, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 34, 290, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 670, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent137Track1[6] = {
    { 756, 180, { 0, 0 }, 229120, 126464, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 765, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateQuestionTask },
    { 765, 310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 798, 399, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 799, 421, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 800, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent137Track2[6] = {
    { 814, 155, { 0, 0 }, 244736, 121344, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 815, 415, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 815, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 814, 590, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 814, 630, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 815, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent137Tracks[3] = {
    { sEvent137Track0, 0, { 0, 0, 0 } },
    { sEvent137Track1, 70, { 0, 0, 0 } },
    { sEvent137Track2, 73, { 0, 0, 0 } },
};

const EventSequenceDef gEvent137 = {
    3,
    { 0, 0, 0 },
    sEvent137Tracks,
    sEvent137Camera,
    sEvent137Script,
    sEvent137SoundCues,
    NULL,
    830,
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
    2,
};

#ifdef VERSION_US
static const MessageScriptEntry sEvent138Script[1] = {
    { 48, 1, 1, 1, { 0, 0, 0 }, gCardMessageTextUs_0903C186, MSG_SCRIPT_FLAG_END, 150 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent138Script[1] = {
    { 48, 1, 1, 3, { 0, 0, 0 }, gEvent138Text00, MSG_SCRIPT_FLAG_END, 150 },
};

#include "event_138_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent138Script[1] = {
    { 48, 1, 1, 1, { 0, 0, 0 }, &gUnkEu_09F68354, MSG_SCRIPT_FLAG_END, 150 },
};
#endif

static const EvSoundCue sEvent138SoundCues[2] = {
    { SONG_BGM_WINNIETHEPOOH, 1, 0, 0 },
    { SONG_BG_POO, 2, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent138Camera[1] = {
    { -65226, 237824, 121344, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent138Track0[2] = {
    { 4, 130, { 0, 0 }, 235008, 129536, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 4, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent138Track1[2] = {
    { 756, 180, { 0, 0 }, 229120, 126464, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 756, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent138Track2[3] = {
    { 814, 80, { 0, 0 }, 244736, 121344, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 815, 415, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 815, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent138Tracks[3] = {
    { sEvent138Track0, 0, { 0, 0, 0 } },
    { sEvent138Track1, 70, { 0, 0, 0 } },
    { sEvent138Track2, 73, { 0, 0, 0 } },
};

const EventSequenceDef gEvent138 = {
    3,
    { 0, 0, 0 },
    sEvent138Tracks,
    sEvent138Camera,
    sEvent138Script,
    sEvent138SoundCues,
    NULL,
    210,
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
    2,
};

#ifdef VERSION_US
#include "event_139_text.inc"
static const MessageScriptEntry sEvent139Script[12] = {
    { 36, 0, 3, 1, { 0, 0, 0 }, gEvent139Text00, 0, 100 },
    { 51, 0, 1, 1, { 0, 0, 0 }, gEvent139Text01, 0, 130 },
    { 36, 0, 3, 1, { 0, 0, 0 }, gEvent139Text02, 0, 160 },
    { 51, 0, 1, 1, { 0, 0, 0 }, gEvent139Text03, 0, 190 },
    { 51, 1, 4, 1, { 0, 0, 0 }, gEvent139Text04, 0, 192 },
    { 51, 1, 4, 1, { 0, 0, 0 }, gEvent139Text05, 0, 194 },
    { 0, 1, 3, 1, { 0, 0, 0 }, gEvent139Text06, 0, 225 },
    { 36, 1, 3, 1, { 0, 0, 0 }, gEvent139Text07, 0, 255 },
    { 51, 0, 1, 1, { 0, 0, 0 }, gEvent139Text08, 0, 430 },
    { 0, 4, 3, 1, { 0, 0, 0 }, gEvent139Text09, 0, 460 },
    { 51, 1, 1, 1, { 0, 0, 0 }, gEvent139Text10, 0, 490 },
    { 51, 1, 1, 1, { 0, 0, 0 }, gEvent139Text11, MSG_SCRIPT_FLAG_END, 760 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent139Script[12] = {
    { 36, 0, 3, 3, { 0, 0, 0 }, gEvent139Text00, 0, 100 },
    { 51, 0, 1, 3, { 0, 0, 0 }, gEvent139Text01, 0, 130 },
    { 36, 0, 3, 3, { 0, 0, 0 }, gEvent139Text02, 0, 160 },
    { 51, 0, 1, 3, { 0, 0, 0 }, gEvent139Text03, 0, 190 },
    { 51, 1, 4, 3, { 0, 0, 0 }, gEvent139Text04, 0, 192 },
    { 51, 1, 4, 3, { 0, 0, 0 }, gEvent139Text05, 0, 194 },
    { 0, 1, 3, 3, { 0, 0, 0 }, gEvent139Text06, 0, 225 },
    { 36, 1, 3, 3, { 0, 0, 0 }, gEvent139Text07, 0, 255 },
    { 51, 0, 1, 3, { 0, 0, 0 }, gEvent139Text08, 0, 430 },
    { 0, 4, 3, 3, { 0, 0, 0 }, gEvent139Text09, 0, 460 },
    { 51, 1, 1, 3, { 0, 0, 0 }, gEvent139Text10, 0, 490 },
    { 51, 1, 1, 3, { 0, 0, 0 }, gEvent139Text11, MSG_SCRIPT_FLAG_END, 760 },
};

#include "event_139_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent139Script[12] = {
    { 36, 0, 3, 1, { 0, 0, 0 }, &gEvent139Text00, 0, 100 },
    { 51, 0, 1, 1, { 0, 0, 0 }, &gEvent139Text01, 0, 130 },
    { 36, 0, 3, 1, { 0, 0, 0 }, &gEvent139Text02, 0, 160 },
    { 51, 0, 1, 1, { 0, 0, 0 }, &gEvent139Text03, 0, 190 },
    { 51, 1, 4, 1, { 0, 0, 0 }, &gEvent139Text04, 0, 192 },
    { 51, 1, 4, 1, { 0, 0, 0 }, &gEvent139Text05, 0, 194 },
    { 0, 1, 3, 1, { 0, 0, 0 }, &gEvent139Text06, 0, 225 },
    { 36, 1, 3, 1, { 0, 0, 0 }, &gEvent139Text07, 0, 255 },
    { 51, 0, 1, 1, { 0, 0, 0 }, &gEvent139Text08, 0, 430 },
    { 0, 4, 3, 1, { 0, 0, 0 }, &gEvent139Text09, 0, 460 },
    { 51, 1, 1, 1, { 0, 0, 0 }, &gEvent139Text10, 0, 490 },
    { 51, 1, 1, 1, { 0, 0, 0 }, &gEvent139Text11, MSG_SCRIPT_FLAG_END, 760 },
};
#endif

static const EvSoundCue sEvent139SoundCues[11] = {
    { SONG_BGM_WINNIETHEPOOH, 0, 0, 0 },
    { SONG_BG_POO, 2, 0, 0 },
    { SONG_SYS_LU_JP, 521, 0, 0 },
    { SONG_SYS_LU_JP, 559, 0, 0 },
    { SONG_SYS_LU_JP, 640, 0, 0 },
    { SONG_SYS_LU_JP, 679, 0, 0 },
    { SONG_SYS_LU_JP, 820, 0, 0 },
    { SONG_SYS_LU_JP, 855, 0, 0 },
    { SONG_SYS_LU_JP, 890, 0, 0 },
    { SONG_BG_POO, 914, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_WINNIETHEPOOH, 915, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent139Camera[1] = {
    { -65336, 323328, 177152, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent139Track0[11] = {
    { 4, 220, { 0, 0 }, 316928, 179456, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 36, 440, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 34, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 535, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 695, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 835, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent139Track1[8] = {
    { 758, 520, { 0, 0 }, 322560, 182784, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 774, 530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 775, 710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 774, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 758, 840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 772, 850, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 757, 860, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 756, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent139Track2[14] = {
    { 816, 270, { 0, 0 }, 327680, 179456, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 816, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 816, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 816, 520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 818, 580, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 100, NULL, NULL },
    { 816, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 816, 610, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 817, 640, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 819, 700, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 817, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 816, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 816, 820, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 818, 1000, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 100, NULL, NULL },
    { 816, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent139Tracks[3] = {
    { sEvent139Track0, 0, { 0, 0, 0 } },
    { sEvent139Track1, 70, { 0, 0, 0 } },
    { sEvent139Track2, 74, { 0, 0, 0 } },
};

const EventSequenceDef gEvent139 = {
    3,
    { 0, 0, 0 },
    sEvent139Tracks,
    sEvent139Camera,
    sEvent139Script,
    sEvent139SoundCues,
    NULL,
    920,
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
    3,
};

#ifdef VERSION_US
#include "event_140_text.inc"
static const MessageScriptEntry sEvent140Script[14] = {
    { 36, 2, 1, 1, { 0, 0, 0 }, gEvent140Text00, 0, 90 },
    { 50, 0, 3, 1, { 0, 0, 0 }, gEvent140Text01, 0, 115 },
    { 36, 3, 1, 1, { 0, 0, 0 }, gEvent140Text02, 0, 160 },
    { 50, 0, 3, 1, { 0, 0, 0 }, gEvent140Text03, 0, 190 },
    { 36, 0, 1, 1, { 0, 0, 0 }, gEvent140Text04, 0, 300 },
    { 36, 1, 4, 1, { 0, 0, 0 }, gEvent140Text05, 0, 302 },
    { 50, 0, 3, 1, { 0, 0, 0 }, gEvent140Text06, 0, 360 },
    { 0, 1, 1, 1, { 0, 0, 0 }, gEvent140Text07, 0, 390 },
    { 50, 0, 3, 1, { 0, 0, 0 }, gEvent140Text08, 0, 420 },
    { 50, 0, 4, 1, { 0, 0, 0 }, gEvent140Text09, 0, 422 },
    { 36, 0, 1, 1, { 0, 0, 0 }, gEvent140Text10, 0, 460 },
    { 50, 0, 3, 1, { 0, 0, 0 }, gEvent140Text11, 0, 500 },
    { 0, 3, 1, 1, { 0, 0, 0 }, gEvent140Text12, 0, 530 },
    { 50, 0, 3, 1, { 0, 0, 0 }, gEvent140Text13, MSG_SCRIPT_FLAG_END, 560 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent140Script[14] = {
    { 36, 2, 1, 3, { 0, 0, 0 }, gEvent140Text00, 0, 90 },
    { 50, 0, 3, 3, { 0, 0, 0 }, gEvent140Text01, 0, 115 },
    { 36, 3, 1, 3, { 0, 0, 0 }, gEvent140Text02, 0, 160 },
    { 50, 0, 3, 3, { 0, 0, 0 }, gEvent140Text03, 0, 190 },
    { 36, 0, 1, 3, { 0, 0, 0 }, gEvent140Text04, 0, 300 },
    { 36, 1, 4, 3, { 0, 0, 0 }, gEvent140Text05, 0, 302 },
    { 50, 0, 3, 3, { 0, 0, 0 }, gEvent140Text06, 0, 360 },
    { 0, 1, 1, 3, { 0, 0, 0 }, gEvent140Text07, 0, 390 },
    { 50, 0, 3, 3, { 0, 0, 0 }, gEvent140Text08, 0, 420 },
    { 50, 0, 4, 3, { 0, 0, 0 }, gEvent140Text09, 0, 422 },
    { 36, 0, 1, 3, { 0, 0, 0 }, gEvent140Text10, 0, 460 },
    { 50, 0, 3, 3, { 0, 0, 0 }, gEvent140Text11, 0, 500 },
    { 0, 3, 1, 3, { 0, 0, 0 }, gEvent140Text12, 0, 530 },
    { 50, 0, 3, 3, { 0, 0, 0 }, gEvent140Text13, MSG_SCRIPT_FLAG_END, 560 },
};

#include "event_140_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent140Script[14] = {
    { 36, 2, 1, 1, { 0, 0, 0 }, &gEvent140Text00, 0, 90 },
    { 50, 0, 3, 1, { 0, 0, 0 }, &gEvent140Text01, 0, 115 },
    { 36, 3, 1, 1, { 0, 0, 0 }, &gEvent140Text02, 0, 160 },
    { 50, 0, 3, 1, { 0, 0, 0 }, &gEvent140Text03, 0, 190 },
    { 36, 0, 1, 1, { 0, 0, 0 }, &gEvent140Text04, 0, 300 },
    { 36, 1, 4, 1, { 0, 0, 0 }, &gEvent140Text05, 0, 302 },
    { 50, 0, 3, 1, { 0, 0, 0 }, &gEvent140Text06, 0, 360 },
    { 0, 1, 1, 1, { 0, 0, 0 }, &gEvent140Text07, 0, 390 },
    { 50, 0, 3, 1, { 0, 0, 0 }, &gEvent140Text08, 0, 420 },
    { 50, 0, 4, 1, { 0, 0, 0 }, &gEvent140Text09, 0, 422 },
    { 36, 0, 1, 1, { 0, 0, 0 }, &gEvent140Text10, 0, 460 },
    { 50, 0, 3, 1, { 0, 0, 0 }, &gEvent140Text11, 0, 500 },
    { 0, 3, 1, 1, { 0, 0, 0 }, &gEvent140Text12, 0, 530 },
    { 50, 0, 3, 1, { 0, 0, 0 }, &gEvent140Text13, MSG_SCRIPT_FLAG_END, 560 },
};
#endif

static const EvSoundCue sEvent140SoundCues[4] = {
    { SONG_BGM_WINNIETHEPOOH, 1, 0, 0 },
    { SONG_BG_POO, 2, 0, 0 },
    { SONG_BG_POO, 614, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_WINNIETHEPOOH, 615, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent140Camera[1] = {
    { -64537, 529664, 289536, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent140Track0[5] = {
    { 4, 385, { 0, 0 }, 536064, 294144, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 36, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 525, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 27, 532, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent140Track1[5] = {
    { 802, 125, { 0, 0 }, 530432, 286720, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 803, 149, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 804, 200, { 0, 0 }, 529664, 287232, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 797, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 756, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent140Track2[4] = {
    { 821, 330, { 0, 0 }, 521472, 292352, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 820, 430, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 821, 470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 820, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent140Track3[2] = {
    { 808, 150, { 0, 0 }, 526848, 313856, -2560, 0, { 0, 0 }, 2, NULL, NULL },
    { 808, 500, { 0, 0 }, 494592, 295424, -2560, 808, { 0, 0 }, 32771, NULL, NULL },
};

static const EventCharaTrack sEvent140Tracks[4] = {
    { sEvent140Track0, 0, { 0, 0, 0 } },
    { sEvent140Track1, 70, { 0, 0, 0 } },
    { sEvent140Track2, 75, { 0, 0, 0 } },
    { sEvent140Track3, 71, { 0, 0, 0 } },
};

const EventSequenceDef gEvent140 = {
    3,
    { 0, 0, 0 },
    sEvent140Tracks,
    sEvent140Camera,
    sEvent140Script,
    sEvent140SoundCues,
    NULL,
    620,
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
    4,
};

#ifdef VERSION_US
#include "event_141_text.inc"
static const MessageScriptEntry sEvent141Script[15] = {
    { 59, 0, 3, 1, { 0, 0, 0 }, gEvent141Text00, 0, 210 },
    { 36, 1, 0, 1, { 0, 0, 0 }, gEvent141Text01, 0, 240 },
    { 59, 1, 3, 1, { 0, 0, 0 }, gEvent141Text02, 0, 270 },
    { 0, 3, 0, 1, { 0, 0, 0 }, gEvent141Text03, 0, 370 },
    { 59, 2, 3, 1, { 0, 0, 0 }, gEvent141Text04, 0, 410 },
    { 59, 2, 4, 1, { 0, 0, 0 }, gEvent141Text05, 0, 414 },
    { 59, 1, 4, 1, { 0, 0, 0 }, gEvent141Text06, 0, 418 },
    { 0, 0, 0, 1, { 0, 0, 0 }, gEvent141Text07, 0, 450 },
    { 59, 1, 3, 1, { 0, 0, 0 }, gEvent141Text08, 0, 480 },
    { 59, 1, 4, 1, { 0, 0, 0 }, gEvent141Text09, 0, 484 },
    { 59, 2, 1, 1, { 0, 0, 0 }, gEvent141Text10, 0, 870 },
    { 0, 1, 2, 1, { 0, 0, 0 }, gEvent141Text11, 0, 900 },
    { 59, 2, 1, 1, { 0, 0, 0 }, gEvent141Text12, 0, 930 },
    { 59, 2, 4, 1, { 0, 0, 0 }, gEvent141Text13, 0, 934 },
    { 36, 3, 3, 1, { 0, 0, 0 }, gEvent141Text14, MSG_SCRIPT_FLAG_END, 1270 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent141Script[15] = {
    { 59, 0, 3, 3, { 0, 0, 0 }, gEvent141Text00, 0, 210 },
    { 36, 1, 0, 3, { 0, 0, 0 }, gEvent141Text01, 0, 240 },
    { 59, 1, 3, 3, { 0, 0, 0 }, gEvent141Text02, 0, 270 },
    { 0, 3, 0, 3, { 0, 0, 0 }, gEvent141Text03, 0, 370 },
    { 59, 2, 3, 3, { 0, 0, 0 }, gEvent141Text04, 0, 410 },
    { 59, 2, 4, 3, { 0, 0, 0 }, gEvent141Text05, 0, 414 },
    { 59, 1, 4, 3, { 0, 0, 0 }, gEvent141Text06, 0, 418 },
    { 0, 0, 0, 3, { 0, 0, 0 }, gEvent141Text07, 0, 450 },
    { 59, 1, 3, 3, { 0, 0, 0 }, gEvent141Text08, 0, 480 },
    { 59, 1, 4, 3, { 0, 0, 0 }, gEvent141Text09, 0, 484 },
    { 59, 2, 1, 3, { 0, 0, 0 }, gEvent141Text10, 0, 870 },
    { 0, 1, 2, 3, { 0, 0, 0 }, gEvent141Text11, 0, 900 },
    { 59, 2, 1, 3, { 0, 0, 0 }, gEvent141Text12, 0, 930 },
    { 59, 2, 4, 3, { 0, 0, 0 }, gEvent141Text13, 0, 934 },
    { 36, 3, 3, 3, { 0, 0, 0 }, gEvent141Text14, MSG_SCRIPT_FLAG_END, 1270 },
};

#include "event_141_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent141Script[15] = {
    { 59, 0, 3, 1, { 0, 0, 0 }, &gEvent141Text00, 0, 210 },
    { 36, 1, 0, 1, { 0, 0, 0 }, &gEvent141Text01, 0, 240 },
    { 59, 1, 3, 1, { 0, 0, 0 }, &gEvent141Text02, 0, 270 },
    { 0, 3, 0, 1, { 0, 0, 0 }, &gEvent141Text03, 0, 370 },
    { 59, 2, 3, 1, { 0, 0, 0 }, &gEvent141Text04, 0, 410 },
    { 59, 2, 4, 1, { 0, 0, 0 }, &gEvent141Text05, 0, 414 },
    { 59, 1, 4, 1, { 0, 0, 0 }, &gEvent141Text06, 0, 418 },
    { 0, 0, 0, 1, { 0, 0, 0 }, &gEvent141Text07, 0, 450 },
    { 59, 1, 3, 1, { 0, 0, 0 }, &gEvent141Text08, 0, 480 },
    { 59, 1, 4, 1, { 0, 0, 0 }, &gEvent141Text09, 0, 484 },
    { 59, 2, 1, 1, { 0, 0, 0 }, &gEvent141Text10, 0, 870 },
    { 0, 1, 2, 1, { 0, 0, 0 }, &gEvent141Text11, 0, 900 },
    { 59, 2, 1, 1, { 0, 0, 0 }, &gEvent141Text12, 0, 930 },
    { 59, 2, 4, 1, { 0, 0, 0 }, &gEvent141Text13, 0, 934 },
    { 36, 3, 3, 1, { 0, 0, 0 }, &gEvent141Text14, MSG_SCRIPT_FLAG_END, 1270 },
};
#endif

static const EvSoundCue sEvent141SoundCues[14] = {
    { SONG_BGM_WINNIETHEPOOH, 1, 0, 0 },
    { SONG_BG_POO, 2, 0, 0 },
    { SONG_SYS_TIGGER_JP, 524, 0, 0 },
    { SONG_SYS_TIGGER_JP, 573, 0, 0 },
    { SONG_SYS_TIGGER_JP, 609, 0, 0 },
    { SONG_SYS_TIGGER_JP, 645, 0, 0 },
    { SONG_SYS_TIGGER_JP, 681, 0, 0 },
    { SONG_SYS_TIGGER_JP, 717, 0, 0 },
    { SONG_SYS_TIGGER_JP, 753, 0, 0 },
    { SONG_SYS_TIGGER_JP, 788, 0, 0 },
    { SONG_SND_961, 1015, 0, 0 },
    { SONG_SND_961, 1050, 0, 0 },
    { SONG_BG_POO, 1294, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_WINNIETHEPOOH, 1295, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent141Camera[7] = {
    { -65486, 588288, 323840, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65036, 582144, 319232, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -64986, 582144, 307200, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -64914, 588288, 312320, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 36, { 0, 0 }, NULL },
    { -64842, 590592, 307200, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 72, { 0, 0 }, NULL },
    { -64516, 588288, 318720, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 72, { 0, 0 }, NULL },
    { -63536, 592896, 327424, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 70, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent141Track0[13] = {
    { 4, 160, { 0, 0 }, 580864, 329984, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 0, 165, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 290, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 340, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateQuestionTask },
    { 4, 445, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 30, 452, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 0, 580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 895, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 36, 925, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 970, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 980, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent141Track1[32] = {
    { 822, 10, { 0, 0 }, 551680, 306688, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 833, 180, { 0, 0 }, 574720, 322048, 0, 822, { 0, 0 }, 67, NULL, NULL },
    { 822, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 826, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 823, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 830, 546, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 85, NULL, NULL },
    { 831, 549, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 85, NULL, NULL },
    { 831, 579, { 0, 0 }, 583680, 315648, 0, 0, { 0, 0 }, 4435, EventCharaHop, NULL },
    { 831, 582, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 341, NULL, NULL },
    { 827, 585, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 341, NULL, NULL },
    { 827, 615, { 0, 0 }, 593152, 321024, 0, 0, { 0, 0 }, 4435, EventCharaHop, NULL },
    { 827, 618, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 341, NULL, NULL },
    { 831, 621, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 341, NULL, NULL },
    { 831, 651, { 0, 0 }, 602368, 316160, 0, 0, { 0, 0 }, 4435, EventCharaHop, NULL },
    { 831, 654, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 341, NULL, NULL },
    { 831, 657, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 277, NULL, NULL },
    { 831, 687, { 0, 0 }, 592896, 311040, 0, 0, { 0, 0 }, 4371, EventCharaHop, NULL },
    { 831, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 277, NULL, NULL },
    { 827, 693, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 277, NULL, NULL },
    { 827, 723, { 0, 0 }, 583680, 315648, 0, 0, { 0, 0 }, 4371, EventCharaHop, NULL },
    { 827, 726, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 277, NULL, NULL },
    { 827, 729, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 341, NULL, NULL },
    { 827, 759, { 0, 0 }, 593152, 321024, 0, 0, { 0, 0 }, 4435, EventCharaHop, NULL },
    { 827, 762, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 341, NULL, NULL },
    { 828, 853, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 277, NULL, NULL },
    { 832, 872, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 277, NULL, NULL },
    { 834, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 277, NULL, NULL },
    { 822, 950, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 277, NULL, NULL },
    { 822, 980, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 341, NULL, NULL },
    { 824, 990, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 372, NULL, NULL },
    { 824, 1150, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 116, NULL, NULL },
    { 822, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98309, NULL, NULL },
};

static const EventCharaKeyframe sEvent141Track2[13] = {
    { 756, 155, { 0, 0 }, 590080, 328960, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 765, 165, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 758, 580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 773, 620, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 758, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 772, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 758, 980, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 757, 1090, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 757, 1110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 782, 1190, { 0, 0 }, 0, 0, 0, 64, { 0, 0 }, 4, NULL, NULL },
    { 757, 1200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 756, 1230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 795, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33093, NULL, NULL },
};

static const EventCharaTrack sEvent141Tracks[3] = {
    { sEvent141Track0, 0, { 0, 0, 0 } },
    { sEvent141Track1, 76, { 0, 0, 0 } },
    { sEvent141Track2, 70, { 0, 0, 0 } },
};

const EventSequenceDef gEvent141 = {
    3,
    { 0, 0, 0 },
    sEvent141Tracks,
    sEvent141Camera,
    sEvent141Script,
    sEvent141SoundCues,
    NULL,
    1300,
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
    5,
};

#ifdef VERSION_US
#include "event_142_text.inc"
static const MessageScriptEntry sEvent142Script[21] = {
    { 0, 7, 3, 1, { 0, 0, 0 }, gEvent142Text00, 0, 100 },
    { 36, 0, 3, 1, { 0, 0, 0 }, gEvent142Text01, 0, 150 },
    { 0, 7, 3, 1, { 0, 0, 0 }, gEvent142Text02, 0, 290 },
    { 49, 2, 2, 1, { 0, 0, 0 }, gEvent142Text03, 0, 340 },
    { 36, 0, 0, 1, { 0, 0, 0 }, gEvent142Text04, 0, 530 },
    { 49, 2, 3, 1, { 0, 0, 0 }, gEvent142Text05, 0, 560 },
    { 0, 0, 3, 1, { 0, 0, 0 }, gEvent142Text06, 0, 600 },
    { 49, 2, 1, 1, { 0, 0, 0 }, gEvent142Text07, 0, 830 },
    { 49, 1, 4, 1, { 0, 0, 0 }, gEvent142Text08, 0, 847 },
    { 36, 0, 2, 1, { 0, 0, 0 }, gEvent142Text09, 0, 880 },
    { 0, 1, 3, 1, { 0, 0, 0 }, gEvent142Text10, 0, 910 },
    { 49, 2, 1, 1, { 0, 0, 0 }, gEvent142Text11, 0, 940 },
    { 49, 1, 1, 1, { 0, 0, 0 }, gEvent142Text12, 0, 1035 },
    { 36, 0, 2, 1, { 0, 0, 0 }, gEvent142Text13, 0, 1060 },
    { 0, 3, 3, 1, { 0, 0, 0 }, gEvent142Text14, 0, 1085 },
    { 36, 0, 2, 1, { 0, 0, 0 }, gEvent142Text15, 0, 1160 },
    { 49, 0, 1, 1, { 0, 0, 0 }, gEvent142Text16, 0, 1190 },
    { 49, 0, 1, 1, { 0, 0, 0 }, gEvent142Text17, 0, 1300 },
    { 0, 1, 3, 1, { 0, 0, 0 }, gEvent142Text18, 0, 1330 },
    { 49, 2, 1, 1, { 0, 0, 0 }, gEvent142Text19, 0, 1360 },
    { 0, 3, 3, 1, { 0, 0, 0 }, gEvent142Text20, MSG_SCRIPT_FLAG_END, 1390 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent142Script[21] = {
    { 0, 7, 3, 3, { 0, 0, 0 }, gEvent142Text00, 0, 100 },
    { 36, 0, 3, 3, { 0, 0, 0 }, gEvent142Text01, 0, 150 },
    { 0, 7, 3, 3, { 0, 0, 0 }, gEvent142Text02, 0, 290 },
    { 49, 2, 2, 3, { 0, 0, 0 }, gEvent142Text03, 0, 340 },
    { 36, 0, 0, 3, { 0, 0, 0 }, gEvent142Text04, 0, 530 },
    { 49, 2, 3, 3, { 0, 0, 0 }, gEvent142Text05, 0, 560 },
    { 0, 0, 3, 3, { 0, 0, 0 }, gEvent142Text06, 0, 600 },
    { 49, 2, 1, 3, { 0, 0, 0 }, gEvent142Text07, 0, 830 },
    { 49, 1, 4, 3, { 0, 0, 0 }, gEvent142Text08, 0, 847 },
    { 36, 0, 2, 3, { 0, 0, 0 }, gEvent142Text09, 0, 880 },
    { 0, 1, 3, 3, { 0, 0, 0 }, gEvent142Text10, 0, 910 },
    { 49, 2, 1, 3, { 0, 0, 0 }, gEvent142Text11, 0, 940 },
    { 49, 1, 1, 3, { 0, 0, 0 }, gEvent142Text12, 0, 1035 },
    { 36, 0, 2, 3, { 0, 0, 0 }, gEvent142Text13, 0, 1060 },
    { 0, 3, 3, 3, { 0, 0, 0 }, gEvent142Text14, 0, 1085 },
    { 36, 0, 2, 3, { 0, 0, 0 }, gEvent142Text15, 0, 1160 },
    { 49, 0, 1, 3, { 0, 0, 0 }, gEvent142Text16, 0, 1190 },
    { 49, 0, 1, 3, { 0, 0, 0 }, gEvent142Text17, 0, 1300 },
    { 0, 1, 3, 3, { 0, 0, 0 }, gEvent142Text18, 0, 1330 },
    { 49, 2, 1, 3, { 0, 0, 0 }, gEvent142Text19, 0, 1360 },
    { 0, 3, 3, 3, { 0, 0, 0 }, gEvent142Text20, MSG_SCRIPT_FLAG_END, 1390 },
};

#include "event_142_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent142Script[21] = {
    { 0, 7, 3, 1, { 0, 0, 0 }, &gEvent142Text00, 0, 100 },
    { 36, 0, 3, 1, { 0, 0, 0 }, &gEvent142Text01, 0, 150 },
    { 0, 7, 3, 1, { 0, 0, 0 }, &gEvent142Text02, 0, 290 },
    { 49, 2, 2, 1, { 0, 0, 0 }, &gEvent142Text03, 0, 340 },
    { 36, 0, 0, 1, { 0, 0, 0 }, &gEvent142Text04, 0, 530 },
    { 49, 2, 3, 1, { 0, 0, 0 }, &gEvent142Text05, 0, 560 },
    { 0, 0, 3, 1, { 0, 0, 0 }, &gEvent142Text06, 0, 600 },
    { 49, 2, 1, 1, { 0, 0, 0 }, &gEvent142Text07, 0, 830 },
    { 49, 1, 4, 1, { 0, 0, 0 }, &gEvent142Text08, 0, 847 },
    { 36, 0, 2, 1, { 0, 0, 0 }, &gEvent142Text09, 0, 880 },
    { 0, 1, 3, 1, { 0, 0, 0 }, &gEvent142Text10, 0, 910 },
    { 49, 2, 1, 1, { 0, 0, 0 }, &gEvent142Text11, 0, 940 },
    { 49, 1, 1, 1, { 0, 0, 0 }, &gEvent142Text12, 0, 1035 },
    { 36, 0, 2, 1, { 0, 0, 0 }, &gEvent142Text13, 0, 1060 },
    { 0, 3, 3, 1, { 0, 0, 0 }, &gEvent142Text14, 0, 1085 },
    { 36, 0, 2, 1, { 0, 0, 0 }, &gEvent142Text15, 0, 1160 },
    { 49, 0, 1, 1, { 0, 0, 0 }, &gEvent142Text16, 0, 1190 },
    { 49, 0, 1, 1, { 0, 0, 0 }, &gEvent142Text17, 0, 1300 },
    { 0, 1, 3, 1, { 0, 0, 0 }, &gEvent142Text18, 0, 1330 },
    { 49, 2, 1, 1, { 0, 0, 0 }, &gEvent142Text19, 0, 1360 },
    { 0, 3, 3, 1, { 0, 0, 0 }, &gEvent142Text20, MSG_SCRIPT_FLAG_END, 1390 },
};
#endif

static const EvSoundCue sEvent142SoundCues[4] = {
    { SONG_BGM_WINNIETHEPOOH, 1, 0, 0 },
    { SONG_BG_POO, 2, 0, 0 },
    { SONG_BG_POO, 1444, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_WINNIETHEPOOH, 1445, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent142Camera[4] = {
    { -65146, 680192, 359424, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64916, 675840, 353280, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -64796, 683264, 353280, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -63536, 681728, 356352, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent142Track0[25] = {
    { 4, 110, { 0, 0 }, 675584, 361728, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 3, 115, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 255, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 34, 345, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 0, 365, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 0, 575, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 905, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 34, 960, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 27, 970, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 27, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 27, 1065, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 1070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 1075, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 1080, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 31, 1090, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 1200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 1205, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 1325, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 36, 1370, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 27, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent142Track1[14] = {
    { 835, 390, { 0, 0 }, 651520, 336384, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 837, 450, { 0, 0 }, 668416, 347136, 0, 835, { 0, 0 }, 67, NULL, NULL },
    { 835, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 835, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 835, 740, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 837, 790, { 0, 0 }, 692224, 357632, 0, 835, { 0, 0 }, 67, NULL, NULL },
    { 835, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 838, 832, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 835, 845, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 835, 1095, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 835, 1145, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateQuestionTask },
    { 835, 1240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 836, 1260, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 835, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent142Track2[11] = {
    { 796, 160, { 0, 0 }, 683520, 366336, 0, 0, { 0, 0 }, 322, NULL, NULL },
    { 797, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 757, 310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 758, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 772, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 777, 390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 758, 770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 772, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 778, 790, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 758, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 758, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent142Tracks[3] = {
    { sEvent142Track0, 0, { 0, 0, 0 } },
    { sEvent142Track1, 77, { 0, 0, 0 } },
    { sEvent142Track2, 70, { 0, 0, 0 } },
};

const EventSequenceDef gEvent142 = {
    3,
    { 0, 0, 0 },
    sEvent142Tracks,
    sEvent142Camera,
    sEvent142Script,
    sEvent142SoundCues,
    NULL,
    1450,
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
    6,
};

#ifdef VERSION_US
#include "event_143_text.inc"
static const MessageScriptEntry sEvent143Script[16] = {
    { 0, 0, 1, 1, { 0, 0, 0 }, gEvent143Text00, 0, 250 },
    { 0, 0, 1, 1, { 0, 0, 0 }, gEvent143Text01, 0, 300 },
    { 36, 1, 3, 1, { 0, 0, 0 }, gEvent143Text02, 0, 330 },
    { 36, 1, 3, 1, { 0, 0, 0 }, gEvent143Text03, 0, 350 },
    { 36, 2, 3, 1, { 0, 0, 0 }, gEvent143Text04, 0, 500 },
    { 0, 4, 1, 1, { 0, 0, 0 }, gEvent143Text05, 0, 670 },
    { 36, 0, 3, 1, { 0, 0, 0 }, gEvent143Text06, 0, 700 },
    { 0, 4, 1, 1, { 0, 0, 0 }, gEvent143Text07, 0, 730 },
    { 36, 1, 3, 1, { 0, 0, 0 }, gEvent143Text08, 0, 760 },
    { 0, 3, 1, 1, { 0, 0, 0 }, gEvent143Text09, 0, 900 },
    { 36, 2, 3, 1, { 0, 0, 0 }, gEvent143Text10, 0, 950 },
    { 0, 4, 1, 1, { 0, 0, 0 }, gEvent143Text11, 0, 980 },
    { 0, 5, 1, 1, { 0, 0, 0 }, gEvent143Text12, 0, 1100 },
    { 36, 0, 3, 1, { 0, 0, 0 }, gEvent143Text13, 0, 1190 },
    { 36, 1, 4, 1, { 0, 0, 0 }, gEvent143Text14, 0, 1192 },
    { 0, 4, 1, 1, { 0, 0, 0 }, gEvent143Text15, MSG_SCRIPT_FLAG_END, 1240 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent143Script[16] = {
    { 0, 0, 1, 3, { 0, 0, 0 }, gEvent143Text00, 0, 250 },
    { 0, 0, 1, 3, { 0, 0, 0 }, gEvent143Text01, 0, 300 },
    { 36, 1, 3, 3, { 0, 0, 0 }, gEvent143Text02, 0, 330 },
    { 36, 1, 3, 3, { 0, 0, 0 }, gEvent143Text03, 0, 350 },
    { 36, 2, 3, 3, { 0, 0, 0 }, gEvent143Text04, 0, 500 },
    { 0, 4, 1, 3, { 0, 0, 0 }, gEvent143Text05, 0, 670 },
    { 36, 0, 3, 3, { 0, 0, 0 }, gEvent143Text06, 0, 700 },
    { 0, 4, 1, 3, { 0, 0, 0 }, gEvent143Text07, 0, 730 },
    { 36, 1, 3, 3, { 0, 0, 0 }, gEvent143Text08, 0, 760 },
    { 0, 3, 1, 3, { 0, 0, 0 }, gEvent143Text09, 0, 900 },
    { 36, 2, 3, 3, { 0, 0, 0 }, gEvent143Text10, 0, 950 },
    { 0, 4, 1, 3, { 0, 0, 0 }, gEvent143Text11, 0, 980 },
    { 0, 5, 1, 3, { 0, 0, 0 }, gEvent143Text12, 0, 1100 },
    { 36, 0, 3, 3, { 0, 0, 0 }, gEvent143Text13, 0, 1190 },
    { 36, 1, 4, 3, { 0, 0, 0 }, gEvent143Text14, 0, 1192 },
    { 0, 4, 1, 3, { 0, 0, 0 }, gEvent143Text15, MSG_SCRIPT_FLAG_END, 1240 },
};

#include "event_143_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent143Script[16] = {
    { 0, 0, 1, 1, { 0, 0, 0 }, &gEvent143Text00, 0, 250 },
    { 0, 0, 1, 1, { 0, 0, 0 }, &gEvent143Text01, 0, 300 },
    { 36, 1, 3, 1, { 0, 0, 0 }, &gEvent143Text02, 0, 330 },
    { 36, 1, 3, 1, { 0, 0, 0 }, &gEvent143Text03, 0, 350 },
    { 36, 2, 3, 1, { 0, 0, 0 }, &gEvent143Text04, 0, 500 },
    { 0, 4, 1, 1, { 0, 0, 0 }, &gEvent143Text05, 0, 670 },
    { 36, 0, 3, 1, { 0, 0, 0 }, &gEvent143Text06, 0, 700 },
    { 0, 4, 1, 1, { 0, 0, 0 }, &gEvent143Text07, 0, 730 },
    { 36, 1, 3, 1, { 0, 0, 0 }, &gEvent143Text08, 0, 760 },
    { 0, 3, 1, 1, { 0, 0, 0 }, &gEvent143Text09, 0, 900 },
    { 36, 2, 3, 1, { 0, 0, 0 }, &gEvent143Text10, 0, 950 },
    { 0, 4, 1, 1, { 0, 0, 0 }, &gEvent143Text11, 0, 980 },
    { 0, 5, 1, 1, { 0, 0, 0 }, &gEvent143Text12, 0, 1100 },
    { 36, 0, 3, 1, { 0, 0, 0 }, &gEvent143Text13, 0, 1190 },
    { 36, 1, 4, 1, { 0, 0, 0 }, &gEvent143Text14, 0, 1192 },
    { 0, 4, 1, 1, { 0, 0, 0 }, &gEvent143Text15, MSG_SCRIPT_FLAG_END, 1240 },
};
#endif

static const EvSoundCue sEvent143SoundCues[6] = {
    { SONG_BGM_WINNIETHEPOOH, 1, 0, 0 },
    { SONG_BG_POO, 2, 0, 0 },
    { SONG_BGM_WINNIETHEPOOH, 725, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT4, 755, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BG_POO, 1294, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT4, 1295, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent143Camera[1] = {
    { -64537, 790528, 416512, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent143Track0[17] = {
    { 2, 1, { 0, 0 }, 772096, 412160, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 7, 100, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 2, 110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 1, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 265, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 640, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 4, 990, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1040, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 4, 1050, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 16, 1220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent143Track1[8] = {
    { 756, 1, { 0, 0 }, 757248, 404224, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 781, 230, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 4, NULL, NULL },
    { 756, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 795, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 804, 770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 797, 1130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 781, 1160, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 4, NULL, NULL },
    { 756, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent143Tracks[2] = {
    { sEvent143Track0, 0, { 0, 0, 0 } },
    { sEvent143Track1, 70, { 0, 0, 0 } },
};

const EventSequenceDef gEvent143 = {
    2,
    { 0, 0, 0 },
    sEvent143Tracks,
    sEvent143Camera,
    sEvent143Script,
    sEvent143SoundCues,
    NULL,
    1300,
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
    7,
};

#ifdef VERSION_US
static const MessageScriptEntry sEvent144Script[8] = {
    { 0, 0, 1, 1, { 0, 0, 0 }, gEvent143Text00, 0, 250 },
    { 0, 0, 1, 1, { 0, 0, 0 }, gEvent143Text01, 0, 300 },
    { 36, 1, 3, 1, { 0, 0, 0 }, gEvent143Text02, 0, 330 },
    { 36, 1, 3, 1, { 0, 0, 0 }, gEvent143Text03, 0, 350 },
    { 36, 2, 3, 1, { 0, 0, 0 }, gEvent143Text04, 0, 500 },
    { 0, 4, 1, 1, { 0, 0, 0 }, gEvent143Text05, 0, 670 },
    { 36, 0, 3, 1, { 0, 0, 0 }, gEvent143Text06, 0, 700 },
    { 0, 4, 1, 1, { 0, 0, 0 }, gEvent143Text07, MSG_SCRIPT_FLAG_END, 730 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent144Script[8] = {
    { 0, 0, 1, 3, { 0, 0, 0 }, gEvent143Text00, 0, 250 },
    { 0, 0, 1, 3, { 0, 0, 0 }, gEvent143Text01, 0, 300 },
    { 36, 1, 3, 3, { 0, 0, 0 }, gEvent143Text02, 0, 330 },
    { 36, 1, 3, 3, { 0, 0, 0 }, gEvent143Text03, 0, 350 },
    { 36, 2, 3, 3, { 0, 0, 0 }, gEvent143Text04, 0, 500 },
    { 0, 4, 1, 3, { 0, 0, 0 }, gEvent143Text05, 0, 670 },
    { 36, 0, 3, 3, { 0, 0, 0 }, gEvent143Text06, 0, 700 },
    { 0, 4, 1, 3, { 0, 0, 0 }, gEvent143Text07, MSG_SCRIPT_FLAG_END, 730 },
};
#endif

#ifdef VERSION_EU
static const MessageScriptEntry sEvent144Script[8] = {
    { 0, 0, 1, 1, { 0, 0, 0 }, &gEvent143Text00, 0, 250 },
    { 0, 0, 1, 1, { 0, 0, 0 }, &gEvent143Text01, 0, 300 },
    { 36, 1, 3, 1, { 0, 0, 0 }, &gEvent143Text02, 0, 330 },
    { 36, 1, 3, 1, { 0, 0, 0 }, &gEvent143Text03, 0, 350 },
    { 36, 2, 3, 1, { 0, 0, 0 }, &gEvent143Text04, 0, 500 },
    { 0, 4, 1, 1, { 0, 0, 0 }, &gEvent143Text05, 0, 670 },
    { 36, 0, 3, 1, { 0, 0, 0 }, &gEvent143Text06, 0, 700 },
    { 0, 4, 1, 1, { 0, 0, 0 }, &gEvent143Text07, MSG_SCRIPT_FLAG_END, 730 },
};
#endif

static const EvSoundCue sEvent144SoundCues[4] = {
    { SONG_BGM_WINNIETHEPOOH, 0, 0, 0 },
    { SONG_BG_POO, 2, 0, 0 },
    { SONG_BG_POO, 784, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_WINNIETHEPOOH, 785, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent144Camera[1] = {
    { -64537, 790528, 416512, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent144Track0[13] = {
    { 2, 1, { 0, 0 }, 772096, 412160, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 7, 100, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 2, 110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 1, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 265, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 640, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 4, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent144Track1[6] = {
    { 756, 1, { 0, 0 }, 757248, 404224, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 781, 230, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 4, NULL, NULL },
    { 756, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 795, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 804, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 804, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33093, NULL, NULL },
};

static const EventCharaTrack sEvent144Tracks[2] = {
    { sEvent144Track0, 0, { 0, 0, 0 } },
    { sEvent144Track1, 70, { 0, 0, 0 } },
};

const EventSequenceDef gEvent144 = {
    2,
    { 0, 0, 0 },
    sEvent144Tracks,
    sEvent144Camera,
    sEvent144Script,
    sEvent144SoundCues,
    NULL,
    790,
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
    7,
};

#ifdef VERSION_US
static const MessageScriptEntry sEvent145Script[10] = {
    { 36, 2, 3, 1, { 0, 0, 0 }, gEvent145Text00, 0, 400 },
    { 0, 4, 1, 1, { 0, 0, 0 }, gEvent145Text01, 0, 430 },
    { 36, 1, 3, 1, { 0, 0, 0 }, gEvent143Text08, 0, 460 },
    { 0, 3, 1, 1, { 0, 0, 0 }, gEvent143Text09, 0, 600 },
    { 36, 2, 3, 1, { 0, 0, 0 }, gEvent143Text10, 0, 650 },
    { 0, 4, 1, 1, { 0, 0, 0 }, gEvent143Text11, 0, 680 },
    { 0, 5, 1, 1, { 0, 0, 0 }, gEvent143Text12, 0, 800 },
    { 36, 0, 3, 1, { 0, 0, 0 }, gEvent143Text13, 0, 890 },
    { 36, 1, 4, 1, { 0, 0, 0 }, gEvent143Text14, 0, 892 },
    { 0, 4, 1, 1, { 0, 0, 0 }, gEvent143Text15, MSG_SCRIPT_FLAG_END, 940 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent145Script[10] = {
    { 36, 2, 3, 3, { 0, 0, 0 }, gEvent145Text00, 0, 400 },
    { 0, 4, 1, 3, { 0, 0, 0 }, gEvent145Text01, 0, 430 },
    { 36, 1, 3, 3, { 0, 0, 0 }, gEvent143Text08, 0, 460 },
    { 0, 3, 1, 3, { 0, 0, 0 }, gEvent143Text09, 0, 600 },
    { 36, 2, 3, 3, { 0, 0, 0 }, gEvent143Text10, 0, 650 },
    { 0, 4, 1, 3, { 0, 0, 0 }, gEvent143Text11, 0, 680 },
    { 0, 5, 1, 3, { 0, 0, 0 }, gEvent143Text12, 0, 800 },
    { 36, 0, 3, 3, { 0, 0, 0 }, gEvent143Text13, 0, 890 },
    { 36, 1, 4, 3, { 0, 0, 0 }, gEvent143Text14, 0, 892 },
    { 0, 4, 1, 3, { 0, 0, 0 }, gEvent143Text15, MSG_SCRIPT_FLAG_END, 940 },
};

#include "event_145_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent145Script[10] = {
    { 36, 2, 3, 1, { 0, 0, 0 }, &gEvent145Text00, 0, 400 },
    { 0, 4, 1, 1, { 0, 0, 0 }, &gEvent145Text01, 0, 430 },
    { 36, 1, 3, 1, { 0, 0, 0 }, &gEvent143Text08, 0, 460 },
    { 0, 3, 1, 1, { 0, 0, 0 }, &gEvent143Text09, 0, 600 },
    { 36, 2, 3, 1, { 0, 0, 0 }, &gEvent143Text10, 0, 650 },
    { 0, 4, 1, 1, { 0, 0, 0 }, &gEvent143Text11, 0, 680 },
    { 0, 5, 1, 1, { 0, 0, 0 }, &gEvent143Text12, 0, 800 },
    { 36, 0, 3, 1, { 0, 0, 0 }, &gEvent143Text13, 0, 890 },
    { 36, 1, 4, 1, { 0, 0, 0 }, &gEvent143Text14, 0, 892 },
    { 0, 4, 1, 1, { 0, 0, 0 }, &gEvent143Text15, MSG_SCRIPT_FLAG_END, 940 },
};
#endif

static const EvSoundCue sEvent145SoundCues[6] = {
    { SONG_BGM_WINNIETHEPOOH, 1, 0, 0 },
    { SONG_BG_POO, 2, 0, 0 },
    { SONG_BGM_WINNIETHEPOOH, 425, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT4, 455, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BG_POO, 994, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT4, 995, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent145Camera[1] = {
    { -64537, 790528, 416512, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent145Track0[11] = {
    { 2, 1, { 0, 0 }, 772096, 412160, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 7, 100, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 2, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 1, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 740, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 4, 750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 16, 920, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent145Track1[7] = {
    { 756, 1, { 0, 0 }, 757248, 404224, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 781, 230, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 4, NULL, NULL },
    { 756, 240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 795, 470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 797, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 781, 860, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 4, NULL, NULL },
    { 756, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent145Tracks[2] = {
    { sEvent145Track0, 0, { 0, 0, 0 } },
    { sEvent145Track1, 70, { 0, 0, 0 } },
};

const EventSequenceDef gEvent145 = {
    2,
    { 0, 0, 0 },
    sEvent145Tracks,
    sEvent145Camera,
    sEvent145Script,
    sEvent145SoundCues,
    NULL,
    1000,
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
    7,
};

#ifdef VERSION_US
#include "event_145_text.inc"
static const MessageScriptEntry sEvent146Script[2] = {
    { 36, 2, 3, 1, { 0, 0, 0 }, gEvent145Text00, 0, 400 },
    { 0, 4, 1, 1, { 0, 0, 0 }, gEvent145Text01, MSG_SCRIPT_FLAG_END, 430 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent146Script[2] = {
    { 36, 2, 3, 3, { 0, 0, 0 }, gEvent145Text00, 0, 400 },
    { 0, 4, 1, 3, { 0, 0, 0 }, gEvent145Text01, MSG_SCRIPT_FLAG_END, 430 },
};
#endif

#ifdef VERSION_EU
static const MessageScriptEntry sEvent146Script[2] = {
    { 36, 2, 3, 1, { 0, 0, 0 }, &gEvent145Text00, 0, 400 },
    { 0, 4, 1, 1, { 0, 0, 0 }, &gEvent145Text01, MSG_SCRIPT_FLAG_END, 430 },
};
#endif

static const EvSoundCue sEvent146SoundCues[4] = {
    { SONG_BGM_WINNIETHEPOOH, 1, 0, 0 },
    { SONG_BG_POO, 2, 0, 0 },
    { SONG_BG_POO, 484, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_WINNIETHEPOOH, 485, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent146Camera[1] = {
    { -64537, 790528, 416512, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent146Track0[8] = {
    { 2, 1, { 0, 0 }, 772096, 412160, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 7, 100, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 2, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 1, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent146Track1[5] = {
    { 756, 1, { 0, 0 }, 757248, 404224, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 781, 230, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 4, NULL, NULL },
    { 756, 240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 795, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 796, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33093, NULL, NULL },
};

static const EventCharaTrack sEvent146Tracks[2] = {
    { sEvent146Track0, 0, { 0, 0, 0 } },
    { sEvent146Track1, 70, { 0, 0, 0 } },
};

const EventSequenceDef gEvent146 = {
    2,
    { 0, 0, 0 },
    sEvent146Tracks,
    sEvent146Camera,
    sEvent146Script,
    sEvent146SoundCues,
    NULL,
    490,
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
    7,
};

#ifdef VERSION_US
#include "event_147_text.inc"
static const MessageScriptEntry sEvent147Script[6] = {
    { 36, 2, 3, 1, { 0, 0, 0 }, gEvent145Text00, 0, 400 },
    { 0, 4, 1, 1, { 0, 0, 0 }, gEvent145Text01, 0, 430 },
    { 36, 0, 3, 1, { 0, 0, 0 }, gEvent147Text02, 0, 560 },
    { 0, 4, 1, 1, { 0, 0, 0 }, gEvent147Text03, 0, 590 },
    { 36, 0, 3, 1, { 0, 0, 0 }, gEvent147Text04, 0, 620 },
    { 36, 1, 4, 1, { 0, 0, 0 }, gEvent147Text05, MSG_SCRIPT_FLAG_END, 622 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent147Script[6] = {
    { 36, 2, 3, 3, { 0, 0, 0 }, gEvent145Text00, 0, 400 },
    { 0, 4, 1, 3, { 0, 0, 0 }, gEvent145Text01, 0, 430 },
    { 36, 0, 3, 3, { 0, 0, 0 }, gEvent147Text02, 0, 560 },
    { 0, 4, 1, 3, { 0, 0, 0 }, gEvent147Text03, 0, 590 },
    { 36, 0, 3, 3, { 0, 0, 0 }, gEvent117Text22, 0, 620 },
    { 36, 1, 4, 3, { 0, 0, 0 }, gEvent147Text05, MSG_SCRIPT_FLAG_END, 622 },
};

#include "event_147_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent147Script[6] = {
    { 36, 2, 3, 1, { 0, 0, 0 }, &gEvent145Text00, 0, 400 },
    { 0, 4, 1, 1, { 0, 0, 0 }, &gEvent145Text01, 0, 430 },
    { 36, 0, 3, 1, { 0, 0, 0 }, &gEvent147Text02, 0, 560 },
    { 0, 4, 1, 1, { 0, 0, 0 }, &gEvent147Text03, 0, 590 },
    { 36, 0, 3, 1, { 0, 0, 0 }, &gEvent147Text04, 0, 620 },
    { 36, 1, 4, 1, { 0, 0, 0 }, &gEvent147Text05, MSG_SCRIPT_FLAG_END, 622 },
};
#endif

static const EvSoundCue sEvent147SoundCues[6] = {
    { SONG_BGM_WINNIETHEPOOH, 0, 0, 0 },
    { SONG_BG_POO, 2, 0, 0 },
    { SONG_BGM_WINNIETHEPOOH, 425, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT4, 555, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BG_POO, 674, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT4, 675, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent147Camera[1] = {
    { -64537, 790528, 416512, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent147Track0[8] = {
    { 2, 1, { 0, 0 }, 772096, 412160, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 7, 100, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 2, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 1, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent147Track1[6] = {
    { 756, 1, { 0, 0 }, 757248, 404224, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 781, 230, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 4, NULL, NULL },
    { 756, 240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 795, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 797, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 756, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent147Tracks[2] = {
    { sEvent147Track0, 0, { 0, 0, 0 } },
    { sEvent147Track1, 70, { 0, 0, 0 } },
};

const EventSequenceDef gEvent147 = {
    2,
    { 0, 0, 0 },
    sEvent147Tracks,
    sEvent147Camera,
    sEvent147Script,
    sEvent147SoundCues,
    NULL,
    680,
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
    7,
};

#ifdef VERSION_US
#include "event_148_text.inc"
static const MessageScriptEntry sEvent148Script[1] = {
    { 0, 7, 1, 1, { 0, 0, 0 }, gEvent148Text00, MSG_SCRIPT_FLAG_END, 150 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent148Script[1] = {
    { 0, 7, 1, 3, { 0, 0, 0 }, gEvent148Text00, MSG_SCRIPT_FLAG_END, 150 },
};

#include "event_148_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent148Script[1] = {
    { 0, 7, 1, 1, { 0, 0, 0 }, &gEvent148Text00, MSG_SCRIPT_FLAG_END, 150 },
};
#endif

static const EvSoundCue sEvent148SoundCues[1] = {
    { 65535, 0, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent148Camera[1] = {
    { -64537, 790528, 416512, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent148Track0[6] = {
    { 2, 80, { 0, 0 }, 790528, 419840, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 1, 90, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 100, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent148Tracks[1] = {
    { sEvent148Track0, 0, { 0, 0, 0 } },
};

const EventSequenceDef gEvent148 = {
    1,
    { 0, 0, 0 },
    sEvent148Tracks,
    sEvent148Camera,
    sEvent148Script,
    sEvent148SoundCues,
    NULL,
    210,
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
    7,
};

#ifdef VERSION_US
#include "event_149_text.inc"
static const MessageScriptEntry sEvent149Script[19] = {
    { 26, 5, 1, 1, { 0, 0, 0 }, gEvent149Text00, 0, 250 },
    { 26, 5, 1, 1, { 0, 0, 0 }, gEvent149Text01, 0, 400 },
    { 52, 0, 2, 1, { 0, 0, 0 }, gEvent149Text02, MSG_SCRIPT_FLAG_SILHOUETTE, 440 },
    { 26, 2, 1, 1, { 0, 0, 0 }, gEvent149Text03, 0, 590 },
    { 52, 0, 2, 1, { 0, 0, 0 }, gEvent149Text04, MSG_SCRIPT_FLAG_SILHOUETTE, 690 },
    { 26, 3, 1, 1, { 0, 0, 0 }, gEvent149Text05, 0, 720 },
    { 26, 3, 1, 1, { 0, 0, 0 }, gEvent149Text06, 0, 880 },
    { 26, 2, 1, 1, { 0, 0, 0 }, gEvent149Text07, 0, 1050 },
    { 52, 0, 2, 1, { 0, 0, 0 }, gEvent149Text08, MSG_SCRIPT_FLAG_SILHOUETTE, 1090 },
    { 52, 0, 4, 1, { 0, 0, 0 }, gEvent149Text09, MSG_SCRIPT_FLAG_SILHOUETTE, 1092 },
    { 26, 2, 1, 1, { 0, 0, 0 }, gEvent149Text10, 0, 1120 },
    { 52, 0, 2, 1, { 0, 0, 0 }, gEvent149Text11, MSG_SCRIPT_FLAG_SILHOUETTE, 1160 },
    { 52, 0, 2, 1, { 0, 0, 0 }, gEvent149Text12, MSG_SCRIPT_FLAG_SILHOUETTE, 1370 },
    { 26, 3, 3, 1, { 0, 0, 0 }, gEvent149Text13, 0, 1590 },
    { 52, 0, 0, 1, { 0, 0, 0 }, gEvent149Text14, MSG_SCRIPT_FLAG_SILHOUETTE, 1630 },
    { 52, 0, 4, 1, { 0, 0, 0 }, gEvent149Text15, MSG_SCRIPT_FLAG_SILHOUETTE, 1632 },
    { 52, 0, 1, 1, { 0, 0, 0 }, gEvent149Text16, MSG_SCRIPT_FLAG_SILHOUETTE, 1730 },
    { 26, 1, 3, 1, { 0, 0, 0 }, gEvent149Text17, 0, 2020 },
    { 52, 0, 1, 1, { 0, 0, 0 }, gEvent149Text18, MSG_SCRIPT_FLAG_SILHOUETTE | MSG_SCRIPT_FLAG_END, 2060 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent149Script[19] = {
    { 26, 5, 1, 3, { 0, 0, 0 }, gEvent149Text00, 0, 250 },
    { 26, 5, 1, 3, { 0, 0, 0 }, gEvent149Text01, 0, 400 },
    { 52, 0, 2, 3, { 0, 0, 0 }, gEvent149Text02, MSG_SCRIPT_FLAG_SILHOUETTE, 440 },
    { 26, 2, 1, 3, { 0, 0, 0 }, gEvent000Text21, 0, 590 },
    { 52, 0, 2, 3, { 0, 0, 0 }, gEvent149Text04, MSG_SCRIPT_FLAG_SILHOUETTE, 690 },
    { 26, 3, 1, 3, { 0, 0, 0 }, gEvent149Text05, 0, 720 },
    { 26, 3, 1, 3, { 0, 0, 0 }, gEvent149Text06, 0, 880 },
    { 26, 2, 1, 3, { 0, 0, 0 }, gEvent149Text07, 0, 1050 },
    { 52, 0, 2, 3, { 0, 0, 0 }, gEvent149Text08, MSG_SCRIPT_FLAG_SILHOUETTE, 1090 },
    { 52, 0, 4, 3, { 0, 0, 0 }, gEvent149Text09, MSG_SCRIPT_FLAG_SILHOUETTE, 1092 },
    { 26, 2, 1, 3, { 0, 0, 0 }, gEvent149Text10, 0, 1120 },
    { 52, 0, 2, 3, { 0, 0, 0 }, gEvent149Text11, MSG_SCRIPT_FLAG_SILHOUETTE, 1160 },
    { 52, 0, 2, 3, { 0, 0, 0 }, gEvent149Text12, MSG_SCRIPT_FLAG_SILHOUETTE, 1370 },
    { 26, 3, 3, 3, { 0, 0, 0 }, gEvent149Text13, 0, 1590 },
    { 52, 0, 0, 3, { 0, 0, 0 }, gEvent149Text14, MSG_SCRIPT_FLAG_SILHOUETTE, 1630 },
    { 52, 0, 4, 3, { 0, 0, 0 }, gEvent149Text15, MSG_SCRIPT_FLAG_SILHOUETTE, 1632 },
    { 52, 0, 1, 3, { 0, 0, 0 }, gEvent149Text16, MSG_SCRIPT_FLAG_SILHOUETTE, 1730 },
    { 26, 1, 3, 3, { 0, 0, 0 }, gEvent149Text17, 0, 2020 },
    { 52, 0, 1, 3, { 0, 0, 0 }, gEvent149Text18, MSG_SCRIPT_FLAG_SILHOUETTE | MSG_SCRIPT_FLAG_END, 2060 },
};

#include "event_149_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent149Script[19] = {
    { 26, 5, 1, 1, { 0, 0, 0 }, &gEvent149Text00, 0, 250 },
    { 26, 5, 1, 1, { 0, 0, 0 }, &gEvent149Text01, 0, 400 },
    { 52, 0, 2, 1, { 0, 0, 0 }, &gEvent149Text02, MSG_SCRIPT_FLAG_SILHOUETTE, 440 },
    { 26, 2, 1, 1, { 0, 0, 0 }, &gEvent149Text03, 0, 590 },
    { 52, 0, 2, 1, { 0, 0, 0 }, &gEvent149Text04, MSG_SCRIPT_FLAG_SILHOUETTE, 690 },
    { 26, 3, 1, 1, { 0, 0, 0 }, &gEvent149Text05, 0, 720 },
    { 26, 3, 1, 1, { 0, 0, 0 }, &gEvent149Text06, 0, 880 },
    { 26, 2, 1, 1, { 0, 0, 0 }, &gEvent149Text07, 0, 1050 },
    { 52, 0, 2, 1, { 0, 0, 0 }, &gEvent149Text08, MSG_SCRIPT_FLAG_SILHOUETTE, 1090 },
    { 52, 0, 4, 1, { 0, 0, 0 }, &gEvent149Text09, MSG_SCRIPT_FLAG_SILHOUETTE, 1092 },
    { 26, 2, 1, 1, { 0, 0, 0 }, &gEvent149Text10, 0, 1120 },
    { 52, 0, 2, 1, { 0, 0, 0 }, &gEvent149Text11, MSG_SCRIPT_FLAG_SILHOUETTE, 1160 },
    { 52, 0, 2, 1, { 0, 0, 0 }, &gEvent149Text12, MSG_SCRIPT_FLAG_SILHOUETTE, 1370 },
    { 26, 3, 3, 1, { 0, 0, 0 }, &gEvent149Text13, 0, 1590 },
    { 52, 0, 0, 1, { 0, 0, 0 }, &gEvent149Text14, MSG_SCRIPT_FLAG_SILHOUETTE, 1630 },
    { 52, 0, 4, 1, { 0, 0, 0 }, &gEvent149Text15, MSG_SCRIPT_FLAG_SILHOUETTE, 1632 },
    { 52, 0, 1, 1, { 0, 0, 0 }, &gEvent149Text16, MSG_SCRIPT_FLAG_SILHOUETTE, 1730 },
    { 26, 1, 3, 1, { 0, 0, 0 }, &gEvent149Text17, 0, 2020 },
    { 52, 0, 1, 1, { 0, 0, 0 }, &gEvent149Text18, MSG_SCRIPT_FLAG_SILHOUETTE | MSG_SCRIPT_FLAG_END, 2060 },
};
#endif

static const EvSoundCue sEvent149SoundCues[5] = {
    { 65535, 0, 0, 0 },
    { SONG_EV_FLASH01, 2100, 0, 0 },
    { SONG_EV_FLASH01, 2120, 0, 0 },
    { SONG_EV_FLASH01, 2130, 0, 0 },
    { SONG_EV_FLASH02, 2220, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent149Camera[13] = {
    { -65456, 32256, 98816, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65436, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_BLACK | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -65356, 32256, 41216, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 1, { 0, 0 }, NULL },
    { -65306, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_BLACK | CAMERA_MODE_KEEP, 60, { 0, 0 }, NULL },
    { -65236, 32256, 41216, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 1, { 0, 0 }, NULL },
    { -64986, 32256, 36096, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -64371, 32256, 32512, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 30, { 0, 0 }, NULL },
    { -63436, 32256, 29952, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -63416, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -63406, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -63386, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -63316, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -63136, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_KEYFRAME_FLAG_END | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 50, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent149Track0[26] = {
    { 547, 300, { 0, 0 }, 29696, 39424, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 545, 460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 545, 530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 546, 552, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 820, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 870, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 514, 875, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 526, 882, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 1030, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 514, 1115, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 524, 1165, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 1285, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 1335, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 514, 1450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 1510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 1520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 1550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 1750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 530, 1880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 515, 1930, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 518, 1950, { 0, 0 }, 35584, 37376, 0, 515, { 0, 0 }, 67, NULL, NULL },
    { 515, 1990, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 558, 2150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 558, 2200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 558, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent149Track1[8] = {
    { 921, 1164, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8258, NULL, NULL },
    { 921, 1165, { 0, 0 }, 25088, 8448, 0, 0, { 0, 0 }, 16450, NULL, NULL },
    { 921, 1265, { 0, 0 }, 25088, 24832, 0, 921, { 0, 0 }, 339, NULL, NULL },
    { 921, 1400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 469, NULL, NULL },
    { 921, 1650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 336, EventCharaCircleSlow, NULL },
    { 921, 1700, { 0, 0 }, 39680, 22528, 0, 921, { 0, 0 }, 339, NULL, NULL },
    { 921, 2230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 469, NULL, NULL },
    { 921, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98370, NULL, NULL },
};

static const EventCharaKeyframe sEvent149Track2[5] = {
    { 591, 1960, { 0, 0 }, 256000, 0, 0, 0, { 0, 0 }, 322, NULL, NULL },
    { 591, 1961, { 0, 0 }, 39680, 22272, 0, 0, { 0, 0 }, 322, NULL, NULL },
    { 592, 2004, { 0, 0 }, 39680, 28672, 0, 591, { 0, 0 }, 323, NULL, NULL },
    { 603, 2900, { 0, 0 }, 35584, 37376, 0, 0, { 0, 0 }, 338, NULL, NULL },
    { 591, 3000, { 0, 0 }, 256000, 0, 0, 0, { 0, 0 }, 33090, NULL, NULL },
};

static const EventCharaKeyframe sEvent149Track3[3] = {
    { 928, 460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 927, 510, { 0, 0 }, 27904, 29952, 0, 0, { 0, 0 }, 16658, NULL, NULL },
    { 928, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaTrack sEvent149Tracks[4] = {
    { sEvent149Track0, 44, { 0, 0, 0 } },
    { sEvent149Track1, 88, { 0, 0, 0 } },
    { sEvent149Track2, 50, { 0, 0, 0 } },
    { sEvent149Track3, 93, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent149 = {
    4,
    { 0, 0, 0 },
    sEvent149Tracks,
    sEvent149Camera,
    sEvent149Script,
    sEvent149SoundCues,
    NULL,
    2390,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    150,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent149 = {
    4,
    { 0, 0, 0 },
    sEvent149Tracks,
    sEvent149Camera,
    sEvent149Script,
    sEvent149SoundCues,
    NULL,
    2390,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    148,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_150_text.inc"
static const MessageScriptEntry sEvent150Script[1] = {
    { 26, 0, 2, 1, { 0, 0, 0 }, gEvent150Text00, MSG_SCRIPT_FLAG_END, 350 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent150Script[1] = {
    { 26, 0, 2, 3, { 0, 0, 0 }, gEvent150Text00, MSG_SCRIPT_FLAG_END, 350 },
};

#include "event_150_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent150Script[1] = {
    { 26, 0, 2, 1, { 0, 0, 0 }, &gEvent150Text00, MSG_SCRIPT_FLAG_END, 350 },
};
#endif

static const EvSoundCue sEvent150SoundCues[2] = {
    { 65535, 0, 0, 0 },
    { SONG_BGM_TOWN_FIELD, 5000, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent150Camera[4] = {
    { -65536, 196352, 58112, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, NULL },
    { -65416, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 110, { 0, 0 }, NULL },
    { -65306, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64537, 205056, 51200, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent150Track0[8] = {
    { 515, 100, { 0, 0 }, 196864, 64768, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 515, 110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 514, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent150Tracks[1] = {
    { sEvent150Track0, 44, { 0, 0, 0 } },
};

const EventSequenceDef gEvent150 = {
    1,
    { 0, 0, 0 },
    sEvent150Tracks,
    sEvent150Camera,
    sEvent150Script,
    sEvent150SoundCues,
    NULL,
    400,
    1,
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

#ifdef VERSION_US
#include "event_151_text.inc"
static const MessageScriptEntry sEvent151Script[14] = {
    { 26, 3, 3, 1, { 0, 0, 0 }, gEvent151Text00, 0, 215 },
    { 26, 0, 3, 1, { 0, 0, 0 }, gEvent151Text01, 0, 310 },
    { 52, 0, 0, 1, { 0, 0, 0 }, gEvent151Text02, MSG_SCRIPT_FLAG_SILHOUETTE, 355 },
    { 26, 3, 3, 1, { 0, 0, 0 }, gEvent151Text03, 0, 365 },
    { 52, 0, 0, 1, { 0, 0, 0 }, gEvent151Text04, MSG_SCRIPT_FLAG_SILHOUETTE, 400 },
    { 52, 0, 4, 1, { 0, 0, 0 }, gEvent151Text05, MSG_SCRIPT_FLAG_SILHOUETTE, 402 },
    { 26, 0, 3, 1, { 0, 0, 0 }, gEvent151Text06, 0, 450 },
    { 26, 0, 1, 1, { 0, 0, 0 }, gEvent151Text07, 0, 570 },
    { 52, 0, 2, 1, { 0, 0, 0 }, gEvent151Text08, MSG_SCRIPT_FLAG_SILHOUETTE, 610 },
    { 26, 0, 1, 1, { 0, 0, 0 }, gEvent151Text09, 0, 640 },
    { 26, 2, 1, 1, { 0, 0, 0 }, gEvent151Text10, 0, 735 },
    { 26, 2, 1, 1, { 0, 0, 0 }, gEvent151Text11, 0, 835 },
    { 26, 2, 4, 1, { 0, 0, 0 }, gEvent151Text12, 0, 837 },
    { 26, 2, 4, 1, { 0, 0, 0 }, gEvent151Text13, MSG_SCRIPT_FLAG_END, 839 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent151Script[14] = {
    { 26, 3, 3, 3, { 0, 0, 0 }, gEvent151Text00, 0, 215 },
    { 26, 0, 3, 3, { 0, 0, 0 }, gEvent151Text01, 0, 310 },
    { 52, 0, 0, 3, { 0, 0, 0 }, gEvent151Text02, MSG_SCRIPT_FLAG_SILHOUETTE, 355 },
    { 26, 3, 3, 3, { 0, 0, 0 }, gEvent151Text03, 0, 365 },
    { 52, 0, 0, 3, { 0, 0, 0 }, gEvent151Text04, MSG_SCRIPT_FLAG_SILHOUETTE, 400 },
    { 52, 0, 4, 3, { 0, 0, 0 }, gEvent151Text05, MSG_SCRIPT_FLAG_SILHOUETTE, 402 },
    { 26, 0, 3, 3, { 0, 0, 0 }, gEvent151Text06, 0, 450 },
    { 26, 0, 1, 3, { 0, 0, 0 }, gEvent151Text07, 0, 570 },
    { 52, 0, 2, 3, { 0, 0, 0 }, gEvent151Text08, MSG_SCRIPT_FLAG_SILHOUETTE, 610 },
    { 26, 0, 1, 3, { 0, 0, 0 }, gEvent151Text09, 0, 640 },
    { 26, 2, 1, 3, { 0, 0, 0 }, gEvent151Text10, 0, 735 },
    { 26, 2, 1, 3, { 0, 0, 0 }, gEvent151Text11, 0, 835 },
    { 26, 2, 4, 3, { 0, 0, 0 }, gEvent151Text12, 0, 837 },
    { 26, 2, 4, 3, { 0, 0, 0 }, gEvent151Text13, MSG_SCRIPT_FLAG_END, 839 },
};

#include "event_151_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent151Script[14] = {
    { 26, 3, 3, 1, { 0, 0, 0 }, &gEvent151Text00, 0, 215 },
    { 26, 0, 3, 1, { 0, 0, 0 }, &gEvent151Text01, 0, 310 },
    { 52, 0, 0, 1, { 0, 0, 0 }, &gEvent151Text02, MSG_SCRIPT_FLAG_SILHOUETTE, 355 },
    { 26, 3, 3, 1, { 0, 0, 0 }, &gEvent151Text03, 0, 365 },
    { 52, 0, 0, 1, { 0, 0, 0 }, &gEvent151Text04, MSG_SCRIPT_FLAG_SILHOUETTE, 400 },
    { 52, 0, 4, 1, { 0, 0, 0 }, &gEvent151Text05, MSG_SCRIPT_FLAG_SILHOUETTE, 402 },
    { 26, 0, 3, 1, { 0, 0, 0 }, &gEvent151Text06, 0, 450 },
    { 26, 0, 1, 1, { 0, 0, 0 }, &gEvent151Text07, 0, 570 },
    { 52, 0, 2, 1, { 0, 0, 0 }, &gEvent151Text08, MSG_SCRIPT_FLAG_SILHOUETTE, 610 },
    { 26, 0, 1, 1, { 0, 0, 0 }, &gEvent151Text09, 0, 640 },
    { 26, 2, 1, 1, { 0, 0, 0 }, &gEvent151Text10, 0, 735 },
    { 26, 2, 1, 1, { 0, 0, 0 }, &gEvent151Text11, 0, 835 },
    { 26, 2, 4, 1, { 0, 0, 0 }, &gEvent151Text12, 0, 837 },
    { 26, 2, 4, 1, { 0, 0, 0 }, &gEvent151Text13, MSG_SCRIPT_FLAG_END, 839 },
};
#endif

static const EvSoundCue sEvent151SoundCues[2] = {
    { SONG_BGM_HOLLOW_FIELD, 0, 0, 0 },
    { SONG_BGM_HOLLOW_FIELD, 955, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent151Camera[2] = {
    { -65536, 55552, 75264, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, NULL },
    { -64537, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 80, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent151Track0[23] = {
    { 514, 1, { 0, 0 }, 18944, 63744, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 516, 155, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 514, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 526, 210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 526, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 514, 305, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 524, 357, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 514, 342, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 526, 368, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 514, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 514, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 543, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 538, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 524, 840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 870, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 522, 1500, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 514, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent151Tracks[1] = {
    { sEvent151Track0, 44, { 0, 0, 0 } },
};

const EventSequenceDef gEvent151 = {
    1,
    { 0, 0, 0 },
    sEvent151Tracks,
    sEvent151Camera,
    sEvent151Script,
    sEvent151SoundCues,
    NULL,
    960,
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
#include "event_152_text.inc"
static const MessageScriptEntry sEvent152Script[7] = {
    { 26, 0, 1, 1, { 0, 0, 0 }, gEvent152Text00, 0, 405 },
    { 52, 0, 2, 1, { 0, 0, 0 }, gEvent152Text01, MSG_SCRIPT_FLAG_SILHOUETTE, 440 },
    { 26, 0, 1, 1, { 0, 0, 0 }, gEvent152Text02, 0, 470 },
    { 26, 0, 1, 1, { 0, 0, 0 }, gEvent152Text03, 0, 520 },
    { 52, 0, 2, 1, { 0, 0, 0 }, gEvent152Text04, MSG_SCRIPT_FLAG_SILHOUETTE, 550 },
    { 52, 0, 4, 1, { 0, 0, 0 }, gEvent152Text05, MSG_SCRIPT_FLAG_SILHOUETTE, 552 },
    { 26, 2, 1, 1, { 0, 0, 0 }, gEvent152Text06, MSG_SCRIPT_FLAG_END, 600 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent152Script[7] = {
    { 26, 0, 1, 3, { 0, 0, 0 }, gEvent152Text00, 0, 405 },
    { 52, 0, 2, 3, { 0, 0, 0 }, gEvent152Text01, MSG_SCRIPT_FLAG_SILHOUETTE, 440 },
    { 26, 0, 1, 3, { 0, 0, 0 }, gEvent152Text02, 0, 470 },
    { 26, 0, 1, 3, { 0, 0, 0 }, gEvent152Text03, 0, 520 },
    { 52, 0, 2, 3, { 0, 0, 0 }, gEvent152Text04, MSG_SCRIPT_FLAG_SILHOUETTE, 550 },
    { 52, 0, 4, 3, { 0, 0, 0 }, gEvent152Text05, MSG_SCRIPT_FLAG_SILHOUETTE, 552 },
    { 26, 2, 1, 3, { 0, 0, 0 }, gEvent152Text06, MSG_SCRIPT_FLAG_END, 600 },
};

#include "event_152_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent152Script[7] = {
    { 26, 0, 1, 1, { 0, 0, 0 }, &gEvent152Text00, 0, 405 },
    { 52, 0, 2, 1, { 0, 0, 0 }, &gEvent152Text01, MSG_SCRIPT_FLAG_SILHOUETTE, 440 },
    { 26, 0, 1, 1, { 0, 0, 0 }, &gEvent152Text02, 0, 470 },
    { 26, 0, 1, 1, { 0, 0, 0 }, &gEvent152Text03, 0, 520 },
    { 52, 0, 2, 1, { 0, 0, 0 }, &gEvent152Text04, MSG_SCRIPT_FLAG_SILHOUETTE, 550 },
    { 52, 0, 4, 1, { 0, 0, 0 }, &gEvent152Text05, MSG_SCRIPT_FLAG_SILHOUETTE, 552 },
    { 26, 2, 1, 1, { 0, 0, 0 }, &gEvent152Text06, MSG_SCRIPT_FLAG_END, 600 },
};
#endif

static const EvSoundCue sEvent152SoundCues[2] = {
    { SONG_BGM_EVENT_SILENCE, 0, 0, 0 },
    { SONG_BGM_EVENT_SILENCE, 675, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent152Camera[3] = {
    { -65535, 78848, 59136, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65064, 63488, 67840, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -60536, 55808, 71168, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 30, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent152Track0[15] = {
    { 514, 1, { 0, 0 }, 88576, 59136, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 516, 120, { 0, 0 }, 64000, 73984, 0, 514, { 0, 0 }, 3, NULL, NULL },
    { 514, 130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 514, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 524, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 472, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 516, 500, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 514, 620, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 520, 1000, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 36, NULL, NULL },
    { 514, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent152Tracks[1] = {
    { sEvent152Track0, 44, { 0, 0, 0 } },
};

const EventSequenceDef gEvent152 = {
    1,
    { 0, 0, 0 },
    sEvent152Tracks,
    sEvent152Camera,
    sEvent152Script,
    sEvent152SoundCues,
    NULL,
    680,
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
#include "event_153_text.inc"
static const MessageScriptEntry sEvent153Script[17] = {
    { 26, 0, 1, 1, { 0, 0, 0 }, gEvent153Text00, 0, 150 },
    { 26, 0, 1, 1, { 0, 0, 0 }, gEvent153Text01, 0, 260 },
    { 26, 2, 1, 1, { 0, 0, 0 }, gEvent153Text02, 0, 440 },
    { 26, 2, 4, 1, { 0, 0, 0 }, gEvent153Text03, 0, 442 },
    { 52, 0, 0, 1, { 0, 0, 0 }, gEvent153Text04, MSG_SCRIPT_FLAG_SILHOUETTE, 490 },
    { 26, 5, 3, 1, { 0, 0, 0 }, gEvent153Text05, 0, 720 },
    { 52, 0, 0, 1, { 0, 0, 0 }, gEvent153Text06, MSG_SCRIPT_FLAG_SILHOUETTE, 760 },
    { 52, 0, 0, 1, { 0, 0, 0 }, gEvent153Text07, MSG_SCRIPT_FLAG_SILHOUETTE, 850 },
    { 52, 0, 4, 1, { 0, 0, 0 }, gEvent153Text08, MSG_SCRIPT_FLAG_SILHOUETTE, 852 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent153Text09, 0, 880 },
    { 52, 0, 0, 1, { 0, 0, 0 }, gEvent153Text10, MSG_SCRIPT_FLAG_SILHOUETTE, 920 },
    { 52, 0, 0, 1, { 0, 0, 0 }, gEvent153Text11, MSG_SCRIPT_FLAG_SILHOUETTE, 1100 },
    { 52, 0, 4, 1, { 0, 0, 0 }, gEvent153Text12, MSG_SCRIPT_FLAG_SILHOUETTE, 1102 },
    { 52, 0, 4, 1, { 0, 0, 0 }, gEvent153Text13, MSG_SCRIPT_FLAG_SILHOUETTE, 1104 },
    { 52, 0, 4, 1, { 0, 0, 0 }, gEvent153Text14, MSG_SCRIPT_FLAG_SILHOUETTE, 1106 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent153Text15, 0, 1125 },
    { 52, 0, 0, 1, { 0, 0, 0 }, gEvent153Text16, MSG_SCRIPT_FLAG_SILHOUETTE | MSG_SCRIPT_FLAG_END, 1160 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent153Script[17] = {
    { 26, 0, 1, 3, { 0, 0, 0 }, gEvent153Text00, 0, 150 },
    { 26, 0, 1, 3, { 0, 0, 0 }, gEvent153Text01, 0, 260 },
    { 26, 2, 1, 3, { 0, 0, 0 }, gEvent153Text02, 0, 440 },
    { 26, 2, 4, 3, { 0, 0, 0 }, gEvent153Text03, 0, 442 },
    { 52, 0, 0, 3, { 0, 0, 0 }, gEvent153Text04, MSG_SCRIPT_FLAG_SILHOUETTE, 490 },
    { 26, 5, 3, 3, { 0, 0, 0 }, gEvent153Text05, 0, 720 },
    { 52, 0, 0, 3, { 0, 0, 0 }, gEvent153Text06, MSG_SCRIPT_FLAG_SILHOUETTE, 760 },
    { 52, 0, 0, 3, { 0, 0, 0 }, gEvent153Text07, MSG_SCRIPT_FLAG_SILHOUETTE, 850 },
    { 52, 0, 4, 3, { 0, 0, 0 }, gEvent153Text08, MSG_SCRIPT_FLAG_SILHOUETTE, 852 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent153Text09, 0, 880 },
    { 52, 0, 0, 3, { 0, 0, 0 }, gEvent153Text10, MSG_SCRIPT_FLAG_SILHOUETTE, 920 },
    { 52, 0, 0, 3, { 0, 0, 0 }, gEvent153Text11, MSG_SCRIPT_FLAG_SILHOUETTE, 1100 },
    { 52, 0, 4, 3, { 0, 0, 0 }, gEvent153Text12, MSG_SCRIPT_FLAG_SILHOUETTE, 1102 },
    { 52, 0, 4, 3, { 0, 0, 0 }, gEvent153Text13, MSG_SCRIPT_FLAG_SILHOUETTE, 1104 },
    { 52, 0, 4, 3, { 0, 0, 0 }, gEvent153Text14, MSG_SCRIPT_FLAG_SILHOUETTE, 1106 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent153Text15, 0, 1125 },
    { 52, 0, 0, 3, { 0, 0, 0 }, gEvent153Text16, MSG_SCRIPT_FLAG_SILHOUETTE | MSG_SCRIPT_FLAG_END, 1160 },
};

#include "event_153_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent153Script[17] = {
    { 26, 0, 1, 1, { 0, 0, 0 }, &gEvent153Text00, 0, 150 },
    { 26, 0, 1, 1, { 0, 0, 0 }, &gEvent153Text01, 0, 260 },
    { 26, 2, 1, 1, { 0, 0, 0 }, &gEvent153Text02, 0, 440 },
    { 26, 2, 4, 1, { 0, 0, 0 }, &gEvent153Text03, 0, 442 },
    { 52, 0, 0, 1, { 0, 0, 0 }, &gEvent153Text04, MSG_SCRIPT_FLAG_SILHOUETTE, 490 },
    { 26, 5, 3, 1, { 0, 0, 0 }, &gEvent153Text05, 0, 720 },
    { 52, 0, 0, 1, { 0, 0, 0 }, &gEvent153Text06, MSG_SCRIPT_FLAG_SILHOUETTE, 760 },
    { 52, 0, 0, 1, { 0, 0, 0 }, &gEvent153Text07, MSG_SCRIPT_FLAG_SILHOUETTE, 850 },
    { 52, 0, 4, 1, { 0, 0, 0 }, &gEvent153Text08, MSG_SCRIPT_FLAG_SILHOUETTE, 852 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent153Text09, 0, 880 },
    { 52, 0, 0, 1, { 0, 0, 0 }, &gEvent153Text10, MSG_SCRIPT_FLAG_SILHOUETTE, 920 },
    { 52, 0, 0, 1, { 0, 0, 0 }, &gEvent153Text11, MSG_SCRIPT_FLAG_SILHOUETTE, 1100 },
    { 52, 0, 4, 1, { 0, 0, 0 }, &gEvent153Text12, MSG_SCRIPT_FLAG_SILHOUETTE, 1102 },
    { 52, 0, 4, 1, { 0, 0, 0 }, &gEvent153Text13, MSG_SCRIPT_FLAG_SILHOUETTE, 1104 },
    { 52, 0, 4, 1, { 0, 0, 0 }, &gEvent153Text14, MSG_SCRIPT_FLAG_SILHOUETTE, 1106 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent153Text15, 0, 1125 },
    { 52, 0, 0, 1, { 0, 0, 0 }, &gEvent153Text16, MSG_SCRIPT_FLAG_SILHOUETTE | MSG_SCRIPT_FLAG_END, 1160 },
};
#endif

static const EvSoundCue sEvent153SoundCues[2] = {
    { SONG_BGM_EVENT_SILENCE, 0, 0, 0 },
    { SONG_BGM_EVENT_SILENCE, 1205, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent153Camera[1] = {
    { -64537, 69888, 80896, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent153Track0[23] = {
    { 515, 1, { 0, 0 }, 104448, 105984, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 518, 120, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 515, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 518, 210, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 515, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 270, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 514, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 543, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 515, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 515, 875, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 538, 882, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 940, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 540, 1070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 540, 1110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 1120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 538, 1130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent153Tracks[1] = {
    { sEvent153Track0, 44, { 0, 0, 0 } },
};

const EventSequenceDef gEvent153 = {
    1,
    { 0, 0, 0 },
    sEvent153Tracks,
    sEvent153Camera,
    sEvent153Script,
    sEvent153SoundCues,
    NULL,
    1210,
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
#include "event_154_text.inc"
static const MessageScriptEntry sEvent154Script[25] = {
    { 44, 1, 1, 1, { 0, 0, 0 }, gEvent154Text00, 0, 280 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent154Text01, 0, 310 },
    { 44, 1, 1, 1, { 0, 0, 0 }, gEvent154Text02, 0, 340 },
    { 26, 1, 3, 1, { 0, 0, 0 }, gEvent154Text03, 0, 510 },
    { 44, 0, 1, 1, { 0, 0, 0 }, gEvent154Text04, 0, 540 },
    { 44, 1, 4, 1, { 0, 0, 0 }, gEvent154Text05, 0, 542 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent154Text06, 0, 570 },
    { 44, 0, 1, 1, { 0, 0, 0 }, gEvent154Text07, 0, 600 },
    { 44, 0, 4, 1, { 0, 0, 0 }, gEvent154Text08, 0, 602 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent154Text09, 0, 630 },
    { 44, 1, 1, 1, { 0, 0, 0 }, gEvent154Text10, 0, 660 },
    { 44, 0, 4, 1, { 0, 0, 0 }, gEvent154Text11, 0, 662 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent154Text12, 0, 850 },
    { 26, 0, 4, 1, { 0, 0, 0 }, gEvent154Text13, 0, 852 },
    { 26, 2, 0, 1, { 0, 0, 0 }, gEvent154Text14, 0, 1030 },
    { 26, 2, 4, 1, { 0, 0, 0 }, gEvent154Text15, 0, 1032 },
    { 26, 2, 2, 1, { 0, 0, 0 }, gEvent154Text16, 0, 1120 },
    { 44, 0, 1, 1, { 0, 0, 0 }, gEvent154Text17, 0, 1150 },
    { 44, 1, 4, 1, { 0, 0, 0 }, gEvent154Text18, 0, 1152 },
    { 26, 2, 2, 1, { 0, 0, 0 }, gEvent154Text19, 0, 1190 },
    { 26, 2, 4, 1, { 0, 0, 0 }, gEvent154Text20, 0, 1192 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent154Text21, 0, 1280 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent154Text22, 0, 1345 },
    { 44, 1, 1, 1, { 0, 0, 0 }, gEvent154Text23, 0, 1385 },
    { 44, 2, 4, 1, { 0, 0, 0 }, gEvent154Text24, MSG_SCRIPT_FLAG_END, 1390 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent154Script[25] = {
    { 44, 1, 1, 3, { 0, 0, 0 }, gEvent154Text00, 0, 280 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent154Text01, 0, 310 },
    { 44, 1, 1, 3, { 0, 0, 0 }, gEvent154Text02, 0, 340 },
    { 26, 1, 3, 3, { 0, 0, 0 }, gEvent154Text03, 0, 510 },
    { 44, 0, 1, 3, { 0, 0, 0 }, gEvent154Text04, 0, 540 },
    { 44, 1, 4, 3, { 0, 0, 0 }, gEvent154Text05, 0, 542 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent154Text06, 0, 570 },
    { 44, 0, 1, 3, { 0, 0, 0 }, gEvent154Text07, 0, 600 },
    { 44, 0, 4, 3, { 0, 0, 0 }, gEvent154Text08, 0, 602 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent154Text09, 0, 630 },
    { 44, 1, 1, 3, { 0, 0, 0 }, gEvent154Text10, 0, 660 },
    { 44, 0, 4, 3, { 0, 0, 0 }, gEvent154Text11, 0, 662 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent154Text12, 0, 850 },
    { 26, 0, 4, 3, { 0, 0, 0 }, gEvent154Text13, 0, 852 },
    { 26, 2, 0, 3, { 0, 0, 0 }, gEvent154Text14, 0, 1030 },
    { 26, 2, 4, 3, { 0, 0, 0 }, gEvent154Text15, 0, 1032 },
    { 26, 2, 2, 3, { 0, 0, 0 }, gEvent154Text16, 0, 1120 },
    { 44, 0, 1, 3, { 0, 0, 0 }, gEvent154Text17, 0, 1150 },
    { 44, 1, 4, 3, { 0, 0, 0 }, gEvent154Text18, 0, 1152 },
    { 26, 2, 2, 3, { 0, 0, 0 }, gEvent154Text19, 0, 1190 },
    { 26, 2, 4, 3, { 0, 0, 0 }, gEvent154Text20, 0, 1192 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent154Text21, 0, 1280 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent154Text22, 0, 1345 },
    { 44, 1, 1, 3, { 0, 0, 0 }, gEvent154Text23, 0, 1385 },
    { 44, 2, 4, 3, { 0, 0, 0 }, gEvent154Text24, MSG_SCRIPT_FLAG_END, 1390 },
};

#include "event_154_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent154Script[25] = {
    { 44, 1, 1, 1, { 0, 0, 0 }, &gEvent154Text00, 0, 280 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent154Text01, 0, 310 },
    { 44, 1, 1, 1, { 0, 0, 0 }, &gEvent154Text02, 0, 340 },
    { 26, 1, 3, 1, { 0, 0, 0 }, &gEvent154Text03, 0, 510 },
    { 44, 0, 1, 1, { 0, 0, 0 }, &gEvent154Text04, 0, 540 },
    { 44, 1, 4, 1, { 0, 0, 0 }, &gEvent154Text05, 0, 542 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent154Text06, 0, 570 },
    { 44, 0, 1, 1, { 0, 0, 0 }, &gEvent154Text07, 0, 600 },
    { 44, 0, 4, 1, { 0, 0, 0 }, &gEvent154Text08, 0, 602 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent154Text09, 0, 630 },
    { 44, 1, 1, 1, { 0, 0, 0 }, &gEvent154Text10, 0, 660 },
    { 44, 0, 4, 1, { 0, 0, 0 }, &gEvent154Text11, 0, 662 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent154Text12, 0, 850 },
    { 26, 0, 4, 1, { 0, 0, 0 }, &gEvent154Text13, 0, 852 },
    { 26, 2, 0, 1, { 0, 0, 0 }, &gEvent154Text14, 0, 1030 },
    { 26, 2, 4, 1, { 0, 0, 0 }, &gEvent154Text15, 0, 1032 },
    { 26, 2, 2, 1, { 0, 0, 0 }, &gEvent154Text16, 0, 1120 },
    { 44, 0, 1, 1, { 0, 0, 0 }, &gEvent154Text17, 0, 1150 },
    { 44, 1, 4, 1, { 0, 0, 0 }, &gEvent154Text18, 0, 1152 },
    { 26, 2, 2, 1, { 0, 0, 0 }, &gEvent154Text19, 0, 1190 },
    { 26, 2, 4, 1, { 0, 0, 0 }, &gEvent154Text20, 0, 1192 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent154Text21, 0, 1280 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent154Text22, 0, 1345 },
    { 44, 1, 1, 1, { 0, 0, 0 }, &gEvent154Text23, 0, 1385 },
    { 44, 2, 4, 1, { 0, 0, 0 }, &gEvent154Text24, MSG_SCRIPT_FLAG_END, 1390 },
};
#endif

static const EvSoundCue sEvent154SoundCues[7] = {
    { 65535, 0, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 285, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_SND_359, 1300, 0, 0 },
    { SONG_SND_375, 1402, 0, 0 },
    { SONG_EV_FLASH01, 1520, 0, 0 },
    { SONG_EV_FLASH01, 1530, 0, 0 },
    { SONG_EV_FLASH02, 1540, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent154Camera[6] = {
    { -65375, 34048, 84224, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64136, 61696, 65280, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 100, { 0, 0 }, NULL },
    { -64016, 61696, 60928, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -64006, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_HALF_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -63996, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_HALF_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -63966, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_KEYFRAME_FLAG_END | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 30, { 0, 0 }, NULL },
};

static const EventBgEffectEntry sEvent154BgEffects[3] = {
    { 1392, 0, 0, 0, 0 },
    { 1402, 0, 0, 0, 0x4 },
    { 1412, 6, 64000, 40448, 0x8001 },
};

static const EventCharaKeyframe sEvent154Track0[26] = {
    { 515, 1, { 0, 0 }, 6912, 99328, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 522, 70, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 515, 73, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 515, 80, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 532, 130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 515, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 518, 230, { 0, 0 }, 50944, 76544, 0, 515, { 0, 0 }, 67, NULL, NULL },
    { 515, 305, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 538, 312, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 515, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 540, 820, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 540, 880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 910, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 940, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 516, 970, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 514, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 543, 1050, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 1070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 1080, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 1210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 518, 1240, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 515, 1300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 560, 9000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent154Track1[6] = {
    { 410, 661, { 0, 0 }, 71424, 66560, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 415, 663, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 416, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 410, 1387, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 414, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 1029, NULL, NULL },
    { 414, 9000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33797, NULL, NULL },
};

static const EventCharaTrack sEvent154Tracks[2] = {
    { sEvent154Track0, 44, { 0, 0, 0 } },
    { sEvent154Track1, 30, { 0, 0, 0 } },
};

const EventSequenceDef gEvent154 = {
    2,
    { 0, 0, 0 },
    sEvent154Tracks,
    sEvent154Camera,
    sEvent154Script,
    sEvent154SoundCues,
    sEvent154BgEffects,
    1620,
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
#include "event_155_text.inc"
static const MessageScriptEntry sEvent155Script[26] = {
    { 52, 0, 0, 1, { 0, 0, 0 }, gEvent155Text00, MSG_SCRIPT_FLAG_SILHOUETTE, 210 },
    { 26, 0, 3, 1, { 0, 0, 0 }, gEvent155Text01, 0, 240 },
    { 52, 0, 0, 1, { 0, 0, 0 }, gEvent155Text02, MSG_SCRIPT_FLAG_SILHOUETTE, 280 },
    { 26, 0, 3, 1, { 0, 0, 0 }, gEvent155Text03, 0, 310 },
    { 52, 0, 0, 1, { 0, 0, 0 }, gEvent155Text04, MSG_SCRIPT_FLAG_SILHOUETTE, 350 },
    { 56, 0, 4, 1, { 0, 0, 0 }, gEvent155Text05, MSG_SCRIPT_FLAG_SILHOUETTE, 360 },
    { 26, 0, 3, 1, { 0, 0, 0 }, gEvent155Text06, 0, 620 },
    { 56, 0, 1, 1, { 0, 0, 0 }, gEvent155Text07, 0, 650 },
    { 26, 0, 3, 1, { 0, 0, 0 }, gEvent155Text08, 0, 680 },
    { 26, 2, 4, 1, { 0, 0, 0 }, gEvent155Text09, 0, 682 },
    { 56, 1, 1, 1, { 0, 0, 0 }, gEvent155Text10, 0, 715 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent155Text11, 0, 745 },
    { 26, 2, 2, 1, { 0, 0, 0 }, gEvent155Text12, 0, 1030 },
    { 56, 1, 1, 1, { 0, 0, 0 }, gEvent155Text13, 0, 1060 },
    { 26, 2, 2, 1, { 0, 0, 0 }, gEvent155Text14, 0, 1090 },
    { 56, 0, 1, 1, { 0, 0, 0 }, gEvent155Text15, 0, 1120 },
    { 26, 2, 2, 1, { 0, 0, 0 }, gEvent155Text16, 0, 1190 },
    { 56, 1, 1, 1, { 0, 0, 0 }, gEvent155Text17, 0, 1220 },
    { 61, 0, 2, 1, { 0, 0, 0 }, gEvent155Text18, MSG_SCRIPT_FLAG_SILHOUETTE, 1250 },
    { 26, 3, 2, 1, { 0, 0, 0 }, gEvent155Text19, 0, 1460 },
    { 26, 3, 2, 1, { 0, 0, 0 }, gEvent155Text20, 0, 1530 },
    { 61, 1, 2, 1, { 0, 0, 0 }, gEvent155Text21, 0, 1560 },
    { 61, 3, 2, 1, { 0, 0, 0 }, gEvent155Text22, 0, 1800 },
    { 26, 4, 3, 1, { 0, 0, 0 }, gEvent155Text23, 0, 1830 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent155Text24, 0, 1910 },
    { 56, 1, 1, 1, { 0, 0, 0 }, gEvent155Text25, MSG_SCRIPT_FLAG_END, 2000 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent155Script[26] = {
    { 52, 0, 0, 3, { 0, 0, 0 }, gEvent155Text00, MSG_SCRIPT_FLAG_SILHOUETTE, 210 },
    { 26, 0, 3, 3, { 0, 0, 0 }, gEvent155Text01, 0, 240 },
    { 52, 0, 0, 3, { 0, 0, 0 }, gEvent155Text02, MSG_SCRIPT_FLAG_SILHOUETTE, 280 },
    { 26, 0, 3, 3, { 0, 0, 0 }, gEvent151Text09, 0, 310 },
    { 52, 0, 0, 3, { 0, 0, 0 }, gEvent155Text04, MSG_SCRIPT_FLAG_SILHOUETTE, 350 },
    { 56, 0, 4, 3, { 0, 0, 0 }, gEvent155Text05, MSG_SCRIPT_FLAG_SILHOUETTE, 360 },
    { 26, 0, 3, 3, { 0, 0, 0 }, gEvent155Text06, 0, 620 },
    { 56, 0, 1, 3, { 0, 0, 0 }, gEvent155Text07, 0, 650 },
    { 26, 0, 3, 3, { 0, 0, 0 }, gEvent155Text08, 0, 680 },
    { 26, 2, 4, 3, { 0, 0, 0 }, gEvent155Text09, 0, 682 },
    { 56, 1, 1, 3, { 0, 0, 0 }, gEvent155Text10, 0, 715 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent155Text11, 0, 745 },
    { 26, 2, 2, 3, { 0, 0, 0 }, gEvent155Text12, 0, 1030 },
    { 56, 1, 1, 3, { 0, 0, 0 }, gEvent155Text13, 0, 1060 },
    { 26, 2, 2, 3, { 0, 0, 0 }, gEvent155Text14, 0, 1090 },
    { 56, 0, 1, 3, { 0, 0, 0 }, gEvent155Text15, 0, 1120 },
    { 26, 2, 2, 3, { 0, 0, 0 }, gEvent155Text16, 0, 1190 },
    { 56, 1, 1, 3, { 0, 0, 0 }, gEvent155Text17, 0, 1220 },
    { 61, 0, 2, 3, { 0, 0, 0 }, gEvent155Text18, MSG_SCRIPT_FLAG_SILHOUETTE, 1250 },
    { 26, 3, 2, 3, { 0, 0, 0 }, gEvent155Text19, 0, 1460 },
    { 26, 3, 2, 3, { 0, 0, 0 }, gEvent155Text20, 0, 1530 },
    { 61, 1, 2, 3, { 0, 0, 0 }, gEvent155Text21, 0, 1560 },
    { 61, 3, 2, 3, { 0, 0, 0 }, gEvent155Text22, 0, 1800 },
    { 26, 4, 3, 3, { 0, 0, 0 }, gEvent155Text23, 0, 1830 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent155Text24, 0, 1910 },
    { 56, 1, 1, 3, { 0, 0, 0 }, gEvent155Text25, MSG_SCRIPT_FLAG_END, 2000 },
};

#include "event_155_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent155Script[26] = {
    { 52, 0, 0, 1, { 0, 0, 0 }, &gEvent155Text00, MSG_SCRIPT_FLAG_SILHOUETTE, 210 },
    { 26, 0, 3, 1, { 0, 0, 0 }, &gEvent155Text01, 0, 240 },
    { 52, 0, 0, 1, { 0, 0, 0 }, &gEvent155Text02, MSG_SCRIPT_FLAG_SILHOUETTE, 280 },
    { 26, 0, 3, 1, { 0, 0, 0 }, &gEvent155Text03, 0, 310 },
    { 52, 0, 0, 1, { 0, 0, 0 }, &gEvent155Text04, MSG_SCRIPT_FLAG_SILHOUETTE, 350 },
    { 56, 0, 4, 1, { 0, 0, 0 }, &gEvent155Text05, MSG_SCRIPT_FLAG_SILHOUETTE, 360 },
    { 26, 0, 3, 1, { 0, 0, 0 }, &gEvent155Text06, 0, 620 },
    { 56, 0, 1, 1, { 0, 0, 0 }, &gEvent155Text07, 0, 650 },
    { 26, 0, 3, 1, { 0, 0, 0 }, &gEvent155Text08, 0, 680 },
    { 26, 2, 4, 1, { 0, 0, 0 }, &gEvent155Text09, 0, 682 },
    { 56, 1, 1, 1, { 0, 0, 0 }, &gEvent155Text10, 0, 715 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent155Text11, 0, 745 },
    { 26, 2, 2, 1, { 0, 0, 0 }, &gEvent155Text12, 0, 1030 },
    { 56, 1, 1, 1, { 0, 0, 0 }, &gEvent155Text13, 0, 1060 },
    { 26, 2, 2, 1, { 0, 0, 0 }, &gEvent155Text14, 0, 1090 },
    { 56, 0, 1, 1, { 0, 0, 0 }, &gEvent155Text15, 0, 1120 },
    { 26, 2, 2, 1, { 0, 0, 0 }, &gEvent155Text16, 0, 1190 },
    { 56, 1, 1, 1, { 0, 0, 0 }, &gEvent155Text17, 0, 1220 },
    { 61, 0, 2, 1, { 0, 0, 0 }, &gEvent155Text18, MSG_SCRIPT_FLAG_SILHOUETTE, 1250 },
    { 26, 3, 2, 1, { 0, 0, 0 }, &gEvent155Text19, 0, 1460 },
    { 26, 3, 2, 1, { 0, 0, 0 }, &gEvent155Text20, 0, 1530 },
    { 61, 1, 2, 1, { 0, 0, 0 }, &gEvent155Text21, 0, 1560 },
    { 61, 3, 2, 1, { 0, 0, 0 }, &gEvent155Text22, 0, 1800 },
    { 26, 4, 3, 1, { 0, 0, 0 }, &gEvent155Text23, 0, 1830 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent155Text24, 0, 1910 },
    { 56, 1, 1, 1, { 0, 0, 0 }, &gEvent155Text25, MSG_SCRIPT_FLAG_END, 2000 },
};
#endif

static const EvSoundCue sEvent155SoundCues[9] = {
    { SONG_BGM_EVENT_UNREST, 0, 0, 0 },
    { SONG_SND_379, 560, 0, 0 },
    { SONG_SND_376, 758, 0, 0 },
    { SONG_EV_FLASH00, 780, 0, 0 },
    { SONG_EV_WOMAN_RSTONEL, 1150, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 1245, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_EV_FLASH00, 1660, 0, 0 },
    { SONG_BGM_EVENT2, 1968, 0, 0 },
    { SONG_SND_359, 1970, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent155Camera[14] = {
    { -65166, 186112, 65792, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65156, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_HALF_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -65116, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_HALF_FLASH | CAMERA_MODE_KEEP, 20, { 0, 0 }, NULL },
    { -65106, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_HALF_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -65026, 195840, 58368, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -64976, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_HALF_FLASH | CAMERA_MODE_KEEP, 50, { 0, 0 }, NULL },
    { -64776, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64756, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 20, { 0, 0 }, NULL },
    { -64736, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 20, { 0, 0 }, NULL },
    { -64656, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -63876, 168448, 71168, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 100, { 0, 0 }, NULL },
    { -63826, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 50, { 0, 0 }, NULL },
    { -62536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -60536, 189952, 64768, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 100, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent155Track0[14] = {
    { 515, 1, { 0, 0 }, 152064, 88064, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 518, 150, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 515, 746, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 563, 760, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 548, 780, { 0, 0 }, 200704, 62976, 0, 515, { 0, 0 }, 67, NULL, NULL },
    { 550, 810, { 0, 0 }, 161024, 80384, 0, 515, { 0, 0 }, 67, NULL, NULL },
    { 547, 1380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 547, 1480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 545, 1860, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 546, 1882, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 1930, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 1940, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 1970, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 560, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent155Track1[8] = {
    { 688, 560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 688, 780, { 0, 0 }, 205824, 60160, 0, 0, { 0, 0 }, 18, EventCharaFadeIn, NULL },
    { 688, 880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 21, NULL, NULL },
    { 690, 1000, { 0, 0 }, 179968, 72448, 0, 688, { 0, 0 }, 19, NULL, NULL },
    { 688, 1140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 690, 1160, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 688, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 688, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent155Track2[10] = {
    { 920, 1251, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8274, NULL, NULL },
    { 920, 1252, { 0, 0 }, 153600, 47360, 0, 0, { 0, 0 }, 16722, NULL, NULL },
    { 920, 1300, { 0, 0 }, 153600, 71680, 0, 920, { 0, 0 }, 339, NULL, NULL },
    { 920, 1350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 469, NULL, NULL },
    { 920, 1540, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 336, EventCharaCircleSlow, NULL },
    { 920, 1570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 469, NULL, NULL },
    { 920, 1610, { 0, 0 }, 161024, 62976, 0, 920, { 0, 0 }, 339, NULL, NULL },
    { 920, 1640, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 341, NULL, NULL },
    { 920, 1660, { 0, 0 }, 161024, 66560, 0, 0, { 0, 0 }, 4435, EventCharaFadeOut, NULL },
    { 920, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98370, NULL, NULL },
};

static const EventCharaKeyframe sEvent155Track3[3] = {
    { 928, 1380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 927, 1430, { 0, 0 }, 156928, 77824, 0, 0, { 0, 0 }, 16658, NULL, NULL },
    { 928, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaTrack sEvent155Tracks[4] = {
    { sEvent155Track0, 44, { 0, 0, 0 } },
    { sEvent155Track1, 64, { 0, 0, 0 } },
    { sEvent155Track2, 87, { 0, 0, 0 } },
    { sEvent155Track3, 93, { 0, 0, 0 } },
};

const EventSequenceDef gEvent155 = {
    4,
    { 0, 0, 0 },
    sEvent155Tracks,
    sEvent155Camera,
    sEvent155Script,
    sEvent155SoundCues,
    NULL,
    2060,
    0,
    1,
    0,
    0,
    0,
    0,
    166,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_156_text.inc"
static const MessageScriptEntry sEvent156Script[21] = {
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent156Text00, 0, 120 },
    { 56, 0, 1, 1, { 0, 0, 0 }, gEvent156Text01, 0, 150 },
    { 26, 3, 3, 1, { 0, 0, 0 }, gEvent156Text02, 0, 250 },
    { 56, 0, 1, 1, { 0, 0, 0 }, gEvent156Text03, 0, 280 },
    { 56, 0, 4, 1, { 0, 0, 0 }, gEvent156Text04, 0, 282 },
    { 26, 0, 3, 1, { 0, 0, 0 }, gEvent156Text05, 0, 310 },
    { 26, 1, 4, 1, { 0, 0, 0 }, gEvent156Text06, 0, 312 },
    { 56, 1, 1, 1, { 0, 0, 0 }, gEvent156Text07, 0, 540 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent156Text08, 0, 860 },
    { 56, 0, 1, 1, { 0, 0, 0 }, gEvent156Text09, 0, 890 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent156Text10, 0, 920 },
    { 56, 0, 1, 1, { 0, 0, 0 }, gEvent156Text11, 0, 950 },
    { 56, 0, 0, 1, { 0, 0, 0 }, gEvent156Text12, 0, 1070 },
    { 62, 0, 0, 1, { 0, 0, 0 }, gEvent156Text13, 0, 1130 },
    { 62, 0, 4, 1, { 0, 0, 0 }, gEvent156Text14, 0, 1132 },
    { 62, 0, 4, 1, { 0, 0, 0 }, gEvent156Text15, 0, 1134 },
    { 62, 0, 0, 1, { 0, 0, 0 }, gEvent156Text16, 0, 1160 },
    { 62, 0, 4, 1, { 0, 0, 0 }, gEvent156Text17, 0, 1162 },
    { 62, 0, 4, 1, { 0, 0, 0 }, gEvent156Text18, 0, 1164 },
    { 62, 0, 0, 1, { 0, 0, 0 }, gEvent156Text19, 0, 1190 },
    { 62, 0, 4, 1, { 0, 0, 0 }, gEvent156Text20, MSG_SCRIPT_FLAG_END, 1192 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent156Script[21] = {
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent156Text00, 0, 120 },
    { 56, 0, 1, 3, { 0, 0, 0 }, gEvent156Text01, 0, 150 },
    { 26, 3, 3, 3, { 0, 0, 0 }, gEvent156Text02, 0, 250 },
    { 56, 0, 1, 3, { 0, 0, 0 }, gEvent156Text03, 0, 280 },
    { 56, 0, 4, 3, { 0, 0, 0 }, gEvent156Text04, 0, 282 },
    { 26, 0, 3, 3, { 0, 0, 0 }, gEvent156Text05, 0, 310 },
    { 26, 1, 4, 3, { 0, 0, 0 }, gEvent156Text06, 0, 312 },
    { 56, 1, 1, 3, { 0, 0, 0 }, gEvent156Text07, 0, 540 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent156Text08, 0, 860 },
    { 56, 0, 1, 3, { 0, 0, 0 }, gEvent156Text09, 0, 890 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent156Text10, 0, 920 },
    { 56, 0, 1, 3, { 0, 0, 0 }, gEvent156Text11, 0, 950 },
    { 56, 1, 0, 3, { 0, 0, 0 }, gEvent156Text12, 0, 1070 },
    { 62, 0, 0, 3, { 0, 0, 0 }, gEvent156Text13, 0, 1130 },
    { 62, 0, 4, 3, { 0, 0, 0 }, gEvent156Text14, 0, 1132 },
    { 62, 0, 4, 3, { 0, 0, 0 }, gEvent156Text15, 0, 1134 },
    { 62, 0, 0, 3, { 0, 0, 0 }, gEvent156Text16, 0, 1160 },
    { 62, 0, 4, 3, { 0, 0, 0 }, gEvent156Text17, 0, 1162 },
    { 62, 0, 4, 3, { 0, 0, 0 }, gEvent156Text18, 0, 1164 },
    { 62, 0, 0, 3, { 0, 0, 0 }, gEvent156Text19, 0, 1190 },
    { 62, 0, 4, 3, { 0, 0, 0 }, gEvent156Text20, MSG_SCRIPT_FLAG_END, 1192 },
};

#include "event_156_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent156Script[21] = {
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent156Text00, 0, 120 },
    { 56, 0, 1, 1, { 0, 0, 0 }, &gEvent156Text01, 0, 150 },
    { 26, 3, 3, 1, { 0, 0, 0 }, &gEvent156Text02, 0, 250 },
    { 56, 0, 1, 1, { 0, 0, 0 }, &gEvent156Text03, 0, 280 },
    { 56, 0, 4, 1, { 0, 0, 0 }, &gEvent156Text04, 0, 282 },
    { 26, 0, 3, 1, { 0, 0, 0 }, &gEvent156Text05, 0, 310 },
    { 26, 1, 4, 1, { 0, 0, 0 }, &gEvent156Text06, 0, 312 },
    { 56, 1, 1, 1, { 0, 0, 0 }, &gEvent156Text07, 0, 540 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent156Text08, 0, 860 },
    { 56, 0, 1, 1, { 0, 0, 0 }, &gEvent156Text09, 0, 890 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent156Text10, 0, 920 },
    { 56, 0, 1, 1, { 0, 0, 0 }, &gEvent156Text11, 0, 950 },
    { 56, 0, 0, 1, { 0, 0, 0 }, &gEvent156Text12, 0, 1070 },
    { 62, 0, 0, 1, { 0, 0, 0 }, &gEvent156Text13, 0, 1130 },
    { 62, 0, 4, 1, { 0, 0, 0 }, &gEvent156Text14, 0, 1132 },
    { 62, 0, 4, 1, { 0, 0, 0 }, &gEvent156Text15, 0, 1134 },
    { 62, 0, 0, 1, { 0, 0, 0 }, &gEvent156Text16, 0, 1160 },
    { 62, 0, 4, 1, { 0, 0, 0 }, &gEvent156Text17, 0, 1162 },
    { 62, 0, 4, 1, { 0, 0, 0 }, &gEvent156Text18, 0, 1164 },
    { 62, 0, 0, 1, { 0, 0, 0 }, &gEvent156Text19, 0, 1190 },
    { 62, 0, 4, 1, { 0, 0, 0 }, &gEvent156Text20, MSG_SCRIPT_FLAG_END, 1192 },
};
#endif

static const EvSoundCue sEvent156SoundCues[5] = {
    { SONG_BGM_EVENT_UNREST, 0, 0, 0 },
    { SONG_EV_CARDTHR, 507, 0, 0 },
    { SONG_SND_377, 640, 0, 0 },
    { SONG_SND_379, 990, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 1245, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent156Camera[2] = {
    { -64496, 193024, 61184, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -62536, 182016, 66560, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
};

static const EventBgEffectEntry sEvent156BgEffects[5] = {
    { 580, 0, 0, 0, 0 },
    { 640, 0, 60, 0, 0x4 },
    { 736, 5, 169728, 54016, 0x1 },
    { 740, 0, 0, 0, 0x2 },
    { 840, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent156Track0[14] = {
    { 561, 220, { 0, 0 }, 181760, 73216, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 562, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 512, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 559, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 670, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 515, 855, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 538, 862, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 915, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 538, 922, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 990, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 1040, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 515, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent156Track1[9] = {
    { 688, 170, { 0, 0 }, 203520, 62720, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 691, 340, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 691, 470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 691, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 692, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 688, 970, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 688, 990, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 4, NULL, NULL },
    { 688, 1050, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 260, EventCharaFadeOut, NULL },
    { 688, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32770, NULL, NULL },
};

static const EventCharaKeyframe sEvent156Track2[10] = {
    { 591, 186, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8258, NULL, NULL },
    { 607, 490, { 0, 0 }, 203520, 62720, 0, 0, { 0, 0 }, 16658, NULL, NULL },
    { 591, 506, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 591, 507, { 0, 0 }, 197632, 56832, 0, 0, { 0, 0 }, 322, NULL, NULL },
    { 591, 517, { 0, 0 }, 186880, 63232, 0, 591, { 0, 0 }, 323, NULL, NULL },
    { 591, 520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 591, 526, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 604, 600, { 0, 0 }, 181760, 73216, 0, 0, { 0, 0 }, 338, NULL, NULL },
    { 591, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 591, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98373, NULL, NULL },
};

static const EventCharaTrack sEvent156Tracks[3] = {
    { sEvent156Track0, 44, { 0, 0, 0 } },
    { sEvent156Track1, 64, { 0, 0, 0 } },
    { sEvent156Track2, 50, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent156 = {
    3,
    { 0, 0, 0 },
    sEvent156Tracks,
    sEvent156Camera,
    sEvent156Script,
    sEvent156SoundCues,
    sEvent156BgEffects,
    1250,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    157,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent156 = {
    3,
    { 0, 0, 0 },
    sEvent156Tracks,
    sEvent156Camera,
    sEvent156Script,
    sEvent156SoundCues,
    sEvent156BgEffects,
    1250,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    155,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_157_text.inc"
static const MessageScriptEntry sEvent157Script[18] = {
    { 55, 5, 1, 1, { 0, 0, 0 }, gEvent157Text00, 0, 370 },
    { 38, 0, 0, 1, { 0, 0, 0 }, gEvent157Text01, 0, 520 },
    { 55, 5, 3, 1, { 0, 0, 0 }, gEvent157Text02, 0, 570 },
    { 55, 0, 4, 1, { 0, 0, 0 }, gEvent157Text03, 0, 572 },
    { 38, 2, 0, 1, { 0, 0, 0 }, gEvent157Text04, 0, 590 },
    { 57, 0, 3, 1, { 0, 0, 0 }, gEvent157Text05, 0, 610 },
    { 57, 0, 3, 1, { 0, 0, 0 }, gEvent157Text06, 0, 810 },
    { 55, 0, 1, 1, { 0, 0, 0 }, gEvent157Text07, 0, 1030 },
    { 55, 0, 4, 1, { 0, 0, 0 }, gEvent157Text08, 0, 1032 },
    { 38, 0, 0, 1, { 0, 0, 0 }, gEvent157Text09, 0, 1060 },
    { 55, 0, 3, 1, { 0, 0, 0 }, gEvent157Text10, 0, 1100 },
    { 55, 0, 1, 1, { 0, 0, 0 }, gEvent157Text11, 0, 1280 },
    { 57, 0, 3, 1, { 0, 0, 0 }, gEvent157Text12, 0, 1310 },
    { 55, 5, 1, 1, { 0, 0, 0 }, gEvent157Text13, 0, 1350 },
    { 55, 0, 4, 1, { 0, 0, 0 }, gEvent157Text14, 0, 1352 },
    { 38, 3, 0, 1, { 0, 0, 0 }, gEvent157Text15, 0, 1380 },
    { 55, 0, 1, 1, { 0, 0, 0 }, gEvent157Text16, 0, 1410 },
    { 57, 0, 3, 1, { 0, 0, 0 }, gEvent157Text17, MSG_SCRIPT_FLAG_END, 1640 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent157Script[18] = {
    { 55, 5, 1, 3, { 0, 0, 0 }, gEvent157Text00, 0, 370 },
    { 38, 0, 0, 3, { 0, 0, 0 }, gEvent157Text01, 0, 520 },
    { 55, 5, 3, 3, { 0, 0, 0 }, gEvent157Text02, 0, 570 },
    { 55, 0, 4, 3, { 0, 0, 0 }, gEvent157Text03, 0, 572 },
    { 38, 2, 0, 3, { 0, 0, 0 }, gEvent157Text04, 0, 590 },
    { 57, 0, 3, 3, { 0, 0, 0 }, gEvent157Text05, 0, 610 },
    { 57, 0, 3, 3, { 0, 0, 0 }, gEvent157Text06, 0, 810 },
    { 55, 0, 1, 3, { 0, 0, 0 }, gEvent157Text07, 0, 1030 },
    { 55, 0, 4, 3, { 0, 0, 0 }, gEvent157Text08, 0, 1032 },
    { 38, 0, 0, 3, { 0, 0, 0 }, gEvent157Text09, 0, 1060 },
    { 55, 0, 3, 3, { 0, 0, 0 }, gEvent157Text10, 0, 1100 },
    { 55, 0, 1, 3, { 0, 0, 0 }, gEvent157Text11, 0, 1280 },
    { 57, 0, 3, 3, { 0, 0, 0 }, gEvent157Text12, 0, 1310 },
    { 55, 5, 1, 3, { 0, 0, 0 }, gEvent157Text13, 0, 1350 },
    { 55, 0, 4, 3, { 0, 0, 0 }, gEvent157Text14, 0, 1352 },
    { 38, 3, 0, 3, { 0, 0, 0 }, gEvent157Text15, 0, 1380 },
    { 55, 0, 1, 3, { 0, 0, 0 }, gEvent157Text16, 0, 1410 },
    { 57, 0, 3, 3, { 0, 0, 0 }, gEvent157Text17, MSG_SCRIPT_FLAG_END, 1640 },
};

#include "event_157_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent157Script[18] = {
    { 55, 5, 1, 1, { 0, 0, 0 }, &gEvent157Text00, 0, 370 },
    { 38, 0, 0, 1, { 0, 0, 0 }, &gEvent157Text01, 0, 520 },
    { 55, 5, 3, 1, { 0, 0, 0 }, &gEvent157Text02, 0, 570 },
    { 55, 0, 4, 1, { 0, 0, 0 }, &gEvent157Text03, 0, 572 },
    { 38, 2, 0, 1, { 0, 0, 0 }, &gEvent157Text04, 0, 590 },
    { 57, 0, 3, 1, { 0, 0, 0 }, &gEvent157Text05, 0, 610 },
    { 57, 0, 3, 1, { 0, 0, 0 }, &gEvent157Text06, 0, 810 },
    { 55, 0, 1, 1, { 0, 0, 0 }, &gEvent157Text07, 0, 1030 },
    { 55, 0, 4, 1, { 0, 0, 0 }, &gEvent157Text08, 0, 1032 },
    { 38, 0, 0, 1, { 0, 0, 0 }, &gEvent157Text09, 0, 1060 },
    { 55, 0, 3, 1, { 0, 0, 0 }, &gEvent157Text10, 0, 1100 },
    { 55, 0, 1, 1, { 0, 0, 0 }, &gEvent157Text11, 0, 1280 },
    { 57, 0, 3, 1, { 0, 0, 0 }, &gEvent157Text12, 0, 1310 },
    { 55, 5, 1, 1, { 0, 0, 0 }, &gEvent157Text13, 0, 1350 },
    { 55, 0, 4, 1, { 0, 0, 0 }, &gEvent157Text14, 0, 1352 },
    { 38, 3, 0, 1, { 0, 0, 0 }, &gEvent157Text15, 0, 1380 },
    { 55, 0, 1, 1, { 0, 0, 0 }, &gEvent157Text16, 0, 1410 },
    { 57, 0, 3, 1, { 0, 0, 0 }, &gEvent157Text17, MSG_SCRIPT_FLAG_END, 1640 },
};
#endif

static const EvSoundCue sEvent157SoundCues[4] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_EV_WARPOUT, 150, 0, 0 },
    { SONG_EV_WARPOUT, 420, 0, 0 },
    { SONG_BGM_EVENT_XIII, 1695, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent157Camera[3] = {
    { -65406, 65536, 48640, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65116, 58368, 52480, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -64537, 65536, 54784, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent157Track0[9] = {
    { 891, 300, { 0, 0 }, 65792, 55808, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 892, 320, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 889, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 889, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 889, 960, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 889, 990, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 889, 1080, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 889, 1260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 889, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent157Track1[10] = {
    { 738, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 738, 470, { 0, 0 }, 84992, 72448, 0, 0, { 0, 0 }, 2, EventCharaFadeIn, NULL },
    { 742, 500, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 738, 630, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 738, 760, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 738, 1120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 738, 1250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 738, 1375, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 740, 1382, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 738, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent157Track2[9] = {
    { 883, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 883, 200, { 0, 0 }, 50944, 64256, 0, 0, { 0, 0 }, 66, EventCharaFadeIn, NULL },
    { 883, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 883, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 884, 1430, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 883, 1450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 887, 1470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 887, 1600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 887, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent157Tracks[3] = {
    { sEvent157Track0, 83, { 0, 0, 0 } },
    { sEvent157Track1, 67, { 0, 0, 0 } },
    { sEvent157Track2, 82, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent157 = {
    3,
    { 0, 0, 0 },
    sEvent157Tracks,
    sEvent157Camera,
    sEvent157Script,
    sEvent157SoundCues,
    NULL,
    1700,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    158,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent157 = {
    3,
    { 0, 0, 0 },
    sEvent157Tracks,
    sEvent157Camera,
    sEvent157Script,
    sEvent157SoundCues,
    NULL,
    1700,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    156,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_158_text.inc"
static const MessageScriptEntry sEvent158Script[21] = {
    { 26, 0, 3, 1, { 0, 0, 0 }, gEvent158Text00, 0, 180 },
    { 26, 0, 3, 1, { 0, 0, 0 }, gEvent158Text01, 0, 310 },
    { 26, 0, 3, 1, { 0, 0, 0 }, gEvent158Text02, 0, 610 },
    { 26, 5, 3, 1, { 0, 0, 0 }, gEvent158Text03, 0, 660 },
    { 61, 0, 0, 1, { 0, 0, 0 }, gEvent158Text04, 0, 840 },
    { 26, 3, 3, 1, { 0, 0, 0 }, gEvent158Text05, 0, 980 },
    { 26, 3, 3, 1, { 0, 0, 0 }, gEvent158Text06, 0, 1230 },
    { 61, 0, 1, 1, { 0, 0, 0 }, gEvent158Text07, 0, 1260 },
    { 26, 0, 3, 1, { 0, 0, 0 }, gEvent158Text08, 0, 1290 },
    { 61, 0, 1, 1, { 0, 0, 0 }, gEvent158Text09, 0, 1320 },
    { 61, 3, 1, 1, { 0, 0, 0 }, gEvent158Text10, 0, 1410 },
    { 61, 0, 4, 1, { 0, 0, 0 }, gEvent158Text11, 0, 1414 },
    { 26, 0, 3, 1, { 0, 0, 0 }, gEvent158Text12, 0, 1450 },
    { 61, 0, 1, 1, { 0, 0, 0 }, gEvent158Text13, 0, 1480 },
    { 61, 0, 4, 1, { 0, 0, 0 }, gEvent158Text14, 0, 1482 },
    { 61, 0, 4, 1, { 0, 0, 0 }, gEvent158Text15, 0, 1484 },
    { 26, 0, 3, 1, { 0, 0, 0 }, gEvent158Text16, 0, 1675 },
    { 61, 3, 1, 1, { 0, 0, 0 }, gEvent158Text17, 0, 1700 },
    { 26, 3, 3, 1, { 0, 0, 0 }, gEvent158Text18, 0, 1890 },
    { 61, 1, 1, 1, { 0, 0, 0 }, gEvent158Text19, 0, 1920 },
    { 26, 4, 3, 1, { 0, 0, 0 }, gEvent158Text20, MSG_SCRIPT_FLAG_END, 1950 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent158Script[21] = {
    { 26, 0, 3, 3, { 0, 0, 0 }, gEvent158Text00, 0, 180 },
    { 26, 0, 3, 3, { 0, 0, 0 }, gEvent158Text01, 0, 310 },
    { 26, 0, 3, 3, { 0, 0, 0 }, gEvent158Text02, 0, 610 },
    { 26, 5, 3, 3, { 0, 0, 0 }, gEvent158Text03, 0, 660 },
    { 61, 0, 0, 3, { 0, 0, 0 }, gEvent158Text04, 0, 840 },
    { 26, 3, 3, 3, { 0, 0, 0 }, gEvent158Text05, 0, 980 },
    { 26, 3, 3, 3, { 0, 0, 0 }, gEvent158Text06, 0, 1230 },
    { 61, 0, 1, 3, { 0, 0, 0 }, gEvent158Text07, 0, 1260 },
    { 26, 0, 3, 3, { 0, 0, 0 }, gEvent158Text08, 0, 1290 },
    { 61, 0, 1, 3, { 0, 0, 0 }, gEvent158Text09, 0, 1320 },
    { 61, 3, 1, 3, { 0, 0, 0 }, gEvent158Text10, 0, 1410 },
    { 61, 0, 4, 3, { 0, 0, 0 }, gEvent158Text11, 0, 1414 },
    { 26, 0, 3, 3, { 0, 0, 0 }, gEvent158Text12, 0, 1450 },
    { 61, 0, 1, 3, { 0, 0, 0 }, gEvent158Text13, 0, 1480 },
    { 61, 0, 4, 3, { 0, 0, 0 }, gEvent158Text14, 0, 1482 },
    { 61, 0, 4, 3, { 0, 0, 0 }, gEvent158Text15, 0, 1484 },
    { 26, 0, 3, 3, { 0, 0, 0 }, gEvent158Text16, 0, 1675 },
    { 61, 3, 1, 3, { 0, 0, 0 }, gEvent158Text17, 0, 1700 },
    { 26, 3, 3, 3, { 0, 0, 0 }, gEvent158Text18, 0, 1890 },
    { 61, 1, 1, 3, { 0, 0, 0 }, gEvent158Text19, 0, 1920 },
    { 26, 4, 3, 3, { 0, 0, 0 }, gEvent000Text15, MSG_SCRIPT_FLAG_END, 1950 },
};

#include "event_158_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent158Script[21] = {
    { 26, 0, 3, 1, { 0, 0, 0 }, &gEvent158Text00, 0, 180 },
    { 26, 0, 3, 1, { 0, 0, 0 }, &gEvent158Text01, 0, 310 },
    { 26, 0, 3, 1, { 0, 0, 0 }, &gEvent158Text02, 0, 610 },
    { 26, 5, 3, 1, { 0, 0, 0 }, &gEvent158Text03, 0, 660 },
    { 61, 0, 0, 1, { 0, 0, 0 }, &gEvent158Text04, 0, 840 },
    { 26, 3, 3, 1, { 0, 0, 0 }, &gEvent158Text05, 0, 980 },
    { 26, 3, 3, 1, { 0, 0, 0 }, &gEvent158Text06, 0, 1230 },
    { 61, 0, 1, 1, { 0, 0, 0 }, &gEvent158Text07, 0, 1260 },
    { 26, 0, 3, 1, { 0, 0, 0 }, &gEvent158Text08, 0, 1290 },
    { 61, 0, 1, 1, { 0, 0, 0 }, &gEvent158Text09, 0, 1320 },
    { 61, 3, 1, 1, { 0, 0, 0 }, &gEvent158Text10, 0, 1410 },
    { 61, 0, 4, 1, { 0, 0, 0 }, &gEvent158Text11, 0, 1414 },
    { 26, 0, 3, 1, { 0, 0, 0 }, &gEvent158Text12, 0, 1450 },
    { 61, 0, 1, 1, { 0, 0, 0 }, &gEvent158Text13, 0, 1480 },
    { 61, 0, 4, 1, { 0, 0, 0 }, &gEvent158Text14, 0, 1482 },
    { 61, 0, 4, 1, { 0, 0, 0 }, &gEvent158Text15, 0, 1484 },
    { 26, 0, 3, 1, { 0, 0, 0 }, &gEvent158Text16, 0, 1675 },
    { 61, 3, 1, 1, { 0, 0, 0 }, &gEvent158Text17, 0, 1700 },
    { 26, 3, 3, 1, { 0, 0, 0 }, &gEvent158Text18, 0, 1890 },
    { 61, 1, 1, 1, { 0, 0, 0 }, &gEvent158Text19, 0, 1920 },
    { 26, 4, 3, 1, { 0, 0, 0 }, &gEvent158Text20, MSG_SCRIPT_FLAG_END, 1950 },
};
#endif

static const EvSoundCue sEvent158SoundCues[8] = {
    { SONG_BGM_T13THFLOOR, 0, 0, 0 },
    { SONG_BGM_T13THFLOOR, 360, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT_UNREST, 611, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT_UNREST, 900, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_EV_FLASH01, 1010, 0, 0 },
    { SONG_EV_FLASH01, 1040, 0, 0 },
    { SONG_EV_FLASH01, 1060, 0, 0 },
    { SONG_EV_WHITEOUT, 1110, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent158Camera[12] = {
    { -64676, 171520, 68352, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64526, 178176, 66560, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -64496, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_HALF_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -64476, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 20, { 0, 0 }, NULL },
    { -64466, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_HALF_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -64426, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64376, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 50, { 0, 0 }, NULL },
    { -64371, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64321, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 50, { 0, 0 }, NULL },
    { -64186, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -63536, 173824, 68608, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent158Track0[31] = {
    { 515, 1, { 0, 0 }, 137216, 93696, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 518, 150, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 515, 210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 514, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 530, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 530, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 530, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 532, 520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 532, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 532, 580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 630, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 540, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 540, 810, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 540, 860, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 975, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 532, 982, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 1495, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 1625, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 515, 1650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 540, 1670, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 1770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 536, 1790, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 536, 1840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 536, 1860, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 558, 1925, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent158Track1[10] = {
    { 745, 1161, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 745, 1350, { 0, 0 }, 185088, 70656, 0, 0, { 0, 0 }, 1048834, NULL, NULL },
    { 747, 1380, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 1048836, NULL, NULL },
    { 745, 1405, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 1048837, NULL, NULL },
    { 751, 1412, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 1048837, NULL, NULL },
    { 745, 1720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 1048837, NULL, NULL },
    { 750, 1890, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 1048837, NULL, NULL },
    { 745, 1980, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 1048837, NULL, NULL },
    { 745, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 524544, EventCharaFadeOut, NULL },
    { 745, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent158Track2[5] = {
    { 920, 860, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8274, NULL, NULL },
    { 920, 861, { 0, 0 }, 185856, 44800, 0, 0, { 0, 0 }, 16722, NULL, NULL },
    { 920, 950, { 0, 0 }, 185856, 61952, 0, 920, { 0, 0 }, 339, NULL, NULL },
    { 920, 1120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 469, NULL, NULL },
    { 920, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98370, NULL, NULL },
};

static const EventCharaTrack sEvent158Tracks[3] = {
    { sEvent158Track0, 44, { 0, 0, 0 } },
    { sEvent158Track1, 69, { 0, 0, 0 } },
    { sEvent158Track2, 87, { 0, 0, 0 } },
};

const EventSequenceDef gEvent158 = {
    3,
    { 0, 0, 0 },
    sEvent158Tracks,
    sEvent158Camera,
    sEvent158Script,
    sEvent158SoundCues,
    NULL,
    2060,
    1,
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

#ifdef VERSION_US
#include "event_159_text.inc"
static const MessageScriptEntry sEvent159Script[17] = {
    { 55, 0, 1, 1, { 0, 0, 0 }, gEvent159Text00, 0, 100 },
    { 38, 3, 3, 1, { 0, 0, 0 }, gEvent159Text01, 0, 130 },
    { 38, 0, 4, 1, { 0, 0, 0 }, gEvent159Text02, 0, 134 },
    { 55, 0, 1, 1, { 0, 0, 0 }, gEvent159Text03, 0, 160 },
    { 38, 0, 3, 1, { 0, 0, 0 }, gEvent159Text04, 0, 190 },
    { 38, 0, 4, 1, { 0, 0, 0 }, gEvent159Text05, 0, 192 },
    { 38, 1, 4, 1, { 0, 0, 0 }, gEvent159Text06, 0, 194 },
    { 55, 0, 1, 1, { 0, 0, 0 }, gEvent159Text07, 0, 225 },
    { 38, 1, 3, 1, { 0, 0, 0 }, gEvent159Text08, 0, 255 },
    { 38, 0, 4, 1, { 0, 0, 0 }, gEvent159Text09, 0, 257 },
    { 55, 0, 1, 1, { 0, 0, 0 }, gEvent159Text10, 0, 290 },
    { 38, 0, 3, 1, { 0, 0, 0 }, gEvent159Text11, 0, 320 },
    { 38, 0, 4, 1, { 0, 0, 0 }, gEvent159Text12, 0, 322 },
    { 55, 0, 1, 1, { 0, 0, 0 }, gEvent159Text13, 0, 360 },
    { 38, 0, 3, 1, { 0, 0, 0 }, gEvent159Text14, 0, 390 },
    { 38, 0, 4, 1, { 0, 0, 0 }, gEvent159Text15, 0, 394 },
    { 38, 1, 4, 1, { 0, 0, 0 }, gEvent159Text16, MSG_SCRIPT_FLAG_END, 396 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent159Script[17] = {
    { 55, 0, 1, 3, { 0, 0, 0 }, gEvent159Text00, 0, 100 },
    { 38, 3, 3, 3, { 0, 0, 0 }, gEvent159Text01, 0, 130 },
    { 38, 0, 4, 3, { 0, 0, 0 }, gEvent159Text02, 0, 134 },
    { 55, 0, 1, 3, { 0, 0, 0 }, gEvent159Text03, 0, 160 },
    { 38, 0, 3, 3, { 0, 0, 0 }, gEvent159Text04, 0, 190 },
    { 38, 0, 4, 3, { 0, 0, 0 }, gEvent159Text05, 0, 192 },
    { 38, 1, 4, 3, { 0, 0, 0 }, gEvent159Text06, 0, 194 },
    { 55, 0, 1, 3, { 0, 0, 0 }, gEvent159Text07, 0, 225 },
    { 38, 1, 3, 3, { 0, 0, 0 }, gEvent159Text08, 0, 255 },
    { 38, 0, 4, 3, { 0, 0, 0 }, gEvent159Text09, 0, 257 },
    { 55, 0, 1, 3, { 0, 0, 0 }, gEvent159Text10, 0, 290 },
    { 38, 0, 3, 3, { 0, 0, 0 }, gEvent159Text11, 0, 320 },
    { 38, 0, 4, 3, { 0, 0, 0 }, gEvent159Text12, 0, 322 },
    { 55, 0, 1, 3, { 0, 0, 0 }, gEvent159Text13, 0, 360 },
    { 38, 0, 3, 3, { 0, 0, 0 }, gEvent159Text14, 0, 390 },
    { 38, 0, 4, 3, { 0, 0, 0 }, gEvent159Text15, 0, 394 },
    { 38, 1, 4, 3, { 0, 0, 0 }, gEvent159Text16, MSG_SCRIPT_FLAG_END, 396 },
};

#include "event_159_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent159Script[17] = {
    { 55, 0, 1, 1, { 0, 0, 0 }, &gEvent159Text00, 0, 100 },
    { 38, 3, 3, 1, { 0, 0, 0 }, &gEvent159Text01, 0, 130 },
    { 38, 0, 4, 1, { 0, 0, 0 }, &gEvent159Text02, 0, 134 },
    { 55, 0, 1, 1, { 0, 0, 0 }, &gEvent159Text03, 0, 160 },
    { 38, 0, 3, 1, { 0, 0, 0 }, &gEvent159Text04, 0, 190 },
    { 38, 0, 4, 1, { 0, 0, 0 }, &gEvent159Text05, 0, 192 },
    { 38, 1, 4, 1, { 0, 0, 0 }, &gEvent159Text06, 0, 194 },
    { 55, 0, 1, 1, { 0, 0, 0 }, &gEvent159Text07, 0, 225 },
    { 38, 1, 3, 1, { 0, 0, 0 }, &gEvent159Text08, 0, 255 },
    { 38, 0, 4, 1, { 0, 0, 0 }, &gEvent159Text09, 0, 257 },
    { 55, 0, 1, 1, { 0, 0, 0 }, &gEvent159Text10, 0, 290 },
    { 38, 0, 3, 1, { 0, 0, 0 }, &gEvent159Text11, 0, 320 },
    { 38, 0, 4, 1, { 0, 0, 0 }, &gEvent159Text12, 0, 322 },
    { 55, 0, 1, 1, { 0, 0, 0 }, &gEvent159Text13, 0, 360 },
    { 38, 0, 3, 1, { 0, 0, 0 }, &gEvent159Text14, 0, 390 },
    { 38, 0, 4, 1, { 0, 0, 0 }, &gEvent159Text15, 0, 394 },
    { 38, 1, 4, 1, { 0, 0, 0 }, &gEvent159Text16, MSG_SCRIPT_FLAG_END, 396 },
};
#endif

static const EventCameraKeyframe sEvent159Camera[1] = {
    { -64537, 68352, 58368, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent159SoundCues[2] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_BGM_EVENT_XIII, 451, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent159Track0[2] = {
    { 889, 100, { 0, 0 }, 78080, 63488, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 889, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent159Track1[4] = {
    { 721, 132, { 0, 0 }, 57856, 66560, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 727, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 729, 392, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 727, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent159Tracks[2] = {
    { sEvent159Track0, 83, { 0, 0, 0 } },
    { sEvent159Track1, 67, { 0, 0, 0 } },
};

const EventSequenceDef gEvent159 = {
    2,
    { 0, 0, 0 },
    sEvent159Tracks,
    sEvent159Camera,
    sEvent159Script,
    sEvent159SoundCues,
    NULL,
    456,
    1,
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

#ifdef VERSION_US
#include "event_160_text.inc"
static const MessageScriptEntry sEvent160Script[13] = {
    { 38, 0, 1, 1, { 0, 0, 0 }, gEvent160Text00, 0, 250 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent160Text01, 0, 280 },
    { 38, 0, 1, 1, { 0, 0, 0 }, gEvent160Text02, 0, 460 },
    { 38, 0, 4, 1, { 0, 0, 0 }, gEvent160Text03, 0, 462 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent160Text04, 0, 490 },
    { 38, 0, 1, 1, { 0, 0, 0 }, gEvent160Text05, 0, 520 },
    { 38, 1, 1, 1, { 0, 0, 0 }, gEvent160Text06, 0, 660 },
    { 38, 0, 4, 1, { 0, 0, 0 }, gEvent160Text07, 0, 662 },
    { 26, 5, 3, 1, { 0, 0, 0 }, gEvent160Text08, 0, 710 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent160Text09, 0, 790 },
    { 26, 2, 4, 1, { 0, 0, 0 }, gEvent160Text10, 0, 792 },
    { 26, 2, 4, 1, { 0, 0, 0 }, gEvent160Text11, 0, 794 },
    { 38, 1, 1, 1, { 0, 0, 0 }, gEvent160Text12, MSG_SCRIPT_FLAG_END, 822 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent160Script[13] = {
    { 38, 0, 1, 3, { 0, 0, 0 }, gEvent160Text00, 0, 250 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent160Text01, 0, 280 },
    { 38, 0, 1, 3, { 0, 0, 0 }, gEvent160Text02, 0, 460 },
    { 38, 0, 4, 3, { 0, 0, 0 }, gEvent160Text03, 0, 462 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent160Text04, 0, 490 },
    { 38, 0, 1, 3, { 0, 0, 0 }, gEvent160Text05, 0, 520 },
    { 38, 1, 1, 3, { 0, 0, 0 }, gEvent160Text06, 0, 660 },
    { 38, 0, 4, 3, { 0, 0, 0 }, gEvent160Text07, 0, 662 },
    { 26, 5, 3, 3, { 0, 0, 0 }, gEvent137Text08, 0, 710 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent160Text09, 0, 790 },
    { 26, 2, 4, 3, { 0, 0, 0 }, gEvent160Text10, 0, 792 },
    { 26, 2, 4, 3, { 0, 0, 0 }, gEvent160Text11, 0, 794 },
    { 38, 1, 1, 3, { 0, 0, 0 }, gEvent160Text12, MSG_SCRIPT_FLAG_END, 822 },
};

#include "event_160_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent160Script[13] = {
    { 38, 0, 1, 1, { 0, 0, 0 }, &gEvent160Text00, 0, 250 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent160Text01, 0, 280 },
    { 38, 0, 1, 1, { 0, 0, 0 }, &gEvent160Text02, 0, 460 },
    { 38, 0, 4, 1, { 0, 0, 0 }, &gEvent160Text03, 0, 462 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent160Text04, 0, 490 },
    { 38, 0, 1, 1, { 0, 0, 0 }, &gEvent160Text05, 0, 520 },
    { 38, 1, 1, 1, { 0, 0, 0 }, &gEvent160Text06, 0, 660 },
    { 38, 0, 4, 1, { 0, 0, 0 }, &gEvent160Text07, 0, 662 },
    { 26, 5, 3, 1, { 0, 0, 0 }, &gEvent160Text08, 0, 710 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent160Text09, 0, 790 },
    { 26, 2, 4, 1, { 0, 0, 0 }, &gEvent160Text10, 0, 792 },
    { 26, 2, 4, 1, { 0, 0, 0 }, &gEvent160Text11, 0, 794 },
    { 38, 1, 1, 1, { 0, 0, 0 }, &gEvent160Text12, MSG_SCRIPT_FLAG_END, 822 },
};
#endif

static const EvSoundCue sEvent160SoundCues[7] = {
    { 65535, 0, 0, 0 },
    { SONG_EV_WARPOUT, 130, 0, 0 },
    { SONG_BGM_EVENT_XIII, 160, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_SND_359, 260, 0, 0 },
    { SONG_SND_359, 750, 0, 0 },
    { SONG_BGM_EVENT_XIII, 705, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT2, 755, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent160Camera[1] = {
    { -64537, 188160, 61184, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent160Track0[13] = {
    { 515, 1, { 0, 0 }, 151552, 86784, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 518, 130, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 515, 140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 532, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 532, 210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 532, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 560, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 534, 590, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 534, 640, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 534, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 563, 750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 560, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent160Track1[4] = {
    { 721, 130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 721, 300, { 0, 0 }, 198144, 64000, 0, 0, { 0, 0 }, 2, EventCharaFadeIn, NULL },
    { 721, 430, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 721, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent160Tracks[2] = {
    { sEvent160Track0, 44, { 0, 0, 0 } },
    { sEvent160Track1, 67, { 0, 0, 0 } },
};

const EventSequenceDef gEvent160 = {
    2,
    { 0, 0, 0 },
    sEvent160Tracks,
    sEvent160Camera,
    sEvent160Script,
    sEvent160SoundCues,
    NULL,
    880,
    0,
    1,
    0,
    0,
    0,
    0,
    176,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_161_text.inc"
static const MessageScriptEntry sEvent161Script[5] = {
    { 38, 1, 1, 1, { 0, 0, 0 }, gEvent161Text00, 0, 100 },
    { 38, 0, 4, 1, { 0, 0, 0 }, gEvent161Text01, 0, 102 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent161Text02, 0, 200 },
    { 38, 0, 1, 1, { 0, 0, 0 }, gEvent161Text03, 0, 230 },
    { 38, 1, 4, 1, { 0, 0, 0 }, gEvent161Text04, MSG_SCRIPT_FLAG_END, 232 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent161Script[5] = {
    { 38, 1, 1, 3, { 0, 0, 0 }, gEvent161Text00, 0, 100 },
    { 38, 0, 4, 3, { 0, 0, 0 }, gEvent161Text01, 0, 102 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent161Text02, 0, 200 },
    { 38, 0, 1, 3, { 0, 0, 0 }, gEvent161Text03, 0, 230 },
    { 38, 1, 4, 3, { 0, 0, 0 }, gEvent161Text04, MSG_SCRIPT_FLAG_END, 232 },
};

#include "event_161_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent161Script[5] = {
    { 38, 1, 1, 1, { 0, 0, 0 }, &gEvent161Text00, 0, 100 },
    { 38, 0, 4, 1, { 0, 0, 0 }, &gEvent161Text01, 0, 102 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent161Text02, 0, 200 },
    { 38, 0, 1, 1, { 0, 0, 0 }, &gEvent161Text03, 0, 230 },
    { 38, 1, 4, 1, { 0, 0, 0 }, &gEvent161Text04, MSG_SCRIPT_FLAG_END, 232 },
};
#endif

static const EvSoundCue sEvent161SoundCues[2] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_EV_WARPIN, 260, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent161Camera[1] = {
    { -64537, 188160, 61184, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent161Track0[4] = {
    { 561, 120, { 0, 0 }, 179200, 72448, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 561, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 562, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 563, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent161Track1[4] = {
    { 721, 260, { 0, 0 }, 198144, 64000, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 721, 300, { 0, 0 }, 198144, 64000, 0, 0, { 0, 0 }, 2, EventCharaFadeOut, NULL },
    { 721, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 721, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent161Tracks[2] = {
    { sEvent161Track0, 44, { 0, 0, 0 } },
    { sEvent161Track1, 67, { 0, 0, 0 } },
};

const EventSequenceDef gEvent161 = {
    2,
    { 0, 0, 0 },
    sEvent161Tracks,
    sEvent161Camera,
    sEvent161Script,
    sEvent161SoundCues,
    NULL,
    340,
    1,
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

#ifdef VERSION_US
#include "event_162_text.inc"
static const MessageScriptEntry sEvent162Script[10] = {
    { 57, 0, 3, 1, { 0, 0, 0 }, gEvent162Text00, 0, 130 },
    { 55, 0, 0, 1, { 0, 0, 0 }, gEvent162Text01, 0, 220 },
    { 57, 0, 3, 1, { 0, 0, 0 }, gEvent162Text02, 0, 250 },
    { 55, 0, 0, 1, { 0, 0, 0 }, gEvent162Text03, 0, 280 },
    { 55, 0, 4, 1, { 0, 0, 0 }, gEvent162Text04, 0, 282 },
    { 55, 0, 4, 1, { 0, 0, 0 }, gEvent162Text05, 0, 284 },
    { 57, 0, 3, 1, { 0, 0, 0 }, gEvent162Text06, 0, 315 },
    { 55, 0, 0, 1, { 0, 0, 0 }, gEvent162Text07, 0, 345 },
    { 57, 0, 3, 1, { 0, 0, 0 }, gEvent162Text08, 0, 375 },
    { 55, 1, 0, 1, { 0, 0, 0 }, gEvent162Text09, MSG_SCRIPT_FLAG_END, 410 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent162Script[10] = {
    { 57, 0, 3, 3, { 0, 0, 0 }, gEvent162Text00, 0, 130 },
    { 55, 0, 0, 3, { 0, 0, 0 }, gEvent162Text01, 0, 220 },
    { 57, 0, 3, 3, { 0, 0, 0 }, gEvent162Text02, 0, 250 },
    { 55, 0, 0, 3, { 0, 0, 0 }, gEvent162Text03, 0, 280 },
    { 55, 0, 4, 3, { 0, 0, 0 }, gEvent162Text04, 0, 282 },
    { 55, 0, 4, 3, { 0, 0, 0 }, gEvent162Text05, 0, 284 },
    { 57, 0, 3, 3, { 0, 0, 0 }, gEvent162Text06, 0, 315 },
    { 55, 0, 0, 3, { 0, 0, 0 }, gEvent162Text07, 0, 345 },
    { 57, 0, 3, 3, { 0, 0, 0 }, gEvent162Text08, 0, 375 },
    { 55, 1, 0, 3, { 0, 0, 0 }, gEvent162Text09, MSG_SCRIPT_FLAG_END, 410 },
};

#include "event_162_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent162Script[10] = {
    { 57, 0, 3, 1, { 0, 0, 0 }, &gEvent162Text00, 0, 130 },
    { 55, 0, 0, 1, { 0, 0, 0 }, &gEvent162Text01, 0, 220 },
    { 57, 0, 3, 1, { 0, 0, 0 }, &gEvent162Text02, 0, 250 },
    { 55, 0, 0, 1, { 0, 0, 0 }, &gEvent162Text03, 0, 280 },
    { 55, 0, 4, 1, { 0, 0, 0 }, &gEvent162Text04, 0, 282 },
    { 55, 0, 4, 1, { 0, 0, 0 }, &gEvent162Text05, 0, 284 },
    { 57, 0, 3, 1, { 0, 0, 0 }, &gEvent162Text06, 0, 315 },
    { 55, 0, 0, 1, { 0, 0, 0 }, &gEvent162Text07, 0, 345 },
    { 57, 0, 3, 1, { 0, 0, 0 }, &gEvent162Text08, 0, 375 },
    { 55, 1, 0, 1, { 0, 0, 0 }, &gEvent162Text09, MSG_SCRIPT_FLAG_END, 410 },
};
#endif

static const EvSoundCue sEvent162SoundCues[2] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_BGM_EVENT_XIII, 455, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent162Camera[1] = {
    { -65116, 83456, 64256, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent162Track0[6] = {
    { 883, 3, { 0, 0 }, 46848, 58624, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 885, 100, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 883, 310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 887, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 883, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 883, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent162Track1[6] = {
    { 889, 160, { 0, 0 }, 97024, 77056, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 889, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 889, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 902, 190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 902, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 902, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent162Tracks[2] = {
    { sEvent162Track0, 82, { 0, 0, 0 } },
    { sEvent162Track1, 83, { 0, 0, 0 } },
};

const EventSequenceDef gEvent162 = {
    2,
    { 0, 0, 0 },
    sEvent162Tracks,
    sEvent162Camera,
    sEvent162Script,
    sEvent162SoundCues,
    NULL,
    460,
    1,
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

#ifdef VERSION_US
#include "event_163_text.inc"
static const MessageScriptEntry sEvent163Script[16] = {
    { 26, 3, 3, 1, { 0, 0, 0 }, gEvent163Text00, 0, 250 },
    { 26, 3, 3, 1, { 0, 0, 0 }, gEvent163Text01, 0, 300 },
    { 27, 0, 1, 1, { 0, 0, 0 }, gEvent163Text02, MSG_SCRIPT_FLAG_SILHOUETTE, 330 },
    { 27, 1, 1, 1, { 0, 0, 0 }, gEvent163Text03, 0, 490 },
    { 27, 1, 1, 1, { 0, 0, 0 }, gEvent163Text04, 0, 570 },
    { 27, 0, 4, 1, { 0, 0, 0 }, gEvent163Text05, 0, 572 },
    { 26, 0, 3, 1, { 0, 0, 0 }, gEvent163Text06, 0, 610 },
    { 27, 2, 1, 1, { 0, 0, 0 }, gEvent163Text07, 0, 640 },
    { 27, 2, 4, 1, { 0, 0, 0 }, gEvent163Text08, 0, 642 },
    { 27, 2, 4, 1, { 0, 0, 0 }, gEvent163Text09, 0, 644 },
    { 27, 0, 1, 1, { 0, 0, 0 }, gEvent163Text10, 0, 700 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent163Text11, 0, 805 },
    { 27, 1, 1, 1, { 0, 0, 0 }, gEvent163Text12, 0, 840 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent163Text13, 0, 870 },
    { 27, 1, 1, 1, { 0, 0, 0 }, gEvent163Text14, 0, 900 },
    { 27, 2, 1, 1, { 0, 0, 0 }, gEvent163Text15, MSG_SCRIPT_FLAG_END, 940 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent163Script[16] = {
    { 26, 3, 3, 3, { 0, 0, 0 }, gEvent163Text00, 0, 250 },
    { 26, 3, 3, 3, { 0, 0, 0 }, gEvent163Text01, 0, 300 },
    { 27, 0, 1, 3, { 0, 0, 0 }, gEvent163Text02, MSG_SCRIPT_FLAG_SILHOUETTE, 330 },
    { 27, 1, 1, 3, { 0, 0, 0 }, gEvent163Text03, 0, 490 },
    { 27, 1, 1, 3, { 0, 0, 0 }, gEvent163Text04, 0, 570 },
    { 27, 0, 4, 3, { 0, 0, 0 }, gEvent163Text05, 0, 572 },
    { 26, 0, 3, 3, { 0, 0, 0 }, gEvent163Text06, 0, 610 },
    { 27, 2, 1, 3, { 0, 0, 0 }, gEvent163Text07, 0, 640 },
    { 27, 2, 4, 3, { 0, 0, 0 }, gEvent163Text08, 0, 642 },
    { 27, 2, 4, 3, { 0, 0, 0 }, gEvent163Text09, 0, 644 },
    { 27, 0, 1, 3, { 0, 0, 0 }, gEvent163Text10, 0, 700 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent163Text11, 0, 805 },
    { 27, 1, 1, 3, { 0, 0, 0 }, gEvent163Text12, 0, 840 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent163Text13, 0, 870 },
    { 27, 1, 1, 3, { 0, 0, 0 }, gEvent163Text14, 0, 900 },
    { 27, 2, 1, 3, { 0, 0, 0 }, gEvent163Text15, MSG_SCRIPT_FLAG_END, 940 },
};

#include "event_163_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent163Script[16] = {
    { 26, 3, 3, 1, { 0, 0, 0 }, &gEvent163Text00, 0, 250 },
    { 26, 3, 3, 1, { 0, 0, 0 }, &gEvent163Text01, 0, 300 },
    { 27, 0, 1, 1, { 0, 0, 0 }, &gEvent163Text02, MSG_SCRIPT_FLAG_SILHOUETTE, 330 },
    { 27, 1, 1, 1, { 0, 0, 0 }, &gEvent163Text03, 0, 490 },
    { 27, 1, 1, 1, { 0, 0, 0 }, &gEvent163Text04, 0, 570 },
    { 27, 0, 4, 1, { 0, 0, 0 }, &gEvent163Text05, 0, 572 },
    { 26, 0, 3, 1, { 0, 0, 0 }, &gEvent163Text06, 0, 610 },
    { 27, 2, 1, 1, { 0, 0, 0 }, &gEvent163Text07, 0, 640 },
    { 27, 2, 4, 1, { 0, 0, 0 }, &gEvent163Text08, 0, 642 },
    { 27, 2, 4, 1, { 0, 0, 0 }, &gEvent163Text09, 0, 644 },
    { 27, 0, 1, 1, { 0, 0, 0 }, &gEvent163Text10, 0, 700 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent163Text11, 0, 805 },
    { 27, 1, 1, 1, { 0, 0, 0 }, &gEvent163Text12, 0, 840 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent163Text13, 0, 870 },
    { 27, 1, 1, 1, { 0, 0, 0 }, &gEvent163Text14, 0, 900 },
    { 27, 2, 1, 1, { 0, 0, 0 }, &gEvent163Text15, MSG_SCRIPT_FLAG_END, 940 },
};
#endif

static const EvSoundCue sEvent163SoundCues[5] = {
    { 65535, 0, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 390, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT_UNREST, 895, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT2, 905, 0, 0 },
    { SONG_SND_359, 910, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent163Camera[4] = {
    { -65535, 145920, 82944, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65205, 0, 0, -7168, 44, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64536, 177152, 69120, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent163Track0[14] = {
    { 515, 1, { 0, 0 }, 145920, 90112, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 518, 120, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 515, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 532, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 532, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 532, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 715, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 532, 725, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 532, 775, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 532, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 538, 810, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent163Track1[8] = {
    { 695, 332, { 0, 0 }, 212224, 58368, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 711, 450, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 695, 635, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 706, 643, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 695, 695, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 717, 710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 695, 910, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 698, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent163Tracks[2] = {
    { sEvent163Track0, 44, { 0, 0, 0 } },
    { sEvent163Track1, 65, { 0, 0, 0 } },
};

const EventSequenceDef gEvent163 = {
    2,
    { 0, 0, 0 },
    sEvent163Tracks,
    sEvent163Camera,
    sEvent163Script,
    sEvent163SoundCues,
    NULL,
    1000,
    0,
    1,
    0,
    0,
    0,
    0,
    171,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_164_text.inc"
static const MessageScriptEntry sEvent164Script[11] = {
    { 26, 1, 3, 1, { 0, 0, 0 }, gEvent164Text00, 0, 100 },
    { 27, 2, 1, 1, { 0, 0, 0 }, gEvent164Text01, 0, 130 },
    { 27, 1, 4, 1, { 0, 0, 0 }, gEvent164Text02, 0, 132 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent164Text03, 0, 160 },
    { 27, 1, 1, 1, { 0, 0, 0 }, gEvent164Text04, 0, 235 },
    { 27, 1, 1, 1, { 0, 0, 0 }, gEvent164Text05, 0, 405 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent164Text06, 0, 430 },
    { 27, 1, 1, 1, { 0, 0, 0 }, gEvent164Text07, 0, 460 },
    { 27, 1, 4, 1, { 0, 0, 0 }, gEvent164Text08, 0, 462 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent164Text09, 0, 565 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent164Text10, MSG_SCRIPT_FLAG_END, 700 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent164Script[11] = {
    { 26, 1, 3, 3, { 0, 0, 0 }, gEvent164Text00, 0, 100 },
    { 27, 2, 1, 3, { 0, 0, 0 }, gEvent164Text01, 0, 130 },
    { 27, 1, 4, 3, { 0, 0, 0 }, gEvent164Text02, 0, 132 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent164Text03, 0, 160 },
    { 27, 1, 1, 3, { 0, 0, 0 }, gEvent164Text04, 0, 235 },
    { 27, 1, 1, 3, { 0, 0, 0 }, gEvent164Text05, 0, 405 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent038Text04, 0, 430 },
    { 27, 1, 1, 3, { 0, 0, 0 }, gEvent164Text07, 0, 460 },
    { 27, 1, 4, 3, { 0, 0, 0 }, gEvent164Text08, 0, 462 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent124Text23, 0, 565 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent164Text10, MSG_SCRIPT_FLAG_END, 700 },
};

#include "event_164_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent164Script[11] = {
    { 26, 1, 3, 1, { 0, 0, 0 }, &gEvent164Text00, 0, 100 },
    { 27, 2, 1, 1, { 0, 0, 0 }, &gEvent164Text01, 0, 130 },
    { 27, 1, 4, 1, { 0, 0, 0 }, &gEvent164Text02, 0, 132 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent164Text03, 0, 160 },
    { 27, 1, 1, 1, { 0, 0, 0 }, &gEvent164Text04, 0, 235 },
    { 27, 1, 1, 1, { 0, 0, 0 }, &gEvent164Text05, 0, 405 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent164Text06, 0, 430 },
    { 27, 1, 1, 1, { 0, 0, 0 }, &gEvent164Text07, 0, 460 },
    { 27, 1, 4, 1, { 0, 0, 0 }, &gEvent164Text08, 0, 462 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent164Text09, 0, 565 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent164Text10, MSG_SCRIPT_FLAG_END, 700 },
};
#endif

static const EvSoundCue sEvent164SoundCues[3] = {
    { SONG_BGM_EVENT_UNREST, 0, 0, 0 },
    { SONG_SND_376, 165, 0, 0 },
    { SONG_SND_378, 194, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent164Camera[8] = {
    { -65371, 182784, 66560, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65356, 191232, 60160, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 20, { 0, 0 }, NULL },
    { -65346, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -65341, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65331, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -65286, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64946, 154112, 80896, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 100, { 0, 0 }, NULL },
    { -62536, 166656, 75520, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent164Track0[14] = {
    { 561, 165, { 0, 0 }, 171264, 76288, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 548, 191, { 0, 0 }, 188160, 69632, 0, 515, { 0, 0 }, 67, NULL, NULL },
    { 515, 194, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 550, 230, { 0, 0 }, 146176, 89856, 0, 515, { 0, 0 }, 67, NULL, NULL },
    { 555, 385, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 556, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 425, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 538, 435, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 538, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 590, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 522, 645, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 515, 649, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 515, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent164Track1[8] = {
    { 705, 191, { 0, 0 }, 194048, 66304, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 695, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 711, 385, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 695, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 696, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 696, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 710, 1000, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 695, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent164Track2[3] = {
    { 926, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 926, 250, { 0, 0 }, 194048, 60160, 0, 0, { 0, 0 }, 16658, NULL, NULL },
    { 926, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaTrack sEvent164Tracks[3] = {
    { sEvent164Track0, 44, { 0, 0, 0 } },
    { sEvent164Track1, 65, { 0, 0, 0 } },
    { sEvent164Track2, 92, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent164 = {
    3,
    { 0, 0, 0 },
    sEvent164Tracks,
    sEvent164Camera,
    sEvent164Script,
    sEvent164SoundCues,
    NULL,
    760,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    165,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent164 = {
    3,
    { 0, 0, 0 },
    sEvent164Tracks,
    sEvent164Camera,
    sEvent164Script,
    sEvent164SoundCues,
    NULL,
    760,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    163,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_165_text.inc"
static const MessageScriptEntry sEvent165Script[6] = {
    { 38, 0, 1, 1, { 0, 0, 0 }, gEvent165Text00, 0, 160 },
    { 27, 1, 3, 1, { 0, 0, 0 }, gEvent165Text01, 0, 190 },
    { 38, 0, 1, 1, { 0, 0, 0 }, gEvent165Text02, 0, 360 },
    { 27, 0, 3, 1, { 0, 0, 0 }, gEvent165Text03, 0, 390 },
    { 38, 0, 1, 1, { 0, 0, 0 }, gEvent165Text04, 0, 420 },
    { 27, 1, 3, 1, { 0, 0, 0 }, gEvent165Text05, MSG_SCRIPT_FLAG_END, 450 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent165Script[6] = {
    { 38, 0, 1, 3, { 0, 0, 0 }, gEvent165Text00, 0, 160 },
    { 27, 1, 3, 3, { 0, 0, 0 }, gEvent165Text01, 0, 190 },
    { 38, 0, 1, 3, { 0, 0, 0 }, gEvent165Text02, 0, 360 },
    { 27, 0, 3, 3, { 0, 0, 0 }, gEvent165Text03, 0, 390 },
    { 38, 0, 1, 3, { 0, 0, 0 }, gEvent165Text04, 0, 420 },
    { 27, 1, 3, 3, { 0, 0, 0 }, gEvent165Text05, MSG_SCRIPT_FLAG_END, 450 },
};

#include "event_165_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent165Script[6] = {
    { 38, 0, 1, 1, { 0, 0, 0 }, &gEvent165Text00, 0, 160 },
    { 27, 1, 3, 1, { 0, 0, 0 }, &gEvent165Text01, 0, 190 },
    { 38, 0, 1, 1, { 0, 0, 0 }, &gEvent165Text02, 0, 360 },
    { 27, 0, 3, 1, { 0, 0, 0 }, &gEvent165Text03, 0, 390 },
    { 38, 0, 1, 1, { 0, 0, 0 }, &gEvent165Text04, 0, 420 },
    { 27, 1, 3, 1, { 0, 0, 0 }, &gEvent165Text05, MSG_SCRIPT_FLAG_END, 450 },
};
#endif

static const EvSoundCue sEvent165SoundCues[2] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_BGM_EVENT_XIII, 505, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent165Camera[1] = {
    { -64537, 68608, 51712, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent165Track0[3] = {
    { 696, 1, { 0, 0 }, 31744, 77312, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 712, 130, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 696, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent165Track1[5] = {
    { 721, 110, { 0, 0 }, 78080, 56576, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 721, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 721, 330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 721, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 721, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent165Tracks[2] = {
    { sEvent165Track0, 65, { 0, 0, 0 } },
    { sEvent165Track1, 67, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent165 = {
    2,
    { 0, 0, 0 },
    sEvent165Tracks,
    sEvent165Camera,
    sEvent165Script,
    sEvent165SoundCues,
    NULL,
    510,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    166,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent165 = {
    2,
    { 0, 0, 0 },
    sEvent165Tracks,
    sEvent165Camera,
    sEvent165Script,
    sEvent165SoundCues,
    NULL,
    510,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    164,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_166_text.inc"
static const MessageScriptEntry sEvent166Script[14] = {
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent166Text00, 0, 115 },
    { 56, 1, 0, 1, { 0, 0, 0 }, gEvent166Text01, 0, 330 },
    { 26, 2, 2, 1, { 0, 0, 0 }, gEvent166Text02, 0, 500 },
    { 56, 0, 1, 1, { 0, 0, 0 }, gEvent166Text03, 0, 530 },
    { 56, 0, 4, 1, { 0, 0, 0 }, gEvent166Text04, 0, 532 },
    { 56, 1, 4, 1, { 0, 0, 0 }, gEvent166Text05, 0, 534 },
    { 26, 2, 2, 1, { 0, 0, 0 }, gEvent166Text06, 0, 565 },
    { 56, 0, 1, 1, { 0, 0, 0 }, gEvent166Text07, 0, 595 },
    { 56, 1, 4, 1, { 0, 0, 0 }, gEvent166Text08, 0, 597 },
    { 26, 1, 2, 1, { 0, 0, 0 }, gEvent166Text09, 0, 770 },
    { 26, 0, 4, 1, { 0, 0, 0 }, gEvent166Text10, 0, 772 },
    { 26, 2, 4, 1, { 0, 0, 0 }, gEvent166Text11, 0, 785 },
    { 56, 1, 1, 1, { 0, 0, 0 }, gEvent166Text12, 0, 950 },
    { 56, 0, 1, 1, { 0, 0, 0 }, gEvent166Text13, MSG_SCRIPT_FLAG_END, 1100 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent166Script[14] = {
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent166Text00, 0, 115 },
    { 56, 1, 0, 3, { 0, 0, 0 }, gEvent166Text01, 0, 330 },
    { 26, 2, 2, 3, { 0, 0, 0 }, gEvent166Text02, 0, 500 },
    { 56, 0, 1, 3, { 0, 0, 0 }, gEvent166Text03, 0, 530 },
    { 56, 0, 4, 3, { 0, 0, 0 }, gEvent166Text04, 0, 532 },
    { 56, 1, 4, 3, { 0, 0, 0 }, gEvent166Text05, 0, 534 },
    { 26, 2, 2, 3, { 0, 0, 0 }, gEvent166Text06, 0, 565 },
    { 56, 0, 1, 3, { 0, 0, 0 }, gEvent166Text07, 0, 595 },
    { 56, 1, 4, 3, { 0, 0, 0 }, gEvent166Text08, 0, 597 },
    { 26, 1, 2, 3, { 0, 0, 0 }, gEvent166Text09, 0, 770 },
    { 26, 0, 4, 3, { 0, 0, 0 }, gEvent166Text10, 0, 772 },
    { 26, 2, 4, 3, { 0, 0, 0 }, gEvent166Text11, 0, 785 },
    { 56, 1, 1, 3, { 0, 0, 0 }, gEvent166Text12, 0, 950 },
    { 56, 0, 1, 3, { 0, 0, 0 }, gEvent166Text13, MSG_SCRIPT_FLAG_END, 1100 },
};

#include "event_166_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent166Script[14] = {
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent166Text00, 0, 115 },
    { 56, 1, 0, 1, { 0, 0, 0 }, &gEvent166Text01, 0, 330 },
    { 26, 2, 2, 1, { 0, 0, 0 }, &gEvent166Text02, 0, 500 },
    { 56, 0, 1, 1, { 0, 0, 0 }, &gEvent166Text03, 0, 530 },
    { 56, 0, 4, 1, { 0, 0, 0 }, &gEvent166Text04, 0, 532 },
    { 56, 1, 4, 1, { 0, 0, 0 }, &gEvent166Text05, 0, 534 },
    { 26, 2, 2, 1, { 0, 0, 0 }, &gEvent166Text06, 0, 565 },
    { 56, 0, 1, 1, { 0, 0, 0 }, &gEvent166Text07, 0, 595 },
    { 56, 1, 4, 1, { 0, 0, 0 }, &gEvent166Text08, 0, 597 },
    { 26, 1, 2, 1, { 0, 0, 0 }, &gEvent166Text09, 0, 770 },
    { 26, 0, 4, 1, { 0, 0, 0 }, &gEvent166Text10, 0, 772 },
    { 26, 2, 4, 1, { 0, 0, 0 }, &gEvent166Text11, 0, 785 },
    { 56, 1, 1, 1, { 0, 0, 0 }, &gEvent166Text12, 0, 950 },
    { 56, 0, 1, 1, { 0, 0, 0 }, &gEvent166Text13, MSG_SCRIPT_FLAG_END, 1100 },
};
#endif

static const EvSoundCue sEvent166SoundCues[5] = {
    { 65535, 0, 0, 0 },
    { SONG_SND_379, 410, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 411, 0, 0 },
    { SONG_EV_CARDTHR, 989, 0, 0 },
    { SONG_SND_379, 1150, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent166Camera[2] = {
    { -65146, 175872, 68352, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -62536, 188416, 61696, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent166Track0[24] = {
    { 515, 1, { 0, 0 }, 141568, 92672, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 522, 100, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 515, 103, { 0, 0 }, 175872, 75264, 0, 515, { 0, 0 }, 67, NULL, NULL },
    { 515, 110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 538, 120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 514, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 514, 340, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 514, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 538, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 610, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 530, 620, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 530, 750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 530, 773, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 538, 788, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 995, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 559, 1180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 4000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent166Track1[10] = {
    { 688, 410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 688, 450, { 0, 0 }, 201728, 63232, 0, 0, { 0, 0 }, 2, EventCharaFadeIn, NULL },
    { 688, 795, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 688, 925, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 688, 970, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 692, 1050, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 688, 1150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 688, 1200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaFadeOut, NULL },
    { 688, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 688, 4000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent166Track2[7] = {
    { 591, 988, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8258, NULL, NULL },
    { 591, 989, { 0, 0 }, 194816, 58624, 0, 0, { 0, 0 }, 16706, NULL, NULL },
    { 591, 1000, { 0, 0 }, 181504, 65536, 0, 591, { 0, 0 }, 323, NULL, NULL },
    { 591, 1008, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 604, 1180, { 0, 0 }, 175872, 75264, 0, 0, { 0, 0 }, 338, NULL, NULL },
    { 591, 1200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 591, 4000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98373, NULL, NULL },
};

static const EventCharaTrack sEvent166Tracks[3] = {
    { sEvent166Track0, 44, { 0, 0, 0 } },
    { sEvent166Track1, 64, { 0, 0, 0 } },
    { sEvent166Track2, 50, { 0, 0, 0 } },
};

const EventSequenceDef gEvent166 = {
    3,
    { 0, 0, 0 },
    sEvent166Tracks,
    sEvent166Camera,
    sEvent166Script,
    sEvent166SoundCues,
    NULL,
    1240,
    1,
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

#ifdef VERSION_US
#include "event_167_text.inc"
static const MessageScriptEntry sEvent167Script[32] = {
    { 20, 0, 3, 1, { 0, 0, 0 }, gEvent028Text07, 0, 100 },
    { 38, 0, 1, 1, { 0, 0, 0 }, gEvent028Text08, 0, 130 },
    { 38, 0, 4, 1, { 0, 0, 0 }, gEvent028Text09, 0, 132 },
    { 38, 1, 4, 1, { 0, 0, 0 }, gEvent028Text10, 0, 134 },
    { 54, 3, 1, 1, { 0, 0, 0 }, gEvent028Text11, 0, 160 },
    { 38, 1, 1, 1, { 0, 0, 0 }, gEvent028Text12, 0, 180 },
    { 20, 0, 3, 1, { 0, 0, 0 }, gEvent028Text13, 0, 220 },
    { 38, 1, 1, 1, { 0, 0, 0 }, gEvent028Text14, 0, 240 },
    { 54, 1, 1, 1, { 0, 0, 0 }, gEvent028Text15, 0, 260 },
    { 38, 0, 1, 1, { 0, 0, 0 }, gEvent028Text16, 0, 280 },
    { 20, 0, 3, 1, { 0, 0, 0 }, gEvent028Text17, 0, 430 },
    { 20, 1, 3, 1, { 0, 0, 0 }, gEvent028Text18, 0, 470 },
    { 38, 1, 1, 1, { 0, 0, 0 }, gEvent028Text19, 0, 490 },
    { 27, 0, 0, 1, { 0, 0, 0 }, gEvent167Text13, 0, 690 },
    { 20, 0, 3, 1, { 0, 0, 0 }, gEvent167Text14, 0, 720 },
    { 54, 0, 1, 1, { 0, 0, 0 }, gEvent167Text15, 0, 750 },
    { 54, 1, 4, 1, { 0, 0, 0 }, gEvent167Text16, 0, 752 },
    { 54, 2, 1, 1, { 0, 0, 0 }, gEvent167Text17, 0, 835 },
    { 27, 3, 0, 1, { 0, 0, 0 }, gEvent167Text18, 0, 920 },
    { 27, 2, 4, 1, { 0, 0, 0 }, gEvent167Text19, 0, 925 },
    { 54, 0, 1, 1, { 0, 0, 0 }, gEvent167Text20, 0, 950 },
    { 38, 0, 3, 1, { 0, 0, 0 }, gEvent167Text21, 0, 1130 },
    { 27, 2, 0, 1, { 0, 0, 0 }, gEvent167Text22, 0, 1150 },
    { 38, 0, 3, 1, { 0, 0, 0 }, gEvent167Text23, 0, 1180 },
    { 54, 2, 0, 1, { 0, 0, 0 }, gEvent167Text24, 0, 1270 },
    { 27, 2, 2, 1, { 0, 0, 0 }, gEvent167Text25, 0, 1420 },
    { 54, 1, 3, 1, { 0, 0, 0 }, gEvent167Text26, 0, 1635 },
    { 54, 1, 3, 1, { 0, 0, 0 }, gEvent167Text27, 0, 1670 },
    { 54, 1, 4, 1, { 0, 0, 0 }, gEvent167Text28, 0, 1672 },
    { 54, 2, 4, 1, { 0, 0, 0 }, gEvent167Text29, 0, 1674 },
    { 27, 3, 0, 1, { 0, 0, 0 }, gEvent167Text30, 0, 1710 },
    { 27, 3, 1, 1, { 0, 0, 0 }, gEvent167Text31, MSG_SCRIPT_FLAG_END, 2070 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent167Script[32] = {
    { 20, 0, 3, 3, { 0, 0, 0 }, gEvent028Text07, 0, 100 },
    { 38, 0, 1, 3, { 0, 0, 0 }, gEvent028Text08, 0, 130 },
    { 38, 0, 4, 3, { 0, 0, 0 }, gEvent028Text09, 0, 132 },
    { 38, 1, 4, 3, { 0, 0, 0 }, gEvent028Text10, 0, 134 },
    { 54, 3, 1, 3, { 0, 0, 0 }, gEvent028Text11, 0, 160 },
    { 38, 1, 1, 3, { 0, 0, 0 }, gEvent028Text12, 0, 180 },
    { 20, 0, 3, 3, { 0, 0, 0 }, gEvent028Text13, 0, 220 },
    { 38, 1, 1, 3, { 0, 0, 0 }, gEvent028Text14, 0, 240 },
    { 54, 1, 1, 3, { 0, 0, 0 }, gEvent028Text15, 0, 260 },
    { 38, 0, 1, 3, { 0, 0, 0 }, gEvent028Text16, 0, 280 },
    { 20, 0, 3, 3, { 0, 0, 0 }, gEvent028Text17, 0, 430 },
    { 20, 1, 3, 3, { 0, 0, 0 }, gEvent028Text18, 0, 470 },
    { 38, 1, 1, 3, { 0, 0, 0 }, gEvent028Text19, 0, 490 },
    { 27, 0, 0, 3, { 0, 0, 0 }, gEvent167Text13, 0, 690 },
    { 20, 0, 3, 3, { 0, 0, 0 }, gEvent167Text14, 0, 720 },
    { 54, 0, 1, 3, { 0, 0, 0 }, gEvent167Text15, 0, 750 },
    { 54, 1, 4, 3, { 0, 0, 0 }, gEvent167Text16, 0, 752 },
    { 54, 2, 1, 3, { 0, 0, 0 }, gEvent167Text17, 0, 835 },
    { 27, 3, 0, 3, { 0, 0, 0 }, gEvent167Text18, 0, 920 },
    { 27, 2, 4, 3, { 0, 0, 0 }, gEvent167Text19, 0, 925 },
    { 54, 0, 1, 3, { 0, 0, 0 }, gEvent167Text20, 0, 950 },
    { 38, 0, 3, 3, { 0, 0, 0 }, gEvent167Text21, 0, 1130 },
    { 27, 2, 0, 3, { 0, 0, 0 }, gEvent167Text22, 0, 1150 },
    { 38, 0, 3, 3, { 0, 0, 0 }, gEvent167Text23, 0, 1180 },
    { 54, 2, 0, 3, { 0, 0, 0 }, gEvent167Text24, 0, 1270 },
    { 27, 2, 2, 3, { 0, 0, 0 }, gEvent167Text25, 0, 1420 },
    { 54, 1, 3, 3, { 0, 0, 0 }, gEvent167Text26, 0, 1635 },
    { 54, 1, 3, 3, { 0, 0, 0 }, gEvent167Text27, 0, 1670 },
    { 54, 1, 4, 3, { 0, 0, 0 }, gEvent167Text28, 0, 1672 },
    { 54, 2, 4, 3, { 0, 0, 0 }, gEvent167Text29, 0, 1674 },
    { 27, 3, 0, 3, { 0, 0, 0 }, gEvent167Text30, 0, 1710 },
    { 27, 3, 1, 3, { 0, 0, 0 }, gEvent167Text31, MSG_SCRIPT_FLAG_END, 2070 },
};

#include "event_167_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent167Script[32] = {
    { 20, 0, 3, 1, { 0, 0, 0 }, &gEvent028Text07, 0, 100 },
    { 38, 0, 1, 1, { 0, 0, 0 }, &gEvent028Text08, 0, 130 },
    { 38, 0, 4, 1, { 0, 0, 0 }, &gEvent028Text09, 0, 132 },
    { 38, 1, 4, 1, { 0, 0, 0 }, &gEvent028Text10, 0, 134 },
    { 54, 3, 1, 1, { 0, 0, 0 }, &gEvent028Text11, 0, 160 },
    { 38, 1, 1, 1, { 0, 0, 0 }, &gEvent028Text12, 0, 180 },
    { 20, 0, 3, 1, { 0, 0, 0 }, &gEvent028Text13, 0, 220 },
    { 38, 1, 1, 1, { 0, 0, 0 }, &gEvent028Text14, 0, 240 },
    { 54, 1, 1, 1, { 0, 0, 0 }, &gEvent028Text15, 0, 260 },
    { 38, 0, 1, 1, { 0, 0, 0 }, &gEvent028Text16, 0, 280 },
    { 20, 0, 3, 1, { 0, 0, 0 }, &gEvent028Text17, 0, 430 },
    { 20, 1, 3, 1, { 0, 0, 0 }, &gEvent028Text18, 0, 470 },
    { 38, 1, 1, 1, { 0, 0, 0 }, &gEvent028Text19, 0, 490 },
    { 27, 0, 0, 1, { 0, 0, 0 }, &gEvent167Text13, 0, 690 },
    { 20, 0, 3, 1, { 0, 0, 0 }, &gEvent167Text14, 0, 720 },
    { 54, 0, 1, 1, { 0, 0, 0 }, &gEvent167Text15, 0, 750 },
    { 54, 1, 4, 1, { 0, 0, 0 }, &gEvent167Text16, 0, 752 },
    { 54, 2, 1, 1, { 0, 0, 0 }, &gEvent167Text17, 0, 835 },
    { 27, 3, 0, 1, { 0, 0, 0 }, &gEvent167Text18, 0, 920 },
    { 27, 2, 4, 1, { 0, 0, 0 }, &gEvent167Text19, 0, 925 },
    { 54, 0, 1, 1, { 0, 0, 0 }, &gEvent167Text20, 0, 950 },
    { 38, 0, 3, 1, { 0, 0, 0 }, &gEvent167Text21, 0, 1130 },
    { 27, 2, 0, 1, { 0, 0, 0 }, &gEvent167Text22, 0, 1150 },
    { 38, 0, 3, 1, { 0, 0, 0 }, &gEvent167Text23, 0, 1180 },
    { 54, 2, 0, 1, { 0, 0, 0 }, &gEvent167Text24, 0, 1270 },
    { 27, 2, 2, 1, { 0, 0, 0 }, &gEvent167Text25, 0, 1420 },
    { 54, 1, 3, 1, { 0, 0, 0 }, &gEvent167Text26, 0, 1635 },
    { 54, 1, 3, 1, { 0, 0, 0 }, &gEvent167Text27, 0, 1670 },
    { 54, 1, 4, 1, { 0, 0, 0 }, &gEvent167Text28, 0, 1672 },
    { 54, 2, 4, 1, { 0, 0, 0 }, &gEvent167Text29, 0, 1674 },
    { 27, 3, 0, 1, { 0, 0, 0 }, &gEvent167Text30, 0, 1710 },
    { 27, 3, 1, 1, { 0, 0, 0 }, &gEvent167Text31, MSG_SCRIPT_FLAG_END, 2070 },
};
#endif

static const EvSoundCue sEvent167SoundCues[5] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_EV_CARDTHR, 448, 0, 0 },
    { SONG_SND_359, 1430, 0, 0 },
    { SONG_EV_FLASH00, 1460, 0, 0 },
    { SONG_BGM_EVENT_XIII, 1750, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

#if defined(VERSION_US) || defined(VERSION_JP)
static const EventCameraKeyframe sEvent167Camera[7] = {
    { -65006, 60672, 55040, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64076, 65536, 58112, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 60, { 0, 0 }, NULL },
    { -64066, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -63986, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -63806, 99840, 67072, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 100, { 0, 0 }, NULL },
    { -61466, 99840, -12544, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 500, { 0, 0 }, NULL },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};
#elif defined(VERSION_EU)
static const EventCameraKeyframe sEvent167Camera[7] = {
    { -65006, 60672, 55040, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64076, 65536, 58112, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 60, { 0, 0 }, NULL },
    { -64066, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -63986, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -63806, 99840, 67072, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 100, { 0, 0 }, NULL },
    { -63266, 99840, -12544, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 500, { 0, 0 }, NULL },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};
#endif

static const EventBgEffectEntry sEvent167BgEffects[5] = {
    { 1770, 0, 0, 0, 0 },
    { 1850, 0, 0, 0, 0x14 },
    { 3380, 0, 0, 0, 0 },
    { 3450, 0, 0, 0, 0x2 },
    { 3500, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent167Track0[7] = {
    { 485, 215, { 0, 0 }, 51200, 55808, 0, 0, { 0, 0 }, 82, NULL, NULL },
    { 509, 225, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 85, NULL, NULL },
    { 509, 290, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 85, NULL, NULL },
    { 509, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 80, NULL, CreateBalloonTask },
    { 485, 431, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 85, NULL, NULL },
    { 500, 475, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 85, NULL, NULL },
    { 485, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32853, NULL, NULL },
};

static const EventCharaKeyframe sEvent167Track2[11] = {
    { 738, 110, { 0, 0 }, 62464, 70656, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 738, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 739, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 738, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 721, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 721, 970, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 727, 980, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 727, 1110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 727, 1160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 729, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 721, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent167Track1[14] = {
    { 856, 1300, { 0, 0 }, 74752, 61952, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 856, 1320, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 881, 1380, { 0, 0 }, 85760, 69120, 0, 856, { 0, 0 }, 67, NULL, NULL },
    { 856, 1390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 856, 1440, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 871, 1520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 856, 1570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 856, 1580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 881, 1620, { 0, 0 }, 93952, 71680, 0, 856, { 0, 0 }, 67, NULL, NULL },
    { 856, 1630, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 857, 1830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 856, 1850, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaFadeOut, NULL },
    { 856, 1870, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 856, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent167Track3[6] = {
    { 591, 447, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 591, 448, { 0, 0 }, 55296, 56320, -5120, 0, { 0, 0 }, 338, NULL, NULL },
    { 591, 459, { 0, 0 }, 57856, 63488, -5120, 591, { 0, 0 }, 323, NULL, NULL },
    { 591, 463, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 610, 480, { 0, 0 }, 63488, 70656, 0, 0, { 0, 0 }, 274, NULL, NULL },
    { 591, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98370, NULL, NULL },
};

static const EventCharaKeyframe sEvent167Track4[23] = {
    { 696, 540, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 696, 541, { 0, 0 }, 99072, 91648, 0, 0, { 0, 0 }, 16386, NULL, NULL },
    { 712, 660, { 0, 0 }, 72960, 74752, 0, 696, { 0, 0 }, 3, NULL, NULL },
    { 696, 765, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 696, 815, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateQuestionTask },
    { 696, 855, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 716, 905, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 716, 922, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 708, 930, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 696, 1145, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 708, 1155, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 696, 1190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 716, 1240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 716, 1250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 696, 1340, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 696, 1430, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 701, 1460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 702, 1465, { 0, 0 }, 80896, 70656, 0, 696, { 0, 0 }, 67, NULL, NULL },
    { 713, 1495, { 0, 0 }, 103424, 71168, 0, 695, { 0, 0 }, 323, NULL, NULL },
    { 713, 1830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 713, 1850, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 320, EventCharaFadeOut, NULL },
    { 696, 2070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 713, 5070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33093, NULL, NULL },
};

static const EventCharaTrack sEvent167Tracks[5] = {
    { sEvent167Track0, 43, { 0, 0, 0 } },
    { sEvent167Track1, 81, { 0, 0, 0 } },
    { sEvent167Track2, 67, { 0, 0, 0 } },
    { sEvent167Track3, 50, { 0, 0, 0 } },
    { sEvent167Track4, 65, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent167 = {
    5,
    { 0, 0, 0 },
    sEvent167Tracks,
    sEvent167Camera,
    sEvent167Script,
    sEvent167SoundCues,
    sEvent167BgEffects,
    2130,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    168,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent167 = {
    5,
    { 0, 0, 0 },
    sEvent167Tracks,
    sEvent167Camera,
    sEvent167Script,
    sEvent167SoundCues,
    sEvent167BgEffects,
    2270,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    166,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_168_text.inc"
static const MessageScriptEntry sEvent168Script[19] = {
    { 54, 4, 1, 1, { 0, 0, 0 }, gEvent168Text00, 0, 100 },
    { 54, 1, 1, 1, { 0, 0, 0 }, gEvent168Text01, 0, 280 },
    { 27, 0, 2, 1, { 0, 0, 0 }, gEvent168Text02, 0, 300 },
    { 27, 0, 2, 1, { 0, 0, 0 }, gEvent168Text03, 0, 450 },
    { 54, 1, 1, 1, { 0, 0, 0 }, gEvent168Text04, 0, 480 },
    { 27, 0, 2, 1, { 0, 0, 0 }, gEvent168Text05, 0, 570 },
    { 27, 0, 2, 1, { 0, 0, 0 }, gEvent168Text06, 0, 650 },
    { 27, 0, 2, 1, { 0, 0, 0 }, gEvent168Text07, 0, 830 },
    { 54, 4, 1, 1, { 0, 0, 0 }, gEvent168Text08, 0, 1170 },
    { 54, 2, 4, 1, { 0, 0, 0 }, gEvent168Text09, 0, 1172 },
    { 54, 0, 1, 1, { 0, 0, 0 }, gEvent168Text10, 0, 1260 },
    { 54, 1, 4, 1, { 0, 0, 0 }, gEvent168Text11, 0, 1262 },
    { 60, 4, 0, 1, { 0, 0, 0 }, gEvent168Text12, 0, 1305 },
    { 60, 4, 0, 1, { 0, 0, 0 }, gEvent168Text13, 0, 1420 },
    { 60, 4, 4, 1, { 0, 0, 0 }, gEvent168Text14, 0, 1422 },
    { 60, 4, 4, 1, { 0, 0, 0 }, gEvent168Text15, 0, 1424 },
    { 54, 3, 1, 1, { 0, 0, 0 }, gEvent168Text16, 0, 1620 },
    { 54, 0, 4, 1, { 0, 0, 0 }, gEvent168Text17, 0, 1622 },
    { 54, 1, 4, 1, { 0, 0, 0 }, gEvent168Text18, MSG_SCRIPT_FLAG_END, 1624 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent168Script[19] = {
    { 54, 4, 1, 3, { 0, 0, 0 }, gEvent168Text00, 0, 100 },
    { 54, 1, 1, 3, { 0, 0, 0 }, gEvent168Text01, 0, 280 },
    { 27, 0, 2, 3, { 0, 0, 0 }, gEvent168Text02, 0, 300 },
    { 27, 0, 2, 3, { 0, 0, 0 }, gEvent168Text03, 0, 450 },
    { 54, 1, 1, 3, { 0, 0, 0 }, gEvent168Text04, 0, 480 },
    { 27, 0, 2, 3, { 0, 0, 0 }, gEvent168Text05, 0, 570 },
    { 27, 0, 2, 3, { 0, 0, 0 }, gEvent168Text06, 0, 650 },
    { 27, 0, 2, 3, { 0, 0, 0 }, gEvent168Text07, 0, 830 },
    { 54, 4, 1, 3, { 0, 0, 0 }, gEvent168Text08, 0, 1170 },
    { 54, 2, 4, 3, { 0, 0, 0 }, gEvent168Text09, 0, 1172 },
    { 54, 0, 1, 3, { 0, 0, 0 }, gEvent168Text10, 0, 1260 },
    { 54, 1, 4, 3, { 0, 0, 0 }, gEvent168Text11, 0, 1262 },
    { 60, 4, 0, 3, { 0, 0, 0 }, gEvent168Text12, 0, 1305 },
    { 60, 4, 0, 3, { 0, 0, 0 }, gEvent168Text13, 0, 1420 },
    { 60, 4, 4, 3, { 0, 0, 0 }, gEvent168Text14, 0, 1422 },
    { 60, 4, 4, 3, { 0, 0, 0 }, gEvent168Text15, 0, 1424 },
    { 54, 3, 1, 3, { 0, 0, 0 }, gEvent168Text16, 0, 1620 },
    { 54, 0, 4, 3, { 0, 0, 0 }, gEvent168Text17, 0, 1622 },
    { 54, 1, 4, 3, { 0, 0, 0 }, gEvent168Text18, MSG_SCRIPT_FLAG_END, 1624 },
};

#include "event_168_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent168Script[19] = {
    { 54, 4, 1, 1, { 0, 0, 0 }, &gEvent168Text00, 0, 100 },
    { 54, 1, 1, 1, { 0, 0, 0 }, &gEvent168Text01, 0, 280 },
    { 27, 0, 2, 1, { 0, 0, 0 }, &gEvent168Text02, 0, 300 },
    { 27, 0, 2, 1, { 0, 0, 0 }, &gEvent168Text03, 0, 450 },
    { 54, 1, 1, 1, { 0, 0, 0 }, &gEvent168Text04, 0, 480 },
    { 27, 0, 2, 1, { 0, 0, 0 }, &gEvent168Text05, 0, 570 },
    { 27, 0, 2, 1, { 0, 0, 0 }, &gEvent168Text06, 0, 650 },
    { 27, 0, 2, 1, { 0, 0, 0 }, &gEvent168Text07, 0, 830 },
    { 54, 4, 1, 1, { 0, 0, 0 }, &gEvent168Text08, 0, 1170 },
    { 54, 2, 4, 1, { 0, 0, 0 }, &gEvent168Text09, 0, 1172 },
    { 54, 0, 1, 1, { 0, 0, 0 }, &gEvent168Text10, 0, 1260 },
    { 54, 1, 4, 1, { 0, 0, 0 }, &gEvent168Text11, 0, 1262 },
    { 60, 4, 0, 1, { 0, 0, 0 }, &gEvent168Text12, 0, 1305 },
    { 60, 4, 0, 1, { 0, 0, 0 }, &gEvent168Text13, 0, 1420 },
    { 60, 4, 4, 1, { 0, 0, 0 }, &gEvent168Text14, 0, 1422 },
    { 60, 4, 4, 1, { 0, 0, 0 }, &gEvent168Text15, 0, 1424 },
    { 54, 3, 1, 1, { 0, 0, 0 }, &gEvent168Text16, 0, 1620 },
    { 54, 0, 4, 1, { 0, 0, 0 }, &gEvent168Text17, 0, 1622 },
    { 54, 1, 4, 1, { 0, 0, 0 }, &gEvent168Text18, MSG_SCRIPT_FLAG_END, 1624 },
};
#endif

static const EvSoundCue sEvent168SoundCues[2] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_BGM_EVENT_XIII, 1680, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent168Camera[3] = {
    { -65036, 77056, 66816, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64346, 73216, 67328, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -64536, 73216, 71680, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent168Track0[10] = {
    { 856, 940, { 0, 0 }, 87296, 66816, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 856, 1070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 856, 1190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 881, 1230, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 856, 1320, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 856, 1370, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateQuestionTask },
    { 856, 1450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 856, 1580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 856, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 856, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent168Track1[6] = {
    { 444, 120, { 0, 0 }, 71680, 82688, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 444, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 444, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 444, 810, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 444, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 444, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent168Track2[2] = {
    { 919, 30, { 0, 0 }, 72192, 82432, 0, 0, { 0, 0 }, 322, NULL, NULL },
    { 919, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33093, NULL, NULL },
};

static const EventCharaKeyframe sEvent168Track3[13] = {
    { 695, 301, { 0, 0 }, 39680, 66048, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 711, 400, { 0, 0 }, 62208, 77824, 0, 695, { 0, 0 }, 67, NULL, NULL },
    { 695, 410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 696, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 695, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 703, 760, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 704, 790, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 695, 850, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 695, 860, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 696, 890, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 712, 1400, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 696, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 696, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent168Track4[4] = {
    { 909, 624, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8514, NULL, NULL },
    { 916, 766, { 0, 0 }, 62208, 77824, 0, 0, { 0, 0 }, 16722, NULL, NULL },
    { 909, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 322, NULL, NULL },
    { 909, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98373, NULL, NULL },
};

static const EventCharaTrack sEvent168Tracks[5] = {
    { sEvent168Track0, 81, { 0, 0, 0 } },
    { sEvent168Track1, 35, { 0, 0, 0 } },
    { sEvent168Track2, 86, { 0, 0, 0 } },
    { sEvent168Track3, 65, { 0, 0, 0 } },
    { sEvent168Track4, 85, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent168 = {
    5,
    { 0, 0, 0 },
    sEvent168Tracks,
    sEvent168Camera,
    sEvent168Script,
    sEvent168SoundCues,
    NULL,
    1685,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    169,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent168 = {
    5,
    { 0, 0, 0 },
    sEvent168Tracks,
    sEvent168Camera,
    sEvent168Script,
    sEvent168SoundCues,
    NULL,
    1685,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    167,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_169_text.inc"
static const MessageScriptEntry sEvent169Script[11] = {
    { 55, 0, 3, 1, { 0, 0, 0 }, gEvent169Text00, 0, 280 },
    { 57, 0, 1, 1, { 0, 0, 0 }, gEvent169Text01, 0, 320 },
    { 55, 0, 3, 1, { 0, 0, 0 }, gEvent169Text02, 0, 350 },
    { 55, 5, 4, 1, { 0, 0, 0 }, gEvent169Text03, 0, 354 },
    { 57, 0, 1, 1, { 0, 0, 0 }, gEvent169Text04, 0, 400 },
    { 57, 0, 4, 1, { 0, 0, 0 }, gEvent169Text05, 0, 402 },
    { 57, 0, 4, 1, { 0, 0, 0 }, gEvent169Text06, 0, 404 },
    { 55, 0, 3, 1, { 0, 0, 0 }, gEvent169Text07, 0, 440 },
    { 57, 0, 1, 1, { 0, 0, 0 }, gEvent169Text08, 0, 470 },
    { 57, 0, 4, 1, { 0, 0, 0 }, gEvent169Text09, 0, 472 },
    { 55, 1, 1, 1, { 0, 0, 0 }, gEvent169Text10, MSG_SCRIPT_FLAG_END, 560 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent169Script[11] = {
    { 55, 0, 3, 3, { 0, 0, 0 }, gEvent169Text00, 0, 280 },
    { 57, 0, 1, 3, { 0, 0, 0 }, gEvent169Text01, 0, 320 },
    { 55, 0, 3, 3, { 0, 0, 0 }, gEvent169Text02, 0, 350 },
    { 55, 5, 4, 3, { 0, 0, 0 }, gEvent169Text03, 0, 354 },
    { 57, 0, 1, 3, { 0, 0, 0 }, gEvent169Text04, 0, 400 },
    { 57, 0, 4, 3, { 0, 0, 0 }, gEvent169Text05, 0, 402 },
    { 57, 0, 4, 3, { 0, 0, 0 }, gEvent169Text06, 0, 404 },
    { 55, 0, 3, 3, { 0, 0, 0 }, gEvent169Text07, 0, 440 },
    { 57, 0, 1, 3, { 0, 0, 0 }, gEvent169Text08, 0, 470 },
    { 57, 0, 4, 3, { 0, 0, 0 }, gEvent169Text09, 0, 472 },
    { 55, 1, 1, 3, { 0, 0, 0 }, gEvent169Text10, MSG_SCRIPT_FLAG_END, 560 },
};

#include "event_169_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent169Script[11] = {
    { 55, 0, 3, 1, { 0, 0, 0 }, &gEvent169Text00, 0, 280 },
    { 57, 0, 1, 1, { 0, 0, 0 }, &gEvent169Text01, 0, 320 },
    { 55, 0, 3, 1, { 0, 0, 0 }, &gEvent169Text02, 0, 350 },
    { 55, 5, 4, 1, { 0, 0, 0 }, &gEvent169Text03, 0, 354 },
    { 57, 0, 1, 1, { 0, 0, 0 }, &gEvent169Text04, 0, 400 },
    { 57, 0, 4, 1, { 0, 0, 0 }, &gEvent169Text05, 0, 402 },
    { 57, 0, 4, 1, { 0, 0, 0 }, &gEvent169Text06, 0, 404 },
    { 55, 0, 3, 1, { 0, 0, 0 }, &gEvent169Text07, 0, 440 },
    { 57, 0, 1, 1, { 0, 0, 0 }, &gEvent169Text08, 0, 470 },
    { 57, 0, 4, 1, { 0, 0, 0 }, &gEvent169Text09, 0, 472 },
    { 55, 1, 1, 1, { 0, 0, 0 }, &gEvent169Text10, MSG_SCRIPT_FLAG_END, 560 },
};
#endif

static const EvSoundCue sEvent169SoundCues[3] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_EV_WARPOUT, 150, 0, 0 },
    { SONG_BGM_EVENT_XIII, 615, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent169Camera[1] = {
    { -64537, 79616, 50432, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent169Track0[5] = {
    { 889, 230, { 0, 0 }, 72448, 56320, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 889, 352, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 890, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 892, 520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 890, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent169Track1[4] = {
    { 883, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 883, 300, { 0, 0 }, 87808, 64000, 0, 0, { 0, 0 }, 2, EventCharaFadeIn, NULL },
    { 887, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 883, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent169Tracks[2] = {
    { sEvent169Track0, 83, { 0, 0, 0 } },
    { sEvent169Track1, 82, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent169 = {
    2,
    { 0, 0, 0 },
    sEvent169Tracks,
    sEvent169Camera,
    sEvent169Script,
    sEvent169SoundCues,
    NULL,
    620,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    170,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent169 = {
    2,
    { 0, 0, 0 },
    sEvent169Tracks,
    sEvent169Camera,
    sEvent169Script,
    sEvent169SoundCues,
    NULL,
    620,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    168,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_170_text.inc"
static const MessageScriptEntry sEvent170Script[2] = {
    { 26, 0, 3, 1, { 0, 0, 0 }, gEvent170Text00, 0, 250 },
    { 26, 5, 3, 1, { 0, 0, 0 }, gEvent170Text01, MSG_SCRIPT_FLAG_END, 350 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent170Script[2] = {
    { 26, 0, 3, 3, { 0, 0, 0 }, gEvent170Text00, 0, 250 },
    { 26, 5, 3, 3, { 0, 0, 0 }, gEvent170Text01, MSG_SCRIPT_FLAG_END, 350 },
};

#include "event_170_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent170Script[2] = {
    { 26, 0, 3, 1, { 0, 0, 0 }, &gEvent170Text00, 0, 250 },
    { 26, 5, 3, 1, { 0, 0, 0 }, &gEvent170Text01, MSG_SCRIPT_FLAG_END, 350 },
};
#endif

static const EvSoundCue sEvent170SoundCues[1] = {
    { SONG_BGM_T13THFLOOR, 0, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent170Camera[1] = {
    { -64537, 190976, 59648, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent170Track0[5] = {
    { 515, 1, { 0, 0 }, 156416, 83968, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 518, 140, { 0, 0 }, 187136, 67840, 0, 515, { 0, 0 }, 67, NULL, NULL },
    { 515, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 557, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent170Track1[3] = {
    { 603, 203, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 603, 1000, { 0, 0 }, 187136, 67840, 0, 0, { 0, 0 }, 338, NULL, NULL },
    { 603, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent170Tracks[2] = {
    { sEvent170Track0, 44, { 0, 0, 0 } },
    { sEvent170Track1, 50, { 0, 0, 0 } },
};

const EventSequenceDef gEvent170 = {
    2,
    { 0, 0, 0 },
    sEvent170Tracks,
    sEvent170Camera,
    sEvent170Script,
    sEvent170SoundCues,
    NULL,
    410,
    1,
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

#ifdef VERSION_US
#include "event_171_text.inc"
static const MessageScriptEntry sEvent171Script[11] = {
    { 26, 0, 3, 1, { 0, 0, 0 }, gEvent171Text00, 0, 430 },
    { 57, 0, 1, 1, { 0, 0, 0 }, gEvent171Text01, 0, 460 },
    { 57, 0, 4, 1, { 0, 0, 0 }, gEvent171Text02, 0, 462 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent171Text03, 0, 490 },
    { 57, 0, 1, 1, { 0, 0, 0 }, gEvent171Text04, 0, 520 },
    { 57, 0, 1, 1, { 0, 0, 0 }, gEvent171Text05, 0, 730 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent171Text06, 0, 780 },
    { 57, 2, 1, 1, { 0, 0, 0 }, gEvent171Text07, 0, 810 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent171Text08, 0, 970 },
    { 57, 1, 1, 1, { 0, 0, 0 }, gEvent171Text09, 0, 1020 },
    { 57, 2, 4, 1, { 0, 0, 0 }, gEvent171Text10, MSG_SCRIPT_FLAG_END, 1022 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent171Script[11] = {
    { 26, 0, 3, 3, { 0, 0, 0 }, gEvent171Text00, 0, 430 },
    { 57, 0, 1, 3, { 0, 0, 0 }, gEvent171Text01, 0, 460 },
    { 57, 0, 4, 3, { 0, 0, 0 }, gEvent171Text02, 0, 462 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent171Text03, 0, 490 },
    { 57, 0, 1, 3, { 0, 0, 0 }, gEvent171Text04, 0, 520 },
    { 57, 0, 1, 3, { 0, 0, 0 }, gEvent171Text05, 0, 730 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent171Text06, 0, 780 },
    { 57, 2, 1, 3, { 0, 0, 0 }, gEvent171Text07, 0, 810 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent171Text08, 0, 970 },
    { 57, 1, 1, 3, { 0, 0, 0 }, gEvent171Text09, 0, 1020 },
    { 57, 2, 4, 3, { 0, 0, 0 }, gEvent171Text10, MSG_SCRIPT_FLAG_END, 1022 },
};

#include "event_171_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent171Script[11] = {
    { 26, 0, 3, 1, { 0, 0, 0 }, &gEvent171Text00, 0, 430 },
    { 57, 0, 1, 1, { 0, 0, 0 }, &gEvent171Text01, 0, 460 },
    { 57, 0, 4, 1, { 0, 0, 0 }, &gEvent171Text02, 0, 462 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent171Text03, 0, 490 },
    { 57, 0, 1, 1, { 0, 0, 0 }, &gEvent171Text04, 0, 520 },
    { 57, 0, 1, 1, { 0, 0, 0 }, &gEvent171Text05, 0, 730 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent171Text06, 0, 780 },
    { 57, 2, 1, 1, { 0, 0, 0 }, &gEvent171Text07, 0, 810 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent171Text08, 0, 970 },
    { 57, 1, 1, 1, { 0, 0, 0 }, &gEvent171Text09, 0, 1020 },
    { 57, 2, 4, 1, { 0, 0, 0 }, &gEvent171Text10, MSG_SCRIPT_FLAG_END, 1022 },
};
#endif

static const EvSoundCue sEvent171SoundCues[6] = {
    { 65535, 0, 0, 0 },
    { SONG_BGM_EVENT_XIII, 250, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT_XIII, 805, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT2, 815, 0, 0 },
    { SONG_SND_380, 835, 0, 0 },
    { SONG_SND_359, 1040, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent171Camera[7] = {
    { -65336, 158464, 76544, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64716, 192000, 60416, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 70, { 0, 0 }, NULL },
    { -64681, 199680, 54272, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 15, { 0, 0 }, NULL },
    { -64586, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_SMALL | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64566, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -63536, 192000, 60416, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 30, { 0, 0 }, NULL },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent171Track0[14] = {
    { 518, 1, { 0, 0 }, 131584, 97536, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 518, 110, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 515, 120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 532, 130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 532, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 532, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 518, 410, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 515, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 515, 860, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 555, 972, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 556, 986, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 1040, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 560, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent171Track1[3] = {
    { 887, 820, { 0, 0 }, 199424, 63488, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 888, 990, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 883, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent171Track2[3] = {
    { 926, 835, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 926, 880, { 0, 0 }, 199680, 54272, 0, 0, { 0, 0 }, 16658, NULL, NULL },
    { 926, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaTrack sEvent171Tracks[3] = {
    { sEvent171Track0, 44, { 0, 0, 0 } },
    { sEvent171Track1, 82, { 0, 0, 0 } },
    { sEvent171Track2, 92, { 0, 0, 0 } },
};

const EventSequenceDef gEvent171 = {
    3,
    { 0, 0, 0 },
    sEvent171Tracks,
    sEvent171Camera,
    sEvent171Script,
    sEvent171SoundCues,
    NULL,
    1090,
    0,
    1,
    0,
    0,
    0,
    0,
    167,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_172_text.inc"
static const MessageScriptEntry sEvent172Script[6] = {
    { 57, 2, 1, 1, { 0, 0, 0 }, gEvent172Text00, 0, 100 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent172Text01, 0, 140 },
    { 26, 1, 4, 1, { 0, 0, 0 }, gEvent172Text02, 0, 144 },
    { 57, 1, 1, 1, { 0, 0, 0 }, gEvent172Text03, 0, 180 },
    { 57, 2, 4, 1, { 0, 0, 0 }, gEvent172Text04, 0, 182 },
    { 26, 3, 3, 1, { 0, 0, 0 }, gEvent172Text05, MSG_SCRIPT_FLAG_END, 480 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent172Script[6] = {
    { 57, 2, 1, 3, { 0, 0, 0 }, gEvent172Text00, 0, 100 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent172Text01, 0, 140 },
    { 26, 1, 4, 3, { 0, 0, 0 }, gEvent172Text02, 0, 144 },
    { 57, 1, 1, 3, { 0, 0, 0 }, gEvent172Text03, 0, 180 },
    { 57, 2, 4, 3, { 0, 0, 0 }, gEvent172Text04, 0, 182 },
    { 26, 3, 3, 3, { 0, 0, 0 }, gEvent033Text09, MSG_SCRIPT_FLAG_END, 480 },
};

#include "event_172_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent172Script[6] = {
    { 57, 2, 1, 1, { 0, 0, 0 }, &gEvent172Text00, 0, 100 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent172Text01, 0, 140 },
    { 26, 1, 4, 1, { 0, 0, 0 }, &gEvent172Text02, 0, 144 },
    { 57, 1, 1, 1, { 0, 0, 0 }, &gEvent172Text03, 0, 180 },
    { 57, 2, 4, 1, { 0, 0, 0 }, &gEvent172Text04, 0, 182 },
    { 26, 3, 3, 1, { 0, 0, 0 }, &gEvent172Text05, MSG_SCRIPT_FLAG_END, 480 },
};
#endif

static const EvSoundCue sEvent172SoundCues[6] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_EV_WARPIN, 230, 0, 0 },
    { SONG_SND_378, 250, 0, 0 },
    { SONG_EV_RUMBLE, 270, 0, 0 },
    { SONG_EV_RUMBLE, 640, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT_XIII, 645, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent172Camera[5] = {
    { -65266, 192256, 60672, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65216, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_SMALL | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64935, 182528, 65792, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_SMALL | CAMERA_MODE_APPROACH, 100, { 0, 0 }, NULL },
    { -64536, 38912, 38400, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EventBgEffectEntry sEvent172BgEffects[5] = {
    { 320, 0, 0, 0, 0 },
    { 450, 0, 60, 0, 0x14 },
    { 3310, 0, 0, 0, 0 },
    { 3380, 0, 0, 0, 0x2 },
    { 3500, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent172Track0[7] = {
    { 555, 280, { 0, 0 }, 182016, 71936, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 556, 290, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 532, 580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 532, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaFadeOut, NULL },
    { 515, 1000, { 0, 0 }, 256000, 256000, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 515, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent172Track1[4] = {
    { 886, 230, { 0, 0 }, 199424, 63488, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 886, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaFadeOut, NULL },
    { 886, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 883, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent172Track2[3] = {
    { 926, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 926, 300, { 0, 0 }, 199936, 60672, 0, 0, { 0, 0 }, 16658, NULL, NULL },
    { 926, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaTrack sEvent172Tracks[3] = {
    { sEvent172Track0, 44, { 0, 0, 0 } },
    { sEvent172Track1, 82, { 0, 0, 0 } },
    { sEvent172Track2, 92, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent172 = {
    3,
    { 0, 0, 0 },
    sEvent172Tracks,
    sEvent172Camera,
    sEvent172Script,
    sEvent172SoundCues,
    sEvent172BgEffects,
    650,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    173,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent172 = {
    3,
    { 0, 0, 0 },
    sEvent172Tracks,
    sEvent172Camera,
    sEvent172Script,
    sEvent172SoundCues,
    sEvent172BgEffects,
    650,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    171,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_173_text.inc"
static const MessageScriptEntry sEvent173Script[15] = {
    { 26, 5, 1, 1, { 0, 0, 0 }, gEvent173Text00, 0, 350 },
    { 56, 0, 3, 1, { 0, 0, 0 }, gEvent173Text01, MSG_SCRIPT_FLAG_SILHOUETTE, 400 },
    { 26, 2, 1, 1, { 0, 0, 0 }, gEvent173Text02, 0, 600 },
    { 56, 0, 2, 1, { 0, 0, 0 }, gEvent173Text03, MSG_SCRIPT_FLAG_SILHOUETTE, 640 },
    { 26, 3, 1, 1, { 0, 0, 0 }, gEvent173Text04, 0, 670 },
    { 56, 0, 2, 1, { 0, 0, 0 }, gEvent173Text05, MSG_SCRIPT_FLAG_SILHOUETTE, 700 },
    { 26, 2, 1, 1, { 0, 0, 0 }, gEvent173Text06, 0, 730 },
    { 56, 0, 2, 1, { 0, 0, 0 }, gEvent173Text07, MSG_SCRIPT_FLAG_SILHOUETTE, 760 },
    { 56, 0, 4, 1, { 0, 0, 0 }, gEvent173Text08, MSG_SCRIPT_FLAG_SILHOUETTE, 762 },
    { 56, 0, 4, 1, { 0, 0, 0 }, gEvent173Text09, MSG_SCRIPT_FLAG_SILHOUETTE, 764 },
    { 56, 1, 1, 1, { 0, 0, 0 }, gEvent173Text10, 0, 850 },
    { 61, 0, 3, 1, { 0, 0, 0 }, gEvent173Text11, MSG_SCRIPT_FLAG_SILHOUETTE, 870 },
    { 26, 3, 3, 1, { 0, 0, 0 }, gEvent173Text12, 0, 955 },
    { 26, 3, 3, 1, { 0, 0, 0 }, gEvent173Text13, 0, 1275 },
    { 56, 2, 1, 1, { 0, 0, 0 }, gEvent173Text14, MSG_SCRIPT_FLAG_END, 1305 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent173Script[15] = {
    { 26, 5, 1, 3, { 0, 0, 0 }, gEvent173Text00, 0, 350 },
    { 56, 0, 3, 3, { 0, 0, 0 }, gEvent173Text01, MSG_SCRIPT_FLAG_SILHOUETTE, 400 },
    { 26, 2, 1, 3, { 0, 0, 0 }, gEvent173Text02, 0, 600 },
    { 56, 0, 2, 3, { 0, 0, 0 }, gEvent173Text03, MSG_SCRIPT_FLAG_SILHOUETTE, 640 },
    { 26, 3, 1, 3, { 0, 0, 0 }, gEvent173Text04, 0, 670 },
    { 56, 0, 2, 3, { 0, 0, 0 }, gEvent173Text05, MSG_SCRIPT_FLAG_SILHOUETTE, 700 },
    { 26, 2, 1, 3, { 0, 0, 0 }, gEvent173Text06, 0, 730 },
    { 56, 0, 2, 3, { 0, 0, 0 }, gEvent173Text07, MSG_SCRIPT_FLAG_SILHOUETTE, 760 },
    { 56, 0, 4, 3, { 0, 0, 0 }, gEvent173Text08, MSG_SCRIPT_FLAG_SILHOUETTE, 762 },
    { 56, 0, 4, 3, { 0, 0, 0 }, gEvent173Text09, MSG_SCRIPT_FLAG_SILHOUETTE, 764 },
    { 56, 1, 1, 3, { 0, 0, 0 }, gEvent173Text10, 0, 850 },
    { 61, 0, 3, 3, { 0, 0, 0 }, gEvent173Text11, MSG_SCRIPT_FLAG_SILHOUETTE, 870 },
    { 26, 3, 3, 3, { 0, 0, 0 }, gEvent155Text19, 0, 955 },
    { 26, 3, 3, 3, { 0, 0, 0 }, gEvent158Text05, 0, 1275 },
    { 56, 2, 1, 3, { 0, 0, 0 }, gEvent173Text14, MSG_SCRIPT_FLAG_END, 1305 },
};

#include "event_173_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent173Script[15] = {
    { 26, 5, 1, 1, { 0, 0, 0 }, &gEvent173Text00, 0, 350 },
    { 56, 0, 3, 1, { 0, 0, 0 }, &gEvent173Text01, MSG_SCRIPT_FLAG_SILHOUETTE, 400 },
    { 26, 2, 1, 1, { 0, 0, 0 }, &gEvent173Text02, 0, 600 },
    { 56, 0, 2, 1, { 0, 0, 0 }, &gEvent173Text03, MSG_SCRIPT_FLAG_SILHOUETTE, 640 },
    { 26, 3, 1, 1, { 0, 0, 0 }, &gEvent173Text04, 0, 670 },
    { 56, 0, 2, 1, { 0, 0, 0 }, &gEvent173Text05, MSG_SCRIPT_FLAG_SILHOUETTE, 700 },
    { 26, 2, 1, 1, { 0, 0, 0 }, &gEvent173Text06, 0, 730 },
    { 56, 0, 2, 1, { 0, 0, 0 }, &gEvent173Text07, MSG_SCRIPT_FLAG_SILHOUETTE, 760 },
    { 56, 0, 4, 1, { 0, 0, 0 }, &gEvent173Text08, MSG_SCRIPT_FLAG_SILHOUETTE, 762 },
    { 56, 0, 4, 1, { 0, 0, 0 }, &gEvent173Text09, MSG_SCRIPT_FLAG_SILHOUETTE, 764 },
    { 56, 1, 1, 1, { 0, 0, 0 }, &gEvent173Text10, 0, 850 },
    { 61, 0, 3, 1, { 0, 0, 0 }, &gEvent173Text11, MSG_SCRIPT_FLAG_SILHOUETTE, 870 },
    { 26, 3, 3, 1, { 0, 0, 0 }, &gEvent173Text12, 0, 955 },
    { 26, 3, 3, 1, { 0, 0, 0 }, &gEvent173Text13, 0, 1275 },
    { 56, 2, 1, 1, { 0, 0, 0 }, &gEvent173Text14, MSG_SCRIPT_FLAG_END, 1305 },
};
#endif

static const EvSoundCue sEvent173SoundCues[4] = {
    { 65535, 0, 0, 0 },
    { SONG_SND_379, 810, 0, 0 },
    { SONG_EV_WHITEOUT, 1085, 0, 0 },
    { SONG_EV_FLASH02, 1335, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent173Camera[11] = {
    { -65316, 30720, 39936, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65016, 30720, 35840, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -64701, 30720, 30720, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -64561, 34560, 26112, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 30, { 0, 0 }, NULL },
    { -64531, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -64511, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -64451, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -64391, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 60, { 0, 0 }, NULL },
    { -64386, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64201, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 100, { 0, 0 }, NULL },
    { -62911, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 60, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent173Track0[15] = {
    { 547, 200, { 0, 0 }, 27904, 37888, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 545, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 545, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 546, 590, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 725, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 526, 763, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 820, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 514, 825, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 835, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 532, 895, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 1270, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 532, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent173Track1[3] = {
    { 688, 810, { 0, 0 }, 89088, 12800, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 694, 915, { 0, 0 }, 42240, 29696, 0, 0, { 0, 0 }, 2, EventCharaFadeIn, NULL },
    { 688, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent173Track2[5] = {
    { 920, 871, { 0, 0 }, 91136, 12800, 0, 0, { 0, 0 }, 8258, NULL, NULL },
    { 920, 872, { 0, 0 }, 35072, 3328, 0, 0, { 0, 0 }, 16706, NULL, NULL },
    { 920, 950, { 0, 0 }, 35328, 26880, 0, 920, { 0, 0 }, 323, NULL, NULL },
    { 920, 1147, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 453, NULL, NULL },
    { 920, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98370, NULL, NULL },
};

static const EventCharaKeyframe sEvent173Track3[3] = {
    { 746, 1147, { 0, 0 }, 96512, 13568, 0, 0, { 0, 0 }, 8258, NULL, NULL },
    { 746, 2000, { 0, 0 }, 34048, 32768, 0, 0, { 0, 0 }, 16450, NULL, NULL },
    { 746, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent173Track4[3] = {
    { 928, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 927, 470, { 0, 0 }, 27904, 29952, 0, 0, { 0, 0 }, 16658, NULL, NULL },
    { 928, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaTrack sEvent173Tracks[5] = {
    { sEvent173Track0, 44, { 0, 0, 0 } },
    { sEvent173Track1, 64, { 0, 0, 0 } },
    { sEvent173Track2, 87, { 0, 0, 0 } },
    { sEvent173Track3, 69, { 0, 0, 0 } },
    { sEvent173Track4, 93, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent173 = {
    5,
    { 0, 0, 0 },
    sEvent173Tracks,
    sEvent173Camera,
    sEvent173Script,
    sEvent173SoundCues,
    NULL,
    1485,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    174,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent173 = {
    5,
    { 0, 0, 0 },
    sEvent173Tracks,
    sEvent173Camera,
    sEvent173Script,
    sEvent173SoundCues,
    NULL,
    1485,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    172,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_174_text.inc"
static const MessageScriptEntry sEvent174Script[4] = {
    { 26, 5, 1, 1, { 0, 0, 0 }, gEvent174Text00, 0, 100 },
    { 26, 5, 1, 1, { 0, 0, 0 }, gEvent174Text01, 0, 250 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent174Text02, 0, 485 },
    { 26, 5, 3, 1, { 0, 0, 0 }, gEvent174Text03, MSG_SCRIPT_FLAG_END, 750 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent174Script[4] = {
    { 26, 5, 1, 3, { 0, 0, 0 }, gEvent163Text13, 0, 100 },
    { 26, 5, 1, 3, { 0, 0, 0 }, gEvent174Text01, 0, 250 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent174Text02, 0, 485 },
    { 26, 5, 3, 3, { 0, 0, 0 }, gEvent174Text03, MSG_SCRIPT_FLAG_END, 750 },
};

#include "event_174_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent174Script[4] = {
    { 26, 5, 1, 1, { 0, 0, 0 }, &gEvent174Text00, 0, 100 },
    { 26, 5, 1, 1, { 0, 0, 0 }, &gEvent174Text01, 0, 250 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent174Text02, 0, 485 },
    { 26, 5, 3, 1, { 0, 0, 0 }, &gEvent174Text03, MSG_SCRIPT_FLAG_END, 750 },
};
#endif

static const EvSoundCue sEvent174SoundCues[1] = {
    { SONG_BGM_T13THFLOOR, 0, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent174Camera[1] = {
    { -64537, 194816, 62720, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent174Track0[15] = {
    { 547, 150, { 0, 0 }, 195840, 64512, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 545, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 546, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 430, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 440, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 538, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 514, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 514, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 514, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 564, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent174Tracks[1] = {
    { sEvent174Track0, 44, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent174 = {
    1,
    { 0, 0, 0 },
    sEvent174Tracks,
    sEvent174Camera,
    sEvent174Script,
    sEvent174SoundCues,
    NULL,
    810,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    175,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent174 = {
    1,
    { 0, 0, 0 },
    sEvent174Tracks,
    sEvent174Camera,
    sEvent174Script,
    sEvent174SoundCues,
    NULL,
    810,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    173,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_175_text.inc"
static const MessageScriptEntry sEvent175Script[13] = {
    { 55, 0, 3, 1, { 0, 0, 0 }, gEvent175Text00, 0, 100 },
    { 55, 0, 4, 1, { 0, 0, 0 }, gEvent175Text01, 0, 102 },
    { 20, 1, 1, 1, { 0, 0, 0 }, gEvent175Text02, 0, 250 },
    { 55, 5, 3, 1, { 0, 0, 0 }, gEvent175Text03, 0, 280 },
    { 20, 0, 1, 1, { 0, 0, 0 }, gEvent175Text04, 0, 310 },
    { 20, 0, 4, 1, { 0, 0, 0 }, gEvent175Text05, 0, 312 },
    { 20, 1, 4, 1, { 0, 0, 0 }, gEvent175Text06, 0, 314 },
    { 55, 0, 3, 1, { 0, 0, 0 }, gEvent175Text07, 0, 340 },
    { 20, 1, 1, 1, { 0, 0, 0 }, gEvent175Text08, 0, 370 },
    { 55, 5, 3, 1, { 0, 0, 0 }, gEvent175Text09, 0, 410 },
    { 20, 1, 1, 1, { 0, 0, 0 }, gEvent175Text10, 0, 460 },
    { 55, 1, 3, 1, { 0, 0, 0 }, gEvent175Text11, 0, 500 },
    { 55, 0, 4, 1, { 0, 0, 0 }, gEvent175Text12, MSG_SCRIPT_FLAG_END, 502 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent175Script[13] = {
    { 55, 0, 3, 3, { 0, 0, 0 }, gEvent175Text00, 0, 100 },
    { 55, 0, 4, 3, { 0, 0, 0 }, gEvent175Text01, 0, 102 },
    { 20, 1, 1, 3, { 0, 0, 0 }, gEvent175Text02, 0, 250 },
    { 55, 5, 3, 3, { 0, 0, 0 }, gEvent175Text03, 0, 280 },
    { 20, 0, 1, 3, { 0, 0, 0 }, gEvent175Text04, 0, 310 },
    { 20, 0, 4, 3, { 0, 0, 0 }, gEvent175Text05, 0, 312 },
    { 20, 1, 4, 3, { 0, 0, 0 }, gEvent175Text06, 0, 314 },
    { 55, 0, 3, 3, { 0, 0, 0 }, gEvent175Text07, 0, 340 },
    { 20, 1, 1, 3, { 0, 0, 0 }, gEvent175Text08, 0, 370 },
    { 55, 5, 3, 3, { 0, 0, 0 }, gEvent175Text09, 0, 410 },
    { 20, 1, 1, 3, { 0, 0, 0 }, gEvent175Text10, 0, 460 },
    { 55, 1, 3, 3, { 0, 0, 0 }, gEvent175Text11, 0, 500 },
    { 55, 0, 4, 3, { 0, 0, 0 }, gEvent175Text12, MSG_SCRIPT_FLAG_END, 502 },
};

#include "event_175_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent175Script[13] = {
    { 55, 0, 3, 1, { 0, 0, 0 }, &gEvent175Text00, 0, 100 },
    { 55, 0, 4, 1, { 0, 0, 0 }, &gEvent175Text01, 0, 102 },
    { 20, 1, 1, 1, { 0, 0, 0 }, &gEvent175Text02, 0, 250 },
    { 55, 5, 3, 1, { 0, 0, 0 }, &gEvent175Text03, 0, 280 },
    { 20, 0, 1, 1, { 0, 0, 0 }, &gEvent175Text04, 0, 310 },
    { 20, 0, 4, 1, { 0, 0, 0 }, &gEvent175Text05, 0, 312 },
    { 20, 1, 4, 1, { 0, 0, 0 }, &gEvent175Text06, 0, 314 },
    { 55, 0, 3, 1, { 0, 0, 0 }, &gEvent175Text07, 0, 340 },
    { 20, 1, 1, 1, { 0, 0, 0 }, &gEvent175Text08, 0, 370 },
    { 55, 5, 3, 1, { 0, 0, 0 }, &gEvent175Text09, 0, 410 },
    { 20, 1, 1, 1, { 0, 0, 0 }, &gEvent175Text10, 0, 460 },
    { 55, 1, 3, 1, { 0, 0, 0 }, &gEvent175Text11, 0, 500 },
    { 55, 0, 4, 1, { 0, 0, 0 }, &gEvent175Text12, MSG_SCRIPT_FLAG_END, 502 },
};
#endif

static const EvSoundCue sEvent175SoundCues[2] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_BGM_EVENT_XIII, 555, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent175Camera[2] = {
    { -65396, 56320, 53248, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64537, 62976, 55808, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent175Track0[4] = {
    { 891, 200, { 0, 0 }, 55808, 61440, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 892, 495, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 890, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 889, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent175Track1[4] = {
    { 486, 103, { 0, 0 }, 97280, 83712, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 502, 227, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 486, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 486, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent175Tracks[2] = {
    { sEvent175Track0, 83, { 0, 0, 0 } },
    { sEvent175Track1, 43, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent175 = {
    2,
    { 0, 0, 0 },
    sEvent175Tracks,
    sEvent175Camera,
    sEvent175Script,
    sEvent175SoundCues,
    NULL,
    560,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    176,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent175 = {
    2,
    { 0, 0, 0 },
    sEvent175Tracks,
    sEvent175Camera,
    sEvent175Script,
    sEvent175SoundCues,
    NULL,
    560,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    174,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_176_text.inc"
static const MessageScriptEntry sEvent176Script[14] = {
    { 26, 3, 3, 1, { 0, 0, 0 }, gEvent176Text00, 0, 240 },
    { 55, 0, 1, 1, { 0, 0, 0 }, gEvent176Text01, 0, 460 },
    { 26, 0, 3, 1, { 0, 0, 0 }, gEvent176Text02, 0, 490 },
    { 26, 3, 3, 1, { 0, 0, 0 }, gEvent176Text03, 0, 600 },
    { 55, 0, 1, 1, { 0, 0, 0 }, gEvent176Text04, 0, 630 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent176Text05, 0, 660 },
    { 55, 5, 1, 1, { 0, 0, 0 }, gEvent176Text06, 0, 690 },
    { 55, 0, 4, 1, { 0, 0, 0 }, gEvent176Text07, 0, 692 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent176Text08, 0, 720 },
    { 55, 0, 1, 1, { 0, 0, 0 }, gEvent176Text09, 0, 750 },
    { 55, 0, 4, 1, { 0, 0, 0 }, gEvent176Text10, 0, 752 },
    { 55, 5, 1, 1, { 0, 0, 0 }, gEvent176Text11, 0, 891 },
    { 26, 3, 3, 1, { 0, 0, 0 }, gEvent176Text12, 0, 950 },
    { 55, 1, 1, 1, { 0, 0, 0 }, gEvent176Text13, MSG_SCRIPT_FLAG_END, 980 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent176Script[14] = {
    { 26, 3, 3, 3, { 0, 0, 0 }, gEvent176Text00, 0, 240 },
    { 55, 0, 1, 3, { 0, 0, 0 }, gEvent176Text01, 0, 460 },
    { 26, 0, 3, 3, { 0, 0, 0 }, gEvent176Text02, 0, 490 },
    { 26, 3, 3, 3, { 0, 0, 0 }, gEvent176Text03, 0, 600 },
    { 55, 0, 1, 3, { 0, 0, 0 }, gEvent176Text04, 0, 630 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent151Text09, 0, 660 },
    { 55, 5, 1, 3, { 0, 0, 0 }, gEvent176Text06, 0, 690 },
    { 55, 0, 4, 3, { 0, 0, 0 }, gEvent176Text07, 0, 692 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent112Text05, 0, 720 },
    { 55, 0, 1, 3, { 0, 0, 0 }, gEvent176Text09, 0, 750 },
    { 55, 0, 4, 3, { 0, 0, 0 }, gEvent176Text10, 0, 752 },
    { 55, 5, 1, 3, { 0, 0, 0 }, gEvent176Text11, 0, 891 },
    { 26, 3, 3, 3, { 0, 0, 0 }, gEvent176Text12, 0, 950 },
    { 55, 1, 1, 3, { 0, 0, 0 }, gEvent176Text13, MSG_SCRIPT_FLAG_END, 980 },
};

#include "event_176_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent176Script[14] = {
    { 26, 3, 3, 1, { 0, 0, 0 }, &gEvent176Text00, 0, 240 },
    { 55, 0, 1, 1, { 0, 0, 0 }, &gEvent176Text01, 0, 460 },
    { 26, 0, 3, 1, { 0, 0, 0 }, &gEvent176Text02, 0, 490 },
    { 26, 3, 3, 1, { 0, 0, 0 }, &gEvent176Text03, 0, 600 },
    { 55, 0, 1, 1, { 0, 0, 0 }, &gEvent176Text04, 0, 630 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent176Text05, 0, 660 },
    { 55, 5, 1, 1, { 0, 0, 0 }, &gEvent176Text06, 0, 690 },
    { 55, 0, 4, 1, { 0, 0, 0 }, &gEvent176Text07, 0, 692 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent176Text08, 0, 720 },
    { 55, 0, 1, 1, { 0, 0, 0 }, &gEvent176Text09, 0, 750 },
    { 55, 0, 4, 1, { 0, 0, 0 }, &gEvent176Text10, 0, 752 },
    { 55, 5, 1, 1, { 0, 0, 0 }, &gEvent176Text11, 0, 891 },
    { 26, 3, 3, 1, { 0, 0, 0 }, &gEvent176Text12, 0, 950 },
    { 55, 1, 1, 1, { 0, 0, 0 }, &gEvent176Text13, MSG_SCRIPT_FLAG_END, 980 },
};
#endif

static const EvSoundCue sEvent176SoundCues[8] = {
    { 65535, 0, 0, 0 },
    { SONG_EV_RUMBLE, 120, 0, 0 },
    { SONG_EV_RUMBLE, 150, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_EV_WARPOUT, 250, 0, 0 },
    { SONG_BGM_EVENT_XIII, 260, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_EV_CARDTHR, 850, 0, 0 },
    { SONG_EV_WARPIN, 1030, 0, 0 },
    { SONG_BGM_EVENT_XIII, 1105, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent176Camera[5] = {
    { -65416, 174080, 72960, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65336, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_MEDIUM | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65326, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_SMALL | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65206, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -62536, 183552, 65280, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent176Track0[15] = {
    { 515, 1, { 0, 0 }, 140032, 91904, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 518, 140, { 0, 0 }, 173568, 76032, 0, 515, { 0, 0 }, 67, NULL, NULL },
    { 515, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 532, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 532, 210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 532, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 515, 595, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 538, 605, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 858, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 559, 890, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 558, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent176Track1[6] = {
    { 889, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 889, 770, { 0, 0 }, 192256, 67328, 0, 0, { 0, 0 }, 2, EventCharaFadeIn, NULL },
    { 893, 880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 895, 1030, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 889, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaFadeOut, NULL },
    { 889, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent176Track2[8] = {
    { 591, 849, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 591, 850, { 0, 0 }, 185600, 61184, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 591, 860, { 0, 0 }, 178432, 65792, 0, 591, { 0, 0 }, 259, NULL, NULL },
    { 591, 870, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 604, 890, { 0, 0 }, 173568, 76032, 0, 0, { 0, 0 }, 338, NULL, NULL },
    { 591, 913, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 603, 3000, { 0, 0 }, 173568, 76032, 0, 0, { 0, 0 }, 338, NULL, NULL },
    { 591, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33029, NULL, NULL },
};

static const EventCharaTrack sEvent176Tracks[3] = {
    { sEvent176Track0, 44, { 0, 0, 0 } },
    { sEvent176Track1, 83, { 0, 0, 0 } },
    { sEvent176Track2, 50, { 0, 0, 0 } },
};

const EventSequenceDef gEvent176 = {
    3,
    { 0, 0, 0 },
    sEvent176Tracks,
    sEvent176Camera,
    sEvent176Script,
    sEvent176SoundCues,
    NULL,
    1110,
    1,
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

#ifdef VERSION_US
#include "event_177_text.inc"
static const MessageScriptEntry sEvent177Script[8] = {
    { 26, 5, 1, 1, { 0, 0, 0 }, gEvent177Text00, 0, 380 },
    { 26, 1, 1, 1, { 0, 0, 0 }, gEvent177Text01, 0, 460 },
    { 26, 1, 4, 1, { 0, 0, 0 }, gEvent177Text02, 0, 462 },
    { 26, 3, 1, 1, { 0, 0, 0 }, gEvent177Text03, 0, 660 },
    { 26, 3, 1, 1, { 0, 0, 0 }, gEvent177Text04, 0, 800 },
    { 26, 3, 1, 1, { 0, 0, 0 }, gEvent177Text05, 0, 980 },
    { 26, 1, 1, 1, { 0, 0, 0 }, gEvent177Text06, 0, 1080 },
    { 26, 3, 1, 1, { 0, 0, 0 }, gEvent177Text07, MSG_SCRIPT_FLAG_END, 1405 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent177Script[8] = {
    { 26, 5, 1, 3, { 0, 0, 0 }, gEvent177Text00, 0, 380 },
    { 26, 1, 1, 3, { 0, 0, 0 }, gEvent177Text01, 0, 460 },
    { 26, 1, 4, 3, { 0, 0, 0 }, gEvent177Text02, 0, 462 },
    { 26, 3, 1, 3, { 0, 0, 0 }, gEvent177Text03, 0, 660 },
    { 26, 3, 1, 3, { 0, 0, 0 }, gEvent142Text03, 0, 800 },
    { 26, 3, 1, 3, { 0, 0, 0 }, gEvent177Text05, 0, 980 },
    { 26, 1, 1, 3, { 0, 0, 0 }, gEvent177Text06, 0, 1080 },
    { 26, 3, 1, 3, { 0, 0, 0 }, gEvent177Text07, MSG_SCRIPT_FLAG_END, 1405 },
};

#include "event_177_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent177Script[8] = {
    { 26, 5, 1, 1, { 0, 0, 0 }, &gEvent177Text00, 0, 380 },
    { 26, 1, 1, 1, { 0, 0, 0 }, &gEvent177Text01, 0, 460 },
    { 26, 1, 4, 1, { 0, 0, 0 }, &gEvent177Text02, 0, 462 },
    { 26, 3, 1, 1, { 0, 0, 0 }, &gEvent177Text03, 0, 660 },
    { 26, 3, 1, 1, { 0, 0, 0 }, &gEvent177Text04, 0, 800 },
    { 26, 3, 1, 1, { 0, 0, 0 }, &gEvent177Text05, 0, 980 },
    { 26, 1, 1, 1, { 0, 0, 0 }, &gEvent177Text06, 0, 1080 },
    { 26, 3, 1, 1, { 0, 0, 0 }, &gEvent177Text07, MSG_SCRIPT_FLAG_END, 1405 },
};
#endif

static const EvSoundCue sEvent177SoundCues[5] = {
    { SONG_BGM_DESTINY_FIELD, 0, 0, 0 },
    { SONG_SND_356, 1, 0, 0 },
    { SONG_SND_370, 1280, 0, 0 },
    { SONG_SND_356, 1585, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_DESTINY_FIELD, 1586, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent177Camera[7] = {
    { -65536, 96768, 77312, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, NULL },
    { -65385, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 80, { 0, 0 }, NULL },
    { -64846, 0, 0, -6912, 44, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64666, 31744, 42752, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 100, { 0, 0 }, NULL },
    { -63986, 34560, 45312, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 30, { 0, 0 }, NULL },
    { -62536, 47104, 51968, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 100, { 0, 0 }, NULL },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent177Track0[24] = {
    { 515, 1, { 0, 0 }, 130816, 102656, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 518, 150, { 0, 0 }, 96768, 84224, 0, 515, { 0, 0 }, 3, NULL, NULL },
    { 515, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 540, 330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 540, 382, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 518, 430, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 515, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 518, 580, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 532, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 532, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 532, 665, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 810, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 522, 880, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 515, 883, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 515, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 950, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateQuestionTask },
    { 515, 1320, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 532, 1330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 532, 1380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 515, 1400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 538, 1407, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 540, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent177Track1[6] = {
    { 676, 1100, { 0, 0 }, 25600, 45312, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 676, 1230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 676, 1280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 676, 1350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaFadeOut, NULL },
    { 676, 2000, { 0, 0 }, 120320, 146176, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 676, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent177Track2[6] = {
    { 627, 1100, { 0, 0 }, 35584, 50432, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 627, 1230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 627, 1280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 627, 1350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaFadeOut, NULL },
    { 627, 2000, { 0, 0 }, 120320, 146176, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 627, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent177Track3[6] = {
    { 678, 1100, { 0, 0 }, 27392, 53248, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 678, 1230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 678, 1280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 678, 1350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaFadeOut, NULL },
    { 678, 2000, { 0, 0 }, 120320, 146176, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 678, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent177Tracks[4] = {
    { sEvent177Track0, 44, { 0, 0, 0 } },
    { sEvent177Track1, 60, { 0, 0, 0 } },
    { sEvent177Track2, 55, { 0, 0, 0 } },
    { sEvent177Track3, 61, { 0, 0, 0 } },
};

const EventSequenceDef gEvent177 = {
    4,
    { 0, 0, 0 },
    sEvent177Tracks,
    sEvent177Camera,
    sEvent177Script,
    sEvent177SoundCues,
    NULL,
    1590,
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
#include "event_178_text.inc"
static const MessageScriptEntry sEvent178Script[14] = {
    { 26, 3, 1, 1, { 0, 0, 0 }, gEvent178Text00, 0, 250 },
    { 26, 0, 1, 1, { 0, 0, 0 }, gEvent178Text01, 0, 600 },
    { 26, 3, 1, 1, { 0, 0, 0 }, gEvent178Text02, 0, 690 },
    { 26, 2, 1, 1, { 0, 0, 0 }, gEvent178Text03, 0, 880 },
    { 55, 5, 0, 1, { 0, 0, 0 }, gEvent178Text04, 0, 910 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent178Text05, 0, 1100 },
    { 55, 0, 1, 1, { 0, 0, 0 }, gEvent178Text06, 0, 1130 },
    { 55, 0, 4, 1, { 0, 0, 0 }, gEvent178Text07, 0, 1132 },
    { 55, 5, 4, 1, { 0, 0, 0 }, gEvent178Text08, 0, 1134 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent178Text09, 0, 1160 },
    { 26, 2, 4, 1, { 0, 0, 0 }, gEvent178Text10, 0, 1162 },
    { 26, 5, 3, 1, { 0, 0, 0 }, gEvent178Text11, 0, 1330 },
    { 55, 0, 1, 1, { 0, 0, 0 }, gEvent178Text12, 0, 1360 },
    { 55, 2, 1, 1, { 0, 0, 0 }, gEvent178Text13, MSG_SCRIPT_FLAG_END, 1460 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent178Script[14] = {
    { 26, 3, 1, 3, { 0, 0, 0 }, gEvent178Text00, 0, 250 },
    { 26, 0, 1, 3, { 0, 0, 0 }, gEvent178Text01, 0, 600 },
    { 26, 3, 1, 3, { 0, 0, 0 }, gEvent018Text11, 0, 690 },
    { 26, 2, 1, 3, { 0, 0, 0 }, gEvent178Text03, 0, 880 },
    { 55, 5, 0, 3, { 0, 0, 0 }, gEvent178Text04, 0, 910 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent151Text09, 0, 1100 },
    { 55, 0, 1, 3, { 0, 0, 0 }, gEvent178Text06, 0, 1130 },
    { 55, 0, 4, 3, { 0, 0, 0 }, gEvent178Text07, 0, 1132 },
    { 55, 5, 4, 3, { 0, 0, 0 }, gEvent178Text08, 0, 1134 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent178Text09, 0, 1160 },
    { 26, 2, 4, 3, { 0, 0, 0 }, gEvent178Text10, 0, 1162 },
    { 26, 5, 3, 3, { 0, 0, 0 }, gEvent178Text11, 0, 1330 },
    { 55, 0, 1, 3, { 0, 0, 0 }, gEvent178Text12, 0, 1360 },
    { 55, 2, 1, 3, { 0, 0, 0 }, gEvent178Text13, MSG_SCRIPT_FLAG_END, 1460 },
};

#include "event_178_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent178Script[14] = {
    { 26, 3, 1, 1, { 0, 0, 0 }, &gEvent178Text00, 0, 250 },
    { 26, 0, 1, 1, { 0, 0, 0 }, &gEvent178Text01, 0, 600 },
    { 26, 3, 1, 1, { 0, 0, 0 }, &gEvent178Text02, 0, 690 },
    { 26, 2, 1, 1, { 0, 0, 0 }, &gEvent178Text03, 0, 880 },
    { 55, 5, 0, 1, { 0, 0, 0 }, &gEvent178Text04, 0, 910 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent178Text05, 0, 1100 },
    { 55, 0, 1, 1, { 0, 0, 0 }, &gEvent178Text06, 0, 1130 },
    { 55, 0, 4, 1, { 0, 0, 0 }, &gEvent178Text07, 0, 1132 },
    { 55, 5, 4, 1, { 0, 0, 0 }, &gEvent178Text08, 0, 1134 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent178Text09, 0, 1160 },
    { 26, 2, 4, 1, { 0, 0, 0 }, &gEvent178Text10, 0, 1162 },
    { 26, 5, 3, 1, { 0, 0, 0 }, &gEvent178Text11, 0, 1330 },
    { 55, 0, 1, 1, { 0, 0, 0 }, &gEvent178Text12, 0, 1360 },
    { 55, 2, 1, 1, { 0, 0, 0 }, &gEvent178Text13, MSG_SCRIPT_FLAG_END, 1460 },
};
#endif

static const EvSoundCue sEvent178SoundCues[4] = {
    { 65535, 0, 0, 0 },
    { SONG_SND_370, 630, 0, 0 },
    { SONG_EV_WARPOUT, 940, 0, 0 },
    { SONG_BGM_EVENT_XIII, 950, EV_SOUND_FLAG_FADE_IN | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent178Camera[6] = {
    { -65366, 73728, 61440, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65176, 36608, 80128, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -64516, 41984, 78080, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -63991, 53760, 71680, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -63936, 31488, 153856, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 1, { 0, 0 }, NULL },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EventBgEffectEntry sEvent178BgEffects[5] = {
    { 1490, 0, 0, 0, 0 },
    { 1540, 0, 60, 0, 0x14 },
    { 3310, 0, 0, 0, 0 },
    { 4000, 0, 0, 0, 0x2 },
    { 5000, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent178Track0[23] = {
    { 514, 1, { 0, 0 }, 104704, 60416, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 520, 80, { 0, 0 }, 73984, 71424, 0, 514, { 0, 0 }, 3, NULL, NULL },
    { 514, 83, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 514, 100, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 526, 110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 526, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 526, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 516, 360, { 0, 0 }, 47104, 81920, 0, 514, { 0, 0 }, 3, NULL, NULL },
    { 514, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 514, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 526, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 528, 990, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 1030, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 1155, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 538, 1180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 1200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 540, 1545, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 540, 2000, { 0, 0 }, 24832, 164096, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent178Track1[6] = {
    { 889, 940, { 0, 0 }, 120320, 11776, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 889, 1455, { 0, 0 }, 62464, 75264, 0, 0, { 0, 0 }, 2, EventCharaFadeIn, NULL },
    { 899, 1520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 898, 1545, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 889, 2000, { 0, 0 }, 40192, 157440, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 889, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent178Track2[4] = {
    { 420, 630, { 0, 0 }, 36608, 86272, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 420, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaFadeOut, NULL },
    { 420, 1000, { 0, 0 }, 120320, 11776, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 420, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98373, NULL, NULL },
};

static const EventCharaTrack sEvent178Tracks[3] = {
    { sEvent178Track0, 44, { 0, 0, 0 } },
    { sEvent178Track1, 83, { 0, 0, 0 } },
    { sEvent178Track2, 34, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent178 = {
    3,
    { 0, 0, 0 },
    sEvent178Tracks,
    sEvent178Camera,
    sEvent178Script,
    sEvent178SoundCues,
    sEvent178BgEffects,
    1700,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    179,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent178 = {
    3,
    { 0, 0, 0 },
    sEvent178Tracks,
    sEvent178Camera,
    sEvent178Script,
    sEvent178SoundCues,
    sEvent178BgEffects,
    1700,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    177,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_179_text.inc"
static const MessageScriptEntry sEvent179Script[6] = {
    { 26, 3, 3, 1, { 0, 0, 0 }, gEvent179Text00, 0, 355 },
    { 55, 0, 1, 1, { 0, 0, 0 }, gEvent179Text01, 0, 385 },
    { 55, 0, 3, 1, { 0, 0, 0 }, gEvent179Text02, 0, 510 },
    { 26, 5, 3, 1, { 0, 0, 0 }, gEvent179Text03, 0, 640 },
    { 55, 0, 3, 1, { 0, 0, 0 }, gEvent179Text04, 0, 670 },
    { 55, 0, 4, 1, { 0, 0, 0 }, gEvent179Text05, MSG_SCRIPT_FLAG_END, 674 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent179Script[6] = {
    { 26, 3, 3, 3, { 0, 0, 0 }, gEvent179Text00, 0, 355 },
    { 55, 0, 1, 3, { 0, 0, 0 }, gEvent179Text01, 0, 385 },
    { 55, 0, 3, 3, { 0, 0, 0 }, gEvent179Text02, 0, 510 },
    { 26, 5, 3, 3, { 0, 0, 0 }, gEvent163Text13, 0, 640 },
    { 55, 0, 3, 3, { 0, 0, 0 }, gEvent179Text04, 0, 670 },
    { 55, 0, 4, 3, { 0, 0, 0 }, gEvent179Text05, MSG_SCRIPT_FLAG_END, 674 },
};

#include "event_179_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent179Script[6] = {
    { 26, 3, 3, 1, { 0, 0, 0 }, &gEvent179Text00, 0, 355 },
    { 55, 0, 1, 1, { 0, 0, 0 }, &gEvent179Text01, 0, 385 },
    { 55, 0, 3, 1, { 0, 0, 0 }, &gEvent179Text02, 0, 510 },
    { 26, 5, 3, 1, { 0, 0, 0 }, &gEvent179Text03, 0, 640 },
    { 55, 0, 3, 1, { 0, 0, 0 }, &gEvent179Text04, 0, 670 },
    { 55, 0, 4, 1, { 0, 0, 0 }, &gEvent179Text05, MSG_SCRIPT_FLAG_END, 674 },
};
#endif

static const EvSoundCue sEvent179SoundCues[4] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_BGM_EVENT_XIII, 635, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT2, 642, 0, 0 },
    { SONG_SND_363, 840, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent179Camera[8] = {
    { -65536, 83456, 98048, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65441, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_BLACK | CAMERA_MODE_KEEP, 30, { 0, 0 }, NULL },
    { -65436, 32256, 98048, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 1, { 0, 0 }, NULL },
    { -65331, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_BLACK | CAMERA_MODE_KEEP, 30, { 0, 0 }, NULL },
    { -65026, 52992, 25088, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 1, { 0, 0 }, NULL },
    { -64856, 70144, 26624, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -64437, 97024, 33536, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 120, { 0, 0 }, NULL },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EventBgEffectEntry sEvent179BgEffects[5] = {
    { 180, 0, 0, 0, 0 },
    { 200, 0, 10, 0, 0x14 },
    { 210, 0, 0, 0, 0 },
    { 211, 0, 0, 0, 0x2 },
    { 250, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent179Track0[11] = {
    { 540, 205, { 0, 0 }, 25344, 109312, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 540, 250, { 0, 0 }, 46080, 36352, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 515, 260, { 0, 0 }, 46080, 36352, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 514, 290, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 532, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 514, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 514, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent179Track1[8] = {
    { 889, 205, { 0, 0 }, 40960, 102400, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 889, 410, { 0, 0 }, 61696, 29440, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 889, 460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 899, 512, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 898, 625, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 889, 672, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 899, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 889, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent179Track2[3] = {
    { 515, 840, { 0, 0 }, 95744, 40192, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 515, 1600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaFadeToBlack, NULL },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent179Tracks[3] = {
    { sEvent179Track0, 44, { 0, 0, 0 } },
    { sEvent179Track1, 83, { 0, 0, 0 } },
    { sEvent179Track2, 44, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent179 = {
    3,
    { 0, 0, 0 },
    sEvent179Tracks,
    sEvent179Camera,
    sEvent179Script,
    sEvent179SoundCues,
    sEvent179BgEffects,
    900,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    180,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent179 = {
    3,
    { 0, 0, 0 },
    sEvent179Tracks,
    sEvent179Camera,
    sEvent179Script,
    sEvent179SoundCues,
    sEvent179BgEffects,
    900,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    178,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_180_text.inc"
static const MessageScriptEntry sEvent180Script[1] = {
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent180Text00, MSG_SCRIPT_FLAG_END, 100 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent180Script[1] = {
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent180Text00, MSG_SCRIPT_FLAG_END, 100 },
};

#include "event_180_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent180Script[1] = {
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent180Text00, MSG_SCRIPT_FLAG_END, 100 },
};
#endif

static const EvSoundCue sEvent180SoundCues[1] = {
    { SONG_BGM_BOSSWORLD, 0, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent180Camera[1] = {
    { -64537, 61440, 92160, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent180Track0[2] = {
    { 514, 40, { 0, 0 }, 51200, 99840, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 526, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent180Track1[1] = {
    { 944, 999, { 0, 0 }, 18432, 36864, 0, 0, { 0, 0 }, 32834, NULL, NULL },
};

static const EventCharaTrack sEvent180Tracks[2] = {
    { sEvent180Track0, 44, { 0, 0, 0 } },
    { sEvent180Track1, 103, { 0, 0, 0 } },
};

const EventSequenceDef gEvent180 = {
    2,
    { 0, 0, 0 },
    sEvent180Tracks,
    sEvent180Camera,
    sEvent180Script,
    sEvent180SoundCues,
    NULL,
    160,
    0,
    1,
    0,
    0,
    0,
    0,
    154,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_181_text.inc"
static const MessageScriptEntry sEvent181Script[7] = {
    { 26, 3, 1, 1, { 0, 0, 0 }, gEvent181Text00, 0, 210 },
    { 26, 3, 1, 1, { 0, 0, 0 }, gEvent181Text01, 0, 260 },
    { 0, 2, 3, 1, { 0, 0, 0 }, gEvent181Text02, 0, 290 },
    { 26, 3, 1, 1, { 0, 0, 0 }, gEvent181Text03, 0, 440 },
    { 0, 5, 3, 1, { 0, 0, 0 }, gEvent181Text04, 0, 460 },
    { 0, 5, 4, 1, { 0, 0, 0 }, gEvent181Text05, 0, 462 },
    { 0, 2, 3, 1, { 0, 0, 0 }, gEvent181Text06, MSG_SCRIPT_FLAG_END, 562 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent181Script[7] = {
    { 26, 3, 1, 3, { 0, 0, 0 }, gEvent124Text06, 0, 210 },
    { 26, 3, 1, 3, { 0, 0, 0 }, gEvent181Text01, 0, 260 },
    { 0, 2, 3, 3, { 0, 0, 0 }, gEvent181Text02, 0, 290 },
    { 26, 3, 1, 3, { 0, 0, 0 }, gEvent181Text03, 0, 440 },
    { 0, 5, 3, 3, { 0, 0, 0 }, gEvent181Text04, 0, 460 },
    { 0, 5, 4, 3, { 0, 0, 0 }, gEvent181Text05, 0, 462 },
    { 0, 2, 3, 3, { 0, 0, 0 }, gEvent181Text06, MSG_SCRIPT_FLAG_END, 562 },
};

#include "event_181_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent181Script[7] = {
    { 26, 3, 1, 1, { 0, 0, 0 }, &gEvent181Text00, 0, 210 },
    { 26, 3, 1, 1, { 0, 0, 0 }, &gEvent181Text01, 0, 260 },
    { 0, 2, 3, 1, { 0, 0, 0 }, &gEvent181Text02, 0, 290 },
    { 26, 3, 1, 1, { 0, 0, 0 }, &gEvent181Text03, 0, 440 },
    { 0, 5, 3, 1, { 0, 0, 0 }, &gEvent181Text04, 0, 460 },
    { 0, 5, 4, 1, { 0, 0, 0 }, &gEvent181Text05, 0, 462 },
    { 0, 2, 3, 1, { 0, 0, 0 }, &gEvent181Text06, MSG_SCRIPT_FLAG_END, 562 },
};
#endif

static const EvSoundCue sEvent181SoundCues[5] = {
    { SONG_BGM_EVENT_UNREST, 0, 0, 0 },
    { SONG_EV_FLASH01, 233, 0, 0 },
    { SONG_EV_FLASH00, 390, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 615, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_EV_WHITEOUT, 620, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent181Camera[9] = {
    { -65366, 67840, 29696, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65356, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -65303, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65293, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -65146, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65136, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -64916, 77824, 37888, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -64536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 100, { 0, 0 }, NULL },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent181Track0[11] = {
    { 561, 100, { 0, 0 }, 65536, 36608, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 561, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 561, 165, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 542, 180, { 0, 0 }, 69120, 37120, 0, 515, { 0, 0 }, 4099, NULL, NULL },
    { 542, 232, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 542, 242, { 0, 0 }, 74752, 38912, 0, 515, { 0, 0 }, 4099, NULL, NULL },
    { 542, 255, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 534, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 550, 415, { 0, 0 }, 87040, 40704, 0, 515, { 0, 0 }, 3, NULL, NULL },
    { 547, 670, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 547, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32832, EventCharaBlendUp, NULL },
};

static const EventCharaKeyframe sEvent181Track1[12] = {
    { 2, 152, { 0, 0 }, 32000, 31744, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 98, 172, { 0, 0 }, 58624, 35584, 0, 2, { 0, 0 }, 4163, NULL, NULL },
    { 98, 190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 103, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 98, 240, { 0, 0 }, 62208, 36096, 0, 2, { 0, 0 }, 4163, NULL, NULL },
    { 98, 255, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 103, 330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 96, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 93, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 102, 586, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 103, 670, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 103, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32832, EventCharaBlendUp, NULL },
};

static const EventCharaKeyframe sEvent181Track2[3] = {
    { 922, 610, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 922, 623, { 0, 0 }, 61696, 37888, 0, 0, { 0, 0 }, 16642, NULL, NULL },
    { 922, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaTrack sEvent181Tracks[3] = {
    { sEvent181Track0, 44, { 0, 0, 0 } },
    { sEvent181Track1, 0, { 0, 0, 0 } },
    { sEvent181Track2, 89, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent181 = {
    3,
    { 0, 0, 0 },
    sEvent181Tracks,
    sEvent181Camera,
    sEvent181Script,
    sEvent181SoundCues,
    NULL,
    850,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    182,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent181 = {
    3,
    { 0, 0, 0 },
    sEvent181Tracks,
    sEvent181Camera,
    sEvent181Script,
    sEvent181SoundCues,
    NULL,
    850,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    180,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_182_text.inc"
static const MessageScriptEntry sEvent182Script[18] = {
    { 26, 5, 3, 1, { 0, 0, 0 }, gEvent182Text00, 0, 200 },
    { 28, 0, 0, 1, { 0, 0, 0 }, gEvent182Text01, 0, 420 },
    { 28, 0, 1, 1, { 0, 0, 0 }, gEvent182Text02, 0, 580 },
    { 28, 0, 4, 1, { 0, 0, 0 }, gEvent182Text03, 0, 582 },
    { 26, 3, 2, 1, { 0, 0, 0 }, gEvent182Text04, 0, 610 },
    { 28, 0, 1, 1, { 0, 0, 0 }, gEvent182Text05, 0, 640 },
    { 28, 0, 4, 1, { 0, 0, 0 }, gEvent182Text06, 0, 642 },
    { 26, 0, 2, 1, { 0, 0, 0 }, gEvent182Text07, 0, 670 },
    { 28, 0, 1, 1, { 0, 0, 0 }, gEvent182Text08, 0, 700 },
    { 28, 0, 4, 1, { 0, 0, 0 }, gEvent182Text09, 0, 702 },
    { 28, 0, 4, 1, { 0, 0, 0 }, gEvent182Text10, 0, 704 },
    { 26, 0, 2, 1, { 0, 0, 0 }, gEvent182Text11, 0, 730 },
    { 28, 1, 1, 1, { 0, 0, 0 }, gEvent182Text12, 0, 760 },
    { 26, 5, 2, 1, { 0, 0, 0 }, gEvent182Text13, 0, 860 },
    { 28, 1, 1, 1, { 0, 0, 0 }, gEvent182Text14, 0, 970 },
    { 26, 0, 2, 1, { 0, 0, 0 }, gEvent182Text15, 0, 1020 },
    { 26, 2, 1, 1, { 0, 0, 0 }, gEvent182Text16, 0, 1210 },
    { 26, 2, 1, 1, { 0, 0, 0 }, gEvent182Text17, MSG_SCRIPT_FLAG_END, 1350 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent182Script[18] = {
    { 26, 5, 3, 3, { 0, 0, 0 }, gEvent182Text00, 0, 200 },
    { 28, 0, 0, 3, { 0, 0, 0 }, gEvent182Text01, 0, 420 },
    { 28, 0, 1, 3, { 0, 0, 0 }, gEvent182Text02, 0, 580 },
    { 28, 0, 4, 3, { 0, 0, 0 }, gEvent182Text03, 0, 582 },
    { 26, 3, 2, 3, { 0, 0, 0 }, gEvent182Text04, 0, 610 },
    { 28, 0, 1, 3, { 0, 0, 0 }, gEvent182Text05, 0, 640 },
    { 28, 0, 4, 3, { 0, 0, 0 }, gEvent182Text06, 0, 642 },
    { 26, 0, 2, 3, { 0, 0, 0 }, gEvent182Text07, 0, 670 },
    { 28, 0, 1, 3, { 0, 0, 0 }, gEvent182Text08, 0, 700 },
    { 28, 0, 4, 3, { 0, 0, 0 }, gEvent182Text09, 0, 702 },
    { 28, 0, 4, 3, { 0, 0, 0 }, gEvent182Text10, 0, 704 },
    { 26, 0, 2, 3, { 0, 0, 0 }, gEvent182Text11, 0, 730 },
    { 28, 1, 1, 3, { 0, 0, 0 }, gEvent182Text12, 0, 760 },
    { 26, 5, 2, 3, { 0, 0, 0 }, gEvent182Text13, 0, 860 },
    { 28, 1, 1, 3, { 0, 0, 0 }, gEvent182Text14, 0, 970 },
    { 26, 0, 2, 3, { 0, 0, 0 }, gEvent182Text15, 0, 1020 },
    { 26, 2, 1, 3, { 0, 0, 0 }, gEvent182Text16, 0, 1210 },
    { 26, 2, 1, 3, { 0, 0, 0 }, gEvent182Text17, MSG_SCRIPT_FLAG_END, 1350 },
};

#include "event_182_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent182Script[18] = {
    { 26, 5, 3, 1, { 0, 0, 0 }, &gEvent182Text00, 0, 200 },
    { 28, 0, 0, 1, { 0, 0, 0 }, &gEvent182Text01, 0, 420 },
    { 28, 0, 1, 1, { 0, 0, 0 }, &gEvent182Text02, 0, 580 },
    { 28, 0, 4, 1, { 0, 0, 0 }, &gEvent182Text03, 0, 582 },
    { 26, 3, 2, 1, { 0, 0, 0 }, &gEvent182Text04, 0, 610 },
    { 28, 0, 1, 1, { 0, 0, 0 }, &gEvent182Text05, 0, 640 },
    { 28, 0, 4, 1, { 0, 0, 0 }, &gEvent182Text06, 0, 642 },
    { 26, 0, 2, 1, { 0, 0, 0 }, &gEvent182Text07, 0, 670 },
    { 28, 0, 1, 1, { 0, 0, 0 }, &gEvent182Text08, 0, 700 },
    { 28, 0, 4, 1, { 0, 0, 0 }, &gEvent182Text09, 0, 702 },
    { 28, 0, 4, 1, { 0, 0, 0 }, &gEvent182Text10, 0, 704 },
    { 26, 0, 2, 1, { 0, 0, 0 }, &gEvent182Text11, 0, 730 },
    { 28, 1, 1, 1, { 0, 0, 0 }, &gEvent182Text12, 0, 760 },
    { 26, 5, 2, 1, { 0, 0, 0 }, &gEvent182Text13, 0, 860 },
    { 28, 1, 1, 1, { 0, 0, 0 }, &gEvent182Text14, 0, 970 },
    { 26, 0, 2, 1, { 0, 0, 0 }, &gEvent182Text15, 0, 1020 },
    { 26, 2, 1, 1, { 0, 0, 0 }, &gEvent182Text16, 0, 1210 },
    { 26, 2, 1, 1, { 0, 0, 0 }, &gEvent182Text17, MSG_SCRIPT_FLAG_END, 1350 },
};
#endif

static const EvSoundCue sEvent182SoundCues[4] = {
    { 65535, 0, 0, 0 },
    { SONG_EV_FLASH02, 1270, 0, 0 },
    { SONG_SND_702, 1440, 0, 0 },
    { SONG_SND_381, 1670, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent182Camera[7] = {
    { -65536, 98048, 32512, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, NULL },
    { -64296, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 60, { 0, 0 }, NULL },
    { -64266, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 30, { 0, 0 }, NULL },
    { -64236, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 30, { 0, 0 }, NULL },
    { -63916, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -63856, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 60, { 0, 0 }, NULL },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EventBgEffectEntry sEvent182BgEffects[5] = {
    { 1380, 0, 0, 0, 0 },
    { 1440, 0, 0, 0, 0x14 },
    { 1490, 2, 87040, 22784, 0x1 },
    { 1600, 0, 0, 0, 0x2 },
    { 3500, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent182Track0[11] = {
    { 565, 100, { 0, 0 }, 97792, 33024, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 565, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 1048837, NULL, NULL },
    { 565, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 1048832, EventCharaFadeOut, NULL },
    { 565, 1100, { 0, 0 }, 41472, 17920, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 514, 1205, { 0, 0 }, 97280, 38400, 0, 0, { 0, 0 }, 2306, EventCharaFadeIn, NULL },
    { 543, 1271, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2309, NULL, NULL },
    { 543, 1370, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 514, 1460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 514, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 524549, NULL, NULL },
    { 514, 2170, { 0, 0 }, 41472, 17920, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 514, 9000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent182Track1[6] = {
    { 420, 450, { 0, 0 }, 29696, 39424, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 420, 930, { 0, 0 }, 97792, 38400, 0, 0, { 0, 0 }, 16642, EventCharaFadeIn, NULL },
    { 421, 1030, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 421, 1060, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 256, EventCharaFadeOut, NULL },
    { 420, 1100, { 0, 0 }, 29696, 39424, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 420, 9000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98309, NULL, NULL },
};

static const EventCharaKeyframe sEvent182Track2[7] = {
    { 695, 1459, { 0, 0 }, 29696, 39424, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 695, 1500, { 0, 0 }, 97280, 38400, 0, 0, { 0, 0 }, 524546, NULL, NULL },
    { 695, 1590, { 0, 0 }, 97280, 38400, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 696, 1610, { 0, 0 }, 97280, 38400, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 696, 1650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 701, 1625, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 702, 9000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33093, NULL, NULL },
};

static const EventCharaTrack sEvent182Tracks[3] = {
    { sEvent182Track0, 44, { 0, 0, 0 } },
    { sEvent182Track1, 34, { 0, 0, 0 } },
    { sEvent182Track2, 65, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent182 = {
    3,
    { 0, 0, 0 },
    sEvent182Tracks,
    sEvent182Camera,
    sEvent182Script,
    sEvent182SoundCues,
    sEvent182BgEffects,
    1770,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    183,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent182 = {
    3,
    { 0, 0, 0 },
    sEvent182Tracks,
    sEvent182Camera,
    sEvent182Script,
    sEvent182SoundCues,
    sEvent182BgEffects,
    1770,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    181,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_183_text.inc"
static const MessageScriptEntry sEvent183Script[10] = {
    { 0, 3, 1, 1, { 0, 0, 0 }, gEvent183Text00, 0, 95 },
    { 55, 3, 1, 1, { 0, 0, 0 }, gEvent183Text01, 0, 240 },
    { 27, 0, 3, 1, { 0, 0, 0 }, gEvent183Text02, 0, 270 },
    { 27, 1, 4, 1, { 0, 0, 0 }, gEvent183Text03, 0, 272 },
    { 55, 2, 1, 1, { 0, 0, 0 }, gEvent183Text04, 0, 400 },
    { 27, 2, 3, 1, { 0, 0, 0 }, gEvent183Text05, 0, 430 },
    { 55, 1, 1, 1, { 0, 0, 0 }, gEvent183Text06, 0, 460 },
    { 27, 2, 3, 1, { 0, 0, 0 }, gEvent183Text07, 0, 490 },
    { 55, 2, 1, 1, { 0, 0, 0 }, gEvent183Text08, 0, 550 },
    { 27, 0, 3, 1, { 0, 0, 0 }, gEvent183Text09, MSG_SCRIPT_FLAG_END, 750 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent183Script[10] = {
    { 0, 3, 1, 3, { 0, 0, 0 }, gEvent183Text00, 0, 95 },
    { 55, 3, 1, 3, { 0, 0, 0 }, gEvent183Text01, 0, 240 },
    { 27, 0, 3, 3, { 0, 0, 0 }, gEvent183Text02, 0, 270 },
    { 27, 1, 4, 3, { 0, 0, 0 }, gEvent183Text03, 0, 272 },
    { 55, 2, 1, 3, { 0, 0, 0 }, gEvent183Text04, 0, 400 },
    { 27, 2, 3, 3, { 0, 0, 0 }, gEvent183Text05, 0, 430 },
    { 55, 1, 1, 3, { 0, 0, 0 }, gEvent183Text06, 0, 460 },
    { 27, 2, 3, 3, { 0, 0, 0 }, gEvent183Text07, 0, 490 },
    { 55, 2, 1, 3, { 0, 0, 0 }, gEvent183Text08, 0, 550 },
    { 27, 0, 3, 3, { 0, 0, 0 }, gEvent183Text09, MSG_SCRIPT_FLAG_END, 750 },
};

#include "event_183_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent183Script[10] = {
    { 0, 3, 1, 1, { 0, 0, 0 }, &gEvent183Text00, 0, 95 },
    { 55, 3, 1, 1, { 0, 0, 0 }, &gEvent183Text01, 0, 240 },
    { 27, 0, 3, 1, { 0, 0, 0 }, &gEvent183Text02, 0, 270 },
    { 27, 1, 4, 1, { 0, 0, 0 }, &gEvent183Text03, 0, 272 },
    { 55, 2, 1, 1, { 0, 0, 0 }, &gEvent183Text04, 0, 400 },
    { 27, 2, 3, 1, { 0, 0, 0 }, &gEvent183Text05, 0, 430 },
    { 55, 1, 1, 1, { 0, 0, 0 }, &gEvent183Text06, 0, 460 },
    { 27, 2, 3, 1, { 0, 0, 0 }, &gEvent183Text07, 0, 490 },
    { 55, 2, 1, 1, { 0, 0, 0 }, &gEvent183Text08, 0, 550 },
    { 27, 0, 3, 1, { 0, 0, 0 }, &gEvent183Text09, MSG_SCRIPT_FLAG_END, 750 },
};
#endif

static const EvSoundCue sEvent183SoundCues[4] = {
    { SONG_BGM_EVENT2, 0, 0, 0 },
    { SONG_SND_364, 100, 0, 0 },
    { SONG_EV_WARPIN, 600, 0, 0 },
    { SONG_BGM_EVENT2, 805, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent183Camera[7] = {
    { -65406, 61440, 27136, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65346, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 60, { 0, 0 }, NULL },
    { -65326, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 30, { 0, 0 }, NULL },
    { -65036, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65016, 65536, 23296, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 15, { 0, 0 }, NULL },
    { -65006, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent183Track0[5] = {
    { 718, 500, { 0, 0 }, 54016, 40448, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 702, 520, { 0, 0 }, 62464, 33024, 0, 696, { 0, 0 }, 4163, NULL, NULL },
    { 702, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 719, 714, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 696, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent183Track1[8] = {
    { 889, 190, { 0, 0 }, 11776, 44800, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 905, 300, { 0, 0 }, 70144, 28672, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 906, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 889, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 900, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 901, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaFadeOut, NULL },
    { 902, 1000, { 0, 0 }, 11776, 44800, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 889, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent183Track2[4] = {
    { 107, 100, { 0, 0 }, 69120, 27904, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 107, 190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaBlendUp, NULL },
    { 107, 500, { 0, 0 }, 11776, 44800, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 4, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent183Tracks[3] = {
    { sEvent183Track0, 65, { 0, 0, 0 } },
    { sEvent183Track1, 83, { 0, 0, 0 } },
    { sEvent183Track2, 0, { 0, 0, 0 } },
};

const EventSequenceDef gEvent183 = {
    3,
    { 0, 0, 0 },
    sEvent183Tracks,
    sEvent183Camera,
    sEvent183Script,
    sEvent183SoundCues,
    NULL,
    810,
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
#include "event_184_text.inc"
static const MessageScriptEntry sEvent184Script[18] = {
    { 55, 3, 1, 1, { 0, 0, 0 }, gEvent184Text00, 0, 230 },
    { 55, 2, 4, 1, { 0, 0, 0 }, gEvent184Text01, 0, 232 },
    { 55, 3, 3, 1, { 0, 0, 0 }, gEvent184Text02, 0, 600 },
    { 55, 3, 3, 1, { 0, 0, 0 }, gEvent184Text03, 0, 900 },
    { 55, 1, 4, 1, { 0, 0, 0 }, gEvent184Text04, 0, 902 },
    { 55, 0, 3, 1, { 0, 0, 0 }, gEvent184Text05, 0, 1000 },
    { 20, 1, 1, 1, { 0, 0, 0 }, gEvent184Text06, 0, 1050 },
    { 20, 0, 1, 1, { 0, 0, 0 }, gEvent184Text07, 0, 1230 },
    { 27, 0, 0, 1, { 0, 0, 0 }, gEvent184Text08, 0, 1260 },
    { 20, 0, 1, 1, { 0, 0, 0 }, gEvent184Text09, 0, 1290 },
    { 20, 0, 4, 1, { 0, 0, 0 }, gEvent184Text10, 0, 1292 },
    { 20, 1, 4, 1, { 0, 0, 0 }, gEvent184Text11, 0, 1294 },
    { 55, 3, 3, 1, { 0, 0, 0 }, gEvent184Text12, 0, 1320 },
    { 20, 1, 1, 1, { 0, 0, 0 }, gEvent184Text13, 0, 1380 },
    { 55, 3, 3, 1, { 0, 0, 0 }, gEvent184Text14, 0, 1460 },
    { 20, 0, 1, 1, { 0, 0, 0 }, gEvent184Text15, 0, 1500 },
    { 20, 1, 4, 1, { 0, 0, 0 }, gEvent184Text16, 0, 1502 },
    { 55, 3, 3, 1, { 0, 0, 0 }, gEvent184Text17, MSG_SCRIPT_FLAG_END, 1650 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent184Script[18] = {
    { 55, 3, 1, 3, { 0, 0, 0 }, gEvent184Text00, 0, 230 },
    { 55, 2, 4, 3, { 0, 0, 0 }, gEvent184Text01, 0, 232 },
    { 55, 3, 3, 3, { 0, 0, 0 }, gEvent184Text02, 0, 600 },
    { 55, 3, 3, 3, { 0, 0, 0 }, gEvent184Text03, 0, 900 },
    { 55, 1, 4, 3, { 0, 0, 0 }, gEvent184Text04, 0, 902 },
    { 55, 0, 3, 3, { 0, 0, 0 }, gEvent184Text05, 0, 1000 },
    { 20, 1, 1, 3, { 0, 0, 0 }, gEvent184Text06, 0, 1050 },
    { 20, 0, 1, 3, { 0, 0, 0 }, gEvent184Text07, 0, 1230 },
    { 27, 0, 0, 3, { 0, 0, 0 }, gEvent126Text11, 0, 1260 },
    { 20, 0, 1, 3, { 0, 0, 0 }, gEvent184Text09, 0, 1290 },
    { 20, 0, 4, 3, { 0, 0, 0 }, gEvent184Text10, 0, 1292 },
    { 20, 1, 4, 3, { 0, 0, 0 }, gEvent184Text11, 0, 1294 },
    { 55, 3, 3, 3, { 0, 0, 0 }, gEvent184Text12, 0, 1320 },
    { 20, 1, 1, 3, { 0, 0, 0 }, gEvent184Text13, 0, 1380 },
    { 55, 3, 3, 3, { 0, 0, 0 }, gEvent184Text14, 0, 1460 },
    { 20, 0, 1, 3, { 0, 0, 0 }, gEvent184Text15, 0, 1500 },
    { 20, 1, 4, 3, { 0, 0, 0 }, gEvent184Text16, 0, 1502 },
    { 55, 3, 3, 3, { 0, 0, 0 }, gEvent184Text17, MSG_SCRIPT_FLAG_END, 1650 },
};

#include "event_184_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent184Script[18] = {
    { 55, 3, 1, 1, { 0, 0, 0 }, &gEvent184Text00, 0, 230 },
    { 55, 2, 4, 1, { 0, 0, 0 }, &gEvent184Text01, 0, 232 },
    { 55, 3, 3, 1, { 0, 0, 0 }, &gEvent184Text02, 0, 600 },
    { 55, 3, 3, 1, { 0, 0, 0 }, &gEvent184Text03, 0, 900 },
    { 55, 1, 4, 1, { 0, 0, 0 }, &gEvent184Text04, 0, 902 },
    { 55, 0, 3, 1, { 0, 0, 0 }, &gEvent184Text05, 0, 1000 },
    { 20, 1, 1, 1, { 0, 0, 0 }, &gEvent184Text06, 0, 1050 },
    { 20, 0, 1, 1, { 0, 0, 0 }, &gEvent184Text07, 0, 1230 },
    { 27, 0, 0, 1, { 0, 0, 0 }, &gEvent184Text08, 0, 1260 },
    { 20, 0, 1, 1, { 0, 0, 0 }, &gEvent184Text09, 0, 1290 },
    { 20, 0, 4, 1, { 0, 0, 0 }, &gEvent184Text10, 0, 1292 },
    { 20, 1, 4, 1, { 0, 0, 0 }, &gEvent184Text11, 0, 1294 },
    { 55, 3, 3, 1, { 0, 0, 0 }, &gEvent184Text12, 0, 1320 },
    { 20, 1, 1, 1, { 0, 0, 0 }, &gEvent184Text13, 0, 1380 },
    { 55, 3, 3, 1, { 0, 0, 0 }, &gEvent184Text14, 0, 1460 },
    { 20, 0, 1, 1, { 0, 0, 0 }, &gEvent184Text15, 0, 1500 },
    { 20, 1, 4, 1, { 0, 0, 0 }, &gEvent184Text16, 0, 1502 },
    { 55, 3, 3, 1, { 0, 0, 0 }, &gEvent184Text17, MSG_SCRIPT_FLAG_END, 1650 },
};
#endif

static const EvSoundCue sEvent184SoundCues[5] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_EV_WARPOUT, 170, 0, 0 },
    { SONG_SND_368, 1530, 0, 0 },
    { SONG_SND_381, 1680, 0, 0 },
    { SONG_BGM_EVENT_XIII, 1710, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent184Camera[6] = {
    { -65196, 46592, 59136, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65016, 83456, 69888, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -64935, 46592, 59136, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -63906, 57088, 59136, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -63536, 30976, 110848, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EventBgEffectEntry sEvent184BgEffects[5] = {
    { 1530, 0, 0, 0, 0 },
    { 1630, 0, 0, 0, 0x14 },
    { 3310, 0, 0, 0, 0 },
    { 3380, 0, 0, 0, 0x2 },
    { 3500, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent184Track0[10] = {
    { 902, 170, { 0, 0 }, 111616, 23040, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 903, 280, { 0, 0 }, 47104, 65792, 0, 0, { 0, 0 }, 2, EventCharaFadeIn, NULL },
    { 903, 521, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 889, 595, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 896, 605, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 889, 1390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 896, 1440, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 896, 1560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 896, 1600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaFadeOut, NULL },
    { 902, 2000, { 0, 0 }, 111616, 23040, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent184Track1[10] = {
    { 486, 601, { 0, 0 }, 86528, 73216, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 502, 720, { 0, 0 }, 65536, 61440, 0, 486, { 0, 0 }, 3, NULL, NULL },
    { 486, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 485, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 509, 1330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 485, 1350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 499, 1470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 485, 1560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 485, 1600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaFadeOut, NULL },
    { 486, 2000, { 0, 0 }, 111616, 23040, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent184Track2[10] = {
    { 696, 601, { 0, 0 }, 82432, 83456, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 712, 700, { 0, 0 }, 65024, 73984, 0, 696, { 0, 0 }, 3, NULL, NULL },
    { 696, 750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 696, 880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 696, 1070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 696, 1200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 696, 1540, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 712, 1560, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 712, 1600, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, EventCharaFadeOut, NULL },
    { 696, 2000, { 0, 0 }, 111616, 23040, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent184Track3[3] = {
    { 928, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 927, 330, { 0, 0 }, 44544, 55552, 0, 0, { 0, 0 }, 16658, NULL, NULL },
    { 928, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaTrack sEvent184Tracks[4] = {
    { sEvent184Track0, 83, { 0, 0, 0 } },
    { sEvent184Track1, 43, { 0, 0, 0 } },
    { sEvent184Track2, 65, { 0, 0, 0 } },
    { sEvent184Track3, 93, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent184 = {
    4,
    { 0, 0, 0 },
    sEvent184Tracks,
    sEvent184Camera,
    sEvent184Script,
    sEvent184SoundCues,
    sEvent184BgEffects,
    1710,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    185,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent184 = {
    4,
    { 0, 0, 0 },
    sEvent184Tracks,
    sEvent184Camera,
    sEvent184Script,
    sEvent184SoundCues,
    sEvent184BgEffects,
    1710,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    183,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_185_text.inc"
static const MessageScriptEntry sEvent185Script[25] = {
    { 56, 0, 0, 1, { 0, 0, 0 }, gEvent185Text00, MSG_SCRIPT_FLAG_SILHOUETTE, 141 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent185Text01, 0, 170 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent185Text02, 0, 260 },
    { 56, 0, 0, 1, { 0, 0, 0 }, gEvent185Text03, 0, 290 },
    { 56, 1, 0, 1, { 0, 0, 0 }, gEvent185Text04, 0, 390 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent185Text05, 0, 420 },
    { 56, 1, 0, 1, { 0, 0, 0 }, gEvent185Text06, 0, 450 },
    { 26, 3, 3, 1, { 0, 0, 0 }, gEvent185Text07, 0, 660 },
    { 56, 0, 0, 1, { 0, 0, 0 }, gEvent185Text08, 0, 690 },
    { 56, 2, 0, 1, { 0, 0, 0 }, gEvent185Text09, 0, 1240 },
    { 61, 0, 2, 1, { 0, 0, 0 }, gEvent185Text10, MSG_SCRIPT_FLAG_SILHOUETTE, 1290 },
    { 61, 1, 3, 1, { 0, 0, 0 }, gEvent185Text11, 0, 1530 },
    { 26, 3, 1, 1, { 0, 0, 0 }, gEvent185Text12, 0, 1730 },
    { 61, 1, 3, 1, { 0, 0, 0 }, gEvent185Text13, 0, 1760 },
    { 61, 2, 3, 1, { 0, 0, 0 }, gEvent185Text14, 0, 1940 },
    { 26, 3, 1, 1, { 0, 0, 0 }, gEvent185Text15, 0, 1970 },
    { 61, 1, 3, 1, { 0, 0, 0 }, gEvent185Text16, 0, 2000 },
    { 26, 4, 1, 1, { 0, 0, 0 }, gEvent185Text17, 0, 2150 },
    { 26, 4, 4, 1, { 0, 0, 0 }, gEvent185Text18, 0, 2152 },
    { 26, 3, 1, 1, { 0, 0, 0 }, gEvent185Text19, 0, 2220 },
    { 61, 0, 3, 1, { 0, 0, 0 }, gEvent185Text20, 0, 2300 },
    { 61, 0, 3, 1, { 0, 0, 0 }, gEvent185Text21, 0, 2400 },
    { 61, 0, 4, 1, { 0, 0, 0 }, gEvent185Text22, 0, 2402 },
    { 61, 1, 4, 1, { 0, 0, 0 }, gEvent185Text23, 0, 2404 },
    { 26, 0, 1, 1, { 0, 0, 0 }, gEvent185Text24, MSG_SCRIPT_FLAG_END, 2550 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent185Script[25] = {
    { 56, 0, 0, 3, { 0, 0, 0 }, gEvent185Text00, MSG_SCRIPT_FLAG_SILHOUETTE, 141 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent000Text21, 0, 170 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent185Text02, 0, 260 },
    { 56, 0, 0, 3, { 0, 0, 0 }, gEvent185Text03, 0, 290 },
    { 56, 1, 0, 3, { 0, 0, 0 }, gEvent185Text04, 0, 390 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent185Text05, 0, 420 },
    { 56, 1, 0, 3, { 0, 0, 0 }, gEvent185Text06, 0, 450 },
    { 26, 3, 3, 3, { 0, 0, 0 }, gEvent185Text07, 0, 660 },
    { 56, 0, 0, 3, { 0, 0, 0 }, gEvent185Text08, 0, 690 },
    { 56, 2, 0, 3, { 0, 0, 0 }, gEvent185Text09, 0, 1240 },
    { 61, 0, 2, 3, { 0, 0, 0 }, gEvent185Text10, MSG_SCRIPT_FLAG_SILHOUETTE, 1290 },
    { 61, 1, 3, 3, { 0, 0, 0 }, gEvent185Text11, 0, 1530 },
    { 26, 3, 1, 3, { 0, 0, 0 }, gEvent185Text12, 0, 1730 },
    { 61, 1, 3, 3, { 0, 0, 0 }, gEvent185Text13, 0, 1760 },
    { 61, 2, 3, 3, { 0, 0, 0 }, gEvent185Text14, 0, 1940 },
    { 26, 3, 1, 3, { 0, 0, 0 }, gEvent185Text15, 0, 1970 },
    { 61, 1, 3, 3, { 0, 0, 0 }, gEvent185Text16, 0, 2000 },
    { 26, 4, 1, 3, { 0, 0, 0 }, gEvent185Text17, 0, 2150 },
    { 26, 4, 4, 3, { 0, 0, 0 }, gEvent185Text18, 0, 2152 },
    { 26, 3, 1, 3, { 0, 0, 0 }, gEvent185Text19, 0, 2220 },
    { 61, 0, 3, 3, { 0, 0, 0 }, gEvent185Text20, 0, 2300 },
    { 61, 0, 3, 3, { 0, 0, 0 }, gEvent185Text21, 0, 2400 },
    { 61, 0, 4, 3, { 0, 0, 0 }, gEvent185Text22, 0, 2402 },
    { 61, 1, 4, 3, { 0, 0, 0 }, gEvent185Text23, 0, 2404 },
    { 26, 0, 1, 3, { 0, 0, 0 }, gEvent185Text24, MSG_SCRIPT_FLAG_END, 2550 },
};

#include "event_185_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent185Script[25] = {
    { 56, 0, 0, 1, { 0, 0, 0 }, &gEvent185Text00, MSG_SCRIPT_FLAG_SILHOUETTE, 141 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent185Text01, 0, 170 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent185Text02, 0, 260 },
    { 56, 0, 0, 1, { 0, 0, 0 }, &gEvent185Text03, 0, 290 },
    { 56, 1, 0, 1, { 0, 0, 0 }, &gEvent185Text04, 0, 390 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent185Text05, 0, 420 },
    { 56, 1, 0, 1, { 0, 0, 0 }, &gEvent185Text06, 0, 450 },
    { 26, 3, 3, 1, { 0, 0, 0 }, &gEvent185Text07, 0, 660 },
    { 56, 0, 0, 1, { 0, 0, 0 }, &gEvent185Text08, 0, 690 },
    { 56, 2, 0, 1, { 0, 0, 0 }, &gEvent185Text09, 0, 1240 },
    { 61, 0, 2, 1, { 0, 0, 0 }, &gEvent185Text10, MSG_SCRIPT_FLAG_SILHOUETTE, 1290 },
    { 61, 1, 3, 1, { 0, 0, 0 }, &gEvent185Text11, 0, 1530 },
    { 26, 3, 1, 1, { 0, 0, 0 }, &gEvent185Text12, 0, 1730 },
    { 61, 1, 3, 1, { 0, 0, 0 }, &gEvent185Text13, 0, 1760 },
    { 61, 2, 3, 1, { 0, 0, 0 }, &gEvent185Text14, 0, 1940 },
    { 26, 3, 1, 1, { 0, 0, 0 }, &gEvent185Text15, 0, 1970 },
    { 61, 1, 3, 1, { 0, 0, 0 }, &gEvent185Text16, 0, 2000 },
    { 26, 4, 1, 1, { 0, 0, 0 }, &gEvent185Text17, 0, 2150 },
    { 26, 4, 4, 1, { 0, 0, 0 }, &gEvent185Text18, 0, 2152 },
    { 26, 3, 1, 1, { 0, 0, 0 }, &gEvent185Text19, 0, 2220 },
    { 61, 0, 3, 1, { 0, 0, 0 }, &gEvent185Text20, 0, 2300 },
    { 61, 0, 3, 1, { 0, 0, 0 }, &gEvent185Text21, 0, 2400 },
    { 61, 0, 4, 1, { 0, 0, 0 }, &gEvent185Text22, 0, 2402 },
    { 61, 1, 4, 1, { 0, 0, 0 }, &gEvent185Text23, 0, 2404 },
    { 26, 0, 1, 1, { 0, 0, 0 }, &gEvent185Text24, MSG_SCRIPT_FLAG_END, 2550 },
};
#endif

static const EvSoundCue sEvent185SoundCues[7] = {
    { 65535, 0, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 289, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT_UNREST, 810, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_SND_382, 1900, 0, 0 },
    { SONG_BGM_EVENT4, 1965, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_EV_HUKUROUJUMP, 2050, 0, 0 },
    { SONG_BGM_EVENT4, 2605, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent185Camera[9] = {
    { -64956, 175616, 68864, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64346, 175616, 63744, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -64326, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 20, { 0, 0 }, NULL },
    { -64294, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64284, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -64076, 185600, 65280, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 20, { 0, 0 }, NULL },
    { -63726, 179968, 61952, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -62966, 176640, 60160, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent185Track0[33] = {
    { 515, 1, { 0, 0 }, 141568, 92416, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 518, 140, { 0, 0 }, 174592, 76288, 0, 515, { 0, 0 }, 67, NULL, NULL },
    { 515, 190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 515, 415, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 538, 422, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 532, 530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 532, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 532, 630, { 0, 0 }, 174592, 76288, -6912, 515, { 0, 0 }, 4163, NULL, NULL },
    { 556, 1250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 532, 1260, { 0, 0 }, 186112, 71168, 0, 515, { 0, 0 }, 67, NULL, NULL },
    { 556, 1282, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 1300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 532, 1350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 532, 1370, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 1400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 1410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 1460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 1560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 1690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 515, 1800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 518, 1850, { 0, 0 }, 178944, 65536, 0, 515, { 0, 0 }, 3, NULL, NULL },
    { 515, 1870, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 536, 1930, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 2050, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 554, 2060, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 4, NULL, NULL },
    { 554, 2430, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 556, 2445, { 0, 0 }, 180992, 66560, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 515, 2460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 536, 2490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 2535, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 558, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent185Track1[8] = {
    { 920, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 920, 721, { 0, 0 }, 137728, 59136, 0, 0, { 0, 0 }, 16642, NULL, NULL },
    { 920, 800, { 0, 0 }, 166912, 53760, 0, 920, { 0, 0 }, 275, NULL, NULL },
    { 920, 1050, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 272, EventCharaCircleSlow, NULL },
    { 920, 1130, { 0, 0 }, 174592, 52992, 0, 920, { 0, 0 }, 275, NULL, NULL },
    { 920, 1160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 920, 1190, { 0, 0 }, 174592, 57344, 0, 0, { 0, 0 }, 4355, EventCharaFadeOut, NULL },
    { 920, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent185Track2[13] = {
    { 746, 1350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8258, NULL, NULL },
    { 746, 1356, { 0, 0 }, 148224, 78336, 0, 0, { 0, 0 }, 16450, NULL, NULL },
    { 754, 1480, { 0, 0 }, 174080, 64000, 0, 746, { 0, 0 }, 67, NULL, NULL },
    { 746, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 745, 1840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 745, 1890, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateQuestionTask },
    { 749, 1920, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaHop, NULL },
    { 745, 2070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 745, 2120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 745, 2250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 752, 2330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 748, 2480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 745, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent185Track3[3] = {
    { 591, 2549, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 603, 5000, { 0, 0 }, 180992, 66560, 0, 0, { 0, 0 }, 16658, NULL, NULL },
    { 591, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32770, NULL, NULL },
};

static const EventCharaTrack sEvent185Tracks[4] = {
    { sEvent185Track0, 44, { 0, 0, 0 } },
    { sEvent185Track1, 87, { 0, 0, 0 } },
    { sEvent185Track2, 69, { 0, 0, 0 } },
    { sEvent185Track3, 50, { 0, 0, 0 } },
};

const EventSequenceDef gEvent185 = {
    4,
    { 0, 0, 0 },
    sEvent185Tracks,
    sEvent185Camera,
    sEvent185Script,
    sEvent185SoundCues,
    NULL,
    2610,
    1,
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

#ifdef VERSION_US
#include "event_186_text.inc"
static const MessageScriptEntry sEvent186Script[21] = {
    { 26, 3, 3, 1, { 0, 0, 0 }, gEvent186Text00, 0, 370 },
    { 26, 0, 4, 1, { 0, 0, 0 }, gEvent186Text01, 0, 372 },
    { 26, 3, 1, 1, { 0, 0, 0 }, gEvent186Text02, 0, 450 },
    { 56, 0, 0, 1, { 0, 0, 0 }, gEvent186Text03, 0, 480 },
    { 56, 0, 1, 1, { 0, 0, 0 }, gEvent186Text04, 0, 690 },
    { 56, 1, 1, 1, { 0, 0, 0 }, gEvent186Text05, 0, 980 },
    { 26, 0, 3, 1, { 0, 0, 0 }, gEvent186Text06, 0, 1010 },
    { 26, 0, 3, 1, { 0, 0, 0 }, gEvent186Text07, 0, 1120 },
    { 26, 0, 4, 1, { 0, 0, 0 }, gEvent186Text08, 0, 1122 },
    { 26, 1, 3, 1, { 0, 0, 0 }, gEvent186Text09, 0, 1240 },
    { 26, 0, 4, 1, { 0, 0, 0 }, gEvent186Text10, 0, 1242 },
    { 56, 0, 1, 1, { 0, 0, 0 }, gEvent186Text11, 0, 1430 },
    { 52, 0, 1, 1, { 0, 0, 0 }, gEvent186Text12, 0, 1600 },
    { 26, 0, 3, 1, { 0, 0, 0 }, gEvent186Text13, 0, 1630 },
    { 52, 0, 1, 1, { 0, 0, 0 }, gEvent186Text14, 0, 1660 },
    { 26, 0, 3, 1, { 0, 0, 0 }, gEvent186Text15, 0, 1690 },
    { 52, 0, 1, 1, { 0, 0, 0 }, gEvent186Text16, 0, 1720 },
    { 52, 0, 1, 1, { 0, 0, 0 }, gEvent186Text17, 0, 1950 },
    { 26, 0, 3, 1, { 0, 0, 0 }, gEvent186Text18, 0, 1980 },
    { 52, 0, 1, 1, { 0, 0, 0 }, gEvent186Text19, 0, 2010 },
    { 26, 3, 3, 1, { 0, 0, 0 }, gEvent186Text20, MSG_SCRIPT_FLAG_END, 2085 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent186Script[21] = {
    { 26, 3, 3, 3, { 0, 0, 0 }, gEvent186Text00, 0, 370 },
    { 26, 0, 4, 3, { 0, 0, 0 }, gEvent186Text01, 0, 372 },
    { 26, 3, 1, 3, { 0, 0, 0 }, gEvent186Text02, 0, 450 },
    { 56, 0, 0, 3, { 0, 0, 0 }, gEvent186Text03, 0, 480 },
    { 56, 0, 1, 3, { 0, 0, 0 }, gEvent186Text04, 0, 690 },
    { 56, 1, 1, 3, { 0, 0, 0 }, gEvent186Text05, 0, 980 },
    { 26, 0, 3, 3, { 0, 0, 0 }, gEvent186Text06, 0, 1010 },
    { 26, 0, 3, 3, { 0, 0, 0 }, gEvent186Text07, 0, 1120 },
    { 26, 0, 4, 3, { 0, 0, 0 }, gEvent186Text08, 0, 1122 },
    { 26, 1, 3, 3, { 0, 0, 0 }, gEvent186Text09, 0, 1240 },
    { 26, 0, 4, 3, { 0, 0, 0 }, gEvent186Text10, 0, 1242 },
    { 56, 0, 1, 3, { 0, 0, 0 }, gEvent067Text01, 0, 1430 },
    { 52, 0, 1, 3, { 0, 0, 0 }, gEvent186Text12, 0, 1600 },
    { 26, 0, 3, 3, { 0, 0, 0 }, gEvent186Text13, 0, 1630 },
    { 52, 0, 1, 3, { 0, 0, 0 }, gEvent186Text14, 0, 1660 },
    { 26, 0, 3, 3, { 0, 0, 0 }, gEvent186Text15, 0, 1690 },
    { 52, 0, 1, 3, { 0, 0, 0 }, gEvent186Text16, 0, 1720 },
    { 52, 0, 1, 3, { 0, 0, 0 }, gEvent186Text17, 0, 1950 },
    { 26, 0, 3, 3, { 0, 0, 0 }, gEvent186Text18, 0, 1980 },
    { 52, 0, 1, 3, { 0, 0, 0 }, gEvent186Text19, 0, 2010 },
    { 26, 3, 3, 3, { 0, 0, 0 }, gEvent186Text20, MSG_SCRIPT_FLAG_END, 2085 },
};

#include "event_186_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent186Script[21] = {
    { 26, 3, 3, 1, { 0, 0, 0 }, &gEvent186Text00, 0, 370 },
    { 26, 0, 4, 1, { 0, 0, 0 }, &gEvent186Text01, 0, 372 },
    { 26, 3, 1, 1, { 0, 0, 0 }, &gEvent186Text02, 0, 450 },
    { 56, 0, 0, 1, { 0, 0, 0 }, &gEvent186Text03, 0, 480 },
    { 56, 0, 1, 1, { 0, 0, 0 }, &gEvent186Text04, 0, 690 },
    { 56, 1, 1, 1, { 0, 0, 0 }, &gEvent186Text05, 0, 980 },
    { 26, 0, 3, 1, { 0, 0, 0 }, &gEvent186Text06, 0, 1010 },
    { 26, 0, 3, 1, { 0, 0, 0 }, &gEvent186Text07, 0, 1120 },
    { 26, 0, 4, 1, { 0, 0, 0 }, &gEvent186Text08, 0, 1122 },
    { 26, 1, 3, 1, { 0, 0, 0 }, &gEvent186Text09, 0, 1240 },
    { 26, 0, 4, 1, { 0, 0, 0 }, &gEvent186Text10, 0, 1242 },
    { 56, 0, 1, 1, { 0, 0, 0 }, &gEvent186Text11, 0, 1430 },
    { 52, 0, 1, 1, { 0, 0, 0 }, &gEvent186Text12, 0, 1600 },
    { 26, 0, 3, 1, { 0, 0, 0 }, &gEvent186Text13, 0, 1630 },
    { 52, 0, 1, 1, { 0, 0, 0 }, &gEvent186Text14, 0, 1660 },
    { 26, 0, 3, 1, { 0, 0, 0 }, &gEvent186Text15, 0, 1690 },
    { 52, 0, 1, 1, { 0, 0, 0 }, &gEvent186Text16, 0, 1720 },
    { 52, 0, 1, 1, { 0, 0, 0 }, &gEvent186Text17, 0, 1950 },
    { 26, 0, 3, 1, { 0, 0, 0 }, &gEvent186Text18, 0, 1980 },
    { 52, 0, 1, 1, { 0, 0, 0 }, &gEvent186Text19, 0, 2010 },
    { 26, 3, 3, 1, { 0, 0, 0 }, &gEvent186Text20, MSG_SCRIPT_FLAG_END, 2085 },
};
#endif

static const EvSoundCue sEvent186SoundCues[9] = {
    { 65535, 0, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 482, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_SND_379, 630, 0, 0 },
    { SONG_SND_359, 710, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 1012, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_EV_WHITEOUT, 1460, 0, 0 },
    { SONG_BGM_TWILIGHTTOWN, 1510, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_SND_379, 2040, 0, 0 },
    { SONG_BGM_TWILIGHTTOWN, 2135, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent186Camera[7] = {
    { -65536, 61184, 107520, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, NULL },
    { -64956, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 80, { 0, 0 }, NULL },
    { -64076, 66816, 103936, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -64036, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 40, { 0, 0 }, NULL },
    { -64006, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -63536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 40, { 0, 0 }, NULL },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent186Track0[25] = {
    { 515, 1, { 0, 0 }, 26624, 134144, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 518, 160, { 0, 0 }, 60160, 116736, 0, 515, { 0, 0 }, 67, NULL, NULL },
    { 515, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 515, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 290, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 514, 330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 514, 410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 514, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 540, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 514, 560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 560, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 561, 930, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 561, 950, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 562, 960, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 1140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 530, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 1770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 1900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 515, 2080, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 538, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent186Track1[10] = {
    { 688, 630, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 688, 685, { 0, 0 }, 74240, 110336, 0, 0, { 0, 0 }, 16386, EventCharaFadeIn, NULL },
    { 694, 692, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 688, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 688, 1070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 688, 1270, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 688, 1400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 688, 1450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 688, 1501, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaBlendUp, NULL },
    { 688, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent186Track2[4] = {
    { 907, 1501, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 907, 2040, { 0, 0 }, 74240, 110336, 0, 0, { 0, 0 }, 16386, NULL, NULL },
    { 907, 2070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaFadeOut, NULL },
    { 907, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 73730, NULL, NULL },
};

static const EventCharaTrack sEvent186Tracks[3] = {
    { sEvent186Track0, 44, { 0, 0, 0 } },
    { sEvent186Track1, 64, { 0, 0, 0 } },
    { sEvent186Track2, 84, { 0, 0, 0 } },
};

const EventSequenceDef gEvent186 = {
    3,
    { 0, 0, 0 },
    sEvent186Tracks,
    sEvent186Camera,
    sEvent186Script,
    sEvent186SoundCues,
    NULL,
    2140,
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
#include "event_187_text.inc"
static const MessageScriptEntry sEvent187Script[13] = {
    { 26, 0, 0, 1, { 0, 0, 0 }, gEvent187Text00, 0, 410 },
    { 27, 0, 3, 1, { 0, 0, 0 }, gEvent187Text01, MSG_SCRIPT_FLAG_SILHOUETTE, 440 },
    { 27, 1, 3, 1, { 0, 0, 0 }, gEvent187Text02, 0, 750 },
    { 27, 1, 4, 1, { 0, 0, 0 }, gEvent187Text03, 0, 752 },
    { 26, 0, 0, 1, { 0, 0, 0 }, gEvent187Text04, 0, 780 },
    { 27, 1, 3, 1, { 0, 0, 0 }, gEvent187Text05, 0, 810 },
    { 26, 2, 0, 1, { 0, 0, 0 }, gEvent187Text06, 0, 860 },
    { 27, 0, 3, 1, { 0, 0, 0 }, gEvent187Text07, 0, 1040 },
    { 27, 1, 4, 1, { 0, 0, 0 }, gEvent187Text08, 0, 1042 },
    { 27, 2, 3, 1, { 0, 0, 0 }, gEvent187Text09, 0, 1070 },
    { 27, 0, 3, 1, { 0, 0, 0 }, gEvent187Text10, 0, 1260 },
    { 27, 2, 4, 1, { 0, 0, 0 }, gEvent187Text11, 0, 1263 },
    { 27, 2, 3, 1, { 0, 0, 0 }, gEvent187Text12, MSG_SCRIPT_FLAG_END, 1430 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent187Script[13] = {
    { 26, 0, 0, 3, { 0, 0, 0 }, gEvent187Text00, 0, 410 },
    { 27, 0, 3, 3, { 0, 0, 0 }, gEvent187Text01, MSG_SCRIPT_FLAG_SILHOUETTE, 440 },
    { 27, 1, 3, 3, { 0, 0, 0 }, gEvent187Text02, 0, 750 },
    { 27, 1, 4, 3, { 0, 0, 0 }, gEvent187Text03, 0, 752 },
    { 26, 0, 0, 3, { 0, 0, 0 }, gEvent187Text04, 0, 780 },
    { 27, 1, 3, 3, { 0, 0, 0 }, gEvent187Text05, 0, 810 },
    { 26, 2, 0, 3, { 0, 0, 0 }, gEvent187Text06, 0, 860 },
    { 27, 0, 3, 3, { 0, 0, 0 }, gEvent187Text07, 0, 1040 },
    { 27, 1, 4, 3, { 0, 0, 0 }, gEvent187Text08, 0, 1042 },
    { 27, 2, 3, 3, { 0, 0, 0 }, gEvent187Text09, 0, 1070 },
    { 27, 0, 3, 3, { 0, 0, 0 }, gEvent187Text10, 0, 1260 },
    { 27, 2, 4, 3, { 0, 0, 0 }, gEvent187Text11, 0, 1263 },
    { 27, 2, 3, 3, { 0, 0, 0 }, gEvent187Text12, MSG_SCRIPT_FLAG_END, 1430 },
};

#include "event_187_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent187Script[13] = {
    { 26, 0, 0, 1, { 0, 0, 0 }, &gEvent187Text00, 0, 410 },
    { 27, 0, 3, 1, { 0, 0, 0 }, &gEvent187Text01, MSG_SCRIPT_FLAG_SILHOUETTE, 440 },
    { 27, 1, 3, 1, { 0, 0, 0 }, &gEvent187Text02, 0, 750 },
    { 27, 1, 4, 1, { 0, 0, 0 }, &gEvent187Text03, 0, 752 },
    { 26, 0, 0, 1, { 0, 0, 0 }, &gEvent187Text04, 0, 780 },
    { 27, 1, 3, 1, { 0, 0, 0 }, &gEvent187Text05, 0, 810 },
    { 26, 2, 0, 1, { 0, 0, 0 }, &gEvent187Text06, 0, 860 },
    { 27, 0, 3, 1, { 0, 0, 0 }, &gEvent187Text07, 0, 1040 },
    { 27, 1, 4, 1, { 0, 0, 0 }, &gEvent187Text08, 0, 1042 },
    { 27, 2, 3, 1, { 0, 0, 0 }, &gEvent187Text09, 0, 1070 },
    { 27, 0, 3, 1, { 0, 0, 0 }, &gEvent187Text10, 0, 1260 },
    { 27, 2, 4, 1, { 0, 0, 0 }, &gEvent187Text11, 0, 1263 },
    { 27, 2, 3, 1, { 0, 0, 0 }, &gEvent187Text12, MSG_SCRIPT_FLAG_END, 1430 },
};
#endif

static const EvSoundCue sEvent187SoundCues[7] = {
    { 65535, 0, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 550, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT_UNREST, 1065, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_SND_377, 1130, 0, 0 },
    { SONG_BGM_EVENT2, 1140, 0, 0 },
    { SONG_SND_359, 1310, 0, 0 },
    { SONG_SND_359, 1350, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent187Camera[3] = {
    { -65416, 65024, 42496, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64436, 65024, 88576, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 260, { 0, 0 }, NULL },
    { -63536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EventBgEffectEntry sEvent187BgEffects[5] = {
    { 1072, 0, 0, 0, 0 },
    { 1130, 0, 50, 0, 0x4 },
    { 1226, 5, 44032, 74752, 0x1 },
    { 1230, 0, 0, 0, 0x2 },
    { 1265, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent187Track0[10] = {
    { 515, 460, { 0, 0 }, 73728, 99328, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 515, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 515, 540, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 625, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 1100, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 532, 1130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 532, 1180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 532, 1250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 1350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 560, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent187Track1[13] = {
    { 696, 510, { 0, 0 }, 29952, 117504, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 712, 670, { 0, 0 }, 56064, 93952, 0, 696, { 0, 0 }, 67, NULL, NULL },
    { 696, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 695, 735, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 707, 790, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 695, 880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 695, 1010, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 695, 1060, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 706, 1230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 695, 1261, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 706, 1265, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 695, 1310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 698, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent187Tracks[2] = {
    { sEvent187Track0, 44, { 0, 0, 0 } },
    { sEvent187Track1, 65, { 0, 0, 0 } },
};

const EventSequenceDef gEvent187 = {
    2,
    { 0, 0, 0 },
    sEvent187Tracks,
    sEvent187Camera,
    sEvent187Script,
    sEvent187SoundCues,
    sEvent187BgEffects,
    1490,
    0,
    1,
    0,
    0,
    0,
    0,
    172,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_188_text.inc"
static const MessageScriptEntry sEvent188Script[9] = {
    { 27, 5, 3, 1, { 0, 0, 0 }, gEvent188Text00, 0, 260 },
    { 27, 1, 3, 1, { 0, 0, 0 }, gEvent188Text01, 0, 470 },
    { 27, 5, 4, 1, { 0, 0, 0 }, gEvent188Text02, 0, 472 },
    { 26, 5, 0, 1, { 0, 0, 0 }, gEvent188Text03, 0, 500 },
    { 27, 5, 3, 1, { 0, 0, 0 }, gEvent188Text04, 0, 690 },
    { 27, 5, 3, 1, { 0, 0, 0 }, gEvent188Text05, 0, 800 },
    { 26, 5, 0, 1, { 0, 0, 0 }, gEvent188Text06, 0, 850 },
    { 27, 1, 3, 1, { 0, 0, 0 }, gEvent188Text07, 0, 880 },
    { 27, 4, 3, 1, { 0, 0, 0 }, gEvent188Text08, MSG_SCRIPT_FLAG_END, 1000 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent188Script[9] = {
    { 27, 5, 3, 3, { 0, 0, 0 }, gEvent188Text00, 0, 260 },
    { 27, 1, 3, 3, { 0, 0, 0 }, gEvent188Text01, 0, 470 },
    { 27, 5, 4, 3, { 0, 0, 0 }, gEvent188Text02, 0, 472 },
    { 26, 5, 0, 3, { 0, 0, 0 }, gEvent188Text03, 0, 500 },
    { 27, 5, 3, 3, { 0, 0, 0 }, gEvent188Text04, 0, 690 },
    { 27, 5, 3, 3, { 0, 0, 0 }, gEvent188Text05, 0, 800 },
    { 26, 5, 0, 3, { 0, 0, 0 }, gEvent188Text06, 0, 850 },
    { 27, 1, 3, 3, { 0, 0, 0 }, gEvent188Text07, 0, 880 },
    { 27, 4, 3, 3, { 0, 0, 0 }, gEvent188Text08, MSG_SCRIPT_FLAG_END, 1000 },
};

#include "event_188_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent188Script[9] = {
    { 27, 5, 3, 1, { 0, 0, 0 }, &gEvent188Text00, 0, 260 },
    { 27, 1, 3, 1, { 0, 0, 0 }, &gEvent188Text01, 0, 470 },
    { 27, 5, 4, 1, { 0, 0, 0 }, &gEvent188Text02, 0, 472 },
    { 26, 5, 0, 1, { 0, 0, 0 }, &gEvent188Text03, 0, 500 },
    { 27, 5, 3, 1, { 0, 0, 0 }, &gEvent188Text04, 0, 690 },
    { 27, 5, 3, 1, { 0, 0, 0 }, &gEvent188Text05, 0, 800 },
    { 26, 5, 0, 1, { 0, 0, 0 }, &gEvent188Text06, 0, 850 },
    { 27, 1, 3, 1, { 0, 0, 0 }, &gEvent188Text07, 0, 880 },
    { 27, 4, 3, 1, { 0, 0, 0 }, &gEvent188Text08, MSG_SCRIPT_FLAG_END, 1000 },
};
#endif

static const EvSoundCue sEvent188SoundCues[4] = {
    { 65535, 0, 0, 0 },
    { SONG_BGM_EVENT_SILENCE, 465, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_SND_379, 1080, 0, 0 },
    { SONG_BGM_EVENT_SILENCE, 1195, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent188Camera[1] = {
    { -64537, 65024, 88576, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent188Track0[5] = {
    { 561, 150, { 0, 0 }, 73728, 99328, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 562, 165, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 290, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent188Track1[5] = {
    { 705, 100, { 0, 0 }, 56064, 93952, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 705, 530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 1048901, NULL, NULL },
    { 705, 1080, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 1048901, NULL, NULL },
    { 705, 1200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 1048896, EventCharaFadeOut, NULL },
    { 705, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98370, NULL, NULL },
};

static const EventCharaKeyframe sEvent188Track2[3] = {
    { 928, 529, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 928, 660, { 0, 0 }, 54528, 86784, 0, 0, { 0, 0 }, 16642, NULL, NULL },
    { 928, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaTrack sEvent188Tracks[3] = {
    { sEvent188Track0, 44, { 0, 0, 0 } },
    { sEvent188Track1, 65, { 0, 0, 0 } },
    { sEvent188Track2, 93, { 0, 0, 0 } },
};

const EventSequenceDef gEvent188 = {
    3,
    { 0, 0, 0 },
    sEvent188Tracks,
    sEvent188Camera,
    sEvent188Script,
    sEvent188SoundCues,
    NULL,
    1200,
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
#include "event_189_text.inc"
static const MessageScriptEntry sEvent189Script[42] = {
    { 26, 0, 1, 1, { 0, 0, 0 }, gEvent189Text00, 0, 190 },
    { 60, 0, 3, 1, { 0, 0, 0 }, gEvent189Text01, 0, 290 },
    { 26, 0, 1, 1, { 0, 0, 0 }, gEvent189Text02, 0, 390 },
    { 60, 2, 3, 1, { 0, 0, 0 }, gEvent189Text03, 0, 420 },
    { 26, 0, 1, 1, { 0, 0, 0 }, gEvent189Text04, 0, 450 },
    { 60, 0, 3, 1, { 0, 0, 0 }, gEvent189Text05, 0, 530 },
    { 26, 3, 0, 1, { 0, 0, 0 }, gEvent189Text06, 0, 900 },
    { 26, 2, 1, 1, { 0, 0, 0 }, gEvent189Text07, 0, 1010 },
    { 60, 1, 3, 1, { 0, 0, 0 }, gEvent189Text08, 0, 1040 },
    { 26, 0, 1, 1, { 0, 0, 0 }, gEvent189Text09, 0, 1070 },
    { 26, 0, 1, 1, { 0, 0, 0 }, gEvent189Text10, 0, 1290 },
    { 26, 0, 4, 1, { 0, 0, 0 }, gEvent189Text11, 0, 1292 },
    { 60, 0, 3, 1, { 0, 0, 0 }, gEvent189Text12, 0, 1320 },
    { 26, 1, 1, 1, { 0, 0, 0 }, gEvent189Text13, 0, 1350 },
    { 60, 0, 3, 1, { 0, 0, 0 }, gEvent189Text14, 0, 1380 },
    { 60, 0, 3, 1, { 0, 0, 0 }, gEvent189Text15, 0, 1560 },
    { 60, 0, 4, 1, { 0, 0, 0 }, gEvent189Text16, 0, 1562 },
    { 60, 0, 3, 1, { 0, 0, 0 }, gEvent189Text17, 0, 1740 },
    { 60, 0, 4, 1, { 0, 0, 0 }, gEvent189Text18, 0, 1742 },
    { 26, 0, 1, 1, { 0, 0, 0 }, gEvent189Text19, 0, 1770 },
    { 26, 0, 1, 1, { 0, 0, 0 }, gEvent189Text20, 0, 1970 },
    { 60, 0, 3, 1, { 0, 0, 0 }, gEvent189Text21, 0, 2000 },
    { 60, 0, 4, 1, { 0, 0, 0 }, gEvent189Text22, 0, 2002 },
    { 60, 0, 3, 1, { 0, 0, 0 }, gEvent189Text23, 0, 2100 },
    { 26, 1, 1, 1, { 0, 0, 0 }, gEvent189Text24, 0, 2500 },
    { 60, 0, 2, 1, { 0, 0, 0 }, gEvent189Text25, 0, 2530 },
    { 26, 1, 1, 1, { 0, 0, 0 }, gEvent189Text26, 0, 2880 },
    { 26, 1, 4, 1, { 0, 0, 0 }, gEvent189Text27, 0, 2882 },
    { 26, 1, 1, 1, { 0, 0, 0 }, gEvent189Text28, 0, 3000 },
    { 26, 1, 4, 1, { 0, 0, 0 }, gEvent189Text29, 0, 3002 },
    { 26, 1, 1, 1, { 0, 0, 0 }, gEvent189Text30, 0, 3070 },
    { 26, 0, 1, 1, { 0, 0, 0 }, gEvent189Text31, 0, 3170 },
    { 60, 2, 2, 1, { 0, 0, 0 }, gEvent189Text32, 0, 3200 },
    { 26, 1, 1, 1, { 0, 0, 0 }, gEvent189Text33, 0, 3230 },
    { 60, 1, 2, 1, { 0, 0, 0 }, gEvent189Text34, 0, 3260 },
    { 26, 1, 1, 1, { 0, 0, 0 }, gEvent189Text35, 0, 3290 },
    { 60, 1, 2, 1, { 0, 0, 0 }, gEvent189Text36, 0, 3310 },
    { 60, 1, 4, 1, { 0, 0, 0 }, gEvent189Text37, 0, 3312 },
    { 26, 0, 1, 1, { 0, 0, 0 }, gEvent189Text38, 0, 3360 },
    { 60, 2, 2, 1, { 0, 0, 0 }, gEvent189Text39, 0, 3390 },
    { 26, 4, 1, 1, { 0, 0, 0 }, gEvent189Text40, 0, 3420 },
    { 26, 0, 2, 1, { 0, 0, 0 }, gEvent189Text41, MSG_SCRIPT_FLAG_END, 3560 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent189Script[42] = {
    { 26, 0, 1, 3, { 0, 0, 0 }, gEvent189Text00, 0, 190 },
    { 60, 0, 3, 3, { 0, 0, 0 }, gEvent189Text01, 0, 290 },
    { 26, 0, 1, 3, { 0, 0, 0 }, gEvent189Text02, 0, 390 },
    { 60, 2, 3, 3, { 0, 0, 0 }, gEvent100Text07, 0, 420 },
    { 26, 0, 1, 3, { 0, 0, 0 }, gEvent189Text04, 0, 450 },
    { 60, 0, 3, 3, { 0, 0, 0 }, gEvent189Text05, 0, 530 },
    { 26, 3, 0, 3, { 0, 0, 0 }, gEvent189Text06, 0, 900 },
    { 26, 2, 1, 3, { 0, 0, 0 }, gEvent189Text07, 0, 1010 },
    { 60, 1, 3, 3, { 0, 0, 0 }, gEvent189Text08, 0, 1040 },
    { 26, 0, 1, 3, { 0, 0, 0 }, gEvent189Text09, 0, 1070 },
    { 26, 0, 1, 3, { 0, 0, 0 }, gEvent189Text10, 0, 1290 },
    { 26, 0, 4, 3, { 0, 0, 0 }, gEvent189Text11, 0, 1292 },
    { 60, 0, 3, 3, { 0, 0, 0 }, gEvent189Text12, 0, 1320 },
    { 26, 1, 1, 3, { 0, 0, 0 }, gEvent189Text13, 0, 1350 },
    { 60, 0, 3, 3, { 0, 0, 0 }, gEvent189Text14, 0, 1380 },
    { 60, 0, 3, 3, { 0, 0, 0 }, gEvent189Text15, 0, 1560 },
    { 60, 0, 4, 3, { 0, 0, 0 }, gEvent189Text16, 0, 1562 },
    { 60, 0, 3, 3, { 0, 0, 0 }, gEvent189Text17, 0, 1740 },
    { 60, 0, 4, 3, { 0, 0, 0 }, gEvent189Text18, 0, 1742 },
    { 26, 0, 1, 3, { 0, 0, 0 }, gEvent189Text19, 0, 1770 },
    { 26, 0, 1, 3, { 0, 0, 0 }, gEvent189Text20, 0, 1970 },
    { 60, 0, 3, 3, { 0, 0, 0 }, gEvent189Text21, 0, 2000 },
    { 60, 0, 4, 3, { 0, 0, 0 }, gEvent189Text22, 0, 2002 },
    { 60, 0, 3, 3, { 0, 0, 0 }, gEvent189Text23, 0, 2100 },
    { 26, 1, 1, 3, { 0, 0, 0 }, gEvent189Text24, 0, 2500 },
    { 60, 0, 2, 3, { 0, 0, 0 }, gEvent072Text39, 0, 2530 },
    { 26, 1, 1, 3, { 0, 0, 0 }, gEvent189Text26, 0, 2880 },
    { 26, 1, 4, 3, { 0, 0, 0 }, gEvent189Text27, 0, 2882 },
    { 26, 1, 1, 3, { 0, 0, 0 }, gEvent189Text28, 0, 3000 },
    { 26, 1, 4, 3, { 0, 0, 0 }, gEvent189Text29, 0, 3002 },
    { 26, 1, 1, 3, { 0, 0, 0 }, gEvent189Text30, 0, 3070 },
    { 26, 0, 1, 3, { 0, 0, 0 }, gEvent189Text31, 0, 3170 },
    { 60, 2, 2, 3, { 0, 0, 0 }, gEvent189Text32, 0, 3200 },
    { 26, 1, 1, 3, { 0, 0, 0 }, gEvent189Text33, 0, 3230 },
    { 60, 1, 2, 3, { 0, 0, 0 }, gEvent189Text34, 0, 3260 },
    { 26, 1, 1, 3, { 0, 0, 0 }, gEvent189Text35, 0, 3290 },
    { 60, 1, 2, 3, { 0, 0, 0 }, gEvent189Text36, 0, 3310 },
    { 60, 1, 4, 3, { 0, 0, 0 }, gEvent189Text37, 0, 3312 },
    { 26, 0, 1, 3, { 0, 0, 0 }, gEvent189Text38, 0, 3360 },
    { 60, 2, 2, 3, { 0, 0, 0 }, gEvent189Text39, 0, 3390 },
    { 26, 4, 1, 3, { 0, 0, 0 }, gEvent189Text40, 0, 3420 },
    { 26, 0, 2, 3, { 0, 0, 0 }, gEvent189Text41, MSG_SCRIPT_FLAG_END, 3560 },
};

#include "event_189_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent189Script[42] = {
    { 26, 0, 1, 1, { 0, 0, 0 }, &gEvent189Text00, 0, 190 },
    { 60, 0, 3, 1, { 0, 0, 0 }, &gEvent189Text01, 0, 290 },
    { 26, 0, 1, 1, { 0, 0, 0 }, &gEvent189Text02, 0, 390 },
    { 60, 2, 3, 1, { 0, 0, 0 }, &gEvent189Text03, 0, 420 },
    { 26, 0, 1, 1, { 0, 0, 0 }, &gEvent189Text04, 0, 450 },
    { 60, 0, 3, 1, { 0, 0, 0 }, &gEvent189Text05, 0, 530 },
    { 26, 3, 0, 1, { 0, 0, 0 }, &gEvent189Text06, 0, 900 },
    { 26, 2, 1, 1, { 0, 0, 0 }, &gEvent189Text07, 0, 1010 },
    { 60, 1, 3, 1, { 0, 0, 0 }, &gEvent189Text08, 0, 1040 },
    { 26, 0, 1, 1, { 0, 0, 0 }, &gEvent189Text09, 0, 1070 },
    { 26, 0, 1, 1, { 0, 0, 0 }, &gEvent189Text10, 0, 1290 },
    { 26, 0, 4, 1, { 0, 0, 0 }, &gEvent189Text11, 0, 1292 },
    { 60, 0, 3, 1, { 0, 0, 0 }, &gEvent189Text12, 0, 1320 },
    { 26, 1, 1, 1, { 0, 0, 0 }, &gEvent189Text13, 0, 1350 },
    { 60, 0, 3, 1, { 0, 0, 0 }, &gEvent189Text14, 0, 1380 },
    { 60, 0, 3, 1, { 0, 0, 0 }, &gEvent189Text15, 0, 1560 },
    { 60, 0, 4, 1, { 0, 0, 0 }, &gEvent189Text16, 0, 1562 },
    { 60, 0, 3, 1, { 0, 0, 0 }, &gEvent189Text17, 0, 1740 },
    { 60, 0, 4, 1, { 0, 0, 0 }, &gEvent189Text18, 0, 1742 },
    { 26, 0, 1, 1, { 0, 0, 0 }, &gEvent189Text19, 0, 1770 },
    { 26, 0, 1, 1, { 0, 0, 0 }, &gEvent189Text20, 0, 1970 },
    { 60, 0, 3, 1, { 0, 0, 0 }, &gEvent189Text21, 0, 2000 },
    { 60, 0, 4, 1, { 0, 0, 0 }, &gEvent189Text22, 0, 2002 },
    { 60, 0, 3, 1, { 0, 0, 0 }, &gEvent189Text23, 0, 2100 },
    { 26, 1, 1, 1, { 0, 0, 0 }, &gEvent189Text24, 0, 2500 },
    { 60, 0, 2, 1, { 0, 0, 0 }, &gEvent189Text25, 0, 2530 },
    { 26, 1, 1, 1, { 0, 0, 0 }, &gEvent189Text26, 0, 2880 },
    { 26, 1, 4, 1, { 0, 0, 0 }, &gEvent189Text27, 0, 2882 },
    { 26, 1, 1, 1, { 0, 0, 0 }, &gEvent189Text28, 0, 3000 },
    { 26, 1, 4, 1, { 0, 0, 0 }, &gEvent189Text29, 0, 3002 },
    { 26, 1, 1, 1, { 0, 0, 0 }, &gEvent189Text30, 0, 3070 },
    { 26, 0, 1, 1, { 0, 0, 0 }, &gEvent189Text31, 0, 3170 },
    { 60, 2, 2, 1, { 0, 0, 0 }, &gEvent189Text32, 0, 3200 },
    { 26, 1, 1, 1, { 0, 0, 0 }, &gEvent189Text33, 0, 3230 },
    { 60, 1, 2, 1, { 0, 0, 0 }, &gEvent189Text34, 0, 3260 },
    { 26, 1, 1, 1, { 0, 0, 0 }, &gEvent189Text35, 0, 3290 },
    { 60, 1, 2, 1, { 0, 0, 0 }, &gEvent189Text36, 0, 3310 },
    { 60, 1, 4, 1, { 0, 0, 0 }, &gEvent189Text37, 0, 3312 },
    { 26, 0, 1, 1, { 0, 0, 0 }, &gEvent189Text38, 0, 3360 },
    { 60, 2, 2, 1, { 0, 0, 0 }, &gEvent189Text39, 0, 3390 },
    { 26, 4, 1, 1, { 0, 0, 0 }, &gEvent189Text40, 0, 3420 },
    { 26, 0, 2, 1, { 0, 0, 0 }, &gEvent189Text41, MSG_SCRIPT_FLAG_END, 3560 },
};
#endif

static const EvSoundCue sEvent189SoundCues[5] = {
    { 65535, 0, 0, 0 },
    { SONG_BGM_EVENT1, 1390, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT1, 2878, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT_NAMINE, 2998, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT_NAMINE, 3585, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent189Camera[13] = {
    { -65456, 68864, 88576, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64906, 75776, 91392, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 70, { 0, 0 }, NULL },
    { -64736, 65536, 74240, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 100, { 0, 0 }, NULL },
    { -64616, 65536, 67584, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -64436, 61696, 78336, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -64376, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_BLACK | CAMERA_MODE_KEEP, 60, { 0, 0 }, NULL },
    { -64356, 65536, 88576, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64336, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64276, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_BLACK | CAMERA_MODE_KEEP, 60, { 0, 0 }, NULL },
    { -63146, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -62066, 70144, 75008, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 100, { 0, 0 }, NULL },
    { -61536, 76800, 85760, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -59536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent189Track0[44] = {
    { 515, 80, { 0, 0 }, 103424, 110848, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 518, 170, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 515, 310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 515, 630, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 518, 700, { 0, 0 }, 71680, 90880, 0, 515, { 0, 0 }, 3, NULL, NULL },
    { 515, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 515, 790, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 522, 840, { 0, 0 }, 83712, 78848, 0, 515, { 0, 0 }, 67, NULL, NULL },
    { 515, 860, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 910, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 920, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 520, 960, { 0, 0 }, 71680, 90880, 0, 514, { 0, 0 }, 3, NULL, NULL },
    { 514, 970, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 538, 1012, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 1160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 530, 1330, { 0, 0 }, 70656, 97536, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 515, 1400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 1530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 515, 1580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 1710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 515, 1765, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 530, 1960, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 2120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 2350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 515, 2370, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 2390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 518, 2440, { 0, 0 }, 75520, 87040, 0, 515, { 0, 0 }, 67, NULL, NULL },
    { 515, 2460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 2560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 530, 2580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 530, 2840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 530, 2980, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 3030, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 3225, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 524, 3355, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 3450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 3470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 516, 3530, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 514, 3580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 516, 5000, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 32836, NULL, NULL },
};

static const EventCharaKeyframe sEvent189Track1[18] = {
    { 428, 220, { 0, 0 }, 71424, 93952, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 422, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 422, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 422, 560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 428, 590, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 450, 655, { 0, 0 }, 56064, 85248, 0, 428, { 0, 0 }, 3, NULL, NULL },
    { 428, 675, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 428, 685, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 422, 1160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 422, 1790, { 0, 0 }, 61696, 94720, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 422, 1920, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 422, 2390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 428, 2420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 450, 2480, { 0, 0 }, 66304, 88576, 0, 428, { 0, 0 }, 67, NULL, NULL },
    { 428, 3090, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 428, 3140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 428, 3500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 422, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent189Tracks[2] = {
    { sEvent189Track0, 44, { 0, 0, 0 } },
    { sEvent189Track1, 35, { 0, 0, 0 } },
};

const EventSequenceDef gEvent189 = {
    2,
    { 0, 0, 0 },
    sEvent189Tracks,
    sEvent189Camera,
    sEvent189Script,
    sEvent189SoundCues,
    NULL,
    3590,
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
#include "event_190_text.inc"
static const MessageScriptEntry sEvent190Script[15] = {
    { 61, 0, 1, 1, { 0, 0, 0 }, gEvent190Text00, 0, 210 },
    { 26, 3, 3, 1, { 0, 0, 0 }, gEvent190Text01, 0, 240 },
    { 61, 0, 1, 1, { 0, 0, 0 }, gEvent190Text02, 0, 270 },
    { 26, 3, 0, 1, { 0, 0, 0 }, gEvent190Text03, 0, 780 },
    { 61, 4, 2, 1, { 0, 0, 0 }, gEvent190Text04, 0, 825 },
    { 26, 0, 2, 1, { 0, 0, 0 }, gEvent190Text05, 0, 880 },
    { 52, 0, 1, 1, { 0, 0, 0 }, gEvent190Text06, 0, 940 },
    { 26, 1, 2, 1, { 0, 0, 0 }, gEvent190Text07, 0, 970 },
    { 52, 0, 1, 1, { 0, 0, 0 }, gEvent190Text08, 0, 1000 },
    { 26, 0, 2, 1, { 0, 0, 0 }, gEvent190Text09, 0, 1050 },
    { 52, 0, 1, 1, { 0, 0, 0 }, gEvent190Text10, 0, 1080 },
    { 26, 0, 2, 1, { 0, 0, 0 }, gEvent190Text11, 0, 1110 },
    { 52, 0, 1, 1, { 0, 0, 0 }, gEvent190Text12, 0, 1140 },
    { 52, 0, 1, 1, { 0, 0, 0 }, gEvent190Text13, 0, 1220 },
    { 26, 0, 2, 1, { 0, 0, 0 }, gEvent190Text14, MSG_SCRIPT_FLAG_END, 1460 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent190Script[15] = {
    { 61, 0, 1, 3, { 0, 0, 0 }, gEvent190Text00, 0, 210 },
    { 26, 3, 3, 3, { 0, 0, 0 }, gEvent190Text01, 0, 240 },
    { 61, 0, 1, 3, { 0, 0, 0 }, gEvent190Text02, 0, 270 },
    { 26, 3, 0, 3, { 0, 0, 0 }, gEvent190Text03, 0, 780 },
    { 61, 4, 2, 3, { 0, 0, 0 }, gEvent190Text04, 0, 825 },
    { 26, 0, 2, 3, { 0, 0, 0 }, gEvent190Text05, 0, 880 },
    { 52, 0, 1, 3, { 0, 0, 0 }, gEvent190Text06, 0, 940 },
    { 26, 1, 2, 3, { 0, 0, 0 }, gEvent190Text07, 0, 970 },
    { 52, 0, 1, 3, { 0, 0, 0 }, gEvent190Text08, 0, 1000 },
    { 26, 0, 2, 3, { 0, 0, 0 }, gEvent190Text09, 0, 1050 },
    { 52, 0, 1, 3, { 0, 0, 0 }, gEvent190Text10, 0, 1080 },
    { 26, 0, 2, 3, { 0, 0, 0 }, gEvent190Text11, 0, 1110 },
    { 52, 0, 1, 3, { 0, 0, 0 }, gEvent190Text12, 0, 1140 },
    { 52, 0, 1, 3, { 0, 0, 0 }, gEvent190Text13, 0, 1220 },
    { 26, 0, 2, 3, { 0, 0, 0 }, gEvent190Text14, MSG_SCRIPT_FLAG_END, 1460 },
};

#include "event_190_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent190Script[15] = {
    { 61, 0, 1, 1, { 0, 0, 0 }, &gEvent190Text00, 0, 210 },
    { 26, 3, 3, 1, { 0, 0, 0 }, &gEvent190Text01, 0, 240 },
    { 61, 0, 1, 1, { 0, 0, 0 }, &gEvent190Text02, 0, 270 },
    { 26, 3, 0, 1, { 0, 0, 0 }, &gEvent190Text03, 0, 780 },
    { 61, 4, 2, 1, { 0, 0, 0 }, &gEvent190Text04, 0, 825 },
    { 26, 0, 2, 1, { 0, 0, 0 }, &gEvent190Text05, 0, 880 },
    { 52, 0, 1, 1, { 0, 0, 0 }, &gEvent190Text06, 0, 940 },
    { 26, 1, 2, 1, { 0, 0, 0 }, &gEvent190Text07, 0, 970 },
    { 52, 0, 1, 1, { 0, 0, 0 }, &gEvent190Text08, 0, 1000 },
    { 26, 0, 2, 1, { 0, 0, 0 }, &gEvent190Text09, 0, 1050 },
    { 52, 0, 1, 1, { 0, 0, 0 }, &gEvent190Text10, 0, 1080 },
    { 26, 0, 2, 1, { 0, 0, 0 }, &gEvent190Text11, 0, 1110 },
    { 52, 0, 1, 1, { 0, 0, 0 }, &gEvent190Text12, 0, 1140 },
    { 52, 0, 1, 1, { 0, 0, 0 }, &gEvent190Text13, 0, 1220 },
    { 26, 0, 2, 1, { 0, 0, 0 }, &gEvent190Text14, MSG_SCRIPT_FLAG_END, 1460 },
};
#endif

static const EvSoundCue sEvent190SoundCues[6] = {
    { SONG_BGM_T13THFLOOR, 0, 0, 0 },
    { SONG_SND_958, 640, 0, 0 },
    { SONG_EV_SR_STONEL, 645, 0, 0 },
    { SONG_SND_959, 660, 0, 0 },
    { SONG_EV_SR_STONER, 665, 0, 0 },
    { SONG_EV_CARDTHR, 1191, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent190Camera[4] = {
    { -65116, 159488, 77056, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64916, 201728, 55296, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -64537, 192000, 61952, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent190Track0[17] = {
    { 515, 1, { 0, 0 }, 125696, 101888, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 518, 110, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 515, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 515, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 620, { 0, 0 }, 167424, 84736, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 518, 690, { 0, 0 }, 185088, 75520, 0, 515, { 0, 0 }, 67, NULL, NULL },
    { 515, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 850, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 1190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 559, 1250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 558, 1280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 558, 1410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 558, 1440, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 1480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 518, 1700, { 0, 0 }, 230400, 52992, 0, 515, { 0, 0 }, 67, NULL, NULL },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent190Track1[18] = {
    { 745, 50, { 0, 0 }, 198400, 64256, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 747, 180, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 745, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 745, 310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 746, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 746, 620, { 0, 0 }, 161792, 76544, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 754, 690, { 0, 0 }, 176384, 70400, 0, 746, { 0, 0 }, 67, NULL, NULL },
    { 746, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 745, 820, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 752, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 745, 920, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 746, 1470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 745, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 747, 1540, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 745, 1550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 746, 1560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 754, 2020, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 746, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent190Track2[4] = {
    { 907, 1160, { 0, 0 }, 201984, 61952, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 908, 1205, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 907, 1600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 907, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent190Track3[8] = {
    { 591, 1190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 591, 1191, { 0, 0 }, 197376, 58624, 0, 0, { 0, 0 }, 16658, NULL, NULL },
    { 591, 1200, { 0, 0 }, 189440, 65792, 0, 591, { 0, 0 }, 275, NULL, NULL },
    { 591, 1203, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 604, 1250, { 0, 0 }, 185088, 75520, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 591, 1264, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 603, 1440, { 0, 0 }, 185088, 75520, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 591, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98309, NULL, NULL },
};

static const EventCharaTrack sEvent190Tracks[4] = {
    { sEvent190Track0, 44, { 0, 0, 0 } },
    { sEvent190Track1, 69, { 0, 0, 0 } },
    { sEvent190Track2, 84, { 0, 0, 0 } },
    { sEvent190Track3, 50, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent190 = {
    4,
    { 0, 0, 0 },
    sEvent190Tracks,
    sEvent190Camera,
    sEvent190Script,
    sEvent190SoundCues,
    NULL,
    1640,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    191,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent190 = {
    4,
    { 0, 0, 0 },
    sEvent190Tracks,
    sEvent190Camera,
    sEvent190Script,
    sEvent190SoundCues,
    NULL,
    1640,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    189,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_191_text.inc"
static const MessageScriptEntry sEvent191Script[15] = {
    { 26, 0, 1, 1, { 0, 0, 0 }, gEvent191Text00, 0, 100 },
    { 61, 1, 3, 1, { 0, 0, 0 }, gEvent191Text01, 0, 280 },
    { 26, 1, 1, 1, { 0, 0, 0 }, gEvent191Text02, 0, 320 },
    { 26, 2, 4, 1, { 0, 0, 0 }, gEvent191Text03, 0, 330 },
    { 61, 2, 3, 1, { 0, 0, 0 }, gEvent191Text04, 0, 410 },
    { 26, 1, 1, 1, { 0, 0, 0 }, gEvent191Text05, 0, 440 },
    { 26, 0, 4, 1, { 0, 0, 0 }, gEvent191Text06, 0, 442 },
    { 26, 0, 1, 1, { 0, 0, 0 }, gEvent191Text07, 0, 540 },
    { 61, 1, 3, 1, { 0, 0, 0 }, gEvent191Text08, 0, 560 },
    { 26, 3, 1, 1, { 0, 0, 0 }, gEvent191Text09, 0, 600 },
    { 61, 3, 3, 1, { 0, 0, 0 }, gEvent191Text10, 0, 630 },
    { 61, 1, 4, 1, { 0, 0, 0 }, gEvent191Text11, 0, 632 },
    { 26, 4, 1, 1, { 0, 0, 0 }, gEvent191Text12, 0, 830 },
    { 61, 1, 3, 1, { 0, 0, 0 }, gEvent191Text13, 0, 860 },
    { 26, 4, 1, 1, { 0, 0, 0 }, gEvent191Text14, MSG_SCRIPT_FLAG_END, 920 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent191Script[15] = {
    { 26, 0, 1, 3, { 0, 0, 0 }, gEvent191Text00, 0, 100 },
    { 61, 1, 3, 3, { 0, 0, 0 }, gEvent191Text01, 0, 280 },
    { 26, 1, 1, 3, { 0, 0, 0 }, gEvent191Text02, 0, 320 },
    { 26, 2, 4, 3, { 0, 0, 0 }, gEvent191Text03, 0, 330 },
    { 61, 2, 3, 3, { 0, 0, 0 }, gEvent191Text04, 0, 410 },
    { 26, 1, 1, 3, { 0, 0, 0 }, gEvent191Text05, 0, 440 },
    { 26, 0, 4, 3, { 0, 0, 0 }, gEvent191Text06, 0, 442 },
    { 26, 0, 1, 3, { 0, 0, 0 }, gEvent191Text07, 0, 540 },
    { 61, 1, 3, 3, { 0, 0, 0 }, gEvent191Text08, 0, 560 },
    { 26, 3, 1, 3, { 0, 0, 0 }, gEvent191Text09, 0, 600 },
    { 61, 3, 3, 3, { 0, 0, 0 }, gEvent191Text10, 0, 630 },
    { 61, 1, 4, 3, { 0, 0, 0 }, gEvent191Text11, 0, 632 },
    { 26, 4, 1, 3, { 0, 0, 0 }, gEvent191Text12, 0, 830 },
    { 61, 1, 3, 3, { 0, 0, 0 }, gEvent191Text13, 0, 860 },
    { 26, 4, 1, 3, { 0, 0, 0 }, gEvent126Text11, MSG_SCRIPT_FLAG_END, 920 },
};

#include "event_191_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent191Script[15] = {
    { 26, 0, 1, 1, { 0, 0, 0 }, &gEvent191Text00, 0, 100 },
    { 61, 1, 3, 1, { 0, 0, 0 }, &gEvent191Text01, 0, 280 },
    { 26, 1, 1, 1, { 0, 0, 0 }, &gEvent191Text02, 0, 320 },
    { 26, 2, 4, 1, { 0, 0, 0 }, &gEvent191Text03, 0, 330 },
    { 61, 2, 3, 1, { 0, 0, 0 }, &gEvent191Text04, 0, 410 },
    { 26, 1, 1, 1, { 0, 0, 0 }, &gEvent191Text05, 0, 440 },
    { 26, 0, 4, 1, { 0, 0, 0 }, &gEvent191Text06, 0, 442 },
    { 26, 0, 1, 1, { 0, 0, 0 }, &gEvent191Text07, 0, 540 },
    { 61, 1, 3, 1, { 0, 0, 0 }, &gEvent191Text08, 0, 560 },
    { 26, 3, 1, 1, { 0, 0, 0 }, &gEvent191Text09, 0, 600 },
    { 61, 3, 3, 1, { 0, 0, 0 }, &gEvent191Text10, 0, 630 },
    { 61, 1, 4, 1, { 0, 0, 0 }, &gEvent191Text11, 0, 632 },
    { 26, 4, 1, 1, { 0, 0, 0 }, &gEvent191Text12, 0, 830 },
    { 61, 1, 3, 1, { 0, 0, 0 }, &gEvent191Text13, 0, 860 },
    { 26, 4, 1, 1, { 0, 0, 0 }, &gEvent191Text14, MSG_SCRIPT_FLAG_END, 920 },
};
#endif

static const EvSoundCue sEvent191SoundCues[4] = {
    { SONG_BGM_T13THFLOOR, 0, 0, 0 },
    { SONG_SND_382, 360, 0, 0 },
    { SONG_BGM_T13THFLOOR, 441, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT4, 559, EV_SOUND_FLAG_FADE_IN | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent191Camera[1] = {
    { -64537, 196096, 58880, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent191Track0[10] = {
    { 558, 120, { 0, 0 }, 202496, 68352, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 558, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 558, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 595, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 532, 602, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 515, 890, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 540, 910, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent191Track1[3] = {
    { 745, 350, { 0, 0 }, 191232, 61952, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 749, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaHop, NULL },
    { 745, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent191Track2[3] = {
    { 603, 300, { 0, 0 }, 202496, 68352, 0, 0, { 0, 0 }, 274, NULL, NULL },
    { 591, 310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 591, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98373, NULL, NULL },
};

static const EventCharaTrack sEvent191Tracks[3] = {
    { sEvent191Track0, 44, { 0, 0, 0 } },
    { sEvent191Track1, 69, { 0, 0, 0 } },
    { sEvent191Track2, 50, { 0, 0, 0 } },
};

const EventSequenceDef gEvent191 = {
    3,
    { 0, 0, 0 },
    sEvent191Tracks,
    sEvent191Camera,
    sEvent191Script,
    sEvent191SoundCues,
    NULL,
    980,
    1,
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

#ifdef VERSION_US
#include "event_192_text.inc"
static const MessageScriptEntry sEvent192Script[3] = {
    { 26, 0, 1, 1, { 0, 0, 0 }, gEvent192Text00, 0, 150 },
    { 56, 1, 2, 1, { 0, 0, 0 }, gEvent192Text01, 0, 250 },
    { 56, 1, 2, 1, { 0, 0, 0 }, gEvent192Text02, MSG_SCRIPT_FLAG_END, 300 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent192Script[3] = {
    { 26, 0, 1, 3, { 0, 0, 0 }, gEvent192Text00, 0, 150 },
    { 56, 1, 2, 3, { 0, 0, 0 }, gEvent192Text01, 0, 250 },
    { 56, 1, 2, 3, { 0, 0, 0 }, gEvent192Text02, MSG_SCRIPT_FLAG_END, 300 },
};

#include "event_192_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent192Script[3] = {
    { 26, 0, 1, 1, { 0, 0, 0 }, &gEvent192Text00, 0, 150 },
    { 56, 1, 2, 1, { 0, 0, 0 }, &gEvent192Text01, 0, 250 },
    { 56, 1, 2, 1, { 0, 0, 0 }, &gEvent192Text02, MSG_SCRIPT_FLAG_END, 300 },
};
#endif

static const EvSoundCue sEvent192SoundCues[3] = {
    { SONG_BGM_F13F_FORGET, 0, 0, 0 },
    { SONG_SND_359, 110, 0, 0 },
    { SONG_BGM_F13F_FORGET, 475, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent192Camera[2] = {
    { -65536, 35072, 32512, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, NULL },
    { -64537, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 80, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent192Track0[9] = {
    { 515, 1, { 0, 0 }, 67328, 56576, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 522, 100, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 515, 103, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 515, 110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 560, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 562, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 522, 1000, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent192Tracks[1] = {
    { sEvent192Track0, 44, { 0, 0, 0 } },
};

const EventSequenceDef gEvent192 = {
    1,
    { 0, 0, 0 },
    sEvent192Tracks,
    sEvent192Camera,
    sEvent192Script,
    sEvent192SoundCues,
    NULL,
    480,
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
#include "event_193_text.inc"
static const MessageScriptEntry sEvent193Script[12] = {
    { 26, 0, 3, 1, { 0, 0, 0 }, gEvent193Text00, 0, 330 },
    { 56, 0, 1, 1, { 0, 0, 0 }, gEvent193Text01, 0, 530 },
    { 56, 0, 1, 1, { 0, 0, 0 }, gEvent193Text02, 0, 650 },
    { 56, 0, 4, 1, { 0, 0, 0 }, gEvent193Text03, 0, 652 },
    { 56, 0, 4, 1, { 0, 0, 0 }, gEvent193Text04, 0, 654 },
    { 26, 0, 2, 1, { 0, 0, 0 }, gEvent193Text05, 0, 680 },
    { 26, 2, 2, 1, { 0, 0, 0 }, gEvent193Text06, 0, 820 },
    { 56, 1, 1, 1, { 0, 0, 0 }, gEvent193Text07, 0, 1020 },
    { 26, 2, 2, 1, { 0, 0, 0 }, gEvent193Text08, 0, 1050 },
    { 26, 0, 2, 1, { 0, 0, 0 }, gEvent193Text09, 0, 1100 },
    { 26, 1, 4, 1, { 0, 0, 0 }, gEvent193Text10, 0, 1102 },
    { 56, 2, 1, 1, { 0, 0, 0 }, gEvent193Text11, MSG_SCRIPT_FLAG_END, 1150 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent193Script[12] = {
    { 26, 0, 3, 3, { 0, 0, 0 }, gEvent193Text00, 0, 330 },
    { 56, 0, 1, 3, { 0, 0, 0 }, gEvent193Text01, 0, 530 },
    { 56, 0, 1, 3, { 0, 0, 0 }, gEvent193Text02, 0, 650 },
    { 56, 0, 4, 3, { 0, 0, 0 }, gEvent193Text03, 0, 652 },
    { 56, 0, 4, 3, { 0, 0, 0 }, gEvent193Text04, 0, 654 },
    { 26, 0, 2, 3, { 0, 0, 0 }, gEvent193Text05, 0, 680 },
    { 26, 2, 2, 3, { 0, 0, 0 }, gEvent193Text06, 0, 820 },
    { 56, 1, 1, 3, { 0, 0, 0 }, gEvent193Text07, 0, 1020 },
    { 26, 2, 2, 3, { 0, 0, 0 }, gEvent193Text08, 0, 1050 },
    { 26, 0, 2, 3, { 0, 0, 0 }, gEvent193Text09, 0, 1100 },
    { 26, 1, 4, 3, { 0, 0, 0 }, gEvent193Text10, 0, 1102 },
    { 56, 2, 1, 3, { 0, 0, 0 }, gEvent193Text11, MSG_SCRIPT_FLAG_END, 1150 },
};

#include "event_193_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent193Script[12] = {
    { 26, 0, 3, 1, { 0, 0, 0 }, &gEvent193Text00, 0, 330 },
    { 56, 0, 1, 1, { 0, 0, 0 }, &gEvent193Text01, 0, 530 },
    { 56, 0, 1, 1, { 0, 0, 0 }, &gEvent193Text02, 0, 650 },
    { 56, 0, 4, 1, { 0, 0, 0 }, &gEvent193Text03, 0, 652 },
    { 56, 0, 4, 1, { 0, 0, 0 }, &gEvent193Text04, 0, 654 },
    { 26, 0, 2, 1, { 0, 0, 0 }, &gEvent193Text05, 0, 680 },
    { 26, 2, 2, 1, { 0, 0, 0 }, &gEvent193Text06, 0, 820 },
    { 56, 1, 1, 1, { 0, 0, 0 }, &gEvent193Text07, 0, 1020 },
    { 26, 2, 2, 1, { 0, 0, 0 }, &gEvent193Text08, 0, 1050 },
    { 26, 0, 2, 1, { 0, 0, 0 }, &gEvent193Text09, 0, 1100 },
    { 26, 1, 4, 1, { 0, 0, 0 }, &gEvent193Text10, 0, 1102 },
    { 56, 2, 1, 1, { 0, 0, 0 }, &gEvent193Text11, MSG_SCRIPT_FLAG_END, 1150 },
};
#endif

static const EvSoundCue sEvent193SoundCues[9] = {
    { 65535, 0, 0, 0 },
    { SONG_SND_379, 450, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 550, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT_UNREST, 700, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_SND_359, 720, 0, 0 },
    { SONG_BGM_EVENT2, 730, 0, 0 },
    { SONG_SND_378, 1200, 0, 0 },
    { SONG_EV_RUMBLE, 1210, 0, 0 },
    { SONG_EV_RUMBLE, 1405, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent193Camera[6] = {
    { -65186, 165376, 73984, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64986, 181504, 65792, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 70, { 0, 0 }, NULL },
    { -64537, 173824, 72704, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 60, { 0, 0 }, NULL },
    { -64326, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64181, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_SMALL | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -63536, 66304, 33792, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_SMALL | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 1, { 0, 0 }, NULL },
};

static const EventBgEffectEntry sEvent193BgEffects[4] = {
    { 1250, 0, 0, 0, 0 },
    { 1350, 0, 0, 0, 0x14 },
    { 3000, 0, 0, 0, 0x2 },
    { 5000, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent193Track0[7] = {
    { 515, 1, { 0, 0 }, 131072, 100352, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 518, 140, { 0, 0 }, 164608, 82432, 0, 515, { 0, 0 }, 67, NULL, NULL },
    { 515, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 515, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 560, 1355, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 561, 5000, { 0, 0 }, 57088, 43520, 0, 0, { 0, 0 }, 32834, NULL, NULL },
};

static const EventCharaKeyframe sEvent193Track1[8] = {
    { 688, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 688, 550, { 0, 0 }, 198144, 66816, 0, 0, { 0, 0 }, 2, EventCharaFadeIn, NULL },
    { 690, 620, { 0, 0 }, 182784, 74752, 0, 688, { 0, 0 }, 3, NULL, NULL },
    { 688, 840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 688, 970, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 688, 1180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 694, 1355, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 694, 5000, { 0, 0 }, 75264, 35840, 0, 0, { 0, 0 }, 32770, NULL, NULL },
};

static const EventCharaKeyframe sEvent193Track2[3] = {
    { 926, 1200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 926, 1215, { 0, 0 }, 184064, 72704, 0, 0, { 0, 0 }, 16658, NULL, NULL },
    { 926, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaTrack sEvent193Tracks[3] = {
    { sEvent193Track0, 44, { 0, 0, 0 } },
    { sEvent193Track1, 64, { 0, 0, 0 } },
    { sEvent193Track2, 92, { 0, 0, 0 } },
};

const EventSequenceDef gEvent193 = {
    3,
    { 0, 0, 0 },
    sEvent193Tracks,
    sEvent193Camera,
    sEvent193Script,
    sEvent193SoundCues,
    sEvent193BgEffects,
    1410,
    0,
    1,
    0,
    0,
    0,
    0,
    177,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_194_text.inc"
static const MessageScriptEntry sEvent194Script[7] = {
    { 56, 2, 1, 1, { 0, 0, 0 }, gEvent194Text00, 0, 100 },
    { 26, 2, 2, 1, { 0, 0, 0 }, gEvent194Text01, 0, 250 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent194Text02, 0, 350 },
    { 56, 2, 1, 1, { 0, 0, 0 }, gEvent194Text03, 0, 380 },
    { 56, 2, 1, 1, { 0, 0, 0 }, gEvent194Text04, 0, 445 },
    { 61, 1, 1, 1, { 0, 0, 0 }, gEvent194Text05, 0, 1180 },
    { 61, 1, 1, 1, { 0, 0, 0 }, gEvent194Text06, MSG_SCRIPT_FLAG_END, 1400 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent194Script[7] = {
    { 56, 2, 1, 3, { 0, 0, 0 }, gEvent194Text00, 0, 100 },
    { 26, 2, 2, 3, { 0, 0, 0 }, gEvent194Text01, 0, 250 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent194Text02, 0, 350 },
    { 56, 2, 1, 3, { 0, 0, 0 }, gEvent194Text03, 0, 380 },
    { 56, 2, 1, 3, { 0, 0, 0 }, gEvent194Text04, 0, 445 },
    { 61, 1, 1, 3, { 0, 0, 0 }, gEvent194Text05, 0, 1180 },
    { 61, 1, 1, 3, { 0, 0, 0 }, gEvent194Text06, MSG_SCRIPT_FLAG_END, 1400 },
};

#include "event_194_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent194Script[7] = {
    { 56, 2, 1, 1, { 0, 0, 0 }, &gEvent194Text00, 0, 100 },
    { 26, 2, 2, 1, { 0, 0, 0 }, &gEvent194Text01, 0, 250 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent194Text02, 0, 350 },
    { 56, 2, 1, 1, { 0, 0, 0 }, &gEvent194Text03, 0, 380 },
    { 56, 2, 1, 1, { 0, 0, 0 }, &gEvent194Text04, 0, 445 },
    { 61, 1, 1, 1, { 0, 0, 0 }, &gEvent194Text05, 0, 1180 },
    { 61, 1, 1, 1, { 0, 0, 0 }, &gEvent194Text06, MSG_SCRIPT_FLAG_END, 1400 },
};
#endif

static const EvSoundCue sEvent194SoundCues[12] = {
    { SONG_BGM_EVENT2, 0, 0, 0 },
    { SONG_SND_380, 105, 0, 0 },
    { SONG_EV_RUMBLE, 120, 0, 0 },
    { SONG_EV_RUMBLE, 190, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_SND_376, 260, 0, 0 },
    { SONG_EV_FLASH00, 270, 0, 0 },
    { SONG_SND_380, 440, 0, 0 },
    { SONG_EV_RUMBLE, 441, 0, 0 },
    { SONG_SND_379, 450, 0, 0 },
    { SONG_EV_RUMBLE, 620, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT2, 660, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_EV_WHITEOUT, 1530, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent194Camera[12] = {
    { -65416, 175616, 66560, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65336, 170752, 71168, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_SMALL | CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -65266, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65246, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 20, { 0, 0 }, NULL },
    { -65136, 188928, 62208, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -65106, 183552, 65536, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 30, { 0, 0 }, NULL },
    { -64676, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_SMALL | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64131, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64088, 69376, 29440, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64006, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -63536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 100, { 0, 0 }, NULL },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EventBgEffectEntry sEvent194BgEffects[5] = {
    { 450, 0, 0, 0, 0 },
    { 530, 0, 80, 0, 0x14 },
    { 3310, 0, 0, 0, 0 },
    { 4000, 0, 0, 0, 0x2 },
    { 5000, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent194Track0[15] = {
    { 561, 120, { 0, 0 }, 158208, 83712, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 542, 170, { 0, 0 }, 149504, 88064, 0, 515, { 0, 0 }, 67, NULL, NULL },
    { 560, 260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 548, 290, { 0, 0 }, 194816, 65792, 0, 515, { 0, 0 }, 67, NULL, NULL },
    { 553, 345, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 563, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 514, 460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 514, 470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 526, 620, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 526, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaFadeOut, NULL },
    { 515, 1450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 514, 1520, { 0, 0 }, 53248, 34816, 0, 0, { 0, 0 }, 322, EventCharaFadeIn, NULL },
    { 515, 1580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 518, 1690, { 0, 0 }, 68096, 31232, 0, 515, { 0, 0 }, 67, NULL, NULL },
    { 514, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33093, NULL, NULL },
};

static const EventCharaKeyframe sEvent194Track1[7] = {
    { 688, 10, { 0, 0 }, 182528, 73216, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 693, 272, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 688, 278, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 693, 425, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 694, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 694, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaFadeOut, NULL },
    { 693, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent194Track2[6] = {
    { 920, 950, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8450, NULL, NULL },
    { 920, 951, { 0, 0 }, 225792, 47104, 0, 0, { 0, 0 }, 16770, NULL, NULL },
    { 920, 1150, { 0, 0 }, 183040, 63744, 0, 920, { 0, 0 }, 259, NULL, NULL },
    { 920, 1280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 389, NULL, NULL },
    { 920, 1310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 256, EventCharaFadeOut, NULL },
    { 920, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent194Track3[5] = {
    { 746, 1450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 745, 1520, { 0, 0 }, 85248, 35584, 0, 0, { 0, 0 }, 258, EventCharaFadeIn, NULL },
    { 746, 1580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 754, 1690, { 0, 0 }, 72704, 30208, 0, 746, { 0, 0 }, 3, NULL, NULL },
    { 746, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33029, NULL, NULL },
};

static const EventCharaKeyframe sEvent194Track4[5] = {
    { 926, 105, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 926, 300, { 0, 0 }, 182016, 66560, 0, 0, { 0, 0 }, 16658, NULL, NULL },
    { 103, 440, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 926, 480, { 0, 0 }, 183552, 65536, 0, 0, { 0, 0 }, 274, NULL, NULL },
    { 926, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaTrack sEvent194Tracks[5] = {
    { sEvent194Track0, 44, { 0, 0, 0 } },
    { sEvent194Track1, 64, { 0, 0, 0 } },
    { sEvent194Track2, 87, { 0, 0, 0 } },
    { sEvent194Track3, 69, { 0, 0, 0 } },
    { sEvent194Track4, 92, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent194 = {
    5,
    { 0, 0, 0 },
    sEvent194Tracks,
    sEvent194Camera,
    sEvent194Script,
    sEvent194SoundCues,
    sEvent194BgEffects,
    1680,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    195,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent194 = {
    5,
    { 0, 0, 0 },
    sEvent194Tracks,
    sEvent194Camera,
    sEvent194Script,
    sEvent194SoundCues,
    sEvent194BgEffects,
    1680,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    193,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_195_text.inc"
static const MessageScriptEntry sEvent195Script[15] = {
    { 61, 0, 1, 1, { 0, 0, 0 }, gEvent195Text00, 0, 100 },
    { 26, 0, 3, 1, { 0, 0, 0 }, gEvent195Text01, 0, 130 },
    { 26, 0, 3, 1, { 0, 0, 0 }, gEvent195Text02, 0, 200 },
    { 26, 5, 4, 1, { 0, 0, 0 }, gEvent195Text03, 0, 202 },
    { 26, 5, 3, 1, { 0, 0, 0 }, gEvent195Text04, 0, 330 },
    { 61, 0, 1, 1, { 0, 0, 0 }, gEvent195Text05, 0, 360 },
    { 61, 0, 1, 1, { 0, 0, 0 }, gEvent195Text06, 0, 550 },
    { 61, 0, 4, 1, { 0, 0, 0 }, gEvent195Text07, 0, 552 },
    { 61, 0, 1, 1, { 0, 0, 0 }, gEvent195Text08, 0, 650 },
    { 61, 0, 4, 1, { 0, 0, 0 }, gEvent195Text09, 0, 652 },
    { 61, 0, 4, 1, { 0, 0, 0 }, gEvent195Text10, 0, 654 },
    { 61, 1, 1, 1, { 0, 0, 0 }, gEvent195Text11, 0, 780 },
    { 26, 1, 3, 1, { 0, 0, 0 }, gEvent195Text12, 0, 850 },
    { 61, 1, 1, 1, { 0, 0, 0 }, gEvent195Text13, 0, 880 },
    { 26, 4, 3, 1, { 0, 0, 0 }, gEvent195Text14, MSG_SCRIPT_FLAG_END, 1060 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent195Script[15] = {
    { 61, 0, 1, 3, { 0, 0, 0 }, gEvent195Text00, 0, 100 },
    { 26, 0, 3, 3, { 0, 0, 0 }, gEvent195Text01, 0, 130 },
    { 26, 0, 3, 3, { 0, 0, 0 }, gEvent195Text02, 0, 200 },
    { 26, 5, 4, 3, { 0, 0, 0 }, gEvent195Text03, 0, 202 },
    { 26, 5, 3, 3, { 0, 0, 0 }, gEvent195Text04, 0, 330 },
    { 61, 0, 1, 3, { 0, 0, 0 }, gEvent195Text05, 0, 360 },
    { 61, 0, 1, 3, { 0, 0, 0 }, gEvent195Text06, 0, 550 },
    { 61, 0, 4, 3, { 0, 0, 0 }, gEvent195Text07, 0, 552 },
    { 61, 0, 1, 3, { 0, 0, 0 }, gEvent195Text08, 0, 650 },
    { 61, 0, 4, 3, { 0, 0, 0 }, gEvent195Text09, 0, 652 },
    { 61, 0, 4, 3, { 0, 0, 0 }, gEvent195Text10, 0, 654 },
    { 61, 1, 1, 3, { 0, 0, 0 }, gEvent195Text11, 0, 780 },
    { 26, 1, 3, 3, { 0, 0, 0 }, gEvent195Text12, 0, 850 },
    { 61, 1, 1, 3, { 0, 0, 0 }, gEvent195Text13, 0, 880 },
    { 26, 4, 3, 3, { 0, 0, 0 }, gEvent195Text14, MSG_SCRIPT_FLAG_END, 1060 },
};

#include "event_195_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent195Script[15] = {
    { 61, 0, 1, 1, { 0, 0, 0 }, &gEvent195Text00, 0, 100 },
    { 26, 0, 3, 1, { 0, 0, 0 }, &gEvent195Text01, 0, 130 },
    { 26, 0, 3, 1, { 0, 0, 0 }, &gEvent195Text02, 0, 200 },
    { 26, 5, 4, 1, { 0, 0, 0 }, &gEvent195Text03, 0, 202 },
    { 26, 5, 3, 1, { 0, 0, 0 }, &gEvent195Text04, 0, 330 },
    { 61, 0, 1, 1, { 0, 0, 0 }, &gEvent195Text05, 0, 360 },
    { 61, 0, 1, 1, { 0, 0, 0 }, &gEvent195Text06, 0, 550 },
    { 61, 0, 4, 1, { 0, 0, 0 }, &gEvent195Text07, 0, 552 },
    { 61, 0, 1, 1, { 0, 0, 0 }, &gEvent195Text08, 0, 650 },
    { 61, 0, 4, 1, { 0, 0, 0 }, &gEvent195Text09, 0, 652 },
    { 61, 0, 4, 1, { 0, 0, 0 }, &gEvent195Text10, 0, 654 },
    { 61, 1, 1, 1, { 0, 0, 0 }, &gEvent195Text11, 0, 780 },
    { 26, 1, 3, 1, { 0, 0, 0 }, &gEvent195Text12, 0, 850 },
    { 61, 1, 1, 1, { 0, 0, 0 }, &gEvent195Text13, 0, 880 },
    { 26, 4, 3, 1, { 0, 0, 0 }, &gEvent195Text14, MSG_SCRIPT_FLAG_END, 1060 },
};
#endif

static const EvSoundCue sEvent195SoundCues[2] = {
    { 65535, 0, 0, 0 },
    { SONG_SND_358, 836, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent195Camera[2] = {
    { -65536, 106752, 103168, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, NULL },
    { -64537, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 80, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent195Track0[10] = {
    { 515, 150, { 0, 0 }, 102400, 111360, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 558, 270, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 295, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 540, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 540, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 540, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 820, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 536, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 536, 1030, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 536, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent195Track1[4] = {
    { 745, 670, { 0, 0 }, 114944, 104704, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 747, 700, { 0, 0 }, 109568, 108800, 0, 745, { 0, 0 }, 3, NULL, NULL },
    { 745, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 750, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent195Tracks[2] = {
    { sEvent195Track0, 44, { 0, 0, 0 } },
    { sEvent195Track1, 69, { 0, 0, 0 } },
};

const EventSequenceDef gEvent195 = {
    2,
    { 0, 0, 0 },
    sEvent195Tracks,
    sEvent195Camera,
    sEvent195Script,
    sEvent195SoundCues,
    NULL,
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
    13,
    0,
    255,
    255,
};

#ifdef VERSION_US
static const MessageScriptEntry sEvent196Script[1] = {
    { 26, 0, 3, 1, { 0, 0, 0 }, gEvent196Text00, MSG_SCRIPT_FLAG_END, 100 },
};

#include "event_196_text.inc"
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent196Script[1] = {
    { 26, 0, 3, 3, { 0, 0, 0 }, gEvent196Text00, MSG_SCRIPT_FLAG_END, 100 },
};

#include "event_196_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent196Script[1] = {
    { 26, 0, 3, 1, { 0, 0, 0 }, NULL, MSG_SCRIPT_FLAG_END, 100 },
};
#endif

const u8 gUnk_0902FC64[8] = {
    13, 0, 0, 0, 0, 128, 0, 0,
};

static const EventCameraKeyframe sEvent196Camera[1] = {
    { -64537, 65280, 71680, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent196Track0[1] = {
    { 515, 999, { 0, 0 }, 89088, 89088, 0, 0, { 0, 0 }, 32770, NULL, NULL },
};

static const EventCharaTrack sEvent196Tracks[1] = {
    { sEvent196Track0, 44, { 0, 0, 0 } },
};

const EventSequenceDef gEvent196 = {
    1,
    { 0, 0, 0 },
    sEvent196Tracks,
    sEvent196Camera,
    sEvent196Script,
    NULL,
    NULL,
    1000,
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
