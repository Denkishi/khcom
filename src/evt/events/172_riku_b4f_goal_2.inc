#ifdef VERSION_US
#include "event_172_text.inc"
#endif

static const MessageScriptEntry sEvent172Script[6] = {
    { 57, 2, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent172Text00), 0, 100 },
    { 26, 2, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent172Text01), 0, 140 },
    { 26, 1, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent172Text02), 0, 144 },
    { 57, 1, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent172Text03), 0, 180 },
    { 57, 2, 4, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent172Text04), 0, 182 },
    { 26, 3, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent172Text05), MSG_SCRIPT_FLAG_END, 480 },
};

#ifdef VERSION_JP
#include "event_172_text.inc"
#endif

static const EvSoundCue sEvent172SoundCues[6] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_EV_WARPIN, 230, 0, 0 },
    { SONG_SND_378, 250, 0, 0 },
    { SONG_EV_RUMBLE, 270, 0, 0 },
    { SONG_EV_RUMBLE, 640, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT_XIII, 645, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent172Camera[5] = {
    { -65266, 192256, 60672, 0, 255, 0, 0, NULL },
    { -65216, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_SHAKE_SMALL | CAMERA_MODE_KEEP, 0, NULL },
    { -64935, 182528, 65792, 0, 255, CAMERA_KEYFRAME_FLAG_SHAKE_SMALL | CAMERA_MODE_APPROACH, 100, NULL },
    { -64536, 38912, 38400, 0, 255, 0, 0, NULL },
    { -60536, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, NULL },
};

static const EventBgEffectEntry sEvent172BgEffects[5] = {
    { 320, 0, 0, 0, 0 },
    { 450, 0, 60, 0, 0x14 },
    { 3310, 0, 0, 0, 0 },
    { 3380, 0, 0, 0, 0x2 },
    { 3500, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent172Track0[7] = {
    { 555, 280, 182016, 71936, 0, 0, 66, NULL, NULL },
    { 556, 290, 0, 0, 0, 0, 69, NULL, NULL },
    { 515, 300, 0, 0, 0, 0, 69, NULL, NULL },
    { 532, 580, 0, 0, 0, 0, 69, NULL, NULL },
    { 532, 600, 0, 0, 0, 0, 64, EventCharaFadeOut, NULL },
    { 515, 1000, 256000, 256000, 0, 0, 66, NULL, NULL },
    { 515, 3000, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent172Track1[4] = {
    { 886, 230, 199424, 63488, 0, 0, 2, NULL, NULL },
    { 886, 250, 0, 0, 0, 0, 0, EventCharaFadeOut, NULL },
    { 886, 500, 0, 0, 0, 0, 2, NULL, NULL },
    { 883, 5000, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent172Track2[3] = {
    { 926, 250, 0, 0, 0, 0, 8194, NULL, NULL },
    { 926, 300, 199936, 60672, 0, 0, 16658, NULL, NULL },
    { 926, 5000, 0, 0, 0, 0, 98306, NULL, NULL },
};

static const EventCharaTrack sEvent172Tracks[3] = {
    { sEvent172Track0, 44 },
    { sEvent172Track1, 82 },
    { sEvent172Track2, 92 },
};

const EventSequenceDef gEvent172 = {
    3,
    sEvent172Tracks,
    sEvent172Camera,
    sEvent172Script,
    sEvent172SoundCues,
    sEvent172BgEffects,
    650,
    0,
    1,
    0,
    0,
    0,
    0,
    EVENT_173_RIKU_B4F_DARK,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
