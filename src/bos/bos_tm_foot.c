#include "macros.h"
#include "registration_data.h"
#include "boss_tm.h"
#include "boss_tm_assets.h"
#include "sprites_boss_tm.h"
#include "engine_math.h"
#include "m4a_song.h"
#include "btl_effect.h"
#include "system_state.h"
#include "acgtrans.h"
#include "sprites_wlogo.h"

extern u8 gBosTmFootIdleFrames[8];
extern s16 gBosTmFootIdleZ[5];
extern TmFootStep gBosTmFootSteps[3];
extern TmFootStep gBosTmFootThrowSteps[16];
extern TmFootStep gBosTmFootWalkSteps[10];
extern TmFootStep gUnk_09EF25A4[9];

s16 gUnk_0203AC60 EWRAM_COMMON(4);
s32 gUnk_0203AC64 EWRAM_COMMON(4);
s16 gUnk_0203AC68 EWRAM_COMMON(4);
s16 gUnk_0203AC6C EWRAM_COMMON(4);
s32 gUnk_0203AC70 EWRAM_COMMON(4);
u16 gUnk_0203AC74 EWRAM_COMMON(4);
s32 gUnk_0203AC78 EWRAM_COMMON(4);

u8 gBosTmFootIdleFrames[8] = { 2, 1, 0, 1, 2, 3, 4, 3 };

s16 gBosTmFootIdleZ[5] = { -15, -6, 0, 8, 20 };

s16 gUnk_09EF21C2 = 0;

TmFootStep gBosTmFootSteps[3] = {
    { 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } },
    { 0, 6, 0, 1, 0, 6, 0, 1, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } },
    { 0, 9, 0, 0, 0, 9, 0, 0, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } },
};

TmFootStep gUnk_09EF2224 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } };

TmFootStep gBosTmFootThrowSteps[16] = {
    { 0, -8, 0, 3, 0, -8, 0, 3, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } },
    { 0, -12, 0, 4, 0, -12, 0, 4, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } },
    { 0, -8, 0, 5, 0, -8, 0, 5, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } },
    { 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } },
    { 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } },
    { 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } },
    { 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } },
    { 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } },
    { 0, 8, 0, 4, 0, 8, 0, 4, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } },
    { 0, 12, 0, 3, 0, 12, 0, 3, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } },
    { 0, 8, 0, 2, 0, 8, 0, 2, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } },
    { 0, 6, 0, 1, 0, 6, 0, 1, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } },
    { 0, 9, 0, 0, 0, 9, 0, 0, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } },
    { 0, -9, 0, 1, 0, -9, 0, 1, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } },
    { 0, -6, 0, 2, 0, -6, 0, 2, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } },
};

TmFootStep gUnk_09EF2444 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } };

TmFootStep gBosTmFootWalkSteps[10] = {
    { 0, 0, 0, 7, 0, 0, 0, 2, -13, -10, { 0, 0, 0, 0 }, 0, 21, { 0, 0, 0, 0 } },
    { 0, 0, 0, 8, 0, 0, 0, 3, -20, 29, { 0, 0, 0, 0 }, 11, 25, { 0, 0, 0, 0 } },
    { 0, 0, 0, 9, 0, 0, 0, 4, -23, 39, { 0, 0, 0, 0 }, 24, 12, { 0, 0, 0, 0 } },
    { 0, 0, 0, 0, 0, 0, 0, 5, -4, 27, { 0, 0, 0, 0 }, 16, -15, { 0, 0, 0, 0 } },
    { 0, 0, 0, 1, 0, 0, 0, 6, 0, 10, { 0, 0, 0, 0 }, -4, -7, { 0, 0, 0, 0 } },
    { 0, 0, 0, 2, 0, 0, 0, 7, 0, 21, { 0, 0, 0, 0 }, -13, -10, { 0, 0, 0, 0 } },
    { 0, 0, 0, 3, 0, 0, 0, 8, 11, 25, { 0, 0, 0, 0 }, -20, 29, { 0, 0, 0, 0 } },
    { 0, 0, 0, 4, 0, 0, 0, 9, 24, 12, { 0, 0, 0, 0 }, -23, 39, { 0, 0, 0, 0 } },
    { 0, 0, 0, 5, 0, 0, 0, 0, 16, -15, { 0, 0, 0, 0 }, -4, 27, { 0, 0, 0, 0 } },
    { 0, 0, 0, 6, 0, 0, 0, 1, -4, -7, { 0, 0, 0, 0 }, 0, 10, { 0, 0, 0, 0 } },
};

TmFootStep gUnk_09EF25A4[9] = {
    { 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } },
    { 0, 6, 0, 1, 0, 6, 0, 1, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } },
    { 0, 9, 0, 0, 0, 9, 0, 0, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } },
    { 0, -9, 0, 0, 0, -9, 0, 0, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } },
    { 0, -6, 0, 1, 0, -6, 0, 1, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } },
    { 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } },
    { 0, -8, 0, 3, 0, -8, 0, 3, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } },
    { 0, -12, 0, 4, 0, -12, 0, 4, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } },
    { 0, -8, 0, 5, 0, -8, 0, 5, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } },
};

TmFootStep gUnk_09EF26C4 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, { 0, 0, 0, 0 }, 0, 0, { 0, 0, 0, 0 } };

TaskDesc gTaskDescBosTmFoot = {
    "task_bos_tm_foot",
    (TaskInitFunc)task_bos_tm_foot_0,
    (TaskUpdateFunc)task_bos_tm_foot_1,
    (TaskDrawFunc)task_bos_tm_foot_2,
    (TaskDestroyFunc)task_bos_tm_foot_3,
    sizeof(TmFootWork),
};

TaskDesc gTaskDescBosTmClb = {
    "task_bos_tm_clb",
    (TaskInitFunc)task_bos_tm_clb_0,
    (TaskUpdateFunc)task_bos_tm_clb_1,
    (TaskDrawFunc)task_bos_tm_clb_2,
    (TaskDestroyFunc)task_bos_tm_clb_3,
    sizeof(TmClbWork),
};

const TmAnimFrame gUnk_09619CDC[3] = {
    { 10, { 0, 0 }, { 175, 0, 0, 0, 160, 0, 0, 0, 140, 0, 0, 0, 0, 0, 0, 0 } },
    { 10, { 0, 0 }, { 175, 0, 0, 0, 155, 0, 0, 0, 145, 0, 0, 0, 180, 0, 0, 0 } },
    { 10, { 0, 0 }, { 175, 0, 0, 0, 165, 0, 0, 0, 152, 0, 0, 0, 220, 0, 0, 0 } },
};

const TmAnimFrame gUnk_09619D18[3] = {
    { 10, { 0, 0 }, { 80, 0, 0, 0, 102, 0, 0, 0, 95, 0, 0, 0, 160, 0, 0, 0 } },
    { 10, { 0, 0 }, { 90, 0, 0, 0, 128, 0, 0, 0, 220, 0, 0, 0, 240, 0, 0, 0 } },
    { 10, { 0, 0 }, { 76, 0, 0, 0, 128, 0, 0, 0, 160, 0, 0, 0, 224, 0, 0, 0 } },
};

const TmAnimFrame gUnk_09619D54[3] = {
    { 10, { 0, 0 }, { 176, 0, 0, 0, 154, 0, 0, 0, 161, 0, 0, 0, 160, 0, 0, 0 } },
    { 10, { 0, 0 }, { 166, 0, 0, 0, 128, 0, 0, 0, 36, 0, 0, 0, 240, 0, 0, 0 } },
    { 10, { 0, 0 }, { 180, 0, 0, 0, 128, 0, 0, 0, 96, 0, 0, 0, 224, 0, 0, 0 } },
};

const TmAnimFrame gUnk_09619D90[3] = {
    { 10, { 0, 0 }, { 81, 0, 0, 0, 96, 0, 0, 0, 116, 0, 0, 0, 0, 0, 0, 0 } },
    { 10, { 0, 0 }, { 81, 0, 0, 0, 101, 0, 0, 0, 111, 0, 0, 0, 180, 0, 0, 0 } },
    { 10, { 0, 0 }, { 81, 0, 0, 0, 91, 0, 0, 0, 104, 0, 0, 0, 220, 0, 0, 0 } },
};

const TmAnimFrame gUnk_09619DCC[1] = {
    { 5, { 0, 0 }, { 128, 0, 0, 0, 128, 0, 0, 0, 108, 0, 0, 0, 214, 0, 0, 0 } },
};

const TmAnimFrame gUnk_09619DE0[1] = {
    { 5, { 0, 0 }, { 128, 0, 0, 0, 128, 0, 0, 0, 108, 0, 0, 0, 64, 0, 0, 0 } },
};

const TmAnimFrame gUnk_09619DF4[1] = {
    { 5, { 0, 0 }, { 128, 0, 0, 0, 128, 0, 0, 0, 148, 0, 0, 0, 64, 0, 0, 0 } },
};

const TmAnimFrame gUnk_09619E08[1] = {
    { 5, { 0, 0 }, { 128, 0, 0, 0, 128, 0, 0, 0, 148, 0, 0, 0, 214, 0, 0, 0 } },
};

const TmAnimFrame gUnk_09619E1C[3] = {
    { 2, { 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { 2, { 0, 0 }, { 192, 0, 0, 0, 192, 0, 0, 0, 192, 0, 0, 0, 192, 0, 0, 0 } },
    { 250, { 0, 0 }, { 120, 0, 0, 0, 160, 0, 0, 0, 220, 0, 0, 0, 230, 0, 0, 0 } },
};

const TmAnimFrame gUnk_09619E58[3] = {
    { 2, { 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { 2, { 0, 0 }, { 192, 0, 0, 0, 192, 0, 0, 0, 192, 0, 0, 0, 192, 0, 0, 0 } },
    { 250, { 0, 0 }, { 120, 0, 0, 0, 160, 0, 0, 0, 220, 0, 0, 0, 5, 0, 0, 0 } },
};

const TmAnimFrame gUnk_09619E94[3] = {
    { 2, { 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { 2, { 0, 0 }, { 64, 0, 0, 0, 64, 0, 0, 0, 64, 0, 0, 0, 192, 0, 0, 0 } },
    { 250, { 0, 0 }, { 136, 0, 0, 0, 96, 0, 0, 0, 36, 0, 0, 0, 5, 0, 0, 0 } },
};

const TmAnimFrame gUnk_09619ED0[3] = {
    { 2, { 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { 2, { 0, 0 }, { 64, 0, 0, 0, 64, 0, 0, 0, 64, 0, 0, 0, 192, 0, 0, 0 } },
    { 250, { 0, 0 }, { 136, 0, 0, 0, 112, 0, 0, 0, 36, 0, 0, 0, 245, 0, 0, 0 } },
};

const TmAnimFrame gUnk_09619F0C[6] = {
    { 3, { 0, 0 }, { 192, 0, 0, 0, 208, 0, 0, 0, 224, 0, 0, 0, 240, 0, 0, 0 } },
    { 3, { 0, 0 }, { 0, 0, 0, 0, 24, 0, 0, 0, 33, 0, 0, 0, 40, 0, 0, 0 } },
    { 24, { 0, 0 }, { 38, 0, 0, 0, 53, 0, 0, 0, 68, 0, 0, 0, 83, 0, 0, 0 } },
    { 1, { 0, 0 }, { 248, 0, 0, 0, 121, 0, 0, 0, 106, 0, 0, 0, 91, 0, 0, 0 } },
    { 1, { 0, 0 }, { 188, 0, 0, 0, 203, 0, 0, 0, 218, 0, 0, 0, 233, 0, 0, 0 } },
    { 250, { 0, 0 }, { 148, 0, 0, 0, 163, 0, 0, 0, 178, 0, 0, 0, 193, 0, 0, 0 } },
};

const TmAnimFrame gUnk_09619F84[6] = {
    { 3, { 0, 0 }, { 192, 0, 0, 0, 208, 0, 0, 0, 224, 0, 0, 0, 240, 0, 0, 0 } },
    { 3, { 0, 0 }, { 0, 0, 0, 0, 24, 0, 0, 0, 33, 0, 0, 0, 40, 0, 0, 0 } },
    { 24, { 0, 0 }, { 38, 0, 0, 0, 53, 0, 0, 0, 68, 0, 0, 0, 83, 0, 0, 0 } },
    { 1, { 0, 0 }, { 248, 0, 0, 0, 121, 0, 0, 0, 106, 0, 0, 0, 91, 0, 0, 0 } },
    { 1, { 0, 0 }, { 188, 0, 0, 0, 203, 0, 0, 0, 218, 0, 0, 0, 233, 0, 0, 0 } },
    { 250, { 0, 0 }, { 148, 0, 0, 0, 163, 0, 0, 0, 178, 0, 0, 0, 193, 0, 0, 0 } },
};

const TmAnimFrame gUnk_09619FFC[6] = {
    { 3, { 0, 0 }, { 64, 0, 0, 0, 48, 0, 0, 0, 32, 0, 0, 0, 240, 0, 0, 0 } },
    { 3, { 0, 0 }, { 0, 0, 0, 0, 232, 0, 0, 0, 223, 0, 0, 0, 40, 0, 0, 0 } },
    { 24, { 0, 0 }, { 218, 0, 0, 0, 203, 0, 0, 0, 188, 0, 0, 0, 83, 0, 0, 0 } },
    { 1, { 0, 0 }, { 8, 0, 0, 0, 135, 0, 0, 0, 150, 0, 0, 0, 91, 0, 0, 0 } },
    { 1, { 0, 0 }, { 68, 0, 0, 0, 53, 0, 0, 0, 38, 0, 0, 0, 233, 0, 0, 0 } },
    { 250, { 0, 0 }, { 108, 0, 0, 0, 93, 0, 0, 0, 78, 0, 0, 0, 193, 0, 0, 0 } },
};

const TmAnimFrame gUnk_0961A074[6] = {
    { 3, { 0, 0 }, { 64, 0, 0, 0, 48, 0, 0, 0, 32, 0, 0, 0, 240, 0, 0, 0 } },
    { 3, { 0, 0 }, { 0, 0, 0, 0, 232, 0, 0, 0, 223, 0, 0, 0, 40, 0, 0, 0 } },
    { 24, { 0, 0 }, { 218, 0, 0, 0, 203, 0, 0, 0, 188, 0, 0, 0, 83, 0, 0, 0 } },
    { 1, { 0, 0 }, { 8, 0, 0, 0, 135, 0, 0, 0, 150, 0, 0, 0, 91, 0, 0, 0 } },
    { 1, { 0, 0 }, { 68, 0, 0, 0, 53, 0, 0, 0, 38, 0, 0, 0, 233, 0, 0, 0 } },
    { 250, { 0, 0 }, { 108, 0, 0, 0, 93, 0, 0, 0, 78, 0, 0, 0, 193, 0, 0, 0 } },
};

const TmAnimFrame gUnk_0961A0EC[6] = {
    { 3, { 0, 0 }, { 192, 0, 0, 0, 208, 0, 0, 0, 224, 0, 0, 0, 240, 0, 0, 0 } },
    { 3, { 0, 0 }, { 0, 0, 0, 0, 24, 0, 0, 0, 33, 0, 0, 0, 40, 0, 0, 0 } },
    { 39, { 0, 0 }, { 38, 0, 0, 0, 53, 0, 0, 0, 68, 0, 0, 0, 83, 0, 0, 0 } },
    { 1, { 0, 0 }, { 248, 0, 0, 0, 121, 0, 0, 0, 106, 0, 0, 0, 91, 0, 0, 0 } },
    { 1, { 0, 0 }, { 188, 0, 0, 0, 203, 0, 0, 0, 218, 0, 0, 0, 233, 0, 0, 0 } },
    { 250, { 0, 0 }, { 148, 0, 0, 0, 163, 0, 0, 0, 178, 0, 0, 0, 193, 0, 0, 0 } },
};

const TmAnimFrame gUnk_0961A164[6] = {
    { 3, { 0, 0 }, { 192, 0, 0, 0, 208, 0, 0, 0, 224, 0, 0, 0, 240, 0, 0, 0 } },
    { 3, { 0, 0 }, { 0, 0, 0, 0, 24, 0, 0, 0, 33, 0, 0, 0, 40, 0, 0, 0 } },
    { 39, { 0, 0 }, { 38, 0, 0, 0, 53, 0, 0, 0, 68, 0, 0, 0, 83, 0, 0, 0 } },
    { 1, { 0, 0 }, { 248, 0, 0, 0, 121, 0, 0, 0, 106, 0, 0, 0, 91, 0, 0, 0 } },
    { 1, { 0, 0 }, { 188, 0, 0, 0, 203, 0, 0, 0, 218, 0, 0, 0, 233, 0, 0, 0 } },
    { 250, { 0, 0 }, { 148, 0, 0, 0, 163, 0, 0, 0, 178, 0, 0, 0, 193, 0, 0, 0 } },
};

const TmAnimFrame gUnk_0961A1DC[6] = {
    { 3, { 0, 0 }, { 64, 0, 0, 0, 48, 0, 0, 0, 32, 0, 0, 0, 240, 0, 0, 0 } },
    { 3, { 0, 0 }, { 0, 0, 0, 0, 232, 0, 0, 0, 223, 0, 0, 0, 40, 0, 0, 0 } },
    { 39, { 0, 0 }, { 218, 0, 0, 0, 203, 0, 0, 0, 188, 0, 0, 0, 83, 0, 0, 0 } },
    { 1, { 0, 0 }, { 8, 0, 0, 0, 135, 0, 0, 0, 150, 0, 0, 0, 91, 0, 0, 0 } },
    { 1, { 0, 0 }, { 68, 0, 0, 0, 53, 0, 0, 0, 38, 0, 0, 0, 233, 0, 0, 0 } },
    { 250, { 0, 0 }, { 108, 0, 0, 0, 93, 0, 0, 0, 78, 0, 0, 0, 193, 0, 0, 0 } },
};

const TmAnimFrame gUnk_0961A254[6] = {
    { 3, { 0, 0 }, { 64, 0, 0, 0, 48, 0, 0, 0, 32, 0, 0, 0, 240, 0, 0, 0 } },
    { 3, { 0, 0 }, { 0, 0, 0, 0, 232, 0, 0, 0, 223, 0, 0, 0, 40, 0, 0, 0 } },
    { 39, { 0, 0 }, { 218, 0, 0, 0, 203, 0, 0, 0, 188, 0, 0, 0, 83, 0, 0, 0 } },
    { 1, { 0, 0 }, { 8, 0, 0, 0, 135, 0, 0, 0, 150, 0, 0, 0, 91, 0, 0, 0 } },
    { 1, { 0, 0 }, { 68, 0, 0, 0, 53, 0, 0, 0, 38, 0, 0, 0, 233, 0, 0, 0 } },
    { 250, { 0, 0 }, { 108, 0, 0, 0, 93, 0, 0, 0, 78, 0, 0, 0, 193, 0, 0, 0 } },
};

const TmAnimFrame gUnk_0961A2CC[6] = {
    { 10, { 0, 0 }, { 148, 0, 0, 0, 128, 0, 0, 0, 108, 0, 0, 0, 88, 0, 0, 0 } },
    { 15, { 0, 0 }, { 138, 0, 0, 0, 118, 0, 0, 0, 98, 0, 0, 0, 68, 0, 0, 0 } },
    { 10, { 0, 0 }, { 128, 0, 0, 0, 148, 0, 0, 0, 168, 0, 0, 0, 208, 0, 0, 0 } },
    { 10, { 0, 0 }, { 118, 0, 0, 0, 148, 0, 0, 0, 178, 0, 0, 0, 218, 0, 0, 0 } },
    { 15, { 0, 0 }, { 138, 0, 0, 0, 168, 0, 0, 0, 228, 0, 0, 0, 248, 0, 0, 0 } },
    { 10, { 0, 0 }, { 158, 0, 0, 0, 138, 0, 0, 0, 108, 0, 0, 0, 58, 0, 0, 0 } },
};

const TmAnimFrame gUnk_0961A344[6] = {
    { 10, { 0, 0 }, { 108, 0, 0, 0, 138, 0, 0, 0, 168, 0, 0, 0, 208, 0, 0, 0 } },
    { 15, { 0, 0 }, { 138, 0, 0, 0, 158, 0, 0, 0, 198, 0, 0, 0, 238, 0, 0, 0 } },
    { 10, { 0, 0 }, { 168, 0, 0, 0, 148, 0, 0, 0, 98, 0, 0, 0, 48, 0, 0, 0 } },
    { 10, { 0, 0 }, { 148, 0, 0, 0, 128, 0, 0, 0, 78, 0, 0, 0, 28, 0, 0, 0 } },
    { 15, { 0, 0 }, { 138, 0, 0, 0, 108, 0, 0, 0, 48, 0, 0, 0, 3, 0, 0, 0 } },
    { 10, { 0, 0 }, { 128, 0, 0, 0, 148, 0, 0, 0, 168, 0, 0, 0, 208, 0, 0, 0 } },
};

const TmAnimFrame gUnk_0961A3BC[6] = {
    { 10, { 0, 0 }, { 108, 0, 0, 0, 128, 0, 0, 0, 148, 0, 0, 0, 88, 0, 0, 0 } },
    { 15, { 0, 0 }, { 118, 0, 0, 0, 138, 0, 0, 0, 158, 0, 0, 0, 68, 0, 0, 0 } },
    { 10, { 0, 0 }, { 128, 0, 0, 0, 108, 0, 0, 0, 88, 0, 0, 0, 208, 0, 0, 0 } },
    { 10, { 0, 0 }, { 138, 0, 0, 0, 108, 0, 0, 0, 78, 0, 0, 0, 218, 0, 0, 0 } },
    { 15, { 0, 0 }, { 118, 0, 0, 0, 88, 0, 0, 0, 28, 0, 0, 0, 248, 0, 0, 0 } },
    { 10, { 0, 0 }, { 98, 0, 0, 0, 118, 0, 0, 0, 148, 0, 0, 0, 58, 0, 0, 0 } },
};

const TmAnimFrame gUnk_0961A434[6] = {
    { 10, { 0, 0 }, { 148, 0, 0, 0, 118, 0, 0, 0, 88, 0, 0, 0, 208, 0, 0, 0 } },
    { 15, { 0, 0 }, { 118, 0, 0, 0, 98, 0, 0, 0, 58, 0, 0, 0, 238, 0, 0, 0 } },
    { 10, { 0, 0 }, { 88, 0, 0, 0, 108, 0, 0, 0, 158, 0, 0, 0, 48, 0, 0, 0 } },
    { 10, { 0, 0 }, { 108, 0, 0, 0, 128, 0, 0, 0, 178, 0, 0, 0, 28, 0, 0, 0 } },
    { 15, { 0, 0 }, { 118, 0, 0, 0, 148, 0, 0, 0, 208, 0, 0, 0, 3, 0, 0, 0 } },
    { 10, { 0, 0 }, { 128, 0, 0, 0, 108, 0, 0, 0, 88, 0, 0, 0, 208, 0, 0, 0 } },
};

const TmAnimFrame gUnk_0961A4AC[5] = {
    { 20, { 0, 0 }, { 128, 0, 0, 0, 112, 0, 0, 0, 72, 0, 0, 0, 58, 0, 0, 0 } },
    { 1, { 0, 0 }, { 160, 0, 0, 0, 144, 0, 0, 0, 112, 0, 0, 0, 96, 0, 0, 0 } },
    { 1, { 0, 0 }, { 192, 0, 0, 0, 184, 0, 0, 0, 96, 0, 0, 0, 118, 0, 0, 0 } },
    { 1, { 0, 0 }, { 192, 0, 0, 0, 188, 0, 0, 0, 178, 0, 0, 0, 160, 0, 0, 0 } },
    { 20, { 0, 0 }, { 192, 0, 0, 0, 198, 0, 0, 0, 224, 0, 0, 0, 248, 0, 0, 0 } },
};

const TmAnimFrame gUnk_0961A510[5] = {
    { 20, { 0, 0 }, { 128, 0, 0, 0, 112, 0, 0, 0, 72, 0, 0, 0, 58, 0, 0, 0 } },
    { 1, { 0, 0 }, { 160, 0, 0, 0, 144, 0, 0, 0, 112, 0, 0, 0, 96, 0, 0, 0 } },
    { 1, { 0, 0 }, { 192, 0, 0, 0, 168, 0, 0, 0, 96, 0, 0, 0, 118, 0, 0, 0 } },
    { 1, { 0, 0 }, { 192, 0, 0, 0, 188, 0, 0, 0, 178, 0, 0, 0, 160, 0, 0, 0 } },
    { 20, { 0, 0 }, { 192, 0, 0, 0, 198, 0, 0, 0, 224, 0, 0, 0, 248, 0, 0, 0 } },
};

const TmAnimFrame gUnk_0961A574[5] = {
    { 20, { 0, 0 }, { 128, 0, 0, 0, 144, 0, 0, 0, 184, 0, 0, 0, 58, 0, 0, 0 } },
    { 1, { 0, 0 }, { 96, 0, 0, 0, 112, 0, 0, 0, 144, 0, 0, 0, 96, 0, 0, 0 } },
    { 1, { 0, 0 }, { 64, 0, 0, 0, 72, 0, 0, 0, 160, 0, 0, 0, 118, 0, 0, 0 } },
    { 1, { 0, 0 }, { 64, 0, 0, 0, 68, 0, 0, 0, 78, 0, 0, 0, 160, 0, 0, 0 } },
    { 20, { 0, 0 }, { 64, 0, 0, 0, 58, 0, 0, 0, 32, 0, 0, 0, 248, 0, 0, 0 } },
};

const TmAnimFrame gUnk_0961A5D8[5] = {
    { 20, { 0, 0 }, { 128, 0, 0, 0, 144, 0, 0, 0, 184, 0, 0, 0, 58, 0, 0, 0 } },
    { 1, { 0, 0 }, { 96, 0, 0, 0, 112, 0, 0, 0, 144, 0, 0, 0, 96, 0, 0, 0 } },
    { 1, { 0, 0 }, { 64, 0, 0, 0, 88, 0, 0, 0, 160, 0, 0, 0, 118, 0, 0, 0 } },
    { 1, { 0, 0 }, { 64, 0, 0, 0, 68, 0, 0, 0, 78, 0, 0, 0, 160, 0, 0, 0 } },
    { 20, { 0, 0 }, { 64, 0, 0, 0, 58, 0, 0, 0, 32, 0, 0, 0, 248, 0, 0, 0 } },
};

const u16 gBosTmArmSegmentLengths[6] = { 24, 26, 28, 30, 28, 26 };

void BosTmFootInitPart(BtlObj* work, s16 x, s16 y, s16 z, s16 a, s16 b, s32 c, s16 d) {
    work->x = x << 8;
    work->y = y << 8;
    work->z = z << 8;

    if (d >= 6 && d <= 7) {
        ColliderInit(&work->collider, 8, a, b);
        ColliderSetPosition(&work->collider, work->x, work->y, work->z);
    }
}

void BosTmFootSetPartPos(BtlObj* p, s32 a, s32 b, s32 c) {
    p->x = (s16)a << 8;
    p->y = (s16)b << 8;
    p->z = (s16)c << 8;
}

void BosTmFootReleasePart(BtlObj* work) {
    ColliderUnregister(&work->collider);
}

void BosTmFootSyncCollider(BtlObj* sub, TmFootWork* work) {
    ColliderSetPosition(&sub->collider, sub->x, sub->y, sub->z);
}

void BosTmFootResetPose(TmFootWork* work) {
    work->unk_002 = 0;
    work->unk_000 = 0;
    SetObjTileSource(work->tiles2, gUnk_09654C04);
    SetObjTileSource(work->tiles3, gUnk_09654C04);
    work->gfx = gUnk_09EF39DC[2];
    work->gfx2 = gUnk_09EF39DC[2];

    if (work->tm->flags & 0x20) {
        work->body.x = work->tm->baseX + 0x100;
        work->body2.x = work->tm->baseX - 0x600;
        work->body3.x = work->tm->baseX + 0x600;
        work->body4.x = work->tm->baseX - 0x200;
        work->body.y = work->tm->baseY + 0x200;
        work->body2.y = work->tm->baseY - 0x200;
        work->body3.y = work->tm->baseY + 0x500;
        work->body4.y = work->tm->baseY - 0x200;
        work->body.z = work->tm->baseZ - 0x400;
        work->body2.z = work->tm->baseZ - 0x400;
        work->body3.z = work->tm->baseZ + 0x2800;
        work->body4.z = work->tm->baseZ + 0x2B00;
    } else {
        work->body.x = work->tm->baseX + 0x600;
        work->body2.x = work->tm->baseX - 0x100;
        work->body3.x = work->tm->baseX + 0x200;
        work->body4.x = work->tm->baseX - 0x600;
        work->body.y = work->tm->baseY - 0x200;
        work->body2.y = work->tm->baseY + 0x200;
        work->body3.y = work->tm->baseY - 0x500;
        work->body4.y = work->tm->baseY + 0x200;
        work->body.z = work->tm->baseZ - 0x400;
        work->body2.z = work->tm->baseZ - 0x400;
        work->body3.z = work->tm->baseZ + 0x2800;
        work->body4.z = work->tm->baseZ + 0x2B00;
    }
}
void func_080BA2B0(TmFootWork* work) {
    SetObjTileSource(work->tiles2, gUnk_09654C04);
    SetObjTileSource(work->tiles3, gUnk_09654C04);
    work->gfx = gUnk_09EF39DC[0];
    work->gfx2 = gUnk_09EF39DC[0];

    if (work->tm->flags & 0x20) {
        work->body.x = work->tm->baseX + 0x100;
        work->body2.x = work->tm->baseX - 0x600;
        work->body3.x = work->tm->baseX + 0x600;
        work->body4.x = work->tm->baseX - 0x200;
        work->body.y = work->tm->y2 + 0x200;
        work->body2.y = work->tm->y2 - 0x200;
        work->body3.y = work->tm->y2 + 0x500;
        work->body4.y = work->tm->y2 - 0x200;
        work->body.z = work->tm->z2 - 0x400;
        work->body2.z = work->tm->z2 - 0x400;
        work->body3.z = work->tm->z2 + 0x1900;
        work->body4.z = work->tm->z2 + 0x1C00;
    } else {
        work->body.x = work->tm->baseX + 0x600;
        work->body2.x = work->tm->baseX - 0x100;
        work->body3.x = work->tm->baseX + 0x200;
        work->body4.x = work->tm->baseX - 0x600;
        work->body.y = work->tm->y2 - 0x200;
        work->body2.y = work->tm->y2 + 0x200;
        work->body3.y = work->tm->y2 - 0x500;
        work->body4.y = work->tm->y2 + 0x200;
        work->body.z = work->tm->z2 - 0x400;
        work->body2.z = work->tm->z2 - 0x400;
        work->body3.z = work->tm->z2 + 0x1900;
        work->body4.z = work->tm->z2 + 0x1C00;
    }
}

void BosTmFootApplyThrowStep(TmFootWork* work, s16 a) {
    work->gfx = gUnk_09EF39DC[gBosTmFootThrowSteps[a].gfxIndex];
    work->gfx2 = gUnk_09EF39DC[gBosTmFootThrowSteps[a].gfx2Index];
    work->body.z += gBosTmFootThrowSteps[a].dz << 8;
    work->body2.z += gBosTmFootThrowSteps[a].dz2 << 8;
}

void BosTmFootSetWalkPose(TmFootWork* work) {
    work->unk_002 = 0;
    work->unk_000 = 0;
    SetObjTileSource(work->tiles2, gUnk_09658C04);
    SetObjTileSource(work->tiles3, gUnk_09658C04);
    work->gfx = gUnk_09EF3A1C[6];
    work->gfx2 = gUnk_09EF3A1C[1];

    if (work->tm->flags & 0x20) {
        work->body.x = work->tm->x2 + 0x500;
        work->body2.x = work->tm->x2 - 0x600;
        work->body3.x = work->tm->x2 + 0x600;
        work->body4.x = work->tm->x2 - 0x200;
        work->body.y = work->tm->y2 + 0x200;
        work->body2.y = work->tm->y2 - 0x200;
        work->body3.y = work->tm->y2 + 0x500;
        work->body4.y = work->tm->y2 - 0x200;
        work->body.z = work->tm->z2 - 0x400;
        work->body2.z = work->tm->z2 - 0x400;
        work->body3.z = work->tm->z2 + 0x1E00;
        work->body4.z = work->tm->z2 + 0x3200;
    } else {
        work->body.x = work->tm->x2 + 0x200;
        work->body2.x = work->tm->x2 - 0x100;
        work->body3.x = work->tm->x2 + 0x200;
        work->body4.x = work->tm->x2 - 0x600;
        work->body.y = work->tm->y2 - 0x200;
        work->body2.y = work->tm->y2 + 0x200;
        work->body3.y = work->tm->y2 - 0x500;
        work->body4.y = work->tm->y2 + 0x200;
        work->body.z = work->tm->z2 - 0x400;
        work->body2.z = work->tm->z2 - 0x400;
        work->body3.z = work->tm->z2 + 0x1E00;
        work->body4.z = work->tm->z2 + 0x3200;
    }
}
void BosTmFootWalk(TmFootWork* work) {
    if (work->tm->stepTimer != 0) {
        return;
    }

    work->gfx = gUnk_09EF3A1C[gBosTmFootWalkSteps[work->tm->step].gfxIndex];
    work->gfx2 = gUnk_09EF3A1C[gBosTmFootWalkSteps[work->tm->step].gfx2Index];

    if (work->tm->flags & 0x20) {
        work->body3.x = work->tm->x2 + ((gBosTmFootWalkSteps[work->tm->step].x3 + 6) << 8);
        work->body4.x = work->tm->x2 + ((gBosTmFootWalkSteps[work->tm->step].x4 - 2) << 8);
        work->body.x = work->tm->x2 + 0x100;
        work->body2.x = work->tm->x2 - 0x600;
        work->body3.y = work->tm->y2 + 0x500;
        work->body4.y = work->tm->y2 - 0x200;
        work->body.y = work->tm->y2 + 0x200;
        work->body2.y = work->tm->y2 - 0x200;
        work->body3.z = work->tm->z2 + ((gBosTmFootWalkSteps[work->tm->step].z3 + 40) << 8);
        work->body4.z = work->tm->z2 + ((gBosTmFootWalkSteps[work->tm->step].z4 + 43) << 8);
        work->body.z = work->tm->z2 - 0x400;
        work->body2.z = work->tm->z2 - 0x400;
    } else {
        work->body3.x = work->tm->x2 + ((2 - gBosTmFootWalkSteps[work->tm->step].x3) << 8);
        work->body4.x = work->tm->x2 + ((-6 - gBosTmFootWalkSteps[work->tm->step].x4) << 8);
        work->body.x = work->tm->x2 + 0x600;
        work->body2.x = work->tm->x2 - 0x100;
        work->body3.y = work->tm->y2 - 0x500;
        work->body4.y = work->tm->y2 + 0x200;
        work->body.y = work->tm->y2 - 0x200;
        work->body2.y = work->tm->y2 + 0x200;
        work->body3.z = work->tm->z2 + ((gBosTmFootWalkSteps[work->tm->step].z3 + 40) << 8);
        work->body4.z = work->tm->z2 + ((gBosTmFootWalkSteps[work->tm->step].z4 + 43) << 8);
        work->body.z = work->tm->z2 - 0x400;
        work->body2.z = work->tm->z2 - 0x400;
    }

    if (work->tm->step == 2) {
        if (ApplyAttackBox(239, work->body3.x, work->body3.y - 0x500, 0, 20, 16, 20) == 1) {
            m4aSongNumStart(SONG_BTL_MON_HIT03);
        }
    }

    if (work->tm->step == 7) {
        if (ApplyAttackBox(239, work->body4.x, work->body4.y - 0x500, 0, 20, 16, 20) == 1) {
            m4aSongNumStart(SONG_BTL_MON_HIT03);
        }
    }
}

void func_080BA8C8(TmFootWork* work, s16 a) {
    work->gfx = gUnk_09EF39DC[gUnk_09EF25A4[a].gfxIndex];
    work->gfx2 = gUnk_09EF39DC[gUnk_09EF25A4[a].gfx2Index];
    work->body.z += gUnk_09EF25A4[a].dz << 8;
    work->body2.z += gUnk_09EF25A4[a].dz2 << 8;
}

void task_bos_tm_foot_0(TmFootWork* work, TmWork* arg) {
    u16 f;

    work->tiles = LoadObjTiles(gUnk_09652E84, 0x1D80);
    work->tiles2 = AllocObjTiles(0x440, gUnk_09654C04);
    work->tiles3 = AllocObjTiles(0x440, gUnk_09654C04);
    work->palette = LoadObjPalette(gBoss03objPalette, 0x60);
    work->palette2 = LoadObjPalette(gUnk_08F69BC4, 32);
    work->gfx = gUnk_09EF39DC[2];
    work->gfx2 = gUnk_09EF39DC[2];
    work->gfx3 = gUnk_09EF39BC;
    work->gfx4 = gUnk_09EF39C4;
    work->tm = arg;
    work->tm->tileCount += work->tiles2->count + work->tiles3->count;
    work->footFrame = 0;
    work->footFrame2 = 0;
    work->unk_000 = 0;
    work->unk_480 = -0x100;
    work->unk_002 = 0;
    work->unk_130 = 0;
    work->unk_248 = 0;
    work->unk_360 = 0;
    work->unk_478 = 0;
    f = work->tm->flags & 8;

    if (f != 0) {
        BosTmFootSetPartPos(&work->body, (s16)(work->tm->x + 1),
                      (s16)(work->tm->y + 2), (s16)(work->tm->z - 4));
        BosTmFootSetPartPos(&work->body2, (s16)(work->tm->x - 6),
                      (s16)(work->tm->y - 2), (s16)(work->tm->z - 4));
        BosTmFootSetPartPos(&work->body3, (s16)(work->tm->x + 6),
                      (s16)(work->tm->y + 5), (s16)(work->tm->z + 40));
        BosTmFootSetPartPos(&work->body4, (s16)(work->tm->x - 2),
                      (s16)(work->tm->y - 2), (s16)(work->tm->z + 43));
    } else {
        BosTmFootInitPart(&work->body, (s16)(work->tm->x + 1),
                      (s16)(work->tm->y + 2), (s16)(work->tm->z - 4), 4, 32, f,
                      4);
        BosTmFootInitPart(&work->body2, (s16)(work->tm->x - 6),
                      (s16)(work->tm->y - 2), (s16)(work->tm->z - 4), 4, 32, f,
                      5);
        BosTmFootInitPart(&work->body3, (s16)(work->tm->x + 6),
                      (s16)(work->tm->y + 5), (s16)(work->tm->z + 40), 20, 140,
                      f, 6);
        BosTmFootInitPart(&work->body4, (s16)(work->tm->x - 2),
                      (s16)(work->tm->y - 2), (s16)(work->tm->z + 43), 20, 140,
                      f, 7);
    }
}
u8 task_bos_tm_foot_1(TmFootWork* work) {
    u16 n;
    TmFootStep* e;
    TmFootStep* table;

    BosTmFootSyncCollider(&work->body3, work);
    BosTmFootSyncCollider(&work->body4, work);

    switch (work->tm->state) {
    case 0:
    case 15:
        if (work->tm->stateTimer != 0) {
            if (work->tm->stepTimer != 0) {
                break;
            }

            work->footFrame = gBosTmFootIdleFrames[(s16)work->tm->step];
            work->footFrame2 = gBosTmFootIdleFrames[((s16)work->tm->step + 4) & 7];
            work->gfx = gUnk_09EF39DC[(s8)work->footFrame];
            work->gfx2 = gUnk_09EF39DC[(s8)work->footFrame2];
            work->body3.z =
                work->tm->z2 + ((gBosTmFootIdleZ[(s8)work->footFrame] + 40) << 8);
            work->body4.z =
                work->tm->z2 + ((gBosTmFootIdleZ[(s8)work->footFrame2] + 43) << 8);
            work->body.z = work->tm->z2 - 0x400;
            work->body2.z = work->tm->z2 - 0x400;
        } else {
            BosTmFootResetPose(work);
        }
        break;
    case 4:
    case 5:
    case 6:
    case 7:
        if (work->tm->stateTimer != 0) {
            BosTmFootWalk(work);
        } else {
            BosTmFootSetWalkPose(work);
        }
        break;
    case 1:
    case 10:
        if (work->tm->stateTimer == 0) {
            BosTmFootResetPose(work);
        }
        break;
    case 2:
    case 3:
        if (work->tm->stateTimer != 0) {
            n = work->tm->step;

            if ((s16)work->tm->step <= 3) {
                BosTmFootApplyThrowStep(work, (s16)work->tm->step);
            } else if (n >= 66 && n <= 74) {
                n -= 62;
                BosTmFootApplyThrowStep(work, (s16)n);
            } else if (n >= 98 && n <= 100) {
                n -= 85;
                BosTmFootApplyThrowStep(work, (s16)n);
            } else {
                break;
            }

        } else {
            BosTmFootResetPose(work);
        }
        break;
    case 11:
        if (work->tm->stateTimer != 0) {
            n = work->tm->step;

            if ((s16)work->tm->step <= 3) {
                BosTmFootApplyThrowStep(work, (s16)work->tm->step);
            } else if (n >= 96 && n <= 104) {
                n -= 92;
                BosTmFootApplyThrowStep(work, (s16)n);
            } else if (n >= 128 && n <= 130) {
                n -= 115;
                BosTmFootApplyThrowStep(work, (s16)n);
            } else {
                break;
            }

        } else {
            BosTmFootResetPose(work);
        }
        break;
    case 9:
        if (work->tm->stateTimer != 0) {
            n = work->tm->step;

            if ((s16)work->tm->step <= 2) {
                func_080BA8C8(work, (s16)work->tm->step);
            } else if (n >= 41 && n <= 46) {
                n -= 38;
                func_080BA8C8(work, (s16)n);
            } else {
                break;
            }

        } else {
            BosTmFootResetPose(work);
        }
        break;
    case 12:
        if (work->tm->hitCount == 1) {
            work->unk_002 = 0;
            work->unk_000 = 0;
            work->gfx = gUnk_09EF39DC[1];
            work->gfx2 = gUnk_09EF39DC[1];
            work->body.z = work->tm->baseZ +
                            ((gBosTmFootSteps[(s16)work->tm->step].dz - 4) << 8);
            work->body2.z = work->tm->baseZ +
                            ((gBosTmFootSteps[(s16)work->tm->step].dz2 - 4) << 8);
            work->body3.z = work->tm->baseZ + 0x2800;
            work->body4.z = work->tm->baseZ + 0x2800;
            break;
        }

        if ((s16)work->tm->step <= 2) {
            work->gfx = gUnk_09EF39DC[gBosTmFootSteps[(s16)work->tm->step].gfxIndex];
            work->gfx2 = gUnk_09EF39DC[gBosTmFootSteps[(s16)work->tm->step].gfx2Index];
            work->body.z += gBosTmFootSteps[(s16)work->tm->step].dz << 8;
            work->body2.z += gBosTmFootSteps[(s16)work->tm->step].dz2 << 8;
        }

        if (work->tm->hurtTimer <= 2) {
            work->gfx =
                gUnk_09EF39DC[(table = gBosTmFootSteps, e = &table[work->tm->hurtTimer])->gfxIndex + 1];
            work->gfx2 = gUnk_09EF39DC[e->gfx2Index + 1];
            work->body.z -= e->dz << 8;
            work->body2.z -= e->dz2 << 8;
        }
        break;
    case 14:
        if (work->tm->stateTimer == 0) {
            func_080BA2B0(work);
        } else if (work->tm->stateTimer > 59) {
            if (work->tm->flags & 0x40) {
                BosTmFootSetWalkPose(work);
            } else {
                BosTmFootResetPose(work);
            }
        }
        break;
    case 13:
        if ((s16)work->tm->step == 0) {
            func_080BA2B0(work);
        }
        break;
    case 8:
    case 16:
    case 17:
    default:
        break;
    }

    return 1;
}
void task_bos_tm_foot_2(TmFootWork* work) {
    void* pal;
    s32 flag;
    s16 x;
    s16 y;
    BtlObj* s0;
    BtlObj* s1;
    BtlObj* s2;
    BtlObj* s3;
    u16 mode;

    flag = work->tm->flags & 0x20;
    mode = 0x801;
    if (flag != 0) {
        mode = 0x800;
    }

    if (gBtlWork->paused != 0) {
        pal = work->palette;
    } else if ((work->tm->flags & 1) && (gFrameCounter & 1)) {
        pal = work->palette2;
    } else {
        pal = work->palette;
    }

    s0 = &work->body;
    s1 = &work->body2;
    s2 = &work->body3;
    s3 = &work->body4;
    WorldToScreen(&x, &y, s0->x, s0->y, s0->z);
    DrawSprite(x, y, work->gfx, work->tiles2, pal, 0, mode, (u16)(-4100 - (s0->y >> 8) * 4));
    WorldToScreen(&x, &y, s1->x, s1->y, s1->z);
    DrawSprite(x, y, work->gfx2, work->tiles3, pal, 0, mode, (u16)(-4100 - (s1->y >> 8) * 4));
    WorldToScreen(&x, &y, s2->x, s2->y, s2->z);
    DrawSprite(x, y, work->gfx3, work->tiles, pal, 0, mode, (u16)(-4100 - (s2->y >> 8) * 4));
    WorldToScreen(&x, &y, s3->x, s3->y, s3->z);
    DrawSprite(x, y, work->gfx4, work->tiles, pal, 0, mode, (u16)(-4100 - (s3->y >> 8) * 4));
}

void task_bos_tm_foot_3(TmFootWork* work) {
    if ((work->tm->flags & 8) == 0) {
        BosTmFootReleasePart(&work->body3);
        BosTmFootReleasePart(&work->body4);
    }

    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ReleaseObjPalette(work->palette2);
}

void CreateBosTmClbTask(TaskPool* pool, TmClbArg* p, TmArmPos* a) {
    p->src = a;
    p->moveMode = 0;
    p->spinMode = 1;
    p->vz = 0;
    TaskCreate(pool, &gTaskDescBosTmClb, p);
}

void BosTmClbThrow(TmClbArg* p, TmArmPos* a, s32 b) {
    p->src = a;
    p->vz = b;
    p->moveMode = 4;
    p->spinMode = 0;
}

void BosTmClbHoldSpinning(TmClbArg* p, TmArmPos* a) {
    p->src = a;
    p->vz = 0;
    p->moveMode = 0;
    p->spinMode = 0;
}

void BosTmClbHold(TmClbArg* p, TmArmPos* a, u8 mode) {
    p->src = a;
    p->vz = 0;
    p->spinMode = 2;

    switch (mode) {
    case 0:
        p->moveMode = 1;
        break;
    case 1:
        p->moveMode = 1;
        break;
    case 2:
        p->moveMode = 2;
        break;
    case 3:
        p->moveMode = 3;
        break;
    }
}

void task_bos_tm_clb_0(TmClbWork* work, TmClbArg* arg) {
    TmArmPos* p;

    work->tiles = LoadObjTiles(gUnk_09652E84, 0x1D80);
    work->palette = LoadObjPalette(gBoss03objPalette, 0x60);
    work->arg = arg;
    p = arg->src;
    work->angle = p->angle;
    work->x = p->x;
    work->y = p->y;
    work->z = p->z;
}

u8 task_bos_tm_clb_1(TmClbWork* work) {
    TmClbArg* a = work->arg;

    switch (a->moveMode) {
    case 4:
        work->x += (a->src->x - work->x) >> 4;
        work->y = a->src->y;
        work->z += a->vz;
        a->vz += 51;

        if (a->vz > 0 && work->z >= a->src->z) {
            work->z = a->src->z;
            a->moveMode = 0;
            a->spinMode = 1;
        }

        break;
    case 0:
        work->x = a->src->x;
        work->y = a->src->y;
        work->z = a->src->z;
        break;
    case 1:
        work->x = a->src->x;
        work->y = a->src->y;
        work->z = a->src->z;
        break;
    case 2:
        work->x = a->src->x - 0x600;
        work->y = a->src->y;
        work->z = a->src->z;
        break;
    case 3:
        work->x = a->src->x + 0x600;
        work->y = a->src->y;
        work->z = a->src->z - 0x500;
        break;
    }

    switch (a->spinMode) {
    case 0:
        work->angle += 0x10;
        break;
    case 1:
        ApproachAngle(&work->angle, a->src->angle, 2);
        break;
    case 2:
        work->angle = a->src->angle;
        break;
    }

    return 1;
}
void task_bos_tm_clb_2(TmClbWork* work) {
    ObjAffine* p;
    s16 x;
    s16 y;

    p = AllocObjAffineAngle(work->angle, 0);
    WorldToScreen(&x, &y, work->x, work->y, work->z);
    DrawSprite(x, y, gUnk_0962E838, work->tiles, work->palette, p, 0x800,
               (u16)(-0x1002 - (work->y >> 8) * 4));
    // @bug AllocObjAffineAngle returns NULL at angle 0 (NULL write).
    p->doubleSize = 1;
    DrawSprite(x, y, work->arg->gfx, work->arg->tiles, work->palette, p, 0x800,
               (u16)(-0x1003 - (work->y >> 8) * 4));
}

void task_bos_tm_clb_3(TmClbWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void BosTmArmSetTargetAngles(TmArmJoint* joints, const u8* src) {
    s32 i;

    i = 3;

    do {
        joints->targetAngle = *src;
        src += 4;
        joints++;
    } while (--i >= 0);
}

void BosTmArmStartJointAnim(TmAnim* anim, const TmAnimFrame* src, u16 a, TmArmJoint* joints) {
    if (anim->frames != src) {
        anim->frames = src;
        anim->timer = 0;
        anim->frame = 0;
        anim->frameCount = a;
        BosTmArmSetTargetAngles(joints, src->angles);
    }
}

void BosTmArmUpdateArm1Tip(TmArmWork* work) {
    TmArmJoint* s = &work->joints.all[7];
    TmArmPos* d = &work->tips[0];

    d->x = s->curX + gSineTable[s->angle] * 12 + work->src->x;
    d->z = s->curY + -gSineTable[s->angle + 0x40] * 12 + work->src->z;
    d->y = work->src->y;
}
void BosTmArmUpdateArm0Tip(TmArmWork* work) {
    TmArmJoint* s = &work->joints.all[3];
    TmArmPos* d = &work->tips[1];

    d->x = s->curX + gSineTable[s->angle] * 12 + work->src->x2;
    d->z = s->curY + -gSineTable[s->angle + 0x40] * 12 + work->src->z2;
    d->y = work->src->y2;
}

void BosTmArmComputeJointPositions(TmArmJoint* joints) {
    s32 x;
    s32 y;
    s32 i;
    s32 n;
    TmArmJoint* p;

    x = 0;
    y = 0;

    for (i = 0; i < 3; i++) {
        p = &joints[i];
        p->x = x;
        p->y = y;
        x += gSineTable[p->angle] * gBosTmArmSegmentLengths[n = p->anim.frame];
        y += -gSineTable[p->angle + 0x40] * gBosTmArmSegmentLengths[n = p->anim.frame];
    }

    p = &joints[n = 3];
    p->x = x;
    p->y = y;
}
void BosTmArmUpdateJoints(TmArmJoint* joints, u16 a) {
    s32 i;
    u8* q;
    TmArmJoint* p;

    for (i = 0; i < 4; i++) {
        p = &joints[i];

        q = &p->angle;
        ApproachAngle(q, p->targetAngle, a);
    }

    BosTmArmComputeJointPositions(joints);

    for (i = 0; i < 4; i++) {
        p = &joints[i];

        p->curX += (p->x - p->curX) >> 1;
        p->curY += (p->y - p->curY) >> 1;
    }
}

void BosTmArmStepJointAnim(TmArmJoint* joints, TmAnim* a) {
    if (a->timer >= a->frames[a->frame].duration) {
        a->timer = 0;
        a->frame++;

        if (a->frame >= a->frameCount) {
            a->frame = 0;
        }

        BosTmArmSetTargetAngles(joints, a->frames[a->frame].angles);
    }

    a->timer++;
    BosTmArmUpdateJoints(joints, 1);
}

void task_bos_tm_arm_0(TmArmWork* work, TmArmSrc* arg) {
    s32 i;
    void* gfx;
    TmArmJoint* a;
    TmArmJoint* b;
    TmArmJoint* p;
    TmArmJoint* q;

    work->src = arg;
    work->tiles = LoadObjTiles(gUnk_09652E84, 0x1D80);
    work->palette = LoadObjPalette(gBoss03objPalette, 0x60);
    work->palette2 = LoadObjPalette(gUnk_08F69BC4, 32);
    work->timer = 0;
    work->timer2 = 0;
    work->clbSwapped = 1;
    work->prevState = 0;
    work->jointAnim2.frames = 0;
    work->jointAnim.frames = 0;
    BosTmArmStartJointAnim(&work->jointAnim2, gUnk_09619CDC, 3, work->joints.arms[0]);
    BosTmArmStartJointAnim(&work->jointAnim, gUnk_09619D18, 3, &work->joints.arms[1][0]);

    for (i = 0; i < 4; i++) {
        p = &work->joints.arms[0][i];
        q = &work->joints.arms[1][i];
        *(u16*)&p->angle = p->targetAngle;
        *(u16*)&q->angle = q->targetAngle;
    }

    a = work->joints.arms[0];
    BosTmArmComputeJointPositions(a);
    b = &work->joints.arms[1][0];
    BosTmArmComputeJointPositions(b);

    for (i = 0; i < 4; i++) {
        work->joints.arms[0][i].curX = work->joints.arms[0][i].x;
        work->joints.arms[0][i].curY = work->joints.arms[0][i].y;
        work->joints.arms[1][i].curX = work->joints.arms[1][i].x;
        work->joints.arms[1][i].curY = work->joints.arms[1][i].y;
    }

    BosTmArmUpdateArm1Tip(work);
    BosTmArmUpdateArm0Tip(work);
    work->tips[0].angle = 272;
    work->tips[1].angle = 240;

    for (i = 0; i < 3; i++) {
        AnimInit(&work->joints.arms[0][i].anim, gUnk_09EF39B4, gUnk_09EF39A0);
        AnimStart(&work->joints.arms[0][i].anim, 0, 1);
        work->joints.arms[0][i].anim.frame = i * 2;
        work->joints.arms[0][i].gfx = AnimGetGfx(&work->joints.arms[0][i].anim);
        AnimInit(&work->joints.arms[1][i].anim, gUnk_09EF39B4, gUnk_09EF39A0);
        AnimStart(&work->joints.arms[1][i].anim, 0, 1);
        work->joints.arms[1][i].anim.frame = i * 2;
        work->joints.arms[1][i].gfx = AnimGetGfx(&work->joints.arms[1][i].anim);
    }

    work->joints.arms[0][3].gfx = gUnk_0962E7A0;
    work->joints.arms[1][3].gfx = gUnk_0962E7A0;
    work->tiles2 = AllocObjTiles(0x140, gUnk_09657C04);
    work->src->tm->tileCount += work->tiles2->count;
    AnimInit(&work->anim, gUnk_09EF3A18, gUnk_09EF39F8);
    AnimStart(&work->anim, 0, 1);
    work->clb.tiles = work->tiles2;
    work->clb2.tiles = work->tiles2;
    gfx = AnimGetGfx(&work->anim);
    work->clb.gfx = gfx;
    work->clb2.gfx = gfx;
    work->paletteStep = 0;
    TaskPoolInit(&work->tasks, 2);
    CreateBosTmClbTask(&work->tasks, &work->clb, &work->tips[0]);
    CreateBosTmClbTask(&work->tasks, &work->clb2, &work->tips[1]);
    gUnk_0203AC74 = 0;
    gUnk_0203AC64 = 0;
    gUnk_0203AC78 = 0;
    gUnk_0203AC70 = 0;
    gUnk_0203AC60 = 0;
    gUnk_0203AC6C = 0;
    gUnk_0203AC68 = 0;
}
void BosTmArmUpdateArm1(TmArmWork* work) {
    TmArmJoint* j;
    TmArmJoint* j2;
    s32 i;
    s32 r;
    s32 x;
    s32 y;
    s32 z;
    s32 x2;
    s32 y2;
    s32 z2;
    u8 v;

    switch (work->src->tm->state) {
    case 0:
    case 15:
        if (work->timer == 0) {
            work->tips[0].angle = 0x110;

            if (work->src->tm->flags & 0x20) {
                BosTmArmStartJointAnim(&work->jointAnim, gUnk_09619D18, 3, &work->joints.all[4]);
            } else {
                BosTmArmStartJointAnim(&work->jointAnim, gUnk_09619D90, 3, &work->joints.all[4]);
            }
        }

        switch (work->timer % 30) {
        case 0:
            v = 0;

            if (work->clbSwapped == 0) {
                v = 1;
            }

            work->clbSwapped = v;
            break;
        case 22:
            if (work->clbSwapped != 0) {
                BosTmClbThrow(&work->clb, &work->tips[0], -0x380);
            } else {
                BosTmClbThrow(&work->clb2, &work->tips[0], -0x380);
            }
            break;
        }

        work->timer++;
        break;
    case 4:
    case 5:
    case 6:
    case 7:
        if (work->timer == 0) {
            work->tips[0].angle = 0x110;
            BosTmClbHoldSpinning(&work->clb, &work->tips[0]);

            if (work->src->tm->flags & 0x20) {
                BosTmArmStartJointAnim(&work->jointAnim, gUnk_0961A2CC, 6, &work->joints.all[4]);
            } else {
                BosTmArmStartJointAnim(&work->jointAnim, gUnk_0961A3BC, 6, &work->joints.all[4]);
            }
        }

        work->timer++;
        break;
    case 12:
    case 14:
        if (work->timer == 0) {
            work->tips[0].angle = 90;
            BosTmClbThrow(&work->clb, &work->tips[0], -128);

            if (work->src->tm->flags & 0x20) {
                BosTmArmStartJointAnim(&work->jointAnim, gUnk_09619DE0, 1, &work->joints.all[4]);
            } else {
                BosTmArmStartJointAnim(&work->jointAnim, gUnk_09619E08, 1, &work->joints.all[4]);
            }
        }

        work->timer++;
        break;
    case 13:
        if (work->timer == 0) {
            work->tips[0].angle = 90;
            BosTmClbThrow(&work->clb, &work->tips[0], -128);

            if (work->src->tm->flags & 0x20) {
                BosTmArmStartJointAnim(&work->jointAnim, gUnk_09619DE0, 1, &work->joints.all[4]);
            } else {
                BosTmArmStartJointAnim(&work->jointAnim, gUnk_09619E08, 1, &work->joints.all[4]);
            }
        }

        work->timer++;
        break;
    case 1:
        if (work->timer == 0) {
            if (work->src->tm->flags & 0x20) {
                BosTmArmStartJointAnim(&work->jointAnim, gUnk_09619E1C, 3, &work->joints.all[4]);
                work->tips[0].angle = 0xE8;
                BosTmClbHold(&work->clb, &work->tips[0], 0);
            } else {
                BosTmArmStartJointAnim(&work->jointAnim, gUnk_09619E94, 3, &work->joints.all[4]);
                work->tips[0].angle = 0xF4;
                BosTmClbHold(&work->clb, &work->tips[0], 2);
            }
        }

        if (work->timer == 45) {
            j = &work->joints.all[3];
            y = work->src->y2;
            z = work->src->z2 + j->curY - 0x2300;

            if (work->src->tm->flags & 0x20) {
                x = work->src->x2 + j->curX - 0x3E00;
                BgFxStartFireAtPlayer(x, y, z, 1, 0, 168, 20);
            } else {
                x = work->src->x2 + j->curX + 0x4800;
                BgFxStartFireAtPlayer(x, y, z, 0, 0, 168, 20);
            }
        } else if (work->timer > 55) {
            if (BgFxIsActive() == 0) {
                work->tips[0].angle = 0x110;
                work->src->tm->flags |= 2;
            }
        }

        work->timer++;
        break;
    case 10:
        if (work->timer == 0) {
            if (work->src->tm->flags & 0x20) {
                BosTmArmStartJointAnim(&work->jointAnim, gUnk_09619E1C, 3, &work->joints.all[4]);
                work->tips[0].angle = 0xE8;
                BosTmClbHold(&work->clb, &work->tips[0], 0);
            } else {
                BosTmArmStartJointAnim(&work->jointAnim, gUnk_09619E94, 3, &work->joints.all[4]);
                work->tips[0].angle = 0xF4;
                BosTmClbHold(&work->clb, &work->tips[0], 2);
            }
        }

        if (work->timer == 30) {
            j = &work->joints.all[3];
            y = work->src->y2;
            z = work->src->z2 + j->curY - 0x2300;

            if (work->src->tm->flags & 0x20) {
                x = work->src->x2 + j->curX - 0x3E00;
                BgFxStartFireAtPlayer(x, y, z, 1, 0, 168, 18);
            } else {
                x = work->src->x2 + j->curX + 0x4800;
                BgFxStartFireAtPlayer(x, y, z, 0, 0, 168, 18);
            }
        } else if (work->timer > 70) {
            if (BgFxIsActive() == 0) {
                work->tips[0].angle = 0x110;
                work->src->tm->flags |= 2;
            }
        } else if (work->timer > 50) {
            v = BgFxIsActive();
            if (v == 0) {
                j2 = &work->joints.all[3];
                y2 = work->src->y2;
                z2 = work->src->z2 + j2->curY - 0x2300;

                if (work->src->tm->flags & 0x20) {
                    x2 = work->src->x2 + j2->curX - 0x3E00;
                    BgFxStartFireAtPlayer(x2, y2, z2, 1, 0, 168, 18);
                } else {
                    x2 = work->src->x2 + j2->curX + 0x4800;
                    BgFxStartFireAtPlayer(x2, y2, z2, 0, 0, 168, 18);
                }
            }
        }

        work->timer++;
        break;
    case 2:
        if (work->timer == 0) {
            if (work->src->tm->flags & 0x20) {
                BosTmArmStartJointAnim(&work->jointAnim, gUnk_09619F0C, 6, &work->joints.all[4]);
            } else {
                BosTmArmStartJointAnim(&work->jointAnim, gUnk_09619FFC, 6, &work->joints.all[4]);
            }

            BosTmClbThrow(&work->clb, &work->tips[0], -0xB00);
            work->tips[0].angle = 0xE8;
        }

        if (work->timer == 35) {
            work->tips[0].angle = 0x110;
            work->src->tm->tableState = 1;

            if (work->src->tm->flags & 0x20) {
                r = ApplyAttackBox(237, work->tips[1].x - 0x1000, work->tips[1].y,
                                  work->tips[1].z + 0x1400, 16, 16, 16);
            } else {
                r = ApplyAttackBox(237, work->tips[1].x + 0x2800, work->tips[1].y,
                                  work->tips[1].z + 0x1400, 16, 16, 16);
            }

            if (r == 1) {
                m4aSongNumStart(SONG_BTL_MON_HIT03);
            }

            m4aSongNumStart(SONG_BTL_LB_RUMB);
        }

        if (work->timer > 50) {
            work->src->tm->flags |= 2;
        } else {
            work->timer++;
        }
        break;
    case 3:
        if (work->timer == 0) {
            if (work->src->tm->flags & 0x20) {
                BosTmArmStartJointAnim(&work->jointAnim, gUnk_09619F0C, 6, &work->joints.all[4]);
            } else {
                BosTmArmStartJointAnim(&work->jointAnim, gUnk_09619FFC, 6, &work->joints.all[4]);
            }

            BosTmClbThrow(&work->clb, &work->tips[0], -0xB00);
            work->tips[0].angle = 0xE8;
        }

        if (work->timer == 35) {
            work->tips[0].angle = 0x110;
        }

        if (work->timer == 37) {
            gUnk_0203AC64 = gBtlWork->viewX;
            gUnk_0203AC78 = gBtlWork->viewY;
            gUnk_0203AC60 = gUnk_0203AC64 >> 8;
            gUnk_0203AC6C = gUnk_0203AC78 >> 8;

            if (work->src->tm->flags & 0x20) {
                BgFxStartGroundImpact(0x10D00, 0x15800);
            } else {
                BgFxStartGroundImpact(0xF000, 0x15800);
            }

            BtlMapStartShake();
            m4aSongNumStart(SONG_BTL_LB_RUMB);
            ApplyAttackBox(238, gBtlWork->viewX, gBtlWork->viewY, 0, 320, 240, 1);
            gUnk_0203AC64 = gBtlWork->viewX;
            gUnk_0203AC78 = gBtlWork->viewY;
            gUnk_0203AC60 = gUnk_0203AC64 >> 8;
            gUnk_0203AC6C = gUnk_0203AC78 >> 8;
        }

        if (work->timer > 50) {
            work->src->tm->flags |= 2;
        } else {
            work->timer++;
        }
        break;
    case 11:
        if (work->timer == 0) {
            if (work->src->tm->flags & 0x20) {
                BosTmArmStartJointAnim(&work->jointAnim, gUnk_0961A0EC, 6, &work->joints.all[4]);
            } else {
                BosTmArmStartJointAnim(&work->jointAnim, gUnk_0961A1DC, 6, &work->joints.all[4]);
            }

            BosTmClbThrow(&work->clb, &work->tips[0], -0xB00);
            work->tips[0].angle = 0xE8;
        }

        if (work->timer == 50) {
            work->tips[0].angle = 0x110;
        }

        if (work->timer == 52) {
            gUnk_0203AC64 = gBtlWork->viewX;
            gUnk_0203AC78 = gBtlWork->viewY;
            gUnk_0203AC60 = gUnk_0203AC64 >> 8;
            gUnk_0203AC6C = gUnk_0203AC78 >> 8;

            if (work->src->tm->flags & 0x20) {
                BgFxStartGroundImpact(0x10D00, 0x15800);
            } else {
                BgFxStartGroundImpact(0xF000, 0x15800);
            }

            BtlMapStartShake();
            m4aSongNumStart(SONG_BTL_LB_RUMB);
            ApplyAttackBox(238, gBtlWork->viewX, gBtlWork->viewY, 0, 320, 240, 1);
            gUnk_0203AC64 = gBtlWork->viewX;
            gUnk_0203AC78 = gBtlWork->viewY;
            gUnk_0203AC60 = gUnk_0203AC64 >> 8;
            gUnk_0203AC6C = gUnk_0203AC78 >> 8;
        }

        if (work->timer > 65) {
            work->src->tm->flags |= 2;
        } else {
            work->timer++;
        }
        break;
    case 9:
        if (work->timer == 0) {
            work->tips[0].angle = 0x10C;
            BosTmClbHoldSpinning(&work->clb, &work->tips[0]);

            if (work->src->tm->flags & 0x20) {
                BosTmArmStartJointAnim(&work->jointAnim, gUnk_0961A4AC, 5, &work->joints.all[4]);
            } else {
                BosTmArmStartJointAnim(&work->jointAnim, gUnk_0961A574, 5, &work->joints.all[4]);
            }
        }

        if (work->timer == 21) {
            if (ApplyAttackBox(240, work->src->tm->baseX, work->src->tm->baseY,
                              work->tips[1].z, 36, 32, 32) == 1) {
                m4aSongNumStart(SONG_BTL_MON_HIT03);
            }
        }

        if (work->timer > 33) {
            work->src->tm->flags |= 2;
        } else {
            work->timer++;
        }

        gUnk_0203AC74 = work->timer;
        break;
    case 17:
        return;
    }

    BosTmArmStepJointAnim(&work->joints.all[4], &work->jointAnim);
    BosTmArmUpdateArm1Tip(work);

    for (i = 0; i < 3; i++) {
        work->joints.arms[1][i].gfx = AnimUpdate(&work->joints.arms[1][i].anim);
    }
}

void BosTmArmUpdateArm0(TmArmWork* work) {
    s32 i;

    switch (work->src->tm->state) {
    case 0:
    case 15:
        if (work->timer2 == 0) {
            work->tips[1].angle = 0x110;

            if (work->src->tm->flags & 0x20) {
                BosTmArmStartJointAnim(&work->jointAnim2, gUnk_09619CDC, 3, work->joints.all);
            } else {
                BosTmArmStartJointAnim(&work->jointAnim2, gUnk_09619D54, 3, work->joints.all);
            }
        }

        if (work->timer2 % 30 == 12) {
            if (work->clbSwapped != 0) {
                BosTmClbThrow(&work->clb2, &work->tips[1], -0x600);
            } else {
                BosTmClbThrow(&work->clb, &work->tips[1], -0x600);
            }
        }

        work->timer2++;
        break;
    case 4:
    case 5:
    case 6:
    case 7:
        if (work->timer2 == 0) {
            work->tips[1].angle = 0x110;
            BosTmClbHoldSpinning(&work->clb2, &work->tips[1]);

            if (work->src->tm->flags & 0x20) {
                BosTmArmStartJointAnim(&work->jointAnim2, gUnk_0961A344, 6, work->joints.all);
            } else {
                BosTmArmStartJointAnim(&work->jointAnim2, gUnk_0961A434, 6, work->joints.all);
            }
        }

        work->timer2++;
        break;
    case 12:
    case 14:
        if (work->timer2 == 0) {
            work->tips[1].angle = 185;
            BosTmClbThrow(&work->clb2, &work->tips[1], -128);

            if (work->src->tm->flags & 0x20) {
                BosTmArmStartJointAnim(&work->jointAnim2, gUnk_09619DCC, 1, work->joints.all);
            } else {
                BosTmArmStartJointAnim(&work->jointAnim2, gUnk_09619DF4, 1, work->joints.all);
            }
        }

        work->timer2++;
        break;
    case 13:
        if (work->timer2 == 0) {
            work->tips[1].angle = 185;
            BosTmClbThrow(&work->clb2, &work->tips[1], -128);

            if (work->src->tm->flags & 0x20) {
                BosTmArmStartJointAnim(&work->jointAnim2, gUnk_09619DCC, 1, work->joints.all);
            } else {
                BosTmArmStartJointAnim(&work->jointAnim2, gUnk_09619DF4, 1, work->joints.all);
            }
        }

        work->timer2++;
        break;
    case 1:
        if (work->timer2 == 0) {
            if (work->src->tm->flags & 0x20) {
                BosTmArmStartJointAnim(&work->jointAnim2, gUnk_09619E58, 3, work->joints.all);
                work->tips[1].angle = 0x10C;
                BosTmClbHold(&work->clb2, &work->tips[1], 1);
            } else {
                BosTmArmStartJointAnim(&work->jointAnim2, gUnk_09619ED0, 3, work->joints.all);
                work->tips[1].angle = 0x118;
                BosTmClbHold(&work->clb2, &work->tips[1], 3);
            }
        }

        if (work->timer2 > 55) {
            if (BgFxIsActive() == 0) {
                work->tips[1].angle = 240;
            }
        }

        work->timer2++;
        break;
    case 10:
        if (work->timer2 == 0) {
            if (work->src->tm->flags & 0x20) {
                BosTmArmStartJointAnim(&work->jointAnim2, gUnk_09619E58, 3, work->joints.all);
                work->tips[1].angle = 0x10C;
                BosTmClbHold(&work->clb2, &work->tips[1], 1);
            } else {
                BosTmArmStartJointAnim(&work->jointAnim2, gUnk_09619ED0, 3, work->joints.all);
                work->tips[1].angle = 0x118;
                BosTmClbHold(&work->clb2, &work->tips[1], 3);
            }
        }

        if (work->timer2 > 70) {
            if (BgFxIsActive() == 0) {
                work->tips[1].angle = 240;
            }
        }

        work->timer2++;
        break;
    case 2:
        if (work->timer2 == 0) {
            if (work->src->tm->flags & 0x20) {
                BosTmArmStartJointAnim(&work->jointAnim2, gUnk_09619F84, 6, work->joints.all);
            } else {
                BosTmArmStartJointAnim(&work->jointAnim2, gUnk_0961A074, 6, work->joints.all);
            }

            BosTmClbThrow(&work->clb2, &work->tips[1], -0xB00);
            work->tips[1].angle = 0x10C;
        }

        if (work->timer2 == 35) {
            work->tips[1].angle = 240;
        }

        work->timer2++;
        break;
    case 3:
        if (work->timer2 == 0) {
            if (work->src->tm->flags & 0x20) {
                BosTmArmStartJointAnim(&work->jointAnim2, gUnk_09619F84, 6, work->joints.all);
            } else {
                BosTmArmStartJointAnim(&work->jointAnim2, gUnk_0961A074, 6, work->joints.all);
            }

            BosTmClbThrow(&work->clb2, &work->tips[1], -0xB00);
            work->tips[1].angle = 0x10C;
        }

        if (work->timer2 == 35) {
            work->tips[1].angle = 240;
        }

        work->timer2++;
        break;
    case 11:
        if (work->timer2 == 0) {
            if (work->src->tm->flags & 0x20) {
                BosTmArmStartJointAnim(&work->jointAnim2, gUnk_0961A164, 6, work->joints.all);
            } else {
                BosTmArmStartJointAnim(&work->jointAnim2, gUnk_0961A254, 6, work->joints.all);
            }

            BosTmClbThrow(&work->clb2, &work->tips[1], -0xB00);
            work->tips[1].angle = 0x10C;
        }

        if (work->timer2 == 50) {
            work->tips[1].angle = 240;
        }

        work->timer2++;
        break;
    case 9:
        if (work->timer2 == 0) {
            work->tips[1].angle = 0x110;
            BosTmClbHoldSpinning(&work->clb2, &work->tips[1]);

            if (work->src->tm->flags & 0x20) {
                BosTmArmStartJointAnim(&work->jointAnim2, gUnk_0961A510, 5, work->joints.all);
            } else {
                BosTmArmStartJointAnim(&work->jointAnim2, gUnk_0961A5D8, 5, work->joints.all);
            }
        }

        work->timer2++;
        break;
    case 17:
        return;
    }

    BosTmArmStepJointAnim(work->joints.all, &work->jointAnim2);
    BosTmArmUpdateArm0Tip(work);

    for (i = 0; i < 3; i++) {
        work->joints.all[i].gfx = AnimUpdate(&work->joints.all[i].anim);
    }
}

u8 task_bos_tm_arm_1(TmArmWork* work) {
    void* gfx;

    if (work->prevState != work->src->tm->state) {
        work->prevState = work->src->tm->state;
        work->timer = 0;
        work->timer2 = 0;
    }

    if (gFrameCounter % 2 != 0) {
        BosTmArmUpdateArm1(work);
    } else {
        BosTmArmUpdateArm0(work);
    }

    if (work->src->tm->state != 13) {
        gfx = AnimUpdate(&work->anim);
        work->clb.gfx = gfx;
        work->clb2.gfx = gfx;

        if (gFrameCounter % 5 == 0) {
            LoadObjPaletteBank(work->palette->index + 1, gUnk_096FB304 + work->paletteStep * 32);
            work->paletteStep = (work->paletteStep + 1) & 7;
        }
    }

    TaskPoolUpdate(&work->tasks);

    return 1;
}

void task_bos_tm_arm_2(TmArmWork* work) {
    void* pal;
    s32 mode;
    ObjAffine* affine;
    s16 depth;
    s16 endDepth;
    s16 x;
    s16 y;
    s32 i;
    TmArmJoint* j;

    if (gBtlWork->paused != 0) {
        pal = work->palette;
    } else if ((work->src->tm->flags & 1) && (gFrameCounter & 1)) {
        pal = work->palette2;
    } else {
        pal = work->palette;
    }

    for (i = 0; i < 3; i++) {
        j = &work->joints.all[i + 4];
        affine = AllocObjAffine(j->angle, 256, 256, 0);
        WorldToScreen(&x, &y, work->src->x + j->curX, work->src->y,
                      work->src->z + j->curY);
        depth = -4100;
        DrawSprite(x, y, j->gfx, work->tiles, pal, affine, 0x800,
                   (depth -= (work->src->y >> 8) * 4, (u16)depth));
        j = &work->joints.all[i];
        affine = AllocObjAffine(j->angle, 256, 256, 0);
        WorldToScreen(&x, &y, work->src->x2 + j->curX, work->src->y2,
                      work->src->z2 + j->curY);
        depth = -4100;
        DrawSprite(x, y, j->gfx, work->tiles, pal, affine, 0x800,
                   (depth -= (work->src->y2 >> 8) * 4, (u16)depth));
    }

    if (work->src->tm->flags & 32) {
        mode = 256;
    } else {
        mode = -256;
    }

    j = &work->joints.all[7];
    affine = AllocObjAffine(j->angle, mode, 256, 0);
    WorldToScreen(&x, &y, work->src->x + j->curX, work->src->y,
                  work->src->z + j->curY);
    DrawSprite(x, y, j->gfx, work->tiles, pal, affine, 0x800,
               (endDepth = -4100 - (work->src->y >> 8) * 4, (u16)endDepth));
    j = &work->joints.all[3];
    affine = AllocObjAffine(j->angle, mode, 256, 0);
    WorldToScreen(&x, &y, work->src->x2 + j->curX, work->src->y2,
                  work->src->z2 + j->curY);
    DrawSprite(x, y, j->gfx, work->tiles, pal, affine, 0x800,
               (endDepth = -4100 - (work->src->y2 >> 8) * 4, (u16)endDepth));
    TaskPoolDraw(&work->tasks);
}

void task_bos_tm_arm_3(TmArmWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjTiles(work->tiles2);
    ReleaseObjPalette(work->palette);
    ReleaseObjPalette(work->palette2);
    TaskPoolDestroy(&work->tasks);
}

void task_bos_tm_tbl_0(TmTblWork* work, TmWork* arg) {
    ColliderInit(&work->collider, 7, 0x1C, 0);
    ColliderSetPosition(&work->collider, 0x10000, 0x16000, 0);
    ColliderSetDisabled(&work->collider, 0);
    DisableBg(1);
    work->tm = arg;
    work->state = 0;
    work->unk_062 = 1;
    work->unk_064 = 0;
    work->frame = 0;
    work->gimmickPlayed = 0;
    work->height = 0;
}

u8 task_bos_tm_tbl_1(TmTblWork* work) {
    u16 t;

    switch (work->state) {
    case 1:
        if (work->tm->tableState == 1) {
            work->frame = 0;
            work->state = 3;
        }
        break;
    case 0:
        if (work->gimmickPlayed == 0) {
            if (ConsumeGimmickFlag(0) != 0) {
                work->gimmickPlayed = 1;
            }
        } else {
            work->state = 2;
            work->tm->tableState = 1;
            work->gimmickPlayed = 0;
        }
        break;
    case 2:
        switch (work->frame) {
        case 0:
            m4aSongNumStart(SONG_BTL_TABLE_U);
            EnableBg(1);
            LoadBgMap(1, &gUnk_096BF464[0x5000], 0x800);
            ColliderSetDisabled(&work->collider, 0);
            break;
        case 2:
            LoadBgMap(1, &gUnk_096BF464[0x4800], 0x800);
            break;
        case 4:
            LoadBgMap(1, &gUnk_096BF464[0x4000], 0x800);
            break;
        case 6:
            LoadBgMap(1, &gUnk_096BF464[0x3800], 0x800);
            break;
        case 8:
            LoadBgMap(1, &gUnk_096BF464[0x3000], 0x800);
            break;
        case 10:
            LoadBgMap(1, &gUnk_096BF464[0x2800], 0x800);
            break;
        case 12:
            LoadBgMap(1, &gUnk_096BF464[0x2000], 0x800);
            break;
        case 14:
            LoadBgMap(1, &gUnk_096BF464[0x1800], 0x800);
            break;
        case 16:
            LoadBgMap(1, &gUnk_096BF464[0x1000], 0x800);
            break;
        }

        if (work->frame > 15) {
            work->frame = 0;
            work->state = 1;
            work->tm->tableState = 2;
            t = work->tm->flags | 0x10;
            work->tm->flags = t;
        } else {
            ColliderSetHeight(&work->collider, work->height);
            work->height += 3;
            work->frame++;
        }
        break;
    case 3:
        switch (work->frame) {
        case 0:
            LoadBgMap(1, &gUnk_096BF464[0x1800], 0x800);
            ColliderSetDisabled(&work->collider, 1);
            work->height = 0;
            break;
        case 1:
            LoadBgMap(1, &gUnk_096BF464[0x2000], 0x800);
            break;
        case 2:
            LoadBgMap(1, &gUnk_096BF464[0x2800], 0x800);
            break;
        case 3:
            LoadBgMap(1, &gUnk_096BF464[0x3000], 0x800);
            break;
        case 4:
            LoadBgMap(1, &gUnk_096BF464[0x3800], 0x800);
            break;
        case 5:
            LoadBgMap(1, &gUnk_096BF464[0x4000], 0x800);
            break;
        case 6:
            LoadBgMap(1, &gUnk_096BF464[0x4800], 0x800);
            break;
        case 7:
            LoadBgMap(1, &gUnk_096BF464[0x5000], 0x800);
            break;
        case 8:
            DisableBg(1);
            break;
        }

        if (work->frame > 7) {
            work->frame = 0;
            work->state = 0;
            work->tm->tableState = 0;
        } else {
            work->frame++;
        }
        break;
    }

    SetBgScroll(1, (u16)((gBtlWork->viewX >> 8) + 8), (u16)((gBtlWork->viewY >> 8) - 70));
    return 1;
}

void task_bos_tm_tbl_3(TmTblWork* work) {
    ColliderUnregister(&work->collider);
    DisableBg(1);
}

TaskDesc gTaskDescBosTmArm = {
    "task_bos_tm_arm",
    (TaskInitFunc)task_bos_tm_arm_0,
    (TaskUpdateFunc)task_bos_tm_arm_1,
    (TaskDrawFunc)task_bos_tm_arm_2,
    (TaskDestroyFunc)task_bos_tm_arm_3,
    sizeof(TmArmWork),
};

TaskDesc gTaskDescBosTmTbl = {
    "task_bos_tm_tbl",
    (TaskInitFunc)task_bos_tm_tbl_0,
    (TaskUpdateFunc)task_bos_tm_tbl_1,
    NULL,
    (TaskDestroyFunc)task_bos_tm_tbl_3,
    sizeof(TmTblWork),
};
