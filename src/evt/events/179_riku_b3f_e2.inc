#ifdef VERSION_US
#include "event_179_text.inc"
#endif

static const MessageScriptEntry sEvent179Script[6] = {
    { 26, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent179Text00), 0, 355 },
    { 55, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent179Text01), 0, 385 },
    { 55, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent179Text02), 0, 510 },
    { 26, 5, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent179Text03), 0, 640 },
    { 55, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent179Text04), 0, 670 },
    { 55, 0, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent179Text05), MSG_SCRIPT_FLAG_END, 674 },
};

#ifdef VERSION_JP
#include "event_179_text.inc"
#endif

static const EvSoundCue sEvent179SoundCues[4] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_BGM_EVENT_XIII, 635, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT2, 642, 0, 0 },
    { SONG_SND_363, 840, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent179Camera[8] = {
    { -65536, 83456, 98048, 0, 255, 0, 0, NULL },
    { -65441, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_FADE_OUT_BLACK | CAMERA_MODE_KEEP, 30, NULL },
    { -65436, 32256, 98048, 0, 255, CAMERA_MODE_APPROACH, 1, NULL },
    { -65331, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_FADE_IN_BLACK | CAMERA_MODE_KEEP, 30, NULL },
    { -65026, 52992, 25088, 0, 255, CAMERA_MODE_APPROACH, 1, NULL },
    { -64856, 70144, 26624, 0, 255, CAMERA_MODE_APPROACH, 80, NULL },
    { -64437, 97024, 33536, 0, 255, CAMERA_MODE_APPROACH, 120, NULL },
    { -60536, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, NULL },
};

static const EventBgEffectEntry sEvent179BgEffects[5] = {
    { 180, 0, 0, 0, 0 },
    { 200, 0, 10, 0, 0x14 },
    { 210, 0, 0, 0, 0 },
    { 211, 0, 0, 0, 0x2 },
    { 250, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent179Track0[11] = {
    { 540, 205, 25344, 109312, 0, 0, 66, NULL, NULL },
    { 540, 250, 46080, 36352, 0, 0, 66, NULL, NULL },
    { 515, 260, 46080, 36352, 0, 0, 66, NULL, NULL },
    { 514, 290, 0, 0, 0, 0, 69, NULL, NULL },
    { 515, 300, 0, 0, 0, 0, 69, NULL, NULL },
    { 515, 330, 0, 0, 0, 0, 5, NULL, NULL },
    { 515, 350, 0, 0, 0, 0, 69, NULL, NULL },
    { 532, 380, 0, 0, 0, 0, 69, NULL, NULL },
    { 515, 560, 0, 0, 0, 0, 69, NULL, NULL },
    { 514, 3000, 0, 0, 0, 0, 69, NULL, NULL },
    { 514, 5000, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent179Track1[8] = {
    { 889, 205, 40960, 102400, 0, 0, 2, NULL, NULL },
    { 889, 410, 61696, 29440, 0, 0, 2, NULL, NULL },
    { 889, 460, 0, 0, 0, 0, 69, NULL, NULL },
    { 899, 512, 0, 0, 0, 0, 69, NULL, NULL },
    { 898, 625, 0, 0, 0, 0, 69, NULL, NULL },
    { 889, 672, 0, 0, 0, 0, 69, NULL, NULL },
    { 899, 800, 0, 0, 0, 0, 69, NULL, NULL },
    { 889, 5000, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent179Track2[3] = {
    { 515, 840, 95744, 40192, 0, 0, 66, NULL, NULL },
    { 515, 1600, 0, 0, 0, 0, 64, EventCharaFadeToBlack, NULL },
    { 515, 5000, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent179Tracks[3] = {
    { sEvent179Track0, 44 },
    { sEvent179Track1, 83 },
    { sEvent179Track2, 44 },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent179 = {
    3,
    sEvent179Tracks,
    sEvent179Camera,
    sEvent179Script,
    sEvent179SoundCues,
    sEvent179BgEffects,
    900,
    0,
    1,
    0,
    0,
    0,
    0,
    180,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent179 = {
    3,
    sEvent179Tracks,
    sEvent179Camera,
    sEvent179Script,
    sEvent179SoundCues,
    sEvent179BgEffects,
    900,
    0,
    1,
    0,
    0,
    0,
    0,
    178,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif
