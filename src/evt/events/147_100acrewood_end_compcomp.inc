#ifdef VERSION_US
#include "event_147_text.inc"
#endif

static const MessageScriptEntry sEvent147Script[6] = {
    { 36, 2, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent145Text00), 0, 400 },
    { 0, 4, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent145Text01), 0, 430 },
    { 36, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent147Text02), 0, 560 },
    { 0, 4, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent147Text03), 0, 590 },
    { 36, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent147Text04), 0, 620 },
    { 36, 1, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent147Text05), MSG_SCRIPT_FLAG_END, 622 },
};

#ifdef VERSION_JP
#include "event_147_text.inc"
#endif

static const EvSoundCue sEvent147SoundCues[6] = {
    { SONG_BGM_WINNIETHEPOOH, 0, 0, 0 },
    { SONG_BG_POO, 2, 0, 0 },
    { SONG_BGM_WINNIETHEPOOH, 425, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT4, 555, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BG_POO, 674, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT4, 675, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent147Camera[1] = {
    { -64537, 790528, 416512, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent147Track0[8] = {
    { 2, 1, { 0, 0 }, 772096, 412160, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 7, 100, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 2, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 1, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent147Track1[6] = {
    { 756, 1, { 0, 0 }, 757248, 404224, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 781, 230, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 4, NULL, NULL },
    { 756, 240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 795, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 797, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 756, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent147Tracks[2] = {
    { sEvent147Track0, 0, { 0, 0, 0 } },
    { sEvent147Track1, 70, { 0, 0, 0 } },
};

const EventSequenceDef gEvent147 = {
    2,
    { 0, 0, 0 },
    sEvent147Tracks,
    sEvent147Camera,
    sEvent147Script,
    sEvent147SoundCues,
    NULL,
    680,
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
    7,
};
