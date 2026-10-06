#ifdef VERSION_US
static const MessageScriptEntry sEvent071Script[1] = {
    { PORTRAIT_KAIRI, 0, 3, 1, gEvent071Text00, MSG_SCRIPT_FLAG_END, 9999 },
};

#include "event_071_text.inc"
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent071Script[1] = {
    { PORTRAIT_KAIRI, 0, 3, 3, gEvent071Text00, MSG_SCRIPT_FLAG_END, 9999 },
};

#include "event_071_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent071Script[1] = {
    { PORTRAIT_KAIRI, 0, 3, 1, NULL, MSG_SCRIPT_FLAG_END, 9999 },
};
#endif

static const EventCameraKeyframe sEvent071Camera[5] = {
    { -65535, 222208, 43776, 0, 255, 0, 0, NULL },
    { -65256, 211712, 51200, 0, 255, CAMERA_MODE_APPROACH, 80, NULL },
    { -65140, 226560, 36864, 0, 255, CAMERA_MODE_APPROACH, 50, NULL },
    { -64986, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 80, NULL },
    { -56536, 0, 0, 0, 255, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, NULL },
};

static const EvSoundCue sEvent071SoundCues[4] = {
    { 65535, 0, 0, 0 },
    { SONG_SND_361, 228, 0, 0 },
    { SONG_SND_362, 290, 0, 0 },
    { SONG_EV_WHITEOUT, 396, EV_SOUND_FLAG_END, 0 },
};

static const EventBgEffectEntry sEvent071BgEffects[6] = {
    { 200, 0, 0, 0, 0 },
    { 228, 0, 0, 0, 0x4 },
    { 290, 3, 200960, 41472, 0x1 },
    { 350, 4, 215296, 31488, 0x1 },
    { 379, 0, 0, 0, 0x2 },
    { 450, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent071Track0[9] = {
    { 2, 1, 215808, 57344, 0, 0, 2, NULL, NULL },
    { 12, 40, 200192, 63232, 0, 2, 3, NULL, NULL },
    { 2, 70, 0, 0, 0, 0, 5, NULL, NULL },
    { 1, 75, 0, 0, 0, 0, 5, NULL, NULL },
    { 2, 80, 0, 0, 0, 0, 69, NULL, NULL },
    { 3, 85, 0, 0, 0, 0, 69, NULL, NULL },
    { 4, 180, 0, 0, 0, 0, 69, NULL, NULL },
    { 100, 400, 0, 0, 0, 0, 69, NULL, NULL },
    { 100, 3000, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent071Track1[8] = {
    { 112, 1, 213504, 53760, 0, 0, 2, NULL, NULL },
    { 121, 80, 185088, 63232, 0, 112, 3, NULL, NULL },
    { 112, 110, 0, 0, 0, 0, 5, NULL, NULL },
    { 111, 115, 0, 0, 0, 0, 5, NULL, NULL },
    { 112, 120, 0, 0, 0, 0, 69, NULL, NULL },
    { 113, 125, 0, 0, 0, 0, 69, NULL, NULL },
    { 114, 130, 0, 0, 0, 0, 69, NULL, NULL },
    { 114, 3000, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent071Track2[8] = {
    { 144, 1, 222976, 58880, 0, 0, 2, NULL, NULL },
    { 152, 115, 196096, 74496, 0, 144, 3, NULL, NULL },
    { 144, 140, 0, 0, 0, 0, 5, NULL, NULL },
    { 145, 155, 0, 0, 0, 0, 5, NULL, NULL },
    { 146, 160, 0, 0, 0, 0, 5, NULL, NULL },
    { 142, 165, 0, 0, 0, 0, 5, NULL, NULL },
    { 146, 170, 0, 0, 0, 0, 69, NULL, NULL },
    { 146, 3000, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent071Tracks[3] = {
    { sEvent071Track0, 0 },
    { sEvent071Track1, 1 },
    { sEvent071Track2, 2 },
};

const EventSequenceDef gEvent071 = {
    3,
    sEvent071Tracks,
    sEvent071Camera,
    sEvent071Script,
    sEvent071SoundCues,
    sEvent071BgEffects,
    650,
    0,
    1,
    0,
    0,
    0,
    0,
    EVENT_072_13F_CASLTE_OBLIVION_LAST7,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
