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
#include "gba/io_reg.h"
#include "system_state.h"

Mode* gCurrentMode;
void (*gCurrentModeUpdate)(void);
u16 gDebugModeIndex;
Mode* gPendingMode;
s32 gPendingModeArg;
vu8 gModeFlags;
u16 gModeBlankColor;
void (*gModeTransitionCallback)(void);
void (*gModeVBlankCallback)(void);
#ifdef VERSION_EU
u32 gUnkEu_030074AC;
#endif

Mode* gDebugModes[] = {
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
    if (t->desc->destroy != 0) {
        t->desc->destroy(t->work);
    }

    EwramFree(t->work);

    return ListPoolRelease(&t->node, a);
}

void TaskKill(TaskPool* a, Task* t) {
    if (t->desc->destroy != 0) {
        t->desc->destroy(t->work);
    }

    EwramFree(t->work);

    ListPoolRelease(&t->node, a);
}

Task* TaskCreate(TaskPool* a, TaskDesc* desc, void* arg) {
    Task* task;

    task = ListPoolFirstFree(a);

    if (task == 0) {
        return 0;
    }

    if (desc->workSize > 0) {
        task->work = EwramAlloc(desc->workSize);

        if (task->work == 0) {
            return 0;
        }
    } else {
        task->work = 0;
    }

    task->desc = desc;
    task->update = desc->update;
    ListPoolActivate(&task->node, a);

    if (desc->init != 0) {
        desc->init(task->work, arg);
    }

    return task;
}

void TaskPoolInit(TaskPool* a, s32 count) {
    Task* t;
    s32 i;

    a->tasks = EwramAlloc(count * sizeof(Task));

    if (a->tasks == 0) {
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

    while (t != 0) {
        if (t->update != 0 && t->update(t->work, t) == 0) {
            t = TaskDestroy(a, t);
        } else {
            t = ListPoolNext(&t->node);
        }
    }
}

void TaskPoolDraw(TaskPool* a) {
    Task* t;

    t = ListPoolFirst(&a->head);

    while (t != 0) {
        if (t->desc->draw != 0) {
            t->desc->draw(t->work);
        }

        t = ListPoolNext(&t->node);
    }
}

void TaskPoolDestroy(TaskPool* a) {
    Task* t;

    t = ListPoolFirst(&a->head);

    while (t != 0) {
        t = TaskDestroy(a, t);
    }

    EwramFree(a->tasks);
}

void func_08000F30(TaskPool* a) {
    Task* t;

    t = ListPoolFirst(&a->head);

    if (t != 0) {
        do {
            t = ListPoolNext(&t->node);
        } while (t != 0);
    }
}

u8 IsTaskActive(Task* t) {
    if (t == 0 || (t->node.flags & 1) == 0) {
        return 0;
    }

    return 1;
}

u8 IsTaskActiveNamed(Task* t, const char* name) {
    if (t == 0 || name == 0 || t->desc->name != name || (t->node.flags & 1) == 0) {
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

s32 func_08000F90(void) {
    return 0;
}

void ModeBlankDisplay(void) {
    REG_DISPCNT &= ~(DISPCNT_BG_ALL_ON | DISPCNT_OBJ_ON);
    *(vu16*)0x05000000 = gModeBlankColor;
}

void ModeStart(Mode* mode, s32 arg) {
    gModeBlankColor = FadeGetColor();
    VTransReset();
    BgReset();
    SpriteReset();
    FadeReset();
    MosaicReset();
    gCurrentMode = mode;

    if (mode->init != 0) {
        mode->init(arg);
    }

    gCurrentModeUpdate = gCurrentMode->update;
    gModeFlags |= 8;
}

#ifdef VERSION_EU
void ModeInit(u8 a) {
#else
void ModeInit(void) {
#endif
    gModeFlags = 3;
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
    gPendingMode = 0;
    gModeTransitionCallback = 0;
    gModeVBlankCallback = 0;
}
void ModeSetTransitionCallback(void (*a)(void), void (*b)(void)) {
    if (a != 0) {
        a();
    }

    gModeTransitionCallback = b;
    gModeFlags |= 4;
}

void ModeClearTransitionCallback(void) {
    gModeFlags &= ~4;
    gModeTransitionCallback = 0;
}

void ModeSetVBlankCallback(void (*fn)(void)) {
    gModeVBlankCallback = fn;
}

void ModeClearVBlankCallback(void) {
    gModeVBlankCallback = 0;
}

u8 IsModeStarted(void) {
    if (gModeFlags & 8) {
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
    gModeFlags |= 0x10;
}

#ifdef VERSION_EU
void eu_0800115C(void) {
    gSoftResetMarker[0] = 0xFEDCBA98;
    SoftReset(0xFD);
}
#endif

void ModeUpdate(void) {
    u8 v;

    if ((((GetKeysPressed() & START_BUTTON) && (GetKeysHeld() & SELECT_BUTTON) && (GetKeysHeld() & A_BUTTON) &&
             (GetKeysHeld() & B_BUTTON)) ||
            ((GetKeysHeld() & START_BUTTON) && (GetKeysPressed() & SELECT_BUTTON) && (GetKeysHeld() & A_BUTTON) &&
                (GetKeysHeld() & B_BUTTON))) &&
        !(gSystemFlags & 0x20)) {
        if (SioIsConnected()) {
            SioLinkClose();
        }

        m4aMPlayAllStop();
#ifdef VERSION_EU
        ScanlineDmaReset();
        eu_0800115C();
#else
        SoftReset(0xFF);
        ScanlineDmaReset();
#endif
    } else {
        if (gModeFlags & 4) {
            return;
        }

        v = gModeFlags & 2;

        if (v != 0) {
            if (gModeFlags & 1) {
                return;
            }

            FadeUpdate();
            FlushDma3QueueWithCpu();
            gModeFlags &= ~2;
        } else if (gPendingMode != 0) {
            if (gCurrentMode->exit != 0) {
                gCurrentMode->exit();
            }

            if (gModeFlags & 0x10) {
                gModeFlags &= ~0x10;
                EwramHeapInit(GetEwramHeapStart(), GetEwramHeapSize());
            }

            gModeFlags = 3;
            ModeStart(gPendingMode, gPendingModeArg);
            gPendingMode = 0;
        } else {
            if (gCurrentModeUpdate != 0) {
                gCurrentModeUpdate();
            }

            FadeUpdate();
            MosaicUpdate();
            SortSprites();
        }
    }
}
void SetModeUpdate(void (*fn)(void)) {
    gCurrentModeUpdate = fn;
}

void ModeFlushDisplay(void) {
    if (gModeFlags & 1) {
        ModeBlankDisplay();
        gModeFlags &= ~1;
    }

    if (!(gModeFlags & 2)) {
        if (gSystemFlags & 0x10) {
            FlushDma3QueueWithCpu();
        } else {
            FlushDma3Queue();
        }

        UpdateSpriteOam();
        CommitDisplayRegs();
    }
}

void ModeRunVBlankCallbacks(void) {
    if ((gModeFlags & 2) && gModeTransitionCallback != 0) {
        gModeTransitionCallback();
    }

    if (gModeVBlankCallback != 0) {
        gModeVBlankCallback();
    }
}

void ModeCallExit(void) {
    if (gCurrentMode->exit != 0) {
        gCurrentMode->exit();
    }
}

const char* GetModeName(void) {
    return gCurrentMode->name;
}

void UpdateDebugModeSelect(void) {
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

            ModeRequest(gDebugModes[(s16)gDebugModeIndex], 0);
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

            ModeRequest(gDebugModes[(s16)gDebugModeIndex], 0);
        }
    }
}
