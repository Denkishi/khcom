#ifdef VERSION_US
#include "event_188_text.inc"
#endif

static const MessageScriptEntry sEvent188Script[9] = {
    { 27, 5, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent188Text00), 0, 260 },
    { 27, 1, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent188Text01), 0, 470 },
    { 27, 5, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent188Text02), 0, 472 },
    { 26, 5, 0, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent188Text03), 0, 500 },
    { 27, 5, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent188Text04), 0, 690 },
    { 27, 5, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent188Text05), 0, 800 },
    { 26, 5, 0, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent188Text06), 0, 850 },
    { 27, 1, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent188Text07), 0, 880 },
    { 27, 4, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent188Text08), MSG_SCRIPT_FLAG_END, 1000 },
};

#ifdef VERSION_JP
#include "event_188_text.inc"
#endif

static const EvSoundCue sEvent188SoundCues[4] = {
    { 65535, 0, 0, 0 },
    { SONG_BGM_EVENT_SILENCE, 465, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_SND_379, 1080, 0, 0 },
    { SONG_BGM_EVENT_SILENCE, 1195, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent188Camera[1] = {
    { -64537, 65024, 88576, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent188Track0[5] = {
    { 561, 150, { 0, 0 }, 73728, 99328, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 562, 165, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 290, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent188Track1[5] = {
    { 705, 100, { 0, 0 }, 56064, 93952, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 705, 530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 1048901, NULL, NULL },
    { 705, 1080, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 1048901, NULL, NULL },
    { 705, 1200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 1048896, EventCharaFadeOut, NULL },
    { 705, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98370, NULL, NULL },
};

static const EventCharaKeyframe sEvent188Track2[3] = {
    { 928, 529, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 928, 660, { 0, 0 }, 54528, 86784, 0, 0, { 0, 0 }, 16642, NULL, NULL },
    { 928, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaTrack sEvent188Tracks[3] = {
    { sEvent188Track0, 44, { 0, 0, 0 } },
    { sEvent188Track1, 65, { 0, 0, 0 } },
    { sEvent188Track2, 93, { 0, 0, 0 } },
};

const EventSequenceDef gEvent188 = {
    3,
    { 0, 0, 0 },
    sEvent188Tracks,
    sEvent188Camera,
    sEvent188Script,
    sEvent188SoundCues,
    NULL,
    1200,
    0,
    0,
    0,
    0,
    1,
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
