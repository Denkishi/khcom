/**
 * mode_chkmov.c
 * Debug Movie Check
 */

#include "card_api.h"
#include "display.h"
#include "gba/keys.h"
#include "key.h"
#include "malloc.h"
#include "mode_chkmov.h"
#include "registration_data.h"
#include "taskpool.h"
#include "mode.h"
#include <stddef.h>
#include "types.h"

#ifdef VERSION_EU

static MovieDebugWork* sMovieDebugWorkEu;

extern const char gMovieDebugTextEu_0812F6D4[];
extern const char gMovieDebugTextEu_0812F6F4[];

extern const MovieDebugEntry gMovieDebugEntriesEu[5];

void eu_0800C76C(s32 arg) {
    sMovieDebugWorkEu = EwramAlloc(sizeof(MovieDebugWork));
    SetBgMode0();
    sMovieDebugWorkEu->index = 0;
    TaskPoolInit(&sMovieDebugWorkEu->pool, 10);
    TaskCreate(&sMovieDebugWorkEu->pool, &gTaskDescPrint, NULL);
}

void mode_chkmov_1() {
    u16 cancel = GetKeysPressed() & B_BUTTON;

    if (cancel) {
        ModeRequest(&gModeDebug, 0);
        return;
    }

    if (GetKeysRepeat() & DPAD_LEFT) {
        sMovieDebugWorkEu->index--;
    }

    if (GetKeysRepeat() & DPAD_RIGHT) {
        sMovieDebugWorkEu->index++;
    }

    if (sMovieDebugWorkEu->index < 0) {
        sMovieDebugWorkEu->index = 4;
    }

    if (sMovieDebugWorkEu->index > 4) {
        sMovieDebugWorkEu->index = 0;
    }

    if (GetKeysPressed() & A_BUTTON) {
        ModeRequestHeapReset(&gModeMovie, gMovieDebugEntriesEu[sMovieDebugWorkEu->index].movie);
        return;
    }

    PrintString(0, 0, 0, gMovieDebugTextEu_0812F6D4);
    PrintNumber(0, 0, 0, sMovieDebugWorkEu->index);
    PrintString(5, 0, 0, gMovieDebugTextEu_0812F6F4);
    PrintString(7, 0, 0, gMovieDebugEntriesEu[sMovieDebugWorkEu->index].label);
    TaskPoolUpdate(&sMovieDebugWorkEu->pool);
    TaskPoolDraw(&sMovieDebugWorkEu->pool);
}

void mode_chkmov_2() {
    TaskPoolDestroy(&sMovieDebugWorkEu->pool);
    EwramFree(sMovieDebugWorkEu);
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
    mode_chkmov_1,
    mode_chkmov_2,
};

#endif
