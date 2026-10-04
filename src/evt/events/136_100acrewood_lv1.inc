#ifdef VERSION_US
#include "event_136_text.inc"
#endif

static const MessageScriptEntry sEvent136Script[18] = {
    { 47, 2, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent136Text00), 0, 120 },
    { 47, 1, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent136Text01), 0, 160 },
    { 0, 3, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent136Text02), 0, 180 },
    { 47, 1, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent136Text03), 0, 200 },
    { 47, 1, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent136Text04), 0, 202 },
    { 36, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent136Text05), 0, 370 },
    { 47, 2, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent136Text06), 0, 420 },
    { 47, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent136Text07), 0, 460 },
    { 47, 1, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent136Text08), 0, 462 },
    { 0, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent136Text09), 0, 470 },
    { 36, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent136Text10), 0, 500 },
    { 47, 2, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent136Text11), 0, 520 },
    { 47, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent136Text12), 0, 670 },
    { 0, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent136Text13), 0, 690 },
    { 47, 2, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent136Text14), 0, 795 },
    { 36, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent136Text15), 0, 870 },
    { 47, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent136Text16), 0, 890 },
    { 47, 0, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent136Text17), MSG_SCRIPT_FLAG_END, 892 },
};

#ifdef VERSION_JP
#include "event_136_text.inc"
#endif

static const EvSoundCue sEvent136SoundCues[4] = {
    { SONG_BGM_WINNIETHEPOOH, 1, 0, 0 },
    { SONG_BG_POO, 2, 0, 0 },
    { SONG_BG_POO, 964, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_WINNIETHEPOOH, 965, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent136Camera[4] = {
    { -65306, 171008, 104704, 0, 255, 0, 0, NULL },
    { -65113, 170752, 109568, 0, 255, CAMERA_MODE_APPROACH, 40, NULL },
    { -64796, 170752, 104704, 0, 255, CAMERA_MODE_APPROACH, 40, NULL },
    { -64537, 184832, 112640, 0, 255, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 40, NULL },
};

static const EventCharaKeyframe sEvent136Track0[11] = {
    { 2, 470, 173568, 106752, 0, 0, 2, NULL, NULL },
    { 32, 500, 0, 0, 0, 0, 5, NULL, NULL },
    { 2, 680, 0, 0, 0, 0, 5, NULL, NULL },
    { 3, 710, 0, 0, 0, 0, 5, NULL, NULL },
    { 2, 715, 0, 0, 0, 0, 5, NULL, NULL },
    { 1, 720, 0, 0, 0, 0, 5, NULL, NULL },
    { 2, 730, 0, 0, 0, 0, 69, NULL, NULL },
    { 7, 795, 0, 0, 0, 83, 68, NULL, NULL },
    { 2, 820, 0, 0, 0, 0, 69, NULL, NULL },
    { 1, 830, 0, 0, 0, 0, 5, NULL, NULL },
    { 2, 999, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent136Track1[20] = {
    { 811, 100, 167168, 110848, 0, 0, 66, NULL, NULL },
    { 811, 120, 0, 0, 0, 0, 64, EventCharaHopLow, CreateExclamationTask },
    { 811, 125, 0, 0, 0, 0, 69, NULL, NULL },
    { 812, 140, 0, 0, 0, 173, 36, NULL, NULL },
    { 811, 380, 0, 0, 0, 0, 69, NULL, NULL },
    { 811, 430, 0, 0, 0, 0, 64, NULL, CreateExclamationTask },
    { 813, 445, 0, 0, 0, 45, 100, NULL, NULL },
    { 811, 448, 0, 0, 0, 45, 100, NULL, NULL },
    { 811, 450, 0, 0, 0, 0, 69, NULL, NULL },
    { 811, 463, 0, 0, 0, 0, 5, NULL, NULL },
    { 811, 510, 0, 0, 0, 0, 69, NULL, NULL },
    { 811, 530, 0, 0, 0, 0, 5, NULL, NULL },
    { 811, 660, 0, 0, 0, 0, 0, NULL, CreateBalloonTask },
    { 811, 750, 0, 0, 0, 0, 5, NULL, NULL },
    { 811, 770, 0, 0, 0, 0, 69, NULL, NULL },
    { 810, 810, 0, 0, 0, 0, 69, NULL, NULL },
    { 812, 850, 0, 0, 0, 83, 100, NULL, NULL },
    { 810, 852, 0, 0, 0, 83, 100, NULL, NULL },
    { 810, 860, 0, 0, 0, 0, 69, NULL, NULL },
    { 811, 999, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent136Track2[15] = {
    { 756, 220, 177664, 104704, 0, 0, 66, NULL, NULL },
    { 757, 230, 0, 0, 0, 0, 69, NULL, NULL },
    { 782, 280, 0, 0, 0, 192, 68, NULL, NULL },
    { 781, 335, 0, 0, 0, 173, 68, NULL, NULL },
    { 756, 345, 0, 0, 0, 0, 69, NULL, NULL },
    { 755, 425, 0, 0, 0, 0, 5, NULL, NULL },
    { 761, 450, 0, 0, 0, 0, 5, NULL, NULL },
    { 756, 720, 0, 0, 0, 0, 5, NULL, NULL },
    { 782, 750, 0, 0, 0, 64, 4, NULL, NULL },
    { 781, 795, 0, 0, 0, 83, 4, NULL, NULL },
    { 756, 796, 0, 0, 0, 0, 5, NULL, NULL },
    { 781, 860, 0, 0, 0, 83, 4, NULL, NULL },
    { 756, 870, 0, 0, 0, 0, 5, NULL, NULL },
    { 755, 900, 0, 0, 0, 0, 5, NULL, NULL },
    { 755, 999, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent136Tracks[3] = {
    { sEvent136Track0, 0 },
    { sEvent136Track1, 72 },
    { sEvent136Track2, 70 },
};

const EventSequenceDef gEvent136 = {
    3,
    sEvent136Tracks,
    sEvent136Camera,
    sEvent136Script,
    sEvent136SoundCues,
    NULL,
    970,
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
    1,
};
