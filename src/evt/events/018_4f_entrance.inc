#ifdef VERSION_US
#include "event_018_text.inc"
#endif

static const MessageScriptEntry sEvent018Script[16] = {
    { 1, 2, 2, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent018Text00), 0, 210 },
    { 2, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent018Text01), 0, 230 },
    { 2, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent018Text02), 0, 380 },
    { 2, 1, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent018Text03), 0, 382 },
    { 0, 4, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent018Text04), 0, 410 },
    { 0, 4, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent018Text05), 0, 500 },
    { 1, 0, 2, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent018Text06), 0, 520 },
    { 0, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent018Text07), 0, 540 },
    { 0, 0, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent018Text08), 0, 542 },
    { 0, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent018Text09), 0, 760 },
    { 0, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent018Text10), 0, 1170 },
    { 0, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent018Text11), 0, 1340 },
    { 0, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent018Text12), 0, 1500 },
    { 1, 5, 2, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent018Text13), 0, 1540 },
    { 0, 3, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent018Text14), 0, 1640 },
    { 2, 1, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent018Text15), MSG_SCRIPT_FLAG_END, 1660 },
};

#ifdef VERSION_JP
#include "event_018_text.inc"
#endif

static const EventCameraKeyframe sEvent018Camera[3] = {
    { -64656, 182528, 66304, 0, 255, 0, 0, NULL },
    { -64236, 200448, 56832, 0, 255, CAMERA_MODE_APPROACH, 100, NULL },
    { -64036, 182528, 66304, 0, 255, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 60, NULL },
};

static const EvSoundCue sEvent018SoundCues[4] = {
    { SONG_BGM_T13THFLOOR, 0, 0, 0 },
    { SONG_BGM_T13THFLOOR, 415, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_SND_369, 820, 0, 0 },
    { SONG_SND_370, 1260, EV_SOUND_FLAG_END, 0 },
};

static const EventBgEffectEntry sEvent018BgEffects[3] = {
    { 820, 0, 0, 0, 0 },
    { 1300, 0, 0, 0, 0x14 },
    { 1900, 0, 0, 0, 0x8018 },
};

static const EventCharaKeyframe sEvent018Track0[31] = {
    { 4, 0, 152832, 85504, 0, 0, 66, NULL, NULL },
    { 9, 170, 190208, 68352, 0, 4, 67, NULL, NULL },
    { 4, 180, 0, 0, 0, 0, 69, NULL, NULL },
    { 3, 185, 0, 0, 0, 0, 69, NULL, NULL },
    { 2, 190, 0, 0, 0, 0, 69, NULL, NULL },
    { 1, 195, 0, 0, 0, 0, 5, NULL, NULL },
    { 2, 240, 0, 0, 0, 0, 5, NULL, NULL },
    { 32, 370, 0, 0, 0, 0, 0, NULL, CreateBalloonTask },
    { 32, 390, 0, 0, 0, 0, 5, NULL, NULL },
    { 2, 415, 0, 0, 0, 0, 5, NULL, NULL },
    { 89, 550, 0, 0, 0, 0, 5, NULL, NULL },
    { 89, 680, 0, 0, 0, 0, 0, NULL, CreateBalloonTask },
    { 88, 690, 0, 0, 0, 0, 5, NULL, NULL },
    { 1, 695, 0, 0, 0, 0, 5, NULL, NULL },
    { 2, 700, 0, 0, 0, 0, 69, NULL, NULL },
    { 3, 705, 0, 0, 0, 0, 69, NULL, NULL },
    { 4, 720, 0, 0, 0, 0, 69, NULL, NULL },
    { 4, 1120, 0, 0, 0, 0, 69, NULL, NULL },
    { 4, 1170, 0, 0, 0, 0, 64, NULL, CreateExclamationTask },
    { 4, 1350, 0, 0, 0, 0, 69, NULL, NULL },
    { 4, 1480, 0, 0, 0, 0, 64, NULL, CreateBalloonTask },
    { 4, 1550, 0, 0, 0, 0, 69, NULL, NULL },
    { 27, 1600, 0, 0, 0, 0, 64, NULL, CreateExclamationTask },
    { 4, 1610, 0, 0, 0, 0, 69, NULL, NULL },
    { 3, 1615, 0, 0, 0, 0, 69, NULL, NULL },
    { 2, 1620, 0, 0, 0, 0, 69, NULL, NULL },
    { 1, 1625, 0, 0, 0, 0, 5, NULL, NULL },
    { 2, 1670, 0, 0, 0, 0, 5, NULL, NULL },
    { 15, 1680, 0, 0, 0, 0, 5, NULL, NULL },
    { 17, 1690, 0, 0, 0, 0, 5, NULL, NULL },
    { 2, 9999, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent018Track1[20] = {
    { 114, 0, 150272, 91904, 0, 0, 66, NULL, NULL },
    { 119, 160, 179712, 77312, 0, 114, 67, NULL, NULL },
    { 114, 209, 0, 0, 0, 0, 69, NULL, NULL },
    { 126, 211, 0, 0, 0, 0, 69, NULL, NULL },
    { 114, 235, 0, 0, 0, 0, 69, NULL, NULL },
    { 127, 240, 0, 0, 0, 0, 69, NULL, NULL },
    { 128, 370, 0, 0, 0, 0, 64, NULL, CreateBalloonTask },
    { 128, 420, 0, 0, 0, 0, 69, NULL, NULL },
    { 129, 430, 0, 0, 0, 0, 69, NULL, NULL },
    { 114, 519, 0, 0, 0, 0, 69, NULL, NULL },
    { 126, 521, 0, 0, 0, 0, 69, NULL, NULL },
    { 114, 820, 0, 0, 0, 0, 69, NULL, NULL },
    { 114, 840, 0, 0, 0, 0, 64, EventCharaFadeOut, NULL },
    { 114, 1300, 0, 0, 0, 0, 66, NULL, NULL },
    { 114, 1320, 179712, 77312, 0, 0, 66, EventCharaFadeIn, NULL },
    { 114, 1350, 0, 0, 0, 0, 69, NULL, NULL },
    { 114, 1480, 0, 0, 0, 0, 64, NULL, CreateQuestionTask },
    { 114, 1539, 0, 0, 0, 0, 69, NULL, NULL },
    { 126, 1541, 0, 0, 0, 0, 69, NULL, NULL },
    { 114, 9999, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent018Track2[21] = {
    { 146, 0, 141568, 91648, 0, 0, 66, NULL, NULL },
    { 151, 160, 173056, 71680, 0, 146, 67, NULL, NULL },
    { 146, 170, 0, 0, 0, 0, 69, NULL, NULL },
    { 145, 175, 0, 0, 0, 0, 69, NULL, NULL },
    { 144, 220, 0, 0, 0, 0, 69, NULL, NULL },
    { 145, 225, 0, 0, 0, 0, 69, NULL, NULL },
    { 146, 230, 0, 0, 0, 0, 69, NULL, NULL },
    { 170, 240, 0, 0, 0, 0, 69, NULL, NULL },
    { 170, 370, 0, 0, 0, 0, 64, NULL, CreateBalloonTask },
    { 146, 375, 0, 0, 0, 0, 69, NULL, NULL },
    { 145, 379, 0, 0, 0, 0, 69, NULL, NULL },
    { 167, 383, 0, 0, 0, 0, 69, NULL, NULL },
    { 145, 820, 0, 0, 0, 0, 69, NULL, NULL },
    { 145, 840, 0, 0, 0, 0, 64, EventCharaFadeOut, NULL },
    { 145, 1300, 0, 0, 0, 0, 66, NULL, NULL },
    { 145, 1320, 173056, 71680, 0, 0, 66, EventCharaFadeIn, NULL },
    { 145, 1350, 0, 0, 0, 0, 69, NULL, NULL },
    { 145, 1480, 0, 0, 0, 0, 64, NULL, CreateQuestionTask },
    { 145, 1659, 0, 0, 0, 0, 69, NULL, NULL },
    { 167, 1661, 0, 0, 0, 0, 69, NULL, NULL },
    { 145, 9999, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent018Track3[5] = {
    { 420, 970, 0, 0, 0, 0, 8194, NULL, NULL },
    { 420, 1000, 205568, 58112, 0, 0, 16642, EventCharaFadeIn, NULL },
    { 420, 1220, 0, 0, 0, 0, 261, NULL, NULL },
    { 420, 1250, 0, 0, 0, 0, 256, EventCharaFadeOut, NULL },
    { 420, 9999, 0, 0, 0, 0, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent018Track4[5] = {
    { 422, 1080, 0, 0, 0, 0, 8194, NULL, NULL },
    { 422, 1110, 205568, 58368, 0, 0, 540930, EventCharaFadeIn, NULL },
    { 422, 1260, 0, 0, 0, 0, 524549, NULL, NULL },
    { 422, 1290, 0, 0, 0, 0, 524544, EventCharaFadeOut, NULL },
    { 422, 1300, 0, 0, 0, 0, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent018Track5[3] = {
    { 911, 450, 0, 0, 0, 0, 8194, NULL, NULL },
    { 911, 680, 190208, 68352, 0, 0, 16658, NULL, NULL },
    { 911, 1000, 0, 0, 0, 0, 98306, NULL, NULL },
};

static const EventCharaTrack sEvent018Tracks[6] = {
    { sEvent018Track0, 0 },
    { sEvent018Track1, 1 },
    { sEvent018Track2, 2 },
    { sEvent018Track3, 34 },
    { sEvent018Track4, 35 },
    { sEvent018Track5, 85 },
};

const EventSequenceDef gEvent018 = {
    6,
    sEvent018Tracks,
    sEvent018Camera,
    sEvent018Script,
    sEvent018SoundCues,
    sEvent018BgEffects,
    1740,
    1,
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
    255,
};
