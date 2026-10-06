#ifdef VERSION_US
#include "event_030_text.inc"
#endif

static const MessageScriptEntry sEvent030Script[25] = {
    { 0, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent030Text00), 0, 200 },
    { 0, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent030Text01), 0, 300 },
    { 0, 4, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent030Text02), 0, 440 },
    { 26, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent030Text03), 0, 590 },
    { 26, 2, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent030Text04), 0, 592 },
    { 0, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent030Text05), 0, 610 },
    { 26, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent030Text06), 0, 630 },
    { 0, 2, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent030Text07), 0, 650 },
    { 26, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent030Text08), 0, 770 },
    { 26, 0, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent030Text09), 0, 772 },
    { 0, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent030Text10), 0, 790 },
    { 26, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent030Text11), 0, 810 },
    { 26, 0, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent030Text12), 0, 812 },
    { 0, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent030Text13), 0, 830 },
    { 26, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent030Text14), 0, 850 },
    { 0, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent030Text15), 0, 870 },
    { 26, 2, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent030Text16), 0, 890 },
    { 0, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent030Text17), 0, 910 },
    { 0, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent030Text18), 0, 1060 },
    { 26, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent030Text19), 0, 1080 },
    { 27, 2, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent030Text20), 0, 1155 },
    { 0, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent030Text21), 0, 1175 },
    { 27, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent030Text22), 0, 1195 },
    { 27, 2, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent030Text23), 0, 1197 },
    { 0, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent030Text24), MSG_SCRIPT_FLAG_END, 1225 },
};

#ifdef VERSION_JP
#include "event_030_text.inc"
#endif

static const EventCameraKeyframe sEvent030Camera[7] = {
    { -65316, 159744, 79360, 0, 255, 0, 0, NULL },
    { -65176, 205824, 54272, 0, 255, CAMERA_MODE_APPROACH, 60, NULL },
    { -64436, 194048, 60672, 0, 255, CAMERA_MODE_APPROACH, 60, NULL },
    { -64426, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 10, NULL },
    { -64416, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 10, NULL },
    { -64306, 0, 0, 0, 255, CAMERA_MODE_KEEP, 0, NULL },
    { -55537, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 20, NULL },
};

static const EvSoundCue sEvent030SoundCues[5] = {
    { 65535, 0, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 635, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT_UNREST, 1085, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_SND_359, 1110, 0, 0 },
    { SONG_BGM_EVENT2, 1160, EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent030Track0[16] = {
    { 4, 1, 125696, 101120, 0, 0, 66, NULL, NULL },
    { 9, 150, 160256, 83712, 0, 4, 67, NULL, NULL },
    { 27, 200, 0, 0, 0, 0, 64, NULL, CreateExclamationTask },
    { 27, 320, 0, 0, 0, 0, 69, NULL, NULL },
    { 14, 420, 189184, 68864, 0, 4, 67, NULL, NULL },
    { 4, 423, 0, 0, 0, 45, 68, NULL, NULL },
    { 4, 649, 0, 0, 0, 0, 69, NULL, NULL },
    { 30, 651, 0, 0, 0, 0, 69, NULL, NULL },
    { 4, 869, 0, 0, 0, 0, 69, NULL, NULL },
    { 30, 871, 0, 0, 0, 0, 69, NULL, NULL },
    { 4, 909, 0, 0, 0, 0, 69, NULL, NULL },
    { 30, 911, 0, 0, 0, 0, 69, NULL, NULL },
    { 4, 1174, 0, 0, 0, 0, 69, NULL, NULL },
    { 30, 1176, 0, 0, 0, 0, 69, NULL, NULL },
    { 4, 1220, 0, 0, 0, 0, 69, NULL, NULL },
    { 27, 9999, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent030Track1[8] = {
    { 114, 1, 124928, 108800, 0, 0, 66, NULL, NULL },
    { 119, 150, 156928, 90880, 0, 114, 67, NULL, NULL },
    { 114, 320, 0, 0, 0, 0, 69, NULL, NULL },
    { 120, 430, 185344, 77312, 0, 114, 67, NULL, NULL },
    { 114, 432, 0, 0, 0, 45, 68, NULL, NULL },
    { 114, 1120, 0, 0, 0, 0, 69, NULL, NULL },
    { 133, 1160, 0, 0, 0, 0, 69, NULL, NULL },
    { 114, 9999, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent030Track2[8] = {
    { 144, 1, 116736, 100864, 0, 0, 2, NULL, NULL },
    { 151, 150, 149248, 86016, 0, 146, 67, NULL, NULL },
    { 146, 325, 0, 0, 0, 0, 69, NULL, NULL },
    { 153, 435, 176640, 71424, 0, 146, 67, NULL, NULL },
    { 146, 437, 0, 0, 0, 45, 68, NULL, NULL },
    { 146, 1123, 0, 0, 0, 0, 69, NULL, NULL },
    { 161, 1162, 0, 0, 0, 0, 69, NULL, NULL },
    { 146, 9999, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent030Track3[8] = {
    { 514, 450, 204800, 60160, 0, 0, 2, NULL, NULL },
    { 514, 580, 0, 0, 0, 0, 0, NULL, CreateBalloonTask },
    { 514, 800, 0, 0, 0, 0, 5, NULL, NULL },
    { 524, 820, 0, 0, 0, 0, 5, NULL, NULL },
    { 514, 920, 0, 0, 0, 0, 5, NULL, NULL },
    { 514, 1050, 0, 0, 0, 0, 0, NULL, CreateBalloonTask },
    { 514, 1110, 0, 0, 0, 0, 5, NULL, NULL },
    { 514, 9999, 0, 0, 0, 0, 98309, NULL, NULL },
};

static const EventCharaKeyframe sEvent030Track4[2] = {
    { 695, 1110, 0, 0, 0, 0, 8194, NULL, NULL },
    { 698, 9999, 204800, 60160, 0, 0, 49154, NULL, NULL },
};

static const EventCharaTrack sEvent030Tracks[5] = {
    { sEvent030Track0, 0 },
    { sEvent030Track1, 1 },
    { sEvent030Track2, 2 },
    { sEvent030Track3, 44 },
    { sEvent030Track4, 65 },
};

const EventSequenceDef gEvent030 = {
    5,
    sEvent030Tracks,
    sEvent030Camera,
    sEvent030Script,
    sEvent030SoundCues,
    NULL,
    1275,
    0,
    1,
    0,
    0,
    0,
    BATTLE_RIKU_1,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
