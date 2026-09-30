#ifndef GUARD_BTL3_H
#define GUARD_BTL3_H


#include "display.h"
#include "util.h"
#include "m4a_song.h"
#include "obj_api.h"
#include "btl_effect.h"
#include "btl_collision.h"
#include "battle_actor.h"
#include "types.h"
#include "engine_math.h"
#include "listpool.h"
#include "battle_work.h"
#include "game_state.h"
#include "taskpool.h"
#include "anim.h"
#include "romcri.h"
#include "formation_types.h"

enum BtlFormFlag {
    BTL_FORM_FLAG_MIRROR_X = 0x1,
    BTL_FORM_FLAG_WAIT_NEXT_ENTRY = 0x2
};

enum BtlRaidFlag {
    BTL_RAID_FLAG_STRIKE_ON_CONTACT = 0x1,
    BTL_RAID_FLAG_BLADE_VISIBLE = 0x2
};

typedef struct BtlFormWork {
    s16 timer;
    s16 stepTimer;
    s16 stepIndex;
    u8 unk_06[0x02];
    const BtlFormList* list;
    const BtlFormEntry* entry;
    s16 entryIndex;
    u8 unk_12[0x02];
    s32 x;
    s32 y;
    s32 z;
    u16 flags;
    u16 nextTileCount;
    s16 waitTimer;
    u8 unk_26[0x02];
} BtlFormWork;

typedef struct BtlVec {
    s32 x;
    s32 y;
    s32 z;
} BtlVec;

typedef struct BtlBornWork {
    BtlVec pos;
    void* desc;
    u16 flags;
    u16 tileCount;
} BtlBornWork;

typedef struct BtlBornArgs {
    void* desc;
    BtlVec pos;
    u16 flags;
    u16 tileCount;
} BtlBornArgs;

typedef struct BtlRaidWork {
    void* tiles2;
    void* palette;
    void* gfx;
    AnimState anim;
    s32 x;
    s32 y;
    s32 z;
    s32 vx;
    s32 bounceVx;
    s16 timer;
    s16 steps;
    u8 facingLeft;
    u8 mainSide;
    u8 unk_3E[0x02];
    u32 state;
    s32 scale;
    u16 variant;
    u8 unk_4A[0x02];
    s32 attack;
    s32 unk_50;
    s16 hitHalfSize;
    u16 flags;
    u16 angle;
    u16 unk_5A;
    BtlObj* actor;
    void* tiles;
    void* palette2;
    u16 song;
    u8 unk_6A[0x02];
} BtlRaidWork;

typedef struct BtlRaidArgs {
    s32 x;
    s32 y;
    s32 z;
    u8 unk_0C[0x06];
    s16 facingLeft;
    s16 mainSide;
    u8 unk_16[0x06];
    u16 variant;
    u8 unk_1E[0x02];
} BtlRaidArgs;

typedef struct BtlBadStatusWork {
    void* tiles;
    void* palette;
    void* palette2;
    AnimState anim;
    BtlObj* actor;
    u32 status;
    void* palette3;
} BtlBadStatusWork;

extern u8 gSor1ll68wTiles[];
extern u8 gSoraPalette[];
extern u8 gBStatesPalette[];
extern u8 gCard00Palette[];
extern u8 gUnk_096FAC64[];

void BtlRaidGetEffectPosition(BtlRaidWork* work, s32* outX, s32* outY, s32* outZ);
BtlObj* BtlRaidGetTarget(BtlRaidWork* work);

#endif /* GUARD_BTL3_H */
