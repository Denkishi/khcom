#ifdef VERSION_US
#include "event_180_text.inc"
#endif

static const MessageScriptEntry sEvent180Script[1] = {
    { 26, 2, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent180Text00), MSG_SCRIPT_FLAG_END, 100 },
};

#ifdef VERSION_JP
#include "event_180_text.inc"
#endif

static const EvSoundCue sEvent180SoundCues[1] = {
    { SONG_BGM_BOSSWORLD, 0, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent180Camera[1] = {
    { -64537, 61440, 92160, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent180Track0[2] = {
    { 514, 40, { 0, 0 }, 51200, 99840, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 526, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent180Track1[1] = {
    { 944, 999, { 0, 0 }, 18432, 36864, 0, 0, { 0, 0 }, 32834, NULL, NULL },
};

static const EventCharaTrack sEvent180Tracks[2] = {
    { sEvent180Track0, 44, { 0, 0, 0 } },
    { sEvent180Track1, 103, { 0, 0, 0 } },
};

const EventSequenceDef gEvent180 = {
    2,
    { 0, 0, 0 },
    sEvent180Tracks,
    sEvent180Camera,
    sEvent180Script,
    sEvent180SoundCues,
    NULL,
    160,
    0,
    1,
    0,
    0,
    0,
    0,
    154,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
