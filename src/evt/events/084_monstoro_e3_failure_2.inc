#ifdef VERSION_US
#include "event_084_text.inc"
#endif

static const MessageScriptEntry sEvent084Script[3] = {
    { 6, 1, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent084Text00), 0, 100 },
    { 0, 7, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent084Text01), 0, 180 },
    { 2, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent084Text02), MSG_SCRIPT_FLAG_YES_NO | MSG_SCRIPT_FLAG_END, 200 },
};

#ifdef VERSION_JP
#include "event_084_text.inc"
#endif

static const EventCameraKeyframe sEvent084Camera[2] = {
    { -65416, 33792, 35840, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64537, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent084SoundCues[2] = {
    { SONG_BGM_EVENT1, 0, 0, 0 },
    { SONG_BGM_EVENT1, 219, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent084Track0[2] = {
    { 2, 200, { 0, 0 }, 35072, 36864, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 2, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent084Track1[2] = {
    { 114, 101, { 0, 0 }, 40448, 42752, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 114, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent084Track2[2] = {
    { 144, 200, { 0, 0 }, 26112, 39168, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 164, 201, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent084Track3[2] = {
    { 231, 510, { 0, 0 }, 24832, 45056, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 231, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent084Tracks[4] = {
    { sEvent084Track0, 0, { 0, 0, 0 } },
    { sEvent084Track1, 1, { 0, 0, 0 } },
    { sEvent084Track2, 2, { 0, 0, 0 } },
    { sEvent084Track3, 8, { 0, 0, 0 } },
};

const EventSequenceDef gEvent084 = {
    4,
    { 0, 0, 0 },
    sEvent084Tracks,
    sEvent084Camera,
    sEvent084Script,
    sEvent084SoundCues,
    NULL,
    220,
    0,
    1,
    0,
    0,
    0,
    0,
    121,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
