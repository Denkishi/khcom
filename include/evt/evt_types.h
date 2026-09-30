#ifndef GUARD_EVT_TYPES_H
#define GUARD_EVT_TYPES_H

#include "types.h"

typedef struct EvtObjRes {
    u16 tileCount;
    u8 unk_02[0x06];
    void* palette;
} EvtObjRes;

typedef struct EvtAnimDef {
    void* gfxTable;
    void* anims;
    void* tiles;
} EvtAnimDef;

typedef struct EvtObjAnim {
    EvtAnimDef* animDef;
    u8 unk_04[0x08];
    u16 animId;
    u16 flags;
} EvtObjAnim;

typedef struct EvtObjResTable {
    EvtObjRes res;
    u8 unk_0C[0x04];
} EvtObjResTable;

typedef char EvtAnimDef_size[(sizeof(EvtAnimDef) == 12) ? 1 : -1];
typedef char EvtObjAnim_size[(sizeof(EvtObjAnim) == 16) ? 1 : -1];
typedef char EvtObjResTable_size[(sizeof(EvtObjResTable) == 16) ? 1 : -1];

struct EvtObj;
struct Task;

enum EventFlag {
    EVENT_FLAG_PAUSED = 0x1,
    EVENT_FLAG_STARTED = 0x2,
    EVENT_FLAG_PLAYER_CONTROL = 0x4
};

typedef struct EventState {
    struct EvtObj* charaObjs[16];
    struct Task* bossTask;
    s32 mapAnim;
    s32 cameraX;
    s32 cameraY;
    s32 centerX;
    s32 centerY;
    s32 x;
    s32 y;
    s32 bossChara;
    u32 flags;
    s16 shakeX;
    s16 shakeY;
    u16 frame;
    u16 bldCnt;
    u16 bldAlpha;
    u8 unk_72[2];
    s32 eventId;
    u8 hasBg2Map;
    u8 hasBg1Map;
    u8 running;
    u8 talking;
    u8 unk_7C;
    u8 msgWaitActive;
    u8 unk_7E;
    u8 unk_7F;
    u8 unk_80;
    u8 unk_81;
    u8 ending;
    u8 endRequest;
    u8 answerYes;
    u8 askedYesNo;
    u8 particleCount;
    u8 msgWinPosition;
    u8 speaker;
    u8 unk_89;
    u8 skipHoldTime;
    u8 unk_8B;
} EventState;

#endif
