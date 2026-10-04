#ifdef VERSION_US
#include "event_178_text.inc"
static const MessageScriptEntry sEvent178Script[14] = {
    { 26, 3, 1, 1, { 0, 0, 0 }, gEvent178Text00, 0, 250 },
    { 26, 0, 1, 1, { 0, 0, 0 }, gEvent178Text01, 0, 600 },
    { 26, 3, 1, 1, { 0, 0, 0 }, gEvent178Text02, 0, 690 },
    { 26, 2, 1, 1, { 0, 0, 0 }, gEvent178Text03, 0, 880 },
    { 55, 5, 0, 1, { 0, 0, 0 }, gEvent178Text04, 0, 910 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent178Text05, 0, 1100 },
    { 55, 0, 1, 1, { 0, 0, 0 }, gEvent178Text06, 0, 1130 },
    { 55, 0, 4, 1, { 0, 0, 0 }, gEvent178Text07, 0, 1132 },
    { 55, 5, 4, 1, { 0, 0, 0 }, gEvent178Text08, 0, 1134 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent178Text09, 0, 1160 },
    { 26, 2, 4, 1, { 0, 0, 0 }, gEvent178Text10, 0, 1162 },
    { 26, 5, 3, 1, { 0, 0, 0 }, gEvent178Text11, 0, 1330 },
    { 55, 0, 1, 1, { 0, 0, 0 }, gEvent178Text12, 0, 1360 },
    { 55, 2, 1, 1, { 0, 0, 0 }, gEvent178Text13, MSG_SCRIPT_FLAG_END, 1460 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent178Script[14] = {
    { 26, 3, 1, 3, { 0, 0, 0 }, gEvent178Text00, 0, 250 },
    { 26, 0, 1, 3, { 0, 0, 0 }, gEvent178Text01, 0, 600 },
    { 26, 3, 1, 3, { 0, 0, 0 }, gEvent018Text11, 0, 690 },
    { 26, 2, 1, 3, { 0, 0, 0 }, gEvent178Text03, 0, 880 },
    { 55, 5, 0, 3, { 0, 0, 0 }, gEvent178Text04, 0, 910 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent151Text09, 0, 1100 },
    { 55, 0, 1, 3, { 0, 0, 0 }, gEvent178Text06, 0, 1130 },
    { 55, 0, 4, 3, { 0, 0, 0 }, gEvent178Text07, 0, 1132 },
    { 55, 5, 4, 3, { 0, 0, 0 }, gEvent178Text08, 0, 1134 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent178Text09, 0, 1160 },
    { 26, 2, 4, 3, { 0, 0, 0 }, gEvent178Text10, 0, 1162 },
    { 26, 5, 3, 3, { 0, 0, 0 }, gEvent178Text11, 0, 1330 },
    { 55, 0, 1, 3, { 0, 0, 0 }, gEvent178Text12, 0, 1360 },
    { 55, 2, 1, 3, { 0, 0, 0 }, gEvent178Text13, MSG_SCRIPT_FLAG_END, 1460 },
};

#include "event_178_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent178Script[14] = {
    { 26, 3, 1, 1, { 0, 0, 0 }, &gEvent178Text00, 0, 250 },
    { 26, 0, 1, 1, { 0, 0, 0 }, &gEvent178Text01, 0, 600 },
    { 26, 3, 1, 1, { 0, 0, 0 }, &gEvent178Text02, 0, 690 },
    { 26, 2, 1, 1, { 0, 0, 0 }, &gEvent178Text03, 0, 880 },
    { 55, 5, 0, 1, { 0, 0, 0 }, &gEvent178Text04, 0, 910 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent178Text05, 0, 1100 },
    { 55, 0, 1, 1, { 0, 0, 0 }, &gEvent178Text06, 0, 1130 },
    { 55, 0, 4, 1, { 0, 0, 0 }, &gEvent178Text07, 0, 1132 },
    { 55, 5, 4, 1, { 0, 0, 0 }, &gEvent178Text08, 0, 1134 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent178Text09, 0, 1160 },
    { 26, 2, 4, 1, { 0, 0, 0 }, &gEvent178Text10, 0, 1162 },
    { 26, 5, 3, 1, { 0, 0, 0 }, &gEvent178Text11, 0, 1330 },
    { 55, 0, 1, 1, { 0, 0, 0 }, &gEvent178Text12, 0, 1360 },
    { 55, 2, 1, 1, { 0, 0, 0 }, &gEvent178Text13, MSG_SCRIPT_FLAG_END, 1460 },
};
#endif

static const EvSoundCue sEvent178SoundCues[4] = {
    { 65535, 0, 0, 0 },
    { SONG_SND_370, 630, 0, 0 },
    { SONG_EV_WARPOUT, 940, 0, 0 },
    { SONG_BGM_EVENT_XIII, 950, EV_SOUND_FLAG_FADE_IN | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent178Camera[6] = {
    { -65366, 73728, 61440, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65176, 36608, 80128, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
    { -64516, 41984, 78080, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -63991, 53760, 71680, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -63936, 31488, 153856, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 1, { 0, 0 }, NULL },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EventBgEffectEntry sEvent178BgEffects[5] = {
    { 1490, 0, 0, 0, 0 },
    { 1540, 0, 60, 0, 0x14 },
    { 3310, 0, 0, 0, 0 },
    { 4000, 0, 0, 0, 0x2 },
    { 5000, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent178Track0[23] = {
    { 514, 1, { 0, 0 }, 104704, 60416, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 520, 80, { 0, 0 }, 73984, 71424, 0, 514, { 0, 0 }, 3, NULL, NULL },
    { 514, 83, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 514, 100, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 526, 110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 526, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 526, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 516, 360, { 0, 0 }, 47104, 81920, 0, 514, { 0, 0 }, 3, NULL, NULL },
    { 514, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 514, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 526, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 528, 990, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 1030, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 1155, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 538, 1180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 1200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 540, 1545, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 540, 2000, { 0, 0 }, 24832, 164096, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent178Track1[6] = {
    { 889, 940, { 0, 0 }, 120320, 11776, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 889, 1455, { 0, 0 }, 62464, 75264, 0, 0, { 0, 0 }, 2, EventCharaFadeIn, NULL },
    { 899, 1520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 898, 1545, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 889, 2000, { 0, 0 }, 40192, 157440, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 889, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent178Track2[4] = {
    { 420, 630, { 0, 0 }, 36608, 86272, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 420, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaFadeOut, NULL },
    { 420, 1000, { 0, 0 }, 120320, 11776, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 420, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98373, NULL, NULL },
};

static const EventCharaTrack sEvent178Tracks[3] = {
    { sEvent178Track0, 44, { 0, 0, 0 } },
    { sEvent178Track1, 83, { 0, 0, 0 } },
    { sEvent178Track2, 34, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent178 = {
    3,
    { 0, 0, 0 },
    sEvent178Tracks,
    sEvent178Camera,
    sEvent178Script,
    sEvent178SoundCues,
    sEvent178BgEffects,
    1700,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    179,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent178 = {
    3,
    { 0, 0, 0 },
    sEvent178Tracks,
    sEvent178Camera,
    sEvent178Script,
    sEvent178SoundCues,
    sEvent178BgEffects,
    1700,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    177,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif
