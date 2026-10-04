#ifdef VERSION_US
#include "event_142_text.inc"
#endif

static const MessageScriptEntry sEvent142Script[21] = {
    { 0, 7, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent142Text00), 0, 100 },
    { 36, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent142Text01), 0, 150 },
    { 0, 7, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent142Text02), 0, 290 },
    { 49, 2, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent142Text03), 0, 340 },
    { 36, 0, 0, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent142Text04), 0, 530 },
    { 49, 2, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent142Text05), 0, 560 },
    { 0, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent142Text06), 0, 600 },
    { 49, 2, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent142Text07), 0, 830 },
    { 49, 1, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent142Text08), 0, 847 },
    { 36, 0, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent142Text09), 0, 880 },
    { 0, 1, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent142Text10), 0, 910 },
    { 49, 2, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent142Text11), 0, 940 },
    { 49, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent142Text12), 0, 1035 },
    { 36, 0, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent142Text13), 0, 1060 },
    { 0, 3, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent142Text14), 0, 1085 },
    { 36, 0, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent142Text15), 0, 1160 },
    { 49, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent142Text16), 0, 1190 },
    { 49, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent142Text17), 0, 1300 },
    { 0, 1, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent142Text18), 0, 1330 },
    { 49, 2, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent142Text19), 0, 1360 },
    { 0, 3, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent142Text20), MSG_SCRIPT_FLAG_END, 1390 },
};

#ifdef VERSION_JP
#include "event_142_text.inc"
#endif

static const EvSoundCue sEvent142SoundCues[4] = {
    { SONG_BGM_WINNIETHEPOOH, 1, 0, 0 },
    { SONG_BG_POO, 2, 0, 0 },
    { SONG_BG_POO, 1444, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_WINNIETHEPOOH, 1445, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent142Camera[4] = {
    { -65146, 680192, 359424, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64916, 675840, 353280, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -64796, 683264, 353280, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -63536, 681728, 356352, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent142Track0[25] = {
    { 4, 110, { 0, 0 }, 675584, 361728, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 3, 115, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 255, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 34, 345, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 0, 365, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 0, 575, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 905, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 34, 960, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 27, 970, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 27, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 27, 1065, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 1070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 1075, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 1080, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 31, 1090, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 2, 1200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 3, 1205, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 1325, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 36, 1370, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 27, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent142Track1[14] = {
    { 835, 390, { 0, 0 }, 651520, 336384, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 837, 450, { 0, 0 }, 668416, 347136, 0, 835, { 0, 0 }, 67, NULL, NULL },
    { 835, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 835, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 835, 740, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 837, 790, { 0, 0 }, 692224, 357632, 0, 835, { 0, 0 }, 67, NULL, NULL },
    { 835, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 838, 832, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 835, 845, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 835, 1095, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 835, 1145, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateQuestionTask },
    { 835, 1240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 836, 1260, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 835, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent142Track2[11] = {
    { 796, 160, { 0, 0 }, 683520, 366336, 0, 0, { 0, 0 }, 322, NULL, NULL },
    { 797, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 757, 310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 758, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 772, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 777, 390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 758, 770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 772, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 778, 790, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 758, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 758, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent142Tracks[3] = {
    { sEvent142Track0, 0, { 0, 0, 0 } },
    { sEvent142Track1, 77, { 0, 0, 0 } },
    { sEvent142Track2, 70, { 0, 0, 0 } },
};

const EventSequenceDef gEvent142 = {
    3,
    { 0, 0, 0 },
    sEvent142Tracks,
    sEvent142Camera,
    sEvent142Script,
    sEvent142SoundCues,
    NULL,
    1450,
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
    6,
};
