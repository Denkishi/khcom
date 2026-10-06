/**
 * taskpool.c
 * Task Pool Management
 */

#include "listpool.h"
#include "taskpool.h"
#include "malloc.h"
#include "main.h"
#include <stddef.h>
#include "types.h"

Task* TaskDestroy(TaskPool* pool, Task* task) {
    if (task->desc->destroy != NULL) {
        task->desc->destroy(task->work);
    }

    EwramFree(task->work);

    return ListPoolRelease(&task->node, pool);
}

void TaskKill(TaskPool* pool, Task* task) {
    if (task->desc->destroy != NULL) {
        task->desc->destroy(task->work);
    }

    EwramFree(task->work);

    ListPoolRelease(&task->node, pool);
}

Task* TaskCreate(TaskPool* pool, TaskDesc* desc, const void* arg) {
    Task* task;

    task = ListPoolFirstFree(pool);

    if (task == NULL) {
        return NULL;
    }

    if (desc->workSize > 0) {
        task->work = EwramAlloc(desc->workSize);

        if (task->work == NULL) {
            return NULL;
        }
    } else {
        task->work = NULL;
    }

    task->desc = desc;
    task->update = desc->update;
    ListPoolActivate(&task->node, pool);

    if (desc->init != NULL) {
        desc->init(task->work, arg);
    }

    return task;
}

void TaskPoolInit(TaskPool* pool, s32 count) {
    Task* t;
    s32 i;

    pool->tasks = EwramAlloc(count * sizeof(Task));

    if (pool->tasks == NULL) {
        return;
    }

    ListPoolInit(pool);

    for (i = 0; i < count; i++) {
        t = &((Task*)pool->tasks)[i];
        ListPoolAddFree(&t->node, pool, t);
    }
}

void TaskPoolUpdate(TaskPool* pool) {
    Task* t;

    t = ListPoolFirst(&pool->head);

    while (t != NULL) {
        if (t->update != NULL && t->update(t->work, t) == 0) {
            t = TaskDestroy(pool, t);
        } else {
            t = ListPoolNext(&t->node);
        }
    }
}

void TaskPoolDraw(TaskPool* pool) {
    Task* t;

    t = ListPoolFirst(&pool->head);

    while (t != NULL) {
        if (t->desc->draw != NULL) {
            t->desc->draw(t->work);
        }

        t = ListPoolNext(&t->node);
    }
}

void TaskPoolDestroy(TaskPool* pool) {
    Task* t;

    t = ListPoolFirst(&pool->head);

    while (t != NULL) {
        t = TaskDestroy(pool, t);
    }

    EwramFree(pool->tasks);
}

void func_08000F30(TaskPool* pool) {
    Task* t;

    t = ListPoolFirst(&pool->head);

    if (t != NULL) {
        do {
            t = ListPoolNext(&t->node);
        } while (t != NULL);
    }
}

u8 IsTaskActive(Task* task) {
    if (task == NULL || (task->node.flags & LIST_NODE_FLAG_ACTIVE) == 0) {
        return 0;
    }

    return 1;
}

u8 IsTaskActiveNamed(Task* task, const char* name) {
    if (task == NULL || name == NULL || task->desc->name != name || (task->node.flags & LIST_NODE_FLAG_ACTIVE) == 0) {
        return 0;
    }

    return 1;
}

const char* GetTaskName(Task* task) {
    return task->desc->name;
}

void SetTaskUpdate(Task* task, TaskUpdateFunc update) {
    task->update = update;
}

s32 func_08000F90() {
    return 0;
}
