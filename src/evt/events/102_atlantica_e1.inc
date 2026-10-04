#ifdef VERSION_US
#include "event_102_text.inc"
#endif

static const MessageScriptEntry sEvent102Script[19] = {
    { 23, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent102Text00), 0, 300 },
    { 0, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent102Text01), 0, 340 },
    { 23, 1, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent102Text02), 0, 400 },
    { 23, 1, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent102Text03), 0, 402 },
    { 23, 1, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent102Text04), 0, 404 },
    { 0, 3, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent102Text05), 0, 420 },
    { 23, 1, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent102Text06), 0, 450 },
    { 0, 0, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent102Text07), 0, 520 },
    { 2, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent102Text08), 0, 540 },
    { 2, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent102Text09), 0, 542 },
    { 0, 3, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent102Text10), 0, 670 },
    { 6, 2, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent102Text11), 0, 720 },
    { 1, 5, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent102Text12), 0, 740 },
    { 6, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent102Text13), 0, 760 },
    { 23, 1, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent102Text14), 0, 800 },
    { 23, 1, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent102Text15), 0, 860 },
    { 23, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent102Text16), 0, 960 },
    { 0, 1, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent102Text17), 0, 1130 },
    { 2, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent102Text18), MSG_SCRIPT_FLAG_END, 1160 },
};

#ifdef VERSION_JP
#include "event_102_text.inc"
#endif

static const EventCameraKeyframe sEvent102Camera[3] = {
    { -64775, 48128, 38144, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -64566, 35840, 29440, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 30, { 0, 0 }, NULL },
    { -64336, 48128, 38144, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 30, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent102SoundCues[2] = {
    { SONG_BGM_EVENT1, 0, 0, 0 },
    { SONG_BGM_EVENT1, 1245, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent102Track0[15] = {
    { 461, 350, { 0, 0 }, 36864, 35328, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 460, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 460, 460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 461, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 461, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 463, 520, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 461, 770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 460, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 460, 790, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 460, 810, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 463, 850, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, NULL, NULL },
    { 460, 870, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 462, 950, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, NULL, NULL },
    { 460, 970, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 461, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent102Track1[12] = {
    { 4, 10, { 0, 0 }, 81920, 57856, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 9, 150, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 4, 419, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 27, 451, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 34, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 34, 669, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 30, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 970, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 1120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 4, 1129, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 36, 1150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent102Track2[7] = {
    { 112, 10, { 0, 0 }, 90368, 57856, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 119, 150, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 114, 739, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 126, 741, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 970, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 1120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 114, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent102Track3[15] = {
    { 144, 10, { 0, 0 }, 77824, 64000, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 151, 150, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 146, 530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 142, 535, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 539, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 165, 543, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 142, 555, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 970, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 1120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateBalloonTask },
    { 146, 1140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 142, 1145, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 1159, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 165, 1161, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent102Track4[8] = {
    { 231, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 231, 151, { 0, 0 }, 49152, 40960, 0, 0, { 0, 0 }, 2, NULL, NULL },
    { 234, 180, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, EventCharaHop, NULL },
    { 231, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 229, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 229, 770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 231, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 231, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaTrack sEvent102Tracks[5] = {
    { sEvent102Track0, 38, { 0, 0, 0 } },
    { sEvent102Track1, 0, { 0, 0, 0 } },
    { sEvent102Track2, 1, { 0, 0, 0 } },
    { sEvent102Track3, 2, { 0, 0, 0 } },
    { sEvent102Track4, 8, { 0, 0, 0 } },
};

const EventSequenceDef gEvent102 = {
    5,
    { 0, 0, 0 },
    sEvent102Tracks,
    sEvent102Camera,
    sEvent102Script,
    sEvent102SoundCues,
    NULL,
    1250,
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
