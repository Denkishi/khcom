#ifndef GUARD_SMN_H
#define GUARD_SMN_H

#include "task_descriptors.h"

#include "registration_data.h"

#include "card_battle.h"

#include "display.h"
#include "m4a_song.h"
#include "btl_effect.h"
#include "btl_collision.h"
#include "obj_api.h"
#include "battle_actor.h"
#include "types.h"
#include "engine_math.h"
#include "listpool.h"
#include "battle_work.h"
#include "anim.h"
#include "taskpool.h"
typedef struct SmnArgs {
    u16 variant;
    u8 mainSide;
    u8 unk_03;
} SmnArgs;

typedef struct SmnCloudWork {
    void* tiles;
    void* palette;
    AnimState anim;
    TaskPool tasks;
    s32 state;
    BtlObj body;
    s16 stateTimer;
    s16 steps;
    s32 speed;
    s32 scaleX;
    s32 scaleY;
    u8 unk_158;
    u8 unk_159[0x03];
    s32 unk_15C;
    u16 unk_160;
    u8 variant;
    u8 mainSide;
    u8 animating;
    u8 unk_165[0x03];
    BtlObj* target;
    s16 targetIndex;
    u8 unk_16E[0x02];
    s32 targetX;
    s32 targetY;
    s32 targetZ;
    u16 attackCount;
    u8 unk_17E[0x02];
} SmnCloudWork;

typedef struct SmnBambiWork {
    void* tiles;
    void* palette;
    AnimState anim;
    TaskPool tasks;
    u32 state;
    BtlObj body;
    s16 stateTimer;
    s16 steps;
    s16 unk_14C;
    u8 unk_14E[0x02];
    s32 unk_150;
    s32 scale;
    u8 angle;
    u8 unk_159[0x03];
    s32 vz;
    u16 unk_160;
    u8 variant;
    u8 mainSide;
    u8 animating;
    u8 unk_165[0x03];
    struct BtlObj* target;
    s16 targetIndex;
    u8 unk_16E[0x02];
    s32 targetX;
    s32 targetY;
} SmnBambiWork;

typedef struct SmnTinkWork {
    void* tiles;
    void* palette;
    AnimState anim;
    TaskPool tasks;
    u32 state;
    BtlObj body;
    s16 stateTimer;
    s16 steps;
    s32 scale;
    u16 unk_150;
    u8 variant;
    u8 mainSide;
    u8 animating;
    u8 unk_155[0x0B];
    s32 hoverZ;
    u8 unk_164[0x04];
    s32 speed;
    u16 flyAngle;
    s16 healFrames;
    s16 frameCount;
    u8 unk_172[0x02];
    s32 healTarget;
    s32 healHp;
    struct BtlObj* actor;
} SmnTinkWork;

typedef struct SmnTinkeffWork {
    void* tiles;
    void* palette;
    AnimState anim;
    s32 x;
    s32 y;
    s32 z;
    s32 vz;
} SmnTinkeffWork;

typedef struct SmnSimbaWork {
    void* tiles;
    void* palette;
    AnimState anim;
    TaskPool tasks;
    u32 state;
    BtlObj body;
    s16 stateTimer;
    s16 steps;
    s16 unk_14C;
    u8 unk_14E[0x02];
    s32 scale;
    u8 variant;
    u8 mainSide;
    u8 animating;
    u8 unk_157;
} SmnSimbaWork;

typedef struct SmnMushuWork {
    void* tiles;
    void* palette;
    AnimState anim;
    TaskPool tasks;
    u32 state;
    BtlObj body;
    s16 stateTimer;
    s16 unk_14A;
    s32 scale;
    u16 unk_150;
    u8 variant;
    u8 mainSide;
    u8 animating;
    u8 unk_155[0x03];
    struct BtlObj* actor;
} SmnMushuWork;

typedef struct SmnDumboWork {
    void* tiles;
    void* palette;
    AnimState anim;
    TaskPool tasks;
    u32 state;
    BtlObj body;
    s16 stateTimer;
    s16 steps;
    s16 unk_14C;
    u8 unk_14E[0x02];
    s32 scale;
    u8 variant;
    u8 mainSide;
    u8 animating;
    u8 unk_157;
} SmnDumboWork;

typedef struct SmnGenieWork {
    void* tiles;
    void* palette;
    AnimState anim;
    TaskPool tasks;
    s32 state;
    BtlObj body;
    u16 stateTimer;
    s16 steps;
    s32 scale;
    u8 variant;
    u8 mainSide;
    u8 animating;
    u8 unk_153;
    struct BtlObj* target;
    s16 targetIndex;
    s16 attacksLeft;
    u8 fired;
    u8 unk_15D[3];
    s32 speedX;
    s32 speedY;
} SmnGenieWork;

typedef struct SmnPrizeArgs {
    s32 x;
    s32 y;
    s32 z;
    u8 unk_0C[0x06];
    s16 kind;
    s16 noTimeout;
    u8 unk_16[0x0A];
} SmnPrizeArgs;

typedef struct SmnKingWork {
    void* tiles;
    void* palette;
    AnimState anim;
    TaskPool tasks;
    s32 state;
    BtlObj body;
    s16 stateTimer;
    s16 steps;
    u16 unk_14C;
    u8 unk_14E[0x06];
    s32 scale;
    u32 vz;
    u8 variant;
    u8 mainSide;
    u8 animating;
    u8 unk_15F[0x09];
} SmnKingWork;

extern u8 gMickeyPalette[];
extern u8 gCroudPalette[];
extern u8 gBStatesPalette[];
extern u8 gBanbPalette[];
extern u8 gDamboPalette[];
extern u8 gShinbaPalette[];
extern u8 gTinkPalette[];
extern u8 gGeniePalette[];
extern u8 gMushuPalette[];
void SmnBambiPickHopTarget(SmnBambiWork* work);
void SmnGenieFollowTarget(SmnGenieWork* work);
u8 SmnBambiApplyGravity(SmnBambiWork* work);
BtlObj* SmnBambiNextTarget(SmnBambiWork* work);
BtlObj* SmnGenieNextTarget(SmnGenieWork* work);
void SmnTinkSpawnSparkle(SmnTinkWork* work);
u8 SmnKingApplyGravity(SmnKingWork* work);

#endif /* GUARD_SMN_H */
