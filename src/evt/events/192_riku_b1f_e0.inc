#ifdef VERSION_US
#include "event_192_text.inc"
#endif

static const MessageScriptEntry sEvent192Script[3] = {
    { 26, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent192Text00), 0, 150 },
    { 56, 1, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent192Text01), 0, 250 },
    { 56, 1, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent192Text02), MSG_SCRIPT_FLAG_END, 300 },
};

#ifdef VERSION_JP
#include "event_192_text.inc"
#endif

static const EvSoundCue sEvent192SoundCues[3] = {
    { SONG_BGM_F13F_FORGET, 0, 0, 0 },
    { SONG_SND_359, 110, 0, 0 },
    { SONG_BGM_F13F_FORGET, 475, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent192Camera[2] = {
    { -65536, 35072, 32512, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, NULL },
    { -64537, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 80, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent192Track0[9] = {
    { 515, 1, { 0, 0 }, 67328, 56576, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 522, 100, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 515, 103, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 515, 110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 560, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 562, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 522, 1000, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent192Tracks[1] = {
    { sEvent192Track0, 44, { 0, 0, 0 } },
};

const EventSequenceDef gEvent192 = {
    1,
    { 0, 0, 0 },
    sEvent192Tracks,
    sEvent192Camera,
    sEvent192Script,
    sEvent192SoundCues,
    NULL,
    480,
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
