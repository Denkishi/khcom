#ifdef VERSION_US
#include "event_111_text.inc"
#endif

static const MessageScriptEntry sEvent111Script[29] = {
    { 0, 1, 0, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent111Text00), 0, 160 },
    { 15, 3, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent111Text01), 0, 180 },
    { 0, 3, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent111Text02), 0, 270 },
    { 1, 5, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent111Text03), 0, 290 },
    { 15, 4, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent111Text04), 0, 400 },
    { 16, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent111Text05), 0, 600 },
    { 16, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent111Text06), 0, 602 },
    { 16, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent111Text07), 0, 604 },
    { 16, 2, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent111Text08), 0, 650 },
    { 15, 2, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent111Text09), 0, 750 },
    { 16, 0, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent111Text10), 0, 850 },
    { 16, 2, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent111Text11), 0, 852 },
    { 0, 3, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent111Text12), 0, 870 },
    { 16, 2, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent111Text13), 0, 900 },
    { 16, 2, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent111Text14), 0, 902 },
    { 16, 0, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent111Text15), 0, 904 },
    { 15, 4, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent111Text16), 0, 1050 },
    { 21, 4, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent111Text17), 0, 1070 },
    { 21, 4, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent111Text18), 0, 1072 },
    { 16, 2, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent111Text19), 0, 1100 },
    { 15, 3, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent111Text20), 0, 1300 },
    { 0, 2, 1, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent111Text21), 0, 1320 },
    { 0, 2, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent111Text22), 0, 1322 },
    { 0, 2, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent111Text23), 0, 1324 },
    { 15, 3, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent111Text24), 0, 1350 },
    { 15, 2, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent111Text25), 0, 1500 },
    { 1, 0, 0, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent111Text26), 0, 1520 },
    { 1, 2, 4, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent111Text27), 0, 1522 },
    { 15, 1, 3, EVENT_TEXT_DELAY, { 0, 0, 0 }, EVENT_TEXT(gEvent111Text28), MSG_SCRIPT_FLAG_END, 1700 },
};

#ifdef VERSION_JP
#include "event_111_text.inc"
#endif

static const EventCameraKeyframe sEvent111Camera[12] = {
    { -65336, 70400, 92416, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, NULL },
    { -65316, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -65296, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -65276, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -65256, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -65236, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, NULL },
    { -65086, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, NULL },
    { -64856, 36352, 28672, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -64756, 68352, 92416, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -64336, 36352, 28672, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -63826, 72704, 97536, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, NULL },
    { -63686, 72704, 22528, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 150, { 0, 0 }, NULL },
};

static const EvSoundCue sEvent111SoundCues[6] = {
    { SONG_BGM_ALADDIN_FIELD, 0, 0, 0 },
    { SONG_BGM_ALADDIN_FIELD, 200, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT_UNREST, 450, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT_UNREST, 1150, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_ALADDIN_FIELD, 1500, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_ALADDIN_FIELD, 1745, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent111Track0[11] = {
    { 21, 1, { 0, 0 }, 84992, 106240, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 21, 100, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 22, 120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 4, 130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 0, 135, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 27, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, NULL, CreateExclamationTask },
    { 4, 1319, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 30, 1326, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 4, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent111Track1[11] = {
    { 123, 1, { 0, 0 }, 75008, 106752, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 123, 105, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 124, 125, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 135, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 114, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 133, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 110, 305, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 1519, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 126, 1524, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 114, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, NULL, NULL },
};

static const EventCharaKeyframe sEvent111Track2[11] = {
    { 155, 1, { 0, 0 }, 59392, 103424, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 158, 110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 159, 130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 161, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 145, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 146, 1301, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 142, 1306, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 146, 1311, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 145, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent111Track3[21] = {
    { 282, 1, { 0, 0 }, 69120, 101120, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 282, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 270, 185, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 282, 190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 282, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 286, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 282, 310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 270, 320, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 270, 340, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 270, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 270, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 270, 410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 270, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 282, 1300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 287, 1330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 287, 1340, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 275, 1360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 275, 1490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 270, 1530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 270, 1690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateBalloonTask },
    { 270, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, NULL, NULL },
};

static const EventCharaKeyframe sEvent111Track4[10] = {
    { 664, 1, { 0, 0 }, 56320, 95488, -2560, 0, { 0, 0 }, 66, NULL, NULL },
    { 664, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 262213, NULL, NULL },
    { 673, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, NULL, CreateExclamationTask },
    { 664, 650, { 0, 0 }, 59136, 97280, -2560, 0, { 0, 0 }, 262210, NULL, NULL },
    { 665, 950, { 0, 0 }, 59136, 97280, -2560, 0, { 0, 0 }, 262146, NULL, NULL },
    { 672, 1020, { 0, 0 }, 52480, 42496, -7680, 664, { 0, 0 }, 4419, NULL, NULL },
    { 672, 1110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 262469, NULL, NULL },
    { 672, 1120, { 0, 0 }, 52480, 42496, -5120, 664, { 0, 0 }, 4419, NULL, NULL },
    { 672, 1180, { 0, 0 }, 52480, 42496, -46080, 664, { 0, 0 }, 4419, NULL, NULL },
    { 664, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98370, NULL, NULL },
};

static const EventCharaKeyframe sEvent111Track5[7] = {
    { 588, 949, { 0, 0 }, 77056, 97792, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 588, 950, { 0, 0 }, 58112, 97280, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 589, 1020, { 0, 0 }, 52480, 42752, -7680, 586, { 0, 0 }, 4419, NULL, NULL },
    { 589, 1110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 262469, NULL, NULL },
    { 589, 1120, { 0, 0 }, 52480, 42752, -5120, 586, { 0, 0 }, 4419, NULL, NULL },
    { 589, 1180, { 0, 0 }, 52480, 42752, -46080, 586, { 0, 0 }, 4419, NULL, NULL },
    { 589, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98370, NULL, NULL },
};

static const EventCharaKeyframe sEvent111Track6[9] = {
    { 632, 500, { 0, 0 }, 22528, 33536, 0, 0, { 0, 0 }, 66, NULL, NULL },
    { 634, 560, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, NULL, NULL },
    { 632, 610, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 635, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 636, 1110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, NULL, NULL },
    { 632, 1120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 633, 1130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, NULL, NULL },
    { 637, 1230, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, NULL, NULL },
    { 633, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98309, NULL, NULL },
};

static const EventCharaTrack sEvent111Tracks[7] = {
    { sEvent111Track0, 0, { 0, 0, 0 } },
    { sEvent111Track1, 1, { 0, 0, 0 } },
    { sEvent111Track2, 2, { 0, 0, 0 } },
    { sEvent111Track3, 12, { 0, 0, 0 } },
    { sEvent111Track4, 59, { 0, 0, 0 } },
    { sEvent111Track5, 48, { 0, 0, 0 } },
    { sEvent111Track6, 56, { 0, 0, 0 } },
};

const EventSequenceDef gEvent111 = {
    7,
    { 0, 0, 0 },
    sEvent111Tracks,
    sEvent111Camera,
    sEvent111Script,
    sEvent111SoundCues,
    NULL,
    1750,
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
