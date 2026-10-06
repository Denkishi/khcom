#ifdef VERSION_US
#include "event_112_text.inc"
#endif

static const MessageScriptEntry sEvent112Script[15] = {
    { 16, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent112Text00), 0, 180 },
    { 16, 2, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent112Text01), 0, 182 },
    { 0, 2, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent112Text02), 0, 220 },
    { 16, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent112Text03), 0, 300 },
    { 21, 4, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent112Text04), 0, 410 },
    { 15, 2, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent112Text05), 0, 600 },
    { 15, 1, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent112Text06), 0, 602 },
    { 16, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent112Text07), 0, 620 },
    { 0, 1, 2, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent112Text08), 0, 660 },
    { 15, 2, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent112Text09), 0, 750 },
    { 21, 3, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent112Text10), 0, 770 },
    { 16, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent112Text11), 0, 980 },
    { 16, 0, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent112Text12), 0, 982 },
    { 16, 2, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent112Text13), 0, 984 },
    { 16, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent112Text14), MSG_SCRIPT_FLAG_END, 1010 },
};

#ifdef VERSION_JP
#include "event_112_text.inc"
#endif

static const EventCameraKeyframe sEvent112Camera[15] = {
    { -65306, 91392, 43520, 0, 255, 0, 0, NULL },
    { -65086, 89600, 33536, 0, 255, CAMERA_MODE_APPROACH, 20, NULL },
    { -65076, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_SHAKE_MEDIUM | CAMERA_MODE_KEEP, 0, NULL },
    { -65036, 0, 0, 0, 255, CAMERA_MODE_KEEP, 0, NULL },
    { -65016, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_SHAKE_LARGE | CAMERA_MODE_KEEP, 0, NULL },
    { -65006, 0, 0, 0, 255, CAMERA_MODE_KEEP, 0, NULL },
    { -64906, 48896, 20736, 0, 255, CAMERA_MODE_APPROACH, 20, NULL },
    { -64856, 91392, 38656, 0, 255, CAMERA_MODE_APPROACH, 20, NULL },
    { -64756, 48896, 20736, 0, 255, CAMERA_MODE_APPROACH, 20, NULL },
    { -64516, 0, 0, 0, 255, CAMERA_MODE_KEEP, 0, NULL },
    { -64506, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, NULL },
    { -64486, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, NULL },
    { -64466, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, NULL },
    { -64436, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 30, NULL },
    { -64036, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, NULL },
};

static const EvSoundCue sEvent112SoundCues[5] = {
    { SONG_BGM_EVENT_UNREST, 0, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 260, 0, 0 },
    { SONG_BGM_EVENT2, 300, 0, 0 },
    { SONG_BTL_AR_PUNCHHIT, 450, 0, 0 },
    { SONG_BTL_MON_HIT06, 500, EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent112Track0[5] = {
    { 4, 1, 52736, 71680, 0, 0, 66, NULL, NULL },
    { 14, 90, 0, 0, 0, 45, 100, NULL, NULL },
    { 4, 93, 0, 0, 0, 45, 68, NULL, NULL },
    { 4, 100, 0, 0, 0, 0, 69, NULL, NULL },
    { 19, 2000, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent112Track1[7] = {
    { 114, 1, 49152, 78336, 0, 0, 66, NULL, NULL },
    { 120, 110, 0, 0, 0, 45, 100, NULL, NULL },
    { 114, 113, 0, 0, 0, 45, 68, NULL, NULL },
    { 114, 120, 0, 0, 0, 0, 69, NULL, NULL },
    { 122, 130, 0, 0, 0, 0, 69, NULL, NULL },
    { 123, 9999, 0, 0, 0, 0, 69, NULL, NULL },
    { 114, 9999, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent112Track2[7] = {
    { 146, 1, 40960, 73728, 0, 0, 66, NULL, NULL },
    { 153, 132, 0, 0, 0, 45, 100, NULL, NULL },
    { 146, 135, 0, 0, 0, 45, 68, NULL, NULL },
    { 146, 140, 0, 0, 0, 0, 69, NULL, NULL },
    { 157, 150, 0, 0, 0, 0, 69, NULL, NULL },
    { 158, 9999, 0, 0, 0, 0, 69, NULL, NULL },
    { 146, 9999, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent112Track3[12] = {
    { 282, 230, 0, 0, 0, 0, 66, NULL, NULL },
    { 282, 231, 69888, 30976, -15360, 0, 66, NULL, NULL },
    { 279, 250, 0, 0, 0, 0, 64, EventCharaDrop, NULL },
    { 280, 305, 0, 0, 0, 0, 69, NULL, NULL },
    { 281, 310, 0, 0, 0, 0, 69, NULL, NULL },
    { 272, 350, 0, 0, 0, 83, 100, NULL, NULL },
    { 272, 353, 0, 0, 0, 83, 68, NULL, NULL },
    { 274, 450, 0, 0, 0, 0, 64, NULL, CreateExclamationTask },
    { 277, 480, 45568, 19456, 0, 270, 67, NULL, NULL },
    { 273, 690, 0, 0, 0, 0, 69, NULL, NULL },
    { 270, 1020, 0, 0, 0, 0, 69, NULL, NULL },
    { 274, 9999, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent112Track4[5] = {
    { 664, 340, 0, 0, 0, 0, 66, NULL, NULL },
    { 665, 420, 91648, 40448, -2560, 0, 262146, NULL, NULL },
    { 667, 520, 0, 0, 0, 0, 262149, NULL, NULL },
    { 665, 600, 0, 0, 0, 0, 262149, NULL, NULL },
    { 664, 9999, 0, 0, 0, 0, 294981, NULL, NULL },
};

static const EventCharaKeyframe sEvent112Track5[3] = {
    { 743, 340, 0, 0, 0, 0, 8194, NULL, NULL },
    { 743, 390, 91648, 40448, -7680, 0, 16658, NULL, NULL },
    { 743, 999, 0, 0, 0, 0, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent112Track6[2] = {
    { 588, 1, 93440, 43008, 0, 0, 2, NULL, NULL },
    { 588, 9999, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent112Track7[11] = {
    { 632, 1, 101632, 47616, 0, 0, 2, NULL, NULL },
    { 632, 190, 0, 0, 0, 0, 5, NULL, NULL },
    { 634, 210, 0, 0, 0, 173, 4, NULL, NULL },
    { 632, 230, 0, 0, 0, 0, 5, NULL, NULL },
    { 632, 280, 0, 0, 0, 0, 0, NULL, CreateExclamationTask },
    { 633, 771, 0, 0, 0, 0, 5, NULL, NULL },
    { 637, 950, 61696, 33024, 0, 633, 3, NULL, NULL },
    { 633, 990, 0, 0, 0, 0, 5, NULL, NULL },
    { 632, 1000, 0, 0, 0, 0, 5, NULL, NULL },
    { 632, 1010, 0, 0, 0, 0, 69, NULL, NULL },
    { 635, 9999, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent112Tracks[8] = {
    { sEvent112Track0, 0 },
    { sEvent112Track1, 1 },
    { sEvent112Track2, 2 },
    { sEvent112Track3, 12 },
    { sEvent112Track4, 59 },
    { sEvent112Track5, 68 },
    { sEvent112Track6, 48 },
    { sEvent112Track7, 56 },
};

const EventSequenceDef gEvent112 = {
    8,
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
    EVENT_113_AGRABAH_BOSS,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
