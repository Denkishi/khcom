#ifndef GUARD_FLD_H
#define GUARD_FLD_H

#include "task_descriptors.h"

#include "field_state.h"

#include "map_types.h"

#include "map_api.h"
#include "fld_tasks.h"

#include "m4a_song.h"
#include <stdlib.h>
#include "fade.h"
#include "btl_collision.h"
#include "obj_api.h"
#include "types.h"
#include "engine_math.h"
#include "game_state.h"
#include "anim.h"
#include "taskpool.h"
#include "key.h"
#include "game.h"
#include "fld_types.h"
#include "bos4_api.h"





typedef struct FldShadowWork {
    s32 x;
    s32 y;
    void* tiles;
    void* palette;
    FldObj* actor;
    AnimState anim;
} FldShadowWork;

typedef char FldShadowWork_size[(sizeof(FldShadowWork) == 0x2C) ? 1 : -1];

void FldRikuSetAnim(FldWork* work, s32 index, u16 flags);

void CreateWorldSelBeforeTask(void* a, s32 x, s32 y, s32 z);

extern u8 gSoraPalette[];
extern u8 gRikuPalette[];
extern u8 gUnk_08F69BE4[];

u8 FldRikuCheckBlocked(FldPos* p);
s32 FldRikuProbeGround(FldPos* p);
u8 FldRikuCheckClimb(FldPos* p, FldWork* work);
u8 FldRikuCheckDoorAhead(FldActor* act);
s32 FldRikuGetGround(FldWork* work);
void FldRikuSetAngleFromDpad(FldActor* act);
void FldRikuTurn(FldActor* act);
u8 FldSoraWaitRoomCreate(FldWork* work, void* task);
u8 FldSoraGmkJump(FldWork* work, void* task);
u8 FldSoraJump(FldWork* work, void* task);
u8 FldSoraClimb(FldWork* work, void* task);
u8 FldSoraLedgeInput(FldWork* work, void* task);
u8 FldSoraHangLedge(FldWork* work, void* task);
u8 FldSoraWalkOut(FldWork* work, void* task);
u8 FldSoraAttack(FldWork* work, void* task);
u8 FldRikuGmkJump(FldWork* work, void* task);
u8 FldRikuJump(FldWork* work, void* task);
u8 FldRikuClimb(FldWork* work, void* task);
u8 FldRikuLedgeInput(FldWork* work, void* task);
u8 FldRikuHangLedge(FldWork* work, void* task);
u8 FldRikuWalkOut(FldWork* work, void* task);
u8 FldRikuAttack(FldWork* work, void* task);
u8 FldRikuWaitRoomCreate(FldWork* work, void* task);

#endif /* GUARD_FLD_H */
