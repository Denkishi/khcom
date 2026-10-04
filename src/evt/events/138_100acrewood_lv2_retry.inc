#ifdef VERSION_US
static const MessageScriptEntry sEvent138Script[1] = {
    { 48, 1, 1, 1, { 0, 0, 0 }, gCardMessageTextUs_0903C186, MSG_SCRIPT_FLAG_END, 150 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent138Script[1] = {
    { 48, 1, 1, 3, { 0, 0, 0 }, gEvent138Text00, MSG_SCRIPT_FLAG_END, 150 },
};

#include "event_138_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent138Script[1] = {
    { 48, 1, 1, 1, { 0, 0, 0 }, &gCardMessageText055, MSG_SCRIPT_FLAG_END, 150 },
};
#endif

static const EvSoundCue sEvent138SoundCues[2] = {
    { SONG_BGM_WINNIETHEPOOH, 1, 0, 0 },
    { SONG_BG_POO, 2, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent138Camera[1] = {
    { -65226, 237824, 121344, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent138Track0[2] = {
    { 4, 130, { 0, 0 }, 235008, 129536, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 4, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent138Track1[2] = {
    { 756, 180, { 0, 0 }, 229120, 126464, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 756, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent138Track2[3] = {
    { 814, 80, { 0, 0 }, 244736, 121344, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 815, 415, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 815, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent138Tracks[3] = {
    { sEvent138Track0, 0, { 0, 0, 0 } },
    { sEvent138Track1, 70, { 0, 0, 0 } },
    { sEvent138Track2, 73, { 0, 0, 0 } },
};

const EventSequenceDef gEvent138 = {
    3,
    { 0, 0, 0 },
    sEvent138Tracks,
    sEvent138Camera,
    sEvent138Script,
    sEvent138SoundCues,
    NULL,
    210,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    2,
};
