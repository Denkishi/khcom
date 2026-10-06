#ifdef VERSION_US
#include "event_070_text.inc"
#endif

static const MessageScriptEntry sEvent070Script[1] = {
    { 58, 1, 0, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent070Text00), MSG_SCRIPT_FLAG_END, 300 },
};

#ifdef VERSION_JP
#include "event_070_text.inc"
#endif

static const EventCameraKeyframe sEvent070Camera[3] = {
    { -65206, 97280, 113664, 0, 255, 0, 0, NULL },
    { -63536, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_SHAKE_SMALL | CAMERA_MODE_KEEP, 0, NULL },
    { -55537, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, NULL },
};

static const EvSoundCue sEvent070SoundCues[3] = {
    { 65535, 0, 0, 0 },
    { SONG_EV_RUMBLE, 330, 0, 0 },
    { SONG_EV_RUMBLE, 595, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent070Track0[7] = {
    { 3, 100, 57088, 122368, 0, 0, 322, NULL, NULL },
    { 13, 160, 0, 0, 0, 64, 356, NULL, NULL },
    { 3, 163, 0, 0, 0, 64, 324, NULL, NULL },
    { 3, 170, 0, 0, 0, 0, 325, NULL, NULL },
    { 18, 350, 0, 0, 0, 0, 325, NULL, NULL },
    { 20, 400, 0, 0, 0, 0, 320, NULL, CreateExclamationTask },
    { 20, 1000, 0, 0, 0, 0, 33093, NULL, NULL },
};

static const EventCharaKeyframe sEvent070Track1[2] = {
    { 938, 430, 0, 0, 0, 0, 2, NULL, NULL },
    { 939, 9999, 0, 0, 0, 0, 32770, NULL, NULL },
};

static const EventCharaTrack sEvent070Tracks[2] = {
    { sEvent070Track0, 0 },
    { sEvent070Track1, 100 },
};

const EventSequenceDef gEvent070 = {
    2,
    sEvent070Tracks,
    sEvent070Camera,
    sEvent070Script,
    sEvent070SoundCues,
    NULL,
    600,
    0,
    1,
    0,
    0,
    0,
    BATTLE_MARLUXIA_2,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
