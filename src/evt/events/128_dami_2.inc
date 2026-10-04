#ifndef VERSION_EU
#ifdef VERSION_US
static const MessageScriptEntry sEvent128Script[4] = {
    { 32, 0, 1, 1, gEvent128Text00, 0, 150 },
    { 0, 0, 3, 1, gEvent128Text01, 0, 180 },
    { 32, 0, 1, 1, gEvent128Text02, 0, 210 },
    { 32, 0, 4, 1, gEvent128Text03, MSG_SCRIPT_FLAG_END, 240 },
};

#include "event_128_text.inc"
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent128Script[4] = {
    { 32, 0, 1, 3, gEvent128Text00, 0, 150 },
    { 0, 0, 3, 3, gEvent128Text01, 0, 180 },
    { 32, 0, 1, 3, gEvent128Text02, 0, 210 },
    { 32, 0, 4, 3, gEvent128Text03, MSG_SCRIPT_FLAG_END, 240 },
};

#include "event_128_text.inc"
#endif
static const EventCameraKeyframe sEvent128Camera[1] = {
    { -55537, 80384, 58368, 0, 255, CAMERA_KEYFRAME_FLAG_END, 0, NULL },
};

static const EvSoundCue sEvent128SoundCues[1] = {
    { SONG_BGM_TOWN_FIELD, 0, EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent128Track0[1] = {
    { 4, 9999, 72960, 68096, 0, 0, 32834, NULL, NULL },
};

static const EventCharaKeyframe sEvent128Track1[1] = {
    { 451, 9999, 82432, 63232, 0, 0, 32770, NULL, NULL },
};

static const EventCharaKeyframe sEvent128Track2[1] = {
    { 638, 9999, 98304, 67840, 0, 0, 32770, NULL, NULL },
};

static const EventCharaKeyframe sEvent128Track3[1] = {
    { 684, 9999, 64512, 62464, 0, 0, 32834, NULL, NULL },
};

static const EventCharaKeyframe sEvent128Track4[1] = {
    { 114, 9999, 68352, 75264, 0, 0, 32834, NULL, NULL },
};

static const EventCharaKeyframe sEvent128Track5[1] = {
    { 146, 9999, 57088, 72448, 0, 0, 32834, NULL, NULL },
};

static const EventCharaTrack sEvent128Tracks[6] = {
    { sEvent128Track0, 0 },
    { sEvent128Track1, 36 },
    { sEvent128Track2, 57 },
    { sEvent128Track3, 63 },
    { sEvent128Track4, 1 },
    { sEvent128Track5, 2 },
};

const EventSequenceDef gEvent128 = {
    6,
    sEvent128Tracks,
    sEvent128Camera,
    sEvent128Script,
    sEvent128SoundCues,
    NULL,
    350,
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
    255,
};
#endif
