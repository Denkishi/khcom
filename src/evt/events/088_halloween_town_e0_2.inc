#ifdef VERSION_US
#include "event_088_text.inc"
#endif

static const MessageScriptEntry sEvent088Script[12] = {
    { PORTRAIT_DONALD, 4, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent088Text00), 0, 100 },
    { PORTRAIT_JACK, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent088Text01), 0, 110 },
    { PORTRAIT_JACK, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent088Text02), 0, 130 },
    { PORTRAIT_SORA, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent088Text03), 0, 160 },
    { PORTRAIT_JACK, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent088Text04), 0, 180 },
    { PORTRAIT_JACK, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent088Text05), 0, 200 },
    { PORTRAIT_JIMINY_CRICKET, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent088Text06), 0, 510 },
    { PORTRAIT_SORA, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent088Text07), 0, 530 },
    { PORTRAIT_DONALD, 1, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent088Text08), 0, 560 },
    { PORTRAIT_JACK, 2, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent088Text09), 0, 590 },
    { PORTRAIT_DONALD, 5, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent088Text10), 0, 650 },
    { PORTRAIT_JACK, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent088Text11), MSG_SCRIPT_FLAG_END, 710 },
};

#ifdef VERSION_JP
#include "event_088_text.inc"
#endif

static const EventCameraKeyframe sEvent088Camera[1] = {
    { -65485, 30720, 20480, 0, 255, CAMERA_KEYFRAME_FLAG_END, 0, NULL },
};

static const EventBgEffectEntry sEvent088BgEffects[5] = {
    { 592, 0, 0, 0, 0 },
    { 593, 0, 0, 0, 0x4 },
    { 620, 0, 0, 0, 0 },
    { 700, 0, 0, 0, 0x2 },
    { 760, 0, 0, 0, 0x8008 },
};

static const EvSoundCue sEvent088SoundCues[4] = {
    { SONG_BGM_HALLOWEEN_FIELD, 0, 0, 0 },
    { SONG_SND_347, 624, 0, 0 },
    { SONG_EV_DL_JUMP, 649, 0, 0 },
    { SONG_BGM_HALLOWEEN_FIELD, 925, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent088Track0[3] = {
    { 4, 30, 24832, 30464, 0, 0, 66, NULL, NULL },
    { 4, 915, 0, 0, 0, 0, 69, NULL, NULL },
    { 9, 9999, 0, 0, 0, 45, 32836, NULL, NULL },
};

static const EventCharaKeyframe sEvent088Track1[12] = {
    { 114, 1, 36608, 28160, 0, 0, 2, NULL, NULL },
    { 131, 110, 0, 0, 0, 0, 0, NULL, CreateSmokeTask },
    { 114, 250, 0, 0, 0, 0, 5, NULL, NULL },
    { 110, 300, 0, 0, 0, 0, 5, NULL, NULL },
    { 114, 550, 0, 0, 0, 0, 69, NULL, NULL },
    { 127, 558, 0, 0, 0, 0, 69, NULL, NULL },
    { 128, 610, 0, 0, 0, 0, 69, NULL, NULL },
    { 129, 618, 0, 0, 0, 0, 69, NULL, NULL },
    { 114, 640, 0, 0, 0, 0, 69, NULL, NULL },
    { 133, 715, 0, 0, 0, 0, 64, EventCharaHopHigh, NULL },
    { 114, 920, 0, 0, 0, 0, 69, NULL, NULL },
    { 119, 9999, 0, 0, 0, 45, 32836, NULL, NULL },
};

static const EventCharaKeyframe sEvent088Track2[6] = {
    { 144, 250, 23808, 19968, 0, 0, 66, NULL, NULL },
    { 145, 540, 0, 0, 0, 0, 69, NULL, NULL },
    { 144, 700, 0, 0, 0, 0, 69, NULL, NULL },
    { 145, 810, 0, 0, 0, 0, 69, NULL, NULL },
    { 146, 930, 0, 0, 0, 0, 69, NULL, NULL },
    { 151, 9999, 0, 0, 0, 45, 32836, NULL, NULL },
};

static const EventCharaKeyframe sEvent088Track3[17] = {
    { 288, 101, 30976, 22784, 0, 0, 2, NULL, NULL },
    { 288, 170, 0, 0, 0, 0, 69, NULL, NULL },
    { 288, 199, 0, 0, 0, 0, 5, NULL, NULL },
    { 298, 201, 0, 0, 0, 0, 5, NULL, NULL },
    { 288, 210, 0, 0, 0, 0, 5, NULL, NULL },
    { 288, 220, 0, 0, 0, 0, 69, NULL, NULL },
    { 289, 230, 0, 0, 0, 0, 69, NULL, NULL },
    { 296, 300, 0, 0, 0, 45, 68, NULL, NULL },
    { 290, 340, 0, 0, 0, 83, 68, NULL, NULL },
    { 296, 450, 0, 0, 0, 45, 68, NULL, NULL },
    { 288, 624, 0, 0, 0, 0, 5, NULL, NULL },
    { 294, 660, 42240, 24832, 0, 0, 2, NULL, NULL },
    { 295, 715, 42240, 24832, 0, 0, 2, EventCharaFadeIn, NULL },
    { 288, 730, 0, 0, 0, 0, 5, NULL, NULL },
    { 288, 740, 0, 0, 0, 0, 69, NULL, NULL },
    { 289, 770, 0, 0, 0, 0, 69, NULL, NULL },
    { 296, 9999, 0, 0, 0, 45, 32836, NULL, NULL },
};

static const EventCharaKeyframe sEvent088Track4[11] = {
    { 231, 440, 0, 0, 0, 0, 8258, NULL, NULL },
    { 231, 441, 24832, 30464, 0, 0, 16450, NULL, NULL },
    { 234, 470, 0, 0, 0, 45, 68, EventCharaHop, NULL },
    { 231, 480, 0, 0, 0, 0, 69, NULL, NULL },
    { 229, 490, 0, 0, 0, 0, 69, NULL, NULL },
    { 229, 591, 0, 0, 0, 0, 5, NULL, NULL },
    { 229, 600, 0, 0, 0, 0, 69, NULL, NULL },
    { 231, 830, 0, 0, 0, 0, 69, NULL, NULL },
    { 229, 840, 0, 0, 0, 0, 5, NULL, NULL },
    { 233, 860, 0, 0, 0, 173, 4, EventCharaHop, NULL },
    { 231, 999, 102400, 102400, 0, 0, 32834, NULL, NULL },
};

static const EventCharaTrack sEvent088Tracks[5] = {
    { sEvent088Track0, 0 },
    { sEvent088Track1, 1 },
    { sEvent088Track2, 2 },
    { sEvent088Track3, 13 },
    { sEvent088Track4, 8 },
};

const EventSequenceDef gEvent088 = {
    5,
    sEvent088Tracks,
    sEvent088Camera,
    sEvent088Script,
    sEvent088SoundCues,
    sEvent088BgEffects,
    930,
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
    1,
    255,
    255,
};
