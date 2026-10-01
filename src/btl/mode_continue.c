#include "continue_ui.h"
#include "map_api.h"
#include "mode.h"
#include "continue_types.h"
#include "game_state.h"
#include "gba/syscall.h"
#include "taskpool.h"

TaskPool gContinueTaskPool;
Task* gContinueTask;

static void Continue_0() {
    TaskPoolInit(&gContinueTaskPool, 2);

    if ((gGameState.flags & GAME_FLAG_RIKU) == 0) {
        gContinueTask = TaskCreate(&gContinueTaskPool, &gTaskDescContinueSora, 0);
    } else {
        gContinueTask = TaskCreate(&gContinueTaskPool, &gTaskDescContinueRiku, 0);
    }
}

void ContinueModeUpdate() {
    ContinueWork* w;

    TaskPoolUpdate(&gContinueTaskPool);
    TaskPoolDraw(&gContinueTaskPool);
    w = gContinueTask->work;

    if (w->state == 3) {
        switch (w->cursor) {
        case 0:
            RequestMapMode();
            break;
        case 1:
#ifdef VERSION_EU
            eu_0800115C();
#else
            SoftReset(RESET_ALL);
#endif
            break;
        }
    }
}

static void Continue_2() {
    TaskPoolDestroy(&gContinueTaskPool);
}

Mode gModeContinue = {
    "Continue",
    (ModeInitFunc)Continue_0,
    ContinueModeUpdate,
    Continue_2,
};
