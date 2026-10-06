#ifdef VERSION_US
#include "event_167_text.inc"
#endif

static const MessageScriptEntry sEvent167Script[32] = {
    { PORTRAIT_AXEL, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent028Text07), 0, 100 },
    { PORTRAIT_VEXEN, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent028Text08), 0, 130 },
    { PORTRAIT_VEXEN, 0, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent028Text09), 0, 132 },
    { PORTRAIT_VEXEN, 1, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent028Text10), 0, 134 },
    { PORTRAIT_LARXENE, 3, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent028Text11), 0, 160 },
    { PORTRAIT_VEXEN, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent028Text12), 0, 180 },
    { PORTRAIT_AXEL, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent028Text13), 0, 220 },
    { PORTRAIT_VEXEN, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent028Text14), 0, 240 },
    { PORTRAIT_LARXENE, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent028Text15), 0, 260 },
    { PORTRAIT_VEXEN, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent028Text16), 0, 280 },
    { PORTRAIT_AXEL, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent028Text17), 0, 430 },
    { PORTRAIT_AXEL, 1, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent028Text18), 0, 470 },
    { PORTRAIT_VEXEN, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent028Text19), 0, 490 },
    { PORTRAIT_RIKU_REPLICA, 0, 0, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent167Text13), 0, 690 },
    { PORTRAIT_AXEL, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent167Text14), 0, 720 },
    { PORTRAIT_LARXENE, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent167Text15), 0, 750 },
    { PORTRAIT_LARXENE, 1, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent167Text16), 0, 752 },
    { PORTRAIT_LARXENE, 2, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent167Text17), 0, 835 },
    { PORTRAIT_RIKU_REPLICA, 3, 0, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent167Text18), 0, 920 },
    { PORTRAIT_RIKU_REPLICA, 2, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent167Text19), 0, 925 },
    { PORTRAIT_LARXENE, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent167Text20), 0, 950 },
    { PORTRAIT_VEXEN, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent167Text21), 0, 1130 },
    { PORTRAIT_RIKU_REPLICA, 2, 0, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent167Text22), 0, 1150 },
    { PORTRAIT_VEXEN, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent167Text23), 0, 1180 },
    { PORTRAIT_LARXENE, 2, 0, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent167Text24), 0, 1270 },
    { PORTRAIT_RIKU_REPLICA, 2, 2, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent167Text25), 0, 1420 },
    { PORTRAIT_LARXENE, 1, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent167Text26), 0, 1635 },
    { PORTRAIT_LARXENE, 1, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent167Text27), 0, 1670 },
    { PORTRAIT_LARXENE, 1, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent167Text28), 0, 1672 },
    { PORTRAIT_LARXENE, 2, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent167Text29), 0, 1674 },
    { PORTRAIT_RIKU_REPLICA, 3, 0, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent167Text30), 0, 1710 },
    { PORTRAIT_RIKU_REPLICA, 3, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent167Text31), MSG_SCRIPT_FLAG_END, 2070 },
};

#ifdef VERSION_JP
#include "event_167_text.inc"
#endif

static const EvSoundCue sEvent167SoundCues[5] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_EV_CARDTHR, 448, 0, 0 },
    { SONG_SND_359, 1430, 0, 0 },
    { SONG_EV_FLASH00, 1460, 0, 0 },
    { SONG_BGM_EVENT_XIII, 1750, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

#if defined(VERSION_US) || defined(VERSION_JP)
static const EventCameraKeyframe sEvent167Camera[7] = {
    { -65006, 60672, 55040, 0, 255, 0, 0, NULL },
    { -64076, 65536, 58112, 0, 255, CAMERA_MODE_APPROACH, 60, NULL },
    { -64066, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 10, NULL },
    { -63986, 0, 0, 0, 255, CAMERA_MODE_KEEP, 0, NULL },
    { -63806, 99840, 67072, 0, 255, CAMERA_MODE_APPROACH, 100, NULL },
    { -61466, 99840, -12544, 0, 255, CAMERA_MODE_APPROACH, 500, NULL },
    { -60536, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, NULL },
};
#elif defined(VERSION_EU)
static const EventCameraKeyframe sEvent167Camera[7] = {
    { -65006, 60672, 55040, 0, 255, 0, 0, NULL },
    { -64076, 65536, 58112, 0, 255, CAMERA_MODE_APPROACH, 60, NULL },
    { -64066, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 10, NULL },
    { -63986, 0, 0, 0, 255, CAMERA_MODE_KEEP, 0, NULL },
    { -63806, 99840, 67072, 0, 255, CAMERA_MODE_APPROACH, 100, NULL },
    { -63266, 99840, -12544, 0, 255, CAMERA_MODE_APPROACH, 500, NULL },
    { -60536, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, NULL },
};
#endif

static const EventBgEffectEntry sEvent167BgEffects[5] = {
    { 1770, 0, 0, 0, 0 },
    { 1850, 0, 0, 0, 0x14 },
    { 3380, 0, 0, 0, 0 },
    { 3450, 0, 0, 0, 0x2 },
    { 3500, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent167Track0[7] = {
    { 485, 215, 51200, 55808, 0, 0, 82, NULL, NULL },
    { 509, 225, 0, 0, 0, 0, 85, NULL, NULL },
    { 509, 290, 0, 0, 0, 0, 85, NULL, NULL },
    { 509, 420, 0, 0, 0, 0, 80, NULL, CreateBalloonTask },
    { 485, 431, 0, 0, 0, 0, 85, NULL, NULL },
    { 500, 475, 0, 0, 0, 0, 85, NULL, NULL },
    { 485, 999, 0, 0, 0, 0, 32853, NULL, NULL },
};

static const EventCharaKeyframe sEvent167Track2[11] = {
    { 738, 110, 62464, 70656, 0, 0, 66, NULL, NULL },
    { 738, 450, 0, 0, 0, 0, 5, NULL, NULL },
    { 739, 480, 0, 0, 0, 0, 5, NULL, NULL },
    { 738, 500, 0, 0, 0, 0, 5, NULL, NULL },
    { 721, 510, 0, 0, 0, 0, 5, NULL, NULL },
    { 721, 970, 0, 0, 0, 0, 69, NULL, NULL },
    { 727, 980, 0, 0, 0, 0, 69, NULL, NULL },
    { 727, 1110, 0, 0, 0, 0, 64, NULL, CreateBalloonTask },
    { 727, 1160, 0, 0, 0, 0, 69, NULL, NULL },
    { 729, 1500, 0, 0, 0, 0, 69, NULL, NULL },
    { 721, 2000, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent167Track1[14] = {
    { 856, 1300, 74752, 61952, 0, 0, 2, NULL, NULL },
    { 856, 1320, 0, 0, 0, 0, 69, NULL, NULL },
    { 881, 1380, 85760, 69120, 0, 856, 67, NULL, NULL },
    { 856, 1390, 0, 0, 0, 0, 69, NULL, NULL },
    { 856, 1440, 0, 0, 0, 0, 5, NULL, NULL },
    { 871, 1520, 0, 0, 0, 0, 5, NULL, NULL },
    { 856, 1570, 0, 0, 0, 0, 5, NULL, NULL },
    { 856, 1580, 0, 0, 0, 0, 69, NULL, NULL },
    { 881, 1620, 93952, 71680, 0, 856, 67, NULL, NULL },
    { 856, 1630, 0, 0, 0, 0, 69, NULL, NULL },
    { 857, 1830, 0, 0, 0, 0, 69, NULL, NULL },
    { 856, 1850, 0, 0, 0, 0, 64, EventCharaFadeOut, NULL },
    { 856, 1870, 0, 0, 0, 0, 2, NULL, NULL },
    { 856, 9999, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent167Track3[6] = {
    { 591, 447, 0, 0, 0, 0, 66, NULL, NULL },
    { 591, 448, 55296, 56320, -5120, 0, 338, NULL, NULL },
    { 591, 459, 57856, 63488, -5120, 591, 323, NULL, NULL },
    { 591, 463, 0, 0, 0, 0, 2, NULL, NULL },
    { 610, 480, 63488, 70656, 0, 0, 274, NULL, NULL },
    { 591, 999, 0, 0, 0, 0, 98370, NULL, NULL },
};

static const EventCharaKeyframe sEvent167Track4[23] = {
    { 696, 540, 0, 0, 0, 0, 8194, NULL, NULL },
    { 696, 541, 99072, 91648, 0, 0, 16386, NULL, NULL },
    { 712, 660, 72960, 74752, 0, 696, 3, NULL, NULL },
    { 696, 765, 0, 0, 0, 0, 5, NULL, NULL },
    { 696, 815, 0, 0, 0, 0, 0, NULL, CreateQuestionTask },
    { 696, 855, 0, 0, 0, 0, 5, NULL, NULL },
    { 716, 905, 0, 0, 0, 0, 0, NULL, CreateExclamationTask },
    { 716, 922, 0, 0, 0, 0, 5, NULL, NULL },
    { 708, 930, 0, 0, 0, 0, 5, NULL, NULL },
    { 696, 1145, 0, 0, 0, 0, 5, NULL, NULL },
    { 708, 1155, 0, 0, 0, 0, 5, NULL, NULL },
    { 696, 1190, 0, 0, 0, 0, 5, NULL, NULL },
    { 716, 1240, 0, 0, 0, 0, 0, NULL, CreateExclamationTask },
    { 716, 1250, 0, 0, 0, 0, 5, NULL, NULL },
    { 696, 1340, 0, 0, 0, 0, 5, NULL, NULL },
    { 696, 1430, 0, 0, 0, 0, 69, NULL, NULL },
    { 701, 1460, 0, 0, 0, 0, 69, NULL, NULL },
    { 702, 1465, 80896, 70656, 0, 696, 67, NULL, NULL },
    { 713, 1495, 103424, 71168, 0, 695, 323, NULL, NULL },
    { 713, 1830, 0, 0, 0, 0, 325, NULL, NULL },
    { 713, 1850, 0, 0, 0, 0, 320, EventCharaFadeOut, NULL },
    { 696, 2070, 0, 0, 0, 0, 2, NULL, NULL },
    { 713, 5070, 0, 0, 0, 0, 33093, NULL, NULL },
};

static const EventCharaTrack sEvent167Tracks[5] = {
    { sEvent167Track0, 43 },
    { sEvent167Track1, 81 },
    { sEvent167Track2, 67 },
    { sEvent167Track3, 50 },
    { sEvent167Track4, 65 },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent167 = {
    5,
    sEvent167Tracks,
    sEvent167Camera,
    sEvent167Script,
    sEvent167SoundCues,
    sEvent167BgEffects,
    2130,
    0,
    1,
    0,
    0,
    0,
    0,
    EVENT_168_RIKU_B6F_DEMO,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent167 = {
    5,
    sEvent167Tracks,
    sEvent167Camera,
    sEvent167Script,
    sEvent167SoundCues,
    sEvent167BgEffects,
    2270,
    0,
    1,
    0,
    0,
    0,
    0,
    EVENT_168_RIKU_B6F_DEMO,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif
