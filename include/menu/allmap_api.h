#ifndef GUARD_ALLMAP_API_H
#define GUARD_ALLMAP_API_H

#include "types.h"

struct TaskPool;

void ClearStockMesDispWork();
u8 TestAllmapRoomFlag(u8 a, u16 b);
void* CreateAllmapRoomTask(struct TaskPool* pool);

#endif
