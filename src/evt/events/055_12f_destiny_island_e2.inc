#ifdef VERSION_US
#include "event_055_text.inc"
#endif

static const MessageScriptEntry sEvent055Script[1] = {
    { 0, 3, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent055Text00), MSG_SCRIPT_FLAG_END, 115 },
};

#ifdef VERSION_JP
#include "event_055_text.inc"
#endif

static const EventCameraKeyframe sEvent055Camera[1] = {
    { -60536, 60928, 26880, 0, 255, CAMERA_KEYFRAME_FLAG_SHAKE_SMALL | CAMERA_KEYFRAME_FLAG_END, 0, NULL },
};

static const EvSoundCue sEvent055SoundCues[3] = {
    { SONG_BGM_EVENT2, 0, 0, 0 },
    { SONG_EV_RUMBLE, 1, 0, 0 },
    { SONG_EV_RUMBLE, 155, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent055Track0[5] = {
    { 4, 5, 96256, 49152, 0, 0, 2, NULL, NULL },
    { 14, 85, 0, 0, 0, 211, 36, NULL, NULL },
    { 4, 88, 0, 0, 0, 211, 36, NULL, NULL },
    { 4, 110, 0, 0, 0, 0, 5, NULL, NULL },
    { 27, 5000, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent055Tracks[1] = {
    { sEvent055Track0, 0 },
};

const EventSequenceDef gEvent055 = {
    1,
    sEvent055Tracks,
    sEvent055Camera,
    sEvent055Script,
    sEvent055SoundCues,
    NULL,
    160,
    0,
    1,
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
