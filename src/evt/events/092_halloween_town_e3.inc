#ifdef VERSION_US
#include "event_092_text.inc"
#endif

static const MessageScriptEntry sEvent092Script[1] = {
    { 12, 2, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent092Text00), MSG_SCRIPT_FLAG_END, 100 },
};

#ifdef VERSION_JP
#include "event_092_text.inc"
#endif

static const EventCameraKeyframe sEvent092Camera[1] = {
    { -65485, 94208, 153600, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent092SoundCues[1] = {
    { SONG_BGM_EVENT2, 0, EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent092Track0[1] = {
    { 20, 30, { 0, 0 }, 92160, 172032, 0, 0, { 0, 0 }, 32834, NULL, NULL },
};

static const EventCharaKeyframe sEvent092Track1[1] = {
    { 936, 30, { 0, 0 }, 78336, 58880, 0, 0, { 0, 0 }, 32770, NULL, NULL },
};

static const EventCharaTrack sEvent092Tracks[2] = {
    { sEvent092Track0, 0, { 0, 0, 0 } },
    { sEvent092Track1, 98, { 0, 0, 0 } },
};

const EventSequenceDef gEvent092 = {
    2,
    { 0, 0, 0 },
    sEvent092Tracks,
    sEvent092Camera,
    sEvent092Script,
    sEvent092SoundCues,
    NULL,
    200,
    0,
    1,
    0,
    0,
    0,
    0,
    155,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
