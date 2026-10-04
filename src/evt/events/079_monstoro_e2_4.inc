#ifdef VERSION_US
static const MessageScriptEntry sEvent079Script[6] = {
    { 10, 8, 3, 1, { 0, 0, 0 }, gEvent078Text00, 0, 250 },
    { 0, 2, 2, 1, { 0, 0, 0 }, gEvent078Text01, 0, 320 },
    { 10, 11, 1, 1, { 0, 0, 0 }, gEvent078Text02, 0, 340 },
    { 0, 2, 2, 1, { 0, 0, 0 }, gEvent078Text03, 0, 420 },
    { 10, 2, 1, 1, { 0, 0, 0 }, gEvent078Text04, 0, 630 },
    { 10, 14, 4, 1, { 0, 0, 0 }, gEvent078Text05, MSG_SCRIPT_FLAG_END, 635 },
};
#endif

#ifdef VERSION_JP
static const MessageScriptEntry sEvent079Script[6] = {
    { 10, 8, 3, 3, { 0, 0, 0 }, gEvent078Text00, 0, 250 },
    { 0, 2, 2, 3, { 0, 0, 0 }, gEvent078Text01, 0, 320 },
    { 10, 11, 1, 3, { 0, 0, 0 }, gEvent078Text02, 0, 340 },
    { 0, 2, 2, 3, { 0, 0, 0 }, gEvent079Text03, 0, 420 },
    { 10, 2, 1, 3, { 0, 0, 0 }, gEvent078Text04, 0, 630 },
    { 10, 14, 4, 3, { 0, 0, 0 }, gEvent078Text05, MSG_SCRIPT_FLAG_END, 635 },
};

#include "event_079_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent079Script[6] = {
    { 10, 8, 3, 1, { 0, 0, 0 }, &gEvent078Text00, 0, 250 },
    { 0, 2, 2, 1, { 0, 0, 0 }, &gEvent078Text01, 0, 320 },
    { 10, 11, 1, 1, { 0, 0, 0 }, &gEvent078Text02, 0, 340 },
    { 0, 2, 2, 1, { 0, 0, 0 }, &gEvent078Text03, 0, 420 },
    { 10, 2, 1, 1, { 0, 0, 0 }, &gEvent078Text04, 0, 630 },
    { 10, 14, 4, 1, { 0, 0, 0 }, &gEvent078Text05, MSG_SCRIPT_FLAG_END, 635 },
};
#endif

static const EventCameraKeyframe sEvent079Camera[2] = {
    { -65535, 34304, 30720, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -63536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent079SoundCues[1] = {
    { 65535, 0, EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent079Track0[21] = {
    { 241, 50, { 0, 0 }, 37376, 36864, 0, 0, { 0, 0 }, 322, NULL, NULL },
    { 241, 80, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 238, 110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 244, 140, { 0, 0 }, 31232, 38144, 0, 236, { 0, 0 }, 259, NULL, NULL },
    { 238, 190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 238, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 241, 210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 250, 220, { 0, 0 }, 34304, 37632, 0, 239, { 0, 0 }, 323, NULL, NULL },
    { 241, 335, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 259, 342, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 241, 352, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 238, 362, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 238, 470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 238, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 256, NULL, CreateBalloonTask },
    { 238, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 247, 710, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 260, NULL, NULL },
    { 253, 770, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 324, NULL, NULL },
    { 247, 820, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 324, NULL, NULL },
    { 253, 890, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 260, NULL, NULL },
    { 247, 920, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 324, NULL, NULL },
    { 247, 2000, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 33028, NULL, NULL },
};

static const EventCharaTrack sEvent079Tracks[1] = {
    { sEvent079Track0, 9, { 0, 0, 0 } },
};

const EventSequenceDef gEvent079 = {
    1,
    { 0, 0, 0 },
    sEvent079Tracks,
    sEvent079Camera,
    sEvent079Script,
    sEvent079SoundCues,
    NULL,
    920,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    80,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
