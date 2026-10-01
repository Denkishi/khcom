#include "mode_battle_data.h"
#include "registration_data.h"
#include "chara_api.h"
#include "display.h"
#include "m4a_song.h"
#include "sio_api.h"
#include "obj_api.h"
#include "fade.h"
#include "listpool.h"
#include "taskpool.h"
#include "gba/syscall.h"
#include "key.h"
#include "malloc.h"
#include "main.h"
#include "mode.h"
#include "gba/keys.h"
#include "sroll_api.h"
#include "gba/defines.h"
#include "gba/io_reg.h"
#include "system_state.h"
#include <stddef.h>
#include "types.h"

Mode* gCurrentMode;
void (*gCurrentModeUpdate)();
u16 gDebugModeIndex;
Mode* gPendingMode;
s32 gPendingModeArg;
vu8 gModeFlags;
u16 gModeBlankColor;
void (*gModeTransitionCallback)();
void (*gModeVBlankCallback)();

#ifdef VERSION_EU
u32 gUnkEu_030074AC;
#endif

static Mode* sDebugModes[] = {
    &gModeDebug,
    &gModeJiminy,
#ifndef VERSION_EU
    &gModeDeckExchange,
#endif
    &gModePremire,
    &gModeWORLDSELECT,
    &gModeDeck,
    &gModeRikuBtlTutorial,
    &gModeRikuDeckTutorial,
#ifdef VERSION_EU
    &gModeTextCheck,
#endif
    &gModeWLogo,
    &gModeSioBattle,
    &gModeSioBtlConnect,
    &gModeSioBtlOption,
    &gModeSioBtlCardget,
    &gModeSioError,
#ifndef VERSION_EU
    &gModeSioChgConnect,
    &gModeSioChgCard,
#endif
    &gModeSioDbgFlg,
    &gModeTitle,
    &gModeCopyright1,
    &gModeCopyright2,
    &gModeMapChk,
    &gModeWorldselect,
    &gModeWorldinspect,
    &gModeWorldwarp,
    &gModeMsTop,
    &gModeMapinspect,
};

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

void ModeBlankDisplay() {
    REG_DISPCNT &= ~(DISPCNT_BG_ALL_ON | DISPCNT_OBJ_ON);
    *(vu16*)PLTT = gModeBlankColor;
}

void ModeStart(Mode* mode, s32 arg) {
    gModeBlankColor = FadeGetColor();
    VTransReset();
    BgReset();
    SpriteReset();
    FadeReset();
    MosaicReset();
    gCurrentMode = mode;

    if (mode->init != NULL) {
        mode->init(arg);
    }

    gCurrentModeUpdate = gCurrentMode->update;
    gModeFlags |= MODE_FLAG_STARTED;
}

#ifdef VERSION_EU
void ModeInit(u8 a) {
#else
void ModeInit() {
#endif
    gModeFlags = (MODE_FLAG_BLANK_PENDING | MODE_FLAG_DISPLAY_HELD);
    gModeBlankColor = 0;
    gDebugModeIndex = 0;

#ifdef VERSION_EU
    if (a) {
        ModeStart(&gModeCopyright1, 0);
    } else {
        ModeStart(&gModeLang, 0);
    }
#else
    ModeStart(&gModeCopyright1, 0);
#endif
    gPendingMode = NULL;
    gModeTransitionCallback = NULL;
    gModeVBlankCallback = NULL;
}

void ModeSetTransitionCallback(void (*a)(), void (*b)()) {
    if (a != NULL) {
        a();
    }

    gModeTransitionCallback = b;
    gModeFlags |= MODE_FLAG_TRANSITION_ACTIVE;
}

void ModeClearTransitionCallback() {
    gModeFlags &= ~MODE_FLAG_TRANSITION_ACTIVE;
    gModeTransitionCallback = NULL;
}

void ModeSetVBlankCallback(void (*fn)()) {
    gModeVBlankCallback = fn;
}

void ModeClearVBlankCallback() {
    gModeVBlankCallback = NULL;
}

u8 IsModeStarted() {
    if (gModeFlags & MODE_FLAG_STARTED) {
        return 1;
    }

    return 0;
}

void ModeRequest(Mode* mode, s32 arg) {
    gPendingMode = mode;
    gPendingModeArg = arg;
}

void ModeRequestHeapReset(Mode* mode, s32 arg) {
    gPendingMode = mode;
    gPendingModeArg = arg;
    gModeFlags |= MODE_FLAG_HEAP_RESET;
}

#ifdef VERSION_EU
void DoSoftReset() {
    gSoftResetMarker[0] = SOFT_RESET_MAGIC;
    SoftReset(RESET_ALL & ~RESET_IWRAM);
}
#endif

void ModeUpdate() {
    u8 v;

    if ((((GetKeysPressed() & START_BUTTON) && (GetKeysHeld() & SELECT_BUTTON) && (GetKeysHeld() & A_BUTTON) &&
             (GetKeysHeld() & B_BUTTON)) ||
            ((GetKeysHeld() & START_BUTTON) && (GetKeysPressed() & SELECT_BUTTON) && (GetKeysHeld() & A_BUTTON) &&
                (GetKeysHeld() & B_BUTTON))) &&
        !(gSystemFlags & SYSTEM_FLAG_NO_SOFT_RESET)) {
        if (SioIsConnected()) {
            SioLinkClose();
        }

        m4aMPlayAllStop();
#ifdef VERSION_EU
        ScanlineDmaReset();
        DoSoftReset();
#else
        SoftReset(RESET_ALL);
        ScanlineDmaReset();
#endif
    } else {
        if (gModeFlags & MODE_FLAG_TRANSITION_ACTIVE) {
            return;
        }

        v = gModeFlags & MODE_FLAG_DISPLAY_HELD;

        if (v != 0) {
            if (gModeFlags & MODE_FLAG_BLANK_PENDING) {
                return;
            }

            FadeUpdate();
            FlushDma3QueueWithCpu();
            gModeFlags &= ~MODE_FLAG_DISPLAY_HELD;
        } else if (gPendingMode != NULL) {
            if (gCurrentMode->exit != NULL) {
                gCurrentMode->exit();
            }

            if (gModeFlags & MODE_FLAG_HEAP_RESET) {
                gModeFlags &= ~MODE_FLAG_HEAP_RESET;
                EwramHeapInit(GetEwramHeapStart(), GetEwramHeapSize());
            }

            gModeFlags = (MODE_FLAG_BLANK_PENDING | MODE_FLAG_DISPLAY_HELD);
            ModeStart(gPendingMode, gPendingModeArg);
            gPendingMode = NULL;
        } else {
            if (gCurrentModeUpdate != NULL) {
                gCurrentModeUpdate();
            }

            FadeUpdate();
            MosaicUpdate();
            SortSprites();
        }
    }
}

void SetModeUpdate(void (*fn)()) {
    gCurrentModeUpdate = fn;
}

void ModeFlushDisplay() {
    if (gModeFlags & MODE_FLAG_BLANK_PENDING) {
        ModeBlankDisplay();
        gModeFlags &= ~MODE_FLAG_BLANK_PENDING;
    }

    if (!(gModeFlags & MODE_FLAG_DISPLAY_HELD)) {
        if (gSystemFlags & SYSTEM_FLAG_DMA3_FLUSH_CPU) {
            FlushDma3QueueWithCpu();
        } else {
            FlushDma3Queue();
        }

        UpdateSpriteOam();
        CommitDisplayRegs();
    }
}

void ModeRunVBlankCallbacks() {
    if ((gModeFlags & MODE_FLAG_DISPLAY_HELD) && gModeTransitionCallback != NULL) {
        gModeTransitionCallback();
    }

    if (gModeVBlankCallback != NULL) {
        gModeVBlankCallback();
    }
}

void ModeCallExit() {
    if (gCurrentMode->exit != NULL) {
        gCurrentMode->exit();
    }
}

const char* GetModeName() {
    return gCurrentMode->name;
}

void UpdateDebugModeSelect() {
    if (GetKeysHeld() & SELECT_BUTTON) {
        if (GetKeysPressed() & L_BUTTON) {
            gDebugModeIndex--;

            if ((s16)gDebugModeIndex < 0) {
#ifdef VERSION_EU
                gDebugModeIndex = 23;
#else
                gDebugModeIndex = 25;
#endif
            }

            ModeRequest(sDebugModes[(s16)gDebugModeIndex], 0);
        }

        if (GetKeysPressed() & R_BUTTON) {
            gDebugModeIndex++;

#ifdef VERSION_EU
            if (gDebugModeIndex > 23) {
#else
            if (gDebugModeIndex > 25) {
#endif
                gDebugModeIndex = 0;
            }

            ModeRequest(sDebugModes[(s16)gDebugModeIndex], 0);
        }
    }
}
