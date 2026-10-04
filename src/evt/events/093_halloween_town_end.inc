#ifdef VERSION_US
#include "event_093_text.inc"
#endif

static const MessageScriptEntry sEvent093Script[25] = {
    { 19, 2, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent093Text00), 0, 100 },
    { 19, 2, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent093Text01), 0, 102 },
    { 2, 0, 0, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent093Text02), 0, 120 },
    { 0, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent093Text03), 0, 330 },
    { 19, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent093Text04), 0, 341 },
    { 18, 2, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent093Text05), 0, 350 },
    { 11, 4, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent093Text06), 0, 360 },
    { 0, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent093Text07), 0, 370 },
    { 0, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent093Text08), 0, 372 },
    { 19, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent093Text09), 0, 590 },
    { 19, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent093Text10), 0, 592 },
    { 18, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent093Text11), 0, 600 },
    { 19, 2, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent093Text12), 0, 610 },
    { 19, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent093Text13), 0, 612 },
    { 0, 3, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent093Text14), 0, 630 },
    { 19, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent093Text15), 0, 641 },
    { 19, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent093Text16), 0, 642 },
    { 11, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent093Text17), 0, 860 },
    { 0, 0, 0, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent093Text18), 0, 880 },
    { 11, 1, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent093Text19), 0, 890 },
    { 11, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent093Text20), 0, 940 },
    { 11, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent093Text21), 0, 960 },
    { 11, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent093Text22), 0, 962 },
    { 0, 4, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent093Text23), 0, 980 },
    { 11, 1, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent093Text24), MSG_SCRIPT_FLAG_END, 1000 },
};

#ifdef VERSION_JP
#include "event_093_text.inc"
#endif

static const EventCameraKeyframe sEvent093Camera[1] = {
    { -65485, 61440, 74496, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent093SoundCues[2] = {
    { SONG_BGM_EVENT3, 0, 0, 0 },
    { SONG_BGM_EVENT3, 1135, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent093Track0[20] = {
    { 4, 125, { 0, 0 }, 65536, 84736, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 3, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 3, 290, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 629, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 27, 643, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 670, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 0, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 34, 861, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 4, 870, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 0, 875, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 891, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 939, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateQuestionTask },
    { 4, 965, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 16, 978, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 0, 1025, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1040, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 14, 1180, { 0, 0 }, 102400, 68096, 0, 4, { 0, 0 }, 67, NULL, NULL },
    { 4, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent093Track1[4] = {
    { 288, 889, { 0, 0 }, 52480, 73984, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 298, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 292, 1090, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 288, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent093Track2[5] = {
    { 568, 0, { 0, 0 }, 66560, 71168, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 568, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 568, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 568, 1070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 568, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent093Track3[10] = {
    { 406, 99, { 0, 0 }, 60928, 76800, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 406, 104, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateSmokeTask },
    { 406, 130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 406, 601, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 407, 609, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 407, 611, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateSmokeTask },
    { 406, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 407, 655, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 409, 800, { 0, 0 }, 102400, 68096, 0, 407, { 0, 0 }, 67, NULL, NULL },
    { 406, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent093Track4[16] = {
    { 112, 380, { 0, 0 }, 75008, 71424, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 112, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 112, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 111, 710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 760, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 113, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 112, 835, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 111, 840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 845, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 111, 1025, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 112, 1030, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 113, 1035, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 1045, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 120, 1170, { 0, 0 }, 102400, 68096, 0, 114, { 0, 0 }, 67, NULL, NULL },
    { 112, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent093Track6[1] = {
    { 575, 999, { 0, 0 }, 54784, 77824, 0, 0, { 0, 0 }, 33026, NULL, NULL },
};

static const EventCharaKeyframe sEvent093Track5[21] = {
    { 146, 104, { 0, 0 }, 73216, 83200, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 146, 106, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 145, 108, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 119, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 164, 121, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 145, 555, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 670, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 142, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 142, 835, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 145, 845, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 881, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 145, 885, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 142, 1025, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 1040, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 153, 1160, { 0, 0 }, 102400, 68096, 0, 146, { 0, 0 }, 67, NULL, NULL },
    { 146, 9990, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent093Tracks[7] = {
    { sEvent093Track0, 0, { 0, 0, 0 } },
    { sEvent093Track1, 13, { 0, 0, 0 } },
    { sEvent093Track2, 45, { 0, 0, 0 } },
    { sEvent093Track3, 29, { 0, 0, 0 } },
    { sEvent093Track4, 1, { 0, 0, 0 } },
    { sEvent093Track5, 2, { 0, 0, 0 } },
    { sEvent093Track6, 46, { 0, 0, 0 } },
};

const EventSequenceDef gEvent093 = {
    7,
    { 0, 0, 0 },
    sEvent093Tracks,
    sEvent093Camera,
    sEvent093Script,
    sEvent093SoundCues,
    NULL,
    1140,
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
