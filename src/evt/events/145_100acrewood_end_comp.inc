static const MessageScriptEntry sEvent145Script[10] = {
    { 36, 2, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent145Text00), 0, 400 },
    { 0, 4, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent145Text01), 0, 430 },
    { 36, 1, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent143Text08), 0, 460 },
    { 0, 3, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent143Text09), 0, 600 },
    { 36, 2, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent143Text10), 0, 650 },
    { 0, 4, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent143Text11), 0, 680 },
    { 0, 5, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent143Text12), 0, 800 },
    { 36, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent143Text13), 0, 890 },
    { 36, 1, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent143Text14), 0, 892 },
    { 0, 4, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent143Text15), MSG_SCRIPT_FLAG_END, 940 },
};

#ifdef VERSION_JP
#include "event_145_text.inc"
#endif

static const EvSoundCue sEvent145SoundCues[6] = {
    { SONG_BGM_WINNIETHEPOOH, 1, 0, 0 },
    { SONG_BG_POO, 2, 0, 0 },
    { SONG_BGM_WINNIETHEPOOH, 425, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT4, 455, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BG_POO, 994, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT4, 995, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent145Camera[1] = {
    { -64537, 790528, 416512, 0, 255, CAMERA_KEYFRAME_FLAG_END, 0, NULL },
};

static const EventCharaKeyframe sEvent145Track0[11] = {
    { 2, 1, 772096, 412160, 0, 0, 66, NULL, NULL },
    { 7, 100, 0, 0, 0, 83, 68, NULL, NULL },
    { 2, 150, 0, 0, 0, 0, 69, NULL, NULL },
    { 1, 160, 0, 0, 0, 0, 5, NULL, NULL },
    { 2, 170, 0, 0, 0, 0, 5, NULL, NULL },
    { 3, 180, 0, 0, 0, 0, 5, NULL, NULL },
    { 4, 690, 0, 0, 0, 0, 5, NULL, NULL },
    { 4, 740, 0, 0, 0, 0, 0, NULL, CreateExclamationTask },
    { 4, 750, 0, 0, 0, 0, 5, NULL, NULL },
    { 16, 920, 0, 0, 0, 0, 5, NULL, NULL },
    { 4, 5000, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent145Track1[7] = {
    { 756, 1, 757248, 404224, 0, 0, 2, NULL, NULL },
    { 781, 230, 0, 0, 0, 83, 4, NULL, NULL },
    { 756, 240, 0, 0, 0, 0, 5, NULL, NULL },
    { 795, 470, 0, 0, 0, 0, 325, NULL, NULL },
    { 797, 830, 0, 0, 0, 0, 325, NULL, NULL },
    { 781, 860, 0, 0, 0, 83, 4, NULL, NULL },
    { 756, 5000, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent145Tracks[2] = {
    { sEvent145Track0, 0 },
    { sEvent145Track1, 70 },
};

const EventSequenceDef gEvent145 = {
    2,
    sEvent145Tracks,
    sEvent145Camera,
    sEvent145Script,
    sEvent145SoundCues,
    NULL,
    1000,
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

#ifdef VERSION_US
#include "event_145_text.inc"
#endif
