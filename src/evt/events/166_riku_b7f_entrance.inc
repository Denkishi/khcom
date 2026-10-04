#ifdef VERSION_US
#include "event_166_text.inc"
#endif

static const MessageScriptEntry sEvent166Script[14] = {
    { 26, 2, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent166Text00), 0, 115 },
    { 56, 1, 0, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent166Text01), 0, 330 },
    { 26, 2, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent166Text02), 0, 500 },
    { 56, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent166Text03), 0, 530 },
    { 56, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent166Text04), 0, 532 },
    { 56, 1, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent166Text05), 0, 534 },
    { 26, 2, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent166Text06), 0, 565 },
    { 56, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent166Text07), 0, 595 },
    { 56, 1, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent166Text08), 0, 597 },
    { 26, 1, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent166Text09), 0, 770 },
    { 26, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent166Text10), 0, 772 },
    { 26, 2, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent166Text11), 0, 785 },
    { 56, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent166Text12), 0, 950 },
    { 56, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent166Text13), MSG_SCRIPT_FLAG_END, 1100 },
};

#ifdef VERSION_JP
#include "event_166_text.inc"
#endif

static const EvSoundCue sEvent166SoundCues[5] = {
    { 65535, 0, 0, 0 },
    { SONG_SND_379, 410, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 411, 0, 0 },
    { SONG_EV_CARDTHR, 989, 0, 0 },
    { SONG_SND_379, 1150, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent166Camera[2] = {
    { -65146, 175872, 68352, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -62536, 188416, 61696, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent166Track0[24] = {
    { 515, 1, { 0, 0 }, 141568, 92672, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 522, 100, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 515, 103, { 0, 0 }, 175872, 75264, 0, 515, { 0, 0 }, 67, NULL, NULL },
    { 515, 110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 538, 120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 515, 210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 514, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 514, 340, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 514, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 514, 460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 538, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 610, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 530, 620, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 530, 750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 530, 773, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 538, 788, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 995, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 559, 1180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 4000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent166Track1[10] = {
    { 688, 410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 688, 450, { 0, 0 }, 201728, 63232, 0, 0, { 0, 0 }, 2, EventCharaFadeIn, NULL },
    { 688, 795, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 688, 925, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 688, 970, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 692, 1050, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 688, 1150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 688, 1200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaFadeOut, NULL },
    { 688, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 688, 4000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent166Track2[7] = {
    { 591, 988, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8258, NULL, NULL },
    { 591, 989, { 0, 0 }, 194816, 58624, 0, 0, { 0, 0 }, 16706, NULL, NULL },
    { 591, 1000, { 0, 0 }, 181504, 65536, 0, 591, { 0, 0 }, 323, NULL, NULL },
    { 591, 1008, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 604, 1180, { 0, 0 }, 175872, 75264, 0, 0, { 0, 0 }, 338, NULL, NULL },
    { 591, 1200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 591, 4000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98373, NULL, NULL },
};

static const EventCharaTrack sEvent166Tracks[3] = {
    { sEvent166Track0, 44, { 0, 0, 0 } },
    { sEvent166Track1, 64, { 0, 0, 0 } },
    { sEvent166Track2, 50, { 0, 0, 0 } },
};

const EventSequenceDef gEvent166 = {
    3,
    { 0, 0, 0 },
    sEvent166Tracks,
    sEvent166Camera,
    sEvent166Script,
    sEvent166SoundCues,
    NULL,
    1240,
    1,
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
    0,
    255,
    255,
};
