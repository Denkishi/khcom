#ifdef VERSION_US
#include "event_105_text.inc"
#endif

static const MessageScriptEntry sEvent105Script[1] = {
    { 14, 2, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent105Text00), MSG_SCRIPT_FLAG_END, 100 },
};

#ifdef VERSION_JP
#include "event_105_text.inc"
#endif

static const EvSoundCue sEvent105SoundCues[1] = {
    { SONG_BGM_EVENT2, 0, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent105Camera[1] = {
    { -64626, 81920, 102400, 0, 255, CAMERA_KEYFRAME_FLAG_END, 0, NULL },
};

static const EventCharaKeyframe sEvent105Track0[1] = {
    { 21, 459, 81920, 122880, 0, 0, 32834, NULL, NULL },
};

static const EventCharaKeyframe sEvent105Track1[1] = {
    { 937, 459, 45312, 60928, 0, 0, 32770, NULL, NULL },
};

static const EventCharaTrack sEvent105Tracks[2] = {
    { sEvent105Track0, 0 },
    { sEvent105Track1, 99 },
};

const EventSequenceDef gEvent105 = {
    2,
    sEvent105Tracks,
    sEvent105Camera,
    sEvent105Script,
    sEvent105SoundCues,
    NULL,
    150,
    0,
    1,
    0,
    0,
    0,
    151,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
