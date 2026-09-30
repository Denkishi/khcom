#include "task_descriptors.h"
#include "registration_data.h"
#ifndef GUARD_ROOMCREATE_H
#define GUARD_ROOMCREATE_H

#include "field_state.h"

#include "card_api.h"

#include "map_api.h"
#include "roomcreate_tasks.h"

#include "fade.h"
#include "types.h"
#include "engine_math.h"
#include "m4a.h"
#include "m4a_catalog_data.h"
#include "taskpool.h"
#include "fld_types.h"
#include "engine.h"
#include "bos4_api.h"


typedef struct RoomCreateWork {
    s32 x;
    s32 y;
    s32 z;
    s32 x2;
    s32 y2;
    s32 z2;
    s32 frontX;
    s32 frontY;
    s32 frontZ;
    u8 angle;
    u8 playerAngle;
    s16 timer;
    u8 spotLightEnd;
    u8 mapSelectStatus;
    u8 unk_2A[0x02];
    TaskPool tasks;
    s32 state;
} RoomCreateWork;


struct Task;

void CreateMapCardSelection(TaskPool* pool, u8* p);
void MapRestoreBg1(void);

#endif /* GUARD_ROOMCREATE_H */
