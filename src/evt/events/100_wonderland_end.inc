#ifdef VERSION_US
#include "event_100_text.inc"
#endif

static const MessageScriptEntry sEvent100Script[28] = {
    { 4, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent100Text00), 0, 200 },
    { 4, 1, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent100Text01), 0, 221 },
    { 0, 7, 2, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent100Text02), 0, 250 },
    { 4, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent100Text03), 0, 280 },
    { 4, 1, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent100Text04), 0, 300 },
    { 5, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent100Text05), 0, 320 },
    { 5, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent100Text06), 0, 330 },
    { 0, 3, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent100Text07), 0, 368 },
    { 5, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent100Text08), 0, 390 },
    { 5, 0, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent100Text09), 0, 392 },
    { 5, 1, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent100Text10), 0, 395 },
    { 0, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent100Text11), 0, 420 },
    { 0, 1, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent100Text12), 0, 425 },
    { 4, 2, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent100Text13), 0, 455 },
    { 5, 1, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent100Text14), 0, 480 },
    { 4, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent100Text15), 0, 500 },
    { 4, 3, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent100Text16), 0, 505 },
    { 5, 1, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent100Text17), 0, 800 },
    { 0, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent100Text18), 0, 820 },
    { 5, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent100Text19), 0, 840 },
    { 5, 0, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent100Text20), 0, 842 },
    { 5, 1, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent100Text21), 0, 844 },
    { 5, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent100Text22), 0, 1000 },
    { 0, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent100Text23), 0, 1020 },
    { 0, 4, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent100Text24), 0, 1022 },
    { 2, 1, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent100Text25), 0, 1050 },
    { 2, 1, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent100Text26), 0, 1052 },
    { 1, 4, 0, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent100Text27), MSG_SCRIPT_FLAG_END, 1070 },
};

#ifdef VERSION_JP
#include "event_100_text.inc"
#endif

static const EvSoundCue sEvent100SoundCues[4] = {
    { SONG_BGM_EVENT3, 1, 0, 0 },
    { SONG_EV_EV10_01, 301, 0, 0 },
    { SONG_EV_EV11_00, 506, 0, 0 },
    { SONG_BGM_EVENT3, 1070, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent100Camera[6] = {
    { -65506, 0, 0, 0, 0, 0, 0, NULL },
    { -65286, 67328, 70144, 0, 255, CAMERA_MODE_APPROACH, 60, NULL },
    { -64986, 0, 0, 0, 255, CAMERA_MODE_KEEP, 0, NULL },
    { -64736, 55808, 76800, 0, 255, CAMERA_MODE_APPROACH, 70, NULL },
    { -64446, 0, 0, 0, 255, CAMERA_MODE_KEEP, 0, NULL },
    { -64436, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_FADE_OUT_BLACK | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 30, NULL },
};

static const EventCharaKeyframe sEvent100Track0[13] = {
    { 4, 1, 61440, 81920, 0, 0, 66, NULL, NULL },
    { 4, 249, 0, 0, 0, 0, 69, NULL, NULL },
    { 36, 301, 0, 0, 0, 0, 69, NULL, NULL },
    { 4, 358, 0, 0, 0, 0, 69, NULL, NULL },
    { 27, 369, 0, 0, 0, 0, 0, NULL, CreateExclamationTask },
    { 28, 421, 0, 0, 0, 0, 5, NULL, NULL },
    { 4, 423, 0, 0, 0, 0, 5, NULL, NULL },
    { 4, 426, 0, 0, 0, 0, 69, NULL, NULL },
    { 4, 801, 0, 0, 0, 0, 69, NULL, NULL },
    { 4, 850, 0, 0, 0, 0, 5, NULL, NULL },
    { 34, 1020, 0, 0, 0, 0, 0, NULL, CreateBalloonTask },
    { 4, 1050, 0, 0, 0, 0, 5, NULL, NULL },
    { 3, 2200, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent100Track2[5] = {
    { 146, 836, 47104, 81408, 0, 0, 66, NULL, NULL },
    { 146, 1030, 0, 0, 0, 0, 69, NULL, NULL },
    { 145, 1049, 0, 0, 0, 0, 69, NULL, NULL },
    { 164, 1053, 0, 0, 0, 0, 69, NULL, NULL },
    { 144, 2200, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent100Track1[5] = {
    { 114, 1, 55808, 84992, 0, 0, 66, NULL, NULL },
    { 114, 840, 0, 0, 0, 0, 69, NULL, NULL },
    { 110, 1050, 0, 0, 0, 0, 5, NULL, NULL },
    { 114, 1069, 0, 0, 0, 0, 5, NULL, NULL },
    { 131, 1071, 0, 0, 0, 0, 32768, NULL, CreateSmokeTask },
};

static const EventCharaKeyframe sEvent100Track6[9] = {
    { 197, 301, 86016, 71168, 0, 0, 2, NULL, NULL },
    { 200, 360, 0, 0, 0, 0, 5, NULL, NULL },
    { 197, 516, 0, 0, 0, 0, 5, NULL, NULL },
    { 203, 528, 0, 0, 0, 83, 68, NULL, NULL },
    { 197, 605, 0, 0, 0, 0, 5, NULL, NULL },
    { 202, 625, 0, 0, 0, 211, 4, NULL, NULL },
    { 202, 690, 93696, 64000, 0, 199, 67, NULL, NULL },
    { 199, 2200, 0, 0, 0, 0, 66, NULL, NULL },
    { 197, 2200, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent100Track7[7] = {
    { 197, 308, 97280, 70144, 0, 0, 2, NULL, NULL },
    { 200, 368, 0, 0, 0, 0, 5, NULL, NULL },
    { 197, 690, 0, 0, 0, 0, 5, NULL, NULL },
    { 202, 710, 0, 0, 0, 211, 4, NULL, NULL },
    { 202, 730, 93696, 64000, 0, 199, 67, NULL, NULL },
    { 199, 2200, 0, 0, 0, 0, 66, NULL, NULL },
    { 197, 2200, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent100Track4[10] = {
    { 206, 301, 75520, 66816, 0, 0, 2, NULL, NULL },
    { 209, 360, 0, 0, 0, 0, 5, NULL, NULL },
    { 206, 516, 0, 0, 0, 0, 5, NULL, NULL },
    { 211, 528, 0, 0, 0, 211, 4, NULL, NULL },
    { 206, 560, 0, 0, 0, 0, 5, NULL, NULL },
    { 212, 590, 0, 0, 0, 83, 68, NULL, NULL },
    { 207, 594, 0, 0, 0, 0, 69, NULL, NULL },
    { 211, 660, 93696, 64000, 0, 208, 67, NULL, NULL },
    { 208, 2200, 0, 0, 0, 0, 66, NULL, NULL },
    { 208, 2200, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent100Track5[8] = {
    { 206, 308, 78592, 60672, 0, 0, 2, NULL, NULL },
    { 209, 368, 0, 0, 0, 0, 5, NULL, NULL },
    { 206, 655, 0, 0, 0, 0, 5, NULL, NULL },
    { 212, 685, 0, 0, 0, 83, 68, NULL, NULL },
    { 207, 688, 0, 0, 0, 0, 69, NULL, NULL },
    { 211, 705, 93696, 64000, 0, 208, 67, NULL, NULL },
    { 208, 2200, 0, 0, 0, 0, 66, NULL, NULL },
    { 206, 2200, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent100Track3[14] = {
    { 215, 201, 71424, 74752, 0, 0, 2, NULL, NULL },
    { 214, 220, 0, 0, 0, 173, 4, NULL, NULL },
    { 219, 281, 0, 0, 0, 0, 5, NULL, NULL },
    { 216, 284, 0, 0, 0, 0, 5, NULL, NULL },
    { 216, 321, 0, 0, 0, 0, 69, NULL, NULL },
    { 215, 331, 0, 0, 0, 0, 5, NULL, NULL },
    { 215, 395, 0, 0, 0, 0, 0, NULL, CreateExclamationTask },
    { 215, 505, 0, 0, 0, 0, 5, NULL, NULL },
    { 219, 520, 0, 0, 0, 0, 5, NULL, NULL },
    { 215, 523, 0, 0, 0, 0, 69, NULL, NULL },
    { 216, 529, 0, 0, 0, 0, 69, NULL, NULL },
    { 217, 600, 93696, 64000, 0, 216, 67, NULL, NULL },
    { 216, 2200, 0, 0, 0, 0, 66, NULL, NULL },
    { 215, 2200, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent100Track8[7] = {
    { 222, 310, 53248, 77568, 0, 0, 66, NULL, NULL },
    { 224, 319, 0, 0, 0, 45, 68, NULL, NULL },
    { 222, 393, 0, 0, 0, 0, 69, NULL, NULL },
    { 221, 450, 0, 0, 0, 0, 69, NULL, NULL },
    { 222, 830, 0, 0, 0, 0, 69, NULL, NULL },
    { 221, 1050, 0, 0, 0, 0, 69, NULL, NULL },
    { 221, 2200, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent100Tracks[9] = {
    { sEvent100Track0, 0 },
    { sEvent100Track1, 1 },
    { sEvent100Track2, 2 },
    { sEvent100Track3, 6 },
    { sEvent100Track4, 5 },
    { sEvent100Track5, 5 },
    { sEvent100Track6, 4 },
    { sEvent100Track7, 4 },
    { sEvent100Track8, 7 },
};

const EventSequenceDef gEvent100 = {
    9,
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
    65535,
    60,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
