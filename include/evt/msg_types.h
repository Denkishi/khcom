#ifndef GUARD_MSG_TYPES_H
#define GUARD_MSG_TYPES_H

#include "types.h"

#ifdef VERSION_EU
typedef u8 MsgLatinChar;
#else
typedef u16 MsgLatinChar;
#endif

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

typedef struct MessageScriptEntry {
    u32 portraitId;
    u32 expressionId;
    u32 positionIndex;
    u8 charDelay;
    u8 unk_0D[3];
    u32 text;
    u16 flags;
    u16 frame;
} MessageScriptEntry;

typedef void (*EventCharaKeyframeFunc)(void*);

typedef struct EventCharaKeyframe {
    u32 anim;
    u16 frame;
    u8 unk_06[2];
    s32 x;
    s32 y;
    s32 z;
    u16 unk_14;
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

typedef struct EvSoundCue {
    u16 song;
    u16 frame;
    u16 flags;
    u16 unk_06;
} EvSoundCue;

typedef struct EventBgEffectEntry {
    u8 frame[0x02];
    u16 effect;
    s32 x;
    s32 y;
    u8 flags[0x04];
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
    u8 unk_1A;
    u8 startsBattle;
    u8 toTitle;
    u8 toCopyright;
    u8 unk_1E;
    u8 unk_1F;
    u16 battleId;
    u16 nextEvent;
    u16 unk_24;
    u8 unk_26[2];
    u16 unk_28;
    u8 unk_2A;
    u8 unk_2B;
    u8 unk_2C;
} EventSequenceDef;

extern EventSequenceDef* gEventSequenceDefs[];

typedef struct MsgFaceControl {
    u8 portraitId;
    u8 expressionId;
    u8 command;
    u8 unk_03;
    u32 positionIndex;
    u8 unk_08;
} MsgFaceControl;

typedef struct GlyphWidthTable {
    u16 widths[256];
} GlyphWidthTable;

#endif
