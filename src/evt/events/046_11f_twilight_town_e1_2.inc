#ifdef VERSION_US
#include "event_046_text.inc"
#endif

static const MessageScriptEntry sEvent046Script[19] = {
    { 38, 2, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent046Text00), 0, 100 },
    { 0, 2, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent046Text01), 0, 230 },
    { 38, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent046Text02), 0, 260 },
    { 38, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent046Text03), 0, 262 },
    { 38, 2, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent046Text04), 0, 272 },
    { 0, 3, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent046Text05), 0, 300 },
    { 38, 3, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent046Text06), 0, 350 },
    { 0, 2, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent046Text07), 0, 525 },
    { 20, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent046Text08), 0, 600 },
    { 38, 2, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent046Text09), 0, 640 },
    { 20, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent046Text10), 0, 670 },
    { 38, 3, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent046Text11), 0, 700 },
    { 20, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent046Text12), 0, 740 },
    { 20, 1, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent046Text13), 0, 742 },
    { 38, 3, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent046Text14), 0, 770 },
    { 20, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent046Text15), 0, 820 },
    { 0, 3, 2, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent046Text16), 0, 1105 },
    { 0, 2, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent046Text17), 0, 1145 },
    { 20, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent046Text18), MSG_SCRIPT_FLAG_END, 1195 },
};

#ifdef VERSION_JP
#include "event_046_text.inc"
#endif

static const EventCameraKeyframe sEvent046Camera[9] = {
    { -65201, 50432, 100096, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65196, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 5, { 0, 0 }, NULL },
    { -65156, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -65126, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 30, { 0, 0 }, NULL },
    { -64686, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64666, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 20, { 0, 0 }, NULL },
    { -64646, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64576, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 30, { 0, 0 }, NULL },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent046SoundCues[6] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_EF_STANIMP, 332, 0, 0 },
    { SONG_EF_SYNC2, 850, 0, 0 },
    { SONG_SND_355, 1018, 0, 0 },
    { SONG_EV_WARPIN, 1200, 0, 0 },
    { SONG_BGM_EVENT_XIII, 1295, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent046Track0[16] = {
    { 21, 150, { 0, 0 }, 40448, 114432, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 22, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 225, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 30, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 295, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 27, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 30, 530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 27, 1050, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 27, 1080, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 1110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 14, 1130, { 0, 0 }, 47360, 106752, 0, 4, { 0, 0 }, 67, NULL, NULL },
    { 4, 1140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 30, 1240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent046Track1[6] = {
    { 123, 155, { 0, 0 }, 33024, 107776, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 124, 165, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 133, 1050, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 133, 1080, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent046Track2[6] = {
    { 158, 160, { 0, 0 }, 50176, 117248, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 159, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 161, 1050, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 161, 1080, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent046Track3[7] = {
    { 732, 263, { 0, 0 }, 60672, 102912, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 733, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 730, 410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 734, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 736, 1040, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 736, 1070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaFadeOut, NULL },
    { 721, 4000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, NULL, NULL },
};

static const EventCharaKeyframe sEvent046Track4[11] = {
    { 513, 301, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 513, 321, { 0, 0 }, 85760, 79104, 0, 0, { 0, 0 }, 258, NULL, NULL },
    { 513, 340, { 0, 0 }, 62464, 90624, 0, 485, { 0, 0 }, 4355, NULL, NULL },
    { 513, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, NULL, NULL },
    { 496, 850, { 0, 0 }, 69632, 98560, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 497, 1080, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 498, 1091, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 485, 1190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 509, 1200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 509, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaFadeOut, NULL },
    { 485, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent046Tracks[5] = {
    { sEvent046Track0, 0, { 0, 0, 0 } },
    { sEvent046Track1, 1, { 0, 0, 0 } },
    { sEvent046Track2, 2, { 0, 0, 0 } },
    { sEvent046Track3, 67, { 0, 0, 0 } },
    { sEvent046Track4, 43, { 0, 0, 0 } },
};

const EventSequenceDef gEvent046 = {
    5,
    { 0, 0, 0 },
    sEvent046Tracks,
    sEvent046Camera,
    sEvent046Script,
    sEvent046SoundCues,
    NULL,
    1300,
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
