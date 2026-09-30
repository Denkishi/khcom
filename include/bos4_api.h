#ifndef GUARD_BOS4_API_H
#define GUARD_BOS4_API_H

#include "types.h"
#include "map_runtime.h"

typedef struct BosMapanimeFrame {
    u16 duration;
    u16 frame;
} BosMapanimeFrame;

typedef struct BosMapanimeDef {
    const BosMapanimeFrame* frames;
    u16 frameCount;
    u16 unk_06;
    void* tiles;
    u16 destOffset;
    u16 copySize;
    u16 frameSize;
    u16 unk_12;
    s32 bg;
} BosMapanimeDef;

typedef struct BosMapanimeState {
    u16 timer;
    u16 frameIndex;
    u8 uploadPending;
    u8 unk_05[0x03];
    const BosMapanimeDef* def;
} BosMapanimeState;

void BosMapanimeInit(struct BosMapanimeState* p, const struct BosMapanimeDef* q);
u8 BosMapanimeUpdate(struct BosMapanimeState* p, const struct BosMapanimeDef* q, u8 a);
void ResetPooState(void);
void SavePooState(void* state);
void LoadPooState(const void* state);

struct BtlObj;

extern u16 gBosBoogieSakuOpenTime;
extern u8 gBosBoogieDiceFace;
extern struct BtlObj* gBosBoogieActor;
extern u16 gBosBoogieDiceBreakCount;
extern u8 gBosBoogieDiceFaceReady;
extern u8 gBosBoogieGimmickCardDropped;
extern u8 gBosBoogieAttackHit;
extern u8 gBosBoogieTaskKnockedDown;
extern u8 gBosBoogieKnivesRetract;
extern u8 gBosBoogieKnivesMoveRight;
extern u8 gBosUrsulaActive;
extern s32 gBosUrsulaBaseZ;
extern u8 gMapChkUseParams;

#endif
