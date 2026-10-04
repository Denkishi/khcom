#ifdef VERSION_US
static const MessageScriptEntry sEvent020Script[1] = {
    { 0, 0, 3, 1, gEvent020Text00, MSG_SCRIPT_FLAG_END, 1000 },
};

#include "event_020_text.inc"
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent020Script[1] = {
    { 0, 0, 3, 3, gEvent020Text00, MSG_SCRIPT_FLAG_END, 1000 },
};

#include "event_020_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent020Script[1] = {
    { 0, 0, 3, 1, NULL, MSG_SCRIPT_FLAG_END, 1000 },
};
#endif

static const EventCameraKeyframe sEvent020Camera[1] = {
    { -60536, 60672, 48384, 0, 255, CAMERA_KEYFRAME_FLAG_END, 0, NULL },
};

static const EvSoundCue sEvent020SoundCues[2] = {
    { SONG_BGM_EVENT_NAMINE, 0, 0, 0 },
    { SONG_BGM_EVENT_NAMINE, 395, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent020Track0[7] = {
    { 442, 80, 59904, 54016, 0, 0, 18, NULL, NULL },
    { 443, 180, 0, 0, 0, 0, 21, NULL, NULL },
    { 442, 200, 0, 0, 0, 0, 21, NULL, NULL },
    { 443, 250, 0, 0, 0, 0, 21, NULL, NULL },
    { 442, 280, 0, 0, 0, 0, 21, NULL, NULL },
    { 443, 300, 0, 0, 0, 0, 21, NULL, NULL },
    { 442, 5000, 0, 0, 0, 0, 32789, NULL, NULL },
};

static const EventCharaKeyframe sEvent020Track1[1] = {
    { 919, 5000, 60416, 53760, 0, 0, 33106, NULL, NULL },
};

static const EventCharaTrack sEvent020Tracks[2] = {
    { sEvent020Track0, 35 },
    { sEvent020Track1, 86 },
};

const EventSequenceDef gEvent020 = {
    2,
    sEvent020Tracks,
    sEvent020Camera,
    sEvent020Script,
    sEvent020SoundCues,
    NULL,
    400,
    0,
    0,
    0,
    0,
    0,
    0,
    21,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
