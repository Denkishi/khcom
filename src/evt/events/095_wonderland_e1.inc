#ifdef VERSION_US
#include "event_095_text.inc"
#endif

static const MessageScriptEntry sEvent095Script[30] = {
    { 2, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text00), 0, 300 },
    { 1, 5, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text01), 0, 320 },
    { 8, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text02), 0, 380 },
    { 5, 2, 2, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text03), 0, 400 },
    { 4, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text04), 0, 420 },
    { 4, 1, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text05), 0, 422 },
    { 5, 2, 2, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text06), 0, 440 },
    { 4, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text07), 0, 460 },
    { 4, 1, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text08), 0, 462 },
    { 8, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text09), 0, 480 },
    { 8, 0, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text10), 0, 482 },
    { 5, 2, 2, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text11), 0, 500 },
    { 4, 2, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text12), 0, 520 },
    { 4, 1, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text13), 0, 522 },
    { 0, 2, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text14), 0, 630 },
    { 2, 2, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text15), 0, 750 },
    { 4, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text16), 0, 860 },
    { 0, 2, 2, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text17), 0, 880 },
    { 0, 2, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text18), 0, 950 },
    { 4, 2, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text19), 0, 970 },
    { 4, 1, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text20), 0, 972 },
    { 0, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text21), 0, 990 },
    { 4, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text22), 0, 1010 },
    { 4, 3, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text23), 0, 1012 },
    { 0, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text24), 0, 1030 },
    { 0, 2, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text25), 0, 1190 },
    { 4, 2, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text26), 0, 1210 },
    { 2, 2, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text27), 0, 1230 },
    { 0, 2, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text28), 0, 1270 },
    { 4, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent095Text29), MSG_SCRIPT_FLAG_END, 1300 },
};

#ifdef VERSION_JP
#include "event_095_text.inc"
#endif

static const EventCameraKeyframe sEvent095Camera[6] = {
    { -65436, 30720, 81920, 0, 255, 0, 0, NULL },
    { -64996, 87040, 51200, 0, 255, CAMERA_MODE_APPROACH, 100, NULL },
    { -64876, 48640, 79872, 0, 255, CAMERA_MODE_APPROACH, 60, NULL },
    { -64776, 0, 0, 0, 0, 0, 0, NULL },
    { -64636, 87040, 51200, 0, 255, CAMERA_MODE_APPROACH, 50, NULL },
    { -64537, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, NULL },
};

static const EvSoundCue sEvent095SoundCues[4] = {
    { SONG_BGM_EVENT1, 0, 0, 0 },
    { SONG_BGM_EVENT1, 1031, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT2, 1210, 0, 0 },
    { SONG_EV_EV10_01, 1305, EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent095Track0[30] = {
    { 4, 0, 25600, 92160, 0, 0, 66, NULL, NULL },
    { 9, 99, 0, 0, 0, 45, 68, NULL, NULL },
    { 4, 629, 0, 0, 0, 0, 69, NULL, NULL },
    { 30, 640, 0, 0, 0, 0, 69, NULL, NULL },
    { 4, 650, 0, 0, 0, 0, 69, NULL, NULL },
    { 13, 690, 0, 0, 0, 64, 116, NULL, NULL },
    { 14, 730, 0, 0, 0, 45, 116, NULL, NULL },
    { 4, 733, 0, 0, 0, 45, 116, NULL, NULL },
    { 4, 890, 0, 0, 0, 0, 85, NULL, NULL },
    { 10, 910, 0, 0, 0, 0, 52, NULL, NULL },
    { 14, 925, 0, 0, 0, 45, 100, NULL, NULL },
    { 4, 949, 0, 0, 0, 0, 69, NULL, NULL },
    { 30, 951, 0, 0, 0, 0, 69, NULL, NULL },
    { 4, 989, 0, 0, 0, 0, 69, NULL, NULL },
    { 30, 991, 0, 0, 0, 0, 69, NULL, NULL },
    { 4, 1029, 0, 0, 0, 0, 69, NULL, NULL },
    { 30, 1031, 0, 0, 0, 0, 69, NULL, NULL },
    { 34, 1170, 0, 0, 0, 0, 64, NULL, CreateBalloonTask },
    { 4, 1189, 0, 0, 0, 0, 69, NULL, NULL },
    { 30, 1231, 0, 0, 0, 0, 69, NULL, NULL },
    { 4, 1240, 0, 0, 0, 0, 69, NULL, NULL },
    { 3, 1245, 0, 0, 0, 0, 69, NULL, NULL },
    { 2, 1250, 0, 0, 0, 0, 69, NULL, NULL },
    { 1, 1255, 0, 0, 0, 0, 5, NULL, NULL },
    { 2, 1310, 0, 0, 0, 0, 5, NULL, NULL },
    { 1, 1315, 0, 0, 0, 0, 5, NULL, NULL },
    { 2, 1320, 0, 0, 0, 0, 69, NULL, NULL },
    { 3, 1325, 0, 0, 0, 0, 69, NULL, NULL },
    { 4, 1330, 0, 0, 0, 0, 69, NULL, NULL },
    { 19, 5000, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent095Track1[7] = {
    { 222, 399, 70144, 64000, 0, 0, 82, NULL, NULL },
    { 228, 401, 0, 0, 0, 0, 85, NULL, NULL },
    { 222, 439, 0, 0, 0, 0, 85, NULL, NULL },
    { 228, 441, 0, 0, 0, 0, 85, NULL, NULL },
    { 222, 499, 0, 0, 0, 0, 85, NULL, NULL },
    { 228, 501, 0, 0, 0, 0, 85, NULL, NULL },
    { 222, 1400, 0, 0, 0, 0, 32853, NULL, NULL },
};

static const EventCharaKeyframe sEvent095Track2[10] = {
    { 114, 0, 27904, 95488, 0, 0, 66, NULL, NULL },
    { 119, 92, 0, 0, 0, 45, 68, NULL, NULL },
    { 114, 890, 0, 0, 0, 0, 85, NULL, NULL },
    { 114, 891, 74752, 79360, 0, 0, 82, NULL, NULL },
    { 120, 950, 85760, 65024, 0, 114, 83, NULL, NULL },
    { 114, 1191, 0, 0, 0, 0, 69, NULL, NULL },
    { 133, 1231, 0, 0, 0, 0, 64, NULL, CreateExclamationTask },
    { 114, 1340, 0, 0, 0, 0, 69, NULL, NULL },
    { 122, 1350, 0, 0, 0, 0, 69, NULL, NULL },
    { 123, 9999, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent095Track3[11] = {
    { 146, 0, 20480, 91392, 0, 0, 82, NULL, NULL },
    { 151, 21, 0, 0, 0, 45, 84, NULL, NULL },
    { 151, 91, 0, 0, 0, 45, 68, NULL, NULL },
    { 146, 890, 0, 0, 0, 0, 69, NULL, NULL },
    { 146, 891, 52224, 65536, 0, 0, 66, NULL, NULL },
    { 153, 950, 76032, 58880, 0, 146, 67, NULL, NULL },
    { 146, 1191, 0, 0, 0, 0, 69, NULL, NULL },
    { 161, 1231, 0, 0, 0, 0, 64, NULL, CreateExclamationTask },
    { 146, 1345, 0, 0, 0, 0, 69, NULL, NULL },
    { 157, 1355, 0, 0, 0, 0, 69, NULL, NULL },
    { 158, 9999, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent095Track4[2] = {
    { 197, 1305, 83456, 51712, 0, 0, 2, NULL, NULL },
    { 200, 2000, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent095Track5[2] = {
    { 206, 1305, 105984, 62464, 0, 0, 2, NULL, NULL },
    { 209, 2500, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent095Track6[4] = {
    { 213, 881, 99840, 47360, 0, 0, 258, NULL, NULL },
    { 213, 950, 0, 0, 0, 0, 256, NULL, CreateQuestionTask },
    { 213, 1191, 0, 0, 0, 0, 261, NULL, NULL },
    { 213, 1231, 0, 0, 0, 0, 33024, NULL, CreateExclamationTask },
};

static const EventCharaKeyframe sEvent095Track7[1] = {
    { 264, 2500, 76800, 37888, 0, 0, 32770, NULL, NULL },
};

static const EventCharaTrack sEvent095Tracks[8] = {
    { sEvent095Track0, 0 },
    { sEvent095Track1, 7 },
    { sEvent095Track2, 1 },
    { sEvent095Track3, 2 },
    { sEvent095Track4, 4 },
    { sEvent095Track5, 5 },
    { sEvent095Track6, 6 },
    { sEvent095Track7, 11 },
};

const EventSequenceDef gEvent095 = {
    8,
    sEvent095Tracks,
    sEvent095Camera,
    sEvent095Script,
    sEvent095SoundCues,
    NULL,
    1450,
    0,
    1,
    0,
    0,
    0,
    BATTLE_CARD_SOLDIERS,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
