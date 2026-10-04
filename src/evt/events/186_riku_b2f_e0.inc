#ifdef VERSION_US
#include "event_186_text.inc"
#endif

static const MessageScriptEntry sEvent186Script[21] = {
    { 26, 3, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent186Text00), 0, 370 },
    { 26, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent186Text01), 0, 372 },
    { 26, 3, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent186Text02), 0, 450 },
    { 56, 0, 0, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent186Text03), 0, 480 },
    { 56, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent186Text04), 0, 690 },
    { 56, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent186Text05), 0, 980 },
    { 26, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent186Text06), 0, 1010 },
    { 26, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent186Text07), 0, 1120 },
    { 26, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent186Text08), 0, 1122 },
    { 26, 1, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent186Text09), 0, 1240 },
    { 26, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent186Text10), 0, 1242 },
    { 56, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent186Text11), 0, 1430 },
    { 52, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent186Text12), 0, 1600 },
    { 26, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent186Text13), 0, 1630 },
    { 52, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent186Text14), 0, 1660 },
    { 26, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent186Text15), 0, 1690 },
    { 52, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent186Text16), 0, 1720 },
    { 52, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent186Text17), 0, 1950 },
    { 26, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent186Text18), 0, 1980 },
    { 52, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent186Text19), 0, 2010 },
    { 26, 3, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent186Text20), MSG_SCRIPT_FLAG_END, 2085 },
};

#ifdef VERSION_JP
#include "event_186_text.inc"
#endif

static const EvSoundCue sEvent186SoundCues[9] = {
    { 65535, 0, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 482, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_SND_379, 630, 0, 0 },
    { SONG_SND_359, 710, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 1012, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_EV_WHITEOUT, 1460, 0, 0 },
    { SONG_BGM_TWILIGHTTOWN, 1510, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_SND_379, 2040, 0, 0 },
    { SONG_BGM_TWILIGHTTOWN, 2135, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent186Camera[7] = {
    { -65536, 61184, 107520, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, NULL },
    { -64956, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 80, { 0, 0 }, NULL },
    { -64076, 66816, 103936, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -64036, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 40, { 0, 0 }, NULL },
    { -64006, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -63536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 40, { 0, 0 }, NULL },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent186Track0[25] = {
    { 515, 1, { 0, 0 }, 26624, 134144, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 518, 160, { 0, 0 }, 60160, 116736, 0, 515, { 0, 0 }, 67, NULL, NULL },
    { 515, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 515, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 290, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 514, 330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 514, 410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 514, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 540, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 514, 560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 560, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 561, 930, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 561, 950, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 562, 960, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 1140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 530, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 1770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 1900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 515, 2080, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 538, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent186Track1[10] = {
    { 688, 630, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 688, 685, { 0, 0 }, 74240, 110336, 0, 0, { 0, 0 }, 16386, EventCharaFadeIn, NULL },
    { 694, 692, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 688, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 688, 1070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 688, 1270, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 688, 1400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 688, 1450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 688, 1501, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaBlendUp, NULL },
    { 688, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent186Track2[4] = {
    { 907, 1501, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 907, 2040, { 0, 0 }, 74240, 110336, 0, 0, { 0, 0 }, 16386, NULL, NULL },
    { 907, 2070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaFadeOut, NULL },
    { 907, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 73730, NULL, NULL },
};

static const EventCharaTrack sEvent186Tracks[3] = {
    { sEvent186Track0, 44, { 0, 0, 0 } },
    { sEvent186Track1, 64, { 0, 0, 0 } },
    { sEvent186Track2, 84, { 0, 0, 0 } },
};

const EventSequenceDef gEvent186 = {
    3,
    { 0, 0, 0 },
    sEvent186Tracks,
    sEvent186Camera,
    sEvent186Script,
    sEvent186SoundCues,
    NULL,
    2140,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    65535,
    0,
    { 0, 0 },
    65535,
    1,
    255,
    255,
};
