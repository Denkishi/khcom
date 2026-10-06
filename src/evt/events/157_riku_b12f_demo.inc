#ifdef VERSION_US
#include "event_157_text.inc"
#endif

static const MessageScriptEntry sEvent157Script[18] = {
    { 55, 5, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent157Text00), 0, 370 },
    { 38, 0, 0, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent157Text01), 0, 520 },
    { 55, 5, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent157Text02), 0, 570 },
    { 55, 0, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent157Text03), 0, 572 },
    { 38, 2, 0, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent157Text04), 0, 590 },
    { 57, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent157Text05), 0, 610 },
    { 57, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent157Text06), 0, 810 },
    { 55, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent157Text07), 0, 1030 },
    { 55, 0, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent157Text08), 0, 1032 },
    { 38, 0, 0, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent157Text09), 0, 1060 },
    { 55, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent157Text10), 0, 1100 },
    { 55, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent157Text11), 0, 1280 },
    { 57, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent157Text12), 0, 1310 },
    { 55, 5, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent157Text13), 0, 1350 },
    { 55, 0, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent157Text14), 0, 1352 },
    { 38, 3, 0, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent157Text15), 0, 1380 },
    { 55, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent157Text16), 0, 1410 },
    { 57, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent157Text17), MSG_SCRIPT_FLAG_END, 1640 },
};

#ifdef VERSION_JP
#include "event_157_text.inc"
#endif

static const EvSoundCue sEvent157SoundCues[4] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_EV_WARPOUT, 150, 0, 0 },
    { SONG_EV_WARPOUT, 420, 0, 0 },
    { SONG_BGM_EVENT_XIII, 1695, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent157Camera[3] = {
    { -65406, 65536, 48640, 0, 255, 0, 0, NULL },
    { -65116, 58368, 52480, 0, 255, CAMERA_MODE_APPROACH, 50, NULL },
    { -64537, 65536, 54784, 0, 255, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 50, NULL },
};

static const EventCharaKeyframe sEvent157Track0[9] = {
    { 891, 300, 65792, 55808, 0, 0, 66, NULL, NULL },
    { 892, 320, 0, 0, 0, 0, 69, NULL, NULL },
    { 889, 550, 0, 0, 0, 0, 5, NULL, NULL },
    { 889, 830, 0, 0, 0, 0, 69, NULL, NULL },
    { 889, 960, 0, 0, 0, 0, 64, NULL, CreateBalloonTask },
    { 889, 990, 0, 0, 0, 0, 69, NULL, NULL },
    { 889, 1080, 0, 0, 0, 0, 5, NULL, NULL },
    { 889, 1260, 0, 0, 0, 0, 69, NULL, NULL },
    { 889, 5000, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent157Track1[10] = {
    { 738, 420, 0, 0, 0, 0, 2, NULL, NULL },
    { 738, 470, 84992, 72448, 0, 0, 2, EventCharaFadeIn, NULL },
    { 742, 500, 0, 0, 0, 211, 4, NULL, NULL },
    { 738, 630, 0, 0, 0, 0, 5, NULL, NULL },
    { 738, 760, 0, 0, 0, 0, 0, NULL, CreateBalloonTask },
    { 738, 1120, 0, 0, 0, 0, 5, NULL, NULL },
    { 738, 1250, 0, 0, 0, 0, 0, NULL, CreateBalloonTask },
    { 738, 1375, 0, 0, 0, 0, 5, NULL, NULL },
    { 740, 1382, 0, 0, 0, 0, 5, NULL, NULL },
    { 738, 5000, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent157Track2[9] = {
    { 883, 150, 0, 0, 0, 0, 66, NULL, NULL },
    { 883, 200, 50944, 64256, 0, 0, 66, EventCharaFadeIn, NULL },
    { 883, 400, 0, 0, 0, 0, 64, NULL, CreateBalloonTask },
    { 883, 780, 0, 0, 0, 0, 69, NULL, NULL },
    { 884, 1430, 0, 0, 0, 0, 69, NULL, NULL },
    { 883, 1450, 0, 0, 0, 0, 69, NULL, NULL },
    { 887, 1470, 0, 0, 0, 0, 69, NULL, NULL },
    { 887, 1600, 0, 0, 0, 0, 64, NULL, CreateBalloonTask },
    { 887, 5000, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent157Tracks[3] = {
    { sEvent157Track0, 83 },
    { sEvent157Track1, 67 },
    { sEvent157Track2, 82 },
};

const EventSequenceDef gEvent157 = {
    3,
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
    EVENT_158_RIKU_B11F_ENTRANCE,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
