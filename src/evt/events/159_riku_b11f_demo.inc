#ifdef VERSION_US
#include "event_159_text.inc"
#endif

static const MessageScriptEntry sEvent159Script[17] = {
    { 55, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent159Text00), 0, 100 },
    { 38, 3, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent159Text01), 0, 130 },
    { 38, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent159Text02), 0, 134 },
    { 55, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent159Text03), 0, 160 },
    { 38, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent159Text04), 0, 190 },
    { 38, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent159Text05), 0, 192 },
    { 38, 1, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent159Text06), 0, 194 },
    { 55, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent159Text07), 0, 225 },
    { 38, 1, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent159Text08), 0, 255 },
    { 38, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent159Text09), 0, 257 },
    { 55, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent159Text10), 0, 290 },
    { 38, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent159Text11), 0, 320 },
    { 38, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent159Text12), 0, 322 },
    { 55, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent159Text13), 0, 360 },
    { 38, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent159Text14), 0, 390 },
    { 38, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent159Text15), 0, 394 },
    { 38, 1, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent159Text16), MSG_SCRIPT_FLAG_END, 396 },
};

#ifdef VERSION_JP
#include "event_159_text.inc"
#endif

static const EventCameraKeyframe sEvent159Camera[1] = {
    { -64537, 68352, 58368, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent159SoundCues[2] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_BGM_EVENT_XIII, 451, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent159Track0[2] = {
    { 889, 100, { 0, 0 }, 78080, 63488, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 889, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent159Track1[4] = {
    { 721, 132, { 0, 0 }, 57856, 66560, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 727, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 729, 392, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 727, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent159Tracks[2] = {
    { sEvent159Track0, 83, { 0, 0, 0 } },
    { sEvent159Track1, 67, { 0, 0, 0 } },
};

const EventSequenceDef gEvent159 = {
    2,
    { 0, 0, 0 },
    sEvent159Tracks,
    sEvent159Camera,
    sEvent159Script,
    sEvent159SoundCues,
    NULL,
    456,
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
