#ifdef VERSION_US
#include "event_133_text.inc"
#endif

static const MessageScriptEntry sEvent133Script[11] = {
    { PORTRAIT_BEAST, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent133Text00), 0, 900 },
    { PORTRAIT_BEAST, 1, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent133Text01), 0, 960 },
    { PORTRAIT_BELLE, 4, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent133Text02), 0, 990 },
    { PORTRAIT_BELLE, 1, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent133Text03), 0, 992 },
    { PORTRAIT_BEAST, 1, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent133Text04), 0, 1020 },
    { PORTRAIT_BEAST, 4, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent133Text05), 0, 1022 },
    { PORTRAIT_BELLE, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent133Text06), 0, 1050 },
    { PORTRAIT_BEAST, 1, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent133Text07), 0, 1080 },
    { PORTRAIT_GOOFY, 1, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent133Text08), 0, 1280 },
    { PORTRAIT_SORA, 1, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent133Text09), 0, 1310 },
    { PORTRAIT_DONALD, 3, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent133Text10), MSG_SCRIPT_FLAG_END, 1340 },
};

#ifdef VERSION_JP
#include "event_133_text.inc"
#endif

static const EvSoundCue sEvent133SoundCues[7] = {
    { 65535, 0, 0, 0 },
    { SONG_EV_CARDFALL, 305, 0, 0 },
    { SONG_EV_WHITEOUT, 580, 0, 0 },
    { SONG_SND_351, 834, 0, 0 },
    { SONG_SND_351, 1019, 0, 0 },
    { SONG_BGM_EVENT4, 1060, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT4, 1505, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent133Camera[13] = {
    { -65535, 42240, 74752, 0, 255, 0, 0, NULL },
    { -65385, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 100, NULL },
    { -65256, 0, 0, 0, 255, CAMERA_MODE_KEEP, 0, NULL },
    { -65036, 76032, 57600, 0, 255, CAMERA_MODE_APPROACH, 150, NULL },
    { -65026, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_HALF_FLASH | CAMERA_MODE_KEEP, 10, NULL },
    { -64996, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_HALF_FLASH | CAMERA_MODE_KEEP, 10, NULL },
    { -64956, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_HALF_FLASH | CAMERA_MODE_KEEP, 10, NULL },
    { -64856, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 90, NULL },
    { -64756, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 100, NULL },
    { -64586, 0, 0, 0, 255, CAMERA_MODE_KEEP, 0, NULL },
    { -64436, 78848, 55040, 0, 255, CAMERA_MODE_APPROACH, 30, NULL },
    { -64106, 38144, 81408, 0, 255, CAMERA_MODE_APPROACH, 150, NULL },
    { -60536, 76032, 57600, 0, 255, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 150, NULL },
};

static const EventCharaKeyframe sEvent133Track0[10] = {
    { 21, 90, 32000, 87808, 0, 0, 66, NULL, NULL },
    { 22, 100, 0, 0, 0, 0, 69, NULL, NULL },
    { 4, 1305, 0, 0, 0, 0, 69, NULL, NULL },
    { 36, 1342, 0, 0, 0, 0, 69, NULL, NULL },
    { 4, 1360, 0, 0, 0, 0, 69, NULL, NULL },
    { 3, 1365, 0, 0, 0, 0, 69, NULL, NULL },
    { 2, 1370, 0, 0, 0, 0, 69, NULL, NULL },
    { 1, 1375, 0, 0, 0, 0, 5, NULL, NULL },
    { 2, 1390, 0, 0, 0, 0, 5, NULL, NULL },
    { 7, 5000, 0, 0, 0, 173, 32772, NULL, NULL },
};

static const EventCharaKeyframe sEvent133Track1[10] = {
    { 123, 100, 44544, 87296, 0, 0, 66, NULL, NULL },
    { 124, 110, 0, 0, 0, 0, 69, NULL, NULL },
    { 114, 1282, 0, 0, 0, 0, 69, NULL, NULL },
    { 110, 1287, 0, 0, 0, 0, 5, NULL, NULL },
    { 114, 1335, 0, 0, 0, 0, 5, NULL, NULL },
    { 126, 1342, 0, 0, 0, 0, 5, NULL, NULL },
    { 114, 1380, 0, 0, 0, 0, 5, NULL, NULL },
    { 113, 1385, 0, 0, 0, 0, 5, NULL, NULL },
    { 112, 1400, 0, 0, 0, 0, 5, NULL, NULL },
    { 117, 5000, 0, 0, 0, 173, 32772, NULL, NULL },
};

static const EventCharaKeyframe sEvent133Track2[10] = {
    { 158, 105, 34048, 79616, 0, 0, 66, NULL, NULL },
    { 159, 115, 0, 0, 0, 0, 69, NULL, NULL },
    { 146, 1250, 0, 0, 0, 0, 69, NULL, NULL },
    { 145, 1255, 0, 0, 0, 0, 69, NULL, NULL },
    { 144, 1278, 0, 0, 0, 0, 69, NULL, NULL },
    { 164, 1282, 0, 0, 0, 0, 69, NULL, NULL },
    { 144, 1375, 0, 0, 0, 0, 69, NULL, NULL },
    { 143, 1380, 0, 0, 0, 0, 5, NULL, NULL },
    { 144, 1395, 0, 0, 0, 0, 5, NULL, NULL },
    { 149, 5000, 0, 0, 0, 173, 32772, NULL, NULL },
};

static const EventCharaKeyframe sEvent133Track3[6] = {
    { 374, 675, 0, 0, 0, 0, 2, NULL, NULL },
    { 374, 980, 84224, 60160, 0, 0, 2, NULL, NULL },
    { 380, 991, 0, 0, 0, 0, 5, NULL, NULL },
    { 374, 1490, 0, 0, 0, 0, 5, NULL, NULL },
    { 376, 1530, 81408, 62720, 0, 374, 3, NULL, NULL },
    { 374, 5000, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent133Track4[12] = {
    { 334, 95, 50688, 78080, 0, 0, 66, NULL, NULL },
    { 329, 200, 0, 0, 0, 0, 69, NULL, NULL },
    { 329, 250, 0, 0, 0, 0, 64, NULL, CreateQuestionTask },
    { 329, 300, 0, 0, 0, 0, 69, NULL, NULL },
    { 331, 350, 0, 0, 0, 45, 68, NULL, NULL },
    { 329, 830, 0, 0, 0, 0, 69, NULL, NULL },
    { 336, 880, 0, 0, 0, 0, 64, NULL, CreateExclamationTask },
    { 329, 905, 0, 0, 0, 0, 69, NULL, NULL },
    { 331, 950, 0, 0, 0, 45, 68, NULL, NULL },
    { 329, 1015, 0, 0, 0, 0, 69, NULL, NULL },
    { 334, 1021, 0, 0, 0, 0, 69, NULL, NULL },
    { 329, 5000, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent133Track5[5] = {
    { 839, 299, 0, 0, 0, 0, 258, NULL, NULL },
    { 839, 300, 84480, 30464, 0, 0, 258, NULL, NULL },
    { 839, 450, 84480, 53248, 0, 839, 259, NULL, NULL },
    { 839, 675, 0, 0, 0, 0, 261, NULL, NULL },
    { 839, 9999, 0, 0, 0, 0, 33090, NULL, NULL },
};

static const EventCharaTrack sEvent133Tracks[6] = {
    { sEvent133Track0, 0 },
    { sEvent133Track1, 1 },
    { sEvent133Track2, 2 },
    { sEvent133Track3, 22 },
    { sEvent133Track4, 16 },
    { sEvent133Track5, 78 },
};

const EventSequenceDef gEvent133 = {
    6,
    sEvent133Tracks,
    sEvent133Camera,
    sEvent133Script,
    sEvent133SoundCues,
    NULL,
    1510,
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
