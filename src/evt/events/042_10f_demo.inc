#ifdef VERSION_US
#include "event_042_text.inc"
#endif

static const MessageScriptEntry sEvent042Script[7] = {
    { 54, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent042Text00), 0, 100 },
    { 54, 1, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent042Text01), 0, 130 },
    { 20, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent042Text02), 0, 330 },
    { 58, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent042Text03), 0, 360 },
    { 20, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent042Text04), 0, 430 },
    { 58, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent042Text05), 0, 510 },
    { 20, 1, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent042Text06), MSG_SCRIPT_FLAG_END, 540 },
};

#ifdef VERSION_JP
#include "event_042_text.inc"
#endif

static const EventCameraKeyframe sEvent042Camera[1] = {
    { -65485, 68864, 59904, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent042SoundCues[2] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_BGM_EVENT_XIII, 625, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent042Track0[8] = {
    { 509, 150, { 0, 0 }, 79360, 62976, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 509, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 509, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 509, 370, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 485, 390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 485, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 494, 700, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 485, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent042Track1[3] = {
    { 876, 120, { 0, 0 }, 69632, 74752, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 876, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 856, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent042Track2[3] = {
    { 841, 505, { 0, 0 }, 56320, 61952, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 845, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 841, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent042Tracks[3] = {
    { sEvent042Track0, 43, { 0, 0, 0 } },
    { sEvent042Track1, 81, { 0, 0, 0 } },
    { sEvent042Track2, 79, { 0, 0, 0 } },
};

const EventSequenceDef gEvent042 = {
    3,
    { 0, 0, 0 },
    sEvent042Tracks,
    sEvent042Camera,
    sEvent042Script,
    sEvent042SoundCues,
    NULL,
    630,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    43,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
