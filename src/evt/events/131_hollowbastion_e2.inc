#ifdef VERSION_US
#include "event_131_text.inc"
#endif

static const MessageScriptEntry sEvent131Script[38] = {
    { 44, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text00), 0, 100 },
    { 53, 4, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text01), 0, 130 },
    { 44, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text02), 0, 160 },
    { 0, 2, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text03), 0, 250 },
    { 0, 2, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text04), 0, 370 },
    { 44, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text05), 0, 400 },
    { 44, 1, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text06), 0, 402 },
    { 43, 0, 0, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text07), 0, 430 },
    { 53, 1, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text08), 0, 630 },
    { 53, 4, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text09), 0, 720 },
    { 53, 2, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text10), 0, 722 },
    { 43, 4, 0, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text11), 0, 770 },
    { 6, 1, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text12), 0, 800 },
    { 43, 0, 0, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text13), 0, 990 },
    { 43, 0, 0, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text14), 0, 1070 },
    { 43, 4, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text15), 0, 1072 },
    { 43, 4, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text16), 0, 1074 },
    { 43, 0, 0, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text17), 0, 1370 },
    { 43, 1, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text18), 0, 1372 },
    { 43, 0, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text19), 0, 1374 },
    { 43, 0, 0, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text20), 0, 1460 },
    { 53, 4, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text21), 0, 1510 },
    { 44, 1, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text22), 0, 1560 },
    { 44, 2, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text23), 0, 1562 },
    { 53, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text24), 0, 1655 },
    { 53, 4, 2, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text25), 0, 1720 },
    { 44, 1, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text26), 0, 2020 },
    { 44, 0, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text27), 0, 2022 },
    { 44, 2, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text28), 0, 2024 },
    { 43, 2, 0, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text29), 0, 2050 },
    { 43, 2, 0, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text30), 0, 2285 },
    { 0, 2, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text31), 0, 2465 },
    { 43, 3, 0, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text32), 0, 2525 },
    { 1, 4, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text33), 0, 2555 },
    { 43, 3, 0, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text34), 0, 2585 },
    { 2, 1, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text35), 0, 2615 },
    { 0, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text36), 0, 2645 },
    { 43, 0, 0, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent131Text37), MSG_SCRIPT_FLAG_END, 2670 },
};

#ifdef VERSION_JP
#include "event_131_text.inc"
#endif

static const EvSoundCue sEvent131SoundCues[13] = {
    { SONG_BGM_HOLLOW_FIELD, 0, 0, 0 },
    { SONG_BGM_HOLLOW_FIELD, 430, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT_SILENCE, 990, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_SND_351, 1459, 0, 0 },
    { SONG_BGM_EVENT_SILENCE, 1515, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT_UNREST, 1560, 0, 0 },
    { SONG_SND_353, 1586, 0, 0 },
    { SONG_SND_353, 1695, EV_SOUND_FLAG_STOP, 0 },
    { SONG_BTL_GMIC_OK, 1701, 0, 0 },
    { SONG_SND_351, 1804, 0, 0 },
    { SONG_SND_352, 2119, 0, 0 },
    { SONG_SND_351, 2204, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 2795, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent131Camera[12] = {
    { -65276, 50176, 79616, 0, 255, 0, 0, NULL },
    { -65096, 35840, 68864, 0, 255, CAMERA_MODE_APPROACH, 80, NULL },
    { -63972, 62464, 82944, 0, 255, CAMERA_MODE_APPROACH, 80, NULL },
    { -63861, 62464, 73728, 0, 255, CAMERA_MODE_APPROACH, 50, NULL },
    { -63836, 62464, 77824, 0, 255, CAMERA_MODE_APPROACH, 30, NULL },
    { -63826, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 10, NULL },
    { -63806, 0, 0, 0, 255, CAMERA_MODE_KEEP, 0, NULL },
    { -63796, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_HALF_FLASH | CAMERA_MODE_KEEP, 10, NULL },
    { -63776, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_HALF_FLASH | CAMERA_MODE_KEEP, 10, NULL },
    { -63546, 0, 0, 0, 255, CAMERA_MODE_KEEP, 0, NULL },
    { -63249, 62464, 82944, 0, 255, CAMERA_MODE_APPROACH, 50, NULL },
    { -55537, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, NULL },
};

static const EventBgEffectEntry sEvent131BgEffects[5] = {
    { 2119, 0, 0, 0, 0 },
    { 2120, 0, 60, 0, 0x14 },
    { 2150, 0, 0, 0, 0 },
    { 2270, 0, 0, 0, 0x2 },
    { 2330, 0, 0, 0, 0x8018 },
};

static const EventCharaKeyframe sEvent131Track0[15] = {
    { 2, 255, 11776, 61184, 0, 0, 66, NULL, NULL },
    { 12, 300, 21760, 71424, 0, 2, 99, NULL, NULL },
    { 2, 365, 0, 0, 0, 0, 69, NULL, NULL },
    { 31, 432, 0, 0, 0, 0, 69, NULL, NULL },
    { 2, 2000, 0, 0, 0, 0, 69, NULL, NULL },
    { 2, 2326, 28160, 74240, 0, 0, 66, NULL, NULL },
    { 12, 2400, 55808, 89088, 0, 2, 99, NULL, NULL },
    { 2, 2430, 0, 0, 0, 0, 69, NULL, NULL },
    { 3, 2435, 0, 0, 0, 0, 69, NULL, NULL },
    { 4, 2470, 0, 0, 0, 0, 69, NULL, NULL },
    { 3, 2475, 0, 0, 0, 0, 69, NULL, NULL },
    { 2, 2710, 0, 0, 0, 0, 69, NULL, NULL },
    { 3, 2715, 0, 0, 0, 0, 69, NULL, NULL },
    { 4, 2760, 0, 0, 0, 0, 69, NULL, NULL },
    { 14, 5000, 0, 0, 0, 45, 32868, NULL, NULL },
};

static const EventCharaKeyframe sEvent131Track1[11] = {
    { 112, 255, 2816, 58880, 0, 0, 66, NULL, NULL },
    { 121, 300, 12032, 70144, 0, 112, 99, NULL, NULL },
    { 112, 2000, 0, 0, 0, 0, 69, NULL, NULL },
    { 112, 2316, 26624, 82176, 0, 0, 66, NULL, NULL },
    { 121, 2400, 47104, 92160, 0, 112, 99, NULL, NULL },
    { 112, 2550, 0, 0, 0, 0, 69, NULL, NULL },
    { 136, 2560, 0, 0, 0, 0, 69, NULL, NULL },
    { 112, 2740, 0, 0, 0, 0, 69, NULL, NULL },
    { 113, 2745, 0, 0, 0, 0, 69, NULL, NULL },
    { 114, 2790, 0, 0, 0, 0, 69, NULL, NULL },
    { 120, 5000, 0, 0, 0, 45, 32868, NULL, NULL },
};

static const EventCharaKeyframe sEvent131Track2[11] = {
    { 144, 255, 11264, 59392, 0, 0, 66, NULL, NULL },
    { 152, 310, 17664, 64512, 0, 144, 99, NULL, NULL },
    { 144, 2000, 0, 0, 0, 0, 69, NULL, NULL },
    { 144, 2316, 26112, 74752, 0, 0, 66, NULL, NULL },
    { 152, 2400, 46336, 87040, 0, 144, 99, NULL, NULL },
    { 144, 2610, 0, 0, 0, 0, 69, NULL, NULL },
    { 164, 2620, 0, 0, 0, 0, 69, NULL, NULL },
    { 144, 2720, 0, 0, 0, 0, 69, NULL, NULL },
    { 145, 2730, 0, 0, 0, 0, 69, NULL, NULL },
    { 146, 2800, 0, 0, 0, 0, 69, NULL, NULL },
    { 153, 5000, 0, 0, 0, 45, 32868, NULL, NULL },
};

static const EventCharaKeyframe sEvent131Track3[7] = {
    { 229, 301, 0, 0, 0, 0, 66, NULL, NULL },
    { 229, 302, 21760, 70400, 0, 0, 2, NULL, NULL },
    { 233, 330, 0, 0, 0, 173, 4, EventCharaHop, NULL },
    { 229, 335, 0, 0, 0, 0, 5, NULL, NULL },
    { 229, 2640, 0, 0, 0, 0, 69, NULL, NULL },
    { 231, 2650, 0, 0, 0, 0, 69, NULL, NULL },
    { 231, 5000, 0, 0, 0, 0, 98370, NULL, NULL },
};

static const EventCharaKeyframe sEvent131Track4[17] = {
    { 410, 190, 62464, 81152, 0, 0, 2, NULL, NULL },
    { 412, 210, 0, 0, 0, 173, 4, NULL, NULL },
    { 410, 380, 0, 0, 0, 0, 5, NULL, NULL },
    { 411, 570, 0, 0, 0, 0, 5, NULL, NULL },
    { 410, 580, 0, 0, 0, 0, 5, NULL, NULL },
    { 410, 1555, 0, 0, 0, 0, 69, NULL, NULL },
    { 415, 1561, 0, 0, 0, 0, 69, NULL, NULL },
    { 416, 1564, 0, 0, 0, 0, 69, NULL, NULL },
    { 414, 1670, 0, 0, 0, 0, 69, NULL, NULL },
    { 410, 2023, 0, 0, 0, 0, 69, NULL, NULL },
    { 415, 2025, 0, 0, 0, 0, 69, NULL, NULL },
    { 416, 2049, 0, 0, 0, 0, 69, NULL, NULL },
    { 410, 2080, 0, 0, 0, 0, 69, NULL, NULL },
    { 414, 2150, 0, 0, 0, 0, 69, NULL, NULL },
    { 410, 2180, 0, 0, 0, 0, 69, NULL, NULL },
    { 410, 2300, 0, 0, 0, 0, 64, EventCharaFadeOut, NULL },
    { 410, 5000, 0, 0, 0, 0, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent131Track5[19] = {
    { 375, 205, 45056, 89088, 0, 0, 66, NULL, NULL },
    { 377, 225, 0, 0, 0, 173, 68, NULL, NULL },
    { 375, 560, 0, 0, 0, 0, 69, NULL, NULL },
    { 374, 650, 0, 0, 0, 0, 69, NULL, NULL },
    { 374, 700, 0, 0, 0, 0, 64, NULL, CreateExclamationTask },
    { 374, 730, 0, 0, 0, 0, 69, NULL, NULL },
    { 375, 740, 0, 0, 0, 0, 69, NULL, NULL },
    { 375, 1000, 0, 0, 0, 0, 5, NULL, NULL },
    { 375, 1050, 0, 0, 0, 0, 0, NULL, CreateExclamationTask },
    { 375, 1110, 0, 0, 0, 0, 5, NULL, NULL },
    { 374, 1130, 0, 0, 0, 0, 5, NULL, NULL },
    { 374, 1614, 0, 0, 0, 0, 69, NULL, NULL },
    { 375, 1640, 0, 0, 0, 0, 69, NULL, NULL },
    { 374, 1670, 0, 0, 0, 0, 69, NULL, NULL },
    { 378, 1700, 68608, 96768, 0, 374, 115, NULL, NULL },
    { 374, 1705, 0, 0, 0, 0, 85, NULL, NULL },
    { 379, 1790, 0, 0, 0, 0, 69, NULL, NULL },
    { 379, 1820, 0, 0, 0, 0, 64, EventCharaFadeOut, NULL },
    { 375, 5000, 0, 0, 0, 0, 98370, NULL, NULL },
};

static const EventCharaKeyframe sEvent131Track6[21] = {
    { 329, 510, 102400, 117760, 0, 0, 2, NULL, NULL },
    { 331, 610, 83968, 103168, 0, 329, 3, NULL, NULL },
    { 329, 830, 0, 0, 0, 0, 5, NULL, NULL },
    { 329, 960, 0, 0, 0, 0, 0, NULL, CreateBalloonTask },
    { 329, 1200, 0, 0, 0, 0, 5, NULL, NULL },
    { 329, 1330, 0, 0, 0, 0, 0, NULL, CreateBalloonTask },
    { 329, 1400, 0, 0, 0, 0, 5, NULL, NULL },
    { 331, 1440, 77824, 101120, 0, 329, 3, NULL, NULL },
    { 329, 1450, 0, 0, 0, 0, 21, NULL, NULL },
    { 334, 1710, 0, 0, 0, 0, 21, NULL, NULL },
    { 329, 1800, 0, 0, 0, 0, 21, NULL, NULL },
    { 336, 2026, 0, 0, 0, 0, 21, NULL, NULL },
    { 329, 2045, 0, 0, 0, 0, 5, NULL, NULL },
    { 334, 2100, 0, 0, 0, 0, 5, NULL, NULL },
    { 329, 2200, 0, 0, 0, 0, 5, NULL, NULL },
    { 336, 2250, 0, 0, 0, 0, 0, NULL, CreateExclamationTask },
    { 329, 2251, 0, 0, 0, 0, 5, NULL, NULL },
    { 331, 2282, 0, 0, 0, 211, 4, NULL, NULL },
    { 329, 2770, 0, 0, 0, 0, 5, NULL, NULL },
    { 329, 2780, 0, 0, 0, 0, 69, NULL, NULL },
    { 333, 5000, 0, 0, 0, 45, 32868, NULL, NULL },
};

static const EventCharaKeyframe sEvent131Track7[5] = {
    { 839, 1792, 0, 0, 0, 0, 8258, NULL, NULL },
    { 839, 1793, 68864, 86016, 0, 0, 16706, NULL, NULL },
    { 839, 1850, 0, 0, 0, 0, 324, NULL, NULL },
    { 839, 1880, 65536, 71680, 0, 0, 4435, EventCharaFadeOut, NULL },
    { 839, 9999, 0, 0, 0, 0, 98370, NULL, NULL },
};

static const EventCharaKeyframe sEvent131Track8[4] = {
    { 925, 1586, 0, 0, 0, 0, 8194, NULL, NULL },
    { 924, 1670, 58112, 59136, 0, 0, 16658, NULL, NULL },
    { 924, 1705, 68096, 85760, 0, 925, 4371, NULL, NULL },
    { 924, 9999, 0, 0, 0, 0, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent131Track9[3] = {
    { 590, 1940, 0, 0, 0, 0, 8194, NULL, NULL },
    { 590, 1960, 63232, 68352, 0, 0, 16658, NULL, NULL },
    { 590, 9999, 0, 0, 0, 0, 98306, NULL, NULL },
};

static const EventCharaTrack sEvent131Tracks[10] = {
    { sEvent131Track0, 0 },
    { sEvent131Track1, 1 },
    { sEvent131Track2, 2 },
    { sEvent131Track3, 8 },
    { sEvent131Track4, 30 },
    { sEvent131Track5, 22 },
    { sEvent131Track6, 16 },
    { sEvent131Track7, 78 },
    { sEvent131Track8, 91 },
    { sEvent131Track9, 49 },
};

const EventSequenceDef gEvent131 = {
    10,
    sEvent131Tracks,
    sEvent131Camera,
    sEvent131Script,
    sEvent131SoundCues,
    sEvent131BgEffects,
    2800,
    0,
    0,
    0,
    0,
    1,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
