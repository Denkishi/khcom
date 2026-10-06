#ifdef VERSION_US
#include "event_017_text.inc"
#endif

static const MessageScriptEntry sEvent017Script[11] = {
    { 54, 1, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent017Text00), 0, 150 },
    { 20, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent017Text01), 0, 180 },
    { 54, 1, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent017Text02), 0, 200 },
    { 20, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent017Text03), 0, 230 },
    { 54, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent017Text04), 0, 270 },
    { 20, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent017Text05), 0, 300 },
    { 20, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent017Text06), 0, 340 },
    { 54, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent017Text07), 0, 490 },
    { 20, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent017Text08), 0, 510 },
    { 54, 0, 3, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent017Text09), 0, 530 },
    { 20, 0, 1, EVENT_TEXT_DELAY, EVENT_TEXT(gEvent017Text10), MSG_SCRIPT_FLAG_END, 550 },
};

#ifdef VERSION_JP
#include "event_017_text.inc"
#endif

static const EventCameraKeyframe sEvent017Camera[1] = {
    { -64537, 70912, 60672, 0, 255, CAMERA_KEYFRAME_FLAG_END, 0, NULL },
};

static const EvSoundCue sEvent017SoundCues[2] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_BGM_EVENT_XIII, 595, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent017Track0[7] = {
    { 485, 175, 79360, 73216, 0, 0, 66, NULL, NULL },
    { 509, 280, 0, 0, 0, 0, 69, NULL, NULL },
    { 485, 310, 0, 0, 0, 0, 69, NULL, NULL },
    { 485, 320, 0, 0, 0, 0, 5, NULL, NULL },
    { 486, 505, 0, 0, 0, 0, 5, NULL, NULL },
    { 506, 515, 0, 0, 0, 0, 5, NULL, NULL },
    { 486, 999, 0, 0, 0, 0, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent017Track1[6] = {
    { 856, 130, 63232, 63488, 0, 0, 66, NULL, NULL },
    { 857, 265, 0, 0, 0, 0, 69, NULL, NULL },
    { 858, 350, 0, 0, 0, 0, 69, NULL, NULL },
    { 858, 480, 0, 0, 0, 0, 64, NULL, CreateBalloonTask },
    { 861, 525, 0, 0, 0, 0, 69, NULL, NULL },
    { 858, 999, 0, 0, 0, 0, 32837, NULL, NULL },
};

static const EventCharaTrack sEvent017Tracks[2] = {
    { sEvent017Track0, 43 },
    { sEvent017Track1, 81 },
};

const EventSequenceDef gEvent017 = {
    2,
    sEvent017Tracks,
    sEvent017Camera,
    sEvent017Script,
    sEvent017SoundCues,
    NULL,
    600,
    0,
    0,
    0,
    0,
    0,
    0,
    EVENT_018_4F_ENTRANCE,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
