#ifndef GUARD_MODE_ALLMAP_H
#define GUARD_MODE_ALLMAP_H

#include "types.h"
#include "taskpool.h"

typedef struct AllmapRoomOrder {
    s32 shapes[16];
} AllmapRoomOrder;

typedef struct AllmapRoomDirs {
    s32 animIds[4];
} AllmapRoomDirs;

extern u16 gAllmapPalTimer;
extern u16 gAllmapPalStep;
extern TaskPool gAllmapTaskPool;
extern u8 gUnk_05000140[];
extern u8 gUnk_0984A0F8[];
extern u8 gUnk_09849F78[];

void InitAllmap(void);
void UpdateAllmap(void);
void DestroyAllmap(void);

void mode_allmap_0(s32 a);
void func_080D3370(void);
void mode_allmap_1(void);
void mode_allmap_2(void);
u8 func_080D3538(u8 a, u8 b);

#endif /* GUARD_MODE_ALLMAP_H */
