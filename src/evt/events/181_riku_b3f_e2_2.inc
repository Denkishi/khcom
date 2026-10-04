#ifdef VERSION_US
#include "event_181_text.inc"
#endif

static const MessageScriptEntry sEvent181Script[7] = {
    { 26, 3, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent181Text00), 0, 210 },
    { 26, 3, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent181Text01), 0, 260 },
    { 0, 2, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent181Text02), 0, 290 },
    { 26, 3, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent181Text03), 0, 440 },
    { 0, 5, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent181Text04), 0, 460 },
    { 0, 5, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent181Text05), 0, 462 },
    { 0, 2, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent181Text06), MSG_SCRIPT_FLAG_END, 562 },
};

#ifdef VERSION_JP
#include "event_181_text.inc"
#endif

static const EvSoundCue sEvent181SoundCues[5] = {
    { SONG_BGM_EVENT_UNREST, 0, 0, 0 },
    { SONG_EV_FLASH01, 233, 0, 0 },
    { SONG_EV_FLASH00, 390, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 615, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_EV_WHITEOUT, 620, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent181Camera[9] = {
    { -65366, 67840, 29696, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65356, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -65303, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65293, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -65146, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65136, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -64916, 77824, 37888, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -64536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 100, { 0, 0 }, NULL },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent181Track0[11] = {
    { 561, 100, { 0, 0 }, 65536, 36608, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 561, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 561, 165, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 542, 180, { 0, 0 }, 69120, 37120, 0, 515, { 0, 0 }, 4099, NULL, NULL },
    { 542, 232, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 542, 242, { 0, 0 }, 74752, 38912, 0, 515, { 0, 0 }, 4099, NULL, NULL },
    { 542, 255, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 534, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 550, 415, { 0, 0 }, 87040, 40704, 0, 515, { 0, 0 }, 3, NULL, NULL },
    { 547, 670, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 547, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32832, EventCharaBlendUp, NULL },
};

static const EventCharaKeyframe sEvent181Track1[12] = {
    { 2, 152, { 0, 0 }, 32000, 31744, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 98, 172, { 0, 0 }, 58624, 35584, 0, 2, { 0, 0 }, 4163, NULL, NULL },
    { 98, 190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 103, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 98, 240, { 0, 0 }, 62208, 36096, 0, 2, { 0, 0 }, 4163, NULL, NULL },
    { 98, 255, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 103, 330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 96, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 93, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 102, 586, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 103, 670, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 103, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32832, EventCharaBlendUp, NULL },
};

static const EventCharaKeyframe sEvent181Track2[3] = {
    { 922, 610, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 922, 623, { 0, 0 }, 61696, 37888, 0, 0, { 0, 0 }, 16642, NULL, NULL },
    { 922, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaTrack sEvent181Tracks[3] = {
    { sEvent181Track0, 44, { 0, 0, 0 } },
    { sEvent181Track1, 0, { 0, 0, 0 } },
    { sEvent181Track2, 89, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent181 = {
    3,
    { 0, 0, 0 },
    sEvent181Tracks,
    sEvent181Camera,
    sEvent181Script,
    sEvent181SoundCues,
    NULL,
    850,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    182,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent181 = {
    3,
    { 0, 0, 0 },
    sEvent181Tracks,
    sEvent181Camera,
    sEvent181Script,
    sEvent181SoundCues,
    NULL,
    850,
    0,
    0,
    0,
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
#endif
