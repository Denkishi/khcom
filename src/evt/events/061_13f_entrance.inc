#ifdef VERSION_US
#include "event_061_text.inc"
#endif

static const MessageScriptEntry sEvent061Script[18] = {
    { 0, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent061Text00), 0, 250 },
    { 0, 5, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent061Text01), 0, 430 },
    { 1, 2, 0, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent061Text02), 0, 460 },
    { 0, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent061Text03), 0, 540 },
    { 0, 7, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent061Text04), 0, 542 },
    { 1, 2, 0, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent061Text05), 0, 580 },
    { 1, 0, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent061Text06), 0, 582 },
    { 1, 2, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent061Text07), 0, 586 },
    { 2, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent061Text08), 0, 740 },
    { 0, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent061Text09), 0, 760 },
    { 2, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent061Text10), 0, 780 },
    { 2, 1, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent061Text11), 0, 782 },
    { 0, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent061Text12), 0, 810 },
    { 1, 3, 2, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent061Text13), 0, 830 },
    { 2, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent061Text14), 0, 850 },
    { 2, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent061Text15), 0, 950 },
    { 0, 4, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent061Text16), 0, 1130 },
    { 1, 3, 2, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent061Text17), MSG_SCRIPT_FLAG_END, 1230 },
};

#ifdef VERSION_JP
#include "event_061_text.inc"
#endif

static const EventCameraKeyframe sEvent061Camera[2] = {
    { -65536, 34304, 34560, 0, 255, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, NULL },
    { -55537, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 80, NULL },
};

static const EvSoundCue sEvent061SoundCues[5] = {
    { SONG_BGM_F13F_FORGET, 0, 0, 0 },
    { SONG_EV_GF_STONE_L, 990, 0, 0 },
    { SONG_SND_358, 1192, 0, 0 },
    { SONG_SND_358, 1372, 0, 0 },
    { SONG_BGM_F13F_FORGET, 1455, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent061Track0[19] = {
    { 4, 1, 73472, 55808, 0, 0, 2, NULL, NULL },
    { 9, 180, 29696, 36096, 0, 4, 3, NULL, NULL },
    { 4, 200, 0, 0, 0, 0, 5, NULL, NULL },
    { 74, 260, 0, 0, 0, 0, 5, NULL, NULL },
    { 74, 390, 0, 0, 0, 0, 0, NULL, CreateBalloonTask },
    { 74, 470, 0, 0, 0, 0, 5, NULL, NULL },
    { 76, 480, 0, 0, 0, 0, 5, NULL, NULL },
    { 4, 500, 0, 0, 0, 0, 5, NULL, NULL },
    { 3, 505, 0, 0, 0, 0, 5, NULL, NULL },
    { 2, 510, 0, 0, 0, 0, 5, NULL, NULL },
    { 1, 515, 0, 0, 0, 0, 5, NULL, NULL },
    { 2, 590, 0, 0, 0, 0, 69, NULL, NULL },
    { 32, 740, 0, 0, 0, 0, 64, NULL, CreateBalloonTask },
    { 32, 760, 0, 0, 0, 0, 69, NULL, NULL },
    { 2, 810, 0, 0, 0, 0, 69, NULL, NULL },
    { 32, 832, 0, 0, 0, 0, 69, NULL, NULL },
    { 2, 1150, 0, 0, 0, 0, 69, NULL, NULL },
    { 91, 1400, 0, 0, 0, 0, 85, NULL, NULL },
    { 92, 2000, 0, 0, 0, 0, 32853, NULL, NULL },
};

static const EventCharaKeyframe sEvent061Track1[25] = {
    { 114, 1, 71680, 65024, 0, 0, 2, NULL, NULL },
    { 119, 180, 32256, 45312, 0, 114, 3, NULL, NULL },
    { 114, 460, 0, 0, 0, 0, 5, NULL, NULL },
    { 126, 461, 0, 0, 0, 0, 5, NULL, NULL },
    { 114, 580, 0, 0, 0, 0, 5, NULL, NULL },
    { 126, 585, 0, 0, 0, 0, 5, NULL, NULL },
    { 127, 590, 0, 0, 0, 0, 5, NULL, NULL },
    { 127, 720, 0, 0, 0, 0, 0, NULL, CreateBalloonTask },
    { 127, 745, 0, 0, 0, 0, 5, NULL, NULL },
    { 129, 750, 0, 0, 0, 0, 5, NULL, NULL },
    { 110, 755, 0, 0, 0, 0, 5, NULL, NULL },
    { 114, 830, 0, 0, 0, 0, 69, NULL, NULL },
    { 126, 831, 0, 0, 0, 0, 69, NULL, NULL },
    { 114, 900, 0, 0, 0, 0, 69, NULL, NULL },
    { 114, 1225, 0, 0, 0, 0, 69, NULL, NULL },
    { 126, 1232, 0, 0, 0, 0, 85, NULL, NULL },
    { 114, 1235, 0, 0, 0, 0, 85, NULL, NULL },
    { 110, 1240, 0, 0, 0, 0, 21, NULL, NULL },
    { 114, 1250, 0, 0, 0, 0, 21, NULL, NULL },
    { 119, 1280, 30464, 39680, 0, 114, 19, NULL, NULL },
    { 114, 1300, 0, 0, 0, 0, 21, NULL, NULL },
    { 110, 1305, 0, 0, 0, 0, 21, NULL, NULL },
    { 114, 1330, 0, 0, 0, 0, 85, NULL, NULL },
    { 140, 1400, 0, 0, 0, 0, 85, NULL, NULL },
    { 141, 2000, 0, 0, 0, 0, 32853, NULL, NULL },
};

static const EventCharaKeyframe sEvent061Track2[18] = {
    { 146, 1, 83968, 57088, 0, 0, 2, NULL, NULL },
    { 151, 180, 42496, 34304, 0, 146, 3, NULL, NULL },
    { 146, 190, 0, 0, 0, 0, 5, NULL, NULL },
    { 145, 200, 0, 0, 0, 0, 5, NULL, NULL },
    { 144, 740, 0, 0, 0, 0, 5, NULL, NULL },
    { 164, 741, 0, 0, 0, 0, 5, NULL, NULL },
    { 144, 780, 0, 0, 0, 0, 5, NULL, NULL },
    { 164, 783, 0, 0, 0, 0, 5, NULL, NULL },
    { 144, 845, 0, 0, 0, 0, 5, NULL, NULL },
    { 164, 852, 0, 0, 0, 0, 5, NULL, NULL },
    { 144, 945, 0, 0, 0, 0, 5, NULL, NULL },
    { 164, 952, 0, 0, 0, 0, 5, NULL, NULL },
    { 144, 980, 0, 0, 0, 0, 5, NULL, NULL },
    { 149, 1000, 38656, 36864, 0, 144, 3, NULL, NULL },
    { 144, 1030, 0, 0, 0, 0, 5, NULL, NULL },
    { 145, 1050, 0, 0, 0, 0, 5, NULL, NULL },
    { 174, 1400, 0, 0, 0, 0, 5, NULL, NULL },
    { 175, 2000, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent061Track3[3] = {
    { 909, 226, 128000, 128000, 0, 0, 8194, NULL, NULL },
    { 913, 470, 29696, 36096, 0, 0, 16658, NULL, NULL },
    { 909, 1000, 128000, 128000, 0, 0, 98306, NULL, NULL },
};

static const EventCharaTrack sEvent061Tracks[4] = {
    { sEvent061Track0, 0 },
    { sEvent061Track1, 1 },
    { sEvent061Track2, 2 },
    { sEvent061Track3, 85 },
};

const EventSequenceDef gEvent061 = {
    4,
    sEvent061Tracks,
    sEvent061Camera,
    sEvent061Script,
    sEvent061SoundCues,
    NULL,
    1460,
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
    WORLD_CASTLE_OBLIVION,
    255,
};
