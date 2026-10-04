#ifdef VERSION_US
#include "event_184_text.inc"
#endif

static const MessageScriptEntry sEvent184Script[18] = {
    { 55, 3, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent184Text00), 0, 230 },
    { 55, 2, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent184Text01), 0, 232 },
    { 55, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent184Text02), 0, 600 },
    { 55, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent184Text03), 0, 900 },
    { 55, 1, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent184Text04), 0, 902 },
    { 55, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent184Text05), 0, 1000 },
    { 20, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent184Text06), 0, 1050 },
    { 20, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent184Text07), 0, 1230 },
    { 27, 0, 0, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent184Text08), 0, 1260 },
    { 20, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent184Text09), 0, 1290 },
    { 20, 0, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent184Text10), 0, 1292 },
    { 20, 1, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent184Text11), 0, 1294 },
    { 55, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent184Text12), 0, 1320 },
    { 20, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent184Text13), 0, 1380 },
    { 55, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent184Text14), 0, 1460 },
    { 20, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent184Text15), 0, 1500 },
    { 20, 1, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent184Text16), 0, 1502 },
    { 55, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent184Text17), MSG_SCRIPT_FLAG_END, 1650 },
};

#ifdef VERSION_JP
#include "event_184_text.inc"
#endif

static const EvSoundCue sEvent184SoundCues[5] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_EV_WARPOUT, 170, 0, 0 },
    { SONG_SND_368, 1530, 0, 0 },
    { SONG_SND_381, 1680, 0, 0 },
    { SONG_BGM_EVENT_XIII, 1710, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent184Camera[6] = {
    { -65196, 46592, 59136, 0, 255, 0, 0, NULL },
    { -65016, 83456, 69888, 0, 255, CAMERA_MODE_APPROACH, 80, NULL },
    { -64935, 46592, 59136, 0, 255, CAMERA_MODE_APPROACH, 80, NULL },
    { -63906, 57088, 59136, 0, 255, CAMERA_MODE_APPROACH, 50, NULL },
    { -63536, 30976, 110848, 0, 255, 0, 0, NULL },
    { -60536, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, NULL },
};

static const EventBgEffectEntry sEvent184BgEffects[5] = {
    { 1530, 0, 0, 0, 0 },
    { 1630, 0, 0, 0, 0x14 },
    { 3310, 0, 0, 0, 0 },
    { 3380, 0, 0, 0, 0x2 },
    { 3500, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent184Track0[10] = {
    { 902, 170, 111616, 23040, 0, 0, 2, NULL, NULL },
    { 903, 280, 47104, 65792, 0, 0, 2, EventCharaFadeIn, NULL },
    { 903, 521, 0, 0, 0, 0, 5, NULL, NULL },
    { 889, 595, 0, 0, 0, 0, 69, NULL, NULL },
    { 896, 605, 0, 0, 0, 0, 69, NULL, NULL },
    { 889, 1390, 0, 0, 0, 0, 69, NULL, NULL },
    { 896, 1440, 0, 0, 0, 0, 64, NULL, CreateExclamationTask },
    { 896, 1560, 0, 0, 0, 0, 69, NULL, NULL },
    { 896, 1600, 0, 0, 0, 0, 64, EventCharaFadeOut, NULL },
    { 902, 2000, 111616, 23040, 0, 0, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent184Track1[10] = {
    { 486, 601, 86528, 73216, 0, 0, 2, NULL, NULL },
    { 502, 720, 65536, 61440, 0, 486, 3, NULL, NULL },
    { 486, 730, 0, 0, 0, 0, 5, NULL, NULL },
    { 485, 1020, 0, 0, 0, 0, 5, NULL, NULL },
    { 509, 1330, 0, 0, 0, 0, 5, NULL, NULL },
    { 485, 1350, 0, 0, 0, 0, 5, NULL, NULL },
    { 499, 1470, 0, 0, 0, 0, 5, NULL, NULL },
    { 485, 1560, 0, 0, 0, 0, 5, NULL, NULL },
    { 485, 1600, 0, 0, 0, 0, 0, EventCharaFadeOut, NULL },
    { 486, 2000, 111616, 23040, 0, 0, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent184Track2[10] = {
    { 696, 601, 82432, 83456, 0, 0, 2, NULL, NULL },
    { 712, 700, 65024, 73984, 0, 696, 3, NULL, NULL },
    { 696, 750, 0, 0, 0, 0, 5, NULL, NULL },
    { 696, 880, 0, 0, 0, 0, 0, NULL, CreateBalloonTask },
    { 696, 1070, 0, 0, 0, 0, 5, NULL, NULL },
    { 696, 1200, 0, 0, 0, 0, 0, NULL, CreateBalloonTask },
    { 696, 1540, 0, 0, 0, 0, 5, NULL, NULL },
    { 712, 1560, 0, 0, 0, 211, 4, NULL, NULL },
    { 712, 1600, 0, 0, 0, 211, 4, EventCharaFadeOut, NULL },
    { 696, 2000, 111616, 23040, 0, 0, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent184Track3[3] = {
    { 928, 280, 0, 0, 0, 0, 8194, NULL, NULL },
    { 927, 330, 44544, 55552, 0, 0, 16658, NULL, NULL },
    { 928, 2000, 0, 0, 0, 0, 98306, NULL, NULL },
};

static const EventCharaTrack sEvent184Tracks[4] = {
    { sEvent184Track0, 83 },
    { sEvent184Track1, 43 },
    { sEvent184Track2, 65 },
    { sEvent184Track3, 93 },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent184 = {
    4,
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
    183,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif
