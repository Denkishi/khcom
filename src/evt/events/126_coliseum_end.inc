#ifdef VERSION_US
#include "event_126_text.inc"
#endif

static const MessageScriptEntry sEvent126Script[21] = {
    { 0, 3, 0, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent126Text00), 0, 150 },
    { 45, 1, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent126Text01), 0, 180 },
    { 45, 1, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent126Text02), 0, 182 },
    { 2, 2, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent126Text03), 0, 210 },
    { 0, 2, 0, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent126Text04), 0, 240 },
    { 46, 4, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent126Text05), 0, 300 },
    { 46, 1, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent126Text06), 0, 302 },
    { 0, 0, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent126Text07), 0, 490 },
    { 46, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent126Text08), 0, 520 },
    { 6, 3, 0, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent126Text09), 0, 600 },
    { 0, 0, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent126Text10), 0, 730 },
    { 35, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent126Text11), 0, 750 },
    { 35, 2, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent126Text12), 0, 810 },
    { 0, 3, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent126Text13), 0, 881 },
    { 0, 1, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent126Text14), 0, 920 },
    { 0, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent126Text15), 0, 922 },
    { 0, 5, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent126Text16), 0, 1030 },
    { 0, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent126Text17), 0, 1032 },
    { 35, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent126Text18), 0, 1360 },
    { 0, 1, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent126Text19), 0, 1401 },
    { 35, 2, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent126Text20), MSG_SCRIPT_FLAG_END, 1480 },
};

#ifdef VERSION_JP
#include "event_126_text.inc"
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
