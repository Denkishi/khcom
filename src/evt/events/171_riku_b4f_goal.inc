#ifdef VERSION_US
#include "event_171_text.inc"
#endif

static const MessageScriptEntry sEvent171Script[11] = {
    { 26, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent171Text00), 0, 430 },
    { 57, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent171Text01), 0, 460 },
    { 57, 0, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent171Text02), 0, 462 },
    { 26, 2, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent171Text03), 0, 490 },
    { 57, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent171Text04), 0, 520 },
    { 57, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent171Text05), 0, 730 },
    { 26, 2, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent171Text06), 0, 780 },
    { 57, 2, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent171Text07), 0, 810 },
    { 26, 2, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent171Text08), 0, 970 },
    { 57, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent171Text09), 0, 1020 },
    { 57, 2, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent171Text10), MSG_SCRIPT_FLAG_END, 1022 },
};

#ifdef VERSION_JP
#include "event_171_text.inc"
#endif

static const EvSoundCue sEvent171SoundCues[6] = {
    { 65535, 0, 0, 0 },
    { SONG_BGM_EVENT_XIII, 250, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT_XIII, 805, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT2, 815, 0, 0 },
    { SONG_SND_380, 835, 0, 0 },
    { SONG_SND_359, 1040, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent171Camera[7] = {
    { -65336, 158464, 76544, 0, 255, 0, 0, NULL },
    { -64716, 192000, 60416, 0, 255, CAMERA_MODE_APPROACH, 70, NULL },
    { -64681, 199680, 54272, 0, 255, CAMERA_MODE_APPROACH, 15, NULL },
    { -64586, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_SHAKE_SMALL | CAMERA_MODE_KEEP, 0, NULL },
    { -64566, 0, 0, 0, 255, CAMERA_MODE_KEEP, 0, NULL },
    { -63536, 192000, 60416, 0, 255, CAMERA_MODE_APPROACH, 30, NULL },
    { -60536, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, NULL },
};

static const EventCharaKeyframe sEvent171Track0[14] = {
    { 518, 1, 131584, 97536, 0, 0, 66, NULL, NULL },
    { 518, 110, 0, 0, 0, 45, 68, NULL, NULL },
    { 515, 120, 0, 0, 0, 0, 69, NULL, NULL },
    { 532, 130, 0, 0, 0, 0, 69, NULL, NULL },
    { 532, 180, 0, 0, 0, 0, 64, NULL, CreateExclamationTask },
    { 532, 300, 0, 0, 0, 0, 69, NULL, NULL },
    { 518, 410, 0, 0, 0, 45, 68, NULL, NULL },
    { 515, 550, 0, 0, 0, 0, 69, NULL, NULL },
    { 515, 680, 0, 0, 0, 0, 64, NULL, CreateBalloonTask },
    { 515, 860, 0, 0, 0, 0, 69, NULL, NULL },
    { 555, 972, 0, 0, 0, 0, 69, NULL, NULL },
    { 556, 986, 0, 0, 0, 0, 69, NULL, NULL },
    { 515, 1040, 0, 0, 0, 0, 69, NULL, NULL },
    { 560, 3000, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent171Track1[3] = {
    { 887, 820, 199424, 63488, 0, 0, 2, NULL, NULL },
    { 888, 990, 0, 0, 0, 0, 5, NULL, NULL },
    { 883, 5000, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent171Track2[3] = {
    { 926, 835, 0, 0, 0, 0, 8194, NULL, NULL },
    { 926, 880, 199680, 54272, 0, 0, 16658, NULL, NULL },
    { 926, 5000, 0, 0, 0, 0, 98306, NULL, NULL },
};

static const EventCharaTrack sEvent171Tracks[3] = {
    { sEvent171Track0, 44 },
    { sEvent171Track1, 82 },
    { sEvent171Track2, 92 },
};

const EventSequenceDef gEvent171 = {
    3,
    sEvent171Tracks,
    sEvent171Camera,
    sEvent171Script,
    sEvent171SoundCues,
    NULL,
    1090,
    0,
    1,
    0,
    0,
    0,
    BATTLE_LEXAEUS,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
