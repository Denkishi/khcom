#ifdef VERSION_US
#include "event_086_text.inc"
#endif

static const MessageScriptEntry sEvent086Script[14] = {
    { 0, 6, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent086Text00), 0, 400 },
    { 2, 0, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent086Text01), 0, 460 },
    { 6, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent086Text02), 0, 650 },
    { 0, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent086Text03), 0, 680 },
    { 6, 3, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent086Text04), 0, 690 },
    { 6, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent086Text05), 0, 692 },
    { 0, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent086Text06), 0, 700 },
    { 6, 0, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent086Text07), 0, 710 },
    { 6, 3, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent086Text08), 0, 712 },
    { 6, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent086Text09), 0, 714 },
    { 0, 4, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent086Text10), 0, 730 },
    { 0, 4, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent086Text11), 0, 732 },
    { 0, 1, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent086Text12), 0, 734 },
    { 6, 3, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent086Text13), MSG_SCRIPT_FLAG_END, 750 },
};

#ifdef VERSION_JP
#include "event_086_text.inc"
#endif

static const EventCameraKeyframe sEvent086Camera[9] = {
    { -65536, 78592, 68352, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, NULL },
    { -65286, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 150, { 0, 0 }, NULL },
    { -65281, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65216, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_BLACK | CAMERA_MODE_KEEP, 60, { 0, 0 }, NULL },
    { -65166, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_BLACK | CAMERA_MODE_KEEP, 50, { 0, 0 }, NULL },
    { -65075, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64956, 37888, 43264, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 60, { 0, 0 }, NULL },
    { -64876, 78592, 68352, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 60, { 0, 0 }, NULL },
    { -64537, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent086SoundCues[2] = {
    { SONG_BGM_EVENT4, 692, 0, 0 },
    { SONG_BGM_EVENT4, 795, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent086Track0[6] = {
    { 69, 0, { 0, 0 }, 82944, 75776, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 69, 316, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateDownTask },
    { 2, 470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 679, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 36, 699, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent086Track1[11] = {
    { 146, 0, { 0, 0 }, 78848, 82432, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 169, 316, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateDownTask },
    { 146, 401, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 415, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 144, 425, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 440, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 459, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 165, 470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 142, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 691, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 142, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent086Track2[4] = {
    { 114, 0, { 0, 0 }, 91648, 82432, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 137, 316, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateDownTask },
    { 114, 691, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 113, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent086Track3[6] = {
    { 231, 580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 231, 621, { 0, 0 }, 81920, 76288, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 234, 649, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, EventCharaHop, NULL },
    { 231, 681, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 229, 686, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 229, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent086Tracks[4] = {
    { sEvent086Track0, 0, { 0, 0, 0 } },
    { sEvent086Track1, 2, { 0, 0, 0 } },
    { sEvent086Track2, 1, { 0, 0, 0 } },
    { sEvent086Track3, 8, { 0, 0, 0 } },
};

const EventSequenceDef gEvent086 = {
    4,
    { 0, 0, 0 },
    sEvent086Tracks,
    sEvent086Camera,
    sEvent086Script,
    sEvent086SoundCues,
    NULL,
    800,
    0,
    0,
    0,
    0,
    1,
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
