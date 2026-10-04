#ifdef VERSION_US
#include "event_143_text.inc"
#endif

static const MessageScriptEntry sEvent143Script[16] = {
    { 0, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent143Text00), 0, 250 },
    { 0, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent143Text01), 0, 300 },
    { 36, 1, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent143Text02), 0, 330 },
    { 36, 1, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent143Text03), 0, 350 },
    { 36, 2, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent143Text04), 0, 500 },
    { 0, 4, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent143Text05), 0, 670 },
    { 36, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent143Text06), 0, 700 },
    { 0, 4, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent143Text07), 0, 730 },
    { 36, 1, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent143Text08), 0, 760 },
    { 0, 3, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent143Text09), 0, 900 },
    { 36, 2, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent143Text10), 0, 950 },
    { 0, 4, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent143Text11), 0, 980 },
    { 0, 5, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent143Text12), 0, 1100 },
    { 36, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent143Text13), 0, 1190 },
    { 36, 1, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent143Text14), 0, 1192 },
    { 0, 4, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent143Text15), MSG_SCRIPT_FLAG_END, 1240 },
};

#ifdef VERSION_JP
#include "event_143_text.inc"
#endif

static const EvSoundCue sEvent143SoundCues[6] = {
    { SONG_BGM_WINNIETHEPOOH, 1, 0, 0 },
    { SONG_BG_POO, 2, 0, 0 },
    { SONG_BGM_WINNIETHEPOOH, 725, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT4, 755, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BG_POO, 1294, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT4, 1295, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent143Camera[1] = {
    { -64537, 790528, 416512, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent143Track0[17] = {
    { 2, 1, { 0, 0 }, 772096, 412160, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 7, 100, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 2, 110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 1, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 2, 260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 3, 265, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 640, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 4, 990, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1040, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 4, 1050, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 16, 1220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent143Track1[8] = {
    { 756, 1, { 0, 0 }, 757248, 404224, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 781, 230, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 4, NULL, NULL },
    { 756, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 795, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 804, 770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 797, 1130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 781, 1160, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 4, NULL, NULL },
    { 756, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent143Tracks[2] = {
    { sEvent143Track0, 0, { 0, 0, 0 } },
    { sEvent143Track1, 70, { 0, 0, 0 } },
};

const EventSequenceDef gEvent143 = {
    2,
    { 0, 0, 0 },
    sEvent143Tracks,
    sEvent143Camera,
    sEvent143Script,
    sEvent143SoundCues,
    NULL,
    1300,
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
