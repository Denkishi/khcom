#ifndef GUARD_MSG_TYPES_H
#define GUARD_MSG_TYPES_H

#include "types.h"

#ifdef VERSION_EU
typedef u8 MsgLatinChar;
#else
typedef u16 MsgLatinChar;
#endif

enum EventCameraMode {
    CAMERA_MODE_FOLLOW,
    CAMERA_MODE_APPROACH,
    CAMERA_MODE_KEEP
};

enum EventCameraKeyframeFlag {
    CAMERA_KEYFRAME_FLAG_FLASH = 0x10,
    CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE = 0x20,
    CAMERA_KEYFRAME_FLAG_FADE_OUT_BLACK = 0x40,
    CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE = 0x80,
    CAMERA_KEYFRAME_FLAG_FADE_IN_BLACK = 0x100,
    CAMERA_KEYFRAME_FLAG_HALF_FLASH = 0x200,
    CAMERA_KEYFRAME_FLAG_SHAKE_MEDIUM = 0x400,
    CAMERA_KEYFRAME_FLAG_SHAKE_LARGE = 0x800,
    CAMERA_KEYFRAME_FLAG_SWAY = 0x1000,
    CAMERA_KEYFRAME_FLAG_SHAKE_SMALL = 0x2000,
    CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE_LINEAR = 0x4000,
    CAMERA_KEYFRAME_FLAG_END = 0x8000,
    CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND = 0x10000,
    CAMERA_KEYFRAME_FLAG_WAVE_START = 0x20000,
    CAMERA_KEYFRAME_FLAG_WAVE_STOP = 0x40000
};

#define CAMERA_KEYFRAME_MODE_MASK 0xF
typedef struct EventCameraKeyframe {
    s32 frame;
    s32 x;
    s32 y;
    s32 yOffset;
    u8 target;
    u8 unk_11[3];
    u32 flags;
    u16 duration;
    u8 unk_1A[2];
    void* callback;
} EventCameraKeyframe;

enum MessageScriptFlag {
    MSG_SCRIPT_FLAG_FOCUS_SPEAKER = 0x10,
    MSG_SCRIPT_FLAG_SILHOUETTE = 0x20,
    MSG_SCRIPT_FLAG_YES_NO = 0x40,
    MSG_SCRIPT_FLAG_NO_FADE = 0x80,
    MSG_SCRIPT_FLAG_END = 0x8000
};

typedef struct MessageScriptEntry {
    u32 portraitId;
    u32 expressionId;
    u32 positionIndex;
    u8 charDelay;
    u8 unk_0D[3];
    const void* text;
    u16 flags;
    u16 frame;
} MessageScriptEntry;

#ifdef VERSION_JP
#define EVENT_TEXT_DELAY 3
#else
#define EVENT_TEXT_DELAY 1
#endif

#ifdef VERSION_EU
#define EVENT_TEXT(name) (&name)
#else
#define EVENT_TEXT(name) (name)
#endif

struct EventCharaWork;

typedef void (*EventCharaKeyframeFunc)(struct EventCharaWork*);

enum EventCharaMotion {
    CHARA_MOTION_SET_POSITION = 2,
    CHARA_MOTION_MOVE_TO = 3,
    CHARA_MOTION_WALK = 4
};

enum EventCharaKeyframeFlag {
    CHARA_KEYFRAME_FLAG_PRIORITY_1 = 0x10,
    CHARA_KEYFRAME_FLAG_FAST = 0x20,
    CHARA_KEYFRAME_FLAG_HFLIP = 0x40,
    CHARA_KEYFRAME_FLAG_BOB = 0x80,
    CHARA_KEYFRAME_FLAG_NO_SHADOW = 0x100,
    CHARA_KEYFRAME_FLAG_PLAYER_CONTROL = 0x200,
    CHARA_KEYFRAME_FLAG_PRIORITY_0 = 0x400,
    CHARA_KEYFRAME_FLAG_SILHOUETTE = 0x800,
    CHARA_KEYFRAME_FLAG_KEEP_ANIM = 0x1000,
    CHARA_KEYFRAME_FLAG_DEFER_SPAWN = 0x2000,
    CHARA_KEYFRAME_FLAG_SPAWN = 0x4000,
    CHARA_KEYFRAME_FLAG_END = 0x8000,
    CHARA_KEYFRAME_FLAG_DESPAWN = 0x10000,
    CHARA_KEYFRAME_FLAG_BOB_LARGE = 0x40000,
    CHARA_KEYFRAME_FLAG_BLINK = 0x80000,
    CHARA_KEYFRAME_FLAG_TRANSLUCENT = 0x100000
};

#define CHARA_KEYFRAME_MOTION_MASK 0xF
typedef struct EventCharaKeyframe {
    u32 anim;
    u16 frame;
    u8 unk_06[2];
    s32 x;
    s32 y;
    s32 z;
    u16 motionArg;
    u8 unk_16[2];
    u32 flags;
    void* update;
    EventCharaKeyframeFunc callback;
} EventCharaKeyframe;

typedef struct EventCharaTrack {
    const EventCharaKeyframe* keyframes;
    u8 chara;
    u8 unk_05[3];
} EventCharaTrack;

enum EvSoundFlag {
    EV_SOUND_FLAG_FADE_OUT = 0x1,
    EV_SOUND_FLAG_FADE_IN = 0x2,
    EV_SOUND_FLAG_STOP = 0x4,
    EV_SOUND_FLAG_END = 0x8000
};

typedef struct EvSoundCue {
    u16 song;
    u16 frame;
    u16 flags;
    u16 unk_06;
} EvSoundCue;

typedef struct EventBgEffectEntry {
    u16 frame;
    u16 effect;
    s32 x;
    s32 y;
    u16 flags;
    u8 unk_0E[0x02];
} EventBgEffectEntry;

typedef struct EventSequenceDef {
    u8 charaCount;
    u8 unk_01[3];
    const EventCharaTrack* charaTracks;
    const EventCameraKeyframe* keyframes;
    const MessageScriptEntry* script;
    const EvSoundCue* soundCues;
    const EventBgEffectEntry* bgEffects;
    u16 endFrame;
    u8 toMap;
    u8 startsBattle;
    u8 toTitle;
    u8 toCopyright;
    u8 toMapFld;
    u8 unk_1F;
    u16 battleId;
    u16 nextEvent;
    u16 startDelay;
    u8 unk_26[2];
    u16 exitCode;
    u8 unk_2A;
    u8 unk_2B;
    u8 unk_2C;
} EventSequenceDef;

extern const EventSequenceDef* gEventSequenceDefs[];

typedef struct MsgFaceControl {
    u8 portraitId;
    u8 expressionId;
    u8 command;
    u8 silhouette;
    u32 positionIndex;
    u8 shown;
} MsgFaceControl;

typedef struct GlyphWidthTable {
    u16 widths[256];
} GlyphWidthTable;

#endif
