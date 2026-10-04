#ifdef VERSION_US
#include "event_097_text.inc"
static const MessageScriptEntry sEvent097Script[21] = {
    { 0, 4, 1, 1, gEvent097Text00, 0, 300 },
    { 5, 0, 3, 1, gEvent097Text01, 0, 450 },
    { 0, 3, 1, 1, gEvent097Text02, 0, 470 },
    { 2, 1, 1, 1, gEvent097Text03, 0, 480 },
    { 1, 4, 1, 1, gEvent097Text04, 0, 490 },
    { 5, 3, 3, 1, gEvent097Text05, 0, 630 },
    { 5, 1, 4, 1, gEvent097Text06, 0, 632 },
    { 5, 3, 3, 1, gEvent097Text07, 0, 750 },
    { 9, 0, 1, 1, gEvent097Text08, 0, 770 },
    { 9, 0, 3, 1, gEvent097Text09, 0, 850 },
    { 9, 0, 4, 1, gEvent097Text10, 0, 852 },
    { 9, 0, 4, 1, gEvent097Text11, 0, 854 },
    { 0, 0, 1, 1, gEvent097Text12, 0, 870 },
    { 6, 1, 3, 1, gEvent097Text13, 0, 900 },
    { 0, 0, 1, 1, gEvent097Text14, 0, 1050 },
    { 9, 0, 3, 1, gEvent097Text15, 0, 1070 },
    { 0, 3, 1, 1, gEvent097Text16, 0, 1080 },
    { 9, 0, 2, 1, gEvent097Text17, 0, 1190 },
    { 9, 0, 4, 1, gEvent097Text18, 0, 1192 },
    { 0, 0, 1, 1, gEvent097Text19, 0, 1210 },
    { 9, 0, 3, 1, gEvent097Text20, MSG_SCRIPT_FLAG_END, 1280 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent097Script[21] = {
    { 0, 4, 1, 3, gEvent097Text00, 0, 300 },
    { 5, 3, 3, 3, gEvent097Text01, 0, 450 },
    { 0, 3, 1, 3, gEvent097Text02, 0, 470 },
    { 2, 1, 1, 3, gEvent097Text03, 0, 480 },
    { 1, 4, 1, 3, gEvent097Text04, 0, 490 },
    { 5, 3, 3, 3, gEvent097Text05, 0, 630 },
    { 5, 1, 4, 3, gEvent097Text06, 0, 632 },
    { 5, 3, 3, 3, gEvent097Text07, 0, 750 },
    { 9, 0, 1, 3, gEvent097Text08, 0, 770 },
    { 9, 0, 3, 3, gEvent097Text09, 0, 850 },
    { 9, 0, 4, 3, gEvent097Text10, 0, 852 },
    { 9, 0, 4, 3, gEvent097Text11, 0, 854 },
    { 0, 0, 1, 3, gEvent097Text12, 0, 870 },
    { 6, 1, 3, 3, gEvent097Text13, 0, 900 },
    { 0, 0, 1, 3, gEvent097Text14, 0, 1050 },
    { 9, 0, 3, 3, gEvent097Text15, 0, 1070 },
    { 0, 3, 1, 3, gEvent097Text16, 0, 1080 },
    { 9, 0, 2, 3, gEvent097Text17, 0, 1190 },
    { 9, 0, 4, 3, gEvent097Text18, 0, 1192 },
    { 0, 0, 1, 3, gEvent097Text19, 0, 1210 },
    { 9, 0, 3, 3, gEvent097Text20, MSG_SCRIPT_FLAG_END, 1280 },
};

#include "event_097_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent097Script[21] = {
    { 0, 4, 1, 1, &gEvent097Text00, 0, 300 },
    { 5, 0, 3, 1, &gEvent097Text01, 0, 450 },
    { 0, 3, 1, 1, &gEvent097Text02, 0, 470 },
    { 2, 1, 1, 1, &gEvent097Text03, 0, 480 },
    { 1, 4, 1, 1, &gEvent097Text04, 0, 490 },
    { 5, 3, 3, 1, &gEvent097Text05, 0, 630 },
    { 5, 1, 4, 1, &gEvent097Text06, 0, 632 },
    { 5, 3, 3, 1, &gEvent097Text07, 0, 750 },
    { 9, 0, 1, 1, &gEvent097Text08, 0, 770 },
    { 9, 0, 3, 1, &gEvent097Text09, 0, 850 },
    { 9, 0, 4, 1, &gEvent097Text10, 0, 852 },
    { 9, 0, 4, 1, &gEvent097Text11, 0, 854 },
    { 0, 0, 1, 1, &gEvent097Text12, 0, 870 },
    { 6, 1, 3, 1, &gEvent097Text13, 0, 900 },
    { 0, 0, 1, 1, &gEvent097Text14, 0, 1050 },
    { 9, 0, 3, 1, &gEvent097Text15, 0, 1070 },
    { 0, 3, 1, 1, &gEvent097Text16, 0, 1080 },
    { 9, 0, 2, 1, &gEvent097Text17, 0, 1190 },
    { 9, 0, 4, 1, &gEvent097Text18, 0, 1192 },
    { 0, 0, 1, 1, &gEvent097Text19, 0, 1210 },
    { 9, 0, 3, 1, &gEvent097Text20, MSG_SCRIPT_FLAG_END, 1280 },
};
#endif

static const EventCameraKeyframe sEvent097Camera[4] = {
    { -64876, 57344, 45312, 0, 255, 0, 0, NULL },
    { -64696, 61184, 38912, 0, 255, CAMERA_MODE_APPROACH, 20, NULL },
    { -64386, 51456, 40960, 0, 255, CAMERA_MODE_APPROACH, 20, NULL },
    { -55537, 57344, 45312, 0, 255, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 20, NULL },
};

static const EvSoundCue sEvent097SoundCues[5] = {
    { SONG_BGM_EVENT3, 0, 0, 0 },
    { SONG_SND_346, 640, 0, 0 },
    { SONG_SND_346, 821, 0, 0 },
    { SONG_SND_346, 1131, 0, 0 },
    { SONG_BGM_EVENT3, 1395, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent097Track0[10] = {
    { 221, 100, 54016, 43264, 0, 0, 66, NULL, NULL },
    { 223, 150, 48896, 40704, 0, 221, 67, NULL, NULL },
    { 221, 301, 0, 0, 0, 0, 69, NULL, NULL },
    { 221, 430, 0, 0, 0, 0, 64, NULL, CreateBalloonTask },
    { 221, 660, 0, 0, 0, 0, 69, NULL, NULL },
    { 222, 670, 0, 0, 0, 0, 69, NULL, NULL },
    { 222, 830, 0, 0, 0, 0, 64, NULL, CreateExclamationTask },
    { 222, 1140, 0, 0, 0, 0, 5, NULL, NULL },
    { 221, 1150, 0, 0, 0, 0, 5, NULL, NULL },
    { 221, 9999, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent097Track1[19] = {
    { 4, 0, 96768, 64768, 0, 0, 2, NULL, NULL },
    { 9, 150, 0, 0, 0, 211, 4, NULL, NULL },
    { 4, 299, 0, 0, 0, 0, 5, NULL, NULL },
    { 36, 469, 0, 0, 0, 0, 5, NULL, NULL },
    { 30, 491, 0, 0, 0, 0, 5, NULL, NULL },
    { 16, 620, 0, 0, 0, 0, 0, NULL, CreateBalloonTask },
    { 4, 662, 0, 0, 0, 0, 5, NULL, NULL },
    { 0, 665, 0, 0, 0, 0, 5, NULL, NULL },
    { 4, 670, 0, 0, 0, 0, 69, NULL, NULL },
    { 4, 830, 0, 0, 0, 0, 64, NULL, CreateExclamationTask },
    { 0, 835, 0, 0, 0, 0, 5, NULL, NULL },
    { 4, 869, 0, 0, 0, 0, 5, NULL, NULL },
    { 34, 901, 0, 0, 0, 0, 5, NULL, NULL },
    { 34, 1049, 0, 0, 0, 0, 0, NULL, CreateBalloonTask },
    { 34, 1051, 0, 0, 0, 0, 5, NULL, NULL },
    { 4, 1140, 0, 0, 0, 0, 5, NULL, NULL },
    { 3, 1145, 0, 0, 0, 0, 5, NULL, NULL },
    { 2, 1150, 0, 0, 0, 0, 5, NULL, NULL },
    { 2, 9999, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent097Track2[13] = {
    { 114, 0, 106752, 62976, 0, 0, 2, NULL, NULL },
    { 119, 150, 0, 0, 0, 211, 4, NULL, NULL },
    { 114, 489, 0, 0, 0, 0, 5, NULL, NULL },
    { 126, 491, 0, 0, 0, 0, 5, NULL, NULL },
    { 114, 660, 0, 0, 0, 0, 5, NULL, NULL },
    { 110, 665, 0, 0, 0, 0, 5, NULL, NULL },
    { 114, 670, 0, 0, 0, 0, 69, NULL, NULL },
    { 114, 840, 0, 0, 0, 0, 64, NULL, CreateExclamationTask },
    { 110, 835, 0, 0, 0, 0, 5, NULL, NULL },
    { 114, 1140, 0, 0, 0, 0, 5, NULL, NULL },
    { 113, 1145, 0, 0, 0, 0, 5, NULL, NULL },
    { 112, 1150, 0, 0, 0, 0, 5, NULL, NULL },
    { 112, 9999, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent097Track3[13] = {
    { 146, 0, 102400, 71168, 0, 0, 2, NULL, NULL },
    { 151, 150, 0, 0, 0, 211, 4, NULL, NULL },
    { 146, 479, 0, 0, 0, 0, 5, NULL, NULL },
    { 165, 481, 0, 0, 0, 0, 5, NULL, NULL },
    { 146, 665, 0, 0, 0, 0, 5, NULL, NULL },
    { 142, 670, 0, 0, 0, 0, 5, NULL, NULL },
    { 146, 675, 0, 0, 0, 0, 69, NULL, NULL },
    { 146, 830, 0, 0, 0, 0, 64, NULL, CreateExclamationTask },
    { 142, 835, 0, 0, 0, 0, 5, NULL, NULL },
    { 146, 1140, 0, 0, 0, 0, 5, NULL, NULL },
    { 145, 1145, 0, 0, 0, 0, 5, NULL, NULL },
    { 144, 1150, 0, 0, 0, 0, 5, NULL, NULL },
    { 144, 9999, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent097Track4[13] = {
    { 231, 150, 0, 0, 0, 0, 2, NULL, NULL },
    { 231, 151, 61952, 47360, 0, 0, 2, NULL, NULL },
    { 234, 180, 0, 0, 0, 211, 4, EventCharaHop, NULL },
    { 231, 660, 0, 0, 0, 0, 5, NULL, NULL },
    { 231, 670, 0, 0, 0, 0, 69, NULL, NULL },
    { 231, 830, 0, 0, 0, 0, 64, NULL, CreateExclamationTask },
    { 231, 880, 0, 0, 0, 0, 5, NULL, NULL },
    { 231, 885, 0, 0, 0, 0, 69, NULL, NULL },
    { 229, 1071, 0, 0, 0, 0, 69, NULL, NULL },
    { 229, 1075, 0, 0, 0, 0, 5, NULL, NULL },
    { 231, 1140, 0, 0, 0, 0, 5, NULL, NULL },
    { 229, 1150, 0, 0, 0, 0, 5, NULL, NULL },
    { 229, 9999, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent097Track5[11] = {
    { 337, 640, 0, 0, 0, 0, 2, NULL, NULL },
    { 337, 765, 81920, 32768, 0, 0, 258, EventCharaFadeIn, NULL },
    { 340, 780, 0, 0, 0, 0, 261, NULL, NULL },
    { 340, 820, 81920, 32768, 0, 0, 258, EventCharaFadeOut, NULL },
    { 337, 821, 0, 0, 0, 0, 258, NULL, NULL },
    { 339, 1090, 34048, 34048, 0, 0, 258, EventCharaFadeIn, NULL },
    { 339, 1130, 34048, 34048, 0, 0, 258, EventCharaFadeOut, NULL },
    { 337, 1131, 0, 0, 0, 0, 258, NULL, NULL },
    { 338, 1220, 40704, 57088, 0, 0, 66, EventCharaFadeIn, NULL },
    { 338, 1300, 40704, 57088, 0, 0, 66, EventCharaFadeOut, NULL },
    { 337, 9999, 0, 0, 0, 0, 32834, NULL, NULL },
};

static const EventCharaTrack sEvent097Tracks[6] = {
    { sEvent097Track0, 7 },
    { sEvent097Track1, 0 },
    { sEvent097Track2, 1 },
    { sEvent097Track3, 2 },
    { sEvent097Track4, 8 },
    { sEvent097Track5, 17 },
};

const EventSequenceDef gEvent097 = {
    6,
    sEvent097Tracks,
    sEvent097Camera,
    sEvent097Script,
    sEvent097SoundCues,
    NULL,
    1400,
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
