#ifdef VERSION_US
#include "event_164_text.inc"
static const MessageScriptEntry sEvent164Script[11] = {
    { 26, 1, 3, 1, { 0, 0, 0 }, gEvent164Text00, 0, 100 },
    { 27, 2, 1, 1, { 0, 0, 0 }, gEvent164Text01, 0, 130 },
    { 27, 1, 4, 1, { 0, 0, 0 }, gEvent164Text02, 0, 132 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent164Text03, 0, 160 },
    { 27, 1, 1, 1, { 0, 0, 0 }, gEvent164Text04, 0, 235 },
    { 27, 1, 1, 1, { 0, 0, 0 }, gEvent164Text05, 0, 405 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent164Text06, 0, 430 },
    { 27, 1, 1, 1, { 0, 0, 0 }, gEvent164Text07, 0, 460 },
    { 27, 1, 4, 1, { 0, 0, 0 }, gEvent164Text08, 0, 462 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent164Text09, 0, 565 },
    { 26, 2, 3, 1, { 0, 0, 0 }, gEvent164Text10, MSG_SCRIPT_FLAG_END, 700 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent164Script[11] = {
    { 26, 1, 3, 3, { 0, 0, 0 }, gEvent164Text00, 0, 100 },
    { 27, 2, 1, 3, { 0, 0, 0 }, gEvent164Text01, 0, 130 },
    { 27, 1, 4, 3, { 0, 0, 0 }, gEvent164Text02, 0, 132 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent164Text03, 0, 160 },
    { 27, 1, 1, 3, { 0, 0, 0 }, gEvent164Text04, 0, 235 },
    { 27, 1, 1, 3, { 0, 0, 0 }, gEvent164Text05, 0, 405 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent038Text04, 0, 430 },
    { 27, 1, 1, 3, { 0, 0, 0 }, gEvent164Text07, 0, 460 },
    { 27, 1, 4, 3, { 0, 0, 0 }, gEvent164Text08, 0, 462 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent124Text23, 0, 565 },
    { 26, 2, 3, 3, { 0, 0, 0 }, gEvent164Text10, MSG_SCRIPT_FLAG_END, 700 },
};

#include "event_164_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent164Script[11] = {
    { 26, 1, 3, 1, { 0, 0, 0 }, &gEvent164Text00, 0, 100 },
    { 27, 2, 1, 1, { 0, 0, 0 }, &gEvent164Text01, 0, 130 },
    { 27, 1, 4, 1, { 0, 0, 0 }, &gEvent164Text02, 0, 132 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent164Text03, 0, 160 },
    { 27, 1, 1, 1, { 0, 0, 0 }, &gEvent164Text04, 0, 235 },
    { 27, 1, 1, 1, { 0, 0, 0 }, &gEvent164Text05, 0, 405 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent164Text06, 0, 430 },
    { 27, 1, 1, 1, { 0, 0, 0 }, &gEvent164Text07, 0, 460 },
    { 27, 1, 4, 1, { 0, 0, 0 }, &gEvent164Text08, 0, 462 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent164Text09, 0, 565 },
    { 26, 2, 3, 1, { 0, 0, 0 }, &gEvent164Text10, MSG_SCRIPT_FLAG_END, 700 },
};
#endif

static const EvSoundCue sEvent164SoundCues[3] = {
    { SONG_BGM_EVENT_UNREST, 0, 0, 0 },
    { SONG_SND_376, 165, 0, 0 },
    { SONG_SND_378, 194, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent164Camera[8] = {
    { -65371, 182784, 66560, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65356, 191232, 60160, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 20, { 0, 0 }, NULL },
    { -65346, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -65341, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65331, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -65286, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64946, 154112, 80896, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 100, { 0, 0 }, NULL },
    { -62536, 166656, 75520, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent164Track0[14] = {
    { 561, 165, { 0, 0 }, 171264, 76288, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 548, 191, { 0, 0 }, 188160, 69632, 0, 515, { 0, 0 }, 67, NULL, NULL },
    { 515, 194, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 550, 230, { 0, 0 }, 146176, 89856, 0, 515, { 0, 0 }, 67, NULL, NULL },
    { 555, 385, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 556, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 425, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 538, 435, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 538, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 590, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 522, 645, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 515, 649, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 515, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent164Track1[8] = {
    { 705, 191, { 0, 0 }, 194048, 66304, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 695, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 711, 385, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 695, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 696, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 696, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 710, 1000, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 695, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent164Track2[3] = {
    { 926, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 926, 250, { 0, 0 }, 194048, 60160, 0, 0, { 0, 0 }, 16658, NULL, NULL },
    { 926, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaTrack sEvent164Tracks[3] = {
    { sEvent164Track0, 44, { 0, 0, 0 } },
    { sEvent164Track1, 65, { 0, 0, 0 } },
    { sEvent164Track2, 92, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent164 = {
    3,
    { 0, 0, 0 },
    sEvent164Tracks,
    sEvent164Camera,
    sEvent164Script,
    sEvent164SoundCues,
    NULL,
    760,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    165,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent164 = {
    3,
    { 0, 0, 0 },
    sEvent164Tracks,
    sEvent164Camera,
    sEvent164Script,
    sEvent164SoundCues,
    NULL,
    760,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    163,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif
