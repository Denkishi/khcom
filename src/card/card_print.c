#include "registration_data.h"
#include "taskpool.h"
#include "card.h"
#include "types.h"

void task_print_0(void) {
    InitPrintLayer(0);
}

s32 task_print_1(void) {
    return 1;
}

void task_print_2(void) {
    ResetPrintLines();
}

void task_print_3(void) {
    FreePrintLayer();
}

TaskDesc gTaskDescPrint = {
    "task_print",
    (TaskInitFunc)task_print_0,
    (TaskUpdateFunc)task_print_1,
    (TaskDrawFunc)task_print_2,
    (TaskDestroyFunc)task_print_3,
    sizeof(PrintWork),
};
