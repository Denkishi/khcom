#ifndef GUARD_FRD_H
#define GUARD_FRD_H

#include "task_descriptors.h"
#include "registration_data.h"

#include "frd_tasks.h"

#include "display.h"
#include "m4a_song.h"
#include "fade.h"
#include "btl_effect.h"
#include "btl_collision.h"
#include "obj_api.h"
#include "battle_actor.h"
#include "types.h"
#include "engine_math.h"
#include "battle_work.h"
#include "game_state.h"
#include "anim.h"
#include "taskpool.h"
#include "smn_api.h"
#include "btl_api.h"

typedef struct FrdArgs {
    u16 variant;
    u8 mainSide;
    u8 unk_03;
} FrdArgs;

typedef struct FrdDonaldWork {
    TaskPool tasks;
    BtlObj* actor;
    void* tiles;
    void* palette;
    BtlObj body;
    AnimState anim;
    s32 state;
    u8 mainSide;
    u8 variant;
    s16 stateTimer;
    s16 steps;
    u8 unk_152[0x02];
    s32 vz;
    s32 unk_158;
    s32 unk_15C;
    s16 repeatsLeft;
    u8 unk_162[0x02];
} FrdDonaldWork;

typedef struct FrdGoofyWork {
    TaskPool tasks;
    BtlObj* actor;
    void* tiles;
    void* palette;
    BtlObj body;
    AnimState anim;
    u32 state;
    u8 mainSide;
    u8 variant;
    s16 stateTimer;
    s16 steps;
    u8 unk_152[0x02];
    s32 vz;
    s32 targetX;
    s32 targetY;
    u8 angle;
    u8 unk_161[0x03];
} FrdGoofyWork;

typedef struct FrdArielWork {
    TaskPool tasks;
    BtlObj* actor;
    void* tiles;
    void* palette;
    BtlObj body;
    AnimState anim;
    u32 state;
    u8 mainSide;
    u8 variant;
    s16 stateTimer;
    s16 steps;
    u8 unk_152[0x02];
    s32 hoverZ;
    s16 passesLeft;
    u8 unk_15A[0x02];
    s32 passSpeed;
    s32 speed;
} FrdArielWork;

typedef struct FrdJackWork {
    TaskPool tasks;
    BtlObj* actor;
    void* tiles;
    void* palette;
    BtlObj body;
    AnimState anim;
    s32 state;
    u8 mainSide;
    u8 variant;
    s16 stateTimer;
    s16 steps;
    s16 unk_152;
    s32 vz;
    s32 targetX;
    s32 targetY;
    s32 rotation;
    s32 rotationTarget;
    s16 repeatsLeft;
    u8 unk_16A[0x02];
} FrdJackWork;

typedef struct FrdPanWork {
    TaskPool tasks;
    BtlObj* actor;
    void* tiles;
    void* palette;
    BtlObj body;
    AnimState anim;
    u32 state;
    u8 mainSide;
    u8 variant;
    s16 stateTimer;
    s16 steps;
    s16 duration;
    s16 unk_154;
    s16 unk_156;
    s32 unk_158;
    s32 targetX;
    s32 unk_160;
    s32 hoverZ;
    s32 vx;
    u8 flyLeft;
    u8 unk_16D[0x03];
} FrdPanWork;

typedef struct FrdAladdinWork {
    TaskPool tasks;
    BtlObj* actor;
    void* tiles;
    void* palette;
    BtlObj body;
    AnimState anim;
    u32 state;
    u8 mainSide;
    u8 variant;
    s16 stateTimer;
    s16 steps;
    s16 duration;
    s32 vz;
    s32 targetX;
    u8 unk_15C[0x04];
} FrdAladdinWork;

typedef struct FrdBeastWork {
    TaskPool tasks;
    BtlObj* actor;
    void* tiles;
    void* palette;
    BtlObj body;
    AnimState anim;
    s32 state;
    u8 mainSide;
    u8 variant;
    s16 stateTimer;
    s32 targetX;
    s32 targetY;
    s32 vz;
    s32 attack;
} FrdBeastWork;

extern u8 gDonaldPalette[];
extern u8 gGoofyPalette[];
extern u8 gArielPalette[];
extern u8 gJackPalette[];
extern u8 gPeterPalette[];
extern u8 gAladdinPalette[];
extern u8 gBeastPalette[];

u8 FrdJackApplyGravity(FrdJackWork* work);
void FrdPanHover(FrdPanWork* work);
void FrdPanSpawnSparkle(FrdPanWork* work);
u8 FrdGoofyApplyGravity(FrdGoofyWork* work);
u8 FrdAladdinApplyGravity(FrdAladdinWork* work);

#endif /* GUARD_FRD_H */
