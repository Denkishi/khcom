#ifndef GUARD_EVT_OBJ_API_H
#define GUARD_EVT_OBJ_API_H

#include "types.h"

struct EvtObj;
struct Task;

void EvtObjSetAnim(struct EvtObj* obj, s32 anim);
void EvtObjSetPos(struct EvtObj* obj, s32 a, s32 b, s32 c);
void CreateEvtObjTask(void* pool, struct EvtObj* obj, s32 res, s32 anim, s32 a, s32 b, s32 c);
void EvtObjSetDrawFlags(struct EvtObj* obj, u16 a);
struct Task* CreateEvtObjTaskWithDesc(void* pool, void* desc, struct EvtObj* obj, s32 res, s32 anim, s32 a, s32 b, s32 c);

#endif
