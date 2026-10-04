#ifdef VERSION_US
#include "event_140_text.inc"
#endif

static const MessageScriptEntry sEvent140Script[14] = {
    { 36, 2, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent140Text00), 0, 90 },
    { 50, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent140Text01), 0, 115 },
    { 36, 3, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent140Text02), 0, 160 },
    { 50, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent140Text03), 0, 190 },
    { 36, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent140Text04), 0, 300 },
    { 36, 1, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent140Text05), 0, 302 },
    { 50, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent140Text06), 0, 360 },
    { 0, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent140Text07), 0, 390 },
    { 50, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent140Text08), 0, 420 },
    { 50, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent140Text09), 0, 422 },
    { 36, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent140Text10), 0, 460 },
    { 50, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent140Text11), 0, 500 },
    { 0, 3, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent140Text12), 0, 530 },
    { 50, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent140Text13), MSG_SCRIPT_FLAG_END, 560 },
};

#ifdef VERSION_JP
#include "event_140_text.inc"
#endif

static const EvSoundCue sEvent140SoundCues[4] = {
    { SONG_BGM_WINNIETHEPOOH, 1, 0, 0 },
    { SONG_BG_POO, 2, 0, 0 },
    { SONG_BG_POO, 614, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_WINNIETHEPOOH, 615, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent140Camera[1] = {
    { -64537, 529664, 289536, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, NULL },
};

static const EventCharaKeyframe sEvent140Track0[5] = {
    { 4, 385, { 0, 0 }, 536064, 294144, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 36, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 525, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 27, 532, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent140Track1[5] = {
    { 802, 125, { 0, 0 }, 530432, 286720, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 803, 149, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 804, 200, { 0, 0 }, 529664, 287232, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 797, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 756, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent140Track2[4] = {
    { 821, 330, { 0, 0 }, 521472, 292352, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 820, 430, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 821, 470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 820, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent140Track3[2] = {
    { 808, 150, { 0, 0 }, 526848, 313856, -2560, 0, { 0, 0 }, 2, NULL, NULL },
    { 808, 500, { 0, 0 }, 494592, 295424, -2560, 808, { 0, 0 }, 32771, NULL, NULL },
};

static const EventCharaTrack sEvent140Tracks[4] = {
    { sEvent140Track0, 0, { 0, 0, 0 } },
    { sEvent140Track1, 70, { 0, 0, 0 } },
    { sEvent140Track2, 75, { 0, 0, 0 } },
    { sEvent140Track3, 71, { 0, 0, 0 } },
};

const EventSequenceDef gEvent140 = {
    3,
    { 0, 0, 0 },
    sEvent140Tracks,
    sEvent140Camera,
    sEvent140Script,
    sEvent140SoundCues,
    NULL,
    620,
    0,
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
    4,
};
