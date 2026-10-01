#include "card_api.h"
#include "display.h"
#include "gba/keys.h"
#include "key.h"
#include "malloc.h"
#include "mode_chkmov.h"
#include "registration_data.h"
#include "taskpool.h"
#include "mode.h"
#include "types.h"

#ifdef VERSION_EU

MovieDebugWork* gMovieDebugWorkEu;

extern const char gMovieDebugTextEu_0812F6D4[];
extern const char gMovieDebugTextEu_0812F6F4[];

extern const MovieDebugEntry gMovieDebugEntriesEu[5];

void eu_0800C76C(s32 arg) {
    gMovieDebugWorkEu = EwramAlloc(sizeof(MovieDebugWork));
    SetBgMode0();
    gMovieDebugWorkEu->index = 0;
    TaskPoolInit(&gMovieDebugWorkEu->pool, 10);
    TaskCreate(&gMovieDebugWorkEu->pool, &gTaskDescPrint, 0);
}

void eu_0800C7A0() {
    u16 cancel = GetKeysPressed() & B_BUTTON;

    if (cancel) {
        ModeRequest(&gModeDebug, 0);
        return;
    }

    if (GetKeysRepeat() & DPAD_LEFT) {
        gMovieDebugWorkEu->index--;
    }

    if (GetKeysRepeat() & DPAD_RIGHT) {
        gMovieDebugWorkEu->index++;
    }

    if (gMovieDebugWorkEu->index < 0) {
        gMovieDebugWorkEu->index = 4;
    }

    if (gMovieDebugWorkEu->index > 4) {
        gMovieDebugWorkEu->index = 0;
    }

    if (GetKeysPressed() & A_BUTTON) {
        ModeRequestHeapReset(&gModeMovie, gMovieDebugEntriesEu[gMovieDebugWorkEu->index].movie);
        return;
    }

    PrintString(0, 0, 0, gMovieDebugTextEu_0812F6D4);
    PrintNumber(0, 0, 0, gMovieDebugWorkEu->index);
    PrintString(5, 0, 0, gMovieDebugTextEu_0812F6F4);
    PrintString(7, 0, 0, gMovieDebugEntriesEu[gMovieDebugWorkEu->index].label);
    TaskPoolUpdate(&gMovieDebugWorkEu->pool);
    TaskPoolDraw(&gMovieDebugWorkEu->pool);
}

void eu_0800C898() {
    TaskPoolDestroy(&gMovieDebugWorkEu->pool);
    EwramFree(gMovieDebugWorkEu);
}

const MovieDebugEntry gMovieDebugEntriesEu[5] = {
    {1, "OPENING"},
    {2, "6F_GOAL"},
    {3, "12F_E2"},
    {4, "ENDING"},
    {5, "RIKU_ENDING"},
};

const char gMovieDebugTextEu_0812F6D4[] = "                              ";

const char gMovieDebugTextEu_0812F6F4[] = ": ";

Mode gModeMovieDebugEu = {
    "mode_chkmov",
    eu_0800C76C,
    eu_0800C7A0,
    eu_0800C898,
};

#endif
