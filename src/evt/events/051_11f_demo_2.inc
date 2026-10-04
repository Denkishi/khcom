#ifdef VERSION_US
#include "event_051_text.inc"
#endif

static const MessageScriptEntry sEvent051Script[12] = {
    { 20, 1, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent051Text00), 0, 280 },
    { 20, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent051Text01), 0, 430 },
    { 60, 4, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent051Text02), 0, 590 },
    { 20, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent051Text03), 0, 620 },
    { 20, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent051Text04), 0, 660 },
    { 60, 2, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent051Text05), 0, 680 },
    { 20, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent051Text06), 0, 700 },
    { 20, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent051Text07), 0, 870 },
    { 20, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent051Text08), 0, 1120 },
    { 20, 2, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent051Text09), 0, 1150 },
    { 20, 2, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent051Text10), 0, 1152 },
    { 20, 2, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent051Text11), MSG_SCRIPT_FLAG_END, 1154 },
};

#ifdef VERSION_JP
#include "event_051_text.inc"
#endif

static const EventCameraKeyframe sEvent051Camera[2] = {
    { -65366, 98304, 63744, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -60536, 89088, 65536, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent051SoundCues[2] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_BGM_EVENT_XIII, 950, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent051Track0[10] = {
    { 486, 111, { 0, 0 }, 57856, 83456, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 502, 190, { 0, 0 }, 79616, 74240, 0, 486, { 0, 0 }, 67, NULL, NULL },
    { 486, 630, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 485, 640, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 485, 705, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 509, 980, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 509, 1110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 485, 1130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 485, 1140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 495, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent051Track1[12] = {
    { 445, 290, { 0, 0 }, 100096, 70144, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 445, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 445, 440, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 447, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 441, 580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 444, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 447, 710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 441, 840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 446, 862, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 422, 890, { 0, 0 }, 98816, 70144, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 448, 1000, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 36, NULL, NULL },
    { 422, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98309, NULL, NULL },
};

static const EventCharaKeyframe sEvent051Track2[1] = {
    { 919, 1, { 0, 0 }, 100608, 69888, 0, 0, { 0, 0 }, 33090, NULL, NULL },
};

static const EventCharaTrack sEvent051Tracks[3] = {
    { sEvent051Track0, 43, { 0, 0, 0 } },
    { sEvent051Track1, 35, { 0, 0, 0 } },
    { sEvent051Track2, 86, { 0, 0, 0 } },
};

const EventSequenceDef gEvent051 = {
    3,
    { 0, 0, 0 },
    sEvent051Tracks,
    sEvent051Camera,
    sEvent051Script,
    sEvent051SoundCues,
    NULL,
    1210,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    52,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
