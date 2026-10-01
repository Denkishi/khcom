#include "registration_data.h"
#include "display.h"
#include "taskpool.h"
#include "card_api.h"
#include "mode.h"
#include "types.h"

#ifdef VERSION_EU

static TaskPool sTextCheckTasks;

static u32 sTextCheckMessageId;

void eu_080AB9FC() {
    sTextCheckMessageId = 0;
    SetBgMode0();
    SetupBg(0, 0, 28, 14);
    TaskPoolInit(&sTextCheckTasks, 1);
    CreateCardMessageTask(&sTextCheckTasks, 0, sTextCheckMessageId);
}

void eu_080ABA38() {
    if (IsMessageWindowOpen() == 0) {
        sTextCheckMessageId++;

        if (sTextCheckMessageId == 179) {
            sTextCheckMessageId = 0;
        }

        CreateCardMessageTask(&sTextCheckTasks, 0, sTextCheckMessageId);
    }

    TaskPoolUpdate(&sTextCheckTasks);
    TaskPoolDraw(&sTextCheckTasks);
}

void eu_080ABA7C() {
    TaskPoolDestroy(&sTextCheckTasks);
}

Mode gModeTextCheck = {
    "Mode_textcheck",
    (ModeInitFunc)eu_080AB9FC,
    eu_080ABA38,
    eu_080ABA7C,
};

#endif
