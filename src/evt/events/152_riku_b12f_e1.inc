#ifdef VERSION_US
#include "event_152_text.inc"
#endif

static const MessageScriptEntry sEvent152Script[7] = {
    { 26, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent152Text00), 0, 405 },
    { 52, 0, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent152Text01), MSG_SCRIPT_FLAG_SILHOUETTE, 440 },
    { 26, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent152Text02), 0, 470 },
    { 26, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent152Text03), 0, 520 },
    { 52, 0, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent152Text04), MSG_SCRIPT_FLAG_SILHOUETTE, 550 },
    { 52, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent152Text05), MSG_SCRIPT_FLAG_SILHOUETTE, 552 },
    { 26, 2, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent152Text06), MSG_SCRIPT_FLAG_END, 600 },
};

#ifdef VERSION_JP
#include "event_152_text.inc"
#endif

static const EvSoundCue sEvent152SoundCues[2] = {
    { SONG_BGM_EVENT_SILENCE, 0, 0, 0 },
    { SONG_BGM_EVENT_SILENCE, 675, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent152Camera[3] = {
    { -65535, 78848, 59136, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65064, 63488, 67840, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -60536, 55808, 71168, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 30, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent152Track0[15] = {
    { 514, 1, { 0, 0 }, 88576, 59136, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 516, 120, { 0, 0 }, 64000, 73984, 0, 514, { 0, 0 }, 3, NULL, NULL },
    { 514, 130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 514, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 524, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 472, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 516, 500, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 514, 620, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 520, 1000, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 36, NULL, NULL },
    { 514, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent152Tracks[1] = {
    { sEvent152Track0, 44, { 0, 0, 0 } },
};

const EventSequenceDef gEvent152 = {
    1,
    { 0, 0, 0 },
    sEvent152Tracks,
    sEvent152Camera,
    sEvent152Script,
    sEvent152SoundCues,
    NULL,
    680,
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
