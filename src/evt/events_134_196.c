#include "events_134_196.h"
#include "events_000_073.h"
#include "events_074_133.h"
#include "msg.h"
#include "card_message_assets.h"
#include "eventselect_api.h"
#include "card_message_text.h"
#include "event_text.h"
#include "msg_localized_data.h"
#include "songs.h"

#ifdef VERSION_US
#include "event_134_text.inc"

static const MessageScriptEntry sEvent134Script[22] = {
    { 0, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09007134, 0, 830 },
    { 36, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900716C, 0, 980 },
    { 0, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_090071A4, 0, 1010 },
    { 0, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_090071D0, 0, 1155 },
    { 36, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900720A, 0, 1185 },
    { 0, 7, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09007250, 0, 1215 },
    { 36, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09007290, 0, 1305 },
    { 36, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090072EE, 0, 1309 },
    { 36, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090073A0, 0, 1311 },
    { 0, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09007408, 0, 1500 },
    { 36, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09007462, 0, 1530 },
    { 0, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09007498, 0, 1560 },
    { 36, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900752E, 0, 1590 },
    { 0, 4, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09007576, 0, 1620 },
    { 36, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090075D6, 0, 1650 },
    { 36, 3, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09007608, 0, 1652 },
    { 0, 4, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09007656, 0, 1690 },
    { 0, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090076E0, 0, 1692 },
    { 36, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09007792, 0, 1725 },
    { 62, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_090077BC, 0, 1920 },
    { 62, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09007868, 0, 1920 },
    { 62, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900790E, MSG_SCRIPT_FLAG_END, 1920 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent134Script[22] = {
    { 0, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE3DC4, 0, 830 },
    { 36, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE3DA8, 0, 980 },
    { 0, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE3D90, 0, 1010 },
    { 0, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE3D6C, 0, 1155 },
    { 36, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE3D44, 0, 1185 },
    { 0, 7, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE3D1C, 0, 1215 },
    { 36, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE3CF0, 0, 1305 },
    { 36, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE3CAC, 0, 1309 },
    { 36, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE3C90, 0, 1311 },
    { 0, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE3C70, 0, 1500 },
    { 36, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE3C54, 0, 1530 },
    { 0, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE3C10, 0, 1560 },
    { 36, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE3BF4, 0, 1590 },
    { 0, 4, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE3BC8, 0, 1620 },
    { 36, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE3BA4, 0, 1650 },
    { 36, 3, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE3B7C, 0, 1652 },
    { 0, 4, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE3B4C, 0, 1690 },
    { 0, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE3AFC, 0, 1692 },
    { 36, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE3AE0, 0, 1725 },
    { 62, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE3A90, 0, 1920 },
    { 62, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE3A5C, 0, 1920 },
    { 62, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE3A1C, MSG_SCRIPT_FLAG_END, 1920 },
};

#include "event_134_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent134Script[22] = {
    { 0, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69628, 0, 830 },
    { 36, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6963C, 0, 980 },
    { 0, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69650, 0, 1010 },
    { 0, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69664, 0, 1155 },
    { 36, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69678, 0, 1185 },
    { 0, 7, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6968C, 0, 1215 },
    { 36, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F696A0, 0, 1305 },
    { 36, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F696B4, 0, 1309 },
    { 36, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F696C8, 0, 1311 },
    { 0, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F696DC, 0, 1500 },
    { 36, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F696F0, 0, 1530 },
    { 0, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69704, 0, 1560 },
    { 36, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69718, 0, 1590 },
    { 0, 4, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6972C, 0, 1620 },
    { 36, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69740, 0, 1650 },
    { 36, 3, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69754, 0, 1652 },
    { 0, 4, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69768, 0, 1690 },
    { 0, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6977C, 0, 1692 },
    { 36, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69790, 0, 1725 },
    { 62, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F697A4, 0, 1920 },
    { 62, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F697B8, 0, 1920 },
    { 62, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F697CC, MSG_SCRIPT_FLAG_END, 1920 },
};
#endif

static const EventCameraKeyframe sEvent134Camera[3] = {
    { -65536, 109312, 65024, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, 0 },
    { -64636, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 80, { 0, 0 }, 0 },
    { -59636, 105216, 67328, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 50, { 0, 0 }, 0 },
};

static const EvSoundCue sEvent134SoundCues[2] = {
    { SONG_BGM_WINNIETHEPOOH, 1, 0, 0 },
    { SONG_BG_POO, 2, EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent134Track0[29] = {
    { 2, 500, { 0, 0 }, 73472, 59648, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 7, 570, { 0, 0 }, 89344, 67328, 0, 2, { 0, 0 }, 67, 0, 0 },
    { 2, 620, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 2, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 7, 770, { 0, 0 }, 100096, 71424, 0, 2, { 0, 0 }, 67, 0, 0 },
    { 2, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 3, 790, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 4, 1030, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 0, 1035, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 4, 1060, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 0, 1065, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 4, 1070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 3, 1075, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 2, 1080, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 1, 1110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 2, 1115, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 3, 1120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 4, 1210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 34, 1340, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 34, 1470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 34, 1490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 4, 1495, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 30, 1502, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 4, 1615, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 36, 1660, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 4, 1830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 3, 1835, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 2, 1860, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 7, 9999, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 32836, 0, 0 },
};

static const EventCharaKeyframe sEvent134Track1[42] = {
    { 756, 1, { 0, 0 }, 110080, 67840, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 781, 130, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 68, 0, 0 },
    { 756, 140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 765, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 764, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 765, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 756, 190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 766, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 766, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 755, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 756, 240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 757, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 758, 260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 783, 380, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 4, 0, 0 },
    { 758, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 774, 410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 757, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 756, 590, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 757, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 758, 620, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 783, 670, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 4, 0, 0 },
    { 758, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 774, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 775, 710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 774, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 758, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 773, 740, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 772, 860, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 759, 870, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 758, 880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 757, 890, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 756, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 781, 950, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 68, 0, 0 },
    { 756, 1240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 798, 1300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 799, 1307, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 795, 1525, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, 0, 0 },
    { 804, 1740, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, 0, 0 },
    { 797, 1830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, 0, 0 },
    { 755, 1840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 756, 1880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 781, 9999, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 32772, 0, 0 },
};

static const EventCharaKeyframe sEvent134Track2[2] = {
    { 806, 475, { 0, 0 }, 146176, 59904, -5120, 0, { 0, 0 }, 2, 0, 0 },
    { 806, 9999, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 33028, 0, 0 },
};

static const EventCharaTrack sEvent134Tracks[3] = {
    { sEvent134Track0, 0, { 0, 0, 0 } },
    { sEvent134Track1, 70, { 0, 0, 0 } },
    { sEvent134Track2, 71, { 0, 0, 0 } },
};

const EventSequenceDef gEvent134 = {
    3,
    { 0, 0, 0 },
    sEvent134Tracks,
    sEvent134Camera,
    sEvent134Script,
    sEvent134SoundCues,
    0,
    1940,
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
    0,
};

#ifdef VERSION_US
#include "event_135_text.inc"

static const MessageScriptEntry sEvent135Script[1] = {
    { 36, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900868C, MSG_SCRIPT_FLAG_END, 300 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent135Script[1] = {
    { 36, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE48E8, MSG_SCRIPT_FLAG_END, 300 },
};

#include "event_135_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent135Script[1] = {
    { 36, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69614, MSG_SCRIPT_FLAG_END, 300 },
};
#endif

static const EventCameraKeyframe sEvent135Camera[2] = {
    { -65536, 105216, 67328, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, 0 },
    { -64636, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 80, { 0, 0 }, 0 },
};

static const EvSoundCue sEvent135SoundCues[2] = {
    { SONG_BGM_WINNIETHEPOOH, 1, 0, 0 },
    { SONG_BG_POO, 2, EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent135Track0[5] = {
    { 2, 1, { 0, 0 }, 73472, 59648, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 7, 121, { 0, 0 }, 100096, 71424, 0, 2, { 0, 0 }, 67, 0, 0 },
    { 2, 140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 3, 145, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 4, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent135Track1[3] = {
    { 796, 160, { 0, 0 }, 110080, 67840, 0, 0, { 0, 0 }, 258, 0, 0 },
    { 797, 1830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, 0, 0 },
    { 756, 1880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent135Track2[2] = {
    { 806, 20, { 0, 0 }, 146176, 59904, -5120, 0, { 0, 0 }, 2, 0, 0 },
    { 806, 9999, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 33028, 0, 0 },
};

static const EventCharaTrack sEvent135Tracks[3] = {
    { sEvent135Track0, 0, { 0, 0, 0 } },
    { sEvent135Track1, 70, { 0, 0, 0 } },
    { sEvent135Track2, 71, { 0, 0, 0 } },
};

const EventSequenceDef gEvent135 = {
    3,
    { 0, 0, 0 },
    sEvent135Tracks,
    sEvent135Camera,
    sEvent135Script,
    sEvent135SoundCues,
    0,
    360,
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
    0,
};

#ifdef VERSION_US
#include "event_136_text.inc"

static const MessageScriptEntry sEvent136Script[18] = {
    { 47, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_090088F4, 0, 120 },
    { 47, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09008902, 0, 160 },
    { 0, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09008988, 0, 180 },
    { 47, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_090089BC, 0, 200 },
    { 47, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090089D0, 0, 202 },
    { 36, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09008A42, 0, 370 },
    { 47, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09008A76, 0, 420 },
    { 47, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09008A9E, 0, 460 },
    { 47, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09008AF2, 0, 462 },
    { 0, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09008B8E, 0, 470 },
    { 36, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09008BDC, 0, 500 },
    { 47, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09008C6C, 0, 520 },
    { 47, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09008CA2, 0, 670 },
    { 0, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09008CD0, 0, 690 },
    { 47, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09008D30, 0, 795 },
    { 36, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09008D46, 0, 870 },
    { 47, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09008D7C, 0, 890 },
    { 47, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09008E12, MSG_SCRIPT_FLAG_END, 892 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent136Script[18] = {
    { 47, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE4F68, 0, 120 },
    { 47, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE4F24, 0, 160 },
    { 0, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE4F08, 0, 180 },
    { 47, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE4EF4, 0, 200 },
    { 47, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE4EA8, 0, 202 },
    { 36, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE4E84, 0, 370 },
    { 47, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE4E70, 0, 420 },
    { 47, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE4E50, 0, 460 },
    { 47, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE4E08, 0, 462 },
    { 0, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE4DE4, 0, 470 },
    { 36, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE4DB4, 0, 500 },
    { 47, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE4D94, 0, 520 },
    { 47, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE4D7C, 0, 670 },
    { 0, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE4D60, 0, 690 },
    { 47, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE4D4C, 0, 795 },
    { 36, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE4D38, 0, 870 },
    { 47, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE4CF0, 0, 890 },
    { 47, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE4CB8, MSG_SCRIPT_FLAG_END, 892 },
};

#include "event_136_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent136Script[18] = {
    { 47, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68E94, 0, 120 },
    { 47, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68EA8, 0, 160 },
    { 0, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68EBC, 0, 180 },
    { 47, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68ED0, 0, 200 },
    { 47, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68EE4, 0, 202 },
    { 36, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68EF8, 0, 370 },
    { 47, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68F0C, 0, 420 },
    { 47, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68F20, 0, 460 },
    { 47, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68F34, 0, 462 },
    { 0, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68F48, 0, 470 },
    { 36, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68F5C, 0, 500 },
    { 47, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68F70, 0, 520 },
    { 47, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68F84, 0, 670 },
    { 0, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68F98, 0, 690 },
    { 47, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68FAC, 0, 795 },
    { 36, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68FC0, 0, 870 },
    { 47, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68FD4, 0, 890 },
    { 47, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68FE8, MSG_SCRIPT_FLAG_END, 892 },
};
#endif

static const EvSoundCue sEvent136SoundCues[4] = {
    { SONG_BGM_WINNIETHEPOOH, 1, 0, 0 },
    { SONG_BG_POO, 2, 0, 0 },
    { SONG_BG_POO, 964, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_WINNIETHEPOOH, 965, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent136Camera[4] = {
    { -65306, 171008, 104704, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -65113, 170752, 109568, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 40, { 0, 0 }, 0 },
    { -64796, 170752, 104704, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 40, { 0, 0 }, 0 },
    { -64537, 184832, 112640, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 40, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent136Track0[11] = {
    { 2, 470, { 0, 0 }, 173568, 106752, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 32, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 2, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 3, 710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 2, 715, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 1, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 2, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 7, 795, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, 0, 0 },
    { 2, 820, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 1, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 2, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent136Track1[20] = {
    { 811, 100, { 0, 0 }, 167168, 110848, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 811, 120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, func_0806ECE0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 811, 125, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 812, 140, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 36, 0, 0 },
    { 811, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 811, 430, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 813, 445, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, 0, 0 },
    { 811, 448, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, 0, 0 },
    { 811, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 811, 463, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 811, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 811, 530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 811, 660, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 811, 750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 811, 770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 810, 810, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 812, 850, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 100, 0, 0 },
    { 810, 852, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 100, 0, 0 },
    { 810, 860, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 811, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent136Track2[15] = {
    { 756, 220, { 0, 0 }, 177664, 104704, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 757, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 782, 280, { 0, 0 }, 0, 0, 0, 192, { 0, 0 }, 68, 0, 0 },
    { 781, 335, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 68, 0, 0 },
    { 756, 345, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 755, 425, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 761, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 756, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 782, 750, { 0, 0 }, 0, 0, 0, 64, { 0, 0 }, 4, 0, 0 },
    { 781, 795, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 4, 0, 0 },
    { 756, 796, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 781, 860, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 4, 0, 0 },
    { 756, 870, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 755, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 755, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaTrack sEvent136Tracks[3] = {
    { sEvent136Track0, 0, { 0, 0, 0 } },
    { sEvent136Track1, 72, { 0, 0, 0 } },
    { sEvent136Track2, 70, { 0, 0, 0 } },
};

const EventSequenceDef gEvent136 = {
    3,
    { 0, 0, 0 },
    sEvent136Tracks,
    sEvent136Camera,
    sEvent136Script,
    sEvent136SoundCues,
    0,
    970,
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
    1,
};

#ifdef VERSION_US
#include "event_137_text.inc"

static const MessageScriptEntry sEvent137Script[16] = {
    { 48, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09009790, 0, 100 },
    { 36, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_090097C2, 0, 120 },
    { 0, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900982E, 0, 140 },
    { 48, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090098A0, 0, 160 },
    { 48, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09009934, 0, 260 },
    { 48, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090099A6, 0, 262 },
    { 48, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09009A3C, 0, 264 },
    { 48, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09009ACC, 0, 266 },
    { 0, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09009B88, 0, 280 },
    { 48, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09009BB0, 0, 300 },
    { 48, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09009C1E, 0, 302 },
    { 36, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09009CC0, 0, 400 },
    { 48, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09009D48, 0, 420 },
    { 36, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09009DD6, 0, 440 },
    { 0, 4, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09009E64, 0, 600 },
    { 48, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09009EC0, MSG_SCRIPT_FLAG_END, 620 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent137Script[16] = {
    { 48, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE5C04, 0, 100 },
    { 36, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE5BD0, 0, 120 },
    { 0, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE5B98, 0, 140 },
    { 48, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE5B48, 0, 160 },
    { 48, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE5B00, 0, 260 },
    { 48, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE5AC0, 0, 262 },
    { 48, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE5A74, 0, 264 },
    { 48, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE5A1C, 0, 266 },
    { 0, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE5A10, 0, 280 },
    { 48, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE59D8, 0, 300 },
    { 48, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE5984, 0, 302 },
    { 36, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE5934, 0, 400 },
    { 48, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE58F8, 0, 420 },
    { 36, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE58B8, 0, 440 },
    { 0, 4, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE5888, 0, 600 },
    { 48, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE5854, MSG_SCRIPT_FLAG_END, 620 },
};

#include "event_137_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent137Script[16] = {
    { 48, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68FFC, 0, 100 },
    { 36, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69010, 0, 120 },
    { 0, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69024, 0, 140 },
    { 48, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69038, 0, 160 },
    { 48, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6904C, 0, 260 },
    { 48, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69060, 0, 262 },
    { 48, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69074, 0, 264 },
    { 48, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69088, 0, 266 },
    { 0, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6909C, 0, 280 },
    { 48, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F690B0, 0, 300 },
    { 48, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F690C4, 0, 302 },
    { 36, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F690D8, 0, 400 },
    { 48, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F690EC, 0, 420 },
    { 36, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69100, 0, 440 },
    { 0, 4, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69114, 0, 600 },
    { 48, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69128, MSG_SCRIPT_FLAG_END, 620 },
};
#endif

static const EvSoundCue sEvent137SoundCues[4] = {
    { SONG_BGM_WINNIETHEPOOH, 0, 0, 0 },
    { SONG_BG_POO, 2, 0, 0 },
    { SONG_BG_POO, 824, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_WINNIETHEPOOH, 825, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent137Camera[1] = {
    { -65226, 237824, 121344, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent137Track0[10] = {
    { 4, 130, { 0, 0 }, 235008, 129536, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 0, 135, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 4, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 0, 175, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 4, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 4, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateQuestionTask },
    { 4, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 34, 290, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 4, 670, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 4, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent137Track1[6] = {
    { 756, 180, { 0, 0 }, 229120, 126464, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 765, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateQuestionTask },
    { 765, 310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 798, 399, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 799, 421, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 800, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent137Track2[6] = {
    { 814, 155, { 0, 0 }, 244736, 121344, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 815, 415, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 815, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 814, 590, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 814, 630, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 815, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaTrack sEvent137Tracks[3] = {
    { sEvent137Track0, 0, { 0, 0, 0 } },
    { sEvent137Track1, 70, { 0, 0, 0 } },
    { sEvent137Track2, 73, { 0, 0, 0 } },
};

const EventSequenceDef gEvent137 = {
    3,
    { 0, 0, 0 },
    sEvent137Tracks,
    sEvent137Camera,
    sEvent137Script,
    sEvent137SoundCues,
    0,
    830,
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
    2,
};

#ifdef VERSION_US
static const MessageScriptEntry sEvent138Script[1] = {
    { 48, 1, 1, 1, { 0, 0, 0 }, (u32)gCardMessageTextUs_0903C186, MSG_SCRIPT_FLAG_END, 150 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent138Script[1] = {
    { 48, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE5FE0, MSG_SCRIPT_FLAG_END, 150 },
};

#include "event_138_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent138Script[1] = {
    { 48, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68354, MSG_SCRIPT_FLAG_END, 150 },
};
#endif

static const EvSoundCue sEvent138SoundCues[2] = {
    { SONG_BGM_WINNIETHEPOOH, 1, 0, 0 },
    { SONG_BG_POO, 2, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent138Camera[1] = {
    { -65226, 237824, 121344, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent138Track0[2] = {
    { 4, 130, { 0, 0 }, 235008, 129536, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 4, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent138Track1[2] = {
    { 756, 180, { 0, 0 }, 229120, 126464, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 756, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent138Track2[3] = {
    { 814, 80, { 0, 0 }, 244736, 121344, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 815, 415, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 815, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaTrack sEvent138Tracks[3] = {
    { sEvent138Track0, 0, { 0, 0, 0 } },
    { sEvent138Track1, 70, { 0, 0, 0 } },
    { sEvent138Track2, 73, { 0, 0, 0 } },
};

const EventSequenceDef gEvent138 = {
    3,
    { 0, 0, 0 },
    sEvent138Tracks,
    sEvent138Camera,
    sEvent138Script,
    sEvent138SoundCues,
    0,
    210,
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
    2,
};

#ifdef VERSION_US
#include "event_139_text.inc"

static const MessageScriptEntry sEvent139Script[12] = {
    { 36, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900A5D8, 0, 100 },
    { 51, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900A654, 0, 130 },
    { 36, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900A6BA, 0, 160 },
    { 51, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900A70E, 0, 190 },
    { 51, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900A75E, 0, 192 },
    { 51, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900A7F6, 0, 194 },
    { 0, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900A822, 0, 225 },
    { 36, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900A862, 0, 255 },
    { 51, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900A8C4, 0, 430 },
    { 0, 4, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900A978, 0, 460 },
    { 51, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900A9EE, 0, 490 },
    { 51, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900AA34, MSG_SCRIPT_FLAG_END, 760 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent139Script[12] = {
    { 36, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE64B8, 0, 100 },
    { 51, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE648C, 0, 130 },
    { 36, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE6458, 0, 160 },
    { 51, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE6418, 0, 190 },
    { 51, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE63D0, 0, 192 },
    { 51, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE63BC, 0, 194 },
    { 0, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE6394, 0, 225 },
    { 36, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE6360, 0, 255 },
    { 51, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE6328, 0, 430 },
    { 0, 4, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE62F4, 0, 460 },
    { 51, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE62DC, 0, 490 },
    { 51, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE62B0, MSG_SCRIPT_FLAG_END, 760 },
};

#include "event_139_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent139Script[12] = {
    { 36, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6913C, 0, 100 },
    { 51, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69150, 0, 130 },
    { 36, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69164, 0, 160 },
    { 51, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69178, 0, 190 },
    { 51, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6918C, 0, 192 },
    { 51, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F691A0, 0, 194 },
    { 0, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F691B4, 0, 225 },
    { 36, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F691C8, 0, 255 },
    { 51, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F691DC, 0, 430 },
    { 0, 4, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F691F0, 0, 460 },
    { 51, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69204, 0, 490 },
    { 51, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69218, MSG_SCRIPT_FLAG_END, 760 },
};
#endif

static const EvSoundCue sEvent139SoundCues[11] = {
    { SONG_BGM_WINNIETHEPOOH, 0, 0, 0 },
    { SONG_BG_POO, 2, 0, 0 },
    { SONG_SYS_LU_JP, 521, 0, 0 },
    { SONG_SYS_LU_JP, 559, 0, 0 },
    { SONG_SYS_LU_JP, 640, 0, 0 },
    { SONG_SYS_LU_JP, 679, 0, 0 },
    { SONG_SYS_LU_JP, 820, 0, 0 },
    { SONG_SYS_LU_JP, 855, 0, 0 },
    { SONG_SYS_LU_JP, 890, 0, 0 },
    { SONG_BG_POO, 914, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_WINNIETHEPOOH, 915, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent139Camera[1] = {
    { -65336, 323328, 177152, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent139Track0[11] = {
    { 4, 220, { 0, 0 }, 316928, 179456, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 36, 440, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 4, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 34, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 4, 530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 3, 535, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 2, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 3, 695, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 4, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 3, 835, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 2, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent139Track1[8] = {
    { 758, 520, { 0, 0 }, 322560, 182784, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 774, 530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 775, 710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 774, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 758, 840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 772, 850, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 757, 860, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 756, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent139Track2[14] = {
    { 816, 270, { 0, 0 }, 327680, 179456, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 816, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 816, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 816, 520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 818, 580, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 100, 0, 0 },
    { 816, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 816, 610, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 817, 640, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 819, 700, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, 0, 0 },
    { 817, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 816, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 816, 820, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 818, 1000, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 100, 0, 0 },
    { 816, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaTrack sEvent139Tracks[3] = {
    { sEvent139Track0, 0, { 0, 0, 0 } },
    { sEvent139Track1, 70, { 0, 0, 0 } },
    { sEvent139Track2, 74, { 0, 0, 0 } },
};

const EventSequenceDef gEvent139 = {
    3,
    { 0, 0, 0 },
    sEvent139Tracks,
    sEvent139Camera,
    sEvent139Script,
    sEvent139SoundCues,
    0,
    920,
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
    3,
};

#ifdef VERSION_US
#include "event_140_text.inc"

static const MessageScriptEntry sEvent140Script[14] = {
    { 36, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900B134, 0, 90 },
    { 50, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900B158, 0, 115 },
    { 36, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900B18C, 0, 160 },
    { 50, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900B1EC, 0, 190 },
    { 36, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900B264, 0, 300 },
    { 36, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900B2D8, 0, 302 },
    { 50, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900B328, 0, 360 },
    { 0, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900B380, 0, 390 },
    { 50, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900B424, 0, 420 },
    { 50, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900B4AA, 0, 422 },
    { 36, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900B50C, 0, 460 },
    { 50, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900B53C, 0, 500 },
    { 0, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900B570, 0, 530 },
    { 50, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900B5D2, MSG_SCRIPT_FLAG_END, 560 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent140Script[14] = {
    { 36, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE6E2C, 0, 90 },
    { 50, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE6E18, 0, 115 },
    { 36, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE6DEC, 0, 160 },
    { 50, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE6DA4, 0, 190 },
    { 36, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE6D78, 0, 300 },
    { 36, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE6D50, 0, 302 },
    { 50, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE6D24, 0, 360 },
    { 0, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE6CCC, 0, 390 },
    { 50, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE6C78, 0, 420 },
    { 50, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE6C48, 0, 422 },
    { 36, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE6C34, 0, 460 },
    { 50, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE6C18, 0, 500 },
    { 0, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE6BE4, 0, 530 },
    { 50, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE6B94, MSG_SCRIPT_FLAG_END, 560 },
};

#include "event_140_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent140Script[14] = {
    { 36, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6922C, 0, 90 },
    { 50, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69240, 0, 115 },
    { 36, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69254, 0, 160 },
    { 50, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69268, 0, 190 },
    { 36, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6927C, 0, 300 },
    { 36, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69290, 0, 302 },
    { 50, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F692A4, 0, 360 },
    { 0, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F692B8, 0, 390 },
    { 50, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F692CC, 0, 420 },
    { 50, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F692E0, 0, 422 },
    { 36, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F692F4, 0, 460 },
    { 50, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69308, 0, 500 },
    { 0, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6931C, 0, 530 },
    { 50, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69330, MSG_SCRIPT_FLAG_END, 560 },
};
#endif

static const EvSoundCue sEvent140SoundCues[4] = {
    { SONG_BGM_WINNIETHEPOOH, 1, 0, 0 },
    { SONG_BG_POO, 2, 0, 0 },
    { SONG_BG_POO, 614, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_WINNIETHEPOOH, 615, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent140Camera[1] = {
    { -64537, 529664, 289536, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent140Track0[5] = {
    { 4, 385, { 0, 0 }, 536064, 294144, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 36, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 4, 525, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 27, 532, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 4, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent140Track1[5] = {
    { 802, 125, { 0, 0 }, 530432, 286720, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 803, 149, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 804, 200, { 0, 0 }, 529664, 287232, 0, 0, { 0, 0 }, 258, 0, 0 },
    { 797, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, 0, 0 },
    { 756, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent140Track2[4] = {
    { 821, 330, { 0, 0 }, 521472, 292352, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 820, 430, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 821, 470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 820, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent140Track3[2] = {
    { 808, 150, { 0, 0 }, 526848, 313856, -2560, 0, { 0, 0 }, 2, 0, 0 },
    { 808, 500, { 0, 0 }, 494592, 295424, -2560, 808, { 0, 0 }, 32771, 0, 0 },
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
    0,
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

#ifdef VERSION_US
#include "event_141_text.inc"

static const MessageScriptEntry sEvent141Script[15] = {
    { 59, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900BA90, 0, 210 },
    { 36, 1, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900BAF2, 0, 240 },
    { 59, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900BB44, 0, 270 },
    { 0, 3, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900BBC0, 0, 370 },
    { 59, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900BBE4, 0, 410 },
    { 59, 2, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900BC78, 0, 414 },
    { 59, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900BCF4, 0, 418 },
    { 0, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900BD56, 0, 450 },
    { 59, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900BDCE, 0, 480 },
    { 59, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900BE4A, 0, 484 },
    { 59, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900BE60, 0, 870 },
    { 0, 1, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900BE7E, 0, 900 },
    { 59, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900BEBA, 0, 930 },
    { 59, 2, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900BEF4, 0, 934 },
    { 36, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900BF9A, MSG_SCRIPT_FLAG_END, 1270 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent141Script[15] = {
    { 59, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE7530, 0, 210 },
    { 36, 1, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE74F8, 0, 240 },
    { 59, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE74A0, 0, 270 },
    { 0, 3, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE7490, 0, 370 },
    { 59, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE7440, 0, 410 },
    { 59, 2, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE73FC, 0, 414 },
    { 59, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE73C8, 0, 418 },
    { 0, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE7380, 0, 450 },
    { 59, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE7330, 0, 480 },
    { 59, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE7324, 0, 484 },
    { 59, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE7310, 0, 870 },
    { 0, 1, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE72F8, 0, 900 },
    { 59, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE72D8, 0, 930 },
    { 59, 2, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE7294, 0, 934 },
    { 36, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE7274, MSG_SCRIPT_FLAG_END, 1270 },
};

#include "event_141_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent141Script[15] = {
    { 59, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69344, 0, 210 },
    { 36, 1, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69358, 0, 240 },
    { 59, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6936C, 0, 270 },
    { 0, 3, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69380, 0, 370 },
    { 59, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69394, 0, 410 },
    { 59, 2, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F693A8, 0, 414 },
    { 59, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F693BC, 0, 418 },
    { 0, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F693D0, 0, 450 },
    { 59, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F693E4, 0, 480 },
    { 59, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F693F8, 0, 484 },
    { 59, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6940C, 0, 870 },
    { 0, 1, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69420, 0, 900 },
    { 59, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69434, 0, 930 },
    { 59, 2, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69448, 0, 934 },
    { 36, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6945C, MSG_SCRIPT_FLAG_END, 1270 },
};
#endif

static const EvSoundCue sEvent141SoundCues[14] = {
    { SONG_BGM_WINNIETHEPOOH, 1, 0, 0 },
    { SONG_BG_POO, 2, 0, 0 },
    { SONG_SYS_TIGGER_JP, 524, 0, 0 },
    { SONG_SYS_TIGGER_JP, 573, 0, 0 },
    { SONG_SYS_TIGGER_JP, 609, 0, 0 },
    { SONG_SYS_TIGGER_JP, 645, 0, 0 },
    { SONG_SYS_TIGGER_JP, 681, 0, 0 },
    { SONG_SYS_TIGGER_JP, 717, 0, 0 },
    { SONG_SYS_TIGGER_JP, 753, 0, 0 },
    { SONG_SYS_TIGGER_JP, 788, 0, 0 },
    { SONG_SND_961, 1015, 0, 0 },
    { SONG_SND_961, 1050, 0, 0 },
    { SONG_BG_POO, 1294, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_WINNIETHEPOOH, 1295, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent141Camera[7] = {
    { -65486, 588288, 323840, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -65036, 582144, 319232, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, 0 },
    { -64986, 582144, 307200, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, 0 },
    { -64914, 588288, 312320, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 36, { 0, 0 }, 0 },
    { -64842, 590592, 307200, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 72, { 0, 0 }, 0 },
    { -64516, 588288, 318720, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 72, { 0, 0 }, 0 },
    { -63536, 592896, 327424, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 70, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent141Track0[13] = {
    { 4, 160, { 0, 0 }, 580864, 329984, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 0, 165, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 4, 290, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 4, 340, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateQuestionTask },
    { 4, 445, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 30, 452, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 4, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 0, 580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 4, 895, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 36, 925, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 4, 970, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 3, 980, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 2, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent141Track1[32] = {
    { 822, 10, { 0, 0 }, 551680, 306688, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 833, 180, { 0, 0 }, 574720, 322048, 0, 822, { 0, 0 }, 67, 0, 0 },
    { 822, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 826, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 823, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 830, 546, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 85, 0, 0 },
    { 831, 549, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 85, 0, 0 },
    { 831, 579, { 0, 0 }, 583680, 315648, 0, 0, { 0, 0 }, 4435, _0806E9DC, 0 },
    { 831, 582, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 341, 0, 0 },
    { 827, 585, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 341, 0, 0 },
    { 827, 615, { 0, 0 }, 593152, 321024, 0, 0, { 0, 0 }, 4435, _0806E9DC, 0 },
    { 827, 618, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 341, 0, 0 },
    { 831, 621, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 341, 0, 0 },
    { 831, 651, { 0, 0 }, 602368, 316160, 0, 0, { 0, 0 }, 4435, _0806E9DC, 0 },
    { 831, 654, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 341, 0, 0 },
    { 831, 657, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 277, 0, 0 },
    { 831, 687, { 0, 0 }, 592896, 311040, 0, 0, { 0, 0 }, 4371, _0806E9DC, 0 },
    { 831, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 277, 0, 0 },
    { 827, 693, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 277, 0, 0 },
    { 827, 723, { 0, 0 }, 583680, 315648, 0, 0, { 0, 0 }, 4371, _0806E9DC, 0 },
    { 827, 726, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 277, 0, 0 },
    { 827, 729, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 341, 0, 0 },
    { 827, 759, { 0, 0 }, 593152, 321024, 0, 0, { 0, 0 }, 4435, _0806E9DC, 0 },
    { 827, 762, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 341, 0, 0 },
    { 828, 853, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 277, 0, 0 },
    { 832, 872, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 277, 0, 0 },
    { 834, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 277, 0, 0 },
    { 822, 950, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 277, 0, 0 },
    { 822, 980, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 341, 0, 0 },
    { 824, 990, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 372, 0, 0 },
    { 824, 1150, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 116, 0, 0 },
    { 822, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98309, 0, 0 },
};

static const EventCharaKeyframe sEvent141Track2[13] = {
    { 756, 155, { 0, 0 }, 590080, 328960, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 765, 165, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 758, 580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 773, 620, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 758, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 772, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 758, 980, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 757, 1090, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 757, 1110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 782, 1190, { 0, 0 }, 0, 0, 0, 64, { 0, 0 }, 4, 0, 0 },
    { 757, 1200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 756, 1230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 795, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33093, 0, 0 },
};

static const EventCharaTrack sEvent141Tracks[3] = {
    { sEvent141Track0, 0, { 0, 0, 0 } },
    { sEvent141Track1, 76, { 0, 0, 0 } },
    { sEvent141Track2, 70, { 0, 0, 0 } },
};

const EventSequenceDef gEvent141 = {
    3,
    { 0, 0, 0 },
    sEvent141Tracks,
    sEvent141Camera,
    sEvent141Script,
    sEvent141SoundCues,
    0,
    1300,
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
    5,
};

#ifdef VERSION_US
#include "event_142_text.inc"

static const MessageScriptEntry sEvent142Script[21] = {
    { 0, 7, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900CB18, 0, 100 },
    { 36, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900CB60, 0, 150 },
    { 0, 7, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900CB84, 0, 290 },
    { 49, 2, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900CBD4, 0, 340 },
    { 36, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900CBE6, 0, 530 },
    { 49, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900CC2E, 0, 560 },
    { 0, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900CC84, 0, 600 },
    { 49, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900CCB6, 0, 830 },
    { 49, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900CD3C, 0, 847 },
    { 36, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900CDFA, 0, 880 },
    { 0, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900CE96, 0, 910 },
    { 49, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900CEE0, 0, 940 },
    { 49, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900CF78, 0, 1035 },
    { 36, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900CFCC, 0, 1060 },
    { 0, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900D000, 0, 1085 },
    { 36, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900D08E, 0, 1160 },
    { 49, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900D0EA, 0, 1190 },
    { 49, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900D15E, 0, 1300 },
    { 0, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900D1EA, 0, 1330 },
    { 49, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900D25A, 0, 1360 },
    { 0, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900D298, MSG_SCRIPT_FLAG_END, 1390 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent142Script[21] = {
    { 0, 7, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8474, 0, 100 },
    { 36, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8460, 0, 150 },
    { 0, 7, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8430, 0, 290 },
    { 49, 2, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8424, 0, 340 },
    { 36, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8404, 0, 530 },
    { 49, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE83D0, 0, 560 },
    { 0, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE83B4, 0, 600 },
    { 49, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8370, 0, 830 },
    { 49, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8320, 0, 847 },
    { 36, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE82F4, 0, 880 },
    { 0, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE82D8, 0, 910 },
    { 49, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE828C, 0, 940 },
    { 49, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE825C, 0, 1035 },
    { 36, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8248, 0, 1060 },
    { 0, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8208, 0, 1085 },
    { 36, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE81E0, 0, 1160 },
    { 49, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE819C, 0, 1190 },
    { 49, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8178, 0, 1300 },
    { 0, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE814C, 0, 1330 },
    { 49, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8138, 0, 1360 },
    { 0, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8124, MSG_SCRIPT_FLAG_END, 1390 },
};

#include "event_142_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent142Script[21] = {
    { 0, 7, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69470, 0, 100 },
    { 36, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69484, 0, 150 },
    { 0, 7, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69498, 0, 290 },
    { 49, 2, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F694AC, 0, 340 },
    { 36, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F694C0, 0, 530 },
    { 49, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F694D4, 0, 560 },
    { 0, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F694E8, 0, 600 },
    { 49, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F694FC, 0, 830 },
    { 49, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69510, 0, 847 },
    { 36, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69524, 0, 880 },
    { 0, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69538, 0, 910 },
    { 49, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6954C, 0, 940 },
    { 49, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69560, 0, 1035 },
    { 36, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69574, 0, 1060 },
    { 0, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69588, 0, 1085 },
    { 36, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6959C, 0, 1160 },
    { 49, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F695B0, 0, 1190 },
    { 49, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F695C4, 0, 1300 },
    { 0, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F695D8, 0, 1330 },
    { 49, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F695EC, 0, 1360 },
    { 0, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69600, MSG_SCRIPT_FLAG_END, 1390 },
};
#endif

static const EvSoundCue sEvent142SoundCues[4] = {
    { SONG_BGM_WINNIETHEPOOH, 1, 0, 0 },
    { SONG_BG_POO, 2, 0, 0 },
    { SONG_BG_POO, 1444, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_WINNIETHEPOOH, 1445, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent142Camera[4] = {
    { -65146, 680192, 359424, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -64916, 675840, 353280, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, 0 },
    { -64796, 683264, 353280, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, 0 },
    { -63536, 681728, 356352, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 50, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent142Track0[25] = {
    { 4, 110, { 0, 0 }, 675584, 361728, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 3, 115, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 2, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 3, 255, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 4, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 34, 345, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 4, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 0, 365, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 4, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 0, 575, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 4, 905, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 34, 960, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 27, 970, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 27, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 27, 1065, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 4, 1070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 3, 1075, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 2, 1080, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 31, 1090, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 2, 1200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 3, 1205, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 4, 1325, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 36, 1370, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 27, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 4, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent142Track1[14] = {
    { 835, 390, { 0, 0 }, 651520, 336384, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 837, 450, { 0, 0 }, 668416, 347136, 0, 835, { 0, 0 }, 67, 0, 0 },
    { 835, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 835, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 835, 740, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 837, 790, { 0, 0 }, 692224, 357632, 0, 835, { 0, 0 }, 67, 0, 0 },
    { 835, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 838, 832, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 835, 845, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 835, 1095, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 835, 1145, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateQuestionTask },
    { 835, 1240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 836, 1260, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, 0, 0 },
    { 835, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent142Track2[11] = {
    { 796, 160, { 0, 0 }, 683520, 366336, 0, 0, { 0, 0 }, 322, 0, 0 },
    { 797, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, 0, 0 },
    { 757, 310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 758, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 772, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 777, 390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 758, 770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 772, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 778, 790, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 758, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 758, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaTrack sEvent142Tracks[3] = {
    { sEvent142Track0, 0, { 0, 0, 0 } },
    { sEvent142Track1, 77, { 0, 0, 0 } },
    { sEvent142Track2, 70, { 0, 0, 0 } },
};

const EventSequenceDef gEvent142 = {
    3,
    { 0, 0, 0 },
    sEvent142Tracks,
    sEvent142Camera,
    sEvent142Script,
    sEvent142SoundCues,
    0,
    1450,
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
    6,
};

#ifdef VERSION_US
#include "event_143_text.inc"

static const MessageScriptEntry sEvent143Script[16] = {
    { 0, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900DC98, 0, 250 },
    { 0, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900DCDA, 0, 300 },
    { 36, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900DD74, 0, 330 },
    { 36, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900DDFE, 0, 350 },
    { 36, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900DE6E, 0, 500 },
    { 0, 4, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900DEDA, 0, 670 },
    { 36, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900DF10, 0, 700 },
    { 0, 4, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900DF3A, 0, 730 },
    { 36, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900DF8A, 0, 760 },
    { 0, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900DFE4, 0, 900 },
    { 36, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900E06A, 0, 950 },
    { 0, 4, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900E09E, 0, 980 },
    { 0, 5, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900E0F8, 0, 1100 },
    { 36, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900E11E, 0, 1190 },
    { 36, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900E16E, 0, 1192 },
    { 0, 4, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900E1C8, MSG_SCRIPT_FLAG_END, 1240 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent143Script[16] = {
    { 0, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE9070, 0, 250 },
    { 0, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE903C, 0, 300 },
    { 36, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE9008, 0, 330 },
    { 36, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8FD8, 0, 350 },
    { 36, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8FBC, 0, 500 },
    { 0, 4, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8FA0, 0, 670 },
    { 36, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8F94, 0, 700 },
    { 0, 4, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8F78, 0, 730 },
    { 36, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8F30, 0, 760 },
    { 0, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8F04, 0, 900 },
    { 36, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8EE4, 0, 950 },
    { 0, 4, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8EA8, 0, 980 },
    { 0, 5, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8E88, 0, 1100 },
    { 36, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8E64, 0, 1190 },
    { 36, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8E1C, 0, 1192 },
    { 0, 4, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8E04, MSG_SCRIPT_FLAG_END, 1240 },
};

#include "event_143_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent143Script[16] = {
    { 0, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68DF4, 0, 250 },
    { 0, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68E08, 0, 300 },
    { 36, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68E1C, 0, 330 },
    { 36, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68E30, 0, 350 },
    { 36, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68E44, 0, 500 },
    { 0, 4, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68E58, 0, 670 },
    { 36, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68E6C, 0, 700 },
    { 0, 4, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68E80, 0, 730 },
    { 36, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68D40, 0, 760 },
    { 0, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68D54, 0, 900 },
    { 36, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68D68, 0, 950 },
    { 0, 4, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68D7C, 0, 980 },
    { 0, 5, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68D90, 0, 1100 },
    { 36, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68DA4, 0, 1190 },
    { 36, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68DB8, 0, 1192 },
    { 0, 4, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68DCC, MSG_SCRIPT_FLAG_END, 1240 },
};
#endif

static const EvSoundCue sEvent143SoundCues[6] = {
    { SONG_BGM_WINNIETHEPOOH, 1, 0, 0 },
    { SONG_BG_POO, 2, 0, 0 },
    { SONG_BGM_WINNIETHEPOOH, 725, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT4, 755, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BG_POO, 1294, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT4, 1295, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent143Camera[1] = {
    { -64537, 790528, 416512, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent143Track0[17] = {
    { 2, 1, { 0, 0 }, 772096, 412160, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 7, 100, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, 0, 0 },
    { 2, 110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 3, 120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 4, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 3, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 2, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 1, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 2, 260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 3, 265, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 4, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 4, 640, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 4, 990, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 4, 1040, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 4, 1050, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 16, 1220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 4, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent143Track1[8] = {
    { 756, 1, { 0, 0 }, 757248, 404224, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 781, 230, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 4, 0, 0 },
    { 756, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 795, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, 0, 0 },
    { 804, 770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, 0, 0 },
    { 797, 1130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, 0, 0 },
    { 781, 1160, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 4, 0, 0 },
    { 756, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaTrack sEvent143Tracks[2] = {
    { sEvent143Track0, 0, { 0, 0, 0 } },
    { sEvent143Track1, 70, { 0, 0, 0 } },
};

const EventSequenceDef gEvent143 = {
    2,
    { 0, 0, 0 },
    sEvent143Tracks,
    sEvent143Camera,
    sEvent143Script,
    sEvent143SoundCues,
    0,
    1300,
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
    7,
};

#ifdef VERSION_US
static const MessageScriptEntry sEvent144Script[8] = {
    { 0, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900DC98, 0, 250 },
    { 0, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900DCDA, 0, 300 },
    { 36, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900DD74, 0, 330 },
    { 36, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900DDFE, 0, 350 },
    { 36, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900DE6E, 0, 500 },
    { 0, 4, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900DEDA, 0, 670 },
    { 36, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900DF10, 0, 700 },
    { 0, 4, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900DF3A, MSG_SCRIPT_FLAG_END, 730 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent144Script[8] = {
    { 0, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE9070, 0, 250 },
    { 0, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE903C, 0, 300 },
    { 36, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE9008, 0, 330 },
    { 36, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8FD8, 0, 350 },
    { 36, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8FBC, 0, 500 },
    { 0, 4, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8FA0, 0, 670 },
    { 36, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8F94, 0, 700 },
    { 0, 4, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8F78, MSG_SCRIPT_FLAG_END, 730 },
};
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent144Script[8] = {
    { 0, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68DF4, 0, 250 },
    { 0, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68E08, 0, 300 },
    { 36, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68E1C, 0, 330 },
    { 36, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68E30, 0, 350 },
    { 36, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68E44, 0, 500 },
    { 0, 4, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68E58, 0, 670 },
    { 36, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68E6C, 0, 700 },
    { 0, 4, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68E80, MSG_SCRIPT_FLAG_END, 730 },
};
#endif

static const EvSoundCue sEvent144SoundCues[4] = {
    { SONG_BGM_WINNIETHEPOOH, 0, 0, 0 },
    { SONG_BG_POO, 2, 0, 0 },
    { SONG_BG_POO, 784, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_WINNIETHEPOOH, 785, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent144Camera[1] = {
    { -64537, 790528, 416512, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent144Track0[13] = {
    { 2, 1, { 0, 0 }, 772096, 412160, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 7, 100, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, 0, 0 },
    { 2, 110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 3, 120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 4, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 3, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 2, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 1, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 2, 260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 3, 265, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 4, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 4, 640, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 4, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent144Track1[6] = {
    { 756, 1, { 0, 0 }, 757248, 404224, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 781, 230, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 4, 0, 0 },
    { 756, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 795, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, 0, 0 },
    { 804, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, 0, 0 },
    { 804, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33093, 0, 0 },
};

static const EventCharaTrack sEvent144Tracks[2] = {
    { sEvent144Track0, 0, { 0, 0, 0 } },
    { sEvent144Track1, 70, { 0, 0, 0 } },
};

const EventSequenceDef gEvent144 = {
    2,
    { 0, 0, 0 },
    sEvent144Tracks,
    sEvent144Camera,
    sEvent144Script,
    sEvent144SoundCues,
    0,
    790,
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
    7,
};

#ifdef VERSION_US
static const MessageScriptEntry sEvent145Script[10] = {
    { 36, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900EF6C, 0, 400 },
    { 0, 4, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900F026, 0, 430 },
    { 36, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900DF8A, 0, 460 },
    { 0, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900DFE4, 0, 600 },
    { 36, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900E06A, 0, 650 },
    { 0, 4, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900E09E, 0, 680 },
    { 0, 5, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900E0F8, 0, 800 },
    { 36, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900E11E, 0, 890 },
    { 36, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900E16E, 0, 892 },
    { 0, 4, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900E1C8, MSG_SCRIPT_FLAG_END, 940 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent145Script[10] = {
    { 36, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE99B0, 0, 400 },
    { 0, 4, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE9978, 0, 430 },
    { 36, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8F30, 0, 460 },
    { 0, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8F04, 0, 600 },
    { 36, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8EE4, 0, 650 },
    { 0, 4, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8EA8, 0, 680 },
    { 0, 5, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8E88, 0, 800 },
    { 36, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8E64, 0, 890 },
    { 36, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8E1C, 0, 892 },
    { 0, 4, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8E04, MSG_SCRIPT_FLAG_END, 940 },
};

#include "event_145_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent145Script[10] = {
    { 36, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68CC8, 0, 400 },
    { 0, 4, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68CDC, 0, 430 },
    { 36, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68D40, 0, 460 },
    { 0, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68D54, 0, 600 },
    { 36, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68D68, 0, 650 },
    { 0, 4, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68D7C, 0, 680 },
    { 0, 5, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68D90, 0, 800 },
    { 36, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68DA4, 0, 890 },
    { 36, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68DB8, 0, 892 },
    { 0, 4, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68DCC, MSG_SCRIPT_FLAG_END, 940 },
};
#endif

static const EvSoundCue sEvent145SoundCues[6] = {
    { SONG_BGM_WINNIETHEPOOH, 1, 0, 0 },
    { SONG_BG_POO, 2, 0, 0 },
    { SONG_BGM_WINNIETHEPOOH, 425, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT4, 455, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BG_POO, 994, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT4, 995, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent145Camera[1] = {
    { -64537, 790528, 416512, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent145Track0[11] = {
    { 2, 1, { 0, 0 }, 772096, 412160, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 7, 100, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, 0, 0 },
    { 2, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 1, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 2, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 3, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 4, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 4, 740, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 4, 750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 16, 920, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 4, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent145Track1[7] = {
    { 756, 1, { 0, 0 }, 757248, 404224, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 781, 230, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 4, 0, 0 },
    { 756, 240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 795, 470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, 0, 0 },
    { 797, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, 0, 0 },
    { 781, 860, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 4, 0, 0 },
    { 756, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaTrack sEvent145Tracks[2] = {
    { sEvent145Track0, 0, { 0, 0, 0 } },
    { sEvent145Track1, 70, { 0, 0, 0 } },
};

const EventSequenceDef gEvent145 = {
    2,
    { 0, 0, 0 },
    sEvent145Tracks,
    sEvent145Camera,
    sEvent145Script,
    sEvent145SoundCues,
    0,
    1000,
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
    7,
};

#ifdef VERSION_US
#include "event_145_text.inc"

static const MessageScriptEntry sEvent146Script[2] = {
    { 36, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900EF6C, 0, 400 },
    { 0, 4, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900F026, MSG_SCRIPT_FLAG_END, 430 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent146Script[2] = {
    { 36, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE99B0, 0, 400 },
    { 0, 4, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE9978, MSG_SCRIPT_FLAG_END, 430 },
};
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent146Script[2] = {
    { 36, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68CC8, 0, 400 },
    { 0, 4, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68CDC, MSG_SCRIPT_FLAG_END, 430 },
};
#endif

static const EvSoundCue sEvent146SoundCues[4] = {
    { SONG_BGM_WINNIETHEPOOH, 1, 0, 0 },
    { SONG_BG_POO, 2, 0, 0 },
    { SONG_BG_POO, 484, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_WINNIETHEPOOH, 485, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent146Camera[1] = {
    { -64537, 790528, 416512, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent146Track0[8] = {
    { 2, 1, { 0, 0 }, 772096, 412160, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 7, 100, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, 0, 0 },
    { 2, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 1, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 2, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 3, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 4, 190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 4, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent146Track1[5] = {
    { 756, 1, { 0, 0 }, 757248, 404224, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 781, 230, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 4, 0, 0 },
    { 756, 240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 795, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, 0, 0 },
    { 796, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33093, 0, 0 },
};

static const EventCharaTrack sEvent146Tracks[2] = {
    { sEvent146Track0, 0, { 0, 0, 0 } },
    { sEvent146Track1, 70, { 0, 0, 0 } },
};

const EventSequenceDef gEvent146 = {
    2,
    { 0, 0, 0 },
    sEvent146Tracks,
    sEvent146Camera,
    sEvent146Script,
    sEvent146SoundCues,
    0,
    490,
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
    7,
};

#ifdef VERSION_US
#include "event_147_text.inc"

static const MessageScriptEntry sEvent147Script[6] = {
    { 36, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900EF6C, 0, 400 },
    { 0, 4, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900F026, 0, 430 },
    { 36, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900F32C, 0, 560 },
    { 0, 4, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900F376, 0, 590 },
    { 36, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900F3DA, 0, 620 },
    { 36, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900F3FC, MSG_SCRIPT_FLAG_END, 622 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent147Script[6] = {
    { 36, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE99B0, 0, 400 },
    { 0, 4, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE9978, 0, 430 },
    { 36, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEA080, 0, 560 },
    { 0, 4, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEA068, 0, 590 },
    { 36, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08F9584C, 0, 620 },
    { 36, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEA01C, MSG_SCRIPT_FLAG_END, 622 },
};

#include "event_147_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent147Script[6] = {
    { 36, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68CC8, 0, 400 },
    { 0, 4, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68CDC, 0, 430 },
    { 36, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68CF0, 0, 560 },
    { 0, 4, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68D04, 0, 590 },
    { 36, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68D18, 0, 620 },
    { 36, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68D2C, MSG_SCRIPT_FLAG_END, 622 },
};
#endif

static const EvSoundCue sEvent147SoundCues[6] = {
    { SONG_BGM_WINNIETHEPOOH, 0, 0, 0 },
    { SONG_BG_POO, 2, 0, 0 },
    { SONG_BGM_WINNIETHEPOOH, 425, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT4, 555, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BG_POO, 674, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT4, 675, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent147Camera[1] = {
    { -64537, 790528, 416512, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent147Track0[8] = {
    { 2, 1, { 0, 0 }, 772096, 412160, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 7, 100, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, 0, 0 },
    { 2, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 1, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 2, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 3, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 4, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 4, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent147Track1[6] = {
    { 756, 1, { 0, 0 }, 757248, 404224, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 781, 230, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 4, 0, 0 },
    { 756, 240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 795, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, 0, 0 },
    { 797, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, 0, 0 },
    { 756, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaTrack sEvent147Tracks[2] = {
    { sEvent147Track0, 0, { 0, 0, 0 } },
    { sEvent147Track1, 70, { 0, 0, 0 } },
};

const EventSequenceDef gEvent147 = {
    2,
    { 0, 0, 0 },
    sEvent147Tracks,
    sEvent147Camera,
    sEvent147Script,
    sEvent147SoundCues,
    0,
    680,
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
    7,
};

#ifdef VERSION_US
#include "event_148_text.inc"

static const MessageScriptEntry sEvent148Script[1] = {
    { 0, 7, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900F7A8, MSG_SCRIPT_FLAG_END, 150 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent148Script[1] = {
    { 0, 7, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEA340, MSG_SCRIPT_FLAG_END, 150 },
};

#include "event_148_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent148Script[1] = {
    { 0, 7, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F68DE0, MSG_SCRIPT_FLAG_END, 150 },
};
#endif

static const EvSoundCue sEvent148SoundCues[1] = {
    { 65535, 0, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent148Camera[1] = {
    { -64537, 790528, 416512, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent148Track0[6] = {
    { 2, 80, { 0, 0 }, 790528, 419840, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 1, 90, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 2, 100, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 3, 110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 4, 120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 4, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaTrack sEvent148Tracks[1] = {
    { sEvent148Track0, 0, { 0, 0, 0 } },
};

const EventSequenceDef gEvent148 = {
    1,
    { 0, 0, 0 },
    sEvent148Tracks,
    sEvent148Camera,
    sEvent148Script,
    sEvent148SoundCues,
    0,
    210,
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
    7,
};

#ifdef VERSION_US
#include "event_149_text.inc"

static const MessageScriptEntry sEvent149Script[19] = {
    { 26, 5, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900F968, 0, 250 },
    { 26, 5, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900F974, 0, 400 },
    { 52, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900F998, MSG_SCRIPT_FLAG_SILHOUETTE, 440 },
    { 26, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900F9A8, 0, 590 },
    { 52, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900F9C4, MSG_SCRIPT_FLAG_SILHOUETTE, 690 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900FA0E, 0, 720 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900FA2A, 0, 880 },
    { 26, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900FAD8, 0, 1050 },
    { 52, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900FB0E, MSG_SCRIPT_FLAG_SILHOUETTE, 1090 },
    { 52, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900FBA6, MSG_SCRIPT_FLAG_SILHOUETTE, 1092 },
    { 26, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900FC88, 0, 1120 },
    { 52, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900FCEC, MSG_SCRIPT_FLAG_SILHOUETTE, 1160 },
    { 52, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900FD1C, MSG_SCRIPT_FLAG_SILHOUETTE, 1370 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900FDA4, 0, 1590 },
    { 52, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900FDC4, MSG_SCRIPT_FLAG_SILHOUETTE, 1630 },
    { 52, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900FE9E, MSG_SCRIPT_FLAG_SILHOUETTE, 1632 },
    { 52, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900FF20, MSG_SCRIPT_FLAG_SILHOUETTE, 1730 },
    { 26, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0900FF94, 0, 2020 },
    { 52, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901000C, MSG_SCRIPT_FLAG_SILHOUETTE | MSG_SCRIPT_FLAG_END, 2060 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent149Script[19] = {
    { 26, 5, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEA9A0, 0, 250 },
    { 26, 5, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEA984, 0, 400 },
    { 52, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEA970, MSG_SCRIPT_FLAG_SILHOUETTE, 440 },
    { 26, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FA7110, 0, 590 },
    { 52, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEA938, MSG_SCRIPT_FLAG_SILHOUETTE, 690 },
    { 26, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEA920, 0, 720 },
    { 26, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEA8DC, 0, 880 },
    { 26, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEA8C4, 0, 1050 },
    { 52, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEA874, MSG_SCRIPT_FLAG_SILHOUETTE, 1090 },
    { 52, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEA81C, MSG_SCRIPT_FLAG_SILHOUETTE, 1092 },
    { 26, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEA7E8, 0, 1120 },
    { 52, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEA7D4, MSG_SCRIPT_FLAG_SILHOUETTE, 1160 },
    { 52, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEA788, MSG_SCRIPT_FLAG_SILHOUETTE, 1370 },
    { 26, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEA774, 0, 1590 },
    { 52, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEA724, MSG_SCRIPT_FLAG_SILHOUETTE, 1630 },
    { 52, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEA6DC, MSG_SCRIPT_FLAG_SILHOUETTE, 1632 },
    { 52, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEA6B0, MSG_SCRIPT_FLAG_SILHOUETTE, 1730 },
    { 26, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEA680, 0, 2020 },
    { 52, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEA664, MSG_SCRIPT_FLAG_SILHOUETTE | MSG_SCRIPT_FLAG_END, 2060 },
};

#include "event_149_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent149Script[19] = {
    { 26, 5, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A668, 0, 250 },
    { 26, 5, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A67C, 0, 400 },
    { 52, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A690, MSG_SCRIPT_FLAG_SILHOUETTE, 440 },
    { 26, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A6A4, 0, 590 },
    { 52, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A6B8, MSG_SCRIPT_FLAG_SILHOUETTE, 690 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A6CC, 0, 720 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A6E0, 0, 880 },
    { 26, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A6F4, 0, 1050 },
    { 52, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A708, MSG_SCRIPT_FLAG_SILHOUETTE, 1090 },
    { 52, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A71C, MSG_SCRIPT_FLAG_SILHOUETTE, 1092 },
    { 26, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A730, 0, 1120 },
    { 52, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A744, MSG_SCRIPT_FLAG_SILHOUETTE, 1160 },
    { 52, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A758, MSG_SCRIPT_FLAG_SILHOUETTE, 1370 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A76C, 0, 1590 },
    { 52, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A780, MSG_SCRIPT_FLAG_SILHOUETTE, 1630 },
    { 52, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A794, MSG_SCRIPT_FLAG_SILHOUETTE, 1632 },
    { 52, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A7A8, MSG_SCRIPT_FLAG_SILHOUETTE, 1730 },
    { 26, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A7BC, 0, 2020 },
    { 52, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A7D0, MSG_SCRIPT_FLAG_SILHOUETTE | MSG_SCRIPT_FLAG_END, 2060 },
};
#endif

static const EvSoundCue sEvent149SoundCues[5] = {
    { 65535, 0, 0, 0 },
    { SONG_EV_FLASH01, 2100, 0, 0 },
    { SONG_EV_FLASH01, 2120, 0, 0 },
    { SONG_EV_FLASH01, 2130, 0, 0 },
    { SONG_EV_FLASH02, 2220, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent149Camera[13] = {
    { -65456, 32256, 98816, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -65436, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_BLACK | CAMERA_MODE_KEEP, 10, { 0, 0 }, 0 },
    { -65356, 32256, 41216, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 1, { 0, 0 }, 0 },
    { -65306, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_BLACK | CAMERA_MODE_KEEP, 60, { 0, 0 }, 0 },
    { -65236, 32256, 41216, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 1, { 0, 0 }, 0 },
    { -64986, 32256, 36096, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, 0 },
    { -64371, 32256, 32512, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 30, { 0, 0 }, 0 },
    { -63436, 32256, 29952, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, 0 },
    { -63416, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 10, { 0, 0 }, 0 },
    { -63406, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 10, { 0, 0 }, 0 },
    { -63386, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 10, { 0, 0 }, 0 },
    { -63316, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -63136, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_KEYFRAME_FLAG_END | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 50, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent149Track0[26] = {
    { 547, 300, { 0, 0 }, 29696, 39424, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 545, 460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 545, 530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 546, 552, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 820, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 870, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 514, 875, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 526, 882, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 1030, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 514, 1115, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 524, 1165, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 1285, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 1335, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 514, 1450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 1510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 1520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 1550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 1750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 530, 1880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 515, 1930, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 518, 1950, { 0, 0 }, 35584, 37376, 0, 515, { 0, 0 }, 67, 0, 0 },
    { 515, 1990, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 558, 2150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 558, 2200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 558, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent149Track1[8] = {
    { 921, 1164, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8258, 0, 0 },
    { 921, 1165, { 0, 0 }, 25088, 8448, 0, 0, { 0, 0 }, 16450, 0, 0 },
    { 921, 1265, { 0, 0 }, 25088, 24832, 0, 921, { 0, 0 }, 339, 0, 0 },
    { 921, 1400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 469, 0, 0 },
    { 921, 1650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 336, func_0806F610, 0 },
    { 921, 1700, { 0, 0 }, 39680, 22528, 0, 921, { 0, 0 }, 339, 0, 0 },
    { 921, 2230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 469, 0, 0 },
    { 921, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98370, 0, 0 },
};

static const EventCharaKeyframe sEvent149Track2[5] = {
    { 591, 1960, { 0, 0 }, 256000, 0, 0, 0, { 0, 0 }, 322, 0, 0 },
    { 591, 1961, { 0, 0 }, 39680, 22272, 0, 0, { 0, 0 }, 322, 0, 0 },
    { 592, 2004, { 0, 0 }, 39680, 28672, 0, 591, { 0, 0 }, 323, 0, 0 },
    { 603, 2900, { 0, 0 }, 35584, 37376, 0, 0, { 0, 0 }, 338, 0, 0 },
    { 591, 3000, { 0, 0 }, 256000, 0, 0, 0, { 0, 0 }, 33090, 0, 0 },
};

static const EventCharaKeyframe sEvent149Track3[3] = {
    { 928, 460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, 0, 0 },
    { 927, 510, { 0, 0 }, 27904, 29952, 0, 0, { 0, 0 }, 16658, 0, 0 },
    { 928, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, 0, 0 },
};

static const EventCharaTrack sEvent149Tracks[4] = {
    { sEvent149Track0, 44, { 0, 0, 0 } },
    { sEvent149Track1, 88, { 0, 0, 0 } },
    { sEvent149Track2, 50, { 0, 0, 0 } },
    { sEvent149Track3, 93, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent149 = {
    4,
    { 0, 0, 0 },
    sEvent149Tracks,
    sEvent149Camera,
    sEvent149Script,
    sEvent149SoundCues,
    0,
    2390,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    150,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent149 = {
    4,
    { 0, 0, 0 },
    sEvent149Tracks,
    sEvent149Camera,
    sEvent149Script,
    sEvent149SoundCues,
    0,
    2390,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    148,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_150_text.inc"

static const MessageScriptEntry sEvent150Script[1] = {
    { 26, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_090109F8, MSG_SCRIPT_FLAG_END, 350 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent150Script[1] = {
    { 26, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEB1C0, MSG_SCRIPT_FLAG_END, 350 },
};

#include "event_150_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent150Script[1] = {
    { 26, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A654, MSG_SCRIPT_FLAG_END, 350 },
};
#endif

static const EvSoundCue sEvent150SoundCues[2] = {
    { 65535, 0, 0, 0 },
    { SONG_BGM_TOWN_FIELD, 5000, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent150Camera[4] = {
    { -65536, 196352, 58112, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, 0 },
    { -65416, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 110, { 0, 0 }, 0 },
    { -65306, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -64537, 205056, 51200, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 80, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent150Track0[8] = {
    { 515, 100, { 0, 0 }, 196864, 64768, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 515, 110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 514, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaTrack sEvent150Tracks[1] = {
    { sEvent150Track0, 44, { 0, 0, 0 } },
};

const EventSequenceDef gEvent150 = {
    1,
    { 0, 0, 0 },
    sEvent150Tracks,
    sEvent150Camera,
    sEvent150Script,
    sEvent150SoundCues,
    0,
    400,
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

#ifdef VERSION_US
#include "event_151_text.inc"

static const MessageScriptEntry sEvent151Script[14] = {
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09010C2C, 0, 215 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09010C90, 0, 310 },
    { 52, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_09010D12, MSG_SCRIPT_FLAG_SILHOUETTE, 355 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09010D84, 0, 365 },
    { 52, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_09010D9A, MSG_SCRIPT_FLAG_SILHOUETTE, 400 },
    { 52, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09010E9E, MSG_SCRIPT_FLAG_SILHOUETTE, 402 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09010F18, 0, 450 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09010F24, 0, 570 },
    { 52, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_09010FDE, MSG_SCRIPT_FLAG_SILHOUETTE, 610 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09011056, 0, 640 },
    { 26, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901106E, 0, 735 },
    { 26, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090110AE, 0, 835 },
    { 26, 2, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090110BA, 0, 837 },
    { 26, 2, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901111C, MSG_SCRIPT_FLAG_END, 839 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent151Script[14] = {
    { 26, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEB740, 0, 215 },
    { 26, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEB704, 0, 310 },
    { 52, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEB6D4, MSG_SCRIPT_FLAG_SILHOUETTE, 355 },
    { 26, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEB6C0, 0, 365 },
    { 52, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEB668, MSG_SCRIPT_FLAG_SILHOUETTE, 400 },
    { 52, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEB648, MSG_SCRIPT_FLAG_SILHOUETTE, 402 },
    { 26, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEB63C, 0, 450 },
    { 26, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEB5E8, 0, 570 },
    { 52, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEB5B0, MSG_SCRIPT_FLAG_SILHOUETTE, 610 },
    { 26, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEB59C, 0, 640 },
    { 26, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEB57C, 0, 735 },
    { 26, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEB574, 0, 835 },
    { 26, 2, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEB534, 0, 837 },
    { 26, 2, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEB514, MSG_SCRIPT_FLAG_END, 839 },
};

#include "event_151_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent151Script[14] = {
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69E5C, 0, 215 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69E70, 0, 310 },
    { 52, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69E84, MSG_SCRIPT_FLAG_SILHOUETTE, 355 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69E98, 0, 365 },
    { 52, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69EAC, MSG_SCRIPT_FLAG_SILHOUETTE, 400 },
    { 52, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69EC0, MSG_SCRIPT_FLAG_SILHOUETTE, 402 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69ED4, 0, 450 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69EE8, 0, 570 },
    { 52, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69EFC, MSG_SCRIPT_FLAG_SILHOUETTE, 610 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69F10, 0, 640 },
    { 26, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69F24, 0, 735 },
    { 26, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69F38, 0, 835 },
    { 26, 2, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69F4C, 0, 837 },
    { 26, 2, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69F60, MSG_SCRIPT_FLAG_END, 839 },
};
#endif

static const EvSoundCue sEvent151SoundCues[2] = {
    { SONG_BGM_HOLLOW_FIELD, 0, 0, 0 },
    { SONG_BGM_HOLLOW_FIELD, 955, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent151Camera[2] = {
    { -65536, 55552, 75264, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, 0 },
    { -64537, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 80, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent151Track0[23] = {
    { 514, 1, { 0, 0 }, 18944, 63744, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 516, 155, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, 0, 0 },
    { 514, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 526, 210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 526, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 514, 305, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 524, 357, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 514, 342, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 526, 368, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 514, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 514, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 543, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 538, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 524, 840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 870, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 522, 1500, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, 0, 0 },
    { 514, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaTrack sEvent151Tracks[1] = {
    { sEvent151Track0, 44, { 0, 0, 0 } },
};

const EventSequenceDef gEvent151 = {
    1,
    { 0, 0, 0 },
    sEvent151Tracks,
    sEvent151Camera,
    sEvent151Script,
    sEvent151SoundCues,
    0,
    960,
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
    1,
    255,
    255,
};

#ifdef VERSION_US
#include "event_152_text.inc"

static const MessageScriptEntry sEvent152Script[7] = {
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09011674, 0, 405 },
    { 52, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_09011704, MSG_SCRIPT_FLAG_SILHOUETTE, 440 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901179C, 0, 470 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090117B2, 0, 520 },
    { 52, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901184C, MSG_SCRIPT_FLAG_SILHOUETTE, 550 },
    { 52, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090118D6, MSG_SCRIPT_FLAG_SILHOUETTE, 552 },
    { 26, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901198E, MSG_SCRIPT_FLAG_END, 600 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent152Script[7] = {
    { 26, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEBD4C, 0, 405 },
    { 52, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEBCF8, MSG_SCRIPT_FLAG_SILHOUETTE, 440 },
    { 26, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEBCE4, 0, 470 },
    { 26, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEBC98, 0, 520 },
    { 52, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEBC54, MSG_SCRIPT_FLAG_SILHOUETTE, 550 },
    { 52, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEBBFC, MSG_SCRIPT_FLAG_SILHOUETTE, 552 },
    { 26, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEBBEC, MSG_SCRIPT_FLAG_END, 600 },
};

#include "event_152_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent152Script[7] = {
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69F74, 0, 405 },
    { 52, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69F88, MSG_SCRIPT_FLAG_SILHOUETTE, 440 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69F9C, 0, 470 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69FB0, 0, 520 },
    { 52, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69FC4, MSG_SCRIPT_FLAG_SILHOUETTE, 550 },
    { 52, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69FD8, MSG_SCRIPT_FLAG_SILHOUETTE, 552 },
    { 26, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69FEC, MSG_SCRIPT_FLAG_END, 600 },
};
#endif

static const EvSoundCue sEvent152SoundCues[2] = {
    { SONG_BGM_EVENT_SILENCE, 0, 0, 0 },
    { SONG_BGM_EVENT_SILENCE, 675, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent152Camera[3] = {
    { -65535, 78848, 59136, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -65064, 63488, 67840, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, 0 },
    { -60536, 55808, 71168, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 30, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent152Track0[15] = {
    { 514, 1, { 0, 0 }, 88576, 59136, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 516, 120, { 0, 0 }, 64000, 73984, 0, 514, { 0, 0 }, 3, 0, 0 },
    { 514, 130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 514, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 524, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 472, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 516, 500, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, 0, 0 },
    { 514, 620, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 520, 1000, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 36, 0, 0 },
    { 514, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaTrack sEvent152Tracks[1] = {
    { sEvent152Track0, 44, { 0, 0, 0 } },
};

const EventSequenceDef gEvent152 = {
    1,
    { 0, 0, 0 },
    sEvent152Tracks,
    sEvent152Camera,
    sEvent152Script,
    sEvent152SoundCues,
    0,
    680,
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

#ifdef VERSION_US
#include "event_153_text.inc"

static const MessageScriptEntry sEvent153Script[17] = {
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09011D0C, 0, 150 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09011D36, 0, 260 },
    { 26, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09011D92, 0, 440 },
    { 26, 2, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09011DF0, 0, 442 },
    { 52, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_09011E52, MSG_SCRIPT_FLAG_SILHOUETTE, 490 },
    { 26, 5, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09011E98, 0, 720 },
    { 52, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_09011EB8, MSG_SCRIPT_FLAG_SILHOUETTE, 760 },
    { 52, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_09011EEA, MSG_SCRIPT_FLAG_SILHOUETTE, 850 },
    { 52, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09011F74, MSG_SCRIPT_FLAG_SILHOUETTE, 852 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901201A, 0, 880 },
    { 52, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_09012052, MSG_SCRIPT_FLAG_SILHOUETTE, 920 },
    { 52, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901209E, MSG_SCRIPT_FLAG_SILHOUETTE, 1100 },
    { 52, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901213E, MSG_SCRIPT_FLAG_SILHOUETTE, 1102 },
    { 52, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09012176, MSG_SCRIPT_FLAG_SILHOUETTE, 1104 },
    { 52, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090121F8, MSG_SCRIPT_FLAG_SILHOUETTE, 1106 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901228E, 0, 1125 },
    { 52, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_090122E6, MSG_SCRIPT_FLAG_SILHOUETTE | MSG_SCRIPT_FLAG_END, 1160 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent153Script[17] = {
    { 26, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEC4B0, 0, 150 },
    { 26, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEC480, 0, 260 },
    { 26, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEC448, 0, 440 },
    { 26, 2, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEC40C, 0, 442 },
    { 52, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEC3F4, MSG_SCRIPT_FLAG_SILHOUETTE, 490 },
    { 26, 5, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEC3E0, 0, 720 },
    { 52, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEC3C0, MSG_SCRIPT_FLAG_SILHOUETTE, 760 },
    { 52, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEC388, MSG_SCRIPT_FLAG_SILHOUETTE, 850 },
    { 52, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEC348, MSG_SCRIPT_FLAG_SILHOUETTE, 852 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEC32C, 0, 880 },
    { 52, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEC304, MSG_SCRIPT_FLAG_SILHOUETTE, 920 },
    { 52, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEC2C8, MSG_SCRIPT_FLAG_SILHOUETTE, 1100 },
    { 52, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEC2A0, MSG_SCRIPT_FLAG_SILHOUETTE, 1102 },
    { 52, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEC268, MSG_SCRIPT_FLAG_SILHOUETTE, 1104 },
    { 52, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEC234, MSG_SCRIPT_FLAG_SILHOUETTE, 1106 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEC20C, 0, 1125 },
    { 52, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEC1F0, MSG_SCRIPT_FLAG_SILHOUETTE | MSG_SCRIPT_FLAG_END, 1160 },
};

#include "event_153_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent153Script[17] = {
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A000, 0, 150 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A014, 0, 260 },
    { 26, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A028, 0, 440 },
    { 26, 2, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A03C, 0, 442 },
    { 52, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A050, MSG_SCRIPT_FLAG_SILHOUETTE, 490 },
    { 26, 5, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A064, 0, 720 },
    { 52, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A078, MSG_SCRIPT_FLAG_SILHOUETTE, 760 },
    { 52, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A08C, MSG_SCRIPT_FLAG_SILHOUETTE, 850 },
    { 52, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A0A0, MSG_SCRIPT_FLAG_SILHOUETTE, 852 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A0B4, 0, 880 },
    { 52, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A0C8, MSG_SCRIPT_FLAG_SILHOUETTE, 920 },
    { 52, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A0DC, MSG_SCRIPT_FLAG_SILHOUETTE, 1100 },
    { 52, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A0F0, MSG_SCRIPT_FLAG_SILHOUETTE, 1102 },
    { 52, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A104, MSG_SCRIPT_FLAG_SILHOUETTE, 1104 },
    { 52, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A118, MSG_SCRIPT_FLAG_SILHOUETTE, 1106 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A12C, 0, 1125 },
    { 52, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A140, MSG_SCRIPT_FLAG_SILHOUETTE | MSG_SCRIPT_FLAG_END, 1160 },
};
#endif

static const EvSoundCue sEvent153SoundCues[2] = {
    { SONG_BGM_EVENT_SILENCE, 0, 0, 0 },
    { SONG_BGM_EVENT_SILENCE, 1205, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent153Camera[1] = {
    { -64537, 69888, 80896, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent153Track0[23] = {
    { 515, 1, { 0, 0 }, 104448, 105984, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 518, 120, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, 0, 0 },
    { 515, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 518, 210, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, 0, 0 },
    { 515, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 270, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 514, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 543, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 515, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 515, 875, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 538, 882, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 940, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 540, 1070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 540, 1110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 1120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 538, 1130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaTrack sEvent153Tracks[1] = {
    { sEvent153Track0, 44, { 0, 0, 0 } },
};

const EventSequenceDef gEvent153 = {
    1,
    { 0, 0, 0 },
    sEvent153Tracks,
    sEvent153Camera,
    sEvent153Script,
    sEvent153SoundCues,
    0,
    1210,
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

#ifdef VERSION_US
#include "event_154_text.inc"

static const MessageScriptEntry sEvent154Script[25] = {
    { 44, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09012864, 0, 280 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901289A, 0, 310 },
    { 44, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090128D0, 0, 340 },
    { 26, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901295E, 0, 510 },
    { 44, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090129CA, 0, 540 },
    { 44, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09012A24, 0, 542 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09012AB6, 0, 570 },
    { 44, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09012ABE, 0, 600 },
    { 44, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09012B22, 0, 602 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09012BE4, 0, 630 },
    { 44, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09012C3E, 0, 660 },
    { 44, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09012CC2, 0, 662 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09012D54, 0, 850 },
    { 26, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09012DEE, 0, 852 },
    { 26, 2, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_09012E6A, 0, 1030 },
    { 26, 2, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09012EBC, 0, 1032 },
    { 26, 2, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_09012F66, 0, 1120 },
    { 44, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09012FA2, 0, 1150 },
    { 44, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09012FFC, 0, 1152 },
    { 26, 2, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_09013052, 0, 1190 },
    { 26, 2, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090130DC, 0, 1192 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09013140, 0, 1280 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_090131CA, 0, 1345 },
    { 44, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090131FC, 0, 1385 },
    { 44, 2, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09013292, MSG_SCRIPT_FLAG_END, 1390 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent154Script[25] = {
    { 44, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FED04C, 0, 280 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FED024, 0, 310 },
    { 44, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FECFD0, 0, 340 },
    { 26, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FECFA4, 0, 510 },
    { 44, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FECF78, 0, 540 },
    { 44, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FECF48, 0, 542 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FECF38, 0, 570 },
    { 44, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FECEFC, 0, 600 },
    { 44, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FECEC4, 0, 602 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FECE98, 0, 630 },
    { 44, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FECE48, 0, 660 },
    { 44, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FECDEC, 0, 662 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FECDA0, 0, 850 },
    { 26, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FECD60, 0, 852 },
    { 26, 2, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FECD30, 0, 1030 },
    { 26, 2, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FECCD8, 0, 1032 },
    { 26, 2, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FECCC4, 0, 1120 },
    { 44, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FECC8C, 0, 1150 },
    { 44, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FECC5C, 0, 1152 },
    { 26, 2, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FECC18, 0, 1190 },
    { 26, 2, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FECBE0, 0, 1192 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FECB90, 0, 1280 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FECB70, 0, 1345 },
    { 44, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FECB14, 0, 1385 },
    { 44, 2, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FECAC8, MSG_SCRIPT_FLAG_END, 1390 },
};

#include "event_154_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent154Script[25] = {
    { 44, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A154, 0, 280 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A168, 0, 310 },
    { 44, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A17C, 0, 340 },
    { 26, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A190, 0, 510 },
    { 44, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A1A4, 0, 540 },
    { 44, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A1B8, 0, 542 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A1CC, 0, 570 },
    { 44, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A1E0, 0, 600 },
    { 44, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A1F4, 0, 602 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A208, 0, 630 },
    { 44, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A21C, 0, 660 },
    { 44, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A230, 0, 662 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A244, 0, 850 },
    { 26, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A258, 0, 852 },
    { 26, 2, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A26C, 0, 1030 },
    { 26, 2, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A280, 0, 1032 },
    { 26, 2, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A294, 0, 1120 },
    { 44, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A2A8, 0, 1150 },
    { 44, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A2BC, 0, 1152 },
    { 26, 2, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A2D0, 0, 1190 },
    { 26, 2, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A2E4, 0, 1192 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A2F8, 0, 1280 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A30C, 0, 1345 },
    { 44, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A320, 0, 1385 },
    { 44, 2, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A334, MSG_SCRIPT_FLAG_END, 1390 },
};
#endif

static const EvSoundCue sEvent154SoundCues[7] = {
    { 65535, 0, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 285, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_SND_359, 1300, 0, 0 },
    { SONG_SND_375, 1402, 0, 0 },
    { SONG_EV_FLASH01, 1520, 0, 0 },
    { SONG_EV_FLASH01, 1530, 0, 0 },
    { SONG_EV_FLASH02, 1540, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent154Camera[6] = {
    { -65375, 34048, 84224, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -64136, 61696, 65280, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 100, { 0, 0 }, 0 },
    { -64016, 61696, 60928, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, 0 },
    { -64006, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_HALF_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 10, { 0, 0 }, 0 },
    { -63996, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_HALF_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 10, { 0, 0 }, 0 },
    { -63966, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_KEYFRAME_FLAG_END | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 30, { 0, 0 }, 0 },
};

static const EventBgEffectEntry sEvent154BgEffects[3] = {
    { 1392, 0, 0, 0, 0 },
    { 1402, 0, 0, 0, 0x4 },
    { 1412, 6, 64000, 40448, 0x8001 },
};

static const EventCharaKeyframe sEvent154Track0[26] = {
    { 515, 1, { 0, 0 }, 6912, 99328, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 522, 70, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, 0, 0 },
    { 515, 73, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, 0, 0 },
    { 515, 80, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 532, 130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 515, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 518, 230, { 0, 0 }, 50944, 76544, 0, 515, { 0, 0 }, 67, 0, 0 },
    { 515, 305, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 538, 312, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 515, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 540, 820, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 540, 880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 910, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 940, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 516, 970, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, 0, 0 },
    { 514, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 543, 1050, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 1070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 1080, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 1210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 518, 1240, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, 0, 0 },
    { 515, 1300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 560, 9000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent154Track1[6] = {
    { 410, 661, { 0, 0 }, 71424, 66560, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 415, 663, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 416, 690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 410, 1387, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 414, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 1029, 0, 0 },
    { 414, 9000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33797, 0, 0 },
};

static const EventCharaTrack sEvent154Tracks[2] = {
    { sEvent154Track0, 44, { 0, 0, 0 } },
    { sEvent154Track1, 30, { 0, 0, 0 } },
};

const EventSequenceDef gEvent154 = {
    2,
    { 0, 0, 0 },
    sEvent154Tracks,
    sEvent154Camera,
    sEvent154Script,
    sEvent154SoundCues,
    sEvent154BgEffects,
    1620,
    0,
    1,
    0,
    0,
    0,
    0,
    153,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_155_text.inc"

static const MessageScriptEntry sEvent155Script[26] = {
    { 52, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_09013B74, MSG_SCRIPT_FLAG_SILHOUETTE, 210 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09013BA8, 0, 240 },
    { 52, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_09013C26, MSG_SCRIPT_FLAG_SILHOUETTE, 280 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09013C8A, 0, 310 },
    { 52, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_09013CAE, MSG_SCRIPT_FLAG_SILHOUETTE, 350 },
    { 56, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09013D14, MSG_SCRIPT_FLAG_SILHOUETTE, 360 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09013D52, 0, 620 },
    { 56, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09013D86, 0, 650 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09013DBA, 0, 680 },
    { 26, 2, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09013E1C, 0, 682 },
    { 56, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09013EE0, 0, 715 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09013F6C, 0, 745 },
    { 26, 2, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_09013FC0, 0, 1030 },
    { 56, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09013FCC, 0, 1060 },
    { 26, 2, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_090140C0, 0, 1090 },
    { 56, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090140F4, 0, 1120 },
    { 26, 2, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901417C, 0, 1190 },
    { 56, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09014198, 0, 1220 },
    { 61, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_090141D8, MSG_SCRIPT_FLAG_SILHOUETTE, 1250 },
    { 26, 3, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_090141F4, 0, 1460 },
    { 26, 3, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901420E, 0, 1530 },
    { 61, 1, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_09014246, 0, 1560 },
    { 61, 3, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901428E, 0, 1800 },
    { 26, 4, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_090143A6, 0, 1830 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_090143B6, 0, 1910 },
    { 56, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09014426, MSG_SCRIPT_FLAG_END, 2000 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent155Script[26] = {
    { 52, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEDCE0, MSG_SCRIPT_FLAG_SILHOUETTE, 210 },
    { 26, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEDCA4, 0, 240 },
    { 52, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEDC64, MSG_SCRIPT_FLAG_SILHOUETTE, 280 },
    { 26, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEB59C, 0, 310 },
    { 52, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEDC30, MSG_SCRIPT_FLAG_SILHOUETTE, 350 },
    { 56, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEDC14, MSG_SCRIPT_FLAG_SILHOUETTE, 360 },
    { 26, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEDBF4, 0, 620 },
    { 56, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEDBCC, 0, 650 },
    { 26, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEDB98, 0, 680 },
    { 26, 2, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEDB4C, 0, 682 },
    { 56, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEDAFC, 0, 715 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEDAD8, 0, 745 },
    { 26, 2, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEDACC, 0, 1030 },
    { 56, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEDA70, 0, 1060 },
    { 26, 2, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEDA58, 0, 1090 },
    { 56, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEDA18, 0, 1120 },
    { 26, 2, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FED9FC, 0, 1190 },
    { 56, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FED9D0, 0, 1220 },
    { 61, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FED9BC, MSG_SCRIPT_FLAG_SILHOUETTE, 1250 },
    { 26, 3, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FED9AC, 0, 1460 },
    { 26, 3, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FED99C, 0, 1530 },
    { 61, 1, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FED974, 0, 1560 },
    { 61, 3, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FED924, 0, 1800 },
    { 26, 4, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FED914, 0, 1830 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FED8F0, 0, 1910 },
    { 56, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FED8BC, MSG_SCRIPT_FLAG_END, 2000 },
};

#include "event_155_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent155Script[26] = {
    { 52, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A44C, MSG_SCRIPT_FLAG_SILHOUETTE, 210 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A460, 0, 240 },
    { 52, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A474, MSG_SCRIPT_FLAG_SILHOUETTE, 280 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A488, 0, 310 },
    { 52, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A49C, MSG_SCRIPT_FLAG_SILHOUETTE, 350 },
    { 56, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A4B0, MSG_SCRIPT_FLAG_SILHOUETTE, 360 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A4C4, 0, 620 },
    { 56, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A4D8, 0, 650 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A4EC, 0, 680 },
    { 26, 2, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A500, 0, 682 },
    { 56, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A514, 0, 715 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A528, 0, 745 },
    { 26, 2, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A53C, 0, 1030 },
    { 56, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A550, 0, 1060 },
    { 26, 2, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A564, 0, 1090 },
    { 56, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A578, 0, 1120 },
    { 26, 2, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A58C, 0, 1190 },
    { 56, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A5A0, 0, 1220 },
    { 61, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A5B4, MSG_SCRIPT_FLAG_SILHOUETTE, 1250 },
    { 26, 3, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A5C8, 0, 1460 },
    { 26, 3, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A5DC, 0, 1530 },
    { 61, 1, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A5F0, 0, 1560 },
    { 61, 3, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A604, 0, 1800 },
    { 26, 4, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A618, 0, 1830 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A62C, 0, 1910 },
    { 56, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A640, MSG_SCRIPT_FLAG_END, 2000 },
};
#endif

static const EvSoundCue sEvent155SoundCues[9] = {
    { SONG_BGM_EVENT_UNREST, 0, 0, 0 },
    { SONG_SND_379, 560, 0, 0 },
    { SONG_SND_376, 758, 0, 0 },
    { SONG_EV_FLASH00, 780, 0, 0 },
    { SONG_EV_WOMAN_RSTONEL, 1150, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 1245, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_EV_FLASH00, 1660, 0, 0 },
    { SONG_BGM_EVENT2, 1968, 0, 0 },
    { SONG_SND_359, 1970, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent155Camera[14] = {
    { -65166, 186112, 65792, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -65156, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_HALF_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, 0 },
    { -65116, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_HALF_FLASH | CAMERA_MODE_KEEP, 20, { 0, 0 }, 0 },
    { -65106, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_HALF_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, 0 },
    { -65026, 195840, 58368, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, 0 },
    { -64976, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_HALF_FLASH | CAMERA_MODE_KEEP, 50, { 0, 0 }, 0 },
    { -64776, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -64756, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 20, { 0, 0 }, 0 },
    { -64736, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 20, { 0, 0 }, 0 },
    { -64656, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -63876, 168448, 71168, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 100, { 0, 0 }, 0 },
    { -63826, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 50, { 0, 0 }, 0 },
    { -62536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -60536, 189952, 64768, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 100, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent155Track0[14] = {
    { 515, 1, { 0, 0 }, 152064, 88064, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 518, 150, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, 0, 0 },
    { 515, 746, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 563, 760, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 548, 780, { 0, 0 }, 200704, 62976, 0, 515, { 0, 0 }, 67, 0, 0 },
    { 550, 810, { 0, 0 }, 161024, 80384, 0, 515, { 0, 0 }, 67, 0, 0 },
    { 547, 1380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 547, 1480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 545, 1860, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 546, 1882, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 1930, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 1940, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 1970, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 560, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent155Track1[8] = {
    { 688, 560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 688, 780, { 0, 0 }, 205824, 60160, 0, 0, { 0, 0 }, 18, EventCharaFadeIn, 0 },
    { 688, 880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 21, 0, 0 },
    { 690, 1000, { 0, 0 }, 179968, 72448, 0, 688, { 0, 0 }, 19, 0, 0 },
    { 688, 1140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 690, 1160, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, 0, 0 },
    { 688, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 688, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent155Track2[10] = {
    { 920, 1251, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8274, 0, 0 },
    { 920, 1252, { 0, 0 }, 153600, 47360, 0, 0, { 0, 0 }, 16722, 0, 0 },
    { 920, 1300, { 0, 0 }, 153600, 71680, 0, 920, { 0, 0 }, 339, 0, 0 },
    { 920, 1350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 469, 0, 0 },
    { 920, 1540, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 336, func_0806F610, 0 },
    { 920, 1570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 469, 0, 0 },
    { 920, 1610, { 0, 0 }, 161024, 62976, 0, 920, { 0, 0 }, 339, 0, 0 },
    { 920, 1640, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 341, 0, 0 },
    { 920, 1660, { 0, 0 }, 161024, 66560, 0, 0, { 0, 0 }, 4435, EventCharaFadeOut, 0 },
    { 920, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98370, 0, 0 },
};

static const EventCharaKeyframe sEvent155Track3[3] = {
    { 928, 1380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, 0, 0 },
    { 927, 1430, { 0, 0 }, 156928, 77824, 0, 0, { 0, 0 }, 16658, 0, 0 },
    { 928, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, 0, 0 },
};

static const EventCharaTrack sEvent155Tracks[4] = {
    { sEvent155Track0, 44, { 0, 0, 0 } },
    { sEvent155Track1, 64, { 0, 0, 0 } },
    { sEvent155Track2, 87, { 0, 0, 0 } },
    { sEvent155Track3, 93, { 0, 0, 0 } },
};

const EventSequenceDef gEvent155 = {
    4,
    { 0, 0, 0 },
    sEvent155Tracks,
    sEvent155Camera,
    sEvent155Script,
    sEvent155SoundCues,
    0,
    2060,
    0,
    1,
    0,
    0,
    0,
    0,
    166,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_156_text.inc"

static const MessageScriptEntry sEvent156Script[21] = {
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09014E74, 0, 120 },
    { 56, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09014E9E, 0, 150 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09014F4C, 0, 250 },
    { 56, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09014F6C, 0, 280 },
    { 56, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09015050, 0, 282 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_090150DE, 0, 310 },
    { 26, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09015122, 0, 312 },
    { 56, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090151AE, 0, 540 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_090151EA, 0, 860 },
    { 56, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901520E, 0, 890 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09015276, 0, 920 },
    { 56, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090152D8, 0, 950 },
    { 56, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901532C, 0, 1070 },
    { 62, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_090153CC, 0, 1130 },
    { 62, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09015480, 0, 1132 },
    { 62, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09015526, 0, 1134 },
    { 62, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_09015600, 0, 1160 },
    { 62, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901565E, 0, 1162 },
    { 62, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090156CA, 0, 1164 },
    { 62, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_09015736, 0, 1190 },
    { 62, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901579C, MSG_SCRIPT_FLAG_END, 1192 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent156Script[21] = {
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEEACC, 0, 120 },
    { 56, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEEA7C, 0, 150 },
    { 26, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEEA68, 0, 250 },
    { 56, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEEA08, 0, 280 },
    { 56, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEE9B8, 0, 282 },
    { 26, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEE990, 0, 310 },
    { 26, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEE94C, 0, 312 },
    { 56, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEE924, 0, 540 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEE918, 0, 860 },
    { 56, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEE8E4, 0, 890 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEE8B4, 0, 920 },
    { 56, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEE894, 0, 950 },
    { 56, 1, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEE84C, 0, 1070 },
    { 62, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEE7FC, 0, 1130 },
    { 62, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEE7A8, 0, 1132 },
    { 62, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEE758, 0, 1134 },
    { 62, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEE720, 0, 1160 },
    { 62, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEE6D0, 0, 1162 },
    { 62, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEE6A4, 0, 1164 },
    { 62, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEE670, 0, 1190 },
    { 62, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEE634, MSG_SCRIPT_FLAG_END, 1192 },
};

#include "event_156_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent156Script[21] = {
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A348, 0, 120 },
    { 56, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A35C, 0, 150 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A370, 0, 250 },
    { 56, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A384, 0, 280 },
    { 56, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A398, 0, 282 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A3AC, 0, 310 },
    { 26, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A3C0, 0, 312 },
    { 56, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A3D4, 0, 540 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A3E8, 0, 860 },
    { 56, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A3FC, 0, 890 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A410, 0, 920 },
    { 56, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A424, 0, 950 },
    { 56, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A438, 0, 1070 },
    { 62, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F697F4, 0, 1130 },
    { 62, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69808, 0, 1132 },
    { 62, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6981C, 0, 1134 },
    { 62, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69830, 0, 1160 },
    { 62, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69844, 0, 1162 },
    { 62, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69858, 0, 1164 },
    { 62, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6986C, 0, 1190 },
    { 62, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69880, MSG_SCRIPT_FLAG_END, 1192 },
};
#endif

static const EvSoundCue sEvent156SoundCues[5] = {
    { SONG_BGM_EVENT_UNREST, 0, 0, 0 },
    { SONG_EV_CARDTHR, 507, 0, 0 },
    { SONG_SND_377, 640, 0, 0 },
    { SONG_SND_379, 990, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 1245, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent156Camera[2] = {
    { -64496, 193024, 61184, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -62536, 182016, 66560, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 50, { 0, 0 }, 0 },
};

static const EventBgEffectEntry sEvent156BgEffects[5] = {
    { 580, 0, 0, 0, 0 },
    { 640, 0, 60, 0, 0x4 },
    { 736, 5, 169728, 54016, 0x1 },
    { 740, 0, 0, 0, 0x2 },
    { 840, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent156Track0[14] = {
    { 561, 220, { 0, 0 }, 181760, 73216, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 562, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 512, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 559, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 670, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 515, 855, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 538, 862, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 915, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 538, 922, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 990, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 1040, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 515, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent156Track1[9] = {
    { 688, 170, { 0, 0 }, 203520, 62720, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 691, 340, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 691, 470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 691, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 692, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 688, 970, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 688, 990, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 4, 0, 0 },
    { 688, 1050, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 260, EventCharaFadeOut, 0 },
    { 688, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32770, 0, 0 },
};

static const EventCharaKeyframe sEvent156Track2[10] = {
    { 591, 186, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8258, 0, 0 },
    { 607, 490, { 0, 0 }, 203520, 62720, 0, 0, { 0, 0 }, 16658, 0, 0 },
    { 591, 506, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 591, 507, { 0, 0 }, 197632, 56832, 0, 0, { 0, 0 }, 322, 0, 0 },
    { 591, 517, { 0, 0 }, 186880, 63232, 0, 591, { 0, 0 }, 323, 0, 0 },
    { 591, 520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, 0, 0 },
    { 591, 526, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 604, 600, { 0, 0 }, 181760, 73216, 0, 0, { 0, 0 }, 338, 0, 0 },
    { 591, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 591, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98373, 0, 0 },
};

static const EventCharaTrack sEvent156Tracks[3] = {
    { sEvent156Track0, 44, { 0, 0, 0 } },
    { sEvent156Track1, 64, { 0, 0, 0 } },
    { sEvent156Track2, 50, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent156 = {
    3,
    { 0, 0, 0 },
    sEvent156Tracks,
    sEvent156Camera,
    sEvent156Script,
    sEvent156SoundCues,
    sEvent156BgEffects,
    1250,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    157,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent156 = {
    3,
    { 0, 0, 0 },
    sEvent156Tracks,
    sEvent156Camera,
    sEvent156Script,
    sEvent156SoundCues,
    sEvent156BgEffects,
    1250,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    155,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_157_text.inc"

static const MessageScriptEntry sEvent157Script[18] = {
    { 55, 5, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09015FC8, 0, 370 },
    { 38, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901600E, 0, 520 },
    { 55, 5, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09016072, 0, 570 },
    { 55, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090160AA, 0, 572 },
    { 38, 2, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_09016180, 0, 590 },
    { 57, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901619C, 0, 610 },
    { 57, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_090161C0, 0, 810 },
    { 55, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901620C, 0, 1030 },
    { 55, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09016290, 0, 1032 },
    { 38, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_090162D2, 0, 1060 },
    { 55, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901638E, 0, 1100 },
    { 55, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09016422, 0, 1280 },
    { 57, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_090164F8, 0, 1310 },
    { 55, 5, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901650E, 0, 1350 },
    { 55, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901652A, 0, 1352 },
    { 38, 3, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_090165CC, 0, 1380 },
    { 55, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090165DE, 0, 1410 },
    { 57, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09016626, MSG_SCRIPT_FLAG_END, 1640 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent157Script[18] = {
    { 55, 5, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEF52C, 0, 370 },
    { 38, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEF4F8, 0, 520 },
    { 55, 5, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEF4C8, 0, 570 },
    { 55, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEF498, 0, 572 },
    { 38, 2, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEF48C, 0, 590 },
    { 57, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEF478, 0, 610 },
    { 57, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEF454, 0, 810 },
    { 55, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEF410, 0, 1030 },
    { 55, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEF3F4, 0, 1032 },
    { 38, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEF3A4, 0, 1060 },
    { 55, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEF348, 0, 1100 },
    { 55, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEF2F4, 0, 1280 },
    { 57, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEF2E8, 0, 1310 },
    { 55, 5, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEF2D4, 0, 1350 },
    { 55, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEF280, 0, 1352 },
    { 38, 3, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEF274, 0, 1380 },
    { 55, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEF254, 0, 1410 },
    { 57, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEF23C, MSG_SCRIPT_FLAG_END, 1640 },
};

#include "event_157_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent157Script[18] = {
    { 55, 5, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69CF4, 0, 370 },
    { 38, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69D08, 0, 520 },
    { 55, 5, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69D1C, 0, 570 },
    { 55, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69D30, 0, 572 },
    { 38, 2, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69D44, 0, 590 },
    { 57, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69D58, 0, 610 },
    { 57, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69D6C, 0, 810 },
    { 55, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69D80, 0, 1030 },
    { 55, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69D94, 0, 1032 },
    { 38, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69DA8, 0, 1060 },
    { 55, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69DBC, 0, 1100 },
    { 55, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69DD0, 0, 1280 },
    { 57, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69DE4, 0, 1310 },
    { 55, 5, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69DF8, 0, 1350 },
    { 55, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69E0C, 0, 1352 },
    { 38, 3, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69E20, 0, 1380 },
    { 55, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69E34, 0, 1410 },
    { 57, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69E48, MSG_SCRIPT_FLAG_END, 1640 },
};
#endif

static const EvSoundCue sEvent157SoundCues[4] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_EV_WARPOUT, 150, 0, 0 },
    { SONG_EV_WARPOUT, 420, 0, 0 },
    { SONG_BGM_EVENT_XIII, 1695, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent157Camera[3] = {
    { -65406, 65536, 48640, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -65116, 58368, 52480, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, 0 },
    { -64537, 65536, 54784, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 50, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent157Track0[9] = {
    { 891, 300, { 0, 0 }, 65792, 55808, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 892, 320, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 889, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 889, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 889, 960, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 889, 990, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 889, 1080, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 889, 1260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 889, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent157Track1[10] = {
    { 738, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 738, 470, { 0, 0 }, 84992, 72448, 0, 0, { 0, 0 }, 2, EventCharaFadeIn, 0 },
    { 742, 500, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, 0, 0 },
    { 738, 630, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 738, 760, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 738, 1120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 738, 1250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 738, 1375, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 740, 1382, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 738, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent157Track2[9] = {
    { 883, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 883, 200, { 0, 0 }, 50944, 64256, 0, 0, { 0, 0 }, 66, EventCharaFadeIn, 0 },
    { 883, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 883, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 884, 1430, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 883, 1450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 887, 1470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 887, 1600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 887, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaTrack sEvent157Tracks[3] = {
    { sEvent157Track0, 83, { 0, 0, 0 } },
    { sEvent157Track1, 67, { 0, 0, 0 } },
    { sEvent157Track2, 82, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent157 = {
    3,
    { 0, 0, 0 },
    sEvent157Tracks,
    sEvent157Camera,
    sEvent157Script,
    sEvent157SoundCues,
    0,
    1700,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    158,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent157 = {
    3,
    { 0, 0, 0 },
    sEvent157Tracks,
    sEvent157Camera,
    sEvent157Script,
    sEvent157SoundCues,
    0,
    1700,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    156,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_158_text.inc"

static const MessageScriptEntry sEvent158Script[21] = {
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09016CE8, 0, 180 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09016D28, 0, 310 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09016D64, 0, 610 },
    { 26, 5, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09016DA6, 0, 660 },
    { 61, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_09016E24, 0, 840 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09016E52, 0, 980 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09016E6E, 0, 1230 },
    { 61, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09016EBE, 0, 1260 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09016F4A, 0, 1290 },
    { 61, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09016F86, 0, 1320 },
    { 61, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09017016, 0, 1410 },
    { 61, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09017078, 0, 1414 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09017116, 0, 1450 },
    { 61, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09017144, 0, 1480 },
    { 61, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090171E8, 0, 1482 },
    { 61, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901725C, 0, 1484 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_090172DC, 0, 1675 },
    { 61, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901730A, 0, 1700 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901738A, 0, 1890 },
    { 61, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090173F6, 0, 1920 },
    { 26, 4, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09017478, MSG_SCRIPT_FLAG_END, 1950 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent158Script[21] = {
    { 26, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEFFB4, 0, 180 },
    { 26, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEFF80, 0, 310 },
    { 26, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEFF68, 0, 610 },
    { 26, 5, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEFF1C, 0, 660 },
    { 61, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEFF08, 0, 840 },
    { 26, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEFF00, 0, 980 },
    { 26, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEFED8, 0, 1230 },
    { 61, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEFE80, 0, 1260 },
    { 26, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEFE70, 0, 1290 },
    { 61, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEFE28, 0, 1320 },
    { 61, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEFDE8, 0, 1410 },
    { 61, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEFD98, 0, 1414 },
    { 26, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEFD84, 0, 1450 },
    { 61, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEFD38, 0, 1480 },
    { 61, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEFD08, 0, 1482 },
    { 61, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEFCD4, 0, 1484 },
    { 26, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEFCB8, 0, 1675 },
    { 61, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEFC70, 0, 1700 },
    { 26, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEFC54, 0, 1890 },
    { 61, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEFC08, 0, 1920 },
    { 26, 4, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FA71CC, MSG_SCRIPT_FLAG_END, 1950 },
};

#include "event_158_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent158Script[21] = {
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69B50, 0, 180 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69B64, 0, 310 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69B78, 0, 610 },
    { 26, 5, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69B8C, 0, 660 },
    { 61, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69BA0, 0, 840 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69BB4, 0, 980 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69BC8, 0, 1230 },
    { 61, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69BDC, 0, 1260 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69BF0, 0, 1290 },
    { 61, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69C04, 0, 1320 },
    { 61, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69C18, 0, 1410 },
    { 61, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69C2C, 0, 1414 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69C40, 0, 1450 },
    { 61, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69C54, 0, 1480 },
    { 61, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69C68, 0, 1482 },
    { 61, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69C7C, 0, 1484 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69C90, 0, 1675 },
    { 61, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69CA4, 0, 1700 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69CB8, 0, 1890 },
    { 61, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69CCC, 0, 1920 },
    { 26, 4, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69CE0, MSG_SCRIPT_FLAG_END, 1950 },
};
#endif

static const EvSoundCue sEvent158SoundCues[8] = {
    { SONG_BGM_T13THFLOOR, 0, 0, 0 },
    { SONG_BGM_T13THFLOOR, 360, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT_UNREST, 611, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT_UNREST, 900, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_EV_FLASH01, 1010, 0, 0 },
    { SONG_EV_FLASH01, 1040, 0, 0 },
    { SONG_EV_FLASH01, 1060, 0, 0 },
    { SONG_EV_WHITEOUT, 1110, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent158Camera[12] = {
    { -64676, 171520, 68352, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -64526, 178176, 66560, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, 0 },
    { -64496, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_HALF_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 10, { 0, 0 }, 0 },
    { -64476, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 20, { 0, 0 }, 0 },
    { -64466, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_HALF_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 10, { 0, 0 }, 0 },
    { -64426, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -64376, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 50, { 0, 0 }, 0 },
    { -64371, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -64321, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 50, { 0, 0 }, 0 },
    { -64186, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -63536, 173824, 68608, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, 0 },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent158Track0[31] = {
    { 515, 1, { 0, 0 }, 137216, 93696, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 518, 150, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, 0, 0 },
    { 515, 210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 514, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 530, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 530, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 530, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 532, 520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 532, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 532, 580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 630, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 540, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 540, 810, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 540, 860, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 975, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 532, 982, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 1495, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 1625, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 515, 1650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 540, 1670, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 1770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 536, 1790, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 536, 1840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 536, 1860, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 558, 1925, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent158Track1[10] = {
    { 745, 1161, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 745, 1350, { 0, 0 }, 185088, 70656, 0, 0, { 0, 0 }, 1048834, 0, 0 },
    { 747, 1380, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 1048836, 0, 0 },
    { 745, 1405, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 1048837, 0, 0 },
    { 751, 1412, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 1048837, 0, 0 },
    { 745, 1720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 1048837, 0, 0 },
    { 750, 1890, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 1048837, 0, 0 },
    { 745, 1980, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 1048837, 0, 0 },
    { 745, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 524544, EventCharaFadeOut, 0 },
    { 745, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent158Track2[5] = {
    { 920, 860, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8274, 0, 0 },
    { 920, 861, { 0, 0 }, 185856, 44800, 0, 0, { 0, 0 }, 16722, 0, 0 },
    { 920, 950, { 0, 0 }, 185856, 61952, 0, 920, { 0, 0 }, 339, 0, 0 },
    { 920, 1120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 469, 0, 0 },
    { 920, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98370, 0, 0 },
};

static const EventCharaTrack sEvent158Tracks[3] = {
    { sEvent158Track0, 44, { 0, 0, 0 } },
    { sEvent158Track1, 69, { 0, 0, 0 } },
    { sEvent158Track2, 87, { 0, 0, 0 } },
};

const EventSequenceDef gEvent158 = {
    3,
    { 0, 0, 0 },
    sEvent158Tracks,
    sEvent158Camera,
    sEvent158Script,
    sEvent158SoundCues,
    0,
    2060,
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

#ifdef VERSION_US
#include "event_159_text.inc"

static const MessageScriptEntry sEvent159Script[17] = {
    { 55, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09017F14, 0, 100 },
    { 38, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09017F60, 0, 130 },
    { 38, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09017F90, 0, 134 },
    { 55, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901805C, 0, 160 },
    { 38, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_090180E6, 0, 190 },
    { 38, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09018162, 0, 192 },
    { 38, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09018202, 0, 194 },
    { 55, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090182BC, 0, 225 },
    { 38, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09018340, 0, 255 },
    { 38, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090183CE, 0, 257 },
    { 55, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09018408, 0, 290 },
    { 38, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09018434, 0, 320 },
    { 38, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901848C, 0, 322 },
    { 55, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09018528, 0, 360 },
    { 38, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09018560, 0, 390 },
    { 38, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09018602, 0, 394 },
    { 38, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09018664, MSG_SCRIPT_FLAG_END, 396 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent159Script[17] = {
    { 55, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF0DC8, 0, 100 },
    { 38, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF0DBC, 0, 130 },
    { 38, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF0D68, 0, 134 },
    { 55, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF0D2C, 0, 160 },
    { 38, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF0CF4, 0, 190 },
    { 38, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF0C9C, 0, 192 },
    { 38, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF0C44, 0, 194 },
    { 55, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF0C0C, 0, 225 },
    { 38, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF0BD4, 0, 255 },
    { 38, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF0B80, 0, 257 },
    { 55, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF0B6C, 0, 290 },
    { 38, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF0B38, 0, 320 },
    { 38, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF0AE4, 0, 322 },
    { 55, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF0ACC, 0, 360 },
    { 38, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF0A84, 0, 390 },
    { 38, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF0A30, 0, 394 },
    { 38, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF09EC, MSG_SCRIPT_FLAG_END, 396 },
};

#include "event_159_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent159Script[17] = {
    { 55, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F699FC, 0, 100 },
    { 38, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69A10, 0, 130 },
    { 38, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69A24, 0, 134 },
    { 55, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69A38, 0, 160 },
    { 38, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69A4C, 0, 190 },
    { 38, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69A60, 0, 192 },
    { 38, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69A74, 0, 194 },
    { 55, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69A88, 0, 225 },
    { 38, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69A9C, 0, 255 },
    { 38, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69AB0, 0, 257 },
    { 55, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69AC4, 0, 290 },
    { 38, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69AD8, 0, 320 },
    { 38, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69AEC, 0, 322 },
    { 55, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69B00, 0, 360 },
    { 38, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69B14, 0, 390 },
    { 38, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69B28, 0, 394 },
    { 38, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69B3C, MSG_SCRIPT_FLAG_END, 396 },
};
#endif

static const EventCameraKeyframe sEvent159Camera[1] = {
    { -64537, 68352, 58368, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, 0 },
};

static const EvSoundCue sEvent159SoundCues[2] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_BGM_EVENT_XIII, 451, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCharaKeyframe sEvent159Track0[2] = {
    { 889, 100, { 0, 0 }, 78080, 63488, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 889, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent159Track1[4] = {
    { 721, 132, { 0, 0 }, 57856, 66560, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 727, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 729, 392, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 727, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
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
    0,
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

#ifdef VERSION_US
#include "event_160_text.inc"

static const MessageScriptEntry sEvent160Script[13] = {
    { 38, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090189C4, 0, 250 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_090189E6, 0, 280 },
    { 38, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09018A28, 0, 460 },
    { 38, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09018AAE, 0, 462 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09018B20, 0, 490 },
    { 38, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09018BA8, 0, 520 },
    { 38, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09018C80, 0, 660 },
    { 38, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09018CAA, 0, 662 },
    { 26, 5, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09018CDA, 0, 710 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09018CF4, 0, 790 },
    { 26, 2, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09018D60, 0, 792 },
    { 26, 2, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09018DCC, 0, 794 },
    { 38, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09018E84, MSG_SCRIPT_FLAG_END, 822 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent160Script[13] = {
    { 38, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF12FC, 0, 250 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF12E0, 0, 280 },
    { 38, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF1298, 0, 460 },
    { 38, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF124C, 0, 462 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF1208, 0, 490 },
    { 38, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF11C8, 0, 520 },
    { 38, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF11B0, 0, 660 },
    { 38, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF1154, 0, 662 },
    { 26, 5, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE5A10, 0, 710 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF1120, 0, 790 },
    { 26, 2, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF10EC, 0, 792 },
    { 26, 2, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF10A8, 0, 794 },
    { 38, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF1070, MSG_SCRIPT_FLAG_END, 822 },
};

#include "event_160_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent160Script[13] = {
    { 38, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F698F8, 0, 250 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6990C, 0, 280 },
    { 38, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69920, 0, 460 },
    { 38, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69934, 0, 462 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69948, 0, 490 },
    { 38, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6995C, 0, 520 },
    { 38, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69970, 0, 660 },
    { 38, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69984, 0, 662 },
    { 26, 5, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69998, 0, 710 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F699AC, 0, 790 },
    { 26, 2, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F699C0, 0, 792 },
    { 26, 2, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F699D4, 0, 794 },
    { 38, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F699E8, MSG_SCRIPT_FLAG_END, 822 },
};
#endif

static const EvSoundCue sEvent160SoundCues[7] = {
    { 65535, 0, 0, 0 },
    { SONG_EV_WARPOUT, 130, 0, 0 },
    { SONG_BGM_EVENT_XIII, 160, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_SND_359, 260, 0, 0 },
    { SONG_SND_359, 750, 0, 0 },
    { SONG_BGM_EVENT_XIII, 705, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT2, 755, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent160Camera[1] = {
    { -64537, 188160, 61184, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent160Track0[13] = {
    { 515, 1, { 0, 0 }, 151552, 86784, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 518, 130, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, 0, 0 },
    { 515, 140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 532, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 532, 210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 532, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 560, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 534, 590, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 534, 640, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 534, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 563, 750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 560, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent160Track1[4] = {
    { 721, 130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 721, 300, { 0, 0 }, 198144, 64000, 0, 0, { 0, 0 }, 2, EventCharaFadeIn, 0 },
    { 721, 430, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 721, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaTrack sEvent160Tracks[2] = {
    { sEvent160Track0, 44, { 0, 0, 0 } },
    { sEvent160Track1, 67, { 0, 0, 0 } },
};

const EventSequenceDef gEvent160 = {
    2,
    { 0, 0, 0 },
    sEvent160Tracks,
    sEvent160Camera,
    sEvent160Script,
    sEvent160SoundCues,
    0,
    880,
    0,
    1,
    0,
    0,
    0,
    0,
    176,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_161_text.inc"

static const MessageScriptEntry sEvent161Script[5] = {
    { 38, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901933C, 0, 100 },
    { 38, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901938E, 0, 102 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09019454, 0, 200 },
    { 38, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901948C, 0, 230 },
    { 38, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901950C, MSG_SCRIPT_FLAG_END, 232 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent161Script[5] = {
    { 38, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF1758, 0, 100 },
    { 38, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF1704, 0, 102 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF16E0, 0, 200 },
    { 38, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF1698, 0, 230 },
    { 38, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF1684, MSG_SCRIPT_FLAG_END, 232 },
};

#include "event_161_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent161Script[5] = {
    { 38, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F69894, 0, 100 },
    { 38, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F698A8, 0, 102 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F698BC, 0, 200 },
    { 38, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F698D0, 0, 230 },
    { 38, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F698E4, MSG_SCRIPT_FLAG_END, 232 },
};
#endif

static const EvSoundCue sEvent161SoundCues[2] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_EV_WARPIN, 260, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent161Camera[1] = {
    { -64537, 188160, 61184, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent161Track0[4] = {
    { 561, 120, { 0, 0 }, 179200, 72448, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 561, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 562, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 563, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent161Track1[4] = {
    { 721, 260, { 0, 0 }, 198144, 64000, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 721, 300, { 0, 0 }, 198144, 64000, 0, 0, { 0, 0 }, 2, EventCharaFadeOut, 0 },
    { 721, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 721, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaTrack sEvent161Tracks[2] = {
    { sEvent161Track0, 44, { 0, 0, 0 } },
    { sEvent161Track1, 67, { 0, 0, 0 } },
};

const EventSequenceDef gEvent161 = {
    2,
    { 0, 0, 0 },
    sEvent161Tracks,
    sEvent161Camera,
    sEvent161Script,
    sEvent161SoundCues,
    0,
    340,
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

#ifdef VERSION_US
#include "event_162_text.inc"

static const MessageScriptEntry sEvent162Script[10] = {
    { 57, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09019748, 0, 130 },
    { 55, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_09019770, 0, 220 },
    { 57, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_090197E6, 0, 250 },
    { 55, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901980A, 0, 280 },
    { 55, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09019870, 0, 282 },
    { 55, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090198E8, 0, 284 },
    { 57, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09019932, 0, 315 },
    { 55, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_09019996, 0, 345 },
    { 57, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09019A02, 0, 375 },
    { 55, 1, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_09019A82, MSG_SCRIPT_FLAG_END, 410 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent162Script[10] = {
    { 57, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF1BE8, 0, 130 },
    { 55, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF1BBC, 0, 220 },
    { 57, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF1BAC, 0, 250 },
    { 55, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF1B70, 0, 280 },
    { 55, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF1B28, 0, 282 },
    { 55, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF1AF4, 0, 284 },
    { 57, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF1AC0, 0, 315 },
    { 55, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF1A8C, 0, 345 },
    { 57, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF1A50, 0, 375 },
    { 55, 1, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF1A00, MSG_SCRIPT_FLAG_END, 410 },
};

#include "event_162_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent162Script[10] = {
    { 57, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C8B4, 0, 130 },
    { 55, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C8C8, 0, 220 },
    { 57, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C8DC, 0, 250 },
    { 55, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C8F0, 0, 280 },
    { 55, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C904, 0, 282 },
    { 55, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C918, 0, 284 },
    { 57, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C92C, 0, 315 },
    { 55, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C940, 0, 345 },
    { 57, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C954, 0, 375 },
    { 55, 1, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C968, MSG_SCRIPT_FLAG_END, 410 },
};
#endif

static const EvSoundCue sEvent162SoundCues[2] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_BGM_EVENT_XIII, 455, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent162Camera[1] = {
    { -65116, 83456, 64256, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent162Track0[6] = {
    { 883, 3, { 0, 0 }, 46848, 58624, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 885, 100, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, 0, 0 },
    { 883, 310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 887, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 883, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 883, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent162Track1[6] = {
    { 889, 160, { 0, 0 }, 97024, 77056, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 889, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 889, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 902, 190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 902, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 902, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaTrack sEvent162Tracks[2] = {
    { sEvent162Track0, 82, { 0, 0, 0 } },
    { sEvent162Track1, 83, { 0, 0, 0 } },
};

const EventSequenceDef gEvent162 = {
    2,
    { 0, 0, 0 },
    sEvent162Tracks,
    sEvent162Camera,
    sEvent162Script,
    sEvent162SoundCues,
    0,
    460,
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

#ifdef VERSION_US
#include "event_163_text.inc"

static const MessageScriptEntry sEvent163Script[16] = {
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09019E1C, 0, 250 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09019E30, 0, 300 },
    { 27, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09019E6A, MSG_SCRIPT_FLAG_SILHOUETTE, 330 },
    { 27, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09019EAC, 0, 490 },
    { 27, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09019F06, 0, 570 },
    { 27, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09019F7A, 0, 572 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09019FC6, 0, 610 },
    { 27, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09019FFA, 0, 640 },
    { 27, 2, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901A024, 0, 642 },
    { 27, 2, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901A08E, 0, 644 },
    { 27, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901A14A, 0, 700 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901A1C0, 0, 805 },
    { 27, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901A1FA, 0, 840 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901A2AE, 0, 870 },
    { 27, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901A2C0, 0, 900 },
    { 27, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901A37E, MSG_SCRIPT_FLAG_END, 940 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent163Script[16] = {
    { 26, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF2230, 0, 250 },
    { 26, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF2214, 0, 300 },
    { 27, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF21F0, MSG_SCRIPT_FLAG_SILHOUETTE, 330 },
    { 27, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF21D8, 0, 490 },
    { 27, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF2198, 0, 570 },
    { 27, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF2160, 0, 572 },
    { 26, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF214C, 0, 610 },
    { 27, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF2138, 0, 640 },
    { 27, 2, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF2108, 0, 642 },
    { 27, 2, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF20B8, 0, 644 },
    { 27, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF207C, 0, 700 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF2064, 0, 805 },
    { 27, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF2010, 0, 840 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF2004, 0, 870 },
    { 27, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF1FBC, 0, 900 },
    { 27, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF1FA0, MSG_SCRIPT_FLAG_END, 940 },
};

#include "event_163_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent163Script[16] = {
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C774, 0, 250 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C788, 0, 300 },
    { 27, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C79C, MSG_SCRIPT_FLAG_SILHOUETTE, 330 },
    { 27, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C7B0, 0, 490 },
    { 27, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C7C4, 0, 570 },
    { 27, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C7D8, 0, 572 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C7EC, 0, 610 },
    { 27, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C800, 0, 640 },
    { 27, 2, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C814, 0, 642 },
    { 27, 2, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C828, 0, 644 },
    { 27, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C83C, 0, 700 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C850, 0, 805 },
    { 27, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C864, 0, 840 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C878, 0, 870 },
    { 27, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C88C, 0, 900 },
    { 27, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C8A0, MSG_SCRIPT_FLAG_END, 940 },
};
#endif

static const EvSoundCue sEvent163SoundCues[5] = {
    { 65535, 0, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 390, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT_UNREST, 895, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT2, 905, 0, 0 },
    { SONG_SND_359, 910, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent163Camera[4] = {
    { -65535, 145920, 82944, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -65205, 0, 0, -7168, 44, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -64536, 177152, 69120, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, 0 },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent163Track0[14] = {
    { 515, 1, { 0, 0 }, 145920, 90112, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 518, 120, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, 0, 0 },
    { 515, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 532, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 532, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 532, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 715, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 532, 725, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 532, 775, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 532, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 538, 810, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent163Track1[8] = {
    { 695, 332, { 0, 0 }, 212224, 58368, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 711, 450, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, 0, 0 },
    { 695, 635, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 706, 643, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 695, 695, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 717, 710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 695, 910, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 698, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaTrack sEvent163Tracks[2] = {
    { sEvent163Track0, 44, { 0, 0, 0 } },
    { sEvent163Track1, 65, { 0, 0, 0 } },
};

const EventSequenceDef gEvent163 = {
    2,
    { 0, 0, 0 },
    sEvent163Tracks,
    sEvent163Camera,
    sEvent163Script,
    sEvent163SoundCues,
    0,
    1000,
    0,
    1,
    0,
    0,
    0,
    0,
    171,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_164_text.inc"

static const MessageScriptEntry sEvent164Script[11] = {
    { 26, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901A93C, 0, 100 },
    { 27, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901A9B4, 0, 130 },
    { 27, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901AA4E, 0, 132 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901AAE8, 0, 160 },
    { 27, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901AB72, 0, 235 },
    { 27, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901ABD4, 0, 405 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901AC64, 0, 430 },
    { 27, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901AC76, 0, 460 },
    { 27, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901ACE2, 0, 462 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901AD48, 0, 565 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901AD68, MSG_SCRIPT_FLAG_END, 700 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent164Script[11] = {
    { 26, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF28E8, 0, 100 },
    { 27, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF28A8, 0, 130 },
    { 27, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF2868, 0, 132 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF2830, 0, 160 },
    { 27, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF27F8, 0, 235 },
    { 27, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF27B0, 0, 405 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FC6D90, 0, 430 },
    { 27, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF278C, 0, 460 },
    { 27, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF2764, 0, 462 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08F9E46C, 0, 565 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF2744, MSG_SCRIPT_FLAG_END, 700 },
};

#include "event_164_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent164Script[11] = {
    { 26, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C698, 0, 100 },
    { 27, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C6AC, 0, 130 },
    { 27, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C6C0, 0, 132 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C6D4, 0, 160 },
    { 27, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C6E8, 0, 235 },
    { 27, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C6FC, 0, 405 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C710, 0, 430 },
    { 27, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C724, 0, 460 },
    { 27, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C738, 0, 462 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C74C, 0, 565 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C760, MSG_SCRIPT_FLAG_END, 700 },
};
#endif

static const EvSoundCue sEvent164SoundCues[3] = {
    { SONG_BGM_EVENT_UNREST, 0, 0, 0 },
    { SONG_SND_376, 165, 0, 0 },
    { SONG_SND_378, 194, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent164Camera[8] = {
    { -65371, 182784, 66560, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -65356, 191232, 60160, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 20, { 0, 0 }, 0 },
    { -65346, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 10, { 0, 0 }, 0 },
    { -65341, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -65331, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 10, { 0, 0 }, 0 },
    { -65286, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -64946, 154112, 80896, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 100, { 0, 0 }, 0 },
    { -62536, 166656, 75520, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 50, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent164Track0[14] = {
    { 561, 165, { 0, 0 }, 171264, 76288, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 548, 191, { 0, 0 }, 188160, 69632, 0, 515, { 0, 0 }, 67, 0, 0 },
    { 515, 194, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 550, 230, { 0, 0 }, 146176, 89856, 0, 515, { 0, 0 }, 67, 0, 0 },
    { 555, 385, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 556, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 425, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 538, 435, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 538, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 590, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 522, 645, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, 0, 0 },
    { 515, 649, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, 0, 0 },
    { 515, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent164Track1[8] = {
    { 705, 191, { 0, 0 }, 194048, 66304, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 695, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 711, 385, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, 0, 0 },
    { 695, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 696, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 696, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 710, 1000, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, 0, 0 },
    { 695, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent164Track2[3] = {
    { 926, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, 0, 0 },
    { 926, 250, { 0, 0 }, 194048, 60160, 0, 0, { 0, 0 }, 16658, 0, 0 },
    { 926, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, 0, 0 },
};

static const EventCharaTrack sEvent164Tracks[3] = {
    { sEvent164Track0, 44, { 0, 0, 0 } },
    { sEvent164Track1, 65, { 0, 0, 0 } },
    { sEvent164Track2, 92, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent164 = {
    3,
    { 0, 0, 0 },
    sEvent164Tracks,
    sEvent164Camera,
    sEvent164Script,
    sEvent164SoundCues,
    0,
    760,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    165,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent164 = {
    3,
    { 0, 0, 0 },
    sEvent164Tracks,
    sEvent164Camera,
    sEvent164Script,
    sEvent164SoundCues,
    0,
    760,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    163,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_165_text.inc"

static const MessageScriptEntry sEvent165Script[6] = {
    { 38, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901B39C, 0, 160 },
    { 27, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901B3EC, 0, 190 },
    { 38, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901B46A, 0, 360 },
    { 27, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901B4D4, 0, 390 },
    { 38, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901B580, 0, 420 },
    { 27, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901B62A, MSG_SCRIPT_FLAG_END, 450 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent165Script[6] = {
    { 38, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF2FF4, 0, 160 },
    { 27, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF2FBC, 0, 190 },
    { 38, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF2F84, 0, 360 },
    { 27, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF2F38, 0, 390 },
    { 38, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF2EF0, 0, 420 },
    { 27, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF2EA8, MSG_SCRIPT_FLAG_END, 450 },
};

#include "event_165_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent165Script[6] = {
    { 38, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C620, 0, 160 },
    { 27, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C634, 0, 190 },
    { 38, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C648, 0, 360 },
    { 27, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C65C, 0, 390 },
    { 38, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C670, 0, 420 },
    { 27, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C684, MSG_SCRIPT_FLAG_END, 450 },
};
#endif

static const EvSoundCue sEvent165SoundCues[2] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_BGM_EVENT_XIII, 505, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent165Camera[1] = {
    { -64537, 68608, 51712, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent165Track0[3] = {
    { 696, 1, { 0, 0 }, 31744, 77312, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 712, 130, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, 0, 0 },
    { 696, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent165Track1[5] = {
    { 721, 110, { 0, 0 }, 78080, 56576, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 721, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 721, 330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 721, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 721, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaTrack sEvent165Tracks[2] = {
    { sEvent165Track0, 65, { 0, 0, 0 } },
    { sEvent165Track1, 67, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent165 = {
    2,
    { 0, 0, 0 },
    sEvent165Tracks,
    sEvent165Camera,
    sEvent165Script,
    sEvent165SoundCues,
    0,
    510,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    166,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent165 = {
    2,
    { 0, 0, 0 },
    sEvent165Tracks,
    sEvent165Camera,
    sEvent165Script,
    sEvent165SoundCues,
    0,
    510,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    164,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_166_text.inc"

static const MessageScriptEntry sEvent166Script[14] = {
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901B8D4, 0, 115 },
    { 56, 1, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901B920, 0, 330 },
    { 26, 2, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901B97E, 0, 500 },
    { 56, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901BA08, 0, 530 },
    { 56, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901BA96, 0, 532 },
    { 56, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901BB04, 0, 534 },
    { 26, 2, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901BB8A, 0, 565 },
    { 56, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901BBEA, 0, 595 },
    { 56, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901BC6A, 0, 597 },
    { 26, 1, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901BD12, 0, 770 },
    { 26, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901BD2E, 0, 772 },
    { 26, 2, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901BDCA, 0, 785 },
    { 56, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901BE18, 0, 950 },
    { 56, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901BE3C, MSG_SCRIPT_FLAG_END, 1100 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent166Script[14] = {
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF35D0, 0, 115 },
    { 56, 1, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF35B0, 0, 330 },
    { 26, 2, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF3568, 0, 500 },
    { 56, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF3534, 0, 530 },
    { 56, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF34E4, 0, 532 },
    { 56, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF34A0, 0, 534 },
    { 26, 2, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF3488, 0, 565 },
    { 56, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF343C, 0, 595 },
    { 56, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF3404, 0, 597 },
    { 26, 1, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF33E4, 0, 770 },
    { 26, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF338C, 0, 772 },
    { 26, 2, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF335C, 0, 785 },
    { 56, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF3350, 0, 950 },
    { 56, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF32F8, MSG_SCRIPT_FLAG_END, 1100 },
};

#include "event_166_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent166Script[14] = {
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C508, 0, 115 },
    { 56, 1, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C51C, 0, 330 },
    { 26, 2, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C530, 0, 500 },
    { 56, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C544, 0, 530 },
    { 56, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C558, 0, 532 },
    { 56, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C56C, 0, 534 },
    { 26, 2, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C580, 0, 565 },
    { 56, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C594, 0, 595 },
    { 56, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C5A8, 0, 597 },
    { 26, 1, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C5BC, 0, 770 },
    { 26, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C5D0, 0, 772 },
    { 26, 2, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C5E4, 0, 785 },
    { 56, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C5F8, 0, 950 },
    { 56, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C60C, MSG_SCRIPT_FLAG_END, 1100 },
};
#endif

static const EvSoundCue sEvent166SoundCues[5] = {
    { 65535, 0, 0, 0 },
    { SONG_SND_379, 410, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 411, 0, 0 },
    { SONG_EV_CARDTHR, 989, 0, 0 },
    { SONG_SND_379, 1150, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent166Camera[2] = {
    { -65146, 175872, 68352, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -62536, 188416, 61696, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 80, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent166Track0[24] = {
    { 515, 1, { 0, 0 }, 141568, 92672, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 522, 100, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 100, 0, 0 },
    { 515, 103, { 0, 0 }, 175872, 75264, 0, 515, { 0, 0 }, 67, 0, 0 },
    { 515, 110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 538, 120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 514, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 514, 340, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 514, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 538, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 610, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 530, 620, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 530, 750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 530, 773, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 538, 788, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 995, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 559, 1180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 4000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent166Track1[10] = {
    { 688, 410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 688, 450, { 0, 0 }, 201728, 63232, 0, 0, { 0, 0 }, 2, EventCharaFadeIn, 0 },
    { 688, 795, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 688, 925, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 688, 970, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 692, 1050, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 688, 1150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 688, 1200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaFadeOut, 0 },
    { 688, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 688, 4000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent166Track2[7] = {
    { 591, 988, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8258, 0, 0 },
    { 591, 989, { 0, 0 }, 194816, 58624, 0, 0, { 0, 0 }, 16706, 0, 0 },
    { 591, 1000, { 0, 0 }, 181504, 65536, 0, 591, { 0, 0 }, 323, 0, 0 },
    { 591, 1008, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 604, 1180, { 0, 0 }, 175872, 75264, 0, 0, { 0, 0 }, 338, 0, 0 },
    { 591, 1200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 591, 4000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98373, 0, 0 },
};

static const EventCharaTrack sEvent166Tracks[3] = {
    { sEvent166Track0, 44, { 0, 0, 0 } },
    { sEvent166Track1, 64, { 0, 0, 0 } },
    { sEvent166Track2, 50, { 0, 0, 0 } },
};

const EventSequenceDef gEvent166 = {
    3,
    { 0, 0, 0 },
    sEvent166Tracks,
    sEvent166Camera,
    sEvent166Script,
    sEvent166SoundCues,
    0,
    1240,
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

#ifdef VERSION_US
#include "event_167_text.inc"

static const MessageScriptEntry sEvent167Script[32] = {
    { 20, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_08FDBD9E, 0, 100 },
    { 38, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_08FDBE1E, 0, 130 },
    { 38, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_08FDBE4C, 0, 132 },
    { 38, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_08FDBEE2, 0, 134 },
    { 54, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_08FDBF48, 0, 160 },
    { 38, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_08FDBFC6, 0, 180 },
    { 20, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_08FDC024, 0, 220 },
    { 38, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_08FDC108, 0, 240 },
    { 54, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_08FDC188, 0, 260 },
    { 38, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_08FDC1B2, 0, 280 },
    { 20, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_08FDC1F4, 0, 430 },
    { 20, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_08FDC28C, 0, 470 },
    { 38, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_08FDC2E6, 0, 490 },
    { 27, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901C6BC, 0, 690 },
    { 20, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901C70E, 0, 720 },
    { 54, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901C784, 0, 750 },
    { 54, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901C87C, 0, 752 },
    { 54, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901C8E4, 0, 835 },
    { 27, 3, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901C980, 0, 920 },
    { 27, 2, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901C9E4, 0, 925 },
    { 54, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901CAC0, 0, 950 },
    { 38, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901CB3C, 0, 1130 },
    { 27, 2, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901CB5E, 0, 1150 },
    { 38, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901CB98, 0, 1180 },
    { 54, 2, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901CBFA, 0, 1270 },
    { 27, 2, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901CC3E, 0, 1420 },
    { 54, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901CC66, 0, 1635 },
    { 54, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901CCEA, 0, 1670 },
    { 54, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901CDCA, 0, 1672 },
    { 54, 2, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901CE56, 0, 1674 },
    { 27, 3, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901CE88, 0, 1710 },
    { 27, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901CE90, MSG_SCRIPT_FLAG_END, 2070 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent167Script[32] = {
    { 20, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FC04C4, 0, 100 },
    { 38, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FC04A8, 0, 130 },
    { 38, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FC0458, 0, 132 },
    { 38, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FC0430, 0, 134 },
    { 54, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FC03DC, 0, 160 },
    { 38, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FC03C0, 0, 180 },
    { 20, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FC0370, 0, 220 },
    { 38, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FC0340, 0, 240 },
    { 54, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FC0324, 0, 260 },
    { 38, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FC0300, 0, 280 },
    { 20, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FC02B8, 0, 430 },
    { 20, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FC0270, 0, 470 },
    { 38, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FC023C, 0, 490 },
    { 27, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF4314, 0, 690 },
    { 20, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF42D8, 0, 720 },
    { 54, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF4288, 0, 750 },
    { 54, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF424C, 0, 752 },
    { 54, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF4200, 0, 835 },
    { 27, 3, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF41D0, 0, 920 },
    { 27, 2, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF4174, 0, 925 },
    { 54, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF4120, 0, 950 },
    { 38, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF4110, 0, 1130 },
    { 27, 2, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF40E4, 0, 1150 },
    { 38, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF40B8, 0, 1180 },
    { 54, 2, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF408C, 0, 1270 },
    { 27, 2, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF407C, 0, 1420 },
    { 54, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF403C, 0, 1635 },
    { 54, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF3FE4, 0, 1670 },
    { 54, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF3F98, 0, 1672 },
    { 54, 2, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF3F80, 0, 1674 },
    { 27, 3, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF3F74, 0, 1710 },
    { 27, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF3F64, MSG_SCRIPT_FLAG_END, 2070 },
};

#include "event_167_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent167Script[32] = {
    { 20, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F65028, 0, 100 },
    { 38, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6503C, 0, 130 },
    { 38, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F65050, 0, 132 },
    { 38, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F65064, 0, 134 },
    { 54, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F65078, 0, 160 },
    { 38, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6508C, 0, 180 },
    { 20, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F650A0, 0, 220 },
    { 38, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F650B4, 0, 240 },
    { 54, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F650C8, 0, 260 },
    { 38, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F650DC, 0, 280 },
    { 20, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F650F0, 0, 430 },
    { 20, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F65104, 0, 470 },
    { 38, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F65118, 0, 490 },
    { 27, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C38C, 0, 690 },
    { 20, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C3A0, 0, 720 },
    { 54, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C3B4, 0, 750 },
    { 54, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C3C8, 0, 752 },
    { 54, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C3DC, 0, 835 },
    { 27, 3, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C3F0, 0, 920 },
    { 27, 2, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C404, 0, 925 },
    { 54, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C418, 0, 950 },
    { 38, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C42C, 0, 1130 },
    { 27, 2, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C440, 0, 1150 },
    { 38, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C454, 0, 1180 },
    { 54, 2, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C468, 0, 1270 },
    { 27, 2, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C47C, 0, 1420 },
    { 54, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C490, 0, 1635 },
    { 54, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C4A4, 0, 1670 },
    { 54, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C4B8, 0, 1672 },
    { 54, 2, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C4CC, 0, 1674 },
    { 27, 3, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C4E0, 0, 1710 },
    { 27, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C4F4, MSG_SCRIPT_FLAG_END, 2070 },
};
#endif

static const EvSoundCue sEvent167SoundCues[5] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_EV_CARDTHR, 448, 0, 0 },
    { SONG_SND_359, 1430, 0, 0 },
    { SONG_EV_FLASH00, 1460, 0, 0 },
    { SONG_BGM_EVENT_XIII, 1750, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

#if defined(VERSION_US) || defined(VERSION_JP)
static const EventCameraKeyframe sEvent167Camera[7] = {
    { -65006, 60672, 55040, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -64076, 65536, 58112, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 60, { 0, 0 }, 0 },
    { -64066, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 10, { 0, 0 }, 0 },
    { -63986, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -63806, 99840, 67072, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 100, { 0, 0 }, 0 },
    { -61466, 99840, -12544, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 500, { 0, 0 }, 0 },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
};
#elif defined(VERSION_EU)
static const EventCameraKeyframe sEvent167Camera[7] = {
    { -65006, 60672, 55040, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -64076, 65536, 58112, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 60, { 0, 0 }, 0 },
    { -64066, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 10, { 0, 0 }, 0 },
    { -63986, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -63806, 99840, 67072, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 100, { 0, 0 }, 0 },
    { -63266, 99840, -12544, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 500, { 0, 0 }, 0 },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
};
#endif

static const EventBgEffectEntry sEvent167BgEffects[5] = {
    { 1770, 0, 0, 0, 0 },
    { 1850, 0, 0, 0, 0x14 },
    { 3380, 0, 0, 0, 0 },
    { 3450, 0, 0, 0, 0x2 },
    { 3500, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent167Track0[7] = {
    { 485, 215, { 0, 0 }, 51200, 55808, 0, 0, { 0, 0 }, 82, 0, 0 },
    { 509, 225, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 85, 0, 0 },
    { 509, 290, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 85, 0, 0 },
    { 509, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 80, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 485, 431, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 85, 0, 0 },
    { 500, 475, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 85, 0, 0 },
    { 485, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32853, 0, 0 },
};

static const EventCharaKeyframe sEvent167Track2[11] = {
    { 738, 110, { 0, 0 }, 62464, 70656, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 738, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 739, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 738, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 721, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 721, 970, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 727, 980, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 727, 1110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 727, 1160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 729, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 721, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent167Track1[14] = {
    { 856, 1300, { 0, 0 }, 74752, 61952, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 856, 1320, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 881, 1380, { 0, 0 }, 85760, 69120, 0, 856, { 0, 0 }, 67, 0, 0 },
    { 856, 1390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 856, 1440, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 871, 1520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 856, 1570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 856, 1580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 881, 1620, { 0, 0 }, 93952, 71680, 0, 856, { 0, 0 }, 67, 0, 0 },
    { 856, 1630, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 857, 1830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 856, 1850, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaFadeOut, 0 },
    { 856, 1870, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 856, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent167Track3[6] = {
    { 591, 447, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 591, 448, { 0, 0 }, 55296, 56320, -5120, 0, { 0, 0 }, 338, 0, 0 },
    { 591, 459, { 0, 0 }, 57856, 63488, -5120, 591, { 0, 0 }, 323, 0, 0 },
    { 591, 463, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 610, 480, { 0, 0 }, 63488, 70656, 0, 0, { 0, 0 }, 274, 0, 0 },
    { 591, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98370, 0, 0 },
};

static const EventCharaKeyframe sEvent167Track4[23] = {
    { 696, 540, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, 0, 0 },
    { 696, 541, { 0, 0 }, 99072, 91648, 0, 0, { 0, 0 }, 16386, 0, 0 },
    { 712, 660, { 0, 0 }, 72960, 74752, 0, 696, { 0, 0 }, 3, 0, 0 },
    { 696, 765, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 696, 815, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateQuestionTask },
    { 696, 855, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 716, 905, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 716, 922, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 708, 930, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 696, 1145, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 708, 1155, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 696, 1190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 716, 1240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 716, 1250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 696, 1340, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 696, 1430, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 701, 1460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 702, 1465, { 0, 0 }, 80896, 70656, 0, 696, { 0, 0 }, 67, 0, 0 },
    { 713, 1495, { 0, 0 }, 103424, 71168, 0, 695, { 0, 0 }, 323, 0, 0 },
    { 713, 1830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, 0, 0 },
    { 713, 1850, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 320, EventCharaFadeOut, 0 },
    { 696, 2070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 713, 5070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33093, 0, 0 },
};

static const EventCharaTrack sEvent167Tracks[5] = {
    { sEvent167Track0, 43, { 0, 0, 0 } },
    { sEvent167Track1, 81, { 0, 0, 0 } },
    { sEvent167Track2, 67, { 0, 0, 0 } },
    { sEvent167Track3, 50, { 0, 0, 0 } },
    { sEvent167Track4, 65, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent167 = {
    5,
    { 0, 0, 0 },
    sEvent167Tracks,
    sEvent167Camera,
    sEvent167Script,
    sEvent167SoundCues,
    sEvent167BgEffects,
    2130,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    168,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent167 = {
    5,
    { 0, 0, 0 },
    sEvent167Tracks,
    sEvent167Camera,
    sEvent167Script,
    sEvent167SoundCues,
    sEvent167BgEffects,
    2270,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    166,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_168_text.inc"

static const MessageScriptEntry sEvent168Script[19] = {
    { 54, 4, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901DBE4, 0, 100 },
    { 54, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901DC44, 0, 280 },
    { 27, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901DCC2, 0, 300 },
    { 27, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901DCF0, 0, 450 },
    { 54, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901DD36, 0, 480 },
    { 27, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901DD54, 0, 570 },
    { 27, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901DDD2, 0, 650 },
    { 27, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901DE30, 0, 830 },
    { 54, 4, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901DE4C, 0, 1170 },
    { 54, 2, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901DEC4, 0, 1172 },
    { 54, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901DFD4, 0, 1260 },
    { 54, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901E032, 0, 1262 },
    { 60, 4, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901E0D6, 0, 1305 },
    { 60, 4, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901E0F8, 0, 1420 },
    { 60, 4, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901E184, 0, 1422 },
    { 60, 4, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901E214, 0, 1424 },
    { 54, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901E244, 0, 1620 },
    { 54, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901E2A6, 0, 1622 },
    { 54, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901E346, MSG_SCRIPT_FLAG_END, 1624 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent168Script[19] = {
    { 54, 4, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF5334, 0, 100 },
    { 54, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF52F4, 0, 280 },
    { 27, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF52DC, 0, 300 },
    { 27, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF52A4, 0, 450 },
    { 54, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF5298, 0, 480 },
    { 27, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF525C, 0, 570 },
    { 27, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF5230, 0, 650 },
    { 27, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF5224, 0, 830 },
    { 54, 4, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF51D8, 0, 1170 },
    { 54, 2, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF517C, 0, 1172 },
    { 54, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF512C, 0, 1260 },
    { 54, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF50D8, 0, 1262 },
    { 60, 4, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF50C8, 0, 1305 },
    { 60, 4, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF5094, 0, 1420 },
    { 60, 4, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF503C, 0, 1422 },
    { 60, 4, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF501C, 0, 1424 },
    { 54, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF4FDC, 0, 1620 },
    { 54, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF4F84, 0, 1622 },
    { 54, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF4F68, MSG_SCRIPT_FLAG_END, 1624 },
};

#include "event_168_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent168Script[19] = {
    { 54, 4, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C210, 0, 100 },
    { 54, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C224, 0, 280 },
    { 27, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C238, 0, 300 },
    { 27, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C24C, 0, 450 },
    { 54, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C260, 0, 480 },
    { 27, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C274, 0, 570 },
    { 27, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C288, 0, 650 },
    { 27, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C29C, 0, 830 },
    { 54, 4, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C2B0, 0, 1170 },
    { 54, 2, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C2C4, 0, 1172 },
    { 54, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C2D8, 0, 1260 },
    { 54, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C2EC, 0, 1262 },
    { 60, 4, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C300, 0, 1305 },
    { 60, 4, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C314, 0, 1420 },
    { 60, 4, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C328, 0, 1422 },
    { 60, 4, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C33C, 0, 1424 },
    { 54, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C350, 0, 1620 },
    { 54, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C364, 0, 1622 },
    { 54, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C378, MSG_SCRIPT_FLAG_END, 1624 },
};
#endif

static const EvSoundCue sEvent168SoundCues[2] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_BGM_EVENT_XIII, 1680, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent168Camera[3] = {
    { -65036, 77056, 66816, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -64346, 73216, 67328, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, 0 },
    { -64536, 73216, 71680, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 80, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent168Track0[10] = {
    { 856, 940, { 0, 0 }, 87296, 66816, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 856, 1070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 856, 1190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 881, 1230, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, 0, 0 },
    { 856, 1320, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 856, 1370, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateQuestionTask },
    { 856, 1450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 856, 1580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 856, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 856, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent168Track1[6] = {
    { 444, 120, { 0, 0 }, 71680, 82688, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 444, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 444, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 444, 810, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 444, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 444, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent168Track2[2] = {
    { 919, 30, { 0, 0 }, 72192, 82432, 0, 0, { 0, 0 }, 322, 0, 0 },
    { 919, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33093, 0, 0 },
};

static const EventCharaKeyframe sEvent168Track3[13] = {
    { 695, 301, { 0, 0 }, 39680, 66048, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 711, 400, { 0, 0 }, 62208, 77824, 0, 695, { 0, 0 }, 67, 0, 0 },
    { 695, 410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 696, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 695, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 703, 760, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 704, 790, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 695, 850, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 695, 860, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 696, 890, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 712, 1400, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, 0, 0 },
    { 696, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 696, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent168Track4[4] = {
    { 909, 624, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8514, 0, 0 },
    { 916, 766, { 0, 0 }, 62208, 77824, 0, 0, { 0, 0 }, 16722, 0, 0 },
    { 909, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 322, 0, 0 },
    { 909, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98373, 0, 0 },
};

static const EventCharaTrack sEvent168Tracks[5] = {
    { sEvent168Track0, 81, { 0, 0, 0 } },
    { sEvent168Track1, 35, { 0, 0, 0 } },
    { sEvent168Track2, 86, { 0, 0, 0 } },
    { sEvent168Track3, 65, { 0, 0, 0 } },
    { sEvent168Track4, 85, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent168 = {
    5,
    { 0, 0, 0 },
    sEvent168Tracks,
    sEvent168Camera,
    sEvent168Script,
    sEvent168SoundCues,
    0,
    1685,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    169,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent168 = {
    5,
    { 0, 0, 0 },
    sEvent168Tracks,
    sEvent168Camera,
    sEvent168Script,
    sEvent168SoundCues,
    0,
    1685,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    167,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_169_text.inc"

static const MessageScriptEntry sEvent169Script[11] = {
    { 55, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901EB08, 0, 280 },
    { 57, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901EB52, 0, 320 },
    { 55, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901EB76, 0, 350 },
    { 55, 5, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901EBC0, 0, 354 },
    { 57, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901EC60, 0, 400 },
    { 57, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901EC98, 0, 402 },
    { 57, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901ED34, 0, 404 },
    { 55, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901EDB4, 0, 440 },
    { 57, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901EE4A, 0, 470 },
    { 57, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901EE7C, 0, 472 },
    { 55, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901EEF8, MSG_SCRIPT_FLAG_END, 560 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent169Script[11] = {
    { 55, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF5C3C, 0, 280 },
    { 57, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF5C24, 0, 320 },
    { 55, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF5BCC, 0, 350 },
    { 55, 5, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF5B9C, 0, 354 },
    { 57, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF5B8C, 0, 400 },
    { 57, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF5B38, 0, 402 },
    { 57, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF5B00, 0, 404 },
    { 55, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF5AAC, 0, 440 },
    { 57, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF5A94, 0, 470 },
    { 57, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF5A48, 0, 472 },
    { 55, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF5A34, MSG_SCRIPT_FLAG_END, 560 },
};

#include "event_169_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent169Script[11] = {
    { 55, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C134, 0, 280 },
    { 57, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C148, 0, 320 },
    { 55, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C15C, 0, 350 },
    { 55, 5, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C170, 0, 354 },
    { 57, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C184, 0, 400 },
    { 57, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C198, 0, 402 },
    { 57, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C1AC, 0, 404 },
    { 55, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C1C0, 0, 440 },
    { 57, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C1D4, 0, 470 },
    { 57, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C1E8, 0, 472 },
    { 55, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C1FC, MSG_SCRIPT_FLAG_END, 560 },
};
#endif

static const EvSoundCue sEvent169SoundCues[3] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_EV_WARPOUT, 150, 0, 0 },
    { SONG_BGM_EVENT_XIII, 615, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent169Camera[1] = {
    { -64537, 79616, 50432, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent169Track0[5] = {
    { 889, 230, { 0, 0 }, 72448, 56320, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 889, 352, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 890, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 892, 520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 890, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent169Track1[4] = {
    { 883, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 883, 300, { 0, 0 }, 87808, 64000, 0, 0, { 0, 0 }, 2, EventCharaFadeIn, 0 },
    { 887, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 883, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaTrack sEvent169Tracks[2] = {
    { sEvent169Track0, 83, { 0, 0, 0 } },
    { sEvent169Track1, 82, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent169 = {
    2,
    { 0, 0, 0 },
    sEvent169Tracks,
    sEvent169Camera,
    sEvent169Script,
    sEvent169SoundCues,
    0,
    620,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    170,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent169 = {
    2,
    { 0, 0, 0 },
    sEvent169Tracks,
    sEvent169Camera,
    sEvent169Script,
    sEvent169SoundCues,
    0,
    620,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    168,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_170_text.inc"

static const MessageScriptEntry sEvent170Script[2] = {
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901F1C8, 0, 250 },
    { 26, 5, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901F1F0, MSG_SCRIPT_FLAG_END, 350 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent170Script[2] = {
    { 26, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF5E7C, 0, 250 },
    { 26, 5, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF5E50, MSG_SCRIPT_FLAG_END, 350 },
};

#include "event_170_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent170Script[2] = {
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C10C, 0, 250 },
    { 26, 5, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C120, MSG_SCRIPT_FLAG_END, 350 },
};
#endif

static const EvSoundCue sEvent170SoundCues[1] = {
    { SONG_BGM_T13THFLOOR, 0, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent170Camera[1] = {
    { -64537, 190976, 59648, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent170Track0[5] = {
    { 515, 1, { 0, 0 }, 156416, 83968, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 518, 140, { 0, 0 }, 187136, 67840, 0, 515, { 0, 0 }, 67, 0, 0 },
    { 515, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 557, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent170Track1[3] = {
    { 603, 203, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 603, 1000, { 0, 0 }, 187136, 67840, 0, 0, { 0, 0 }, 338, 0, 0 },
    { 603, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaTrack sEvent170Tracks[2] = {
    { sEvent170Track0, 44, { 0, 0, 0 } },
    { sEvent170Track1, 50, { 0, 0, 0 } },
};

const EventSequenceDef gEvent170 = {
    2,
    { 0, 0, 0 },
    sEvent170Tracks,
    sEvent170Camera,
    sEvent170Script,
    sEvent170SoundCues,
    0,
    410,
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

#ifdef VERSION_US
#include "event_171_text.inc"

static const MessageScriptEntry sEvent171Script[11] = {
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901F424, 0, 430 },
    { 57, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901F46E, 0, 460 },
    { 57, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901F50C, 0, 462 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901F56E, 0, 490 },
    { 57, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901F596, 0, 520 },
    { 57, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901F5C6, 0, 730 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901F6D0, 0, 780 },
    { 57, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901F6F2, 0, 810 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901F74C, 0, 970 },
    { 57, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901F758, 0, 1020 },
    { 57, 2, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901F7FA, MSG_SCRIPT_FLAG_END, 1022 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent171Script[11] = {
    { 26, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF62D4, 0, 430 },
    { 57, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF6298, 0, 460 },
    { 57, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF625C, 0, 462 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF6240, 0, 490 },
    { 57, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF6230, 0, 520 },
    { 57, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF61DC, 0, 730 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF61C8, 0, 780 },
    { 57, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF61A0, 0, 810 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF6194, 0, 970 },
    { 57, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF6148, 0, 1020 },
    { 57, 2, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF6128, MSG_SCRIPT_FLAG_END, 1022 },
};

#include "event_171_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent171Script[11] = {
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C030, 0, 430 },
    { 57, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C044, 0, 460 },
    { 57, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C058, 0, 462 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C06C, 0, 490 },
    { 57, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C080, 0, 520 },
    { 57, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C094, 0, 730 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C0A8, 0, 780 },
    { 57, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C0BC, 0, 810 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C0D0, 0, 970 },
    { 57, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C0E4, 0, 1020 },
    { 57, 2, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C0F8, MSG_SCRIPT_FLAG_END, 1022 },
};
#endif

static const EvSoundCue sEvent171SoundCues[6] = {
    { 65535, 0, 0, 0 },
    { SONG_BGM_EVENT_XIII, 250, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT_XIII, 805, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT2, 815, 0, 0 },
    { SONG_SND_380, 835, 0, 0 },
    { SONG_SND_359, 1040, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent171Camera[7] = {
    { -65336, 158464, 76544, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -64716, 192000, 60416, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 70, { 0, 0 }, 0 },
    { -64681, 199680, 54272, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 15, { 0, 0 }, 0 },
    { -64586, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_SMALL | CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -64566, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -63536, 192000, 60416, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 30, { 0, 0 }, 0 },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent171Track0[14] = {
    { 518, 1, { 0, 0 }, 131584, 97536, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 518, 110, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, 0, 0 },
    { 515, 120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 532, 130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 532, 180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 532, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 518, 410, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, 0, 0 },
    { 515, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 515, 860, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 555, 972, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 556, 986, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 1040, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 560, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent171Track1[3] = {
    { 887, 820, { 0, 0 }, 199424, 63488, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 888, 990, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 883, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent171Track2[3] = {
    { 926, 835, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, 0, 0 },
    { 926, 880, { 0, 0 }, 199680, 54272, 0, 0, { 0, 0 }, 16658, 0, 0 },
    { 926, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, 0, 0 },
};

static const EventCharaTrack sEvent171Tracks[3] = {
    { sEvent171Track0, 44, { 0, 0, 0 } },
    { sEvent171Track1, 82, { 0, 0, 0 } },
    { sEvent171Track2, 92, { 0, 0, 0 } },
};

const EventSequenceDef gEvent171 = {
    3,
    { 0, 0, 0 },
    sEvent171Tracks,
    sEvent171Camera,
    sEvent171Script,
    sEvent171SoundCues,
    0,
    1090,
    0,
    1,
    0,
    0,
    0,
    0,
    167,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_172_text.inc"

static const MessageScriptEntry sEvent172Script[6] = {
    { 57, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901FD90, 0, 100 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901FDB4, 0, 140 },
    { 26, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901FDCA, 0, 144 },
    { 57, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901FE30, 0, 180 },
    { 57, 2, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901FE68, 0, 182 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0901FF50, MSG_SCRIPT_FLAG_END, 480 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent172Script[6] = {
    { 57, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF689C, 0, 100 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF688C, 0, 140 },
    { 26, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF6844, 0, 144 },
    { 57, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF6810, 0, 180 },
    { 57, 2, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF67C0, 0, 182 },
    { 26, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FC3F14, MSG_SCRIPT_FLAG_END, 480 },
};

#include "event_172_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent172Script[6] = {
    { 57, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BF68, 0, 100 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BF7C, 0, 140 },
    { 26, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BF90, 0, 144 },
    { 57, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BFA4, 0, 180 },
    { 57, 2, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BFB8, 0, 182 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BFCC, MSG_SCRIPT_FLAG_END, 480 },
};
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
    { -65266, 192256, 60672, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -65216, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_SMALL | CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -64935, 182528, 65792, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_SMALL | CAMERA_MODE_APPROACH, 100, { 0, 0 }, 0 },
    { -64536, 38912, 38400, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
};

static const EventBgEffectEntry sEvent172BgEffects[5] = {
    { 320, 0, 0, 0, 0 },
    { 450, 0, 60, 0, 0x14 },
    { 3310, 0, 0, 0, 0 },
    { 3380, 0, 0, 0, 0x2 },
    { 3500, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent172Track0[7] = {
    { 555, 280, { 0, 0 }, 182016, 71936, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 556, 290, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 532, 580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 532, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaFadeOut, 0 },
    { 515, 1000, { 0, 0 }, 256000, 256000, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 515, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent172Track1[4] = {
    { 886, 230, { 0, 0 }, 199424, 63488, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 886, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaFadeOut, 0 },
    { 886, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 883, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent172Track2[3] = {
    { 926, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, 0, 0 },
    { 926, 300, { 0, 0 }, 199936, 60672, 0, 0, { 0, 0 }, 16658, 0, 0 },
    { 926, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, 0, 0 },
};

static const EventCharaTrack sEvent172Tracks[3] = {
    { sEvent172Track0, 44, { 0, 0, 0 } },
    { sEvent172Track1, 82, { 0, 0, 0 } },
    { sEvent172Track2, 92, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent172 = {
    3,
    { 0, 0, 0 },
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
    0,
    173,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent172 = {
    3,
    { 0, 0, 0 },
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
    0,
    171,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_173_text.inc"

static const MessageScriptEntry sEvent173Script[15] = {
    { 26, 5, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09020354, 0, 350 },
    { 56, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09020394, MSG_SCRIPT_FLAG_SILHOUETTE, 400 },
    { 26, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090203D0, 0, 600 },
    { 56, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_090203E4, MSG_SCRIPT_FLAG_SILHOUETTE, 640 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902041C, 0, 670 },
    { 56, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_090204A6, MSG_SCRIPT_FLAG_SILHOUETTE, 700 },
    { 26, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09020512, 0, 730 },
    { 56, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_09020520, MSG_SCRIPT_FLAG_SILHOUETTE, 760 },
    { 56, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902056A, MSG_SCRIPT_FLAG_SILHOUETTE, 762 },
    { 56, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090205FC, MSG_SCRIPT_FLAG_SILHOUETTE, 764 },
    { 56, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09020690, 0, 850 },
    { 61, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_090206C2, MSG_SCRIPT_FLAG_SILHOUETTE, 870 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09020710, 0, 955 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09020728, 0, 1275 },
    { 56, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09020744, MSG_SCRIPT_FLAG_END, 1305 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent173Script[15] = {
    { 26, 5, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF6F60, 0, 350 },
    { 56, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF6F48, MSG_SCRIPT_FLAG_SILHOUETTE, 400 },
    { 26, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF6F34, 0, 600 },
    { 56, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF6F14, MSG_SCRIPT_FLAG_SILHOUETTE, 640 },
    { 26, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF6ED8, 0, 670 },
    { 56, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF6EA8, MSG_SCRIPT_FLAG_SILHOUETTE, 700 },
    { 26, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF6E9C, 0, 730 },
    { 56, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF6E68, MSG_SCRIPT_FLAG_SILHOUETTE, 760 },
    { 56, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF6E1C, MSG_SCRIPT_FLAG_SILHOUETTE, 762 },
    { 56, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF6DCC, MSG_SCRIPT_FLAG_SILHOUETTE, 764 },
    { 56, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF6DBC, 0, 850 },
    { 61, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF6D94, MSG_SCRIPT_FLAG_SILHOUETTE, 870 },
    { 26, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FED9AC, 0, 955 },
    { 26, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEFF00, 0, 1275 },
    { 56, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF6D84, MSG_SCRIPT_FLAG_END, 1305 },
};

#include "event_173_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent173Script[15] = {
    { 26, 5, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BD38, 0, 350 },
    { 56, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BD4C, MSG_SCRIPT_FLAG_SILHOUETTE, 400 },
    { 26, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BD60, 0, 600 },
    { 56, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BD74, MSG_SCRIPT_FLAG_SILHOUETTE, 640 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BD88, 0, 670 },
    { 56, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BD9C, MSG_SCRIPT_FLAG_SILHOUETTE, 700 },
    { 26, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BDB0, 0, 730 },
    { 56, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BDC4, MSG_SCRIPT_FLAG_SILHOUETTE, 760 },
    { 56, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BDD8, MSG_SCRIPT_FLAG_SILHOUETTE, 762 },
    { 56, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BDEC, MSG_SCRIPT_FLAG_SILHOUETTE, 764 },
    { 56, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BE00, 0, 850 },
    { 61, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BE14, MSG_SCRIPT_FLAG_SILHOUETTE, 870 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BE28, 0, 955 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BE3C, 0, 1275 },
    { 56, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BE50, MSG_SCRIPT_FLAG_END, 1305 },
};
#endif

static const EvSoundCue sEvent173SoundCues[4] = {
    { 65535, 0, 0, 0 },
    { SONG_SND_379, 810, 0, 0 },
    { SONG_EV_WHITEOUT, 1085, 0, 0 },
    { SONG_EV_FLASH02, 1335, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent173Camera[11] = {
    { -65316, 30720, 39936, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -65016, 30720, 35840, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, 0 },
    { -64701, 30720, 30720, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, 0 },
    { -64561, 34560, 26112, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 30, { 0, 0 }, 0 },
    { -64531, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, 0 },
    { -64511, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, 0 },
    { -64451, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, 0 },
    { -64391, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 60, { 0, 0 }, 0 },
    { -64386, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -64201, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 100, { 0, 0 }, 0 },
    { -62911, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 60, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent173Track0[15] = {
    { 547, 200, { 0, 0 }, 27904, 37888, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 545, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 545, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 546, 590, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 725, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 526, 763, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 820, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 514, 825, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 830, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 835, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 532, 895, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 1270, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 532, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent173Track1[3] = {
    { 688, 810, { 0, 0 }, 89088, 12800, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 694, 915, { 0, 0 }, 42240, 29696, 0, 0, { 0, 0 }, 2, EventCharaFadeIn, 0 },
    { 688, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent173Track2[5] = {
    { 920, 871, { 0, 0 }, 91136, 12800, 0, 0, { 0, 0 }, 8258, 0, 0 },
    { 920, 872, { 0, 0 }, 35072, 3328, 0, 0, { 0, 0 }, 16706, 0, 0 },
    { 920, 950, { 0, 0 }, 35328, 26880, 0, 920, { 0, 0 }, 323, 0, 0 },
    { 920, 1147, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 453, 0, 0 },
    { 920, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98370, 0, 0 },
};

static const EventCharaKeyframe sEvent173Track3[3] = {
    { 746, 1147, { 0, 0 }, 96512, 13568, 0, 0, { 0, 0 }, 8258, 0, 0 },
    { 746, 2000, { 0, 0 }, 34048, 32768, 0, 0, { 0, 0 }, 16450, 0, 0 },
    { 746, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent173Track4[3] = {
    { 928, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, 0, 0 },
    { 927, 470, { 0, 0 }, 27904, 29952, 0, 0, { 0, 0 }, 16658, 0, 0 },
    { 928, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, 0, 0 },
};

static const EventCharaTrack sEvent173Tracks[5] = {
    { sEvent173Track0, 44, { 0, 0, 0 } },
    { sEvent173Track1, 64, { 0, 0, 0 } },
    { sEvent173Track2, 87, { 0, 0, 0 } },
    { sEvent173Track3, 69, { 0, 0, 0 } },
    { sEvent173Track4, 93, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent173 = {
    5,
    { 0, 0, 0 },
    sEvent173Tracks,
    sEvent173Camera,
    sEvent173Script,
    sEvent173SoundCues,
    0,
    1485,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    174,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent173 = {
    5,
    { 0, 0, 0 },
    sEvent173Tracks,
    sEvent173Camera,
    sEvent173Script,
    sEvent173SoundCues,
    0,
    1485,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    172,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_174_text.inc"

static const MessageScriptEntry sEvent174Script[4] = {
    { 26, 5, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09020EBC, 0, 100 },
    { 26, 5, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09020EC8, 0, 250 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09020EF6, 0, 485 },
    { 26, 5, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09020F4E, MSG_SCRIPT_FLAG_END, 750 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent174Script[4] = {
    { 26, 5, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF2004, 0, 100 },
    { 26, 5, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF761C, 0, 250 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF75F0, 0, 485 },
    { 26, 5, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF75D4, MSG_SCRIPT_FLAG_END, 750 },
};

#include "event_174_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent174Script[4] = {
    { 26, 5, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BFE0, 0, 100 },
    { 26, 5, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BFF4, 0, 250 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C008, 0, 485 },
    { 26, 5, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6C01C, MSG_SCRIPT_FLAG_END, 750 },
};
#endif

static const EvSoundCue sEvent174SoundCues[1] = {
    { SONG_BGM_T13THFLOOR, 0, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent174Camera[1] = {
    { -64537, 194816, 62720, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent174Track0[15] = {
    { 547, 150, { 0, 0 }, 195840, 64512, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 545, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 546, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 430, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 440, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 538, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 514, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 514, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 514, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 564, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaTrack sEvent174Tracks[1] = {
    { sEvent174Track0, 44, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent174 = {
    1,
    { 0, 0, 0 },
    sEvent174Tracks,
    sEvent174Camera,
    sEvent174Script,
    sEvent174SoundCues,
    0,
    810,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    175,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent174 = {
    1,
    { 0, 0, 0 },
    sEvent174Tracks,
    sEvent174Camera,
    sEvent174Script,
    sEvent174SoundCues,
    0,
    810,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    173,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_175_text.inc"

static const MessageScriptEntry sEvent175Script[13] = {
    { 55, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09021260, 0, 100 },
    { 55, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090212BC, 0, 102 },
    { 20, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09021308, 0, 250 },
    { 55, 5, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_090213B2, 0, 280 },
    { 20, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090213C8, 0, 310 },
    { 20, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090213DE, 0, 312 },
    { 20, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090214D8, 0, 314 },
    { 55, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902152E, 0, 340 },
    { 20, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090215CE, 0, 370 },
    { 55, 5, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_090216BA, 0, 410 },
    { 20, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09021708, 0, 460 },
    { 55, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_090217A0, 0, 500 },
    { 55, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090217D8, MSG_SCRIPT_FLAG_END, 502 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent175Script[13] = {
    { 55, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF7C94, 0, 100 },
    { 55, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF7C74, 0, 102 },
    { 20, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF7C1C, 0, 250 },
    { 55, 5, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF7C00, 0, 280 },
    { 20, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF7BE8, 0, 310 },
    { 20, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF7B8C, 0, 312 },
    { 20, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF7B5C, 0, 314 },
    { 55, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF7B10, 0, 340 },
    { 20, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF7AB8, 0, 370 },
    { 55, 5, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF7A80, 0, 410 },
    { 20, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF7A34, 0, 460 },
    { 55, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF7A18, 0, 500 },
    { 55, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF79E8, MSG_SCRIPT_FLAG_END, 502 },
};

#include "event_175_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent175Script[13] = {
    { 55, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BE64, 0, 100 },
    { 55, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BE78, 0, 102 },
    { 20, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BE8C, 0, 250 },
    { 55, 5, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BEA0, 0, 280 },
    { 20, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BEB4, 0, 310 },
    { 20, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BEC8, 0, 312 },
    { 20, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BEDC, 0, 314 },
    { 55, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BEF0, 0, 340 },
    { 20, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BF04, 0, 370 },
    { 55, 5, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BF18, 0, 410 },
    { 20, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BF2C, 0, 460 },
    { 55, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BF40, 0, 500 },
    { 55, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BF54, MSG_SCRIPT_FLAG_END, 502 },
};
#endif

static const EvSoundCue sEvent175SoundCues[2] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_BGM_EVENT_XIII, 555, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent175Camera[2] = {
    { -65396, 56320, 53248, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -64537, 62976, 55808, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 50, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent175Track0[4] = {
    { 891, 200, { 0, 0 }, 55808, 61440, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 892, 495, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 890, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 889, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent175Track1[4] = {
    { 486, 103, { 0, 0 }, 97280, 83712, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 502, 227, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, 0, 0 },
    { 486, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 486, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaTrack sEvent175Tracks[2] = {
    { sEvent175Track0, 83, { 0, 0, 0 } },
    { sEvent175Track1, 43, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent175 = {
    2,
    { 0, 0, 0 },
    sEvent175Tracks,
    sEvent175Camera,
    sEvent175Script,
    sEvent175SoundCues,
    0,
    560,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    176,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent175 = {
    2,
    { 0, 0, 0 },
    sEvent175Tracks,
    sEvent175Camera,
    sEvent175Script,
    sEvent175SoundCues,
    0,
    560,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    174,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_176_text.inc"

static const MessageScriptEntry sEvent176Script[14] = {
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09021B1C, 0, 240 },
    { 55, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09021BB4, 0, 460 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09021C92, 0, 490 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09021CB4, 0, 600 },
    { 55, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09021CF0, 0, 630 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09021D6C, 0, 660 },
    { 55, 5, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09021D96, 0, 690 },
    { 55, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09021DFE, 0, 692 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09021E5C, 0, 720 },
    { 55, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09021E68, 0, 750 },
    { 55, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09021F52, 0, 752 },
    { 55, 5, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09021F84, 0, 891 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09021FE2, 0, 950 },
    { 55, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09022012, MSG_SCRIPT_FLAG_END, 980 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent176Script[14] = {
    { 26, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF81B8, 0, 240 },
    { 55, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF8174, 0, 460 },
    { 26, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF8160, 0, 490 },
    { 26, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF813C, 0, 600 },
    { 55, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF8108, 0, 630 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEB59C, 0, 660 },
    { 55, 5, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF80CC, 0, 690 },
    { 55, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF8094, 0, 692 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08F9114C, 0, 720 },
    { 55, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF8048, 0, 750 },
    { 55, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF8028, 0, 752 },
    { 55, 5, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF7FFC, 0, 891 },
    { 26, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF7FE0, 0, 950 },
    { 55, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF7FCC, MSG_SCRIPT_FLAG_END, 980 },
};

#include "event_176_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent176Script[14] = {
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BC20, 0, 240 },
    { 55, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BC34, 0, 460 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BC48, 0, 490 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BC5C, 0, 600 },
    { 55, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BC70, 0, 630 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BC84, 0, 660 },
    { 55, 5, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BC98, 0, 690 },
    { 55, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BCAC, 0, 692 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BCC0, 0, 720 },
    { 55, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BCD4, 0, 750 },
    { 55, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BCE8, 0, 752 },
    { 55, 5, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BCFC, 0, 891 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BD10, 0, 950 },
    { 55, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BD24, MSG_SCRIPT_FLAG_END, 980 },
};
#endif

static const EvSoundCue sEvent176SoundCues[8] = {
    { 65535, 0, 0, 0 },
    { SONG_EV_RUMBLE, 120, 0, 0 },
    { SONG_EV_RUMBLE, 150, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_EV_WARPOUT, 250, 0, 0 },
    { SONG_BGM_EVENT_XIII, 260, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_EV_CARDTHR, 850, 0, 0 },
    { SONG_EV_WARPIN, 1030, 0, 0 },
    { SONG_BGM_EVENT_XIII, 1105, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent176Camera[5] = {
    { -65416, 174080, 72960, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -65336, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_MEDIUM | CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -65326, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_SMALL | CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -65206, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -62536, 183552, 65280, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 80, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent176Track0[15] = {
    { 515, 1, { 0, 0 }, 140032, 91904, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 518, 140, { 0, 0 }, 173568, 76032, 0, 515, { 0, 0 }, 67, 0, 0 },
    { 515, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 532, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 532, 210, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 532, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 515, 595, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 538, 605, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 858, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 559, 890, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 558, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent176Track1[6] = {
    { 889, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 889, 770, { 0, 0 }, 192256, 67328, 0, 0, { 0, 0 }, 2, EventCharaFadeIn, 0 },
    { 893, 880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 895, 1030, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 889, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaFadeOut, 0 },
    { 889, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent176Track2[8] = {
    { 591, 849, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 258, 0, 0 },
    { 591, 850, { 0, 0 }, 185600, 61184, 0, 0, { 0, 0 }, 258, 0, 0 },
    { 591, 860, { 0, 0 }, 178432, 65792, 0, 591, { 0, 0 }, 259, 0, 0 },
    { 591, 870, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 258, 0, 0 },
    { 604, 890, { 0, 0 }, 173568, 76032, 0, 0, { 0, 0 }, 338, 0, 0 },
    { 591, 913, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 258, 0, 0 },
    { 603, 3000, { 0, 0 }, 173568, 76032, 0, 0, { 0, 0 }, 338, 0, 0 },
    { 591, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33029, 0, 0 },
};

static const EventCharaTrack sEvent176Tracks[3] = {
    { sEvent176Track0, 44, { 0, 0, 0 } },
    { sEvent176Track1, 83, { 0, 0, 0 } },
    { sEvent176Track2, 50, { 0, 0, 0 } },
};

const EventSequenceDef gEvent176 = {
    3,
    { 0, 0, 0 },
    sEvent176Tracks,
    sEvent176Camera,
    sEvent176Script,
    sEvent176SoundCues,
    0,
    1110,
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

#ifdef VERSION_US
#include "event_177_text.inc"

static const MessageScriptEntry sEvent177Script[8] = {
    { 26, 5, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090226C0, 0, 380 },
    { 26, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09022726, 0, 460 },
    { 26, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090227A0, 0, 462 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090227E2, 0, 660 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090227F6, 0, 800 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09022800, 0, 980 },
    { 26, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902289C, 0, 1080 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090228E6, MSG_SCRIPT_FLAG_END, 1405 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent177Script[8] = {
    { 26, 5, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF88C0, 0, 380 },
    { 26, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF8888, 0, 460 },
    { 26, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF886C, 0, 462 },
    { 26, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF885C, 0, 660 },
    { 26, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE8424, 0, 800 },
    { 26, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF8814, 0, 980 },
    { 26, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF87F4, 0, 1080 },
    { 26, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF87E8, MSG_SCRIPT_FLAG_END, 1405 },
};

#include "event_177_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent177Script[8] = {
    { 26, 5, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B720, 0, 380 },
    { 26, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B734, 0, 460 },
    { 26, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B748, 0, 462 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B75C, 0, 660 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B770, 0, 800 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B784, 0, 980 },
    { 26, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B798, 0, 1080 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B7AC, MSG_SCRIPT_FLAG_END, 1405 },
};
#endif

static const EvSoundCue sEvent177SoundCues[5] = {
    { SONG_BGM_DESTINY_FIELD, 0, 0, 0 },
    { SONG_SND_356, 1, 0, 0 },
    { SONG_SND_370, 1280, 0, 0 },
    { SONG_SND_356, 1585, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_DESTINY_FIELD, 1586, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent177Camera[7] = {
    { -65536, 96768, 77312, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, 0 },
    { -65385, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 80, { 0, 0 }, 0 },
    { -64846, 0, 0, -6912, 44, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -64666, 31744, 42752, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 100, { 0, 0 }, 0 },
    { -63986, 34560, 45312, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 30, { 0, 0 }, 0 },
    { -62536, 47104, 51968, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 100, { 0, 0 }, 0 },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent177Track0[24] = {
    { 515, 1, { 0, 0 }, 130816, 102656, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 518, 150, { 0, 0 }, 96768, 84224, 0, 515, { 0, 0 }, 3, 0, 0 },
    { 515, 200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 540, 330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 540, 382, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 518, 430, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, 0, 0 },
    { 515, 500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 518, 580, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, 0, 0 },
    { 532, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 532, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 532, 665, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 810, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 522, 880, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, 0, 0 },
    { 515, 883, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, 0, 0 },
    { 515, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 950, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateQuestionTask },
    { 515, 1320, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 532, 1330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 532, 1380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 515, 1400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 538, 1407, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 540, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent177Track1[6] = {
    { 676, 1100, { 0, 0 }, 25600, 45312, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 676, 1230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 676, 1280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 676, 1350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaFadeOut, 0 },
    { 676, 2000, { 0, 0 }, 120320, 146176, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 676, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent177Track2[6] = {
    { 627, 1100, { 0, 0 }, 35584, 50432, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 627, 1230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 627, 1280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 627, 1350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaFadeOut, 0 },
    { 627, 2000, { 0, 0 }, 120320, 146176, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 627, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent177Track3[6] = {
    { 678, 1100, { 0, 0 }, 27392, 53248, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 678, 1230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 678, 1280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 678, 1350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaFadeOut, 0 },
    { 678, 2000, { 0, 0 }, 120320, 146176, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 678, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaTrack sEvent177Tracks[4] = {
    { sEvent177Track0, 44, { 0, 0, 0 } },
    { sEvent177Track1, 60, { 0, 0, 0 } },
    { sEvent177Track2, 55, { 0, 0, 0 } },
    { sEvent177Track3, 61, { 0, 0, 0 } },
};

const EventSequenceDef gEvent177 = {
    4,
    { 0, 0, 0 },
    sEvent177Tracks,
    sEvent177Camera,
    sEvent177Script,
    sEvent177SoundCues,
    0,
    1590,
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
    1,
    255,
    255,
};

#ifdef VERSION_US
#include "event_178_text.inc"

static const MessageScriptEntry sEvent178Script[14] = {
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090230F4, 0, 250 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09023102, 0, 600 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09023140, 0, 690 },
    { 26, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09023148, 0, 880 },
    { 55, 5, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_09023160, 0, 910 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_090231A6, 0, 1100 },
    { 55, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090231D6, 0, 1130 },
    { 55, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902325A, 0, 1132 },
    { 55, 5, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090232B8, 0, 1134 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902338A, 0, 1160 },
    { 26, 2, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902342E, 0, 1162 },
    { 26, 5, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09023476, 0, 1330 },
    { 55, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902349E, 0, 1360 },
    { 55, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902353E, MSG_SCRIPT_FLAG_END, 1460 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent178Script[14] = {
    { 26, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF93A8, 0, 250 },
    { 26, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF9388, 0, 600 },
    { 26, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FB93C4, 0, 690 },
    { 26, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF937C, 0, 880 },
    { 55, 5, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF9348, 0, 910 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FEB59C, 0, 1100 },
    { 55, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF9308, 0, 1130 },
    { 55, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF92D0, 0, 1132 },
    { 55, 5, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF9278, 0, 1134 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF9224, 0, 1160 },
    { 26, 2, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF91F0, 0, 1162 },
    { 26, 5, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF91D8, 0, 1330 },
    { 55, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF919C, 0, 1360 },
    { 55, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF917C, MSG_SCRIPT_FLAG_END, 1460 },
};

#include "event_178_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent178Script[14] = {
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B7C0, 0, 250 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B7D4, 0, 600 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B7E8, 0, 690 },
    { 26, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B7FC, 0, 880 },
    { 55, 5, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B810, 0, 910 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B824, 0, 1100 },
    { 55, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B838, 0, 1130 },
    { 55, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B84C, 0, 1132 },
    { 55, 5, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B860, 0, 1134 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B874, 0, 1160 },
    { 26, 2, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B888, 0, 1162 },
    { 26, 5, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B89C, 0, 1330 },
    { 55, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B8B0, 0, 1360 },
    { 55, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B8C4, MSG_SCRIPT_FLAG_END, 1460 },
};
#endif

static const EvSoundCue sEvent178SoundCues[4] = {
    { 65535, 0, 0, 0 },
    { SONG_SND_370, 630, 0, 0 },
    { SONG_EV_WARPOUT, 940, 0, 0 },
    { SONG_BGM_EVENT_XIII, 950, EV_SOUND_FLAG_FADE_IN | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent178Camera[6] = {
    { -65366, 73728, 61440, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -65176, 36608, 80128, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, 0 },
    { -64516, 41984, 78080, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, 0 },
    { -63991, 53760, 71680, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, 0 },
    { -63936, 31488, 153856, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 1, { 0, 0 }, 0 },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
};

static const EventBgEffectEntry sEvent178BgEffects[5] = {
    { 1490, 0, 0, 0, 0 },
    { 1540, 0, 60, 0, 0x14 },
    { 3310, 0, 0, 0, 0 },
    { 4000, 0, 0, 0, 0x2 },
    { 5000, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent178Track0[23] = {
    { 514, 1, { 0, 0 }, 104704, 60416, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 520, 80, { 0, 0 }, 73984, 71424, 0, 514, { 0, 0 }, 3, 0, 0 },
    { 514, 83, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, 0, 0 },
    { 514, 100, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 526, 110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 526, 160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 526, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 516, 360, { 0, 0 }, 47104, 81920, 0, 514, { 0, 0 }, 3, 0, 0 },
    { 514, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 514, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 526, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 528, 990, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 1030, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 1155, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 538, 1180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 1200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 540, 1545, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 540, 2000, { 0, 0 }, 24832, 164096, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent178Track1[6] = {
    { 889, 940, { 0, 0 }, 120320, 11776, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 889, 1455, { 0, 0 }, 62464, 75264, 0, 0, { 0, 0 }, 2, EventCharaFadeIn, 0 },
    { 899, 1520, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 898, 1545, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 889, 2000, { 0, 0 }, 40192, 157440, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 889, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent178Track2[4] = {
    { 420, 630, { 0, 0 }, 36608, 86272, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 420, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaFadeOut, 0 },
    { 420, 1000, { 0, 0 }, 120320, 11776, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 420, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98373, 0, 0 },
};

static const EventCharaTrack sEvent178Tracks[3] = {
    { sEvent178Track0, 44, { 0, 0, 0 } },
    { sEvent178Track1, 83, { 0, 0, 0 } },
    { sEvent178Track2, 34, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent178 = {
    3,
    { 0, 0, 0 },
    sEvent178Tracks,
    sEvent178Camera,
    sEvent178Script,
    sEvent178SoundCues,
    sEvent178BgEffects,
    1700,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    179,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent178 = {
    3,
    { 0, 0, 0 },
    sEvent178Tracks,
    sEvent178Camera,
    sEvent178Script,
    sEvent178SoundCues,
    sEvent178BgEffects,
    1700,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    177,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_179_text.inc"

static const MessageScriptEntry sEvent179Script[6] = {
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09023CDC, 0, 355 },
    { 55, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09023D04, 0, 385 },
    { 55, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09023DBE, 0, 510 },
    { 26, 5, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09023DF2, 0, 640 },
    { 55, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09023DFE, 0, 670 },
    { 55, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09023F0A, MSG_SCRIPT_FLAG_END, 674 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent179Script[6] = {
    { 26, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF9B78, 0, 355 },
    { 55, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF9B24, 0, 385 },
    { 55, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF9B10, 0, 510 },
    { 26, 5, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF2004, 0, 640 },
    { 55, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF9ABC, 0, 670 },
    { 55, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FF9A60, MSG_SCRIPT_FLAG_END, 674 },
};

#include "event_179_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent179Script[6] = {
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BA40, 0, 355 },
    { 55, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BA54, 0, 385 },
    { 55, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BA68, 0, 510 },
    { 26, 5, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BA7C, 0, 640 },
    { 55, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BA90, 0, 670 },
    { 55, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BAA4, MSG_SCRIPT_FLAG_END, 674 },
};
#endif

static const EvSoundCue sEvent179SoundCues[4] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_BGM_EVENT_XIII, 635, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT2, 642, 0, 0 },
    { SONG_SND_363, 840, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent179Camera[8] = {
    { -65536, 83456, 98048, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -65441, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_BLACK | CAMERA_MODE_KEEP, 30, { 0, 0 }, 0 },
    { -65436, 32256, 98048, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 1, { 0, 0 }, 0 },
    { -65331, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_BLACK | CAMERA_MODE_KEEP, 30, { 0, 0 }, 0 },
    { -65026, 52992, 25088, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 1, { 0, 0 }, 0 },
    { -64856, 70144, 26624, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, 0 },
    { -64437, 97024, 33536, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 120, { 0, 0 }, 0 },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
};

static const EventBgEffectEntry sEvent179BgEffects[5] = {
    { 180, 0, 0, 0, 0 },
    { 200, 0, 10, 0, 0x14 },
    { 210, 0, 0, 0, 0 },
    { 211, 0, 0, 0, 0x2 },
    { 250, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent179Track0[11] = {
    { 540, 205, { 0, 0 }, 25344, 109312, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 540, 250, { 0, 0 }, 46080, 36352, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 515, 260, { 0, 0 }, 46080, 36352, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 514, 290, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 532, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 514, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 514, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent179Track1[8] = {
    { 889, 205, { 0, 0 }, 40960, 102400, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 889, 410, { 0, 0 }, 61696, 29440, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 889, 460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 899, 512, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 898, 625, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 889, 672, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 899, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 889, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent179Track2[3] = {
    { 515, 840, { 0, 0 }, 95744, 40192, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 515, 1600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, func_0806FB6C, 0 },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaTrack sEvent179Tracks[3] = {
    { sEvent179Track0, 44, { 0, 0, 0 } },
    { sEvent179Track1, 83, { 0, 0, 0 } },
    { sEvent179Track2, 44, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent179 = {
    3,
    { 0, 0, 0 },
    sEvent179Tracks,
    sEvent179Camera,
    sEvent179Script,
    sEvent179SoundCues,
    sEvent179BgEffects,
    900,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    180,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent179 = {
    3,
    { 0, 0, 0 },
    sEvent179Tracks,
    sEvent179Camera,
    sEvent179Script,
    sEvent179SoundCues,
    sEvent179BgEffects,
    900,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    178,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_180_text.inc"

static const MessageScriptEntry sEvent180Script[1] = {
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_090244E0, MSG_SCRIPT_FLAG_END, 100 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent180Script[1] = {
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFA074, MSG_SCRIPT_FLAG_END, 100 },
};

#include "event_180_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent180Script[1] = {
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B8D8, MSG_SCRIPT_FLAG_END, 100 },
};
#endif

static const EvSoundCue sEvent180SoundCues[1] = {
    { SONG_BGM_BOSSWORLD, 0, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent180Camera[1] = {
    { -64537, 61440, 92160, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent180Track0[2] = {
    { 514, 40, { 0, 0 }, 51200, 99840, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 526, 999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent180Track1[1] = {
    { 944, 999, { 0, 0 }, 18432, 36864, 0, 0, { 0, 0 }, 32834, 0, 0 },
};

static const EventCharaTrack sEvent180Tracks[2] = {
    { sEvent180Track0, 44, { 0, 0, 0 } },
    { sEvent180Track1, 103, { 0, 0, 0 } },
};

const EventSequenceDef gEvent180 = {
    2,
    { 0, 0, 0 },
    sEvent180Tracks,
    sEvent180Camera,
    sEvent180Script,
    sEvent180SoundCues,
    0,
    160,
    0,
    1,
    0,
    0,
    0,
    0,
    154,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_181_text.inc"

static const MessageScriptEntry sEvent181Script[7] = {
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090245FC, 0, 210 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902460A, 0, 260 },
    { 0, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09024658, 0, 290 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090246D2, 0, 440 },
    { 0, 5, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_090246DE, 0, 460 },
    { 0, 5, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09024736, 0, 462 },
    { 0, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_090247B0, MSG_SCRIPT_FLAG_END, 562 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent181Script[7] = {
    { 26, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08F9E724, 0, 210 },
    { 26, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFA314, 0, 260 },
    { 0, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFA2D0, 0, 290 },
    { 26, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFA2C4, 0, 440 },
    { 0, 5, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFA278, 0, 460 },
    { 0, 5, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFA244, 0, 462 },
    { 0, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFA218, MSG_SCRIPT_FLAG_END, 562 },
};

#include "event_181_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent181Script[7] = {
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B8EC, 0, 210 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B900, 0, 260 },
    { 0, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B914, 0, 290 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B928, 0, 440 },
    { 0, 5, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B93C, 0, 460 },
    { 0, 5, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B950, 0, 462 },
    { 0, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B964, MSG_SCRIPT_FLAG_END, 562 },
};
#endif

static const EvSoundCue sEvent181SoundCues[5] = {
    { SONG_BGM_EVENT_UNREST, 0, 0, 0 },
    { SONG_EV_FLASH01, 233, 0, 0 },
    { SONG_EV_FLASH00, 390, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 615, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_EV_WHITEOUT, 620, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent181Camera[9] = {
    { -65366, 67840, 29696, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -65356, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, 0 },
    { -65303, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -65293, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 10, { 0, 0 }, 0 },
    { -65146, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -65136, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 10, { 0, 0 }, 0 },
    { -64916, 77824, 37888, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, 0 },
    { -64536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 100, { 0, 0 }, 0 },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent181Track0[11] = {
    { 561, 100, { 0, 0 }, 65536, 36608, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 561, 150, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 561, 165, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 542, 180, { 0, 0 }, 69120, 37120, 0, 515, { 0, 0 }, 4099, 0, 0 },
    { 542, 232, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 542, 242, { 0, 0 }, 74752, 38912, 0, 515, { 0, 0 }, 4099, 0, 0 },
    { 542, 255, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 534, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 550, 415, { 0, 0 }, 87040, 40704, 0, 515, { 0, 0 }, 3, 0, 0 },
    { 547, 670, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 547, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32832, func_0806F2EC, 0 },
};

static const EventCharaKeyframe sEvent181Track1[12] = {
    { 2, 152, { 0, 0 }, 32000, 31744, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 98, 172, { 0, 0 }, 58624, 35584, 0, 2, { 0, 0 }, 4163, 0, 0 },
    { 98, 190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 103, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 98, 240, { 0, 0 }, 62208, 36096, 0, 2, { 0, 0 }, 4163, 0, 0 },
    { 98, 255, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 103, 330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 96, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 93, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 102, 586, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 103, 670, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 103, 3000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32832, func_0806F2EC, 0 },
};

static const EventCharaKeyframe sEvent181Track2[3] = {
    { 922, 610, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, 0, 0 },
    { 922, 623, { 0, 0 }, 61696, 37888, 0, 0, { 0, 0 }, 16642, 0, 0 },
    { 922, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, 0, 0 },
};

static const EventCharaTrack sEvent181Tracks[3] = {
    { sEvent181Track0, 44, { 0, 0, 0 } },
    { sEvent181Track1, 0, { 0, 0, 0 } },
    { sEvent181Track2, 89, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent181 = {
    3,
    { 0, 0, 0 },
    sEvent181Tracks,
    sEvent181Camera,
    sEvent181Script,
    sEvent181SoundCues,
    0,
    850,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    182,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent181 = {
    3,
    { 0, 0, 0 },
    sEvent181Tracks,
    sEvent181Camera,
    sEvent181Script,
    sEvent181SoundCues,
    0,
    850,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    180,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_182_text.inc"

static const MessageScriptEntry sEvent182Script[18] = {
    { 26, 5, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09024DF0, 0, 200 },
    { 28, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_09024E36, 0, 420 },
    { 28, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09024E56, 0, 580 },
    { 28, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09024EE2, 0, 582 },
    { 26, 3, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_09024F90, 0, 610 },
    { 28, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09024FAE, 0, 640 },
    { 28, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09025078, 0, 642 },
    { 26, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902510A, 0, 670 },
    { 28, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09025170, 0, 700 },
    { 28, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090251F4, 0, 702 },
    { 28, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902525C, 0, 704 },
    { 26, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_090252BA, 0, 730 },
    { 28, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09025326, 0, 760 },
    { 26, 5, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_090253BC, 0, 860 },
    { 28, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090253E6, 0, 970 },
    { 26, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902540C, 0, 1020 },
    { 26, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902542A, 0, 1210 },
    { 26, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090254A2, MSG_SCRIPT_FLAG_END, 1350 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent182Script[18] = {
    { 26, 5, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFACFC, 0, 200 },
    { 28, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFACEC, 0, 420 },
    { 28, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFACAC, 0, 580 },
    { 28, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFAC5C, 0, 582 },
    { 26, 3, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFAC48, 0, 610 },
    { 28, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFAC00, 0, 640 },
    { 28, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFABA4, 0, 642 },
    { 26, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFAB74, 0, 670 },
    { 28, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFAB40, 0, 700 },
    { 28, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFAB08, 0, 702 },
    { 28, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFAAE8, 0, 704 },
    { 26, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFAAC0, 0, 730 },
    { 28, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFAA90, 0, 760 },
    { 26, 5, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFAA80, 0, 860 },
    { 28, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFAA6C, 0, 970 },
    { 26, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFAA54, 0, 1020 },
    { 26, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFAA2C, 0, 1210 },
    { 26, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFAA24, MSG_SCRIPT_FLAG_END, 1350 },
};

#include "event_182_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent182Script[18] = {
    { 26, 5, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BAB8, 0, 200 },
    { 28, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BACC, 0, 420 },
    { 28, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BAE0, 0, 580 },
    { 28, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BAF4, 0, 582 },
    { 26, 3, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BB08, 0, 610 },
    { 28, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BB1C, 0, 640 },
    { 28, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BB30, 0, 642 },
    { 26, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BB44, 0, 670 },
    { 28, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BB58, 0, 700 },
    { 28, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BB6C, 0, 702 },
    { 28, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BB80, 0, 704 },
    { 26, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BB94, 0, 730 },
    { 28, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BBA8, 0, 760 },
    { 26, 5, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BBBC, 0, 860 },
    { 28, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BBD0, 0, 970 },
    { 26, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BBE4, 0, 1020 },
    { 26, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BBF8, 0, 1210 },
    { 26, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BC0C, MSG_SCRIPT_FLAG_END, 1350 },
};
#endif

static const EvSoundCue sEvent182SoundCues[4] = {
    { 65535, 0, 0, 0 },
    { SONG_EV_FLASH02, 1270, 0, 0 },
    { SONG_SND_702, 1440, 0, 0 },
    { SONG_SND_381, 1670, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent182Camera[7] = {
    { -65536, 98048, 32512, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, 0 },
    { -64296, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 60, { 0, 0 }, 0 },
    { -64266, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 30, { 0, 0 }, 0 },
    { -64236, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 30, { 0, 0 }, 0 },
    { -63916, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -63856, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 60, { 0, 0 }, 0 },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
};

static const EventBgEffectEntry sEvent182BgEffects[5] = {
    { 1380, 0, 0, 0, 0 },
    { 1440, 0, 0, 0, 0x14 },
    { 1490, 2, 87040, 22784, 0x1 },
    { 1600, 0, 0, 0, 0x2 },
    { 3500, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent182Track0[11] = {
    { 565, 100, { 0, 0 }, 97792, 33024, 0, 0, { 0, 0 }, 258, 0, 0 },
    { 565, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 1048837, 0, 0 },
    { 565, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 1048832, EventCharaFadeOut, 0 },
    { 565, 1100, { 0, 0 }, 41472, 17920, 0, 0, { 0, 0 }, 258, 0, 0 },
    { 514, 1205, { 0, 0 }, 97280, 38400, 0, 0, { 0, 0 }, 2306, EventCharaFadeIn, 0 },
    { 543, 1271, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2309, 0, 0 },
    { 543, 1370, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, 0, 0 },
    { 514, 1460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, 0, 0 },
    { 514, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 524549, 0, 0 },
    { 514, 2170, { 0, 0 }, 41472, 17920, 0, 0, { 0, 0 }, 258, 0, 0 },
    { 514, 9000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent182Track1[6] = {
    { 420, 450, { 0, 0 }, 29696, 39424, 0, 0, { 0, 0 }, 8194, 0, 0 },
    { 420, 930, { 0, 0 }, 97792, 38400, 0, 0, { 0, 0 }, 16642, EventCharaFadeIn, 0 },
    { 421, 1030, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, 0, 0 },
    { 421, 1060, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 256, EventCharaFadeOut, 0 },
    { 420, 1100, { 0, 0 }, 29696, 39424, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 420, 9000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98309, 0, 0 },
};

static const EventCharaKeyframe sEvent182Track2[7] = {
    { 695, 1459, { 0, 0 }, 29696, 39424, 0, 0, { 0, 0 }, 258, 0, 0 },
    { 695, 1500, { 0, 0 }, 97280, 38400, 0, 0, { 0, 0 }, 524546, 0, 0 },
    { 695, 1590, { 0, 0 }, 97280, 38400, 0, 0, { 0, 0 }, 258, 0, 0 },
    { 696, 1610, { 0, 0 }, 97280, 38400, 0, 0, { 0, 0 }, 258, 0, 0 },
    { 696, 1650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, 0, 0 },
    { 701, 1625, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, 0, 0 },
    { 702, 9000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33093, 0, 0 },
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

#ifdef VERSION_US
#include "event_183_text.inc"

static const MessageScriptEntry sEvent183Script[10] = {
    { 0, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09025B70, 0, 95 },
    { 55, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09025B8E, 0, 240 },
    { 27, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09025BD2, 0, 270 },
    { 27, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09025C52, 0, 272 },
    { 55, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09025C9E, 0, 400 },
    { 27, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09025D20, 0, 430 },
    { 55, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09025D42, 0, 460 },
    { 27, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09025DA8, 0, 490 },
    { 55, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09025DC2, 0, 550 },
    { 27, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09025DE6, MSG_SCRIPT_FLAG_END, 750 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent183Script[10] = {
    { 0, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFB460, 0, 95 },
    { 55, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFB438, 0, 240 },
    { 27, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFB404, 0, 270 },
    { 27, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFB3DC, 0, 272 },
    { 55, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFB3A4, 0, 400 },
    { 27, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFB384, 0, 430 },
    { 55, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFB348, 0, 460 },
    { 27, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFB338, 0, 490 },
    { 55, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFB324, 0, 550 },
    { 27, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFB314, MSG_SCRIPT_FLAG_END, 750 },
};

#include "event_183_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent183Script[10] = {
    { 0, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B978, 0, 95 },
    { 55, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B98C, 0, 240 },
    { 27, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B9A0, 0, 270 },
    { 27, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B9B4, 0, 272 },
    { 55, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B9C8, 0, 400 },
    { 27, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B9DC, 0, 430 },
    { 55, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B9F0, 0, 460 },
    { 27, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BA04, 0, 490 },
    { 55, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BA18, 0, 550 },
    { 27, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6BA2C, MSG_SCRIPT_FLAG_END, 750 },
};
#endif

static const EvSoundCue sEvent183SoundCues[4] = {
    { SONG_BGM_EVENT2, 0, 0, 0 },
    { SONG_SND_364, 100, 0, 0 },
    { SONG_EV_WARPIN, 600, 0, 0 },
    { SONG_BGM_EVENT2, 805, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent183Camera[7] = {
    { -65406, 61440, 27136, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -65346, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 60, { 0, 0 }, 0 },
    { -65326, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 30, { 0, 0 }, 0 },
    { -65036, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -65016, 65536, 23296, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 15, { 0, 0 }, 0 },
    { -65006, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, 0 },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent183Track0[5] = {
    { 718, 500, { 0, 0 }, 54016, 40448, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 702, 520, { 0, 0 }, 62464, 33024, 0, 696, { 0, 0 }, 4163, 0, 0 },
    { 702, 700, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 719, 714, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 696, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent183Track1[8] = {
    { 889, 190, { 0, 0 }, 11776, 44800, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 905, 300, { 0, 0 }, 70144, 28672, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 906, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 889, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 900, 600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 901, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaFadeOut, 0 },
    { 902, 1000, { 0, 0 }, 11776, 44800, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 889, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent183Track2[4] = {
    { 107, 100, { 0, 0 }, 69120, 27904, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 107, 190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, func_0806F2EC, 0 },
    { 107, 500, { 0, 0 }, 11776, 44800, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 4, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaTrack sEvent183Tracks[3] = {
    { sEvent183Track0, 65, { 0, 0, 0 } },
    { sEvent183Track1, 83, { 0, 0, 0 } },
    { sEvent183Track2, 0, { 0, 0, 0 } },
};

const EventSequenceDef gEvent183 = {
    3,
    { 0, 0, 0 },
    sEvent183Tracks,
    sEvent183Camera,
    sEvent183Script,
    sEvent183SoundCues,
    0,
    810,
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

#ifdef VERSION_US
#include "event_184_text.inc"

static const MessageScriptEntry sEvent184Script[18] = {
    { 55, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902629C, 0, 230 },
    { 55, 2, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090262C2, 0, 232 },
    { 55, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902634A, 0, 600 },
    { 55, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09026368, 0, 900 },
    { 55, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090263B8, 0, 902 },
    { 55, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09026430, 0, 1000 },
    { 20, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902643C, 0, 1050 },
    { 20, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090264B8, 0, 1230 },
    { 27, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_090264F2, 0, 1260 },
    { 20, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090264FE, 0, 1290 },
    { 20, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09026590, 0, 1292 },
    { 20, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09026638, 0, 1294 },
    { 55, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902669C, 0, 1320 },
    { 20, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090266DE, 0, 1380 },
    { 55, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902674A, 0, 1460 },
    { 20, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902677E, 0, 1500 },
    { 20, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09026798, 0, 1502 },
    { 55, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902682A, MSG_SCRIPT_FLAG_END, 1650 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent184Script[18] = {
    { 55, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFBCB4, 0, 230 },
    { 55, 2, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFBC68, 0, 232 },
    { 55, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFBC54, 0, 600 },
    { 55, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFBC1C, 0, 900 },
    { 55, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFBBDC, 0, 902 },
    { 55, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFBBCC, 0, 1000 },
    { 20, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFBB80, 0, 1050 },
    { 20, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFBB6C, 0, 1230 },
    { 27, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08F9F980, 0, 1260 },
    { 20, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFBB2C, 0, 1290 },
    { 20, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFBAF0, 0, 1292 },
    { 20, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFBAB4, 0, 1294 },
    { 55, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFBA8C, 0, 1320 },
    { 20, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFBA58, 0, 1380 },
    { 55, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFBA40, 0, 1460 },
    { 20, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFBA28, 0, 1500 },
    { 20, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFB9E0, 0, 1502 },
    { 55, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFB9D0, MSG_SCRIPT_FLAG_END, 1650 },
};

#include "event_184_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent184Script[18] = {
    { 55, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B5B8, 0, 230 },
    { 55, 2, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B5CC, 0, 232 },
    { 55, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B5E0, 0, 600 },
    { 55, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B5F4, 0, 900 },
    { 55, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B608, 0, 902 },
    { 55, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B61C, 0, 1000 },
    { 20, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B630, 0, 1050 },
    { 20, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B644, 0, 1230 },
    { 27, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B658, 0, 1260 },
    { 20, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B66C, 0, 1290 },
    { 20, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B680, 0, 1292 },
    { 20, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B694, 0, 1294 },
    { 55, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B6A8, 0, 1320 },
    { 20, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B6BC, 0, 1380 },
    { 55, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B6D0, 0, 1460 },
    { 20, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B6E4, 0, 1500 },
    { 20, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B6F8, 0, 1502 },
    { 55, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B70C, MSG_SCRIPT_FLAG_END, 1650 },
};
#endif

static const EvSoundCue sEvent184SoundCues[5] = {
    { SONG_BGM_EVENT_XIII, 0, 0, 0 },
    { SONG_EV_WARPOUT, 170, 0, 0 },
    { SONG_SND_368, 1530, 0, 0 },
    { SONG_SND_381, 1680, 0, 0 },
    { SONG_BGM_EVENT_XIII, 1710, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent184Camera[6] = {
    { -65196, 46592, 59136, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -65016, 83456, 69888, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, 0 },
    { -64935, 46592, 59136, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, 0 },
    { -63906, 57088, 59136, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, 0 },
    { -63536, 30976, 110848, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
};

static const EventBgEffectEntry sEvent184BgEffects[5] = {
    { 1530, 0, 0, 0, 0 },
    { 1630, 0, 0, 0, 0x14 },
    { 3310, 0, 0, 0, 0 },
    { 3380, 0, 0, 0, 0x2 },
    { 3500, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent184Track0[10] = {
    { 902, 170, { 0, 0 }, 111616, 23040, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 903, 280, { 0, 0 }, 47104, 65792, 0, 0, { 0, 0 }, 2, EventCharaFadeIn, 0 },
    { 903, 521, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 889, 595, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 896, 605, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 889, 1390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 896, 1440, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 896, 1560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 896, 1600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, EventCharaFadeOut, 0 },
    { 902, 2000, { 0, 0 }, 111616, 23040, 0, 0, { 0, 0 }, 98306, 0, 0 },
};

static const EventCharaKeyframe sEvent184Track1[10] = {
    { 486, 601, { 0, 0 }, 86528, 73216, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 502, 720, { 0, 0 }, 65536, 61440, 0, 486, { 0, 0 }, 3, 0, 0 },
    { 486, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 485, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 509, 1330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 485, 1350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 499, 1470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 485, 1560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 485, 1600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaFadeOut, 0 },
    { 486, 2000, { 0, 0 }, 111616, 23040, 0, 0, { 0, 0 }, 98306, 0, 0 },
};

static const EventCharaKeyframe sEvent184Track2[10] = {
    { 696, 601, { 0, 0 }, 82432, 83456, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 712, 700, { 0, 0 }, 65024, 73984, 0, 696, { 0, 0 }, 3, 0, 0 },
    { 696, 750, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 696, 880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 696, 1070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 696, 1200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 696, 1540, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 712, 1560, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, 0, 0 },
    { 712, 1600, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, EventCharaFadeOut, 0 },
    { 696, 2000, { 0, 0 }, 111616, 23040, 0, 0, { 0, 0 }, 98306, 0, 0 },
};

static const EventCharaKeyframe sEvent184Track3[3] = {
    { 928, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, 0, 0 },
    { 927, 330, { 0, 0 }, 44544, 55552, 0, 0, { 0, 0 }, 16658, 0, 0 },
    { 928, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, 0, 0 },
};

static const EventCharaTrack sEvent184Tracks[4] = {
    { sEvent184Track0, 83, { 0, 0, 0 } },
    { sEvent184Track1, 43, { 0, 0, 0 } },
    { sEvent184Track2, 65, { 0, 0, 0 } },
    { sEvent184Track3, 93, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent184 = {
    4,
    { 0, 0, 0 },
    sEvent184Tracks,
    sEvent184Camera,
    sEvent184Script,
    sEvent184SoundCues,
    sEvent184BgEffects,
    1710,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    185,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent184 = {
    4,
    { 0, 0, 0 },
    sEvent184Tracks,
    sEvent184Camera,
    sEvent184Script,
    sEvent184SoundCues,
    sEvent184BgEffects,
    1710,
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
#endif

#ifdef VERSION_US
#include "event_185_text.inc"

static const MessageScriptEntry sEvent185Script[25] = {
    { 56, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902701C, MSG_SCRIPT_FLAG_SILHOUETTE, 141 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09027036, 0, 170 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09027050, 0, 260 },
    { 56, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902707E, 0, 290 },
    { 56, 1, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_090270F8, 0, 390 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_090271AC, 0, 420 },
    { 56, 1, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_090271E2, 0, 450 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09027204, 0, 660 },
    { 56, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_09027224, 0, 690 },
    { 56, 2, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_090272F8, 0, 1240 },
    { 61, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_09027336, MSG_SCRIPT_FLAG_SILHOUETTE, 1290 },
    { 61, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_090273D4, 0, 1530 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902741C, 0, 1730 },
    { 61, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902744C, 0, 1760 },
    { 61, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09027464, 0, 1940 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090274B0, 0, 1970 },
    { 61, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09027536, 0, 2000 },
    { 26, 4, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09027562, 0, 2150 },
    { 26, 4, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090275D4, 0, 2152 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09027678, 0, 2220 },
    { 61, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09027712, 0, 2300 },
    { 61, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902774C, 0, 2400 },
    { 61, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090277FA, 0, 2402 },
    { 61, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090278E6, 0, 2404 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09027944, MSG_SCRIPT_FLAG_END, 2550 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent185Script[25] = {
    { 56, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFC9B0, MSG_SCRIPT_FLAG_SILHOUETTE, 141 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FA7110, 0, 170 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFC99C, 0, 260 },
    { 56, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFC970, 0, 290 },
    { 56, 1, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFC918, 0, 390 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFC904, 0, 420 },
    { 56, 1, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFC8F8, 0, 450 },
    { 26, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFC8E8, 0, 660 },
    { 56, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFC890, 0, 690 },
    { 56, 2, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFC86C, 0, 1240 },
    { 61, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFC820, MSG_SCRIPT_FLAG_SILHOUETTE, 1290 },
    { 61, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFC800, 0, 1530 },
    { 26, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFC7F0, 0, 1730 },
    { 61, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFC7E4, 0, 1760 },
    { 61, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFC7AC, 0, 1940 },
    { 26, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFC764, 0, 1970 },
    { 61, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFC730, 0, 2000 },
    { 26, 4, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFC700, 0, 2150 },
    { 26, 4, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFC6A8, 0, 2152 },
    { 26, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFC670, 0, 2220 },
    { 61, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFC650, 0, 2300 },
    { 61, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFC5FC, 0, 2400 },
    { 61, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFC5B0, 0, 2402 },
    { 61, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFC574, 0, 2404 },
    { 26, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFC560, MSG_SCRIPT_FLAG_END, 2550 },
};

#include "event_185_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent185Script[25] = {
    { 56, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B3C4, MSG_SCRIPT_FLAG_SILHOUETTE, 141 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B3D8, 0, 170 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B3EC, 0, 260 },
    { 56, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B400, 0, 290 },
    { 56, 1, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B414, 0, 390 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B428, 0, 420 },
    { 56, 1, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B43C, 0, 450 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B450, 0, 660 },
    { 56, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B464, 0, 690 },
    { 56, 2, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B478, 0, 1240 },
    { 61, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B48C, MSG_SCRIPT_FLAG_SILHOUETTE, 1290 },
    { 61, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B4A0, 0, 1530 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B4B4, 0, 1730 },
    { 61, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B4C8, 0, 1760 },
    { 61, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B4DC, 0, 1940 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B4F0, 0, 1970 },
    { 61, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B504, 0, 2000 },
    { 26, 4, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B518, 0, 2150 },
    { 26, 4, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B52C, 0, 2152 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B540, 0, 2220 },
    { 61, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B554, 0, 2300 },
    { 61, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B568, 0, 2400 },
    { 61, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B57C, 0, 2402 },
    { 61, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B590, 0, 2404 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B5A4, MSG_SCRIPT_FLAG_END, 2550 },
};
#endif

static const EvSoundCue sEvent185SoundCues[7] = {
    { 65535, 0, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 289, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT_UNREST, 810, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_SND_382, 1900, 0, 0 },
    { SONG_BGM_EVENT4, 1965, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_EV_HUKUROUJUMP, 2050, 0, 0 },
    { SONG_BGM_EVENT4, 2605, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent185Camera[9] = {
    { -64956, 175616, 68864, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -64346, 175616, 63744, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, 0 },
    { -64326, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 20, { 0, 0 }, 0 },
    { -64294, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -64284, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_MODE_KEEP, 10, { 0, 0 }, 0 },
    { -64076, 185600, 65280, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 20, { 0, 0 }, 0 },
    { -63726, 179968, 61952, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, 0 },
    { -62966, 176640, 60160, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, 0 },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent185Track0[33] = {
    { 515, 1, { 0, 0 }, 141568, 92416, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 518, 140, { 0, 0 }, 174592, 76288, 0, 515, { 0, 0 }, 67, 0, 0 },
    { 515, 190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 240, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 515, 415, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 538, 422, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 532, 530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 532, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 532, 630, { 0, 0 }, 174592, 76288, -6912, 515, { 0, 0 }, 4163, 0, 0 },
    { 556, 1250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 532, 1260, { 0, 0 }, 186112, 71168, 0, 515, { 0, 0 }, 67, 0, 0 },
    { 556, 1282, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 1300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 532, 1350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 532, 1370, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 1400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 1410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 1460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 1560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 1690, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 515, 1800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 518, 1850, { 0, 0 }, 178944, 65536, 0, 515, { 0, 0 }, 3, 0, 0 },
    { 515, 1870, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 536, 1930, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 2050, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 554, 2060, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 4, 0, 0 },
    { 554, 2430, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 556, 2445, { 0, 0 }, 180992, 66560, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 515, 2460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 536, 2490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 2535, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 558, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent185Track1[8] = {
    { 920, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, 0, 0 },
    { 920, 721, { 0, 0 }, 137728, 59136, 0, 0, { 0, 0 }, 16642, 0, 0 },
    { 920, 800, { 0, 0 }, 166912, 53760, 0, 920, { 0, 0 }, 275, 0, 0 },
    { 920, 1050, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 272, func_0806F610, 0 },
    { 920, 1130, { 0, 0 }, 174592, 52992, 0, 920, { 0, 0 }, 275, 0, 0 },
    { 920, 1160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, 0, 0 },
    { 920, 1190, { 0, 0 }, 174592, 57344, 0, 0, { 0, 0 }, 4355, EventCharaFadeOut, 0 },
    { 920, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, 0, 0 },
};

static const EventCharaKeyframe sEvent185Track2[13] = {
    { 746, 1350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8258, 0, 0 },
    { 746, 1356, { 0, 0 }, 148224, 78336, 0, 0, { 0, 0 }, 16450, 0, 0 },
    { 754, 1480, { 0, 0 }, 174080, 64000, 0, 746, { 0, 0 }, 67, 0, 0 },
    { 746, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 745, 1840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 745, 1890, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateQuestionTask },
    { 749, 1920, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, _0806E9DC, 0 },
    { 745, 2070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 745, 2120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 745, 2250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 752, 2330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 748, 2480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 745, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent185Track3[3] = {
    { 591, 2549, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, 0, 0 },
    { 603, 5000, { 0, 0 }, 180992, 66560, 0, 0, { 0, 0 }, 16658, 0, 0 },
    { 591, 9999, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32770, 0, 0 },
};

static const EventCharaTrack sEvent185Tracks[4] = {
    { sEvent185Track0, 44, { 0, 0, 0 } },
    { sEvent185Track1, 87, { 0, 0, 0 } },
    { sEvent185Track2, 69, { 0, 0, 0 } },
    { sEvent185Track3, 50, { 0, 0, 0 } },
};

const EventSequenceDef gEvent185 = {
    4,
    { 0, 0, 0 },
    sEvent185Tracks,
    sEvent185Camera,
    sEvent185Script,
    sEvent185SoundCues,
    0,
    2610,
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

#ifdef VERSION_US
#include "event_186_text.inc"

static const MessageScriptEntry sEvent186Script[21] = {
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09028570, 0, 370 },
    { 26, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090285CA, 0, 372 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902861A, 0, 450 },
    { 56, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_09028636, 0, 480 },
    { 56, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09028668, 0, 690 },
    { 56, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090286BE, 0, 980 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09028754, 0, 1010 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09028778, 0, 1120 },
    { 26, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902880E, 0, 1122 },
    { 26, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902888A, 0, 1240 },
    { 26, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_09028902, 0, 1242 },
    { 56, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902899E, 0, 1430 },
    { 52, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_090289B0, 0, 1600 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09028A46, 0, 1630 },
    { 52, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09028AA2, 0, 1660 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09028ACE, 0, 1690 },
    { 52, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09028ADE, 0, 1720 },
    { 52, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09028B7A, 0, 1950 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09028BCA, 0, 1980 },
    { 52, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_09028BF2, 0, 2010 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09028C48, MSG_SCRIPT_FLAG_END, 2085 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent186Script[21] = {
    { 26, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFD878, 0, 370 },
    { 26, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFD860, 0, 372 },
    { 26, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFD858, 0, 450 },
    { 56, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFD848, 0, 480 },
    { 56, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFD820, 0, 690 },
    { 56, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFD7D4, 0, 980 },
    { 26, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFD7B4, 0, 1010 },
    { 26, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFD768, 0, 1120 },
    { 26, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFD72C, 0, 1122 },
    { 26, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFD6E8, 0, 1240 },
    { 26, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFD690, 0, 1242 },
    { 56, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FDE8B4, 0, 1430 },
    { 52, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFD65C, 0, 1600 },
    { 26, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFD630, 0, 1630 },
    { 52, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFD61C, 0, 1660 },
    { 26, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFD614, 0, 1690 },
    { 52, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFD5CC, 0, 1720 },
    { 52, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFD598, 0, 1950 },
    { 26, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFD584, 0, 1980 },
    { 52, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFD574, 0, 2010 },
    { 26, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFD564, MSG_SCRIPT_FLAG_END, 2085 },
};

#include "event_186_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent186Script[21] = {
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AF3C, 0, 370 },
    { 26, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AF50, 0, 372 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AF64, 0, 450 },
    { 56, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AF78, 0, 480 },
    { 56, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AF8C, 0, 690 },
    { 56, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AFA0, 0, 980 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AFB4, 0, 1010 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AFC8, 0, 1120 },
    { 26, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AFDC, 0, 1122 },
    { 26, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AFF0, 0, 1240 },
    { 26, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B004, 0, 1242 },
    { 56, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B018, 0, 1430 },
    { 52, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B02C, 0, 1600 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B040, 0, 1630 },
    { 52, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B054, 0, 1660 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B068, 0, 1690 },
    { 52, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B07C, 0, 1720 },
    { 52, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B090, 0, 1950 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B0A4, 0, 1980 },
    { 52, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B0B8, 0, 2010 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B0CC, MSG_SCRIPT_FLAG_END, 2085 },
};
#endif

static const EvSoundCue sEvent186SoundCues[9] = {
    { 65535, 0, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 482, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_SND_379, 630, 0, 0 },
    { SONG_SND_359, 710, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 1012, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_EV_WHITEOUT, 1460, 0, 0 },
    { SONG_BGM_TWILIGHTTOWN, 1510, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_SND_379, 2040, 0, 0 },
    { SONG_BGM_TWILIGHTTOWN, 2135, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent186Camera[7] = {
    { -65536, 61184, 107520, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, 0 },
    { -64956, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 80, { 0, 0 }, 0 },
    { -64076, 66816, 103936, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, 0 },
    { -64036, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 40, { 0, 0 }, 0 },
    { -64006, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -63536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_MODE_KEEP, 40, { 0, 0 }, 0 },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent186Track0[25] = {
    { 515, 1, { 0, 0 }, 26624, 134144, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 518, 160, { 0, 0 }, 60160, 116736, 0, 515, { 0, 0 }, 67, 0, 0 },
    { 515, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 220, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 515, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 290, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 514, 330, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 514, 410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 514, 490, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 540, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 514, 560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 560, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 561, 930, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 561, 950, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 562, 960, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 1140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 530, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 1770, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 1900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 515, 2080, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 538, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent186Track1[10] = {
    { 688, 630, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, 0, 0 },
    { 688, 685, { 0, 0 }, 74240, 110336, 0, 0, { 0, 0 }, 16386, EventCharaFadeIn, 0 },
    { 694, 692, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 688, 1020, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 688, 1070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 688, 1270, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 688, 1400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 688, 1450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 688, 1501, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, func_0806F2EC, 0 },
    { 688, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, 0, 0 },
};

static const EventCharaKeyframe sEvent186Track2[4] = {
    { 907, 1501, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, 0, 0 },
    { 907, 2040, { 0, 0 }, 74240, 110336, 0, 0, { 0, 0 }, 16386, 0, 0 },
    { 907, 2070, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaFadeOut, 0 },
    { 907, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 73730, 0, 0 },
};

static const EventCharaTrack sEvent186Tracks[3] = {
    { sEvent186Track0, 44, { 0, 0, 0 } },
    { sEvent186Track1, 64, { 0, 0, 0 } },
    { sEvent186Track2, 84, { 0, 0, 0 } },
};

const EventSequenceDef gEvent186 = {
    3,
    { 0, 0, 0 },
    sEvent186Tracks,
    sEvent186Camera,
    sEvent186Script,
    sEvent186SoundCues,
    0,
    2140,
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
    1,
    255,
    255,
};

#ifdef VERSION_US
#include "event_187_text.inc"

static const MessageScriptEntry sEvent187Script[13] = {
    { 26, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_09029550, 0, 410 },
    { 27, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09029582, MSG_SCRIPT_FLAG_SILHOUETTE, 440 },
    { 27, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_090295AC, 0, 750 },
    { 27, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090295E4, 0, 752 },
    { 26, 0, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902966A, 0, 780 },
    { 27, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902968E, 0, 810 },
    { 26, 2, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_090296B0, 0, 860 },
    { 27, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_090296C8, 0, 1040 },
    { 27, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090296EE, 0, 1042 },
    { 27, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09029794, 0, 1070 },
    { 27, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09029822, 0, 1260 },
    { 27, 2, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_090298C6, 0, 1263 },
    { 27, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902991C, MSG_SCRIPT_FLAG_END, 1430 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent187Script[13] = {
    { 26, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFE2DC, 0, 410 },
    { 27, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFE2D0, MSG_SCRIPT_FLAG_SILHOUETTE, 440 },
    { 27, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFE2B0, 0, 750 },
    { 27, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFE280, 0, 752 },
    { 26, 0, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFE270, 0, 780 },
    { 27, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFE258, 0, 810 },
    { 26, 2, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFE24C, 0, 860 },
    { 27, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFE23C, 0, 1040 },
    { 27, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFE1F4, 0, 1042 },
    { 27, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFE19C, 0, 1070 },
    { 27, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFE14C, 0, 1260 },
    { 27, 2, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFE120, 0, 1263 },
    { 27, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFE0D8, MSG_SCRIPT_FLAG_END, 1430 },
};

#include "event_187_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent187Script[13] = {
    { 26, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B194, 0, 410 },
    { 27, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B1A8, MSG_SCRIPT_FLAG_SILHOUETTE, 440 },
    { 27, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B1BC, 0, 750 },
    { 27, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B1D0, 0, 752 },
    { 26, 0, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B1E4, 0, 780 },
    { 27, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B1F8, 0, 810 },
    { 26, 2, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B20C, 0, 860 },
    { 27, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B220, 0, 1040 },
    { 27, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B234, 0, 1042 },
    { 27, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B248, 0, 1070 },
    { 27, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B25C, 0, 1260 },
    { 27, 2, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B270, 0, 1263 },
    { 27, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B284, MSG_SCRIPT_FLAG_END, 1430 },
};
#endif

static const EvSoundCue sEvent187SoundCues[7] = {
    { 65535, 0, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 550, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT_UNREST, 1065, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_SND_377, 1130, 0, 0 },
    { SONG_BGM_EVENT2, 1140, 0, 0 },
    { SONG_SND_359, 1310, 0, 0 },
    { SONG_SND_359, 1350, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent187Camera[3] = {
    { -65416, 65024, 42496, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -64436, 65024, 88576, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 260, { 0, 0 }, 0 },
    { -63536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
};

static const EventBgEffectEntry sEvent187BgEffects[5] = {
    { 1072, 0, 0, 0, 0 },
    { 1130, 0, 50, 0, 0x4 },
    { 1226, 5, 44032, 74752, 0x1 },
    { 1230, 0, 0, 0, 0x2 },
    { 1265, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent187Track0[10] = {
    { 515, 460, { 0, 0 }, 73728, 99328, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 515, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 515, 540, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 625, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 1100, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 532, 1130, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 532, 1180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 532, 1250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 1350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 560, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent187Track1[13] = {
    { 696, 510, { 0, 0 }, 29952, 117504, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 712, 670, { 0, 0 }, 56064, 93952, 0, 696, { 0, 0 }, 67, 0, 0 },
    { 696, 680, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 695, 735, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 707, 790, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 695, 880, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 695, 1010, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 695, 1060, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 706, 1230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 695, 1261, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 706, 1265, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 695, 1310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 698, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaTrack sEvent187Tracks[2] = {
    { sEvent187Track0, 44, { 0, 0, 0 } },
    { sEvent187Track1, 65, { 0, 0, 0 } },
};

const EventSequenceDef gEvent187 = {
    2,
    { 0, 0, 0 },
    sEvent187Tracks,
    sEvent187Camera,
    sEvent187Script,
    sEvent187SoundCues,
    sEvent187BgEffects,
    1490,
    0,
    1,
    0,
    0,
    0,
    0,
    172,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_188_text.inc"

static const MessageScriptEntry sEvent188Script[9] = {
    { 27, 5, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09029F8C, 0, 260 },
    { 27, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_09029FB4, 0, 470 },
    { 27, 5, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902A03A, 0, 472 },
    { 26, 5, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902A0C6, 0, 500 },
    { 27, 5, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902A0F2, 0, 690 },
    { 27, 5, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902A182, 0, 800 },
    { 26, 5, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902A1DC, 0, 850 },
    { 27, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902A258, 0, 880 },
    { 27, 4, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902A27E, MSG_SCRIPT_FLAG_END, 1000 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent188Script[9] = {
    { 27, 5, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFE990, 0, 260 },
    { 27, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFE950, 0, 470 },
    { 27, 5, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFE900, 0, 472 },
    { 26, 5, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFE8F0, 0, 500 },
    { 27, 5, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFE8B8, 0, 690 },
    { 27, 5, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFE8A4, 0, 800 },
    { 26, 5, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFE874, 0, 850 },
    { 27, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFE848, 0, 880 },
    { 27, 4, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFE834, MSG_SCRIPT_FLAG_END, 1000 },
};

#include "event_188_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent188Script[9] = {
    { 27, 5, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B0E0, 0, 260 },
    { 27, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B0F4, 0, 470 },
    { 27, 5, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B108, 0, 472 },
    { 26, 5, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B11C, 0, 500 },
    { 27, 5, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B130, 0, 690 },
    { 27, 5, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B144, 0, 800 },
    { 26, 5, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B158, 0, 850 },
    { 27, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B16C, 0, 880 },
    { 27, 4, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B180, MSG_SCRIPT_FLAG_END, 1000 },
};
#endif

static const EvSoundCue sEvent188SoundCues[4] = {
    { 65535, 0, 0, 0 },
    { SONG_BGM_EVENT_SILENCE, 465, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_SND_379, 1080, 0, 0 },
    { SONG_BGM_EVENT_SILENCE, 1195, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent188Camera[1] = {
    { -64537, 65024, 88576, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent188Track0[5] = {
    { 561, 150, { 0, 0 }, 73728, 99328, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 562, 165, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 290, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent188Track1[5] = {
    { 705, 100, { 0, 0 }, 56064, 93952, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 705, 530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 1048901, 0, 0 },
    { 705, 1080, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 1048901, 0, 0 },
    { 705, 1200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 1048896, EventCharaFadeOut, 0 },
    { 705, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98370, 0, 0 },
};

static const EventCharaKeyframe sEvent188Track2[3] = {
    { 928, 529, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, 0, 0 },
    { 928, 660, { 0, 0 }, 54528, 86784, 0, 0, { 0, 0 }, 16642, 0, 0 },
    { 928, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, 0, 0 },
};

static const EventCharaTrack sEvent188Tracks[3] = {
    { sEvent188Track0, 44, { 0, 0, 0 } },
    { sEvent188Track1, 65, { 0, 0, 0 } },
    { sEvent188Track2, 93, { 0, 0, 0 } },
};

const EventSequenceDef gEvent188 = {
    3,
    { 0, 0, 0 },
    sEvent188Tracks,
    sEvent188Camera,
    sEvent188Script,
    sEvent188SoundCues,
    0,
    1200,
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

#ifdef VERSION_US
#include "event_189_text.inc"

static const MessageScriptEntry sEvent189Script[42] = {
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902A5C8, 0, 190 },
    { 60, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902A5E6, 0, 290 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902A5F0, 0, 390 },
    { 60, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902A612, 0, 420 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902A61C, 0, 450 },
    { 60, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902A646, 0, 530 },
    { 26, 3, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902A672, 0, 900 },
    { 26, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902A694, 0, 1010 },
    { 60, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902A6C4, 0, 1040 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902A744, 0, 1070 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902A772, 0, 1290 },
    { 26, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902A780, 0, 1292 },
    { 60, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902A80C, 0, 1320 },
    { 26, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902A850, 0, 1350 },
    { 60, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902A8AC, 0, 1380 },
    { 60, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902A91C, 0, 1560 },
    { 60, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902A9C2, 0, 1562 },
    { 60, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902AA46, 0, 1740 },
    { 60, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902AAAC, 0, 1742 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902AAF8, 0, 1770 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902AB9E, 0, 1970 },
    { 60, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902ABC0, 0, 2000 },
    { 60, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902AC90, 0, 2002 },
    { 60, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902ACE6, 0, 2100 },
    { 26, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902AD2C, 0, 2500 },
    { 60, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902ADC4, 0, 2530 },
    { 26, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902ADCE, 0, 2880 },
    { 26, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902AEBE, 0, 2882 },
    { 26, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902AF4C, 0, 3000 },
    { 26, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902AFEA, 0, 3002 },
    { 26, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902B068, 0, 3070 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902B0D2, 0, 3170 },
    { 60, 2, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902B158, 0, 3200 },
    { 26, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902B1C4, 0, 3230 },
    { 60, 1, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902B216, 0, 3260 },
    { 26, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902B230, 0, 3290 },
    { 60, 1, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902B290, 0, 3310 },
    { 60, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902B2C2, 0, 3312 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902B344, 0, 3360 },
    { 60, 2, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902B3B0, 0, 3390 },
    { 26, 4, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902B3C6, 0, 3420 },
    { 26, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902B438, MSG_SCRIPT_FLAG_END, 3560 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent189Script[42] = {
    { 26, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF710, 0, 190 },
    { 60, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF708, 0, 290 },
    { 26, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF6E8, 0, 390 },
    { 60, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08F85C04, 0, 420 },
    { 26, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF6D8, 0, 450 },
    { 60, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF6B8, 0, 530 },
    { 26, 3, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF6A4, 0, 900 },
    { 26, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF690, 0, 1010 },
    { 60, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF658, 0, 1040 },
    { 26, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF648, 0, 1070 },
    { 26, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF63C, 0, 1290 },
    { 26, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF5EC, 0, 1292 },
    { 60, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF5C0, 0, 1320 },
    { 26, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF58C, 0, 1350 },
    { 60, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF568, 0, 1380 },
    { 60, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF514, 0, 1560 },
    { 60, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF4D8, 0, 1562 },
    { 60, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF490, 0, 1740 },
    { 60, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF45C, 0, 1742 },
    { 26, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF418, 0, 1770 },
    { 26, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF408, 0, 1970 },
    { 60, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF3B4, 0, 2000 },
    { 60, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF39C, 0, 2002 },
    { 60, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF378, 0, 2100 },
    { 26, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF33C, 0, 2500 },
    { 60, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FE079C, 0, 2530 },
    { 26, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF2E8, 0, 2880 },
    { 26, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF2AC, 0, 2882 },
    { 26, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF274, 0, 3000 },
    { 26, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF224, 0, 3002 },
    { 26, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF1F0, 0, 3070 },
    { 26, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF1A8, 0, 3170 },
    { 60, 2, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF174, 0, 3200 },
    { 26, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF148, 0, 3230 },
    { 60, 1, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF13C, 0, 3260 },
    { 26, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF100, 0, 3290 },
    { 60, 1, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF0DC, 0, 3310 },
    { 60, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF09C, 0, 3312 },
    { 26, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF050, 0, 3360 },
    { 60, 2, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFF03C, 0, 3390 },
    { 26, 4, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFEFFC, 0, 3420 },
    { 26, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_08FFEFEC, MSG_SCRIPT_FLAG_END, 3560 },
};

#include "event_189_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent189Script[42] = {
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6ABF4, 0, 190 },
    { 60, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AC08, 0, 290 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AC1C, 0, 390 },
    { 60, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AC30, 0, 420 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AC44, 0, 450 },
    { 60, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AC58, 0, 530 },
    { 26, 3, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AC6C, 0, 900 },
    { 26, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AC80, 0, 1010 },
    { 60, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AC94, 0, 1040 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6ACA8, 0, 1070 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6ACBC, 0, 1290 },
    { 26, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6ACD0, 0, 1292 },
    { 60, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6ACE4, 0, 1320 },
    { 26, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6ACF8, 0, 1350 },
    { 60, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AD0C, 0, 1380 },
    { 60, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AD20, 0, 1560 },
    { 60, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AD34, 0, 1562 },
    { 60, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AD48, 0, 1740 },
    { 60, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AD5C, 0, 1742 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AD70, 0, 1770 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AD84, 0, 1970 },
    { 60, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AD98, 0, 2000 },
    { 60, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6ADAC, 0, 2002 },
    { 60, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6ADC0, 0, 2100 },
    { 26, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6ADD4, 0, 2500 },
    { 60, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6ADE8, 0, 2530 },
    { 26, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6ADFC, 0, 2880 },
    { 26, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AE10, 0, 2882 },
    { 26, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AE24, 0, 3000 },
    { 26, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AE38, 0, 3002 },
    { 26, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AE4C, 0, 3070 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AE60, 0, 3170 },
    { 60, 2, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AE74, 0, 3200 },
    { 26, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AE88, 0, 3230 },
    { 60, 1, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AE9C, 0, 3260 },
    { 26, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AEB0, 0, 3290 },
    { 60, 1, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AEC4, 0, 3310 },
    { 60, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AED8, 0, 3312 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AEEC, 0, 3360 },
    { 60, 2, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AF00, 0, 3390 },
    { 26, 4, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AF14, 0, 3420 },
    { 26, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AF28, MSG_SCRIPT_FLAG_END, 3560 },
};
#endif

static const EvSoundCue sEvent189SoundCues[5] = {
    { 65535, 0, 0, 0 },
    { SONG_BGM_EVENT1, 1390, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT1, 2878, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT_NAMINE, 2998, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT_NAMINE, 3585, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent189Camera[13] = {
    { -65456, 68864, 88576, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -64906, 75776, 91392, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 70, { 0, 0 }, 0 },
    { -64736, 65536, 74240, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 100, { 0, 0 }, 0 },
    { -64616, 65536, 67584, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, 0 },
    { -64436, 61696, 78336, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, 0 },
    { -64376, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_BLACK | CAMERA_MODE_KEEP, 60, { 0, 0 }, 0 },
    { -64356, 65536, 88576, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -64336, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -64276, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_BLACK | CAMERA_MODE_KEEP, 60, { 0, 0 }, 0 },
    { -63146, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -62066, 70144, 75008, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 100, { 0, 0 }, 0 },
    { -61536, 76800, 85760, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, 0 },
    { -59536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent189Track0[44] = {
    { 515, 80, { 0, 0 }, 103424, 110848, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 518, 170, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, 0, 0 },
    { 515, 310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 515, 630, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 518, 700, { 0, 0 }, 71680, 90880, 0, 515, { 0, 0 }, 3, 0, 0 },
    { 515, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 515, 790, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 522, 840, { 0, 0 }, 83712, 78848, 0, 515, { 0, 0 }, 67, 0, 0 },
    { 515, 860, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 910, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 920, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 520, 960, { 0, 0 }, 71680, 90880, 0, 514, { 0, 0 }, 3, 0, 0 },
    { 514, 970, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 538, 1012, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 1160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 530, 1330, { 0, 0 }, 70656, 97536, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 515, 1400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 1530, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 515, 1580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 1710, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 515, 1765, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 530, 1960, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 2120, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 2350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 515, 2370, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 2390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 518, 2440, { 0, 0 }, 75520, 87040, 0, 515, { 0, 0 }, 67, 0, 0 },
    { 515, 2460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 2560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 530, 2580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 530, 2840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 530, 2980, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 3030, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 3225, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 524, 3355, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 3450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 514, 3470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 516, 3530, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, 0, 0 },
    { 514, 3580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 516, 5000, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 32836, 0, 0 },
};

static const EventCharaKeyframe sEvent189Track1[18] = {
    { 428, 220, { 0, 0 }, 71424, 93952, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 422, 230, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 422, 550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 422, 560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 428, 590, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 450, 655, { 0, 0 }, 56064, 85248, 0, 428, { 0, 0 }, 3, 0, 0 },
    { 428, 675, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 428, 685, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 422, 1160, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 422, 1790, { 0, 0 }, 61696, 94720, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 422, 1920, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 422, 2390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 428, 2420, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 450, 2480, { 0, 0 }, 66304, 88576, 0, 428, { 0, 0 }, 67, 0, 0 },
    { 428, 3090, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 428, 3140, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 428, 3500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 422, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaTrack sEvent189Tracks[2] = {
    { sEvent189Track0, 44, { 0, 0, 0 } },
    { sEvent189Track1, 35, { 0, 0, 0 } },
};

const EventSequenceDef gEvent189 = {
    2,
    { 0, 0, 0 },
    sEvent189Tracks,
    sEvent189Camera,
    sEvent189Script,
    sEvent189SoundCues,
    0,
    3590,
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

#ifdef VERSION_US
#include "event_190_text.inc"

static const MessageScriptEntry sEvent190Script[15] = {
    { 61, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902C30C, 0, 210 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902C35E, 0, 240 },
    { 61, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902C388, 0, 270 },
    { 26, 3, 0, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902C3A2, 0, 780 },
    { 61, 4, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902C3BE, 0, 825 },
    { 26, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902C454, 0, 880 },
    { 52, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902C492, 0, 940 },
    { 26, 1, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902C534, 0, 970 },
    { 52, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902C5A4, 0, 1000 },
    { 26, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902C60E, 0, 1050 },
    { 52, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902C636, 0, 1080 },
    { 26, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902C68E, 0, 1110 },
    { 52, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902C6FA, 0, 1140 },
    { 52, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902C768, 0, 1220 },
    { 26, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902C82C, MSG_SCRIPT_FLAG_END, 1460 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent190Script[15] = {
    { 61, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_090005D8, 0, 210 },
    { 26, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_090005C0, 0, 240 },
    { 61, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_090005A4, 0, 270 },
    { 26, 3, 0, 3, { 0, 0, 0 }, (u32)gEventTextJp_0900058C, 0, 780 },
    { 61, 4, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_09000544, 0, 825 },
    { 26, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_0900052C, 0, 880 },
    { 52, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_090004E8, 0, 940 },
    { 26, 1, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_090004BC, 0, 970 },
    { 52, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_09000484, 0, 1000 },
    { 26, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_0900046C, 0, 1050 },
    { 52, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_0900043C, 0, 1080 },
    { 26, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_090003EC, 0, 1110 },
    { 52, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_090003B4, 0, 1140 },
    { 52, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_0900035C, 0, 1220 },
    { 26, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_0900034C, MSG_SCRIPT_FLAG_END, 1460 },
};

#include "event_190_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent190Script[15] = {
    { 61, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B298, 0, 210 },
    { 26, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B2AC, 0, 240 },
    { 61, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B2C0, 0, 270 },
    { 26, 3, 0, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B2D4, 0, 780 },
    { 61, 4, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B2E8, 0, 825 },
    { 26, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B2FC, 0, 880 },
    { 52, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B310, 0, 940 },
    { 26, 1, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B324, 0, 970 },
    { 52, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B338, 0, 1000 },
    { 26, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B34C, 0, 1050 },
    { 52, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B360, 0, 1080 },
    { 26, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B374, 0, 1110 },
    { 52, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B388, 0, 1140 },
    { 52, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B39C, 0, 1220 },
    { 26, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6B3B0, MSG_SCRIPT_FLAG_END, 1460 },
};
#endif

static const EvSoundCue sEvent190SoundCues[6] = {
    { SONG_BGM_T13THFLOOR, 0, 0, 0 },
    { SONG_SND_958, 640, 0, 0 },
    { SONG_EV_SR_STONEL, 645, 0, 0 },
    { SONG_SND_959, 660, 0, 0 },
    { SONG_EV_SR_STONER, 665, 0, 0 },
    { SONG_EV_CARDTHR, 1191, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent190Camera[4] = {
    { -65116, 159488, 77056, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -64916, 201728, 55296, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 80, { 0, 0 }, 0 },
    { -64537, 192000, 61952, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, 0 },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent190Track0[17] = {
    { 515, 1, { 0, 0 }, 125696, 101888, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 518, 110, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, 0, 0 },
    { 515, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 400, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateExclamationTask },
    { 515, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 620, { 0, 0 }, 167424, 84736, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 518, 690, { 0, 0 }, 185088, 75520, 0, 515, { 0, 0 }, 67, 0, 0 },
    { 515, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 850, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 1190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 559, 1250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 558, 1280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 558, 1410, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 558, 1440, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 1480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 518, 1700, { 0, 0 }, 230400, 52992, 0, 515, { 0, 0 }, 67, 0, 0 },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent190Track1[18] = {
    { 745, 50, { 0, 0 }, 198400, 64256, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 747, 180, { 0, 0 }, 0, 0, 0, 173, { 0, 0 }, 4, 0, 0 },
    { 745, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 745, 310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 746, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 746, 620, { 0, 0 }, 161792, 76544, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 754, 690, { 0, 0 }, 176384, 70400, 0, 746, { 0, 0 }, 67, 0, 0 },
    { 746, 800, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 745, 820, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 752, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 745, 920, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 746, 1470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 745, 1500, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 747, 1540, { 0, 0 }, 0, 0, 0, 83, { 0, 0 }, 68, 0, 0 },
    { 745, 1550, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 746, 1560, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 754, 2020, { 0, 0 }, 0, 0, 0, 45, { 0, 0 }, 68, 0, 0 },
    { 746, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent190Track2[4] = {
    { 907, 1160, { 0, 0 }, 201984, 61952, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 908, 1205, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 907, 1600, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 907, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent190Track3[8] = {
    { 591, 1190, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, 0, 0 },
    { 591, 1191, { 0, 0 }, 197376, 58624, 0, 0, { 0, 0 }, 16658, 0, 0 },
    { 591, 1200, { 0, 0 }, 189440, 65792, 0, 591, { 0, 0 }, 275, 0, 0 },
    { 591, 1203, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 604, 1250, { 0, 0 }, 185088, 75520, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 591, 1264, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 603, 1440, { 0, 0 }, 185088, 75520, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 591, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98309, 0, 0 },
};

static const EventCharaTrack sEvent190Tracks[4] = {
    { sEvent190Track0, 44, { 0, 0, 0 } },
    { sEvent190Track1, 69, { 0, 0, 0 } },
    { sEvent190Track2, 84, { 0, 0, 0 } },
    { sEvent190Track3, 50, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent190 = {
    4,
    { 0, 0, 0 },
    sEvent190Tracks,
    sEvent190Camera,
    sEvent190Script,
    sEvent190SoundCues,
    0,
    1640,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    191,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent190 = {
    4,
    { 0, 0, 0 },
    sEvent190Tracks,
    sEvent190Camera,
    sEvent190Script,
    sEvent190SoundCues,
    0,
    1640,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    189,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_191_text.inc"

static const MessageScriptEntry sEvent191Script[15] = {
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902D160, 0, 100 },
    { 61, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902D1A4, 0, 280 },
    { 26, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902D200, 0, 320 },
    { 26, 2, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902D230, 0, 330 },
    { 61, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902D272, 0, 410 },
    { 26, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902D28C, 0, 440 },
    { 26, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902D302, 0, 442 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902D38A, 0, 540 },
    { 61, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902D3D6, 0, 560 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902D40A, 0, 600 },
    { 61, 3, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902D494, 0, 630 },
    { 61, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902D556, 0, 632 },
    { 26, 4, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902D5EA, 0, 830 },
    { 61, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902D68C, 0, 860 },
    { 26, 4, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902D6F0, MSG_SCRIPT_FLAG_END, 920 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent191Script[15] = {
    { 26, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_0900113C, 0, 100 },
    { 61, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_09001118, 0, 280 },
    { 26, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_0900110C, 0, 320 },
    { 26, 2, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_090010F8, 0, 330 },
    { 61, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_090010E8, 0, 410 },
    { 26, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_090010B8, 0, 440 },
    { 26, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_09001068, 0, 442 },
    { 26, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_09001044, 0, 540 },
    { 61, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_09001020, 0, 560 },
    { 26, 3, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_09000FF0, 0, 600 },
    { 61, 3, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_09000FA8, 0, 630 },
    { 61, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_09000F60, 0, 632 },
    { 26, 4, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_09000F3C, 0, 830 },
    { 61, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_09000F10, 0, 860 },
    { 26, 4, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_08F9F980, MSG_SCRIPT_FLAG_END, 920 },
};

#include "event_191_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent191Script[15] = {
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AAC8, 0, 100 },
    { 61, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AADC, 0, 280 },
    { 26, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AAF0, 0, 320 },
    { 26, 2, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AB04, 0, 330 },
    { 61, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AB18, 0, 410 },
    { 26, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AB2C, 0, 440 },
    { 26, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AB40, 0, 442 },
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AB54, 0, 540 },
    { 61, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AB68, 0, 560 },
    { 26, 3, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AB7C, 0, 600 },
    { 61, 3, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AB90, 0, 630 },
    { 61, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6ABA4, 0, 632 },
    { 26, 4, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6ABB8, 0, 830 },
    { 61, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6ABCC, 0, 860 },
    { 26, 4, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6ABE0, MSG_SCRIPT_FLAG_END, 920 },
};
#endif

static const EvSoundCue sEvent191SoundCues[4] = {
    { SONG_BGM_T13THFLOOR, 0, 0, 0 },
    { SONG_SND_382, 360, 0, 0 },
    { SONG_BGM_T13THFLOOR, 441, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT4, 559, EV_SOUND_FLAG_FADE_IN | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent191Camera[1] = {
    { -64537, 196096, 58880, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent191Track0[10] = {
    { 558, 120, { 0, 0 }, 202496, 68352, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 558, 250, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 558, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 595, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 532, 602, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 780, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 515, 890, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 540, 910, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaKeyframe sEvent191Track1[3] = {
    { 745, 350, { 0, 0 }, 191232, 61952, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 749, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, _0806E9DC, 0 },
    { 745, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent191Track2[3] = {
    { 603, 300, { 0, 0 }, 202496, 68352, 0, 0, { 0, 0 }, 274, 0, 0 },
    { 591, 310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 258, 0, 0 },
    { 591, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98373, 0, 0 },
};

static const EventCharaTrack sEvent191Tracks[3] = {
    { sEvent191Track0, 44, { 0, 0, 0 } },
    { sEvent191Track1, 69, { 0, 0, 0 } },
    { sEvent191Track2, 50, { 0, 0, 0 } },
};

const EventSequenceDef gEvent191 = {
    3,
    { 0, 0, 0 },
    sEvent191Tracks,
    sEvent191Camera,
    sEvent191Script,
    sEvent191SoundCues,
    0,
    980,
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

#ifdef VERSION_US
#include "event_192_text.inc"

static const MessageScriptEntry sEvent192Script[3] = {
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902DB50, 0, 150 },
    { 56, 1, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902DB7C, 0, 250 },
    { 56, 1, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902DBB2, MSG_SCRIPT_FLAG_END, 300 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent192Script[3] = {
    { 26, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_090014EC, 0, 150 },
    { 56, 1, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_090014C8, 0, 250 },
    { 56, 1, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_09001478, MSG_SCRIPT_FLAG_END, 300 },
};

#include "event_192_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent192Script[3] = {
    { 26, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A7E4, 0, 150 },
    { 56, 1, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A7F8, 0, 250 },
    { 56, 1, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A80C, MSG_SCRIPT_FLAG_END, 300 },
};
#endif

static const EvSoundCue sEvent192SoundCues[3] = {
    { SONG_BGM_F13F_FORGET, 0, 0, 0 },
    { SONG_SND_359, 110, 0, 0 },
    { SONG_BGM_F13F_FORGET, 475, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent192Camera[2] = {
    { -65536, 35072, 32512, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, 0 },
    { -64537, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 80, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent192Track0[9] = {
    { 515, 1, { 0, 0 }, 67328, 56576, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 522, 100, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, 0, 0 },
    { 515, 103, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 4, 0, 0 },
    { 515, 110, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 560, 350, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 562, 360, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 515, 390, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 522, 1000, { 0, 0 }, 0, 0, 0, 211, { 0, 0 }, 36, 0, 0 },
    { 515, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaTrack sEvent192Tracks[1] = {
    { sEvent192Track0, 44, { 0, 0, 0 } },
};

const EventSequenceDef gEvent192 = {
    1,
    { 0, 0, 0 },
    sEvent192Tracks,
    sEvent192Camera,
    sEvent192Script,
    sEvent192SoundCues,
    0,
    480,
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

#ifdef VERSION_US
#include "event_193_text.inc"

static const MessageScriptEntry sEvent193Script[12] = {
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902DEA4, 0, 330 },
    { 56, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902DEEE, 0, 530 },
    { 56, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902DF72, 0, 650 },
    { 56, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902DFF6, 0, 652 },
    { 56, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902E076, 0, 654 },
    { 26, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902E13C, 0, 680 },
    { 26, 2, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902E168, 0, 820 },
    { 56, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902E196, 0, 1020 },
    { 26, 2, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902E298, 0, 1050 },
    { 26, 0, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902E2AC, 0, 1100 },
    { 26, 1, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902E326, 0, 1102 },
    { 56, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902E34C, MSG_SCRIPT_FLAG_END, 1150 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent193Script[12] = {
    { 26, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_09001A68, 0, 330 },
    { 56, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_09001A18, 0, 530 },
    { 56, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_090019D4, 0, 650 },
    { 56, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_0900198C, 0, 652 },
    { 56, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_09001940, 0, 654 },
    { 26, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_09001920, 0, 680 },
    { 26, 2, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_090018FC, 0, 820 },
    { 56, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_090018A4, 0, 1020 },
    { 26, 2, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_09001890, 0, 1050 },
    { 26, 0, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_09001848, 0, 1100 },
    { 26, 1, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_09001828, 0, 1102 },
    { 56, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_09001804, MSG_SCRIPT_FLAG_END, 1150 },
};

#include "event_193_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent193Script[12] = {
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A9D8, 0, 330 },
    { 56, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A9EC, 0, 530 },
    { 56, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AA00, 0, 650 },
    { 56, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AA14, 0, 652 },
    { 56, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AA28, 0, 654 },
    { 26, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AA3C, 0, 680 },
    { 26, 2, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AA50, 0, 820 },
    { 56, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AA64, 0, 1020 },
    { 26, 2, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AA78, 0, 1050 },
    { 26, 0, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AA8C, 0, 1100 },
    { 26, 1, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AAA0, 0, 1102 },
    { 56, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6AAB4, MSG_SCRIPT_FLAG_END, 1150 },
};
#endif

static const EvSoundCue sEvent193SoundCues[9] = {
    { 65535, 0, 0, 0 },
    { SONG_SND_379, 450, 0, 0 },
    { SONG_BGM_EVENT_UNREST, 550, EV_SOUND_FLAG_FADE_IN, 0 },
    { SONG_BGM_EVENT_UNREST, 700, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_SND_359, 720, 0, 0 },
    { SONG_BGM_EVENT2, 730, 0, 0 },
    { SONG_SND_378, 1200, 0, 0 },
    { SONG_EV_RUMBLE, 1210, 0, 0 },
    { SONG_EV_RUMBLE, 1405, EV_SOUND_FLAG_FADE_OUT | EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent193Camera[6] = {
    { -65186, 165376, 73984, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -64986, 181504, 65792, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 70, { 0, 0 }, 0 },
    { -64537, 173824, 72704, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 60, { 0, 0 }, 0 },
    { -64326, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -64181, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_SMALL | CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -63536, 66304, 33792, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_SMALL | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_APPROACH, 1, { 0, 0 }, 0 },
};

static const EventBgEffectEntry sEvent193BgEffects[4] = {
    { 1250, 0, 0, 0, 0 },
    { 1350, 0, 0, 0, 0x14 },
    { 3000, 0, 0, 0, 0x2 },
    { 5000, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent193Track0[7] = {
    { 515, 1, { 0, 0 }, 131072, 100352, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 518, 140, { 0, 0 }, 164608, 82432, 0, 515, { 0, 0 }, 67, 0, 0 },
    { 515, 170, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 300, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 515, 720, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 560, 1355, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 561, 5000, { 0, 0 }, 57088, 43520, 0, 0, { 0, 0 }, 32834, 0, 0 },
};

static const EventCharaKeyframe sEvent193Track1[8] = {
    { 688, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 688, 550, { 0, 0 }, 198144, 66816, 0, 0, { 0, 0 }, 2, EventCharaFadeIn, 0 },
    { 690, 620, { 0, 0 }, 182784, 74752, 0, 688, { 0, 0 }, 3, 0, 0 },
    { 688, 840, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 688, 970, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 688, 1180, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 694, 1355, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 694, 5000, { 0, 0 }, 75264, 35840, 0, 0, { 0, 0 }, 32770, 0, 0 },
};

static const EventCharaKeyframe sEvent193Track2[3] = {
    { 926, 1200, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, 0, 0 },
    { 926, 1215, { 0, 0 }, 184064, 72704, 0, 0, { 0, 0 }, 16658, 0, 0 },
    { 926, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, 0, 0 },
};

static const EventCharaTrack sEvent193Tracks[3] = {
    { sEvent193Track0, 44, { 0, 0, 0 } },
    { sEvent193Track1, 64, { 0, 0, 0 } },
    { sEvent193Track2, 92, { 0, 0, 0 } },
};

const EventSequenceDef gEvent193 = {
    3,
    { 0, 0, 0 },
    sEvent193Tracks,
    sEvent193Camera,
    sEvent193Script,
    sEvent193SoundCues,
    sEvent193BgEffects,
    1410,
    0,
    1,
    0,
    0,
    0,
    0,
    177,
    65535,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};

#ifdef VERSION_US
#include "event_194_text.inc"

static const MessageScriptEntry sEvent194Script[7] = {
    { 56, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902E8D8, 0, 100 },
    { 26, 2, 2, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902E8F6, 0, 250 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902E904, 0, 350 },
    { 56, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902E926, 0, 380 },
    { 56, 2, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902E998, 0, 445 },
    { 61, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902E9B6, 0, 1180 },
    { 61, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902EA50, MSG_SCRIPT_FLAG_END, 1400 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent194Script[7] = {
    { 56, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_09002038, 0, 100 },
    { 26, 2, 2, 3, { 0, 0, 0 }, (u32)gEventTextJp_09002028, 0, 250 },
    { 26, 2, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_09002014, 0, 350 },
    { 56, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_09001FC4, 0, 380 },
    { 56, 2, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_09001FB4, 0, 445 },
    { 61, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_09001F64, 0, 1180 },
    { 61, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_09001F54, MSG_SCRIPT_FLAG_END, 1400 },
};

#include "event_194_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent194Script[7] = {
    { 56, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A94C, 0, 100 },
    { 26, 2, 2, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A960, 0, 250 },
    { 26, 2, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A974, 0, 350 },
    { 56, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A988, 0, 380 },
    { 56, 2, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A99C, 0, 445 },
    { 61, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A9B0, 0, 1180 },
    { 61, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A9C4, MSG_SCRIPT_FLAG_END, 1400 },
};
#endif

static const EvSoundCue sEvent194SoundCues[12] = {
    { SONG_BGM_EVENT2, 0, 0, 0 },
    { SONG_SND_380, 105, 0, 0 },
    { SONG_EV_RUMBLE, 120, 0, 0 },
    { SONG_EV_RUMBLE, 190, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_SND_376, 260, 0, 0 },
    { SONG_EV_FLASH00, 270, 0, 0 },
    { SONG_SND_380, 440, 0, 0 },
    { SONG_EV_RUMBLE, 441, 0, 0 },
    { SONG_SND_379, 450, 0, 0 },
    { SONG_EV_RUMBLE, 620, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_BGM_EVENT2, 660, EV_SOUND_FLAG_FADE_OUT, 0 },
    { SONG_EV_WHITEOUT, 1530, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent194Camera[12] = {
    { -65416, 175616, 66560, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -65336, 170752, 71168, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_SMALL | CAMERA_MODE_APPROACH, 80, { 0, 0 }, 0 },
    { -65266, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -65246, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FLASH | CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND | CAMERA_MODE_KEEP, 20, { 0, 0 }, 0 },
    { -65136, 188928, 62208, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 50, { 0, 0 }, 0 },
    { -65106, 183552, 65536, 0, 255, { 0, 0, 0 }, CAMERA_MODE_APPROACH, 30, { 0, 0 }, 0 },
    { -64676, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_SHAKE_SMALL | CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -64131, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -64088, 69376, 29440, 0, 255, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0 },
    { -64006, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
    { -63536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE | CAMERA_MODE_KEEP, 100, { 0, 0 }, 0 },
    { -60536, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 0, { 0, 0 }, 0 },
};

static const EventBgEffectEntry sEvent194BgEffects[5] = {
    { 450, 0, 0, 0, 0 },
    { 530, 0, 80, 0, 0x14 },
    { 3310, 0, 0, 0, 0 },
    { 4000, 0, 0, 0, 0x2 },
    { 5000, 0, 0, 0, 0x8008 },
};

static const EventCharaKeyframe sEvent194Track0[15] = {
    { 561, 120, { 0, 0 }, 158208, 83712, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 542, 170, { 0, 0 }, 149504, 88064, 0, 515, { 0, 0 }, 67, 0, 0 },
    { 560, 260, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 548, 290, { 0, 0 }, 194816, 65792, 0, 515, { 0, 0 }, 67, 0, 0 },
    { 553, 345, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 563, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 514, 460, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 514, 470, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 526, 620, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 526, 650, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaFadeOut, 0 },
    { 515, 1450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 514, 1520, { 0, 0 }, 53248, 34816, 0, 0, { 0, 0 }, 322, EventCharaFadeIn, 0 },
    { 515, 1580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 325, 0, 0 },
    { 518, 1690, { 0, 0 }, 68096, 31232, 0, 515, { 0, 0 }, 67, 0, 0 },
    { 514, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33093, 0, 0 },
};

static const EventCharaKeyframe sEvent194Track1[7] = {
    { 688, 10, { 0, 0 }, 182528, 73216, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 693, 272, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 688, 278, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 693, 425, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 694, 450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 694, 480, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 0, EventCharaFadeOut, 0 },
    { 693, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, 0, 0 },
};

static const EventCharaKeyframe sEvent194Track2[6] = {
    { 920, 950, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8450, 0, 0 },
    { 920, 951, { 0, 0 }, 225792, 47104, 0, 0, { 0, 0 }, 16770, 0, 0 },
    { 920, 1150, { 0, 0 }, 183040, 63744, 0, 920, { 0, 0 }, 259, 0, 0 },
    { 920, 1280, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 389, 0, 0 },
    { 920, 1310, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 256, EventCharaFadeOut, 0 },
    { 920, 2000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, 0, 0 },
};

static const EventCharaKeyframe sEvent194Track3[5] = {
    { 746, 1450, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 745, 1520, { 0, 0 }, 85248, 35584, 0, 0, { 0, 0 }, 258, EventCharaFadeIn, 0 },
    { 746, 1580, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 261, 0, 0 },
    { 754, 1690, { 0, 0 }, 72704, 30208, 0, 746, { 0, 0 }, 3, 0, 0 },
    { 746, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 33029, 0, 0 },
};

static const EventCharaKeyframe sEvent194Track4[5] = {
    { 926, 105, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 8194, 0, 0 },
    { 926, 300, { 0, 0 }, 182016, 66560, 0, 0, { 0, 0 }, 16658, 0, 0 },
    { 103, 440, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 926, 480, { 0, 0 }, 183552, 65536, 0, 0, { 0, 0 }, 274, 0, 0 },
    { 926, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 98306, 0, 0 },
};

static const EventCharaTrack sEvent194Tracks[5] = {
    { sEvent194Track0, 44, { 0, 0, 0 } },
    { sEvent194Track1, 64, { 0, 0, 0 } },
    { sEvent194Track2, 87, { 0, 0, 0 } },
    { sEvent194Track3, 69, { 0, 0, 0 } },
    { sEvent194Track4, 92, { 0, 0, 0 } },
};

#if defined(VERSION_US) || defined(VERSION_JP)
const EventSequenceDef gEvent194 = {
    5,
    { 0, 0, 0 },
    sEvent194Tracks,
    sEvent194Camera,
    sEvent194Script,
    sEvent194SoundCues,
    sEvent194BgEffects,
    1680,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    195,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#elif defined(VERSION_EU)
const EventSequenceDef gEvent194 = {
    5,
    { 0, 0, 0 },
    sEvent194Tracks,
    sEvent194Camera,
    sEvent194Script,
    sEvent194SoundCues,
    sEvent194BgEffects,
    1680,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    193,
    0,
    { 0, 0 },
    65535,
    0,
    255,
    255,
};
#endif

#ifdef VERSION_US
#include "event_195_text.inc"

static const MessageScriptEntry sEvent195Script[15] = {
    { 61, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902F2F8, 0, 100 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902F34C, 0, 130 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902F37A, 0, 200 },
    { 26, 5, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902F3E6, 0, 202 },
    { 26, 5, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902F420, 0, 330 },
    { 61, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902F474, 0, 360 },
    { 61, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902F4DC, 0, 550 },
    { 61, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902F542, 0, 552 },
    { 61, 0, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902F59C, 0, 650 },
    { 61, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902F5EE, 0, 652 },
    { 61, 0, 4, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902F69E, 0, 654 },
    { 61, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902F6E8, 0, 780 },
    { 26, 1, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902F750, 0, 850 },
    { 61, 1, 1, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902F7BC, 0, 880 },
    { 26, 4, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902F816, MSG_SCRIPT_FLAG_END, 1060 },
};
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent195Script[15] = {
    { 61, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_09002C34, 0, 100 },
    { 26, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_09002C20, 0, 130 },
    { 26, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_09002BE8, 0, 200 },
    { 26, 5, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_09002BCC, 0, 202 },
    { 26, 5, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_09002B94, 0, 330 },
    { 61, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_09002B60, 0, 360 },
    { 61, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_09002B18, 0, 550 },
    { 61, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_09002AE4, 0, 552 },
    { 61, 0, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_09002ABC, 0, 650 },
    { 61, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_09002A60, 0, 652 },
    { 61, 0, 4, 3, { 0, 0, 0 }, (u32)gEventTextJp_09002A34, 0, 654 },
    { 61, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_09002A18, 0, 780 },
    { 26, 1, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_090029E0, 0, 850 },
    { 61, 1, 1, 3, { 0, 0, 0 }, (u32)gEventTextJp_090029A4, 0, 880 },
    { 26, 4, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_0900298C, MSG_SCRIPT_FLAG_END, 1060 },
};

#include "event_195_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent195Script[15] = {
    { 61, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A820, 0, 100 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A834, 0, 130 },
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A848, 0, 200 },
    { 26, 5, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A85C, 0, 202 },
    { 26, 5, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A870, 0, 330 },
    { 61, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A884, 0, 360 },
    { 61, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A898, 0, 550 },
    { 61, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A8AC, 0, 552 },
    { 61, 0, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A8C0, 0, 650 },
    { 61, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A8D4, 0, 652 },
    { 61, 0, 4, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A8E8, 0, 654 },
    { 61, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A8FC, 0, 780 },
    { 26, 1, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A910, 0, 850 },
    { 61, 1, 1, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A924, 0, 880 },
    { 26, 4, 3, 1, { 0, 0, 0 }, (u32)&gUnkEu_09F6A938, MSG_SCRIPT_FLAG_END, 1060 },
};
#endif

static const EvSoundCue sEvent195SoundCues[2] = {
    { 65535, 0, 0, 0 },
    { SONG_SND_358, 836, EV_SOUND_FLAG_END, 0 },
};

static const EventCameraKeyframe sEvent195Camera[2] = {
    { -65536, 106752, 103168, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE, 0, { 0, 0 }, 0 },
    { -64537, 0, 0, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE | CAMERA_KEYFRAME_FLAG_END | CAMERA_MODE_KEEP, 80, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent195Track0[10] = {
    { 515, 150, { 0, 0 }, 102400, 111360, 0, 0, { 0, 0 }, 66, 0, 0 },
    { 558, 270, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 295, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 540, 380, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 540, 510, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 540, 570, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 515, 820, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 536, 900, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 69, 0, 0 },
    { 536, 1030, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 64, 0, (EventCharaKeyframeFunc)CreateBalloonTask },
    { 536, 5000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32837, 0, 0 },
};

static const EventCharaKeyframe sEvent195Track1[4] = {
    { 745, 670, { 0, 0 }, 114944, 104704, 0, 0, { 0, 0 }, 2, 0, 0 },
    { 747, 700, { 0, 0 }, 109568, 108800, 0, 745, { 0, 0 }, 3, 0, 0 },
    { 745, 730, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 5, 0, 0 },
    { 750, 1000, { 0, 0 }, 0, 0, 0, 0, { 0, 0 }, 32773, 0, 0 },
};

static const EventCharaTrack sEvent195Tracks[2] = {
    { sEvent195Track0, 44, { 0, 0, 0 } },
    { sEvent195Track1, 69, { 0, 0, 0 } },
};

const EventSequenceDef gEvent195 = {
    2,
    { 0, 0, 0 },
    sEvent195Tracks,
    sEvent195Camera,
    sEvent195Script,
    sEvent195SoundCues,
    0,
    1120,
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
    13,
    0,
    255,
    255,
};

#ifdef VERSION_US
static const MessageScriptEntry sEvent196Script[1] = {
    { 26, 0, 3, 1, { 0, 0, 0 }, (u32)gEventTextUs_0902FC48, MSG_SCRIPT_FLAG_END, 100 },
};

#include "event_196_text.inc"
#endif
#ifdef VERSION_JP
static const MessageScriptEntry sEvent196Script[1] = {
    { 26, 0, 3, 3, { 0, 0, 0 }, (u32)gEventTextJp_09002F0C, MSG_SCRIPT_FLAG_END, 100 },
};

#include "event_196_text.inc"
#endif
#ifdef VERSION_EU
static const MessageScriptEntry sEvent196Script[1] = {
    { 26, 0, 3, 1, { 0, 0, 0 }, 0, MSG_SCRIPT_FLAG_END, 100 },
};
#endif

const u8 gUnk_0902FC64[8] = {
    13, 0, 0, 0, 0, 128, 0, 0,
};

static const EventCameraKeyframe sEvent196Camera[1] = {
    { -64537, 65280, 71680, 0, 255, { 0, 0, 0 }, CAMERA_KEYFRAME_FLAG_END, 0, { 0, 0 }, 0 },
};

static const EventCharaKeyframe sEvent196Track0[1] = {
    { 515, 999, { 0, 0 }, 89088, 89088, 0, 0, { 0, 0 }, 32770, 0, 0 },
};

static const EventCharaTrack sEvent196Tracks[1] = {
    { sEvent196Track0, 44, { 0, 0, 0 } },
};

const EventSequenceDef gEvent196 = {
    1,
    { 0, 0, 0 },
    sEvent196Tracks,
    sEvent196Camera,
    sEvent196Script,
    0,
    0,
    1000,
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
    255,
};
