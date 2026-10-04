#ifdef VERSION_US
#include "event_168_text.inc"
#endif

static const MessageScriptEntry sEvent168Script[19] = {
    { 54, 4, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent168Text00), 0, 100 },
    { 54, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent168Text01), 0, 280 },
    { 27, 0, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent168Text02), 0, 300 },
    { 27, 0, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent168Text03), 0, 450 },
    { 54, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent168Text04), 0, 480 },
    { 27, 0, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent168Text05), 0, 570 },
    { 27, 0, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent168Text06), 0, 650 },
    { 27, 0, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent168Text07), 0, 830 },
    { 54, 4, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent168Text08), 0, 1170 },
    { 54, 2, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent168Text09), 0, 1172 },
    { 54, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent168Text10), 0, 1260 },
    { 54, 1, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent168Text11), 0, 1262 },
    { 60, 4, 0, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent168Text12), 0, 1305 },
    { 60, 4, 0, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent168Text13), 0, 1420 },
    { 60, 4, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent168Text14), 0, 1422 },
    { 60, 4, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent168Text15), 0, 1424 },
    { 54, 3, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent168Text16), 0, 1620 },
    { 54, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent168Text17), 0, 1622 },
    { 54, 1, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent168Text18), MSG_SCRIPT_FLAG_END, 1624 },
};

#ifdef VERSION_JP
#include "event_168_text.inc"
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
