#ifdef VERSION_US
#include "event_034_text.inc"
#endif

static const MessageScriptEntry sEvent034Script[10] = {
    { 27, 2, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent034Text00), 0, 100 },
    { 27, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent034Text01), 0, 160 },
    { 27, 1, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent034Text02), 0, 162 },
    { 0, 2, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent034Text03), 0, 250 },
    { 0, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent034Text04), 0, 310 },
    { 27, 2, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent034Text05), 0, 340 },
    { 27, 2, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent034Text06), 0, 420 },
    { 0, 3, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent034Text07), 0, 450 },
    { 27, 2, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent034Text08), 0, 480 },
    { 0, 2, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent034Text09), MSG_SCRIPT_FLAG_END, 830 },
};

#ifdef VERSION_JP
#include "event_034_text.inc"
#endif

static const EventCameraKeyframe sEvent034Camera[2] = {
    { -64966, 193792, 61696, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -62536, 188416, 64768, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 80, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent034SoundCues[1] = {
    { SONG_BGM_EVENT_UNREST, 0, EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent034Track0[9] = {
    { 21, 190, { 0, 0 }, 190464, 68352, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 22, 205, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 270, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 9, 290, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 4, 445, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 30, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 4, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent034Track1[3] = {
    { 123, 195, { 0, 0 }, 186624, 75776, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 124, 210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent034Track2[3] = {
    { 158, 198, { 0, 0 }, 178432, 70144, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 159, 213, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent034Track3[7] = {
    { 699, 120, { 0, 0 }, 208128, 60160, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 700, 135, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 695, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 696, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 696, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 710, 600, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, NULL, NULL },
    { 696, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent034Tracks[4] = {
    { sEvent034Track0, 0, { 0, 0, 0 } },
    { sEvent034Track1, 1, { 0, 0, 0 } },
    { sEvent034Track2, 2, { 0, 0, 0 } },
    { sEvent034Track3, 65, { 0, 0, 0 } },
};

const EventSequenceDef gEvent034 = {
    4,
    { 0, 0, 0 },
    sEvent034Tracks,
    sEvent034Camera,
    sEvent034Script,
    sEvent034SoundCues,
    NULL,
    890,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    35,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
