#ifdef VERSION_US
#include "event_122_text.inc"
#endif

static const MessageScriptEntry sEvent122Script[16] = {
    { 2, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent122Text00), 0, 170 },
    { 1, 4, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent122Text01), 0, 200 },
    { 0, 2, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent122Text02), 0, 260 },
    { 35, 2, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent122Text03), 0, 310 },
    { 2, 1, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent122Text04), 0, 440 },
    { 1, 0, 0, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent122Text05), 0, 470 },
    { 0, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent122Text06), 0, 500 },
    { 0, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent122Text07), 0, 780 },
    { 35, 2, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent122Text08), 0, 830 },
    { 35, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent122Text09), 0, 860 },
    { 0, 3, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent122Text10), 0, 940 },
    { 35, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent122Text11), 0, 970 },
    { 35, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent122Text12), 0, 1220 },
    { 0, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent122Text13), 0, 1250 },
    { 0, 1, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent122Text14), 0, 1252 },
    { 35, 2, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent122Text15), MSG_SCRIPT_FLAG_END, 1440 },
};

#ifdef VERSION_JP
#include "event_122_text.inc"
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
