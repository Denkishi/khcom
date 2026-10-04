#ifdef VERSION_US
#include "event_190_text.inc"
#endif

static const MessageScriptEntry sEvent190Script[15] = {
    { 61, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent190Text00), 0, 210 },
    { 26, 3, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent190Text01), 0, 240 },
    { 61, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent190Text02), 0, 270 },
    { 26, 3, 0, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent190Text03), 0, 780 },
    { 61, 4, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent190Text04), 0, 825 },
    { 26, 0, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent190Text05), 0, 880 },
    { 52, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent190Text06), 0, 940 },
    { 26, 1, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent190Text07), 0, 970 },
    { 52, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent190Text08), 0, 1000 },
    { 26, 0, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent190Text09), 0, 1050 },
    { 52, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent190Text10), 0, 1080 },
    { 26, 0, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent190Text11), 0, 1110 },
    { 52, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent190Text12), 0, 1140 },
    { 52, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent190Text13), 0, 1220 },
    { 26, 0, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent190Text14), MSG_SCRIPT_FLAG_END, 1460 },
};

#ifdef VERSION_JP
#include "event_190_text.inc"
#endif

static const EvSoundCue sEvent190SoundCues[6] = {
    { SONG_BGM_T13THFLOOR, 0, 0, 0 },
    { SONG_SND_958, 640, 0, 0 },
    { SONG_EV_SR_STONEL, 645, 0, 0 },
    { SONG_SND_959, 660, 0, 0 },
    { SONG_EV_SR_STONER, 665, 0, 0 },
    { SONG_EV_CARDTHR, 1191, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent190Camera[4] = {
    { -65116, 159488, 77056, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64916, 201728, 55296, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -64537, 192000, 61952, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent190Track0[17] = {
    { 515, 1, { 0, 0 }, 125696, 101888, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 518, 110, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 515, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 515, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 620, { 0, 0 }, 167424, 84736, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 518, 690, { 0, 0 }, 185088, 75520, 0, 515, { 0, 0 }, 67, NULL, NULL },
    { 515, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 850, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 1190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 559, 1250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 558, 1280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 558, 1410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 558, 1440, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 1480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 518, 1700, { 0, 0 }, 230400, 52992, 0, 515, { 0, 0 }, 67, NULL, NULL },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent190Track1[18] = {
    { 745, 50, { 0, 0 }, 198400, 64256, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 747, 180, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 745, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 745, 310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 746, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 746, 620, { 0, 0 }, 161792, 76544, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 754, 690, { 0, 0 }, 176384, 70400, 0, 746, { 0, 0 }, 67, NULL, NULL },
    { 746, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 745, 820, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 752, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 745, 920, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 746, 1470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 745, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 747, 1540, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 745, 1550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 746, 1560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 754, 2020, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 746, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent190Track2[4] = {
    { 907, 1160, { 0, 0 }, 201984, 61952, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 908, 1205, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 907, 1600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 907, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent190Track3[8] = {
    { 591, 1190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 591, 1191, { 0, 0 }, 197376, 58624, 0, 0, { 0, 0 }, 16658, NULL, NULL },
    { 591, 1200, { 0, 0 }, 189440, 65792, 0, 591, { 0, 0 }, 275, NULL, NULL },
    { 591, 1203, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 604, 1250, { 0, 0 }, 185088, 75520, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 591, 1264, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 603, 1440, { 0, 0 }, 185088, 75520, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 591, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98309, NULL, NULL },
};

static const EventCharaTrack sEvent190Tracks[4] = {
    { sEvent190Track0, 44, { 0, 0, 0 } },
    { sEvent190Track1, 69, { 0, 0, 0 } },
    { sEvent190Track2, 84, { 0, 0, 0 } },
    { sEvent190Track3, 50, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent190 = {
    4,
    { 0, 0, 0 },
    sEvent190Tracks,
    sEvent190Camera,
    sEvent190Script,
    sEvent190SoundCues,
    NULL,
    1640,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    191,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent190 = {
    4,
    { 0, 0, 0 },
    sEvent190Tracks,
    sEvent190Camera,
    sEvent190Script,
    sEvent190SoundCues,
    NULL,
    1640,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    189,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif
