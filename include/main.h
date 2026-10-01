#ifndef GUARD_MAIN_H
#define GUARD_MAIN_H

#include "types.h"
#include "taskpool.h"

struct Task;

void func_08000F30(TaskPool* a);
s32 func_08000F90();

void InitSystem();
void InitIntrTable();

void* GetEwramHeapStart();
u32 GetEwramHeapSize();

#endif /* GUARD_MAIN_H */
