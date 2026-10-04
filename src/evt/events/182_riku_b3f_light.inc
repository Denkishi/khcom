#ifdef VERSION_US
#include "event_182_text.inc"
#endif

static const MessageScriptEntry sEvent182Script[18] = {
    { 26, 5, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent182Text00), 0, 200 },
    { 28, 0, 0, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent182Text01), 0, 420 },
    { 28, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent182Text02), 0, 580 },
    { 28, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent182Text03), 0, 582 },
    { 26, 3, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent182Text04), 0, 610 },
    { 28, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent182Text05), 0, 640 },
    { 28, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent182Text06), 0, 642 },
    { 26, 0, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent182Text07), 0, 670 },
    { 28, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent182Text08), 0, 700 },
    { 28, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent182Text09), 0, 702 },
    { 28, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent182Text10), 0, 704 },
    { 26, 0, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent182Text11), 0, 730 },
    { 28, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent182Text12), 0, 760 },
    { 26, 5, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent182Text13), 0, 860 },
    { 28, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent182Text14), 0, 970 },
    { 26, 0, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent182Text15), 0, 1020 },
    { 26, 2, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent182Text16), 0, 1210 },
    { 26, 2, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent182Text17), MSG_SCRIPT_FLAG_END, 1350 },
};

#ifdef VERSION_JP
#include "event_182_text.inc"
#endif

static const EvSoundCue sEvent182SoundCues[4] = {
    { 65535, 0, 0, 0 },
    { SONG_EV_FLASH02, 1270, 0, 0 },
    { SONG_SND_702, 1440, 0, 0 },
    { SONG_SND_381, 1670, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent182Camera[7] = {
    { -65536, 98048, 32512, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, NULL },
    { -64296, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 60, { 0, 0 }, NULL },
    { -64266, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 30, { 0, 0 }, NULL },
    { -64236, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 30, { 0, 0 }, NULL },
    { -63916, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -63856, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 60, { 0, 0 }, NULL },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EventBgEffectEntry sEvent182BgEffects[5] = {
    { 1380, 0, 0, 0, 0 },
    { 1440, 0, 0, 0, 0x14 },
    { 1490, 2, 87040, 22784, 0x1 },
    { 1600, 0, 0, 0, 0x2 },
    { 3500, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent182Track0[11] = {
    { 565, 100, { 0, 0 }, 97792, 33024, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 565, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 1048837, NULL, NULL },
    { 565, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 1048832, EventCharaFadeOut, NULL },
    { 565, 1100, { 0, 0 }, 41472, 17920, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 514, 1205, { 0, 0 }, 97280, 38400, 0, 0, { 0, 0 }, 2306, EventCharaFadeIn, NULL },
    { 543, 1271, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2309, NULL, NULL },
    { 543, 1370, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 514, 1460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 514, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 524549, NULL, NULL },
    { 514, 2170, { 0, 0 }, 41472, 17920, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 514, 9000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent182Track1[6] = {
    { 420, 450, { 0, 0 }, 29696, 39424, 0, 0, { 0, 0 }, 8194, NULL, NULL },
    { 420, 930, { 0, 0 }, 97792, 38400, 0, 0, { 0, 0 }, 16642, EventCharaFadeIn, NULL },
    { 421, 1030, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 421, 1060, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 256, EventCharaFadeOut, NULL },
    { 420, 1100, { 0, 0 }, 29696, 39424, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 420, 9000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98309, NULL, NULL },
};

static const EventCharaKeyframe sEvent182Track2[7] = {
    { 695, 1459, { 0, 0 }, 29696, 39424, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 695, 1500, { 0, 0 }, 97280, 38400, 0, 0, { 0, 0 }, 524546, NULL, NULL },
    { 695, 1590, { 0, 0 }, 97280, 38400, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 696, 1610, { 0, 0 }, 97280, 38400, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 696, 1650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 701, 1625, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, NULL, NULL },
    { 702, 9000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33093, NULL, NULL },
};

static const EventCharaTrack sEvent182Tracks[3] = {
    { sEvent182Track0, 44, { 0, 0, 0 } },
    { sEvent182Track1, 34, { 0, 0, 0 } },
    { sEvent182Track2, 65, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent182 = {
    3,
    { 0, 0, 0 },
    sEvent182Tracks,
    sEvent182Camera,
    sEvent182Script,
    sEvent182SoundCues,
    sEvent182BgEffects,
    1770,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    183,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent182 = {
    3,
    { 0, 0, 0 },
    sEvent182Tracks,
    sEvent182Camera,
    sEvent182Script,
    sEvent182SoundCues,
    sEvent182BgEffects,
    1770,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    181,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif
