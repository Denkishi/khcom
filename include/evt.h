#ifndef GUARD_EVT_H
#define GUARD_EVT_H

#include "task_descriptors.h"
#include "evt_object_types.h"

#include "evt_tasks.h"

#include "obj.h"
#include "obj_api.h"
#include "types.h"
#include "anim.h"
#include "taskpool.h"
#include "evt_types.h"
#include "evt_data.h"
#include "game.h"
#include "evt_api.h"

typedef struct EvtObjParam {
    EvtObjRes* res;
    EvtObj* obj;
} EvtObjParam;

typedef struct EvtObjWork {
    EvtObj* obj;
    void* tiles;
    ObjPalette* palette;
    AnimState anim;
    TaskPool tasks;
} EvtObjWork;

typedef struct EvtShadowWork {
    void* palette;
    EvtObj* obj;
    void* tiles;
    void* tiles2;
    void* tiles3;
} EvtShadowWork;

extern u8 gUnk_08F69BE4[];

void func_0801CD94(EvtObj* obj, s32 a);
void EvtObjChangeAnim(EvtObjWork* work);

#endif /* GUARD_EVT_H */
