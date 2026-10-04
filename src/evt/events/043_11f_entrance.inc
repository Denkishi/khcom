#ifdef VERSION_US
#include "event_043_text.inc"
#endif

static const MessageScriptEntry sEvent043Script[2] = {
    { 6, 1, 0, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent043Text00), 0, 210 },
    { 0, 2, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent043Text01), MSG_SCRIPT_FLAG_END, 250 },
};

#ifdef VERSION_JP
#include "event_043_text.inc"
#endif

static const EventCameraKeyframe sEvent043Camera[1] = {
    { -65485, 165120, 75776, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent043SoundCues[1] = {
    { SONG_BGM_T13THFLOOR, 0, EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent043Track0[7] = {
    { 4, 1, { 0, 0 }, 136704, 95488, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 9, 110, { 0, 0 }, 163584, 82176, 0, 4, { 0, 0 }, 67, NULL, NULL },
    { 4, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 74, 252, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 76, 260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 9, 999, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 32836, NULL, NULL },
};

static const EventCharaKeyframe sEvent043Track1[4] = {
    { 114, 1, { 0, 0 }, 137984, 103680, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 119, 110, { 0, 0 }, 160512, 90624, 0, 114, { 0, 0 }, 67, NULL, NULL },
    { 114, 315, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 119, 999, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 32836, NULL, NULL },
};

static const EventCharaKeyframe sEvent043Track2[4] = {
    { 146, 1, { 0, 0 }, 125440, 95744, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 151, 110, { 0, 0 }, 150784, 80384, 0, 146, { 0, 0 }, 67, NULL, NULL },
    { 146, 320, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 151, 999, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 32836, NULL, NULL },
};

static const EventCharaKeyframe sEvent043Track3[8] = {
    { 231, 120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 231, 121, { 0, 0 }, 163584, 82176, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 234, 150, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, EventCharaHop, NULL },
    { 231, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 229, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 229, 270, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 233, 300, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, EventCharaHop, NULL },
    { 229, 310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent043Track4[3] = {
    { 591, 206, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8258, NULL, NULL },
    { 601, 252, { 0, 0 }, 163584, 82176, 0, 0, { 0, 0 }, 16722, NULL, NULL },
    { 591, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98370, NULL, NULL },
};

static const EventCharaTrack sEvent043Tracks[5] = {
    { sEvent043Track0, 0, { 0, 0, 0 } },
    { sEvent043Track1, 1, { 0, 0, 0 } },
    { sEvent043Track2, 2, { 0, 0, 0 } },
    { sEvent043Track3, 8, { 0, 0, 0 } },
    { sEvent043Track4, 50, { 0, 0, 0 } },
};

const EventSequenceDef gEvent043 = {
    5,
    { 0, 0, 0 },
    sEvent043Tracks,
    sEvent043Camera,
    sEvent043Script,
    sEvent043SoundCues,
    NULL,
    400,
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
