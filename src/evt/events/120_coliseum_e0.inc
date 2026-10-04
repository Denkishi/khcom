#ifdef VERSION_US
#include "event_120_text.inc"
#endif

static const MessageScriptEntry sEvent120Script[24] = {
    { 1, 0, 0, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent120Text00), 0, 240 },
    { 6, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent120Text01), 0, 425 },
    { 6, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent120Text02), 0, 485 },
    { 6, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent120Text03), 0, 487 },
    { 6, 2, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent120Text04), 0, 489 },
    { 6, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent120Text05), 0, 540 },
    { 0, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent120Text06), 0, 560 },
    { 2, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent120Text07), 0, 580 },
    { 1, 1, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent120Text08), 0, 610 },
    { 0, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent120Text09), 0, 790 },
    { 1, 3, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent120Text10), 0, 810 },
    { 6, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent120Text11), 0, 875 },
    { 6, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent120Text12), 0, 930 },
    { 6, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent120Text13), 0, 990 },
    { 0, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent120Text14), 0, 1020 },
    { 34, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent120Text15), 0, 1730 },
    { 34, 3, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent120Text16), 0, 1976 },
    { 34, 3, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent120Text17), 0, 1978 },
    { 35, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent120Text18), MSG_SCRIPT_FLAG_SILHOUETTE, 1985 },
    { 34, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent120Text19), 0, 2025 },
    { 34, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent120Text20), 0, 2175 },
    { 34, 2, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent120Text21), 0, 2177 },
    { 35, 0, 0, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent120Text22), 0, 2207 },
    { 34, 2, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent120Text23), MSG_SCRIPT_FLAG_END, 2237 },
};

#ifdef VERSION_JP
#include "event_120_text.inc"
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
