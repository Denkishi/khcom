#ifdef VERSION_US
#include "event_174_text.inc"
#endif

static const MessageScriptEntry sEvent174Script[4] = {
    { 26, 5, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent174Text00), 0, 100 },
    { 26, 5, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent174Text01), 0, 250 },
    { 26, 2, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent174Text02), 0, 485 },
    { 26, 5, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent174Text03), MSG_SCRIPT_FLAG_END, 750 },
};

#ifdef VERSION_JP
#include "event_174_text.inc"
#endif

static const EvSoundCue sEvent174SoundCues[1] = {
    { SONG_BGM_T13THFLOOR, 0, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent174Camera[1] = {
    { -64537, 194816, 62720, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent174Track0[15] = {
    { 547, 150, { 0, 0 }, 195840, 64512, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 545, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 546, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 430, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 440, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 538, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 514, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 514, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 514, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 564, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent174Tracks[1] = {
    { sEvent174Track0, 44, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent174 = {
    1,
    { 0, 0, 0 },
    sEvent174Tracks,
    sEvent174Camera,
    sEvent174Script,
    sEvent174SoundCues,
    NULL,
    810,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    175,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent174 = {
    1,
    { 0, 0, 0 },
    sEvent174Tracks,
    sEvent174Camera,
    sEvent174Script,
    sEvent174SoundCues,
    NULL,
    810,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    173,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif
