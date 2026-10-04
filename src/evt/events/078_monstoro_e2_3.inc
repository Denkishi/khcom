#ifdef VERSION_US
#include "event_078_text.inc"
#endif

static const MessageScriptEntry sEvent078Script[6] = {
    { 10, 8, 0, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent078Text00), 0, 100 },
    { 0, 2, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent078Text01), 0, 110 },
    { 10, 11, 0, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent078Text02), 0, 120 },
    { 0, 2, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent078Text03), 0, 130 },
    { 10, 2, 0, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent078Text04), 0, 140 },
    { 10, 14, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent078Text05), MSG_SCRIPT_FLAG_END, 142 },
};

#ifdef VERSION_JP
#include "event_078_text.inc"
#endif

static const EventCameraKeyframe sEvent078Camera[8] = {
    { -65376, 104448, 98304, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65366, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_SMALL | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65346, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65336, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_SMALL | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65316, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65256, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_MEDIUM | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65186, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_KEYFRAME_FLAG_SHAKE_MEDIUM | CAMERA_MODE_KEEP, 30, { 0, 0 }, NULL },
    { -64936, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent078SoundCues[9] = {
    { SONG_BGM_EVENT2, 0, 0, 0 },
    { SONG_EV_RUMBLE, 160, 0, 0 },
    { SONG_EV_RUMBLE, 161, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_EV_RUMBLE, 190, 0, 0 },
    { SONG_EV_RUMBLE, 191, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_EV_RUMBLE, 220, 0, 0 },
    { SONG_EV_RUMBLE, 225, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_EV_FLASH02, 250, 0, 0 },
    { SONG_BGM_EVENT2, 255, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent078Track0[1] = {
    { 20, 30, { 0, 0 }, 96000, 112640, 0, 0, { 0, 0 }, 33106, NULL, NULL },
};

static const EventCharaKeyframe sEvent078Track1[3] = {
    { 942, 245, { 0, 0 }, 0, 12800, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 943, 299, { 0, 0 }, 0, 12800, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 942, 500, { 0, 0 }, 0, 12800, 0, 0, { 0, 0 }, 32770, NULL, NULL },
};

static const EventCharaTrack sEvent078Tracks[2] = {
    { sEvent078Track0, 0, { 0, 0, 0 } },
    { sEvent078Track1, 97, { 0, 0, 0 } },
};

const EventSequenceDef gEvent078 = {
    2,
    { 0, 0, 0 },
    sEvent078Tracks,
    sEvent078Camera,
    sEvent078Script,
    sEvent078SoundCues,
    NULL,
    400,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    80,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
