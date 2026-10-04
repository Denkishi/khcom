#ifdef VERSION_US
#include "event_104_text.inc"
#endif

static const MessageScriptEntry sEvent104Script[16] = {
    { 14, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent104Text00), 0, 180 },
    { 14, 1, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent104Text01), 0, 182 },
    { 13, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent104Text02), 0, 200 },
    { 13, 1, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent104Text03), 0, 202 },
    { 14, 1, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent104Text04), 0, 240 },
    { 22, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent104Text05), 0, 370 },
    { 1, 4, 0, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent104Text06), 0, 390 },
    { 14, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent104Text07), 0, 410 },
    { 14, 1, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent104Text08), 0, 680 },
    { 14, 2, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent104Text09), 0, 682 },
    { 13, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent104Text10), 0, 700 },
    { 14, 1, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent104Text11), 0, 730 },
    { 14, 1, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent104Text12), 0, 900 },
    { 14, 1, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent104Text13), 0, 902 },
    { 14, 2, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent104Text14), 0, 904 },
    { 14, 2, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent104Text15), MSG_SCRIPT_FLAG_END, 906 },
};

#ifdef VERSION_JP
#include "event_104_text.inc"
#endif

static const EventCameraKeyframe sEvent104Camera[3] = {
    { -64626, 45312, 35328, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64556, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_MEDIUM | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64486, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_KEYFRAME_FLAG_SHAKE_MEDIUM | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 20, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent104SoundCues[7] = {
    { SONG_BGM_EVENT_UNREST, 0, 0, 0 },
    { SONG_SND_346, 300, 0, 0 },
    { SONG_SND_350, 590, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 902, 0, 0 },
    { SONG_BGM_EVENT2, 904, 0, 0 },
    { SONG_EV_RUMBLE, 910, 0, 0 },
    { SONG_EV_RUMBLE, 945, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent104Track1[6] = {
    { 4, 1, { 0, 0 }, 81920, 61696, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 14, 80, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 4, 83, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 4, 305, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 4, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent104Track2[6] = {
    { 114, 1, { 0, 0 }, 85760, 68864, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 120, 100, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 114, 103, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 114, 389, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 131, 391, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateSmokeTask },
    { 114, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent104Track3[4] = {
    { 146, 1, { 0, 0 }, 97536, 61184, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 153, 125, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 146, 128, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 146, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent104Track0[15] = {
    { 316, 1, { 0, 0 }, 86272, 60416, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 321, 80, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 317, 83, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, NULL, NULL },
    { 316, 305, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 316, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 316, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 316, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 316, 575, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 316, 635, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 316, 660, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 4, NULL, NULL },
    { 316, 699, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 326, 701, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 316, 825, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 316, 890, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 316, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent104Track4[14] = {
    { 354, 140, { 0, 0 }, 36096, 35840, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 353, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 353, 241, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 359, 340, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 357, 360, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 68, NULL, NULL },
    { 357, 391, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 353, 392, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 357, 409, { 0, 0 }, 39936, 37120, 0, 353, { 0, 0 }, 4163, NULL, NULL },
    { 357, 672, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 355, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 356, 722, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 355, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 353, 906, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 360, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent104Track5[9] = {
    { 464, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 464, 391, { 0, 0 }, 24576, 37376, -2560, 0, { 0, 0 }, 66, EventCharaFadeIn, NULL },
    { 464, 409, { 0, 0 }, 35840, 35072, -2560, 464, { 0, 0 }, 67, NULL, NULL },
    { 464, 740, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 465, 770, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 466, 825, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 100, NULL, NULL },
    { 466, 840, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 36, NULL, NULL },
    { 464, 890, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 465, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent104Track6[3] = {
    { 590, 590, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 590, 635, { 0, 0 }, 36608, 31744, 0, 0, { 0, 0 }, 16658, NULL, NULL },
    { 590, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaTrack sEvent104Tracks[7] = {
    { sEvent104Track0, 15, { 0, 0, 0 } },
    { sEvent104Track1, 0, { 0, 0, 0 } },
    { sEvent104Track2, 1, { 0, 0, 0 } },
    { sEvent104Track3, 2, { 0, 0, 0 } },
    { sEvent104Track4, 20, { 0, 0, 0 } },
    { sEvent104Track5, 39, { 0, 0, 0 } },
    { sEvent104Track6, 49, { 0, 0, 0 } },
};

const EventSequenceDef gEvent104 = {
    7,
    { 0, 0, 0 },
    sEvent104Tracks,
    sEvent104Camera,
    sEvent104Script,
    sEvent104SoundCues,
    NULL,
    1100,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    105,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
