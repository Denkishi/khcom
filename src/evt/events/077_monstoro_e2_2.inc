#ifdef VERSION_US
#include "event_077_text.inc"
#endif

static const MessageScriptEntry sEvent077Script[3] = {
    { 0, 2, 2, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent077Text00), 0, 100 },
    { 10, 11, 0, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent077Text01), 0, 150 },
    { 0, 3, 2, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent077Text02), MSG_SCRIPT_FLAG_END, 170 },
};

#ifdef VERSION_JP
#include "event_077_text.inc"
#endif

static const EventCameraKeyframe sEvent077Camera[1] = {
    { -65485, 104448, 98304, 0, 255, CAMERA_KEYFRAME_FLAG_END, 0, NULL },
};

static const EvSoundCue sEvent077SoundCues[1] = {
    { SONG_BGM_EVENT2, 0, EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent077Track1[6] = {
    { 20, 1, 96000, 112640, 0, 0, 66, NULL, NULL },
    { 4, 78, 0, 0, 0, 0, 85, NULL, NULL },
    { 2, 90, 0, 0, 0, 0, 85, NULL, NULL },
    { 3, 169, 0, 0, 0, 0, 85, NULL, NULL },
    { 3, 171, 0, 0, 0, 0, 80, NULL, CreateExclamationTask },
    { 18, 230, 0, 0, 0, 0, 32853, NULL, NULL },
};

static const EventCharaKeyframe sEvent077Track0[1] = {
    { 934, 999, 0, 12800, 0, 0, 32770, NULL, NULL },
};

static const EventCharaTrack sEvent077Tracks[2] = {
    { sEvent077Track0, 96 },
    { sEvent077Track1, 0 },
};

const EventSequenceDef gEvent077 = {
    2,
    sEvent077Tracks,
    sEvent077Camera,
    sEvent077Script,
    sEvent077SoundCues,
    NULL,
    280,
    0,
    1,
    0,
    0,
    0,
    BATTLE_PARASITE_CAGE,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
