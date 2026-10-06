#ifdef VERSION_US
#include "event_187_text.inc"
#endif

static const MessageScriptEntry sEvent187Script[13] = {
    { PORTRAIT_RIKU, 0, 0, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent187Text00), 0, 410 },
    { PORTRAIT_RIKU_REPLICA, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent187Text01), MSG_SCRIPT_FLAG_SILHOUETTE, 440 },
    { PORTRAIT_RIKU_REPLICA, 1, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent187Text02), 0, 750 },
    { PORTRAIT_RIKU_REPLICA, 1, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent187Text03), 0, 752 },
    { PORTRAIT_RIKU, 0, 0, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent187Text04), 0, 780 },
    { PORTRAIT_RIKU_REPLICA, 1, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent187Text05), 0, 810 },
    { PORTRAIT_RIKU, 2, 0, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent187Text06), 0, 860 },
    { PORTRAIT_RIKU_REPLICA, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent187Text07), 0, 1040 },
    { PORTRAIT_RIKU_REPLICA, 1, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent187Text08), 0, 1042 },
    { PORTRAIT_RIKU_REPLICA, 2, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent187Text09), 0, 1070 },
    { PORTRAIT_RIKU_REPLICA, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent187Text10), 0, 1260 },
    { PORTRAIT_RIKU_REPLICA, 2, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent187Text11), 0, 1263 },
    { PORTRAIT_RIKU_REPLICA, 2, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent187Text12), MSG_SCRIPT_FLAG_END, 1430 },
};

#ifdef VERSION_JP
#include "event_187_text.inc"
#endif

static const EvSoundCue sEvent187SoundCues[7] = {
    { 65535, 0, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 550, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT_UNREST, 1065, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_SND_377, 1130, 0, 0 },
    { SONG_BGM_EVENT2, 1140, 0, 0 },
    { SONG_SND_359, 1310, 0, 0 },
    { SONG_SND_359, 1350, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent187Camera[3] = {
    { -65416, 65024, 42496, 0, 255, 0, 0, NULL },
    { -64436, 65024, 88576, 0, 255, CAMERA_MODE_APPROACH, 260, NULL },
    { -63536, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, NULL },
};

static const EventBgEffectEntry sEvent187BgEffects[5] = {
    { 1072, 0, 0, 0, 0 },
    { 1130, 0, 50, 0, 0x4 },
    { 1226, 5, 44032, 74752, 0x1 },
    { 1230, 0, 0, 0, 0x2 },
    { 1265, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent187Track0[10] = {
    { 515, 460, 73728, 99328, 0, 0, 2, NULL, NULL },
    { 515, 510, 0, 0, 0, 0, 0, NULL, CreateExclamationTask },
    { 515, 540, 0, 0, 0, 0, 5, NULL, NULL },
    { 514, 625, 0, 0, 0, 0, 5, NULL, NULL },
    { 515, 1100, 0, 0, 0, 0, 5, NULL, NULL },
    { 532, 1130, 0, 0, 0, 0, 5, NULL, NULL },
    { 532, 1180, 0, 0, 0, 0, 0, NULL, CreateExclamationTask },
    { 532, 1250, 0, 0, 0, 0, 5, NULL, NULL },
    { 515, 1350, 0, 0, 0, 0, 5, NULL, NULL },
    { 560, 5000, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent187Track1[13] = {
    { 696, 510, 29952, 117504, 0, 0, 66, NULL, NULL },
    { 712, 670, 56064, 93952, 0, 696, 67, NULL, NULL },
    { 696, 680, 0, 0, 0, 0, 69, NULL, NULL },
    { 695, 735, 0, 0, 0, 0, 69, NULL, NULL },
    { 707, 790, 0, 0, 0, 0, 69, NULL, NULL },
    { 695, 880, 0, 0, 0, 0, 69, NULL, NULL },
    { 695, 1010, 0, 0, 0, 0, 64, NULL, CreateBalloonTask },
    { 695, 1060, 0, 0, 0, 0, 69, NULL, NULL },
    { 706, 1230, 0, 0, 0, 0, 69, NULL, NULL },
    { 695, 1261, 0, 0, 0, 0, 69, NULL, NULL },
    { 706, 1265, 0, 0, 0, 0, 69, NULL, NULL },
    { 695, 1310, 0, 0, 0, 0, 69, NULL, NULL },
    { 698, 2000, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent187Tracks[2] = {
    { sEvent187Track0, EVENT_CHARA_RIKU },
    { sEvent187Track1, EVENT_CHARA_RIKU_REPLICA },
};

const EventSequenceDef gEvent187 = {
    2,
    sEvent187Tracks,
    sEvent187Camera,
    sEvent187Script,
    sEvent187SoundCues,
    sEvent187BgEffects,
    1490,
    0,
    1,
    0,
    0,
    0,
    BATTLE_RIKU_6,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
