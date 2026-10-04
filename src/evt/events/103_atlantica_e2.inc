#ifdef VERSION_US
#include "event_103_text.inc"
#endif

static const MessageScriptEntry sEvent103Script[30] = {
    { 0, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text00), 0, 140 },
    { 13, 4, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text01), 0, 300 },
    { 13, 5, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text02), 0, 302 },
    { 1, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text03), 0, 320 },
    { 2, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text04), 0, 340 },
    { 14, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text05), MSG_SCRIPT_FLAG_SILHOUETTE, 380 },
    { 14, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text06), 0, 560 },
    { 14, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text07), 0, 580 },
    { 14, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text08), 0, 582 },
    { 13, 1, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text09), 0, 600 },
    { 14, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text10), 0, 640 },
    { 14, 1, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text11), 0, 642 },
    { 13, 4, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text12), 0, 700 },
    { 13, 5, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text13), 0, 740 },
    { 14, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text14), 0, 910 },
    { 14, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text15), 0, 1020 },
    { 14, 1, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text16), 0, 1022 },
    { 13, 5, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text17), 0, 1320 },
    { 0, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text18), 0, 1340 },
    { 13, 3, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text19), 0, 1510 },
    { 0, 1, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text20), 0, 1530 },
    { 1, 1, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text21), 0, 1550 },
    { 1, 1, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text22), 0, 1552 },
    { 13, 2, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text23), 0, 1570 },
    { 13, 4, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text24), 0, 1572 },
    { 13, 4, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text25), 0, 1574 },
    { 0, 4, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text26), 0, 1600 },
    { 0, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text27), 0, 1700 },
    { 13, 3, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text28), 0, 1720 },
    { 0, 4, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent103Text29), MSG_SCRIPT_FLAG_END, 1740 },
};

#ifdef VERSION_JP
#include "event_103_text.inc"
#endif

static const EventCameraKeyframe sEvent103Camera[3] = {
    { -65376, 39168, 61952, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64186, 83200, 45824, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -55537, 69632, 47616, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent103SoundCues[7] = {
    { 65535, 0, 0, 0 },
    { SONG_BGM_EVENT_SILENCE, 300, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT_SILENCE, 370, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT_UNREST, 381, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT_UNREST, 1100, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_UNDERTHESEA, 1700, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_UNDERTHESEA, 1845, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent103Track0[21] = {
    { 316, 381, { 0, 0 }, 73984, 45056, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 316, 410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 316, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 314, 430, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 314, 599, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 324, 601, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 314, 710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 314, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 316, 1150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 314, 1160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 314, 1170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 314, 1310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 314, 1350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 314, 1360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 322, 1509, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 323, 1511, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 314, 1610, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 314, 1690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateQuestionTask },
    { 314, 1719, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 322, 1721, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 314, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent103Track1[7] = {
    { 4, 1, { 0, 0 }, 20992, 71680, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 9, 60, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 4, 1350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 9, 1490, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 4, 1529, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 36, 1531, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent103Track2[8] = {
    { 114, 1, { 0, 0 }, 24832, 76288, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 119, 60, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 114, 1350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 119, 1490, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 114, 1549, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 127, 1553, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 129, 1560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent103Track3[5] = {
    { 146, 1, { 0, 0 }, 14592, 71680, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 151, 60, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 146, 1350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 151, 1490, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 146, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent103Track4[14] = {
    { 354, 390, { 0, 0 }, 129792, 74496, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 358, 467, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 354, 478, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 358, 540, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 358, 750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 358, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 358, 920, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 354, 930, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 353, 950, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 357, 1010, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 357, 1040, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 353, 1041, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 357, 1410, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 353, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent103Tracks[5] = {
    { sEvent103Track0, 15, { 0, 0, 0 } },
    { sEvent103Track1, 0, { 0, 0, 0 } },
    { sEvent103Track2, 1, { 0, 0, 0 } },
    { sEvent103Track3, 2, { 0, 0, 0 } },
    { sEvent103Track4, 20, { 0, 0, 0 } },
};

const EventSequenceDef gEvent103 = {
    5,
    { 0, 0, 0 },
    sEvent103Tracks,
    sEvent103Camera,
    sEvent103Script,
    sEvent103SoundCues,
    NULL,
    1850,
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
