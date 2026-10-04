#include "listpool.h"
#include "taskpool.h"
#include "malloc.h"
#include "main.h"
#include <stddef.h>
#include "types.h"

Task* TaskDestroy(TaskPool* a, Task* t) {
    if (t->desc->destroy != NULL) {
        t->desc->destroy(t->work);
    }

    EwramFree(t->work);

    return ListPoolRelease(&t->node, a);
}

void TaskKill(TaskPool* a, Task* t) {
    if (t->desc->destroy != NULL) {
        t->desc->destroy(t->work);
    }

    EwramFree(t->work);

    ListPoolRelease(&t->node, a);
}

Task* TaskCreate(TaskPool* a, TaskDesc* desc, const void* arg) {
    Task* task;

    task = ListPoolFirstFree(a);

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
    ListPoolActivate(&task->node, a);

    if (desc->init != NULL) {
        desc->init(task->work, arg);
    }

    return task;
}

void TaskPoolInit(TaskPool* a, s32 count) {
    Task* t;
    s32 i;

    a->tasks = EwramAlloc(count * sizeof(Task));

    if (a->tasks == NULL) {
        return;
    }

    ListPoolInit(a);

    for (i = 0; i < count; i++) {
        t = &((Task*)a->tasks)[i];
        ListPoolAddFree(&t->node, a, t);
    }
}

void TaskPoolUpdate(TaskPool* a) {
    Task* t;

    t = ListPoolFirst(&a->head);

    while (t != NULL) {
        if (t->update != NULL && t->update(t->work, t) == 0) {
            t = TaskDestroy(a, t);
        } else {
            t = ListPoolNext(&t->node);
        }
    }
}

void TaskPoolDraw(TaskPool* a) {
    Task* t;

    t = ListPoolFirst(&a->head);

    while (t != NULL) {
        if (t->desc->draw != NULL) {
            t->desc->draw(t->work);
        }

        t = ListPoolNext(&t->node);
    }
}

void TaskPoolDestroy(TaskPool* a) {
    Task* t;

    t = ListPoolFirst(&a->head);

    while (t != NULL) {
        t = TaskDestroy(a, t);
    }

    EwramFree(a->tasks);
}

void func_08000F30(TaskPool* a) {
    Task* t;

    t = ListPoolFirst(&a->head);

    if (t != NULL) {
        do {
            t = ListPoolNext(&t->node);
        } while (t != NULL);
    }
}

u8 IsTaskActive(Task* t) {
    if (t == NULL || (t->node.flags & LIST_NODE_FLAG_ACTIVE) == 0) {
        return 0;
    }

    return 1;
}

u8 IsTaskActiveNamed(Task* t, const char* name) {
    if (t == NULL || name == NULL || t->desc->name != name || (t->node.flags & LIST_NODE_FLAG_ACTIVE) == 0) {
        return 0;
    }

    return 1;
}

const char* GetTaskName(Task* t) {
    return t->desc->name;
}

void SetTaskUpdate(Task* task, TaskUpdateFunc update) {
    task->update = update;
}

s32 func_08000F90() {
    return 0;
}
