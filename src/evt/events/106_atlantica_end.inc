#ifdef VERSION_US
#include "event_106_text.inc"
#endif

static const MessageScriptEntry sEvent106Script[20] = {
    { 22, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent106Text00), 0, 150 },
    { 13, 2, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent106Text01), 0, 170 },
    { 13, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent106Text02), 0, 172 },
    { 0, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent106Text03), 0, 200 },
    { 13, 2, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent106Text04), 0, 240 },
    { 23, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent106Text05), 0, 270 },
    { 23, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent106Text06), 0, 272 },
    { 13, 3, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent106Text07), 0, 370 },
    { 2, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent106Text08), 0, 390 },
    { 0, 3, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent106Text09), 0, 460 },
    { 0, 1, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent106Text10), 0, 462 },
    { 13, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent106Text11), 0, 490 },
    { 13, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent106Text12), 0, 492 },
    { 13, 4, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent106Text13), 0, 590 },
    { 13, 5, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent106Text14), 0, 592 },
    { 13, 5, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent106Text15), 0, 640 },
    { 13, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent106Text16), 0, 642 },
    { 13, 2, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent106Text17), 0, 680 },
    { 6, 4, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent106Text18), 0, 870 },
    { 0, 1, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent106Text19), MSG_SCRIPT_FLAG_END, 910 },
};

#ifdef VERSION_JP
#include "event_106_text.inc"
#endif

static const EventCameraKeyframe sEvent106Camera[1] = {
    { -64626, 45056, 38144, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent106SoundCues[2] = {
    { SONG_BGM_EVENT4, 0, 0, 0 },
    { SONG_BGM_EVENT4, 965, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent106Track0[6] = {
    { 464, 210, { 0, 0 }, 44288, 40192, -2560, 0, { 0, 0 }, 66, NULL, NULL },
    { 464, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 464, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 464, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 464, 470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 464, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent106Track1[10] = {
    { 316, 210, { 0, 0 }, 48896, 43008, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 314, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 314, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 314, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 314, 369, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 322, 371, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 314, 470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 314, 610, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 316, 660, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 314, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent106Track2[8] = {
    { 4, 459, { 0, 0 }, 36608, 45312, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 30, 463, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateQuestionTask },
    { 4, 710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 4, 905, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 36, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent106Track3[1] = {
    { 112, 999, { 0, 0 }, 54784, 34560, 0, 0, { 0, 0 }, 32770, NULL, NULL },
};

static const EventCharaKeyframe sEvent106Track4[3] = {
    { 144, 389, { 0, 0 }, 36096, 35072, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 164, 391, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 144, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent106Track5[4] = {
    { 231, 620, { 0, 0 }, 32256, 41984, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 229, 860, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 233, 872, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaHop, NULL },
    { 229, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent106Tracks[6] = {
    { sEvent106Track0, 39, { 0, 0, 0 } },
    { sEvent106Track1, 15, { 0, 0, 0 } },
    { sEvent106Track2, 0, { 0, 0, 0 } },
    { sEvent106Track3, 1, { 0, 0, 0 } },
    { sEvent106Track4, 2, { 0, 0, 0 } },
    { sEvent106Track5, 8, { 0, 0, 0 } },
};

const EventSequenceDef gEvent106 = {
    6,
    { 0, 0, 0 },
    sEvent106Tracks,
    sEvent106Camera,
    sEvent106Script,
    sEvent106SoundCues,
    NULL,
    970,
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
