#ifdef VERSION_US
#include "event_160_text.inc"
#endif

static const MessageScriptEntry sEvent160Script[13] = {
    { 38, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent160Text00), 0, 250 },
    { 26, 2, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent160Text01), 0, 280 },
    { 38, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent160Text02), 0, 460 },
    { 38, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent160Text03), 0, 462 },
    { 26, 2, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent160Text04), 0, 490 },
    { 38, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent160Text05), 0, 520 },
    { 38, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent160Text06), 0, 660 },
    { 38, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent160Text07), 0, 662 },
    { 26, 5, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent160Text08), 0, 710 },
    { 26, 2, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent160Text09), 0, 790 },
    { 26, 2, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent160Text10), 0, 792 },
    { 26, 2, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent160Text11), 0, 794 },
    { 38, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent160Text12), MSG_SCRIPT_FLAG_END, 822 },
};

#ifdef VERSION_JP
#include "event_160_text.inc"
#endif

static const EvSoundCue sEvent160SoundCues[7] = {
    { 65535, 0, 0, 0 },
    { SONG_EV_WARPOUT, 130, 0, 0 },
    { SONG_BGM_EVENT_XIII, 160, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_SND_359, 260, 0, 0 },
    { SONG_SND_359, 750, 0, 0 },
    { SONG_BGM_EVENT_XIII, 705, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT2, 755, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent160Camera[1] = {
    { -64537, 188160, 61184, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent160Track0[13] = {
    { 515, 1, { 0, 0 }, 151552, 86784, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 518, 130, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 515, 140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 532, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 532, 210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 532, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 515, 260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 560, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 534, 590, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 534, 640, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 534, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 563, 750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 560, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent160Track1[4] = {
    { 721, 130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 721, 300, { 0, 0 }, 198144, 64000, 0, 0, { 0, 0 }, 2, EventCharaFadeIn, NULL },
    { 721, 430, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 721, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent160Tracks[2] = {
    { sEvent160Track0, 44, { 0, 0, 0 } },
    { sEvent160Track1, 67, { 0, 0, 0 } },
};

const EventSequenceDef gEvent160 = {
    2,
    { 0, 0, 0 },
    sEvent160Tracks,
    sEvent160Camera,
    sEvent160Script,
    sEvent160SoundCues,
    NULL,
    880,
    0,
    1,
    0,
    0,
    0,
    0,
    176,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
