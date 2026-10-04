#ifdef VERSION_US
#include "event_098_text.inc"
#endif

static const MessageScriptEntry sEvent098Script[16] = {
    { 2, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent098Text00), 0, 170 },
    { 5, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent098Text01), 0, 200 },
    { 5, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent098Text02), 0, 450 },
    { 4, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent098Text03), 0, 530 },
    { 0, 2, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent098Text04), 0, 540 },
    { 4, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent098Text05), 0, 560 },
    { 4, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent098Text06), 0, 700 },
    { 4, 2, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent098Text07), 0, 710 },
    { 4, 2, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent098Text08), 0, 910 },
    { 4, 2, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent098Text09), 0, 913 },
    { 1, 5, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent098Text10), 0, 930 },
    { 4, 2, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent098Text11), 0, 950 },
    { 4, 1, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent098Text12), 0, 952 },
    { 0, 0, 2, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent098Text13), 0, 1070 },
    { 2, 0, 2, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent098Text14), 0, 1090 },
    { 5, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent098Text15), MSG_SCRIPT_FLAG_END, 1190 },
};

#ifdef VERSION_JP
#include "event_098_text.inc"
#endif

static const EvSoundCue sEvent098SoundCues[4] = {
    { SONG_BGM_EVENT1, 0, 0, 0 },
    { SONG_EV_FLASH02, 600, 0, 0 },
    { SONG_BGM_EVENT2, 1130, 0, 0 },
    { SONG_EV_FLASH02, 1230, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent098Camera[16] = {
    { -65076, 47872, 89088, 0, 255, 0, 0, NULL },
    { -64975, 74752, 65792, 0, 255, CAMERA_MODE_APPROACH, 60, NULL },
    { -64956, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, NULL },
    { -64936, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, NULL },
    { -64876, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 10, NULL },
    { -64846, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 20, NULL },
    { -64566, 0, 0, 0, 255, CAMERA_MODE_KEEP, 0, NULL },
    { -64486, 55040, 79104, 0, 255, CAMERA_MODE_APPROACH, 50, NULL },
    { -64436, 0, 0, 0, 255, CAMERA_MODE_KEEP, 0, NULL },
    { -64426, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, NULL },
    { -64396, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, NULL },
    { -64336, 0, 0, 0, 255, CAMERA_MODE_KEEP, 0, NULL },
    { -64326, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, NULL },
    { -64306, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, NULL },
    { -64136, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 30, NULL },
    { -55537, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, NULL },
};

static const EventCharaKeyframe sEvent098Track0[7] = {
    { 4, 1, 32000, 93952, 0, 0, 66, NULL, NULL },
    { 9, 40, 0, 0, 0, 45, 68, NULL, NULL },
    { 4, 451, 0, 0, 0, 0, 69, NULL, NULL },
    { 4, 550, 0, 0, 0, 0, 64, NULL, CreateExclamationTask },
    { 4, 1110, 0, 0, 0, 0, 69, NULL, NULL },
    { 27, 1500, 0, 0, 0, 0, 64, NULL, CreateExclamationTask },
    { 4, 2200, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent098Track2[14] = {
    { 146, 1, 20992, 94208, 0, 0, 66, NULL, NULL },
    { 151, 40, 0, 0, 0, 45, 68, NULL, NULL },
    { 146, 90, 0, 0, 0, 0, 69, NULL, NULL },
    { 142, 120, 0, 0, 0, 0, 5, NULL, NULL },
    { 145, 150, 0, 0, 0, 0, 69, NULL, NULL },
    { 146, 169, 0, 0, 0, 0, 69, NULL, NULL },
    { 165, 171, 0, 0, 0, 0, 69, NULL, NULL },
    { 146, 451, 0, 0, 0, 0, 69, NULL, NULL },
    { 146, 550, 0, 0, 0, 0, 64, NULL, CreateExclamationTask },
    { 145, 1089, 0, 0, 0, 0, 69, NULL, NULL },
    { 145, 1091, 0, 0, 0, 0, 64, EventCharaToggleAnim, NULL },
    { 146, 1112, 0, 0, 0, 0, 69, NULL, NULL },
    { 161, 1500, 0, 0, 0, 0, 64, NULL, CreateExclamationTask },
    { 146, 2200, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent098Track1[7] = {
    { 114, 1, 31232, 101888, 0, 0, 66, NULL, NULL },
    { 119, 40, 0, 0, 0, 45, 68, NULL, NULL },
    { 114, 451, 0, 0, 0, 0, 69, NULL, NULL },
    { 114, 550, 0, 0, 0, 0, 64, NULL, CreateExclamationTask },
    { 114, 1114, 0, 0, 0, 0, 69, NULL, NULL },
    { 133, 1500, 0, 0, 0, 0, 64, NULL, CreateExclamationTask },
    { 114, 2200, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent098Track6[3] = {
    { 197, 201, 90368, 73728, 0, 0, 2, NULL, NULL },
    { 200, 341, 0, 0, 0, 0, 5, NULL, NULL },
    { 197, 600, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent098Track7[3] = {
    { 197, 207, 100096, 70400, 0, 0, 2, NULL, NULL },
    { 200, 341, 0, 0, 0, 0, 5, NULL, NULL },
    { 197, 600, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent098Track4[3] = {
    { 206, 201, 67840, 58368, 0, 0, 2, NULL, NULL },
    { 209, 341, 0, 0, 0, 0, 5, NULL, NULL },
    { 206, 600, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent098Track5[3] = {
    { 206, 208, 71424, 64768, 0, 0, 2, NULL, NULL },
    { 209, 341, 0, 0, 0, 0, 5, NULL, NULL },
    { 206, 600, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent098Track3[8] = {
    { 215, 460, 88832, 66048, 0, 0, 2, NULL, NULL },
    { 214, 510, 0, 0, 0, 173, 4, NULL, NULL },
    { 219, 711, 0, 0, 0, 0, 5, NULL, NULL },
    { 219, 780, 0, 0, 0, 0, 0, NULL, CreateQuestionTask },
    { 219, 781, 0, 0, 0, 0, 5, NULL, NULL },
    { 219, 900, 0, 0, 0, 0, 0, NULL, CreateBalloonTask },
    { 219, 911, 0, 0, 0, 0, 5, NULL, NULL },
    { 218, 9999, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent098Track8[15] = {
    { 222, 1, 38912, 90880, 0, 0, 66, NULL, NULL },
    { 224, 40, 0, 0, 0, 45, 68, NULL, NULL },
    { 222, 180, 0, 0, 0, 0, 69, NULL, NULL },
    { 221, 190, 0, 0, 0, 0, 69, NULL, NULL },
    { 221, 211, 0, 0, 0, 0, 5, NULL, NULL },
    { 221, 220, 0, 0, 0, 0, 69, NULL, NULL },
    { 222, 230, 0, 0, 0, 0, 69, NULL, NULL },
    { 226, 380, 0, 0, 0, 45, 68, NULL, NULL },
    { 222, 451, 0, 0, 0, 0, 69, NULL, NULL },
    { 224, 520, 0, 0, 0, 173, 68, NULL, NULL },
    { 222, 1091, 0, 0, 0, 0, 69, NULL, NULL },
    { 221, 1100, 0, 0, 0, 0, 69, NULL, NULL },
    { 221, 1105, 0, 0, 0, 0, 5, NULL, NULL },
    { 225, 1180, 0, 0, 0, 173, 4, NULL, NULL },
    { 221, 9999, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent098Tracks[9] = {
    { sEvent098Track0, 0 },
    { sEvent098Track1, 1 },
    { sEvent098Track2, 2 },
    { sEvent098Track3, 6 },
    { sEvent098Track4, 5 },
    { sEvent098Track5, 5 },
    { sEvent098Track6, 4 },
    { sEvent098Track7, 4 },
    { sEvent098Track8, 7 },
};

const EventSequenceDef gEvent098 = {
    9,
    sEvent098Tracks,
    sEvent098Camera,
    sEvent098Script,
    sEvent098SoundCues,
    NULL,
    1340,
    0,
    0,
    0,
    0,
    0,
    0,
    99,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
