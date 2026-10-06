#ifdef VERSION_US
#include "event_163_text.inc"
#endif

static const MessageScriptEntry sEvent163Script[16] = {
    { 26, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent163Text00), 0, 250 },
    { 26, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent163Text01), 0, 300 },
    { 27, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent163Text02), MSG_SCRIPT_FLAG_SILHOUETTE, 330 },
    { 27, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent163Text03), 0, 490 },
    { 27, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent163Text04), 0, 570 },
    { 27, 0, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent163Text05), 0, 572 },
    { 26, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent163Text06), 0, 610 },
    { 27, 2, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent163Text07), 0, 640 },
    { 27, 2, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent163Text08), 0, 642 },
    { 27, 2, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent163Text09), 0, 644 },
    { 27, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent163Text10), 0, 700 },
    { 26, 2, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent163Text11), 0, 805 },
    { 27, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent163Text12), 0, 840 },
    { 26, 2, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent163Text13), 0, 870 },
    { 27, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent163Text14), 0, 900 },
    { 27, 2, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent163Text15), MSG_SCRIPT_FLAG_END, 940 },
};

#ifdef VERSION_JP
#include "event_163_text.inc"
#endif

static const EvSoundCue sEvent163SoundCues[5] = {
    { 65535, 0, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 390, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT_UNREST, 895, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT2, 905, 0, 0 },
    { SONG_SND_359, 910, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent163Camera[4] = {
    { -65535, 145920, 82944, 0, 255, 0, 0, NULL },
    { -65205, 0, 0, -7168, 44, 0, 0, NULL },
    { -64536, 177152, 69120, 0, 255, CAMERA_MODE_APPROACH, 50, NULL },
    { -60536, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, NULL },
};

static const EventCharaKeyframe sEvent163Track0[14] = {
    { 515, 1, 145920, 90112, 0, 0, 66, NULL, NULL },
    { 518, 120, 0, 0, 0, 45, 68, NULL, NULL },
    { 515, 150, 0, 0, 0, 0, 69, NULL, NULL },
    { 532, 170, 0, 0, 0, 0, 69, NULL, NULL },
    { 532, 220, 0, 0, 0, 0, 64, NULL, CreateExclamationTask },
    { 532, 350, 0, 0, 0, 0, 69, NULL, NULL },
    { 515, 715, 0, 0, 0, 0, 69, NULL, NULL },
    { 532, 725, 0, 0, 0, 0, 69, NULL, NULL },
    { 532, 775, 0, 0, 0, 0, 64, NULL, CreateExclamationTask },
    { 532, 780, 0, 0, 0, 0, 69, NULL, NULL },
    { 515, 800, 0, 0, 0, 0, 69, NULL, NULL },
    { 538, 810, 0, 0, 0, 0, 69, NULL, NULL },
    { 515, 3000, 0, 0, 0, 0, 69, NULL, NULL },
    { 515, 5000, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent163Track1[8] = {
    { 695, 332, 212224, 58368, 0, 0, 2, NULL, NULL },
    { 711, 450, 0, 0, 0, 173, 4, NULL, NULL },
    { 695, 635, 0, 0, 0, 0, 5, NULL, NULL },
    { 706, 643, 0, 0, 0, 0, 5, NULL, NULL },
    { 695, 695, 0, 0, 0, 0, 5, NULL, NULL },
    { 717, 710, 0, 0, 0, 0, 5, NULL, NULL },
    { 695, 910, 0, 0, 0, 0, 5, NULL, NULL },
    { 698, 5000, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent163Tracks[2] = {
    { sEvent163Track0, 44 },
    { sEvent163Track1, 65 },
};

const EventSequenceDef gEvent163 = {
    2,
    sEvent163Tracks,
    sEvent163Camera,
    sEvent163Script,
    sEvent163SoundCues,
    NULL,
    1000,
    0,
    1,
    0,
    0,
    0,
    BATTLE_RIKU_5,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
