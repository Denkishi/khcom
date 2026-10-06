#ifdef VERSION_US
#include "event_113_text.inc"
#endif

static const MessageScriptEntry sEvent113Script[1] = {
    { 0, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent113Text00), MSG_SCRIPT_FLAG_END, 250 },
};

#ifdef VERSION_JP
#include "event_113_text.inc"
#endif

static const EventCameraKeyframe sEvent113Camera[3] = {
    { -65536, 146944, 75776, 0, 255, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, NULL },
    { -65336, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 100, NULL },
    { -55537, 146944, 75776, 0, 255, CAMERA_KEYFRAME_FLAG_END, 0, NULL },
};

static const EvSoundCue sEvent113SoundCues[1] = {
    { SONG_BGM_EVENT2, 0, EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent113Track0[1] = {
    { 20, 10, 179712, 106496, 0, 0, 32834, NULL, NULL },
};

static const EventCharaKeyframe sEvent113Track1[1] = {
    { 940, 10, 86528, 14080, 0, 0, 32770, NULL, NULL },
};

static const EventCharaTrack sEvent113Tracks[2] = {
    { sEvent113Track0, 0 },
    { sEvent113Track1, 101 },
};

const EventSequenceDef gEvent113 = {
    2,
    sEvent113Tracks,
    sEvent113Camera,
    sEvent113Script,
    sEvent113SoundCues,
    NULL,
    300,
    0,
    1,
    0,
    0,
    0,
    BATTLE_JAFAR,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
