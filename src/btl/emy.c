#include "task_descriptors.h"
#include "display.h"
#include "emy.h"
#include "task_animation_assets.h"
#include "sprites_emy.h"
#include "sprites_evt.h"
#include "system_state.h"
#include "btl_api.h"
#include "enemy_common.h"
#include "songs.h"
#include "player_progression.h"
#include "actor_localized_data.h"
#include "emy_tasks.h"

static const AnimDef sEmy00CommonAnimDefs[3] = {
    { gEmy00L00Frames, gEmy00L00Anims, gEmy00L00Tiles, 0, { 0, 0, 0 } },
    { gEmy00L09Frames, gEmy00L09Anims, gEmy00L09Tiles, 0, { 0, 0, 0 } },
    { gEmy00L02Frames, gEmy00L02Anims, gEmy00L02Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy00AnimDefs[7] = {
    { gEmy00L07Frames, gEmy00L07Anims, gEmy00L07Tiles, 1, { 0, 0, 0 } },
    { gEmy00L12Frames, gEmy00L12Anims, gEmy00L12Tiles, 0, { 0, 0, 0 } },
    { gEmy00L06Frames, gEmy00L06Anims, gEmy00L06Tiles, 1, { 0, 0, 0 } },
    { gEmy00L06Frames, gEmy00L06Anims, gEmy00L06Tiles, 0, { 0, 0, 0 } },
    { gEmy00L04Frames, gEmy00L04Anims, gEmy00L04Tiles, 0, { 0, 0, 0 } },
    { gEmy00L10Frames, gEmy00L10Anims, gEmy00L10Tiles, 0, { 0, 0, 0 } },
    { gEmy00L11Frames, gEmy00L11Anims, gEmy00L11Tiles, 0, { 0, 0, 0 } },
};

static const EmyDef sEmy00Def = { gEmy00Palette, sEmy00CommonAnimDefs, 384, 130, 10, 20, 64, 32, 16, 10, 3, { 0, 12, 32, 12, 16, 100, 0 } };

TaskDesc gTaskDescEmy00 = {
    "task_emy_00",
    (TaskInitFunc)task_emy_00_0,
    (TaskUpdateFunc)task_emy_00_1,
    (TaskDrawFunc)task_emy_00_2,
    (TaskDestroyFunc)task_emy_00_3,
    sizeof(EmyWork),
};

static const AnimDef sEmy01CommonAnimDefs[3] = {
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 0, { 0, 0, 0 } },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 3, { 0, 0, 0 } },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 2, { 0, 0, 0 } },
};

static const AnimDef sEmy01AnimDefs[2] = {
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 1, { 0, 0, 0 } },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 1, { 0, 0, 0 } },
};

static const EmyDef sEmy01Def = { gEmy01Palette, sEmy01CommonAnimDefs, 384, 130, 20, 20, 64, 32, 32, 10, 0, { 1, 33, 24, 12, 4, 100, 8 } };

TaskDesc gTaskDescEmy01 = {
    "task_emy_01",
    (TaskInitFunc)task_emy_01_0,
    (TaskUpdateFunc)task_emy_01_1,
    (TaskDrawFunc)task_emy_01_2,
    (TaskDestroyFunc)task_emy_01_3,
    sizeof(EmyWork),
};

static const AnimDef sEmy02CommonAnimDefs[3] = {
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 0, { 0, 0, 0 } },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 3, { 0, 0, 0 } },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 2, { 0, 0, 0 } },
};

static const AnimDef sEmy02AnimDefs[2] = {
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 6, { 0, 0, 0 } },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 8, { 0, 0, 0 } },
};

static const EmyDef sEmy02Def = { gEmy02Palette, sEmy02CommonAnimDefs, 460, 130, 20, 20, 64, 32, 32, 10, 0, { 2, 34, 24, 12, 4, 100, 8 } };

TaskDesc gTaskDescEmy02 = {
    "task_emy_02",
    (TaskInitFunc)task_emy_02_0,
    (TaskUpdateFunc)task_emy_02_1,
    (TaskDrawFunc)task_emy_02_2,
    (TaskDestroyFunc)task_emy_02_3,
    sizeof(EmyWork),
};

static const AnimDef sEmy03CommonAnimDefs[3] = {
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 0, { 0, 0, 0 } },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 3, { 0, 0, 0 } },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 2, { 0, 0, 0 } },
};

static const AnimDef sEmy03AnimDefs[2] = {
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 7, { 0, 0, 0 } },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 5, { 0, 0, 0 } },
};

static const EmyDef sEmy03Def = { gEmy03Palette, sEmy03CommonAnimDefs, 512, 130, 20, 20, 64, 32, 32, 10, 0, { 3, 36, 24, 12, 4, 100, 8 } };

TaskDesc gTaskDescEmy03 = {
    "task_emy_03",
    (TaskInitFunc)task_emy_03_0,
    (TaskUpdateFunc)task_emy_03_1,
    (TaskDrawFunc)task_emy_03_2,
    (TaskDestroyFunc)task_emy_03_3,
    sizeof(Emy03Work),
};

static const AnimDef sEmy04CommonAnimDefs[3] = {
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 0, { 0, 0, 0 } },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 3, { 0, 0, 0 } },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 2, { 0, 0, 0 } },
};

static const AnimDef sEmy04AnimDef = { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 4, { 0, 0, 0 } };

static const EmyDef sEmy04Def = { gEmy04Palette, sEmy04CommonAnimDefs, 332, 130, 20, 20, 0, 0, 0, 200, 0, { 4, 27, 24, 12, 4, 100, 8 } };

TaskDesc gTaskDescEmy04 = {
    "task_emy_04",
    (TaskInitFunc)task_emy_04_0,
    (TaskUpdateFunc)task_emy_04_1,
    (TaskDrawFunc)task_emy_04_2,
    (TaskDestroyFunc)task_emy_04_3,
    sizeof(Emy04Work),
};

static const AnimDef sEmy06CommonAnimDefs[3] = {
    { gEmy0600Frames, gEmy0600Anims, gEmy0600Tiles, 0, { 0, 0, 0 } },
    { gEmy0603Frames, gEmy0603Anims, gEmy0603Tiles, 0, { 0, 0, 0 } },
    { gEmy0600Frames, gEmy0600Anims, gEmy0600Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy06AnimDefs[2] = {
    { gEmy0610Frames, gEmy0610Anims, gEmy0610Tiles, 0, { 0, 0, 0 } },
    { gEmy0611Frames, gEmy0611Anims, gEmy0611Tiles, 0, { 0, 0, 0 } },
};

static const EmyDef sEmy06Def = { gEmy06Palette, sEmy06CommonAnimDefs, 230, 130, 20, 20, 70, 32, 48, 10, 0, { 5, 42, 32, 8, 16, 100, 0 } };

TaskDesc gTaskDescEmy06 = {
    "task_emy_06",
    (TaskInitFunc)task_emy_06_0,
    (TaskUpdateFunc)task_emy_06_1,
    (TaskDrawFunc)task_emy_06_2,
    (TaskDestroyFunc)task_emy_06_3,
    sizeof(Emy06Work),
};

static const AnimDef sEmy07CommonAnimDefs[3] = {
    { gEmy07Fl00Frames, gEmy07Fl00Anims, gEmy07Fl00Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl03Frames, gEmy07Fl03Anims, gEmy07Fl03Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl00Frames, gEmy07Fl00Anims, gEmy07Fl00Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy07AnimDefs[7] = {
    { gEmy07Fl05Frames, gEmy07Fl05Anims, gEmy07Fl05Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl04Frames, gEmy07Fl04Anims, gEmy07Fl04Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl04tFrames, gEmy07Fl04tAnims, gEmy07Fl04tTiles, 0, { 0, 0, 0 } },
    { gEmy07Fl07Frames, gEmy07Fl07Anims, gEmy07Fl07Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl06Frames, gEmy07Fl06Anims, gEmy07Fl06Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl08Frames, gEmy07Fl08Anims, gEmy07Fl08Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl02Frames, gEmy07Fl02Anims, gEmy07Fl02Tiles, 0, { 0, 0, 0 } },
};

static const EmyDef sEmy07Def = { gEmy07Palette, sEmy07CommonAnimDefs, 0, 130, 20, 20, 0, 0, 0, 1, 0, { 6, 40, 32, 12, 16, 100, 0 } };

TaskDesc gTaskDescEmy07 = {
    "task_emy_07",
    (TaskInitFunc)task_emy_07_0,
    (TaskUpdateFunc)task_emy_07_1,
    (TaskDrawFunc)task_emy_07_2,
    (TaskDestroyFunc)task_emy_07_3,
    sizeof(Emy07Work),
};

static const AnimDef sEmy08CommonAnimDefs[3] = {
    { gEmy07Fl00Frames, gEmy07Fl00Anims, gEmy07Fl00Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl03Frames, gEmy07Fl03Anims, gEmy07Fl03Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl09Frames, gEmy07Fl09Anims, gEmy07Fl09Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy08AnimDefs[6] = {
    { gEmy07Fl10Frames, gEmy07Fl10Anims, gEmy07Fl10Tiles, 0, { 0, 0, 0 } },
    { gUnk_09EDFFDC, gUnk_09EE0004, gUnk_089C292C, 0, { 0, 0, 0 } },
    { gEmy07Fl10tFrames, gEmy07Fl10tAnims, gEmy07Fl10tTiles, 0, { 0, 0, 0 } },
    { gEmy07Fl10fFrames, gEmy07Fl10fAnims, gEmy07Fl10fTiles, 0, { 0, 0, 0 } },
    { gEmy07Fl11tFrames, gEmy07Fl11tAnims, gEmy07Fl11tTiles, 0, { 0, 0, 0 } },
    { gEmy07Fl11fFrames, gEmy07Fl11fAnims, gEmy07Fl11fTiles, 0, { 0, 0, 0 } },
};

static const EmyDef sEmy08Def = { gEmy07bPalette, sEmy08CommonAnimDefs, 179, 130, 20, 20, 24, 24, 16, 5, 0, { 7, 999, 32, 12, 16, 100, 0 } };

TaskDesc gTaskDescEmy08 = {
    "task_emy_08",
    (TaskInitFunc)task_emy_08_0,
    (TaskUpdateFunc)task_emy_08_1,
    (TaskDrawFunc)task_emy_08_2,
    (TaskDestroyFunc)task_emy_08_3,
    sizeof(Emy08Work),
};

static const AnimDef sEmy14CommonAnimDefs[3] = {
    { gEmy14Ll00Frames, gEmy14Ll00Anims, gEmy14Ll00Tiles, 0, { 0, 0, 0 } },
    { gEmy14Ll03Frames, gEmy14Ll03Anims, gEmy14Ll03Tiles, 0, { 0, 0, 0 } },
    { gEmy14Ll01Frames, gEmy14Ll01Anims, gEmy14Ll01Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy14AnimDefs[2] = {
    { gEmy14Ll02Frames, gEmy14Ll02Anims, gEmy14Ll02Tiles, 0, { 0, 0, 0 } },
    { gEmy14Ll04Frames, gEmy14Ll04Anims, gEmy14Ll04Tiles, 0, { 0, 0, 0 } },
};

static const EmyDef sEmy14Def = { gEmy14Palette, sEmy14CommonAnimDefs, 307, 130, 10, 20, 64, 32, 16, 10, 0, { 9, 32, 35, 12, 16, 100, 0 } };

TaskDesc gTaskDescEmy14 = {
    "task_emy_14",
    (TaskInitFunc)task_emy_14_0,
    (TaskUpdateFunc)task_emy_14_1,
    (TaskDrawFunc)task_emy_14_2,
    (TaskDestroyFunc)task_emy_14_3,
    sizeof(EmyWork),
};

static const AnimDef sEmy15CommonAnimDefs[3] = {
    { gEmy1500Frames, gEmy1500Anims, gEmy1500Tiles, 0, { 0, 0, 0 } },
    { gEmy1502Frames, gEmy1502Anims, gEmy1502Tiles, 0, { 0, 0, 0 } },
    { gEmy1501Frames, gEmy1501Anims, gEmy1501Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy15AnimDefs[5] = {
    { gEmy1510Frames, gEmy1510Anims, gEmy1510Tiles, 0, { 0, 0, 0 } },
    { gEmy1510Frames, gEmy1510Anims, gEmy1510Tiles, 1, { 0, 0, 0 } },
    { gEmy1510Frames, gEmy1510Anims, gEmy1510Tiles, 2, { 0, 0, 0 } },
    { gEmy1511Frames, gEmy1511Anims, gEmy1511Tiles, 0, { 0, 0, 0 } },
    { gEmy1511Frames, gEmy1511Anims, gEmy1511Tiles, 1, { 0, 0, 0 } },
};

static const EmyDef sEmy15Def = { gEmy15Palette, sEmy15CommonAnimDefs, 192, 200, 2, 20, 64, 32, 32, 10, 0, { 10, 41, 35, 12, 16, 100, 0 } };

TaskDesc gTaskDescEmy15 = {
    "task_emy_15",
    (TaskInitFunc)task_emy_15_0,
    (TaskUpdateFunc)task_emy_15_1,
    (TaskDrawFunc)task_emy_15_2,
    (TaskDestroyFunc)task_emy_15_3,
    sizeof(EmyWork),
};

static const AnimDef sEmy16CommonAnimDefs[3] = {
    { gEmy1600Frames, gEmy1600Anims, gEmy1600Tiles, 0, { 0, 0, 0 } },
    { gEmy1602Frames, gEmy1602Anims, gEmy1602Tiles, 0, { 0, 0, 0 } },
    { gEmy1601Frames, gEmy1601Anims, gEmy1601Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy16AnimDefs[2] = {
    { gEmy1610Frames, gEmy1610Anims, gEmy1610Tiles, 0, { 0, 0, 0 } },
    { gEmy1611Frames, gEmy1611Anims, gEmy1611Tiles, 0, { 0, 0, 0 } },
};

static const EmyDef sEmy16Def = { gEmy16Palette, sEmy16CommonAnimDefs, 307, 130, 20, 20, 99, 32, 32, 10, 0, { 11, 29, 16, 8, 16, 100, 0 } };

TaskDesc gTaskDescEmy16 = {
    "task_emy_16",
    (TaskInitFunc)task_emy_16_0,
    (TaskUpdateFunc)task_emy_16_1,
    (TaskDrawFunc)task_emy_16_2,
    (TaskDestroyFunc)task_emy_16_3,
    sizeof(Emy16Work),
};

static TaskDesc sTaskDescEmy16B = {
    "task_emy_16_b",
    (TaskInitFunc)task_emy_16_b_0,
    (TaskUpdateFunc)task_emy_16_b_1,
    (TaskDrawFunc)task_emy_16_b_2,
    (TaskDestroyFunc)task_emy_16_b_3,
    sizeof(Emy16bWork),
};

static TaskDesc sTaskDescEmy16P = {
    "task_emy_16_p",
    (TaskInitFunc)task_emy_16_p_0,
    (TaskUpdateFunc)task_emy_16_p_1,
    (TaskDrawFunc)task_emy_16_p_2,
    (TaskDestroyFunc)task_emy_16_p_3,
    sizeof(Emy16pWork),
};

static const AnimDef sEmy18CommonAnimDefs[3] = {
    { gEmy1800Frames, gEmy1800Anims, gEmy1800Tiles, 0, { 0, 0, 0 } },
    { gEmy1802Frames, gEmy1802Anims, gEmy1802Tiles, 0, { 0, 0, 0 } },
    { gEmy1801Frames, gEmy1801Anims, gEmy1801Tiles, 1, { 0, 0, 0 } },
};

static const AnimDef sEmy18AnimDefs[4] = {
    { gEmy1810Frames, gEmy1810Anims, gEmy1810Tiles, 0, { 0, 0, 0 } },
    { gEmy1811Frames, gEmy1811Anims, gEmy1811Tiles, 0, { 0, 0, 0 } },
    { gEmy1801Frames, gEmy1801Anims, gEmy1801Tiles, 0, { 0, 0, 0 } },
    { gEmy1801Frames, gEmy1801Anims, gEmy1801Tiles, 2, { 0, 0, 0 } },
};

static const EmyDef sEmy18Def = { gEmy18Palette, sEmy18CommonAnimDefs, 768, 150, 4, 20, 40, 24, 16, 10, 0, { 12, 45, 40, 8, 16, 100, 0 } };

TaskDesc gTaskDescEmy18 = {
    "task_emy_18",
    (TaskInitFunc)task_emy_18_0,
    (TaskUpdateFunc)task_emy_18_1,
    (TaskDrawFunc)task_emy_18_2,
    (TaskDestroyFunc)task_emy_18_3,
    sizeof(Emy18Work),
};

static const AnimDef sEmy19CommonAnimDefs[3] = {
    { gEmy1900Frames, gEmy1900Anims, gEmy1900Tiles, 0, { 0, 0, 0 } },
    { gEmy1902Frames, gEmy1902Anims, gEmy1902Tiles, 0, { 0, 0, 0 } },
    { gEmy1901Frames, gEmy1901Anims, gEmy1901Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy19AnimDefs[5] = {
    { gEmy1910Frames, gEmy1910Anims, gEmy1910Tiles, 0, { 0, 0, 0 } },
    { gEmy1910Frames, gEmy1910Anims, gEmy1910Tiles, 1, { 0, 0, 0 } },
    { gEmy1910Frames, gEmy1910Anims, gEmy1910Tiles, 2, { 0, 0, 0 } },
    { gEmy1910Frames, gEmy1910Anims, gEmy1910Tiles, 3, { 0, 0, 0 } },
    { gEmy1911Frames, gEmy1911Anims, gEmy1911Tiles, 0, { 0, 0, 0 } },
};

static const EmyDef sEmy19Def = { gEmy19Palette, sEmy19CommonAnimDefs, 256, 130, 20, 20, 80, 80, 32, 10, 0, { 13, 53, 32, 13, 16, 100, 0 } };

TaskDesc gTaskDescEmy19 = {
    "task_emy_19",
    (TaskInitFunc)task_emy_19_0,
    (TaskUpdateFunc)task_emy_19_1,
    (TaskDrawFunc)task_emy_19_2,
    (TaskDestroyFunc)task_emy_19_3,
    sizeof(Emy19Work),
};

static const AnimDef sEmy21CommonAnimDefs[3] = {
    { gEmy2100Frames, gEmy2100Anims, gEmy2100Tiles, 0, { 0, 0, 0 } },
    { gEmy2102Frames, gEmy2102Anims, gEmy2102Tiles, 0, { 0, 0, 0 } },
    { gEmy2101Frames, gEmy2101Anims, gEmy2101Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy21AnimDefs[4] = {
    { gEmy2110Frames, gEmy2110Anims, gEmy2110Tiles, 0, { 0, 0, 0 } },
    { gEmy2111Frames, gEmy2111Anims, gEmy2111Tiles, 0, { 0, 0, 0 } },
    { gEmy2111Frames, gEmy2111Anims, gEmy2111Tiles, 1, { 0, 0, 0 } },
    { gEmy2111fFrames, gEmy2111fAnims, gEmy2111fTiles, 0, { 0, 0, 0 } },
};

static const EmyDef sEmy21Def = { gEmy21Palette, sEmy21CommonAnimDefs, 396, 130, 20, 20, 80, 80, 16, 5, 0, { 14, 40, 32, 16, 16, 100, 0 } };

TaskDesc gTaskDescEmy21 = {
    "task_emy_21",
    (TaskInitFunc)task_emy_21_0,
    (TaskUpdateFunc)task_emy_21_1,
    (TaskDrawFunc)task_emy_21_2,
    (TaskDestroyFunc)task_emy_21_3,
    sizeof(Emy21Work),
};

static const AnimDef sEmy22CommonAnimDefs[3] = {
    { gEmy2200Frames, gEmy2200Anims, gEmy2200Tiles, 0, { 0, 0, 0 } },
    { gEmy2202Frames, gEmy2202Anims, gEmy2202Tiles, 0, { 0, 0, 0 } },
    { gEmy2200Frames, gEmy2200Anims, gEmy2200Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy22AnimDefs[2] = {
    { gEmy2210Frames, gEmy2210Anims, gEmy2210Tiles, 0, { 0, 0, 0 } },
    { gEmy2211Frames, gEmy2211Anims, gEmy2211Tiles, 0, { 0, 0, 0 } },
};

static const EmyDef sEmy22Def = { gEmy22Palette, sEmy22CommonAnimDefs, 192, 130, 20, 20, 64, 32, 32, 5, 0, { 15, 61, 40, 12, 24, 15, 8 } };

TaskDesc gTaskDescEmy22 = {
    "task_emy_22",
    (TaskInitFunc)task_emy_22_0,
    (TaskUpdateFunc)task_emy_22_1,
    (TaskDrawFunc)task_emy_22_2,
    (TaskDestroyFunc)task_emy_22_3,
    sizeof(Emy22Work),
};

static const AnimDef sEmy23CommonAnimDefs[3] = {
    { gEmy2300Frames, gEmy2300Anims, gEmy2300Tiles, 0, { 0, 0, 0 } },
    { gEmy2302Frames, gEmy2302Anims, gEmy2302Tiles, 0, { 0, 0, 0 } },
    { gEmy2301Frames, gEmy2301Anims, gEmy2301Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy23AnimDefs[2] = {
    { gEmy2310Frames, gEmy2310Anims, gEmy2310Tiles, 0, { 0, 0, 0 } },
    { gEmy2311Frames, gEmy2311Anims, gEmy2311Tiles, 0, { 0, 0, 0 } },
};

static const EmyDef sEmy23Def = { gEmy23Palette, sEmy23CommonAnimDefs, 192, 30, 2, 20, 64, 40, 32, 25, 0, { 16, 66, 36, 10, 16, 100, 0 } };

TaskDesc gTaskDescEmy23 = {
    "task_emy_23",
    (TaskInitFunc)task_emy_23_0,
    (TaskUpdateFunc)task_emy_23_1,
    (TaskDrawFunc)task_emy_23_2,
    (TaskDestroyFunc)task_emy_23_3,
    sizeof(Emy23Work),
};

static const AnimDef sEmy25CommonAnimDefs[3] = {
    { gEmy2500Frames, gEmy2500Anims, gEmy2500Tiles, 0, { 0, 0, 0 } },
    { gEmy2502Frames, gEmy2502Anims, gEmy2502Tiles, 0, { 0, 0, 0 } },
    { gEmy2501Frames, gEmy2501Anims, gEmy2501Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy25AnimDefs[2] = {
    { gEmy2510Frames, gEmy2510Anims, gEmy2510Tiles, 0, { 0, 0, 0 } },
    { gEmy2511Frames, gEmy2511Anims, gEmy2511Tiles, 0, { 0, 0, 0 } },
};

static const EmyDef sEmy25Def = { gEmy25Palette, sEmy25CommonAnimDefs, 253, 130, 20, 20, 24, 16, 16, 3, 0, { 17, 79, 40, 12, 32, 100, 0 } };

TaskDesc gTaskDescEmy25 = {
    "task_emy_25",
    (TaskInitFunc)task_emy_25_0,
    (TaskUpdateFunc)task_emy_25_1,
    (TaskDrawFunc)task_emy_25_2,
    (TaskDestroyFunc)task_emy_25_3,
    sizeof(EmyWork),
};

static const AnimDef sEmy26CommonAnimDefs[3] = {
    { gEmy2600Frames, gEmy2600Anims, gEmy2600Tiles, 0, { 0, 0, 0 } },
    { gEmy2602Frames, gEmy2602Anims, gEmy2602Tiles, 0, { 0, 0, 0 } },
    { gEmy2601Frames, gEmy2601Anims, gEmy2601Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy26AnimDefs[2] = {
    { gEmy2610Frames, gEmy2610Anims, gEmy2610Tiles, 0, { 0, 0, 0 } },
    { gEmy2611Frames, gEmy2611Anims, gEmy2611Tiles, 0, { 0, 0, 0 } },
};

static const EmyDef sEmy26Def = { gEmy26Palette, sEmy26CommonAnimDefs, 192, 130, 20, 20, 64, 32, 32, 10, 0, { 18, 89, 36, 20, 16, 100, 4 } };

TaskDesc gTaskDescEmy26 = {
    "task_emy_26",
    (TaskInitFunc)task_emy_26_0,
    (TaskUpdateFunc)task_emy_26_1,
    (TaskDrawFunc)task_emy_26_2,
    (TaskDestroyFunc)task_emy_26_3,
    sizeof(EmyWork),
};

static const AnimDef sEmy27CommonAnimDefs[3] = {
    { gEmy2700Frames, gEmy2700Anims, gEmy2700Tiles, 0, { 0, 0, 0 } },
    { gEmy2702Frames, gEmy2702Anims, gEmy2702Tiles, 0, { 0, 0, 0 } },
    { gEmy2701Frames, gEmy2701Anims, gEmy2701Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy27AnimDefs[2] = {
    { gEmy2710Frames, gEmy2710Anims, gEmy2710Tiles, 0, { 0, 0, 0 } },
    { gEmy2711Frames, gEmy2711Anims, gEmy2711Tiles, 0, { 0, 0, 0 } },
};

static const EmyDef sEmy27Def = { gEmy27Palette, sEmy27CommonAnimDefs, 192, 130, 20, 20, 64, 32, 64, 10, 0, { 19, 125, 32, 12, 16, 100, 0 } };

TaskDesc gTaskDescEmy27 = {
    "task_emy_27",
    (TaskInitFunc)task_emy_27_0,
    (TaskUpdateFunc)task_emy_27_1,
    (TaskDrawFunc)task_emy_27_2,
    (TaskDestroyFunc)task_emy_27_3,
    sizeof(EmyWork),
};

static const AnimDef sEmy28CommonAnimDefs[3] = {
    { gEmy2800Frames, gEmy2800Anims, gEmy2800Tiles, 0, { 0, 0, 0 } },
    { gEmy2802Frames, gEmy2802Anims, gEmy2802Tiles, 0, { 0, 0, 0 } },
    { gEmy2801Frames, gEmy2801Anims, gEmy2801Tiles, 1, { 0, 0, 0 } },
};

static const AnimDef sEmy28AnimDefs[4] = {
    { gEmy2810Frames, gEmy2810Anims, gEmy2810Tiles, 0, { 0, 0, 0 } },
    { gEmy2811Frames, gEmy2811Anims, gEmy2811Tiles, 0, { 0, 0, 0 } },
    { gEmy2801Frames, gEmy2801Anims, gEmy2801Tiles, 0, { 0, 0, 0 } },
    { gEmy2801Frames, gEmy2801Anims, gEmy2801Tiles, 2, { 0, 0, 0 } },
};

static const EmyDef sEmy28Def = { gEmy28Palette, sEmy28CommonAnimDefs, 1024, 150, 4, 20, 40, 24, 16, 25, 0, { 20, 45, 48, 8, 16, 100, 4 } };

TaskDesc gTaskDescEmy28 = {
    "task_emy_28",
    (TaskInitFunc)task_emy_28_0,
    (TaskUpdateFunc)task_emy_28_1,
    (TaskDrawFunc)task_emy_28_2,
    (TaskDestroyFunc)task_emy_28_3,
    sizeof(Emy28Work),
};

static const AnimDef sEmy29CommonAnimDefs[3] = {
    { gEmy2900Frames, gEmy2900Anims, gEmy2900Tiles, 0, { 0, 0, 0 } },
    { gEmy2902Frames, gEmy2902Anims, gEmy2902Tiles, 0, { 0, 0, 0 } },
    { gEmy2900Frames, gEmy2900Anims, gEmy2900Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy29AnimDefs[2] = {
    { gEmy2910Frames, gEmy2910Anims, gEmy2910Tiles, 0, { 0, 0, 0 } },
    { gEmy2911Frames, gEmy2911Anims, gEmy2911Tiles, 0, { 0, 0, 0 } },
};

static const EmyDef sEmy29Def = { gEmy29Palette, sEmy29CommonAnimDefs, 192, 300, 20, 20, 64, 64, 32, 30, 0, { 21, 80, 56, 22, 32, 100, 4 } };

TaskDesc gTaskDescEmy29 = {
    "task_emy_29",
    (TaskInitFunc)task_emy_29_0,
    (TaskUpdateFunc)task_emy_29_1,
    (TaskDrawFunc)task_emy_29_2,
    (TaskDestroyFunc)task_emy_29_3,
    sizeof(Emy29Work),
};

static const AnimDef sEmy30CommonAnimDefs[3] = {
    { gEmy3000Frames, gEmy3000Anims, gEmy3000Tiles, 0, { 0, 0, 0 } },
    { gEmy3002Frames, gEmy3002Anims, gEmy3002Tiles, 0, { 0, 0, 0 } },
    { gEmy3001Frames, gEmy3001Anims, gEmy3001Tiles, 1, { 0, 0, 0 } },
};

static const AnimDef sEmy30AnimDefs[8] = {
    { gEmy3001Frames, gEmy3001Anims, gEmy3001Tiles, 0, { 0, 0, 0 } },
    { gEmy3001Frames, gEmy3001Anims, gEmy3001Tiles, 2, { 0, 0, 0 } },
    { gEmy3010Frames, gEmy3010Anims, gEmy3010Tiles, 0, { 0, 0, 0 } },
    { gEmy3010Frames, gEmy3010Anims, gEmy3010Tiles, 1, { 0, 0, 0 } },
    { gEmy3010Frames, gEmy3010Anims, gEmy3010Tiles, 2, { 0, 0, 0 } },
    { gEmy3011Frames, gEmy3011Anims, gEmy3011Tiles, 0, { 0, 0, 0 } },
    { gEmy3011Frames, gEmy3011Anims, gEmy3011Tiles, 1, { 0, 0, 0 } },
    { gEmy3011Frames, gEmy3011Anims, gEmy3011Tiles, 2, { 0, 0, 0 } },
};

static const EmyDef sEmy30Def = { gEmy30Palette, sEmy30CommonAnimDefs, 1024, 150, 4, 20, 60, 32, 32, 30, 0, { 22, 45, 34, 30, 16, 100, 4 } };

TaskDesc gTaskDescEmy30 = {
    "task_emy_30",
    (TaskInitFunc)task_emy_30_0,
    (TaskUpdateFunc)task_emy_30_1,
    (TaskDrawFunc)task_emy_30_2,
    (TaskDestroyFunc)task_emy_30_3,
    sizeof(EmyWork),
};

static const AnimDef sEmy31CommonAnimDefs[3] = {
    { gEmy3100Frames, gEmy3100Anims, gEmy3100Tiles, 0, { 0, 0, 0 } },
    { gEmy3104Frames, gEmy3104Anims, gEmy3104Tiles, 0, { 0, 0, 0 } },
    { gEmy3100Frames, gEmy3100Anims, gEmy3100Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy31AnimDefs[3] = {
    { gEmy3105Frames, gEmy3105Anims, gEmy3105Tiles, 0, { 0, 0, 0 } },
    { gEmy3106Frames, gEmy3106Anims, gEmy3106Tiles, 0, { 0, 0, 0 } },
    { gEmy3107Frames, gEmy3107Anims, gEmy3107Tiles, 0, { 0, 0, 0 } },
};

static const EmyDef sEmy31Def = { gEmy31Palette, sEmy31CommonAnimDefs, 256, 100, 10, 20, 64, 32, 32, 10, 0, { 23, 95, 32, 12, 24, 100, 0 } };

TaskDesc gTaskDescEmy31 = {
    "task_emy_31",
    (TaskInitFunc)task_emy_31_0,
    (TaskUpdateFunc)task_emy_31_1,
    (TaskDrawFunc)task_emy_31_2,
    (TaskDestroyFunc)task_emy_31_3,
    sizeof(Emy31Work),
};

static const AnimDef sEmy37CommonAnimDefs[3] = {
    { gEmy3700Frames, gEmy3700Anims, gEmy3700Tiles, 0, { 0, 0, 0 } },
    { gEmy3702Frames, gEmy3702Anims, gEmy3702Tiles, 0, { 0, 0, 0 } },
    { gEmy3701Frames, gEmy3701Anims, gEmy3701Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy37AnimDefs[11] = {
    { gEmy3710Frames, gEmy3710Anims, gEmy3710Tiles, 0, { 0, 0, 0 } },
    { gEmy3711Frames, gEmy3711Anims, gEmy3711Tiles, 0, { 0, 0, 0 } },
    { gEmy3711Frames, gEmy3711Anims, gEmy3711Tiles, 1, { 0, 0, 0 } },
    { gEmy3711Frames, gEmy3711Anims, gEmy3711Tiles, 2, { 0, 0, 0 } },
    { gEmy3711Frames, gEmy3711Anims, gEmy3711Tiles, 3, { 0, 0, 0 } },
    { gEmy3720Frames, gEmy3720Anims, gEmy3720Tiles, 0, { 0, 0, 0 } },
    { gEmy3720Frames, gEmy3720Anims, gEmy3720Tiles, 1, { 0, 0, 0 } },
    { gEmy3720Frames, gEmy3720Anims, gEmy3720Tiles, 2, { 0, 0, 0 } },
    { gEmy3720Frames, gEmy3720Anims, gEmy3720Tiles, 3, { 0, 0, 0 } },
    { gEmy3721Frames, gEmy3721Anims, gEmy3721Tiles, 0, { 0, 0, 0 } },
    { gEmy3721Frames, gEmy3721Anims, gEmy3721Tiles, 1, { 0, 0, 0 } },
};

static const EmyDef sEmy37Def = { gEmy37Palette, sEmy37CommonAnimDefs, 409, 130, 20, 20, 64, 32, 32, 10, 3, { 24, 110, 38, 12, 20, 100, 0 } };

TaskDesc gTaskDescEmy37 = {
    "task_emy_37",
    (TaskInitFunc)task_emy_37_0,
    (TaskUpdateFunc)task_emy_37_1,
    (TaskDrawFunc)task_emy_37_2,
    (TaskDestroyFunc)task_emy_37_3,
    sizeof(Emy37Work),
};

static const AnimDef sEmy38CommonAnimDefs[3] = {
    { gEmy3800Frames, gEmy3800Anims, gEmy3800Tiles, 0, { 0, 0, 0 } },
    { gEmy3802Frames, gEmy3802Anims, gEmy3802Tiles, 0, { 0, 0, 0 } },
    { gEmy3801Frames, gEmy3801Anims, gEmy3801Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy38AnimDefs[2] = {
    { gEmy3811Frames, gEmy3811Anims, gEmy3811Tiles, 0, { 0, 0, 0 } },
    { gEmy3810Frames, gEmy3810Anims, gEmy3810Tiles, 0, { 0, 0, 0 } },
};

static const EmyDef sEmy38Def = { gEmy38Palette, sEmy38CommonAnimDefs, 76, 130, 80, 22, 64, 32, 32, 10, 0, { 25, 112, 56, 25, 32, 100, 4 } };

TaskDesc gTaskDescEmy38 = {
    "task_emy_38",
    (TaskInitFunc)task_emy_38_0,
    (TaskUpdateFunc)task_emy_38_1,
    (TaskDrawFunc)task_emy_38_2,
    (TaskDestroyFunc)task_emy_38_3,
    sizeof(EmyWork),
};

static const AnimDef sEmy39CommonAnimDefs[3] = {
    { gEmy3900Frames, gEmy3900Anims, gEmy3900Tiles, 0, { 0, 0, 0 } },
    { gEmy3902Frames, gEmy3902Anims, gEmy3902Tiles, 0, { 0, 0, 0 } },
    { gEmy3901Frames, gEmy3901Anims, gEmy3901Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy39AnimDefs[2] = {
    { gEmy3910Frames, gEmy3910Anims, gEmy3910Tiles, 0, { 0, 0, 0 } },
    { gEmy3911Frames, gEmy3911Anims, gEmy3911Tiles, 0, { 0, 0, 0 } },
};

static const EmyDef sEmy39Def = { gEmy39Palette, sEmy39CommonAnimDefs, 102, 130, 100, 22, 64, 32, 32, 10, 0, { 26, 134, 56, 25, 32, 100, 4 } };

TaskDesc gTaskDescEmy39 = {
    "task_emy_39",
    (TaskInitFunc)task_emy_39_0,
    (TaskUpdateFunc)task_emy_39_1,
    (TaskDrawFunc)task_emy_39_2,
    (TaskDestroyFunc)task_emy_39_3,
    sizeof(Emy39Work),
};

static const AnimDef sEmy41CommonAnimDefs[3] = {
    { gEmy4100Frames, gEmy4100Anims, gEmy4100Tiles, 0, { 0, 0, 0 } },
    { gEmy4102Frames, gEmy4102Anims, gEmy4102Tiles, 0, { 0, 0, 0 } },
    { gEmy4101Frames, gEmy4101Anims, gEmy4101Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy41AnimDefs[2] = {
    { gEmy4110Frames, gEmy4110Anims, gEmy4110Tiles, 0, { 0, 0, 0 } },
    { gEmy4111Frames, gEmy4111Anims, gEmy4111Tiles, 0, { 0, 0, 0 } },
};

static const EmyDef sEmy41Def = { gEmy41Palette, sEmy41CommonAnimDefs, 192, 400, 50, 20, 64, 32, 32, 10, 0, { 27, 108, 56, 32, 20, 100, 4 } };

TaskDesc gTaskDescEmy41 = {
    "task_emy_41",
    (TaskInitFunc)task_emy_41_0,
    (TaskUpdateFunc)task_emy_41_1,
    (TaskDrawFunc)task_emy_41_2,
    (TaskDestroyFunc)task_emy_41_3,
    sizeof(Emy41Work),
};

static const AnimDef sEmy44CommonAnimDefs[3] = {
    { gEmy4400Frames, gEmy4400Anims, gEmy4400Tiles, 0, { 0, 0, 0 } },
    { gEmy4402Frames, gEmy4402Anims, gEmy4402Tiles, 0, { 0, 0, 0 } },
    { gEmy4401Frames, gEmy4401Anims, gEmy4401Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy44AnimDefs[2] = {
    { gEmy4410Frames, gEmy4410Anims, gEmy4410Tiles, 0, { 0, 0, 0 } },
    { gEmy4412Frames, gEmy4412Anims, gEmy4412Tiles, 0, { 0, 0, 0 } },
};

static const EmyDef sEmy44Def = { gEmy44Palette, sEmy44CommonAnimDefs, 192, 130, 90, 20, 60, 60, 16, 10, 0, { 28, 260, 48, 25, 32, 100, 4 } };

TaskDesc gTaskDescEmy44 = {
    "task_emy_44",
    (TaskInitFunc)task_emy_44_0,
    (TaskUpdateFunc)task_emy_44_1,
    (TaskDrawFunc)task_emy_44_2,
    (TaskDestroyFunc)task_emy_44_3,
    sizeof(EmyWork),
};

static const AnimDef sEmy81CommonAnimDefs[3] = {
    { gEmy8100Frames, gEmy8100Anims, gEmy8100Tiles, 0, { 0, 0, 0 } },
    { gEmy8102Frames, gEmy8102Anims, gEmy8102Tiles, 0, { 0, 0, 0 } },
    { gEmy8100Frames, gEmy8100Anims, gEmy8100Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy81AnimDefs[5] = {
    { gEmy8110Frames, gEmy8110Anims, gEmy8110Tiles, 0, { 0, 0, 0 } },
    { gEmy8111Frames, gEmy8111Anims, gEmy8111Tiles, 0, { 0, 0, 0 } },
    { gEmy8105Frames, gEmy8105Anims, gEmy8105Tiles, 0, { 0, 0, 0 } },
    { gEmy8105Frames, gEmy8105Anims, gEmy8105Tiles, 1, { 0, 0, 0 } },
    { gEmy8105Frames, gEmy8105Anims, gEmy8105Tiles, 2, { 0, 0, 0 } },
};

static const EmyDef sEmy81Def = { gEmy81Palette, sEmy81CommonAnimDefs, 128, 130, 20, 15, 64, 32, 32, 10, 0, { 29, 66, 27, 13, 16, 100, 0 } };

TaskDesc gTaskDescEmy81 = {
    "task_emy_81",
    (TaskInitFunc)task_emy_81_0,
    (TaskUpdateFunc)task_emy_81_1,
    (TaskDrawFunc)task_emy_81_2,
    (TaskDestroyFunc)task_emy_81_3,
    sizeof(Emy81Work),
};

static const AnimDef sEmy82CommonAnimDefs[3] = {
    { gEmy8200Frames, gEmy8200Anims, gEmy8200Tiles, 0, { 0, 0, 0 } },
    { gEmy8202Frames, gEmy8202Anims, gEmy8202Tiles, 0, { 0, 0, 0 } },
    { gEmy8201Frames, gEmy8201Anims, gEmy8201Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy82AnimDefs[6] = {
    { gEmy8210jFrames, gEmy8210jAnims, gEmy8210jTiles, 0, { 0, 0, 0 } },
    { gEmy8210jFrames, gEmy8210jAnims, gEmy8210jTiles, 1, { 0, 0, 0 } },
    { gEmy8210jFrames, gEmy8210jAnims, gEmy8210jTiles, 2, { 0, 0, 0 } },
    { gEmy8210Frames, gEmy8210Anims, gEmy8210Tiles, 0, { 0, 0, 0 } },
    { gEmy8211Frames, gEmy8211Anims, gEmy8211Tiles, 0, { 0, 0, 0 } },
    { gEmy8212Frames, gEmy8212Anims, gEmy8212Tiles, 0, { 0, 0, 0 } },
};

static const EmyDef sEmy82Def = { gEmy82Palette, sEmy82CommonAnimDefs, 204, 3, 20, 20, 48, 32, 32, 1, 0, { 30, 66, 32, 10, 16, 100, 0 } };

TaskDesc gTaskDescEmy82 = {
    "task_emy_82",
    (TaskInitFunc)task_emy_82_0,
    (TaskUpdateFunc)task_emy_82_1,
    (TaskDrawFunc)task_emy_82_2,
    (TaskDestroyFunc)task_emy_82_3,
    sizeof(Emy82Work),
};

static const AnimDef sEmy83CommonAnimDefs[3] = {
    { gEmy8300Frames, gEmy8300Anims, gEmy8300Tiles, 0, { 0, 0, 0 } },
    { gEmy8302Frames, gEmy8302Anims, gEmy8302Tiles, 0, { 0, 0, 0 } },
    { gEmy8300Frames, gEmy8300Anims, gEmy8300Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy83AnimDefs[4] = {
    { gEmy8310Frames, gEmy8310Anims, gEmy8310Tiles, 0, { 0, 0, 0 } },
    { gEmy8311Frames, gEmy8311Anims, gEmy8311Tiles, 0, { 0, 0, 0 } },
    { gEmy8311Frames, gEmy8311Anims, gEmy8311Tiles, 1, { 0, 0, 0 } },
    { gEmy8311Frames, gEmy8311Anims, gEmy8311Tiles, 2, { 0, 0, 0 } },
};

static const EmyDef sEmy83Def = { gEmy83Palette, sEmy83CommonAnimDefs, 192, 130, 20, 20, 50, 50, 50, 10, 0, { 31, 66, 35, 12, 24, 100, 0 } };

TaskDesc gTaskDescEmy83 = {
    "task_emy_83",
    (TaskInitFunc)task_emy_83_0,
    (TaskUpdateFunc)task_emy_83_1,
    (TaskDrawFunc)task_emy_83_2,
    (TaskDestroyFunc)task_emy_83_3,
    sizeof(Emy83Work),
};

static TaskDesc sTaskDescEmy83B = {
    "task_emy_83_b",
    (TaskInitFunc)task_emy_83_b_0,
    (TaskUpdateFunc)task_emy_83_b_1,
    (TaskDrawFunc)task_emy_83_b_2,
    (TaskDestroyFunc)task_emy_83_b_3,
    sizeof(Emy83bWork),
};

static TaskDesc sTaskDescEmy83S = {
    "task_emy_83_s",
    (TaskInitFunc)task_emy_83_s_0,
    (TaskUpdateFunc)task_emy_83_s_1,
    (TaskDrawFunc)task_emy_83_s_2,
    (TaskDestroyFunc)task_emy_83_s_3,
    sizeof(Emy83sWork),
};

static const AnimDef sEmyTrumpHCommonAnimDefs[3] = {
    { gTrumpH00bFrames, gTrumpH00bAnims, gTrumpH00bTiles, 0, { 0, 0, 0 } },
    { gTrumpH02bFrames, gTrumpH02bAnims, gTrumpH02bTiles, 0, { 0, 0, 0 } },
    { gTrumpH03Frames, gTrumpH03Anims, gTrumpH03Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmyTrumpHAnimDef = { gTrumpH10Frames, gTrumpH10Anims, gTrumpH10Tiles, 0, { 0, 0, 0 } };

static const EmyDef sEmyTrumpHDef = { gTrumpHPalette, sEmyTrumpHCommonAnimDefs, 409, 130, 20, 20, 90, 32, 32, 10, 0, { 47, 200, 40, 16, 16, 100, 0 } };

TaskDesc gTaskDescEmyTrumpH = {
    "task_emy_trump_h",
    (TaskInitFunc)task_emy_trump_h_0,
    (TaskUpdateFunc)task_emy_trump_h_1,
    (TaskDrawFunc)task_emy_trump_h_2,
    (TaskDestroyFunc)task_emy_trump_h_3,
    sizeof(EmyWork),
};

static const AnimDef sEmyTrumpSCommonAnimDefs[3] = {
    { gTrumpS00bFrames, gTrumpS00bAnims, gTrumpS00bTiles, 0, { 0, 0, 0 } },
    { gTrumpS02bFrames, gTrumpS02bAnims, gTrumpS02bTiles, 0, { 0, 0, 0 } },
    { gTrumpS03Frames, gTrumpS03Anims, gTrumpS03Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmyTrumpSAnimDef = { gTrumpS10Frames, gTrumpS10Anims, gTrumpS10Tiles, 0, { 0, 0, 0 } };

static const EmyDef sEmyTrumpSDef = { gTrumpSPalette, sEmyTrumpSCommonAnimDefs, 307, 130, 20, 20, 64, 32, 32, 10, 0, { 46, 200, 40, 16, 16, 100, 0 } };

TaskDesc gTaskDescEmyTrumpS = {
    "task_emy_trump_s",
    (TaskInitFunc)task_emy_trump_s_0,
    (TaskUpdateFunc)task_emy_trump_s_1,
    (TaskDrawFunc)task_emy_trump_s_2,
    (TaskDestroyFunc)task_emy_trump_s_3,
    sizeof(EmyWork),
};

static const AnimDef sEmyTestCommonAnimDefs[3] = {
    { gUnk_09EE2608, gUnk_09EE2618, gUnk_08C69204, 0, { 0, 0, 0 } },
    { gUnk_09EE2608, gUnk_09EE2618, gUnk_08C69204, 0, { 0, 0, 0 } },
    { gUnk_09EE2608, gUnk_09EE2618, gUnk_08C69204, 0, { 0, 0, 0 } },
};

static const EmyDef sEmyTestDef = { gUnk_08F6DD44, sEmyTestCommonAnimDefs, 0, 130, 20, 60, 64, 32, 32, 10, 0, { 28, 260, 16, 8, 16, 100, 0 } };

void task_emy_00_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmy00Def, obj);
    work->flags |= 1;
    work->idleState = 0x12;
    work->state = 0x16;
}

u8 task_emy_00_1(EmyWork* work) {
    EmyWork* w;
    BtlObj* act;
    u16 r;
    s32 pos;
    s32 pos2;
    u8 ret;

    w = work;
    act = &work->actor;

    if (_0800CBDC(work)) {
        r = GetRandom();

        switch (r & 1) {
        case 0:
            work->state = 24;
            break;
        case 1:
            work->state = 25;
            break;
        }
    }

    switch (w->state) {
    case 24:
        AnimChangeWithDef(sEmy00AnimDefs, &work->anim, 5, 0, work->tiles);
        EmyLungeAttack(w, 31, 18, 11, 165, 40, SONG_BTL_MON_HIT00, 0, 0, 24);
        break;
    case 25:
        AnimChangeWithDef(sEmy00AnimDefs, &work->anim, 6, 0, work->tiles);

        if (w->stateTimer == 10) {
            w->vz = -0x400;
        }

        EmyLungeAttack(w, 14, 35, 10, 166, 96, SONG_BTL_MON_HIT00, 0, 0, 24);
        break;
    case 19:
        AnimChangeWithDef(sEmy00AnimDefs, &work->anim, 0, 0, work->tiles);

        if (AnimIsFinished(&w->anim)) {
            w->state = 20;
            ColliderSetDisabled(&act->collider, 1);
            act->flags |= BTLOBJ_FLAG_INTANGIBLE;
            act->centerHeight = 0;
        }
        break;
    case 20:
        if (gBtlWork->flags & BTL_FLAG_ENEMY_MOVE_ENABLED) {
            GetEnemyTargetPosition(act, &pos, 0, 0);
            AnimChangeWithDef(sEmy00AnimDefs, &work->anim, 1, ANIM_FLAG_LOOP, work->tiles);
            act->x += gSineTable[w->angle] * w->speed >> 8;
            act->y += -gSineTable[w->angle + 64] * w->speed >> 8;

            if (w->stateTimer > 100) {
                w->state = 21;
                ColliderSetDisabled(&act->collider, 0);
                act->flags &= ~BTLOBJ_FLAG_INTANGIBLE;
                act->centerHeight = 16;
                w->stateTimer = 0;
            } else {
                w->stateTimer++;
            }

            if (act->x > pos) {
                act->flags |= BTLOBJ_FLAG_FACING_LEFT;
            } else {
                act->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
            }
        }
        break;
    case 22:
        AnimChangeWithDef(sEmy00AnimDefs, &work->anim, 3, 0, work->tiles);

        if (w->stateTimer == 20) {
            act->flags &= ~BTLOBJ_FLAG_INTANGIBLE;

            if (gGameState.flags & GAME_FLAG_FIRST_STRIKE) {
                EmyFinishSpawn(w);
                break;
            }
        }

        if (AnimIsFinished(&w->anim)) {
            EmyFinishSpawn(w);
            break;
        }

        w->stateTimer++;
        break;
    case 21:
        AnimChangeWithDef(sEmy00AnimDefs, &work->anim, 2, 0, work->tiles);

        if (w->stateTimer == 30) {
            act->flags &= ~BTLOBJ_FLAG_INTANGIBLE;
        }

        if (AnimIsFinished(&w->anim)) {
            act->flags &= ~(BTLOBJ_FLAG_INTANGIBLE | BTLOBJ_FLAG_CARD_USE_BLOCKED);
            w->state = 18;

#ifdef VERSION_EU
            w->stateTimer = 0;
#endif
        } else {
            w->stateTimer++;
        }
        break;
    case 18:
        if (w->stateTimer == 0) {
            ColliderSetDisabled(&act->collider, 0);
            act->flags &= ~(BTLOBJ_FLAG_INTANGIBLE | BTLOBJ_FLAG_CARD_USE_BLOCKED);
            AnimChangeWithDef(work->def->animDef, &work->anim, 0, ANIM_FLAG_LOOP | ANIM_FLAG_RANDOM_START,
                work->tiles);
        }

        TryEnemyCardUse(act);

        if (GetRandom() % 120 == 0) {
            w->state = 4;

            if (GetRandom() % 2 == 0) {
                w->x = -((act->attackOffset
                    + (-act->attackRangeX
                        + GetRandom() % (act->attackRangeX - -act->attackRangeX + 1)))
                    << 8);
            } else {
                w->x = (act->attackOffset
                    + (-act->attackRangeX
                        + GetRandom() % (act->attackRangeX - -act->attackRangeX + 1)))
                    << 8;
            }
        } else if (GetRandom() % 200 == 0) {
            w->state = 19;
            act->flags |= BTLOBJ_FLAG_CARD_USE_BLOCKED;
            w->angle = GetRandom();
            w->stateTimer = 0;
            break;
        }

        if (GetRandom() % w->def->turnInterval == 0) {
            GetEnemyTargetPosition(act, &pos2, 0, 0);

            if (act->x > pos2) {
                act->flags |= BTLOBJ_FLAG_FACING_LEFT;
            } else {
                act->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
            }
        }

        w->stateTimer++;
        break;
    }

    ret = _0800CDF0(w);

    if (w->state == 14) {
        AnimChangeWithDef(sEmy00AnimDefs, &work->anim, 4, ANIM_FLAG_LOOP, work->tiles);
    }

    return ret;
}

void task_emy_00_2(EmyWork* work) {
    BtlObj* act;
    u16 pri;
    ObjAffine* affine;
    s32 rot;
    s32 scale;
    s32 zoom;
    s16 x;
    s16 y;

    if (work->visible != 0) {
        act = &work->actor;
        pri = GetBattleSpritePriorityFlags(act->y) | work->spriteFlags;
        WorldToScreen(&x, &y, act->x, act->y, act->z);
        zoom = work->scaleY;

        if (zoom == 0x100) {
            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                scale = gBtlWork->scale;
                rot = scale;
            } else if (gBtlWork->scale == zoom) {
                scale = zoom;
                rot = scale;
                pri |= 1;
            } else {
                rot = -gBtlWork->scale;
                scale = gBtlWork->scale;
            }
        } else {
            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                rot = gBtlWork->scale * work->scaleX >> 8;
                scale = gBtlWork->scale;
            } else {
                rot = -(gBtlWork->scale * work->scaleX >> 8);
                scale = gBtlWork->scale;
            }

            scale = scale * zoom >> 8;
        }

        if (scale == 0x100 && rot == scale) {
            affine = 0;
        } else if (scale <= 0xFF) {
            affine = AllocObjAffine(0, rot, scale, 0);
        } else {
            affine = AllocObjAffine(0, rot, scale, 1);
        }

        if (StepHitFlash(act)) {
            DrawSprite(x, y, work->gfx, work->tiles, work->palette2, affine, pri,
                -0x1004 - (act->y >> 8) * 4);
        } else if (work->state == 0x14) {
            DrawSprite(x, y, work->gfx, work->tiles, work->palette, affine, pri, 0xFFFF);
        } else {
            DrawSprite(x, y, work->gfx, work->tiles, work->palette, affine, pri,
                -0x1004 - (act->y >> 8) * 4);
        }

        TaskPoolDraw(&work->tasks);
    }
}

void task_emy_00_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_01_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmy01Def, obj);
    work->idleState = 7;
}

u8 task_emy_01_1(EmyWork* work) {
    EmyWork* w;
    BtlObj* act;
    u16 r;
    s32 x;

    w = work;
    act = &work->actor;

    if (_0800CBDC(work)) {
        r = GetRandom();

        switch (r & 1) {
        case 0:
            work->state = 0x12;
            break;
        case 1:
            work->state = 0x13;
            break;
        }
    }

    switch (work->state) {
    case 0x12: {
        s32 z;
        AnimChangeWithDef(sEmy01AnimDefs, &w->anim, 0, 0, w->tiles);
        work->vz = 0;

        if (work->stateTimer != 0) {
            if (work->stateTimer == 0x16) {
                z = act->y;

                if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    x = act->x - 0x6400;
                    BgFxStartFire(0, act->x - 0x2600, z, act->z - 0xC00, x, z, 0, 1,
                        0xA7);
                } else {
                    x = act->x + 0x6400;
                    BgFxStartFire(0, act->x + 0x2600, z, act->z - 0xC00, x, z, 0, 0,
                        0xA7);
                }
            }
        }

        if (work->stateTimer > 0x15 && !BgFxIsActive()) {
            EmyReturnToIdle(work);
        } else {
            work->stateTimer++;
        }
        break;
    }
    case 0x13: {
        s32 z;
        AnimChangeWithDef(sEmy01AnimDefs, &w->anim, 1, 0, w->tiles);
        work->vz = 0;

        if (work->stateTimer != 0) {
            if (work->stateTimer == 0x16) {
                z = act->y;

                if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    x = act->x - 0x6400;
                    BgFxStartFire(1, act->x - 0x2600, z, act->z - 0xC00, x, z, 0, 1,
                        0xA8);
                } else {
                    x = act->x + 0x6400;
                    BgFxStartFire(1, act->x + 0x2600, z, act->z - 0xC00, x, z, 0, 0,
                        0xA8);
                }
            }
        }

        if (work->stateTimer > 0x15 && !BgFxIsActive()) {
            EmyReturnToIdle(work);
        } else {
            work->stateTimer++;
        }
        break;
    }
    }

    return _0800CDF0(work);
}

void task_emy_01_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_01_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_02_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmy02Def, obj);
    work->idleState = 7;
}

u8 task_emy_02_1(EmyWork* work) {
    EmyWork* w;
    BtlObj* act;
    u16 r;
    s32 p;

    w = work;
    act = &work->actor;

    if (_0800CBDC(work)) {
        r = GetRandom();

        switch (r & 1) {
        case 0:
            work->state = 0x12;
            break;
        case 1:
            work->state = 0x13;
            break;
        }
    }

    switch (work->state) {
    case 0x12: {
        s32 y;

        AnimChangeWithDef(sEmy02AnimDefs, &w->anim, 0, 0, w->tiles);
        work->vz = 0;

        if (work->stateTimer == 0) {
        } else if (work->stateTimer == 22) {
            y = act->y;

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                p = act->x - 0x3C00;
                BgFxStartBlizzard(0, act->x - 0x2800, y, act->z - 0x800, p, y, 0, 1,
                    0xA9);
            } else {
                p = act->x + 0x3C00;
                BgFxStartBlizzard(0, act->x + 0x2800, y, act->z - 0x800, p, y, 0, 0,
                    0xA9);
            }
        }

        if (work->stateTimer > 21 && !BgFxIsActive()) {
            EmyReturnToIdle(work);
        } else {
            work->stateTimer++;
        }
        break;
    }
    case 0x13: {
        s32 y;

        AnimChangeWithDef(sEmy02AnimDefs, &w->anim, 1, 0, w->tiles);
        work->vz = 0;

        if (work->stateTimer == 0) {
        } else if (work->stateTimer == 3) {
            y = act->y;

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                p = act->x - 0x3C00;
                BgFxStartBlizzard(1, act->x - 0x2800, y, act->z - 0x800, p, y, 0, 1,
                    0xAA);
            } else {
                p = act->x + 0x3C00;
                BgFxStartBlizzard(1, act->x + 0x2800, y, act->z - 0x800, p, y, 0, 0,
                    0xAA);
            }
        }

        if (work->stateTimer > 2 && !BgFxIsActive()) {
            EmyReturnToIdle(work);
        } else {
            work->stateTimer++;
        }
        break;
    }
    }

    return _0800CDF0(work);
}

void task_emy_02_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_02_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_03_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmy03Def, obj);
    work->idleState = 7;
}

u8 task_emy_03_1(Emy03Work* work) {
    Emy03Work* w;
    BtlObj* act;
    u16 r;

    w = work;
    act = &work->base.actor;

    if (_0800CBDC(&work->base)) {
        r = GetRandom();

        switch (r & 1) {
        case 0:
            work->base.state = 0x12;
            break;
        case 1:
            work->base.state = 0x13;
            break;
        }
    }

    switch (work->base.state) {
    case 0x12:
        if (work->base.stateTimer == 0) {
            work->base.vz = -0x480;
            AnimChangeWithDef(sEmy03AnimDefs, &w->base.anim, 0, 0, w->base.tiles);
        } else if (work->base.stateTimer == 1) {
            BgFxStartActorThunder(act);
            m4aSongNumStart(SONG_BTL_YELLOW_MOV);
        }

        if (EmyLungeAttack(&work->base, 0x11, 0x17, 0x0A, 0xAB, 0x50, SONG_BTL_YELLOW_HIT, 0, 0, 0x0A) == 2) {
            BgAnimStop();
        }
        break;
    case 0x13:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sEmy03AnimDefs, &w->base.anim, 1, 0, w->base.tiles);
        } else if (work->base.stateTimer == 1) {
            GetEnemyTargetPosition(act, &w->targetX, &w->targetY, 0);
            w->unk_18C = 0;
            BgFxStartThunder(0, act->x, act->y, act->z - 0x1000, w->targetX,
                w->targetY, 0, 0xAC);
        }

        work->base.vz = 0;

        if (AnimIsFinished(&work->base.anim) && !BgFxIsActive()) {
            EmyReturnToIdle(&work->base);
        } else {
            work->base.stateTimer++;
        }
        break;
    }

    return _0800CDF0(&work->base);
}

void task_emy_03_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_03_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_04_0(Emy04Work* work, void* obj) {
    EmyInit(&work->base, &sEmy04Def, obj);
    work->base.idleState = 7;
    work->unk_184 = 0;
    work->healCount = 0;
}

u8 task_emy_04_1(Emy04Work* work) {
    Emy04Work* w;
    BtlObj* act;
    BtlObj* p;
    BtlObj* best;
    s16 bestv;

    w = work;
    act = &work->base.actor;

    if (_0800CBDC(&work->base)) {
        work->base.state = 0x12;
    }

    switch (work->base.state) {
    case 0x12:
        AnimChangeWithDef(&sEmy04AnimDef, &work->base.anim, 0, 0, work->base.tiles);
        work->base.vz = 0;

        if (work->healCount > 2) {
            CreateBtlPopTask(act, 2);
            EmyReturnToIdle(&work->base);
            break;
        }

        if (work->base.stateTimer == 3) {
            best = 0;
            bestv = 0;

            for (p = ListPoolFirst(&gBtlWork->pool); p != NULL;
                    p = ListPoolNext(&p->node)) {
                if (!(p->flags & BTLOBJ_FLAG_INTANGIBLE)) {
                    if (bestv < p->maxHp - p->hp) {
                        bestv = p->maxHp - p->hp;
                        best = p;
                    }
                }
            }

            if (best == NULL) {
                best = act;
            }

            if (best->hp == best->maxHp) {
                CreateBtlPopTask(act, 2);
                EmyReturnToIdle(&work->base);
                break;
            }

            best->flags |= BTLOBJ_FLAG_HEAL_PENDING;
            best->damage = -0x1E;
            BgFxStartCure(0, best->x, best->y, best->z);
            w->healCount++;
        }

        if (work->base.stateTimer > 0x0D) {
            if (!BgFxIsActive()) {
                EmyReturnToIdle(&work->base);
            }
        } else {
            work->base.stateTimer++;
        }
        break;
    }

    return _0800CDF0(&work->base);
}

void task_emy_04_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_04_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_06_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmy06Def, obj);
    work->idleState = 7;
}

u8 task_emy_06_1(Emy06Work* work) {
    Emy06Work* w;
    BtlObj* act;
    s32* p;
    u16 s;
    u16 m;
    s32 pos;
    s32 d;
    s32 t;
    s32 v;
    s32 e;
    s32 tx;
    s32 ty;

    w = work;
    act = &work->base.actor;

    if (_0800CBDC(&work->base)) {
        GetEnemyTargetPosition(act, 0, &pos, 0);
        d = act->y - pos;

        if (d >= 0 ? d <= 0xFFF : pos - act->y <= 0xFFF) {
            work->base.state = 0x13;
        } else {
            work->base.state = 0x12;
        }

        w->speed = 0;
    }

    switch (work->base.state) {
    case 0x12:
        AnimChangeWithDef(sEmy06AnimDefs, &w->base.anim, 0, 0, w->base.tiles);
        work->base.vz = 0;
        p = &gBtlWork->targetZ;
        t = act->z + 0xC00;
        act->z += (*p - t) >> 4;
        s = AnimGetFrame(&work->base.anim);

        if (s >= 5 && s <= 20) {
            m = work->base.stateTimer;
            m &= 3;

            if (m == 0) {
                GetEnemyTargetPosition(act, &tx, &ty, 0);
                work->base.angle = GetAngle(act->x, act->y, tx, ty);
            }

            act->x += gSineTable[work->base.angle] * 2;
            act->y -= gSineTable[work->base.angle + 0x40] * 2;

            if (ApplyAttackBox(0xAF, act->x, act->y, act->z - 0x800, 0x14, 0x14,
                    8)) {
                m4aSongNumStart(SONG_BTL_MON_HIT04);
            }
        }

        if (AnimIsFinished(&work->base.anim)) {
            EmyReturnToIdle(&work->base);
        } else {
            work->base.stateTimer++;
        }
        break;
    case 0x13:
        AnimChangeWithDef(sEmy06AnimDefs, &w->base.anim, 1, 0, w->base.tiles);
        work->base.vz = 0;
        p = &gBtlWork->targetZ;
        t = act->z + 0xC00;
        act->z += (*p - t) >> 4;
        s = AnimGetFrame(&work->base.anim);

        if (s >= 6 && s <= 16) {
            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                v = act->x;
                v += 0x7800;
            } else {
                v = act->x;
                v -= 0x7800;
            }

            e = (act->originX - v) >> 3;
            w->speed += 0x33;

            if (e > w->speed) {
                e = w->speed;
            } else if (e < -w->speed) {
                e = -w->speed;
            }

            act->x += e;

            if (ApplyAttackBox(0xB0, act->x, act->y, act->z - 0x800, 0x10, 0x10,
                    8)) {
                m4aSongNumStart(SONG_BTL_MON_HIT00);
            }
        }

        if (AnimIsFinished(&work->base.anim)) {
            EmyReturnToIdle(&work->base);
        } else {
            work->base.stateTimer++;
        }
        break;
    }

    return _0800CDF0(&work->base);
}

void task_emy_06_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_06_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_07_0(Emy07Work* work, void* obj) {
    EmyInit(&work->base, &sEmy07Def, obj);
    work->successCount = 0;
    work->unk_186 = 0;
    work->base.idleState = 0x12;
    work->base.actor.flags |= BTLOBJ_FLAG_NEVER_USES_CARDS;
    work->rewarded = 0;
}

u8 task_emy_07_1(Emy07Work* work) {
    Emy07Work* w;
    BtlObj* act;
    EmySpawn spawn;
    u32 state;
    s32 pos;
    s32 pos2;

    w = work;
    act = &work->base.actor;
    state = work->base.state;

#ifdef VERSION_EU
    act->hp = 0x7FFF;
#endif

    _0800CBDC(&work->base);

#ifdef VERSION_EU
    act->hp = act->maxHp;
#endif

    switch (work->base.state) {
    case 1:
    case 3:
    case 15:
        work->base.state = 26;

        switch (state) {
        case 21:
            w->unk_186 = 0;

            if (act->hitFlags & 0x10000000) {
                ClearBtlObjActionFlags(act);
                work->base.state = 20;
                work->base.stateTimer = 0;
            }
            break;
        case 22:
            w->unk_186 = 0;

            if (act->hitFlags & 0x20000000) {
                ClearBtlObjActionFlags(act);
                work->base.state = 20;
                work->base.stateTimer = 0;
            }
            break;
        case 23:
            w->unk_186 = 1;

            if (act->hitFlags & 0x40000000) {
                ClearBtlObjActionFlags(act);
                work->base.state = 20;
                work->base.stateTimer = 0;
            }
            break;
        }

        act->hp = act->maxHp;
        ColliderSetDisabled(&act->collider, 0);
        break;
    }

    switch (work->base.state) {
    case 18:
        AnimChangeWithDef(w->base.def->animDef, &w->base.anim, 0, ANIM_FLAG_LOOP | ANIM_FLAG_RANDOM_START,
            w->base.tiles);
        GetEnemyTargetPosition(act, &pos, 0, 0);

        if (act->x < pos) {
            act->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
        } else {
            act->flags |= BTLOBJ_FLAG_FACING_LEFT;
        }

        if (GetRandom() % 60 == 0) {
            work->base.stateTimer = 0;

            switch (GetRandom() % 3) {
            case 1:
                work->base.state = 22;
                break;
            case 2:
                work->base.state = 23;
                break;
            case 0:
            default:
                work->base.state = 21;
                break;
            }
        } else {
            work->base.stateTimer++;
        }
        break;
    case 21:
        AnimChangeWithDef(sEmy07AnimDefs, &w->base.anim, 3, ANIM_FLAG_LOOP, w->base.tiles);

        if (work->base.stateTimer > 300) {
            work->base.stateTimer = 0;
            work->base.state = 18;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 22:
        AnimChangeWithDef(sEmy07AnimDefs, &w->base.anim, 4, ANIM_FLAG_LOOP, w->base.tiles);

        if (work->base.stateTimer > 300) {
            work->base.stateTimer = 0;
            work->base.state = 18;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 23:
        AnimChangeWithDef(sEmy07AnimDefs, &w->base.anim, 5, ANIM_FLAG_LOOP, w->base.tiles);

        if (work->base.stateTimer > 300) {
            work->base.stateTimer = 0;
            work->base.state = 18;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 20:
        if (w->unk_186 != 0) {
            AnimChangeWithDef(sEmy07AnimDefs, &w->base.anim, 2, 0, w->base.tiles);
        } else {
            AnimChangeWithDef(sEmy07AnimDefs, &w->base.anim, 1, 0, w->base.tiles);
        }

        if (work->base.stateTimer == 0) {
            m4aSongNumStart(SONG_BTL_WM_OK);
            work->base.stateTimer = 1;
            act->flags |= BTLOBJ_FLAG_INTANGIBLE;
        }

        if (w->successCount == 2 && gFrameCounter % 10 == 0) {
            spawn.unk_12 = 1;
            spawn.unk_14 = 0;
            spawn.x = act->x;
            spawn.y = act->y;
            spawn.z = act->z - (act->height << 8);
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBtlPrize,
                &spawn);
        }

        if (AnimIsFinished(&work->base.anim)) {
            w->successCount++;

            if (w->successCount > 2) {
                work->base.stateTimer = 0;
                work->base.state = 25;
                w->rewarded = 1;
                SetJiminyFlag(110);
            } else {
                work->base.stateTimer = 0;
                work->base.state = 18;
                act->flags &= ~BTLOBJ_FLAG_INTANGIBLE;
            }
        }
        break;
    case 26:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(w->base.def->animDef, &w->base.anim, 1, 0,
                w->base.tiles);
        }

        GetEnemyTargetPosition(act, &pos2, 0, 0);

        if (act->x < pos2) {
            act->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
        } else {
            act->flags |= BTLOBJ_FLAG_FACING_LEFT;
        }

        if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            act->flags |= BTLOBJ_FLAG_INTANGIBLE;
            work->base.stateTimer = 0;
            work->base.state = 19;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 19:
        AnimChangeWithDef(sEmy07AnimDefs, &w->base.anim, 0, 0, w->base.tiles);

        if (work->base.stateTimer == 0) {
            act->flags |= BTLOBJ_FLAG_INTANGIBLE;
            work->base.stateTimer = 1;
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 25;
        }
        break;
    case 25:
        AnimChangeWithDef(sEmy07AnimDefs, &w->base.anim, 6, 0, w->base.tiles);

        if (AnimIsFinished(&work->base.anim)) {
            if (w->rewarded != 0) {
                DropEnemyPrizes(act);
                TryDropPremireCard(act);
            }

            return 0;
        }
        break;
    }

    return _0800CDF0(&work->base);
}

void task_emy_07_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_07_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_08_0(Emy08Work* work, void* obj) {
    EmyInit(&work->base, &sEmy08Def, obj);
    work->palette = LoadObjPalette(gEmy07mPalette, 0x20);
    work->basePalette = work->base.palette;
    work->flags = 0;
}

u8 task_emy_08_1(Emy08Work* work) {
    Emy08Work* w;
    BtlObj* act;
    u16 r;
    s32 dx;
    s32 dy;

    w = work;
    act = &work->base.actor;

    if (_0800CBDC(&work->base)) {
        r = GetRandom();

        switch (r & 1) {
        case 0:
            work->base.state = 0x12;
            break;
        case 1:
            work->base.state = 0x13;
            break;
        }
    }

    switch (work->base.state) {
    case 0:
        if (GetRandom() % 100 == 0) {
            if (w->flags & 2) {
                work->base.state = 23;
            } else {
                work->base.state = 22;
            }

            work->base.stateTimer = 0;
        }
        break;
    case 22:
        AnimChangeWithDef(sEmy08AnimDefs, &w->base.anim, 4, 0, w->base.tiles);

        if (AnimGetFrame(&work->base.anim) == 6) {
            act->flags |= (BTLOBJ_FLAG_IMMUNE_STOP | BTLOBJ_FLAG_INVULNERABLE);
            w->flags |= 2;
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = work->base.idleState;
        }
        break;
    case 23:
        AnimChangeWithDef(sEmy08AnimDefs, &w->base.anim, 5, 0, w->base.tiles);

        if (AnimGetFrame(&work->base.anim) == 4) {
            act->flags &= ~(BTLOBJ_FLAG_IMMUNE_STOP | BTLOBJ_FLAG_INVULNERABLE);
            w->flags &= ~2;
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = work->base.idleState;
        }
        break;
    case 18:
        AnimChangeWithDef(sEmy08AnimDefs, &w->base.anim, 0, 0, w->base.tiles);

        if (AnimIsFinished(&work->base.anim)) {
            EmyReturnToIdle(&work->base);
            act->flags |= BTLOBJ_FLAG_CARD_USE_BLOCKED;

            if (w->flags & 1) {
                work->base.state = 20;
            } else {
                work->base.state = 21;
            }
        } else if (work->base.anim.timer == 0) {
            dx = 0;
            dy = 0;

            switch (work->base.anim.frame) {
            case 1:
                dx = 2;
                break;
            case 2:
                dx = 2;
                dy = 1;
                break;
            case 3:
                dx = 2;
                dy = 1;
                break;
            case 4:
                dx = 2;
                dy = 1;
                break;
            case 5:
                dx = 3;
                dy = 1;
                break;
            case 6:
                dx = 3;
                break;
            case 7:
                dx = 2;

                if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                        ? ApplyAttackBox(0xB1, act->x - 0x1400, act->y, act->z,
                            4, 4, 0x20)
                        : ApplyAttackBox(0xB1, act->x + 0x1400, act->y, act->z,
                            4, 4, 0x20)) {
                    m4aSongNumStart(SONG_BTL_HANE_HIT);
                    w->flags |= 1;
                } else {
                    w->flags &= ~1;
                }
                break;
            }

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                act->x -= dx << 8;
            } else {
                act->x += dx << 8;
            }

            act->y -= dy << 8;
        }
        break;
    case 20:
        AnimChangeWithDef(sEmy08AnimDefs, &w->base.anim, 2, 0, w->base.tiles);

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = work->base.idleState;
            act->flags &= ~BTLOBJ_FLAG_CARD_USE_BLOCKED;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 21:
        AnimChangeWithDef(sEmy08AnimDefs, &w->base.anim, 3, 0, w->base.tiles);

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = work->base.idleState;
            act->flags &= ~BTLOBJ_FLAG_CARD_USE_BLOCKED;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 19:
        AnimChangeWithDef(sEmy08AnimDefs, &w->base.anim, 1, 0, w->base.tiles);

        if (work->base.anim.timer == 0
                && AnimGetFrame(&work->base.anim) == 7) {
            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                BgFxStartGas(act->x, act->y, act->z - 0xA00, 1);
            } else {
                BgFxStartGas(act->x, act->y, act->z - 0xA00, 0);
            }
        }

        if (work->base.stateTimer == 60) {
            (act->flags & BTLOBJ_FLAG_FACING_LEFT)
                ? ApplyAttackBox(0xB2, act->x, act->y, act->z, 0x20, 0x20, 0x20)
                : ApplyAttackBox(0xB2, act->x, act->y, act->z, 0x20, 0x20, 0x20);
        }

        if (AnimIsFinished(&work->base.anim) && !BgFxIsActive()) {
            EmyReturnToIdle(&work->base);
        } else {
            work->base.stateTimer++;
        }
        break;
    }

    return _0800CDF0(&work->base);
}

void task_emy_08_2(Emy08Work* work) {
    work->base.palette = (work->flags & 2) ? work->palette : work->basePalette;
    EmyDraw(&work->base);
    work->base.palette = work->basePalette;
}

void task_emy_08_3(Emy08Work* work) {
    EmyReleaseResources(&work->base);
    ReleaseObjPalette(work->palette);
}

void task_emy_14_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmy14Def, obj);
}

u8 task_emy_14_1(EmyWork* work) {
    EmyWork* w;
    BtlObj* act;
    s32 pos;
    s32 d;

    w = work;
    act = &work->actor;

    if (_0800CBDC(work)) {
        GetEnemyTargetPosition(act, &pos, 0, 0);
        d = act->x - pos;

        if (d >= 0 ? d <= 0x31FF : pos - act->x <= 0x31FF) {
            work->state = 0x12;
        } else {
            work->state = 0x13;
        }
    }

    switch (work->state) {
    case 0x12:
        AnimChangeWithDef(sEmy14AnimDefs, &w->anim, 0, 0, w->tiles);
        EmyLungeAttack(work, 0x0F, 0x0E, 0x14, 0xB3, 0x18, SONG_BTL_HANE_HIT, 0, 0, 0x16);
        break;
    case 0x13:
        AnimChangeWithDef(sEmy14AnimDefs, &w->anim, 1, 0, w->tiles);
        EmyLungeAttack(work, 0x14, 0x25, 0x06, 0xB4, 0x64, SONG_BTL_MON_HIT02, 0, 0, 0x14);
        break;
    }

    return _0800CDF0(work);
}

void task_emy_14_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_14_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_15_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmy15Def, obj);
}

u8 task_emy_15_1(EmyWork* work) {
    EmyWork* w;
    BtlObj* act;
    u16 r;

    w = work;
    act = &work->actor;

    if (_0800CBDC(work)) {
        r = GetRandom();

        switch (r & 1) {
        case 0:
            work->state = 0x12;
            break;
        case 1:
            work->state = 0x15;
            break;
        }
    }

    switch (work->state) {
    case 0x12:
        AnimChangeWithDef(sEmy15AnimDefs, &w->anim, 0, 0, w->tiles);

        if (AnimIsFinished(&work->anim)) {
            work->state = 0x13;
            work->stateTimer = 0x1E;
        }
        break;
    case 0x13:
        AnimChangeWithDef(sEmy15AnimDefs, &w->anim, 1, 0, w->tiles);

        if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
            ApproachValueHalfSteps(&act->x, act->originX - 0x5000, work->stateTimer);
        } else {
            ApproachValueHalfSteps(&act->x, act->originX + 0x5000, work->stateTimer);
        }

        work->stateTimer--;

        if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                ? ApplyAttackBox(0xB5, act->x - 0x1400, act->y, act->z, 5, 5, 4)
                : ApplyAttackBox(0xB5, act->x + 0x1400, act->y, act->z, 5, 5, 4)) {
            m4aSongNumStart(SONG_BTL_HANE_HIT);
        }

        if (work->stateTimer <= 0) {
            work->state = 0x14;
            work->stateTimer = 0;
        }
        break;
    case 0x14:
        AnimChangeWithDef(sEmy15AnimDefs, &w->anim, 2, 0, w->tiles);

        if (AnimIsFinished(&work->anim)) {
            EmyReturnToIdle(work);
        }
        break;
    case 0x15:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sEmy15AnimDefs, &w->anim, 3, 0, w->tiles);
            work->vz = -0x533;
        }

        if (work->stateTimer > 5) {
            work->state = 0x16;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }
        break;
    case 0x16:
        AnimChangeWithDef(sEmy15AnimDefs, &w->anim, 4, 0, w->tiles);
        EmyLungeAttack(work, 0x16, 0x16, 0x3C, 0xB6, 0x40, SONG_BTL_MON_HIT02, 0x10, -0x0C, 0x0C);
        break;
    }

    return _0800CDF0(work);
}

void task_emy_15_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_15_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_16_0(Emy16Work* work, void* obj) {
    EmyInit(&work->base, &sEmy16Def, obj);
    work->pTask = 0;
    work->bTask = 0;
    TaskPoolInit(&work->tasks, 2);
}

u8 task_emy_16_1(Emy16Work* work) {
    Emy16Work* w;
    BtlObj* act;
    EmySpawn spawn;
    u16 r;

    w = work;
    act = &work->base.actor;

    if (_0800CBDC(&work->base)) {
        if (IsTaskActiveNamed(work->bTask, sTaskDescEmy16B.name)) {
            work->base.state = 0x12;
        } else {
            r = GetRandom();

            switch (r & 1) {
            case 0:
                work->base.state = 0x12;
                break;
            case 1:
                work->base.state = 0x13;
                break;
            }
        }

        w->pTaskStarted = 0;
    }

    switch (work->base.state) {
    case 0x12:
        AnimChangeWithDef(sEmy16AnimDefs, &w->base.anim, 0, 0, w->base.tiles);

        if (AnimGetFrame(&work->base.anim) == 3 && work->base.anim.timer == 0) {
            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                spawn.x = act->x - 0x1000;
                spawn.y = act->y;
                spawn.z = act->z - 0x1000;
                spawn.unk_12 = 1;
            } else {
                spawn.x = act->x + 0x1000;
                spawn.y = act->y;
                spawn.z = act->z - 0x1000;
                spawn.unk_12 = 0;
            }

            w->pTask = TaskCreate(&w->tasks, &sTaskDescEmy16P, &spawn);
            w->pTaskStarted = 1;
        }

        if (w->pTaskStarted != 0) {
            if (!IsTaskActiveNamed(w->pTask, sTaskDescEmy16P.name)) {
                EmyReturnToIdle(&work->base);
            }
        }
        break;
    case 0x13:
        AnimChangeWithDef(sEmy16AnimDefs, &w->base.anim, 1, 0, w->base.tiles);

        if (AnimGetFrame(&work->base.anim) == 0x0A && work->base.anim.timer == 0) {
            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                spawn.x = act->x - 0xC00;
                spawn.y = act->y;
                spawn.z = act->z - 0x200;
                spawn.unk_12 = 1;
            } else {
                spawn.x = act->x + 0xC00;
                spawn.y = act->y;
                spawn.z = act->z - 0x200;
                spawn.unk_12 = 0;
            }

            w->bTask = TaskCreate(&w->tasks, &sTaskDescEmy16B, &spawn);
        }

        if (AnimIsFinished(&work->base.anim)) {
            EmyReturnToIdle(&work->base);
        }
        break;
    }

    TaskPoolUpdate(&w->tasks);
    return _0800CDF0(&work->base);
}

void task_emy_16_2(Emy16Work* work) {
    EmyDraw(&work->base);
    TaskPoolDraw(&work->tasks);
}

void task_emy_16_3(Emy16Work* work) {
    EmyReleaseResources(&work->base);
    TaskPoolDestroy(&work->tasks);
}

void task_emy_16_b_0(Emy16bWork* work, EmySpawn* spawn) {
    if (spawn->unk_12 != 0) {
        work->facingLeft = 1;
    } else {
        work->facingLeft = 0;
    }

    work->palette = LoadObjPalette(gEmy16Palette, 0x20);
    work->tiles = AllocObjTiles(0x80, gEmy1611bTiles);
    AnimInit(&work->anim, gEmy1611bAnims, gEmy1611bFrames);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->state = 0;
    work->x = spawn->x;
    work->y = spawn->y;
    work->z = spawn->z;
    work->vx = 0x200;
    work->vz = -0x34C;
    work->timer = 0;
    work->visible = 1;
    work->bounced = 0;
    ColliderInit(&work->collider, 0x0C, 4, 3);
    ColliderSetDisabled(&work->collider, 1);
}

u8 task_emy_16_b_1(Emy16bWork* work) {
    switch (work->state) {
    case 0:
        if (work->facingLeft != 0) {
            work->x -= work->vx;
        } else {
            work->x += work->vx;
        }

        if (ClampBattlePosition(&work->x, &work->y, -0x10, 0) != 0) {
            work->vx = -work->vx;
        }

        if (work->bounced == 0
                && TestAttackBox(work->x, work->y, work->z, 4, 4, 4)) {
            work->vx = -(work->vx >> 1);
            work->bounced = 1;
        }

        if (work->z >= 0) {
            work->state = 1;
            work->timer = 0;
        }
        break;
    case 1:
        if (work->timer == 0) {
            ColliderSetDisabled(&work->collider, 0);
            AnimStart(&work->anim, 1, ANIM_FLAG_LOOP);
        }

        if (work->collider.colliding != 0) {
            work->timer = 0;
            work->state = 2;
            ColliderSetDisabled(&work->collider, 1);
        } else if (work->timer > 0x64) {
            work->timer = 0;
            work->state = 3;
        } else {
            work->timer++;
        }
        break;
    case 2:
        if (work->timer != 0) {
            if (work->z >= 0) {
                work->timer = 0;
                work->state = 3;
                break;
            }
        } else {
            AnimStart(&work->anim, 2, ANIM_FLAG_LOOP);
            work->vz = -0x3CC;
        }

        work->timer++;
        break;
    case 3:
        if ((work->timer & 3) == 0) {
            work->visible = work->visible == 0;
        }

        if (work->collider.colliding != 0) {
            work->timer = 0;
            work->state = 2;
            ColliderSetDisabled(&work->collider, 1);
            work->visible = 1;
        } else if (work->timer > 0x3C) {
            return 0;
        } else {
            work->timer++;
        }
        break;
    }

    work->z += work->vz;
    work->vz += 0x33;

    if (work->z >= 0) {
        work->vz = 0;
        work->z = 0;
    }

    ColliderSetPosition(&work->collider, work->x, work->y, work->z);
    AnimUpdate(&work->anim);
    return 1;
}

void task_emy_16_b_2(Emy16bWork* work) {
    void* gfx;
    u16 pri;
    ObjAffine* affine;
    s32 angle;
    s16 x;
    s16 y;

    gfx = AnimGetGfx(&work->anim);

    if (work->visible != 0) {
        pri = GetBattleSpritePriorityFlags(work->y);
        WorldToScreen(&x, &y, work->x, work->y, work->z);
        angle = gBtlWork->scale;

        if (angle == 0x100) {
            affine = 0;

            if (work->facingLeft == 0) {
                pri |= 1;
            }
        } else if (work->facingLeft == 0) {
            affine = AllocObjAffine(0, -angle, angle, 1);
        } else {
            affine = AllocObjAffine(0, angle, angle, 1);
        }

        DrawSprite(x, y, gfx, work->tiles, work->palette, affine, pri,
            -0x1004 - (work->y >> 8) * 4);
    }
}

void task_emy_16_b_3(Emy16bWork* work) {
    ColliderUnregister(&work->collider);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void task_emy_16_p_0(Emy16pWork* work, EmySpawn* spawn) {
    if (spawn->unk_12 != 0) {
        work->facingLeft = 1;
    } else {
        work->facingLeft = 0;
    }

    work->palette = LoadObjPalette(gEmy16Palette, 0x20);
    work->tiles = AllocObjTiles(0x80, gEmy1610bTiles);
    AnimInit(&work->anim, gEmy1610bAnims, gEmy1610bFrames);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->x = spawn->x;
    work->y = spawn->y;
    work->z = spawn->z;
    work->vz = 0;
}

u8 task_emy_16_p_1(Emy16pWork* work) {
    if ((gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_ACTION) == 0) {
        return 0;
    }

    if (work->facingLeft != 0) {
        work->x -= 0x400;
    } else {
        work->x += 0x400;
    }

    if (ApplyAttackBox(0xB7, work->x, work->y, work->z, 4, 4, 4) != 0) {
        m4aSongNumStart(SONG_BTL_BW_PACHIN);
    }

    if (ClampBattlePosition(&work->x, &work->y, 0x10, 0) != 0) {
        return 0;
    }

    work->z += work->vz;
    work->vz += 0x2E;

    if (work->z >= 0) {
        work->vz = -0x400;
        work->z = 0;
    }

    AnimUpdate(&work->anim);
    return 1;
}

void task_emy_16_p_2(Emy16pWork* work) {
    void* gfx;
    u16 pri;
    s16 x;
    s16 y;

    gfx = AnimGetGfx(&work->anim);
    pri = GetBattleSpritePriorityFlags(work->y);
    WorldToScreen(&x, &y, work->x, work->y, work->z);
    DrawSprite(x, y, gfx, work->tiles, work->palette, 0, pri,
        -0x1004 - ((work->y + 0x1000) >> 8) * 4);
}

void task_emy_16_p_3(Emy16pWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void task_emy_18_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmy18Def, obj);
    work->actor.z = (GetRandom() % 0x1001) - 0x3000;
    work->idleState = 7;
}

u8 task_emy_18_1(Emy18Work* work) {
    Emy18Work* w;
    BtlObj* act;
    u16 r;

    w = work;
    act = &work->base.actor;

    if (_0800CBDC(&work->base)) {
        r = GetRandom();

        switch (r & 1) {
        case 0:
            work->base.state = 18;
            break;
        case 1:
            work->base.state = 19;
            break;
        }

        w->unk_184 = 0xEFFF;
    }

    if (work->base.state == 8) {
        work->base.state = 20;
        work->base.stateTimer = 0;
    }

    switch (work->base.state) {
    case 20:
        AnimChangeWithDef(sEmy18AnimDefs, &w->base.anim, 2, 0, w->base.tiles);
        work->base.vz = 0;

        if (AnimGetFrame(&work->base.anim) == 5) {
            work->base.angle = GetAngle(act->x, act->y, work->base.x,
                work->base.y);
            work->base.speed = work->base.def->speed;
            act->x += gSineTable[work->base.angle] * work->base.speed >> 8;
            act->y += -gSineTable[work->base.angle + 64] * work->base.speed
                >> 8;
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 22;
        }
        break;
    case 22:
        work->base.vz = 0;
        AnimChangeWithDef(w->base.def->animDef, &w->base.anim, 2, ANIM_FLAG_LOOP | ANIM_FLAG_RANDOM_START,
            w->base.tiles);

        if (gBtlWork->flags & BTL_FLAG_ENEMY_MOVE_ENABLED) {
            if (act->x > work->base.x) {
                act->flags |= BTLOBJ_FLAG_FACING_LEFT;
            } else {
                act->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
            }

            work->base.angle = GetAngle(act->x, act->y, work->base.x,
                work->base.y);
            work->base.speed = work->base.def->speed;
            act->x += gSineTable[work->base.angle] * work->base.speed >> 8;
            act->y += -gSineTable[work->base.angle + 64] * work->base.speed
                >> 8;
            act->z += (work->base.hoverZ - act->z) >> 3;

            if ((work->base.flags & 2) ||
                    ((act->x - work->base.x >= 0
                    ? act->x - work->base.x <= 0xFFF
                    : work->base.x - act->x <= 0xFFF) &&
                    (act->y - work->base.y >= 0
                        ? act->y - work->base.y <= 0xFFF
                        : work->base.y - act->y <= 0xFFF))) {
                work->base.state = 21;
                work->base.stateTimer = 0;
                break;
            }

            work->base.stateTimer++;
        }
        break;
    case 21:
        AnimChangeWithDef(sEmy18AnimDefs, &w->base.anim, 3, 0, w->base.tiles);
        work->base.vz = 0;
        act->x += gSineTable[work->base.angle] * work->base.speed >> 8;
        act->y += -gSineTable[work->base.angle + 64] * work->base.speed >> 8;
        work->base.speed -= 25;

        if (work->base.speed < 0) {
            work->base.speed = 0;
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 7;
        }
        break;
    case 18:
        AnimChangeWithDef(sEmy18AnimDefs, &w->base.anim, 0, 0, w->base.tiles);

        if (work->base.stateTimer <= 29) {
            work->base.vz = 0;
            act->z += (-0x3500 - act->z) >> 3;
        } else if (work->base.stateTimer == 30) {
            work->base.vz = 0x300;
        }

        if (EmyLungeAttack(&work->base, 30, 10, 6, 185, 32, SONG_BTL_MON_HIT02, 24, -10, 16)
                == 1) {
            w->unk_184 = work->base.stateTimer;
        }
        break;
    case 19:
        AnimChangeWithDef(sEmy18AnimDefs, &w->base.anim, 1, 0, w->base.tiles);

        if (work->base.anim.timer == 0) {
            switch (AnimGetFrame(&work->base.anim)) {
            case 0:
                work->base.vz = 0x300;
                break;
            case 3:
                work->base.vz = -0x600;
                break;
            }
        }

        if (EmyLungeAttack(&work->base, 21, 8, 7, 186, 32, SONG_BTL_MON_HIT00, 16, -30, 16)
                == 1) {
            w->unk_184 = work->base.stateTimer;
        }
        break;
    }

    return _0800CDF0(&work->base);
}

void task_emy_18_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_18_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_19_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmy19Def, obj);
}

u8 task_emy_19_1(Emy19Work* work) {
    Emy19Work* w;
    BtlObj* act;
    s32 pos;
    s32 d;

    w = work;
    act = &work->base.actor;

    if (_0800CBDC(&work->base)) {
        GetEnemyTargetPosition(act, &pos, 0, 0);
        d = act->x - pos;

        if (d >= 0 ? d <= 0x3BFF : pos - act->x <= 0x3BFF) {
            work->base.state = 0x17;
        } else {
            work->base.state = 0x12;
        }

        w->dashSpeed = 0;
    }

    switch (work->base.state) {
    case 0x12:
        AnimChangeWithDef(sEmy19AnimDefs, &w->base.anim, 0, 0, w->base.tiles);

        if (AnimIsFinished(&work->base.anim)) {
            work->base.state = 0x13;
            work->base.stateTimer = 0;
        }
        break;
    case 0x13:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sEmy19AnimDefs, &w->base.anim, 1, 0, w->base.tiles);
            work->base.vz = -0x500;
            w->dashSpeed = 0x500;
        }

        act->x = act->flags & BTLOBJ_FLAG_FACING_LEFT ? act->x - w->dashSpeed : act->x + w->dashSpeed;
        w->dashSpeed = w->dashSpeed * 248 >> 8;

        if (AnimIsFinished(&work->base.anim)) {
            work->base.state = 0x14;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 0x14:
        AnimChangeWithDef(sEmy19AnimDefs, &w->base.anim, 2, ANIM_FLAG_LOOP, w->base.tiles);
        act->x = act->flags & BTLOBJ_FLAG_FACING_LEFT ? act->x - w->dashSpeed : act->x + w->dashSpeed;
        w->dashSpeed = w->dashSpeed * 248 >> 8;

        if (act->z >= act->groundZ) {
            work->base.vz = -0x500;
        }

        if (ApplyAttackBox(0xBB, act->x, act->y, act->z, 10, 10, 10) != 0) {
            m4aSongNumStart(SONG_BTL_MON_SWORD03);
            w->dashSpeed = -w->dashSpeed;
            work->base.vz = -0x500;
        }

        if (work->base.stateTimer > 55) {
            work->base.state = 0x15;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 0x15:
        AnimChangeWithDef(sEmy19AnimDefs, &w->base.anim, 3, 0, w->base.tiles);
        act->x = act->flags & BTLOBJ_FLAG_FACING_LEFT ? act->x - w->dashSpeed : act->x + w->dashSpeed;
        w->dashSpeed = w->dashSpeed * 248 >> 8;

        if (act->z >= act->groundZ) {
            work->base.state = 0x16;
            work->base.stateTimer = 0;
        }
        break;
    case 0x16:
        AnimChangeWithDef(sEmy19AnimDefs, &w->base.anim, 0, 0, w->base.tiles);

        if (AnimIsFinished(&work->base.anim)) {
            EmyReturnToIdle(&work->base);
        }
        break;
    case 0x17:
        AnimChangeWithDef(sEmy19AnimDefs, &w->base.anim, 4, 0, w->base.tiles);

        switch (AnimGetFrame(&work->base.anim)) {
        case 3:
            if (work->base.anim.timer == 0) {
                w->dashSpeed = 0x400;
            }
            break;
        case 4:
            if (work->base.anim.timer == 0) {
                w->dashSpeed = 0;
            }

            if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                    ? ApplyAttackBox(0xBC, act->x - 0x1000, act->y, act->z, 16, 16, 32) != 0
                    : ApplyAttackBox(0xBC, act->x + 0x1000, act->y, act->z, 16, 16, 32) != 0) {
                m4aSongNumStart(SONG_BTL_MON_SWORD02);
            }
            break;
        }

        act->x = act->flags & BTLOBJ_FLAG_FACING_LEFT ? act->x - w->dashSpeed : act->x + w->dashSpeed;
        w->dashSpeed = w->dashSpeed * 240 >> 8;

        if (AnimIsFinished(&work->base.anim)) {
            EmyReturnToIdle(&work->base);
        }
        break;
    }

    return _0800CDF0(&work->base);
}

void task_emy_19_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_19_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_21_0(Emy21Work* work, void* obj) {
    EmyInit(&work->base, &sEmy21Def, obj);
    work->dashSpeed = 0;
}

u8 task_emy_21_1(Emy21Work* work) {
    Emy21Work* w;
    BtlObj* act;
    s32 pos;
    s32 d;

    w = work;
    act = &work->base.actor;

    if (_0800CBDC(&work->base)) {
        GetEnemyTargetPosition(act, &pos, 0, 0);
        d = pos - act->x;

        if (d >= 0 ? d <= 0x3FFF : act->x - pos <= 0x3FFF) {
            work->base.state = 0x12;
        } else {
            work->base.state = 0x14;
        }
    } else if (work->base.state == 5 && work->base.stateTimer == 0) {
        m4aSongNumStop(SONG_EF_TARU_BOMB);
    }

    switch (work->base.state) {
    case 0x12:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sEmy21AnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP, w->base.tiles);
        }

        if (work->base.stateTimer > 29) {
            work->base.stateTimer = 0;
            work->base.state = 0x13;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 0x13: {
        u16 t;

        t = work->base.stateTimer;

        if (t >= 12 && t <= 39) {
            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                ApplyAttackBox(0xBD, act->x, act->y, act->z, 30, 30, 32);
            } else {
                ApplyAttackBox(0xBD, act->x, act->y, act->z, 30, 30, 32);
            }
        }

        switch (work->base.stateTimer) {
        case 2:
            MakeOpponentsHittable();
            BgFxStartExplosion(work->base.actor.x, work->base.actor.y,
                work->base.actor.z - 0x1000);
            break;
        case 40:
            ClearBtlObjActionFlags(act);
            return 0;
        }

        work->base.stateTimer++;
        break;
    }
    case 0x14:
        AnimChangeWithDef(sEmy21AnimDefs, &w->base.anim, 1, 0, w->base.tiles);

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 0x15;
        }
        break;
    case 0x15:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sEmy21AnimDefs, &w->base.anim, 2, ANIM_FLAG_LOOP, w->base.tiles);
            w->dashSpeed = 0;
        }

        act->x = act->flags & BTLOBJ_FLAG_FACING_LEFT ? act->x - w->dashSpeed : act->x + w->dashSpeed;
        w->dashSpeed += 43;

        if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
            ? ApplyAttackBox(0xBE, act->x, act->y, act->z, 20, 32, 32)
            : ApplyAttackBox(0xBE, act->x, act->y, act->z, 20, 32, 32)) {
            work->base.stateTimer = 0;
            work->base.state = 0x13;
        } else if (work->base.stateTimer > 28) {
            work->base.stateTimer = 0;
            work->base.state = 0x16;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 0x16:
        AnimChangeWithDef(sEmy21AnimDefs, &w->base.anim, 3, 0, w->base.tiles);

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 0x13;
            break;
        }

        if (work->base.anim.timer == 0) {
            switch (AnimGetFrame(&work->base.anim)) {
            case 0:
            case 1:
                act->x -= 0x380;
                act->y += 0x80;
                break;
            case 2:
                act->x -= 0x680;
                act->y += 0x280;
                break;
            case 3:
                act->x -= 0x500;
                act->y += 0x280;
                break;
            case 4:
                act->x -= 0x580;
                act->y += 0xC0;
                break;
            case 5:
                act->x -= 0x280;
                act->y += 0x3C0;
                break;
            case 6:
                act->x -= 0x180;
                break;
            case 7:
                act->x += 0x80;
                act->y += 0x40;
                break;
            }
        }

        act->x = act->flags & BTLOBJ_FLAG_FACING_LEFT ? act->x - w->dashSpeed : act->x + w->dashSpeed;
        w->dashSpeed -= 46;

        if (w->dashSpeed < 0) {
            w->dashSpeed = 0;
        }

        work->base.stateTimer++;
        break;
    }

    return _0800CDF0(&work->base);
}

void task_emy_21_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_21_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_22_0(Emy22Work* work, void* obj) {
    EmyInit(&work->base, &sEmy22Def, obj);
    work->base.idleState = 7;
    work->counterPending = 0;
}

u8 task_emy_22_1(Emy22Work* work) {
    Emy22Work* w;
    BtlObj* act;
    s32 pos;
    s32 pos2;
    s32 pos3;

    w = work;
    act = &work->base.actor;

    if (_0800CBDC(&work->base)) {
        if (act->hp < act->maxHp) {
            work->base.state = 20;
        } else {
            work->base.state = 21;
        }
    }

    switch (work->base.state) {
    case 1:
        if (work->base.stateTimer == 0) {
            w->counterPending = 1;
        }
        break;
    case 7:
        if (w->counterPending != 0 && work->base.stateTimer == 0) {
            work->base.state = 18;
            work->base.stateTimer = 0;
            w->counterPending = 0;
        }
        break;
    case 18:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(w->base.def->animDef, &w->base.anim, 0, ANIM_FLAG_LOOP,
                w->base.tiles);
            act->flags |= (BTLOBJ_FLAG_INTANGIBLE | BTLOBJ_FLAG_CARD_USE_BLOCKED);
            work->base.steps = 20;
            work->base.stateTimer = 1;
        }

        work->base.vz = 0;

        if (work->base.steps > 0) {
            ApproachValue(&work->base.scaleX, 25, work->base.steps);

            if (--work->base.steps > 0) {
                break;
            }
        }

        work->base.state = 19;
        work->base.stateTimer = 0;
        break;
    case 19:
        if (work->base.stateTimer == 0) {
            GetEnemyTargetPosition(act, &pos, 0, 0);
            AnimChangeWithDef(w->base.def->animDef, &w->base.anim, 0, ANIM_FLAG_LOOP,
                w->base.tiles);

            if (act->x > pos) {
                act->flags |= BTLOBJ_FLAG_FACING_LEFT;
            } else {
                act->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
            }

            act->x = (gBtlWork->xMin
                + GetRandom() % (gBtlWork->xMax - gBtlWork->xMin + 1))
                << 8;
            act->y = (gBtlWork->yMin
                + GetRandom() % (gBtlWork->yMax - gBtlWork->yMin + 1))
                << 8;
            act->z = gBtlWork->targetZ;
            work->base.scaleX = 25;
            work->base.steps = 20;
            work->base.stateTimer = 1;
            m4aSongNumStart(SONG_BTL_WARPIN);
        }

        work->base.vz = 0;

        if (work->base.steps > 0) {
            ApproachValue(&work->base.scaleX, 0x100, work->base.steps);

            if (--work->base.steps > 0) {
                break;
            }
        }

        act->flags &= ~(BTLOBJ_FLAG_INTANGIBLE | BTLOBJ_FLAG_CARD_USE_BLOCKED);
        work->base.state = work->base.idleState;
        work->base.stateTimer = 0;
        break;
    case 20:
        if (work->base.stateTimer == 0) {
            GetEnemyTargetPosition(act, &pos2, 0, 0);

            if (act->x > pos2) {
                act->flags |= BTLOBJ_FLAG_FACING_LEFT;
            } else {
                act->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
            }
        }

        act->z += -act->z >> 4;
        AnimChangeWithDef(sEmy22AnimDefs, &w->base.anim, 0, 0, w->base.tiles);
        EmyLungeAttack(&work->base, 27, 14, 40, 191, 24, SONG_BTL_MON_HIT00, 24, 0, 24);

        if (gBtlWork->actor->flags & BTLOBJ_FLAG_DAMAGE_PENDING) {
            act->hp += act->maxHp >> 3;

            if (act->hp > act->maxHp) {
                act->hp = act->maxHp;
            }

            CreateBtlPopTask(act, 10);
        }
        break;
    case 21:
        if (work->base.stateTimer == 0) {
            GetEnemyTargetPosition(act, &pos3, 0, 0);

            if (act->x > pos3) {
                act->flags |= BTLOBJ_FLAG_FACING_LEFT;
            } else {
                act->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
            }
        }

        act->z += -act->z >> 4;
        AnimChangeWithDef(sEmy22AnimDefs, &w->base.anim, 1, 0, w->base.tiles);
        EmyLungeAttack(&work->base, 50, 19, 30, 192, 16, SONG_BTL_MON_HIT00, 48, 0, 24);
        break;
    }

    return _0800CDF0(&work->base);
}

void task_emy_22_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_22_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_23_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmy23Def, obj);
    work->idleState = 7;
}

u8 task_emy_23_1(Emy23Work* work) {
    Emy23Work* w;
    BtlObj* act;
    s32 pos;
    s32 d;
    s32 t;

    w = work;
    act = &work->base.actor;

    if (_0800CBDC(&work->base)) {
        GetEnemyTargetPosition(act, &pos, 0, 0);
        d = act->x - pos;

        if (d >= 0 ? d <= 0x31FF : pos - act->x <= 0x31FF) {
            work->base.state = 0x13;
        } else {
            work->base.state = 0x12;
        }
    }

    switch (work->base.state) {
    case 0x12:
        AnimChangeWithDef(sEmy23AnimDefs, &w->base.anim, 0, 0, w->base.tiles);

        switch (AnimGetFrame(&work->base.anim)) {
        case 0:
        case 1:
        case 2:
            work->base.vz = 0;
            act->z += (-0x4000 - act->z) >> 3;
            break;
        case 3:
            if (work->base.anim.timer == 0) {
                GetEnemyTargetPosition(act, &t, 0, 0);
                work->base.vz = 0x200;
                w->targetX = t;
            }
        case 4:
        case 5:
            if (act->z >= act->groundZ) {
                work->base.vz = -0x466;
            }

            act->x += (w->targetX - act->x) >> 4;

            if (ApplyAttackBox(0xC1, act->x, act->y, act->z - 0x1000, 12, 16, 16)) {
                m4aSongNumStart(SONG_BTL_MON_SWORD00);
                work->base.vz = -0x466;
            }
            break;
        }

        if (AnimIsFinished(&work->base.anim)) {
            EmyReturnToIdle(&work->base);
        }
        break;
    case 0x13:
        AnimChangeWithDef(sEmy23AnimDefs, &w->base.anim, 1, 0, w->base.tiles);
        act->z += -act->z >> 2;

        if (AnimGetFrame(&work->base.anim) == 3) {
            if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                    ? ApplyAttackBox(0xC2, act->x - 0x1E00, act->y, act->z,
                        0x10, 0x10, 4)
                    : ApplyAttackBox(0xC2, act->x + 0x1E00, act->y, act->z,
                        0x10, 0x10, 4)) {
                m4aSongNumStart(SONG_BTL_MON_SWORD00);
            }
        }

        if (AnimIsFinished(&work->base.anim)) {
            EmyReturnToIdle(&work->base);
        }
        break;
    }

    return _0800CDF0(&work->base);
}

void task_emy_23_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_23_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_25_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmy25Def, obj);
}

u8 task_emy_25_1(EmyWork* work) {
    EmyWork* w;
    BtlObj* act;
    u16 r;
    s32 dx;
    u16 dy;
    u16 e;
    u16 f;

    w = work;
    act = &work->actor;

    if (_0800CBDC(work)) {
        r = GetRandom();

        switch (r & 1) {
        case 0:
            work->state = 0x12;
            break;
        case 1:
            work->state = 0x13;
            break;
        }
    }

    switch (work->state) {
    case 0x12:
        AnimChangeWithDef(sEmy25AnimDefs, &w->anim, 0, 0, w->tiles);

        if (AnimIsFinished(&work->anim)) {
            EmyReturnToIdle(work);
        } else if (work->anim.timer == 0) {
            dx = 0;
            dy = 0;

            switch (work->anim.frame) {
            case 2:
                dx = 5;
                dy = -1;
                break;
            case 3:
                dx = 5;
                dy = -2;

                if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                        ? ApplyAttackBox(0xC3, act->x - 0x2800, act->y, act->z,
                            0x10, 0x10, 0x20)
                        : ApplyAttackBox(0xC3, act->x + 0x2800, act->y, act->z,
                            0x10, 0x10, 0x20)) {
                    m4aSongNumStart(SONG_BTL_HANE_HIT);
                }
                break;
            case 4:
                dx = 5;
                dy = -1;
                break;
            case 5:
                dx = 6;
                dy = -2;
                break;
            case 6:
                dx = 6;
                dy = -1;
                break;
            case 7:
                dx = 1;
                dy = -1;
                break;
            }

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                act->x -= dx << 8;
            } else {
                act->x += dx << 8;
            }

            act->y -= (s16)dy << 8;
        }
        break;
    case 0x13:
        AnimChangeWithDef(sEmy25AnimDefs, &w->anim, 1, 0, w->tiles);

        if (AnimIsFinished(&work->anim)) {
            EmyReturnToIdle(work);
        } else if (work->anim.timer == 0) {
            e = 0;
            f = 0;

            switch (work->anim.frame) {
            case 8:
                e = 4;
                break;
            case 9:
                e = 2;
                break;
            case 10:
                e = 2;
                f = -1;
                break;
            case 11:
                e = 4;
                break;
            case 12:
                e = 7;
                f = -2;
                break;
            case 13:
                e = 1;
                f = -2;
                break;
            case 26:
                e = -5;
                f = 1;
                break;
            case 27:
                e = -15;
                f = 4;
                break;
            }

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                act->x -= (s16)e << 8;
            } else {
                act->x += (s16)e << 8;
            }

            act->y -= (s16)f << 8;

            if (work->anim.frame >= 8 && work->anim.frame <= 22) {
                if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                        ? ApplyAttackBox(0xC4, act->x, act->y, act->z, 0x30, 0x30,
                            0x20)
                        : ApplyAttackBox(0xC4, act->x, act->y, act->z, 0x30, 0x30,
                            0x20)) {
                    m4aSongNumStart(SONG_BTL_MON_HIT00);
                }
            }
        }
        break;
    }

    return _0800CDF0(work);
}

void task_emy_25_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_25_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_26_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmy26Def, obj);
    work->actor.z = (GetRandom() % 0x1001) - 0x3000;
    work->idleState = 7;
}

u8 task_emy_26_1(EmyWork* work) {
    EmyWork* w;
    BtlObj* act;
    u16 r;
    s32 z;
    s32 x;
    s32 t;
    s32* p;

    w = work;
    act = &work->actor;

    if (_0800CBDC(work)) {
        r = GetRandom();

        switch (r & 1) {
        case 0:
            work->state = 0x12;
            break;
        case 1:
            work->state = 0x13;
            break;
        }
    }

    switch (work->state) {
    case 0x12:
        AnimChangeWithDef(sEmy26AnimDefs, &w->anim, 0, 0, w->tiles);

        switch (AnimGetFrame(&work->anim)) {
        case 3:
            if (work->anim.timer == 0) {
                work->vz = 0x300;
            }
            break;
        case 0:
        case 1:
        case 2:
            work->vz = 0;
            p = &gBtlWork->targetZ;
            t = act->z + 0x3C00;
            act->z += (*p - t) >> 3;
            break;
        }

        EmyLungeAttack(work, 0x20, 0x0C, 0x14, 0xC5, 0x28, SONG_BTL_HANE_HIT, 0x14, 0x0A, 0x0A);
        break;
    case 0x13:
        work->vz = 0;

        switch (work->stateTimer) {
        case 0:
            AnimChangeWithDef(sEmy26AnimDefs, &w->anim, 1, 0, w->tiles);
            work->stateTimer++;
            break;
        case 1:
            if (AnimIsFinished(&work->anim)) {
                z = act->y;

                if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    x = act->x - 0x6400;
                    BgFxStartFire(1, act->x - 0x2600, z, act->z - 0x2000, x, z, 0, 1,
                        0xC6);
                } else {
                    x = act->x + 0x6400;
                    BgFxStartFire(1, act->x + 0x2600, z, act->z - 0x2000, x, z, 0, 0,
                        0xC6);
                }

                work->stateTimer++;
            }
            break;
        case 2:
            AnimChange(&work->anim, 1, 0);

            if (AnimIsFinished(&work->anim)) {
                work->stateTimer++;
            }
            break;
        case 3:
            AnimChange(&work->anim, 1, 0);

            if (AnimIsFinished(&work->anim)) {
                EmyReturnToIdle(work);
            }
            break;
        }
        break;
    }

    return _0800CDF0(work);
}

void task_emy_26_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_26_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_27_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmy27Def, obj);
}

u8 task_emy_27_1(EmyWork* work) {
    EmyWork* w;
    BtlObj* act;
    u16 s;
    s32 d;
    s32 y;
    s32 tx;
    s32 ty;

    w = work;
    act = &work->actor;

    if (_0800CBDC(work)) {
        GetEnemyTargetPosition(act, 0, &y, 0);
        d = act->y - y;

        if (d >= 0 ? d <= 0xFFF : y - act->y <= 0xFFF) {
            work->state = 0x12;
        } else {
            work->state = 0x13;
        }
    }

    switch (work->state) {
    case 0x12:
        AnimChangeWithDef(sEmy27AnimDefs, &w->anim, 0, 0, w->tiles);

        if (AnimGetFrame(&work->anim) == 1 && work->anim.timer == 0) {
            m4aSongNumStart(SONG_BTL_SWORDFLASH);

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                BgFxStartFlash(act->x - 0xC00, act->y, act->z - 0x2200);
            } else {
                BgFxStartFlash(act->x + 0xC00, act->y, act->z - 0x2200);
            }
        }

        EmyLungeAttack(work, 0x3D, 6, 0x14, 0xC8, 0x20, SONG_BTL_MON_SWORD04, 0x28, 0, 0x14);
        break;
    case 0x13:
        AnimChangeWithDef(sEmy27AnimDefs, &w->anim, 1, ANIM_FLAG_LOOP, w->tiles);
        GetEnemyTargetPosition(act, &tx, &ty, 0);

        if (work->stateTimer % 6 == 0) {
            work->angle = GetAngle(act->x, act->y, tx, ty);
        }

        act->x += gSineTable[work->angle];
        act->y -= gSineTable[work->angle + 0x40];

        if (act->x > tx) {
            act->flags |= BTLOBJ_FLAG_FACING_LEFT;
        } else {
            act->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
        }

        s = AnimGetFrame(&work->anim);

        if (s == 2 || s == 5) {
            if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                    ? ApplyAttackBox(0xC7, act->x - 0x1000, act->y, act->z, 0x14,
                        0x14, 0x20)
                    : ApplyAttackBox(0xC7, act->x + 0x1000, act->y, act->z, 0x14,
                        0x14, 0x20)) {
                m4aSongNumStart(SONG_BTL_MON_SWORD03);
            }
        }

        if (work->stateTimer > 0x78) {
            EmyReturnToIdle(work);
        } else {
            work->stateTimer++;
        }
        break;
    }

    return _0800CDF0(work);
}

void task_emy_27_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_27_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_28_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmy28Def, obj);
    work->actor.z = (GetRandom() % 0x1001) - 0x3000;
    work->idleState = 7;
}

u8 task_emy_28_1(Emy28Work* work) {
    Emy28Work* w;
    BtlObj* act;
    u16 r;

    w = work;
    act = &work->base.actor;

    if (_0800CBDC(&work->base)) {
        r = GetRandom();

        switch (r & 1) {
        case 0:
            work->base.state = 18;
            break;
        case 1:
            work->base.state = 19;
            break;
        }

        w->unk_184 = 0xEFFF;
    }

    if (work->base.state == 8) {
        work->base.state = 20;
        work->base.stateTimer = 0;
    }

    switch (work->base.state) {
    case 20:
        AnimChangeWithDef(sEmy28AnimDefs, &w->base.anim, 2, 0, w->base.tiles);
        work->base.vz = 0;

        if (AnimGetFrame(&work->base.anim) == 1) {
            work->base.angle = GetAngle(act->x, act->y, work->base.x,
                work->base.y);
            work->base.speed = work->base.def->speed;
            act->x += gSineTable[work->base.angle] * work->base.speed >> 8;
            act->y += -gSineTable[work->base.angle + 64] * work->base.speed
                >> 8;
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 22;
        }
        break;
    case 22:
        work->base.vz = 0;
        AnimChangeWithDef(w->base.def->animDef, &w->base.anim, 2, ANIM_FLAG_LOOP | ANIM_FLAG_RANDOM_START,
            w->base.tiles);

        if (gBtlWork->flags & BTL_FLAG_ENEMY_MOVE_ENABLED) {
            if (act->x > work->base.x) {
                act->flags |= BTLOBJ_FLAG_FACING_LEFT;
            } else {
                act->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
            }

            work->base.angle = GetAngle(act->x, act->y, work->base.x,
                work->base.y);
            work->base.speed = work->base.def->speed;
            act->x += gSineTable[work->base.angle] * work->base.speed >> 8;
            act->y += -gSineTable[work->base.angle + 64] * work->base.speed
                >> 8;
            act->z += (work->base.hoverZ - act->z) >> 3;

            if ((work->base.flags & 2) ||
                    ((act->x - work->base.x >= 0
                    ? act->x - work->base.x <= 0xFFF
                    : work->base.x - act->x <= 0xFFF) &&
                    (act->y - work->base.y >= 0
                        ? act->y - work->base.y <= 0xFFF
                        : work->base.y - act->y <= 0xFFF))) {
                work->base.state = 21;
                work->base.stateTimer = 0;
                break;
            }

            work->base.stateTimer++;
        }
        break;
    case 21:
        AnimChangeWithDef(sEmy28AnimDefs, &w->base.anim, 3, 0, w->base.tiles);
        work->base.vz = 0;
        act->x += gSineTable[work->base.angle] * work->base.speed >> 8;
        act->y += -gSineTable[work->base.angle + 64] * work->base.speed >> 8;
        work->base.speed -= 25;

        if (work->base.speed < 0) {
            work->base.speed = 0;
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 7;
        }
        break;
    case 18:
        AnimChangeWithDef(sEmy28AnimDefs, &w->base.anim, 0, 0, w->base.tiles);

        if (work->base.anim.timer == 0) {
            switch (AnimGetFrame(&work->base.anim)) {
            case 0:
                work->base.vz = 0x300;
                break;
            case 3:
                work->base.vz = -0x600;
                break;
            }
        }

        if (EmyLungeAttack(&work->base, 22, 10, 20, 201, 32, SONG_BTL_MON_HIT00, 16, -40, 32)
                == 1) {
            w->unk_184 = work->base.stateTimer;
        }
        break;
    case 19:
        AnimChangeWithDef(sEmy28AnimDefs, &w->base.anim, 1, 0, w->base.tiles);

        if (work->base.stateTimer <= 34) {
            work->base.vz = 0;
            act->z += (-0x4000 - act->z) >> 3;
        } else if (work->base.stateTimer == 35) {
            work->base.vz = 0x300;
        }

        if (work->base.anim.timer == 0 && AnimGetFrame(&work->base.anim) == 1) {
            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                BgFxStartFlash(act->x + 0x1000, act->y, act->z - 0x3200);
            } else {
                BgFxStartFlash(act->x - 0x1000, act->y, act->z - 0x3200);
            }

            m4aSongNumStart(SONG_BTL_SWORDFLASH);
        }

        if (EmyLungeAttack(&work->base, 35, 10, 14, 202, 32, SONG_BTL_MON_HIT04, 24, 32, 16)
                == 1) {
            w->unk_184 = work->base.stateTimer;
        }
        break;
    }

    return _0800CDF0(&work->base);
}

void task_emy_28_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_28_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_29_0(Emy29Work* work, void* obj) {
    EmyInit(&work->base, &sEmy29Def, obj);
    work->base.fxScale = 0x180;
    work->base.idleState = 7;
    work->base.flags |= 1;
    work->state = 0;
    work->steps = 0;
}

void Emy29MoveToPose(Emy29Work* work, s16 anim, s16 dx, s16 dy, s16 dz) {
    if (work->steps > 0) {
        AnimChange(&work->base.anim, anim, 0);
        ApproachValue(&work->base.actor.x, work->base.actor.originX + (dx << 8), work->steps);
        ApproachValue(&work->base.actor.y, work->base.actor.originY + (dy << 8), work->steps);
        ApproachValue(&work->base.actor.z, dz << 8, work->steps);
        work->steps--;
    } else {
        work->steps = 8;
        work->state++;
    }
}

u8 task_emy_29_1(Emy29Work* work) {
    Emy29Work* w;
    BtlObj* act;
    s32 pos;
    s32 d;
    s32 a;
    s32 t;
    s16 c;

    w = work;
    act = &work->base.actor;

    if (_0800CBDC(&work->base)) {
        GetEnemyTargetPosition(act, &pos, 0, 0);
        d = act->x - pos;

        if (d >= 0 ? d <= 0x27FF : pos - act->x <= 0x27FF) {
            work->base.state = 0x13;
        } else {
            work->base.state = 0x12;
        }
    }

    switch (work->base.state) {
    case 0x12:
        AnimChangeWithDef(sEmy29AnimDefs, &w->base.anim, 0, 0, w->base.tiles);
        work->base.vz = 0;
        a = -gSineTable[(((u16)work->base.stateTimer * 2) & 0xFF) + 0x40] << 4;
        t = act->z + 0x1000;
        act->z += (a - t) >> 2;

        if (EmyLungeAttack(&work->base, 0x16, 0x64, 0x18, 0xCB, 0xB4, SONG_BTL_KAMITUKI, 0, 0, 0x0C) == 1) {
            EmyReturnToIdle(&work->base);
        }
        break;
    case 0x13:
        c = work->base.stateTimer;

        if (c == 0) {
            AnimChangeWithDef(sEmy29AnimDefs, &w->base.anim, 1, 0, w->base.tiles);
            w->state = 0;
            w->steps = 8;
            work->base.stateTimer++;
            m4aSongNumStart(SONG_BTL_BOYOYON);
        }

        switch (w->state) {
        case 0:
            Emy29MoveToPose(w, 0, -25, 5, -10);
            break;
        case 1:
            Emy29MoveToPose(w, 1, 25, 0, 0);
            break;
        case 2:
            Emy29MoveToPose(w, 2, -20, -5, -22);
            break;
        case 3:
            Emy29MoveToPose(w, 3, 5, -17, -8);
            break;
        case 4:
            Emy29MoveToPose(w, 4, -5, 17, -16);
            break;
        case 5:
            Emy29MoveToPose(w, 5, 0, -17, 0);
            break;
        case 6:
            Emy29MoveToPose(w, 6, 25, 0, -11);
            break;
        case 7:
            Emy29MoveToPose(w, 7, -25, 0, -4);
            break;
        case 8:
            Emy29MoveToPose(w, 8, 0, 0, 0);
            break;
        case 9:
            EmyReturnToIdle(&work->base);
            break;
        }

        if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                ? ApplyAttackBox(0xCC, act->x, act->y, act->z, 0x0C, 0x0C, 0x0C)
                : ApplyAttackBox(0xCC, act->x, act->y, act->z, 0x0C, 0x0C, 0x0C)) {
            m4aSongNumStart(SONG_BTL_MON_HIT01);
        }
        break;
    }

    return _0800CDF0(&work->base);
}

void task_emy_29_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_29_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_30_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmy30Def, obj);
    work->actor.z = (GetRandom() % 0x1001) - 0x3000;
    work->idleState = 7;
}

u8 task_emy_30_1(EmyWork* work) {
    EmyWork* w;
    BtlObj* act;
    s32 x;
    s32 y;
    s32 d;
    u16 r;

    w = work;
    act = &work->actor;
    GetEnemyTargetPosition(act, &x, &y, 0);

    if (_0800CBDC(work)) {
        r = GetRandom();

        switch (r & 1) {
        case 0:
            work->state = 18;
            break;
        case 1:
            work->state = 21;
            break;
        }
    }

    if (work->state == 8) {
        work->state = 24;
        work->stateTimer = 0;
    }

    switch (work->state) {
    case 24:
        AnimChangeWithDef(sEmy30AnimDefs, &w->anim, 0, 0, w->tiles);
        work->vz = 0;

        if (AnimGetFrame(&work->anim) == 1) {
            work->angle = GetAngle(act->x, act->y, work->x, work->y);
            work->speed = work->def->speed;
            act->x += gSineTable[work->angle] * work->speed >> 8;
            act->y += -gSineTable[work->angle + 64] * work->speed >> 8;
        }

        if (AnimIsFinished(&work->anim)) {
            work->stateTimer = 0;
            work->state = 26;
        }
        break;
    case 26:
        work->vz = 0;
        AnimChangeWithDef(w->def->animDef, &w->anim, 2, ANIM_FLAG_LOOP | ANIM_FLAG_RANDOM_START, w->tiles);

        if (gBtlWork->flags & BTL_FLAG_ENEMY_MOVE_ENABLED) {
            if (act->x > work->x) {
                act->flags |= BTLOBJ_FLAG_FACING_LEFT;
            } else {
                act->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
            }

            work->angle = GetAngle(act->x, act->y, work->x, work->y);
            work->speed = work->def->speed;
            act->x += gSineTable[work->angle] * work->speed >> 8;
            act->y += -gSineTable[work->angle + 64] * work->speed >> 8;
            act->z += (work->hoverZ - act->z) >> 3;

            if ((work->flags & 2)
                || ((act->x - work->x >= 0
                        ? act->x - work->x
                        : work->x - act->x) <= 0xFFF
                    && (act->y - work->y >= 0
                        ? act->y - work->y
                        : work->y - act->y) <= 0xFFF)) {
                work->state = 25;
                work->stateTimer = 0;
            } else {
                work->stateTimer++;
            }
        }
        break;
    case 25:
        AnimChangeWithDef(sEmy30AnimDefs, &w->anim, 1, 0, w->tiles);
        work->vz = 0;
        act->x += gSineTable[work->angle] * work->speed >> 8;
        act->y += -gSineTable[work->angle + 64] * work->speed >> 8;
        work->speed -= 25;

        if (work->speed < 0) {
            work->speed = 0;
        }

        if (AnimIsFinished(&work->anim)) {
            work->stateTimer = 0;
            work->state = 7;
        }
        break;
    case 18: {
    s32 currentX;
    s32 targetX;
        AnimChangeWithDef(sEmy30AnimDefs, &w->anim, 2, 0, w->tiles);
        work->vz = 0;
        act->z += (-0x4000 - act->z) >> 3;
        act->y += (y - act->y) >> 3;

        currentX = act->x;
        targetX = x;

        if (currentX < targetX) {
            act->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
            d = currentX + 0x1400;
        } else {
            act->flags |= BTLOBJ_FLAG_FACING_LEFT;
            d = currentX - 0x1400;
        }

        act->x = currentX + ((targetX - d) >> 3);

        if (AnimIsFinished(&work->anim)) {
            work->state = 19;
            work->stateTimer = 0;
        }
        break;
    }
    case 19: {
    s32 currentX;
    s32 targetX;
        AnimChangeWithDef(sEmy30AnimDefs, &w->anim, 3, ANIM_FLAG_LOOP, w->tiles);
        work->vz = 0;
        act->z += (-0x2000 - act->z) >> 3;
        act->y += (y - act->y) >> 4;

        currentX = act->x;
        targetX = x;

        if (currentX < targetX) {
            act->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
            d = currentX + 0x1400;
        } else {
            act->flags |= BTLOBJ_FLAG_FACING_LEFT;
            d = currentX - 0x1400;
        }

        act->x = currentX + ((targetX - d) >> 3);

        if (work->anim.timer == 0) {
            switch (AnimGetFrame(&work->anim)) {
            case 1:
            case 3:
                MakeOpponentsHittable();

                if (ApplyAttackBox(0xCD, act->x, act->y, act->z, 12, 12, 12)) {
                    m4aSongNumStart(SONG_BTL_KAMITUKI);
                }
                break;
            }
        }

        if (work->stateTimer > 100) {
            work->stateTimer = 0;
            work->state = 20;
        } else {
            work->stateTimer++;
        }
        break;
    }
    case 20:
        AnimChangeWithDef(sEmy30AnimDefs, &w->anim, 4, 0, w->tiles);
        work->vz = 0;

        if (AnimIsFinished(&work->anim)) {
            EmyReturnToIdle(work);
        }
        break;
    case 21:
        work->vz = 0;

        if (work->stateTimer == 0) {
            AnimChangeWithDef(sEmy30AnimDefs, &w->anim, 5, 0, w->tiles);

            if (act->x > 0x10000) {
                act->flags |= BTLOBJ_FLAG_FACING_LEFT;
                work->x = gBtlWork->xMax * 256;
            } else {
                act->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
                work->x = gBtlWork->xMin * 256;
            }
        }

        act->x += (work->x - act->x) >> 4;
        act->y += (y - act->y) >> 4;
        act->z += (-0x800 - act->z) >> 4;

        if (AnimIsFinished(&work->anim) && (work->flags & 2)) {
            work->stateTimer = 0;
            work->state = 22;
            work->speed = 0;
        } else {
            work->stateTimer++;
        }
        break;
    case 22:
        AnimChangeWithDef(sEmy30AnimDefs, &w->anim, 6, ANIM_FLAG_LOOP, w->tiles);
        work->vz = 0;
        work->speed += 38;
        act->y += (y - act->y) >> 4;
        act->z += (-0x800 - act->z) >> 4;

        if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
            if (ApplyAttackBox(0xCE, act->x - 0x1400, act->y, act->z, 12, 12, 12)) {
                m4aSongNumStart(SONG_BTL_MON_HIT03);
            }

            act->x -= work->speed;

            if (act->x < (gBtlWork->xMin + 32) * 256) {
                work->state = 23;
                work->stateTimer = 0;
            }
        } else {
            if (ApplyAttackBox(0xCE, act->x + 0x1400, act->y, act->z, 12, 12, 12)) {
                m4aSongNumStart(SONG_BTL_MON_HIT03);
            }

            act->x += work->speed;

            if (act->x > (gBtlWork->xMax - 32) * 256) {
                work->state = 23;
                work->stateTimer = 0;
            }
        }
        break;
    case 23:
        AnimChangeWithDef(sEmy30AnimDefs, &w->anim, 7, 0, w->tiles);
        work->vz = 0;
        work->speed -= 128;

        if (work->speed < 0) {
            work->speed = 0;
        }

        if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
            act->x -= work->speed;
        } else {
            act->x += work->speed;
        }

        if (AnimIsFinished(&work->anim)) {
            EmyReturnToIdle(work);
        }
        break;
    }

    return _0800CDF0(work);
}

void task_emy_30_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_30_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_31_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmy31Def, obj);
    work->idleState = 7;
}

u8 task_emy_31_1(Emy31Work* work) {
    Emy31Work* w;
    BtlObj* act;

    w = work;
    act = &work->base.actor;

    if (_0800CBDC(&work->base)) {
        switch ((u16)(GetRandom() % 3)) {
        case 0:
            work->base.state = 18;
            break;
        case 1:
            work->base.state = 19;
            break;
        case 2:
            work->base.state = 20;
            break;
        }

        w->state = 0;
    }

    switch (work->base.state) {
    case 18: {
        s32 x;
        s32 y;
        work->base.vz = 0;

        switch (w->state) {
        case 0:
            if (work->base.stateTimer == 0) {
                AnimChangeWithDef(sEmy31AnimDefs, &w->base.anim, 0, 0,
                    w->base.tiles);
            }

            if (AnimIsFinished(&work->base.anim)) {
                w->state = 1;
                work->base.stateTimer = 0;
            } else {
                work->base.stateTimer++;
            }
            break;
        case 1:
            if (work->base.stateTimer == 0) {
                AnimStart(&work->base.anim, 1, 0);

                y = act->y;
                if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    x = act->x - 0xC800;
                    BgFxStartFire(1, act->x - 0x4000, y, act->z,
                        x, y, 0, 1, 0xCF);
                } else {
                    x = act->x + 0xC800;
                    BgFxStartFire(1, act->x + 0x4000, y, act->z,
                        x, y, 0, 0, 0xCF);
                }
            }

            if (work->base.stateTimer > 30) {
                w->state = 3;
                work->base.stateTimer = 0;
            } else {
                work->base.stateTimer++;
            }
            break;
        case 3:
            if (work->base.stateTimer == 0) {
                AnimStart(&work->base.anim, 2, 0);
            }

            if (AnimIsFinished(&work->base.anim)) {
                AnimChangeWithDef(w->base.def->animDef, &w->base.anim, 0, ANIM_FLAG_LOOP,
                    w->base.tiles);
            }

            if (BgFxIsActive()) {
                work->base.stateTimer++;
            } else {
                w->state = 0;
                EmyReturnToIdle(&work->base);
            }
            break;
        }
        break;
    }
    case 19: {
        s32 x;
        s32 y;
        work->base.vz = 0;

        switch (w->state) {
        case 0:
            if (work->base.stateTimer == 0) {
                AnimChangeWithDef(sEmy31AnimDefs, &w->base.anim, 1, 0,
                    w->base.tiles);
            }

            if (AnimIsFinished(&work->base.anim)) {
                w->state = 1;
                work->base.stateTimer = 0;
            } else {
                work->base.stateTimer++;
            }
            break;
        case 1:
            if (work->base.stateTimer == 0) {
                AnimStart(&work->base.anim, 1, ANIM_FLAG_LOOP);

                y = act->y;
                if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    x = act->x - 0x6400;
                    BgFxStartBlizzard(1, act->x - 0x4600, y, act->z,
                        x, y, 0, 1, 0xD0);
                } else {
                    x = act->x + 0x6400;
                    BgFxStartBlizzard(1, act->x + 0x4600, y, act->z,
                        x, y, 0, 0, 0xD0);
                }
            }

            if (work->base.stateTimer > 60) {
                w->state = 2;
                work->base.stateTimer = 0;
            } else {
                work->base.stateTimer++;
            }
            break;
        case 2:
            if (work->base.stateTimer == 0) {
                AnimStart(&work->base.anim, 2, 0);
            }

            if (AnimIsFinished(&work->base.anim)) {
                AnimChangeWithDef(w->base.def->animDef, &w->base.anim, 0, ANIM_FLAG_LOOP,
                    w->base.tiles);
            }

            if (BgFxIsActive()) {
                work->base.stateTimer++;
            } else {
                w->state = 0;
                EmyReturnToIdle(&work->base);
            }
            break;
        }
        break;
    }
    case 20:
        work->base.vz = 0;

        switch (w->state) {
        case 0:
            if (work->base.stateTimer == 0) {
                AnimChangeWithDef(sEmy31AnimDefs, &w->base.anim, 2, 0,
                    w->base.tiles);
                GetEnemyTargetPosition(act, &w->targetX, &w->targetY, &w->targetZ);
            }

            if (AnimIsFinished(&work->base.anim)) {
                w->state = 1;
                work->base.stateTimer = 0;
            } else {
                work->base.stateTimer++;
            }
            break;
        case 1:
            if (work->base.stateTimer == 0) {
                AnimStart(&work->base.anim, 1, 0);
                work->base.steps = 0;
            }

            if (AnimIsFinished(&work->base.anim)) {
                if (work->base.steps == 0) {
                    if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                        BgFxStartThunder(1, act->x - 0x1600, act->y,
                            act->z - 0x3C00, w->targetX, w->targetY,
                            w->targetZ, 0xD1);
                    } else {
                        BgFxStartThunder(1, act->x + 0x1600, act->y,
                            act->z - 0x3C00, w->targetX, w->targetY,
                            w->targetZ, 0xD1);
                    }

                    work->base.steps++;
                }

                if (!BgFxIsActive()) {
                    w->state = 2;
                    work->base.stateTimer = 0;
                    break;
                }
            }
            work->base.stateTimer++;
            break;
        case 2:
            if (work->base.stateTimer == 0) {
                AnimStart(&work->base.anim, 2, 0);
            }

            if (AnimIsFinished(&work->base.anim)) {
                w->state = 0;
                EmyReturnToIdle(&work->base);
            } else {
                work->base.stateTimer++;
            }
            break;
        }
        break;
    }

    return _0800CDF0(&work->base);
}

void task_emy_31_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_31_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_37_0(Emy37Work* work, void* obj) {
    EmyInit(&work->base, &sEmy37Def, obj);
    work->base.flags |= 1;
    work->base.idleState = 0x12;
    work->base.state = 0x1C;
    work->rotation = 0;
}

u8 task_emy_37_1(Emy37Work* work) {
    Emy37Work* w;
    BtlObj* act;

    w = work;
    act = &work->base.actor;

    if (_0800CBDC(&work->base)) {
        if (work->base.state == 20) {
            work->rotation = 0;
            act->flags &= ~BTLOBJ_FLAG_INTANGIBLE;
            work->base.state = 25;
            work->base.actor.centerHeight = 20;
        } else {
            work->base.state = 24;
        }
    }

    switch (work->base.state) {
    case 24:
        AnimChangeWithDef(sEmy37AnimDefs, &w->base.anim, 0, 0, w->base.tiles);
        EmyLungeAttack(&work->base, 30, 14, 20, 0xD2, 70, SONG_BTL_MON_HIT00, 0, 0, 24);
        break;
    case 25:
        AnimChangeWithDef(sEmy37AnimDefs, &w->base.anim, 4, 0, w->base.tiles);

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 29;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 29:
        if (work->base.stateTimer == 0) {
            work->base.vz = -0x399;
            AnimChangeWithDef(sEmy37AnimDefs, &w->base.anim, 1, 0, w->base.tiles);
        }

        if (work->base.vz > 0) {
            work->base.vz = 0;
        }

        if (ApplyAttackBox(0xD3, act->x, act->y, act->z, 16, 8, 32)) {
            m4aSongNumStart(SONG_BTL_MON_HIT00);
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 30;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 30:
        if (work->base.stateTimer == 0) {
            s32 x;
            s32 y;

            AnimChangeWithDef(sEmy37AnimDefs, &w->base.anim, 2, ANIM_FLAG_LOOP, w->base.tiles);
            w->speed = 0;
            GetEnemyTargetPosition(act, &x, &y, 0);
            w->angle = GetAngle(act->x, act->y, x, y);
        }

        if (((u16)work->base.stateTimer % 4) == 0) {
            u8 angle;
            s32 x;
            s32 y;

            GetEnemyTargetPosition(act, &x, &y, 0);
            angle = GetAngle(act->x, act->y, x, y);
            ApproachAngle(&w->angle, angle, 4);
        }

        act->x += gSineTable[(u8)w->angle] * (s32)w->speed >> 8;
        act->y += -gSineTable[(u8)w->angle + 64] * (s32)w->speed >> 8;
        w->speed += 12;

        if (ApplyAttackBox(0xD3, act->x, act->y, act->z, 32, 16, 16)) {
            m4aSongNumStart(SONG_BTL_MON_HIT00);
            work->base.stateTimer = 120;
        }

        work->base.vz = 0;

        if (work->base.stateTimer > 120) {
            EmyReturnToIdle(&work->base);
        } else {
            work->base.stateTimer++;
        }
        break;
    case 28:
        AnimChangeWithDef(sEmy37AnimDefs, &w->base.anim, 10, 0, w->base.tiles);

        if (AnimIsFinished(&work->base.anim)) {
            act->flags &= ~BTLOBJ_FLAG_INTANGIBLE;
            EmyFinishSpawn(&work->base);
        } else {
            work->base.stateTimer++;
        }
        break;
    case 19:
        AnimChangeWithDef(sEmy37AnimDefs, &w->base.anim, 9, 0, w->base.tiles);

        if (AnimIsFinished(&work->base.anim)) {
            work->base.state = 20;
            ColliderSetDisabled(&act->collider, 1);
            act->flags |= BTLOBJ_FLAG_INTANGIBLE;
            act->centerHeight = 0;
        }
        break;
    case 20:
        if (gBtlWork->flags & BTL_FLAG_ENEMY_MOVE_ENABLED) {
            s32 x;
            s32 y;
            s32 dx;
            s32 dy;
            s32 sample;
            s32 offset;

            GetEnemyTargetPosition(act, &x, &y, 0);
            AnimChangeWithDef(sEmy37AnimDefs, &w->base.anim, 5, ANIM_FLAG_LOOP, w->base.tiles);
            sample = gSineTable[work->base.angle];
            offset = 70;
            offset *= sample;
            dx = x + offset;
            dy = y + -gSineTable[work->base.angle + 64] * 35;
            dx -= act->x;
            dx >>= 4;
            dy -= act->y;
            dy >>= 4;

            if (dx > 0x300) {
                dx = 0x300;
            } else if (dx < -0x300) {
                dx = -0x300;
            }

            if (dy > 0x300) {
                dy = 0x300;
            } else if (dy < -0x300) {
                dy = -0x300;
            }

            act->x += dx;
            act->y += dy;

            if (work->base.stateTimer == 0) {
                act->flags &= ~BTLOBJ_FLAG_CARD_USE_BLOCKED;
            }

            TryEnemyCardUse(act);

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                work->base.angle -= 2;
                w->rotation = work->base.angle;
            } else {
                work->base.angle += 2;
                w->rotation = -work->base.angle;
            }

            if (work->base.stateTimer > 160) {
                w->rotation = 0;
                work->base.state = 21;
                ColliderSetDisabled(&act->collider, 0);
                act->flags &= ~BTLOBJ_FLAG_INTANGIBLE;
                act->centerHeight = 20;
                act->flags |= BTLOBJ_FLAG_CARD_USE_BLOCKED;
                work->base.stateTimer = 0;
            } else {
                work->base.stateTimer++;
            }
        }
        break;
    case 21:
        AnimChangeWithDef(sEmy37AnimDefs, &w->base.anim, 6, 0, w->base.tiles);

        if (work->base.stateTimer == 30) {
            act->flags &= ~BTLOBJ_FLAG_INTANGIBLE;
        }

        if (AnimIsFinished(&work->base.anim)) {
            act->flags &= ~(BTLOBJ_FLAG_INTANGIBLE | BTLOBJ_FLAG_CARD_USE_BLOCKED);
            work->base.state = 26;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 26:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sEmy37AnimDefs, &w->base.anim, 7, 0, w->base.tiles);
            work->base.vz = -0x433;
        }

        if (work->base.vz > 0) {
            work->base.state = 27;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 27:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sEmy37AnimDefs, &w->base.anim, 8, 0, w->base.tiles);
        }

        if (act->z >= act->groundZ) {
            work->base.state = 18;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 18:
        if (work->base.stateTimer == 0) {
            act->centerHeight = 20;
            ColliderSetDisabled(&act->collider, 0);
            act->flags &= ~(BTLOBJ_FLAG_INTANGIBLE | BTLOBJ_FLAG_CARD_USE_BLOCKED);
            AnimChangeWithDef(w->base.def->animDef, &w->base.anim, 0, ANIM_FLAG_LOOP | ANIM_FLAG_RANDOM_START, w->base.tiles);
        }

        TryEnemyCardUse(act);

        if ((u16)(GetRandom() % 200U) == 0) {
            work->base.state = 4;

            if (GetRandom() % 2 == 0) {
                work->base.x = -((act->attackOffset
                    + (-act->attackRangeX + GetRandom() % (act->attackRangeX - -act->attackRangeX + 1))) * 256);
            } else {
                work->base.x = (act->attackOffset
                    + (-act->attackRangeX + GetRandom() % (act->attackRangeX - -act->attackRangeX + 1))) * 256;
            }
            break;
        } else if ((u16)(GetRandom() % 100U) == 0) {
            work->base.state = 19;
            act->flags |= BTLOBJ_FLAG_CARD_USE_BLOCKED;
            work->base.angle = GetRandom();
            work->base.stateTimer = 0;
            break;
        }

        if ((u16)((u32)GetRandom() % work->base.def->turnInterval) == 0) {
            s32 x;

            GetEnemyTargetPosition(act, &x, 0, 0);

            if (act->x > x) {
                act->flags |= BTLOBJ_FLAG_FACING_LEFT;
            } else {
                act->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
            }
        }

        work->base.stateTimer++;
        break;
    }

    return _0800CDF0(&work->base);
}

void task_emy_37_2(Emy37Work* work) {
    Emy37Work* w;
    BtlObj* act;
    u16 pri;
    ObjAffine* affine;
    s32 rot;
    s32 scale;
    s32 zoom;
    s16 x;
    s16 y;

    w = work;

    if (work->base.visible != 0) {
        act = &work->base.actor;
        pri = GetBattleSpritePriorityFlags(act->y) | work->base.spriteFlags;
        WorldToScreen(&x, &y, act->x, act->y, act->z);

        zoom = work->base.scaleY;

        if (zoom == 0x100) {
            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                scale = gBtlWork->scale;
                rot = scale;
            } else if (work->rotation == 0 && gBtlWork->scale == zoom) {
                scale = zoom;
                rot = scale;
                pri |= 1;
            } else {
                rot = -gBtlWork->scale;
                scale = gBtlWork->scale;
            }
        } else {
            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                rot = gBtlWork->scale * work->base.scaleX >> 8;
                scale = gBtlWork->scale;
            } else {
                rot = -(gBtlWork->scale * work->base.scaleX >> 8);
                scale = gBtlWork->scale;
            }

            scale = scale * zoom >> 8;
        }

        if (w->rotation) {
            affine = AllocObjAffine(w->rotation, rot, scale, 1);
        } else if (scale == 0x100 && rot == scale) {
            affine = 0;
        } else if (scale <= 0xFF) {
            affine = AllocObjAffine(0, rot, scale, 0);
        } else {
            affine = AllocObjAffine(0, rot, scale, 1);
        }

        if (StepHitFlash(act)) {
            DrawSprite(x, y, work->base.gfx, work->base.tiles, work->base.palette2, affine,
                pri, -0x1004 - (act->y >> 8) * 4);
        } else if (work->base.state == 0x14) {
            DrawSprite(x, y, work->base.gfx, work->base.tiles, work->base.palette, affine,
                pri, 0xFFFF);
        } else {
            DrawSprite(x, y, work->base.gfx, work->base.tiles, work->base.palette, affine,
                pri, -0x1004 - (act->y >> 8) * 4);
        }

        TaskPoolDraw(&work->base.tasks);
    }
}

void task_emy_37_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_38_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmy38Def, obj);
}

u8 task_emy_38_1(EmyWork* work) {
    EmyWork* w;
    BtlObj* act;
    u16 r;
    u8 ret;

    w = work;
    act = &work->actor;

    if (_0800CBDC(work)) {
        r = GetRandom();

        switch (r & 1) {
        case 0:
            work->state = 0x12;
            break;
        case 1:
            work->state = 0x13;
            break;
        }
    }

    switch (work->state) {
    case 0x12:
        AnimChangeWithDef(sEmy38AnimDefs, &w->anim, 0, 0, w->tiles);
        EmyLungeAttack(work, 0x1E, 0x14, 0x2D, 0xD4, 0x32, SONG_BTL_MON_HIT01, 0, 0, 0x18);

        if (work->stateTimer == 0x1E) {
            work->vz = -0x300;
        }
        break;
    case 0x13:
        AnimChangeWithDef(sEmy38AnimDefs, &w->anim, 1, 0, w->tiles);

        if (work->stateTimer == 0x3F) {
            ApplyAttackBox(0xD5, act->x, act->y, act->z, 0x100, 0x100, 1);
            m4aSongNumStart(SONG_BTL_LB_RUMB);
            BtlMapStartShake();
        }

        if (AnimIsFinished(&work->anim)) {
            EmyReturnToIdle(work);
        } else {
            work->stateTimer++;
        }
        break;
    }

    ret = _0800CDF0(work);

    if ((gBtlWork->actor->x < work->actor.x && (work->actor.flags & BTLOBJ_FLAG_FACING_LEFT)) ||
            (gBtlWork->actor->x > work->actor.x &&
                !(work->actor.flags & BTLOBJ_FLAG_FACING_LEFT))) {
        work->actor.flags |= BTLOBJ_FLAG_GUARD_PHYSICAL;
    } else {
        work->actor.flags &= ~BTLOBJ_FLAG_GUARD_PHYSICAL;
    }

    return ret;
}

void task_emy_38_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_38_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_39_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmy39Def, obj);
}

u8 task_emy_39_1(Emy39Work* work) {
    Emy39Work* w;
    BtlObj* act;
    u16 r;
    s16 c;
    s32 z;
    s32 x;
    s32 p;
    s32 q;
    u8 ret;

    w = work;
    act = &work->base.actor;

    if (_0800CBDC(&work->base)) {
        r = GetRandom();

        switch (r & 1) {
        case 0:
            work->base.state = 0x12;
            break;
        case 1:
            work->base.state = 0x13;
            break;
        }
    }

    switch (work->base.state) {
    case 0x12:
        AnimChangeWithDef(sEmy39AnimDefs, &w->base.anim, 0, 0, w->base.tiles);

        if (work->base.stateTimer == 0x30) {
            z = act->y;

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                x = act->x - 0x6400;
                BgFxStartFire(0, act->x - 0x4000, z, act->z - 0x2000, x, z, 0, 1,
                    0xD6);
            } else {
                x = act->x + 0x6400;
                BgFxStartFire(0, act->x + 0x4000, z, act->z - 0x2000, x, z, 0, 0,
                    0xD6);
            }
        }

        if (work->base.stateTimer > 0x30 && BgAnimIsStopped()) {
            EmyReturnToIdle(&work->base);
        } else {
            work->base.stateTimer++;
        }
        break;
    case 0x13:
        c = work->base.stateTimer;

        if (c == 0) {
            AnimChangeWithDef(sEmy39AnimDefs, &w->base.anim, 1, 0, w->base.tiles);
            w->dashSpeed = 0;
        }

        switch (AnimGetFrame(&work->base.anim)) {
        case 0:
            p = 24;
            q = 20;
            break;
        case 1:
            p = 30;
            q = 16;
            break;
        case 2:
            p = 24;
            q = 20;

            if (work->base.anim.timer == 0) {
                w->dashSpeed = 0x200;
            }
            break;
        case 3:
            p = 24;
            q = 16;
            break;
        case 4:
            p = 48;
            q = 20;
            break;
        case 5:
            p = 30;
            q = 16;

            if (work->base.anim.timer == 0) {
                w->dashSpeed = 0x200;
            }
            break;
        case 6:
            p = 48;
            q = 20;
            break;
        case 7:
        default:
            p = 24;
            q = 20;
            break;
        }

        if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
            act->x -= w->dashSpeed;
        } else {
            act->x += w->dashSpeed;
        }

        w->dashSpeed -= 0x19;

        if (w->dashSpeed < 0) {
            w->dashSpeed = 0;
        }

        if (ApplyAttackBox(0xD7, act->x, act->y, act->z, p, q, 0x28)) {
            m4aSongNumStart(SONG_BTL_MON_HIT02);
        }

        if (AnimIsFinished(&work->base.anim)) {
            EmyReturnToIdle(&work->base);
        } else {
            work->base.stateTimer++;
        }
        break;
    }

    ret = _0800CDF0(&work->base);

    if ((gBtlWork->actor->x < work->base.actor.x
                && (work->base.actor.flags & BTLOBJ_FLAG_FACING_LEFT))
            || (gBtlWork->actor->x > work->base.actor.x
                && !(work->base.actor.flags & BTLOBJ_FLAG_FACING_LEFT))) {
        work->base.actor.flags |= BTLOBJ_FLAG_GUARD_PHYSICAL;
    } else {
        work->base.actor.flags &= ~BTLOBJ_FLAG_GUARD_PHYSICAL;
    }

    return ret;
}

void task_emy_39_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_39_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_41_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmy41Def, obj);
    work->idleState = 7;
}

u8 task_emy_41_1(Emy41Work* work) {
    Emy41Work* w;
    BtlObj* act;
    u16 r;
    s32 t;
    s32 a;

    w = work;
    act = &work->base.actor;

    if (_0800CBDC(&work->base)) {
        r = GetRandom();

        switch (r & 1) {
        case 0:
            work->base.state = 0x12;
            break;
        case 1:
            work->base.state = 0x13;
            break;
        }
    }

    switch (work->base.state) {
    case 0x12:
        AnimChangeWithDef(sEmy41AnimDefs, &w->base.anim, 0, 0, w->base.tiles);
        work->base.vz = 0;
        a = gSineTable[((u16)work->base.stateTimer * 4) & 0xFF] << 4;
        t = act->z + 0x1000;
        act->z += (a - t) >> 2;
        EmyLungeAttack(&work->base, 0x14, 0x63, 0x1E, 0xD8, 0x40, SONG_BTL_MON_HIT02, 0, -0x10, 0x2C);
        break;
    case 0x13:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sEmy41AnimDefs, &w->base.anim, 1, 0, w->base.tiles);
            GetEnemyTargetPosition(act, &w->targetX, &w->targetY, 0);
            w->targetZ = 0;
        }

        if (AnimGetFrame(&work->base.anim) == 4 && work->base.anim.timer == 0) {
            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                BgFxStartThunder(1, act->x - 0x2C00, act->y, act->z, w->targetX,
                    w->targetY, w->targetZ, 0xD9);
            } else {
                BgFxStartThunder(1, act->x + 0x2C00, act->y, act->z, w->targetX,
                    w->targetY, w->targetZ, 0xD9);
            }
        }

        if (AnimIsFinished(&work->base.anim)) {
            EmyReturnToIdle(&work->base);
        } else {
            work->base.stateTimer++;
        }
        break;
    }

    return _0800CDF0(&work->base);
}

void task_emy_41_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_41_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_44_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmy44Def, obj);
}

u8 task_emy_44_1(EmyWork* work) {
    EmyWork* w;
    BtlObj* act;
    s32 pos;
    s32 d;
    u8 ret;

    w = work;
    act = &work->actor;

    if (_0800CBDC(work)) {
        GetEnemyTargetPosition(act, &pos, 0, 0);
        d = act->x - pos;

        if (d >= 0 ? d <= 0x4FFF : pos - act->x <= 0x4FFF) {
            work->state = 0x12;
        } else {
            work->state = 0x13;
        }
    }

    switch (work->state) {
    case 0x12:
        AnimChangeWithDef(sEmy44AnimDefs, &w->anim, 0, 0, w->tiles);

        switch (AnimGetFrame(&work->anim)) {
        case 1:
        case 2:
        case 3:
        case 4:
            if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                    ? ApplyAttackBox(0xDA, act->x - 0x2000, act->y, act->z, 0x20,
                        0x10, 0x28)
                    : ApplyAttackBox(0xDA, act->x + 0x2000, act->y, act->z, 0x20,
                        0x10, 0x28)) {
                m4aSongNumStart(SONG_BTL_DF_HIT);
            }
            break;
        }

        if (AnimIsFinished(&work->anim)) {
            EmyReturnToIdle(work);
        }
        break;
    case 0x13:
        AnimChangeWithDef(sEmy44AnimDefs, &w->anim, 1, 0, w->tiles);

        if (AnimGetFrame(&work->anim) == 7 && work->anim.timer == 0) {
            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                BgFxStartFire(1, act->x - 0x4000, act->y, act->z - 0x400,
                    act->x - 0xB400, act->y, act->z - 0x400, 1, 0xDB);
            } else {
                BgFxStartFire(1, act->x + 0x4000, act->y, act->z - 0x400,
                    act->x + 0xB400, act->y, act->z - 0x400, 0, 0xDB);
            }
        }

        if (AnimIsFinished(&work->anim)) {
            EmyReturnToIdle(work);
        }
        break;
    }

    ret = _0800CDF0(work);

    if ((gBtlWork->actor->x < work->actor.x && (work->actor.flags & BTLOBJ_FLAG_FACING_LEFT)) ||
            (gBtlWork->actor->x > work->actor.x &&
                !(work->actor.flags & BTLOBJ_FLAG_FACING_LEFT))) {
        work->actor.flags |= (BTLOBJ_FLAG_GUARD_PHYSICAL | BTLOBJ_FLAG_IMMUNE_FIRE | BTLOBJ_FLAG_IMMUNE_BLIZZARD);
    } else {
        work->actor.flags &= ~(BTLOBJ_FLAG_GUARD_PHYSICAL | BTLOBJ_FLAG_IMMUNE_FIRE | BTLOBJ_FLAG_IMMUNE_BLIZZARD);
    }

    return ret;
}

void task_emy_44_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_44_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_81_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmy81Def, obj);
}

static inline s32 EmyFacingX(BtlObj* actor, s32 offset) {
    return actor->flags & BTLOBJ_FLAG_FACING_LEFT ? actor->x - offset : actor->x + offset;
}

u8 task_emy_81_1(Emy81Work* work) {
    Emy81Work* w;
    BtlObj* act;
    u16 r;
    u16 frame;
    u16 idleFrame;
    s32 d;
    s32 hitX;
    s32 a;
    s32 z;
    s32 b;

    w = work;
    act = &work->base.actor;

    if (_0800CBDC(&work->base)) {
        r = GetRandom();

        switch (r & 1) {
        case 0:
            work->base.state = 18;
            break;
        case 1:
            work->base.state = 19;
            break;
        }
    }

    switch (work->base.state) {
    case 0:
    case 4:
        idleFrame = AnimGetGfxIndex(&work->base.anim);

        if ((idleFrame == 2 || idleFrame == 6) && work->base.anim.timer == 0) {
            work->base.vz = -0x133;
        }

        if (GetRandom() % 200 == 0) {
            work->base.state = 20;
            work->base.stateTimer = 0;
            w->speedX = 0;
        }
        break;
    case 20:
        AnimChangeWithDef(sEmy81AnimDefs, &w->base.anim, 2, 0, w->base.tiles);

        d = (-0x2800 - act->z) >> 4;

        if (d < -w->speedX) {
            w->speedX += 25;
        } else {
            w->speedX = -d;
        }

        work->base.vz = 0;

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 21;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 21:
        if (work->base.stateTimer == 0) {
            GetEnemyTargetPosition(act, &a, &b, 0);
            AnimChangeWithDef(sEmy81AnimDefs, &w->base.anim, 3, ANIM_FLAG_LOOP, w->base.tiles);
            w->targetX = (a * 2) - act->x;
            w->targetY = (b * 2) - act->y;
            w->speedX = 0;
            w->speedY = 0;
        }

        work->base.vz = 0;
        {
            s32 sample = gSineTable[((u16)work->base.stateTimer * 4) & 0xFF] * 10;
            s32 current = act->z;

            z = current + 0x2800;
            act->z = current + ((sample - z) >> 3);
        }

        d = (w->targetX - act->x) >> 4;

        if (d > w->speedX) {
            d = w->speedX;
            w->speedX += 51;
        } else if (d < -w->speedX) {
            d = -w->speedX;
            w->speedX += 51;
        } else {
            w->speedX = d < 0 ? -d : d;
        }

        act->x += d;
        d = (w->targetY - act->y) >> 4;

        if (d > w->speedY) {
            d = w->speedY;
            w->speedY = d + 2;
        } else if (d < -w->speedY) {
            d = -w->speedY;
            w->speedY += 2;
        } else {
            w->speedY = d < 0 ? -d : d;
        }

        act->y += d;

        if ((work->base.flags & 2)
                || ((w->targetX - act->x < 0
                        ? act->x - w->targetX
                        : w->targetX - act->x) <= 0x7FF
                    && (w->targetY - act->y < 0
                        ? act->y - w->targetY
                        : w->targetY - act->y) <= 0x7FF)) {
            work->base.state = 22;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 22:
        AnimChangeWithDef(sEmy81AnimDefs, &w->base.anim, 4, 0, w->base.tiles);
        work->base.vz -= 25;

        if (act->z >= act->groundZ) {
            work->base.state = work->base.idleState;
            work->base.stateTimer = 0;
        }
        break;
    case 18:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sEmy81AnimDefs, &w->base.anim, 0, 0, w->base.tiles);
        }

        {
            s32 currentX;
            s32 targetX;
            s32 adjustedX;

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                targetX = 0x3000;
                currentX = act->x;
                adjustedX = currentX + targetX;
            } else {
                targetX = -0x3000;
                currentX = act->x;
                adjustedX = currentX + targetX;
            }

            targetX = act->originX;
            targetX -= adjustedX;
            targetX >>= 4;
            currentX += targetX;
            act->x = currentX;
        }

        frame = AnimGetFrame(&work->base.anim);

        if (frame >= 3 && frame <= 6) {
            work->base.vz = 0;
        }

        switch (frame) {
        case 1:
            if (work->base.anim.timer == 0) {
                work->base.vz = -0x400;
            }
            break;
        case 3:
            hitX = EmyFacingX(act, 0x1600);

            if (ApplyAttackBox(0xDC, hitX, act->y, act->z + 0x800, 10, 10, 10)) {
                m4aSongNumStart(SONG_BTL_MON_HIT04);
            }
            break;
        }

        if (AnimIsFinished(&work->base.anim)) {
            EmyReturnToIdle(&work->base);
        } else {
            work->base.stateTimer++;
        }
        break;
    case 19:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sEmy81AnimDefs, &w->base.anim, 1, 0, w->base.tiles);
        }

        {
            s32 currentX;
            s32 targetX;
            s32 adjustedX;

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                targetX = 0x4600;
                currentX = act->x;
                adjustedX = currentX + targetX;
            } else {
                targetX = -0x4600;
                currentX = act->x;
                adjustedX = currentX + targetX;
            }

            targetX = act->originX;
            targetX -= adjustedX;
            targetX >>= 4;
            currentX += targetX;
            act->x = currentX;
        }

        frame = AnimGetFrame(&work->base.anim);

        if (frame == 4) {
            s32 centerX = EmyFacingX(act, 0);

            if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                    ? ApplyAttackBox(0xDD, centerX - 0x1800, act->y, act->z,
                        0x10, 0x10, 10)
                    : ApplyAttackBox(0xDD, centerX + 0x1800, act->y, act->z,
                        0x10, 0x10, 10)) {
                m4aSongNumStart(SONG_BTL_MON_HIT00);
            }
        }

        if (AnimIsFinished(&work->base.anim)) {
            EmyReturnToIdle(&work->base);
        } else {
            work->base.stateTimer++;
        }
        break;
    }

    return _0800CDF0(&work->base);
}

void task_emy_81_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_81_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_82_0(Emy82Work* work, void* obj) {
    EmyInit(&work->base, &sEmy82Def, obj);
    work->base.idleState = 0x15;
    work->spawnCount = 0;
}

u8 GetEmyApproachAngle(EmyWork* work) {
    BtlObj* act;
    s32 x;
    s32 y;
    s32 d;
    s32 t;
    s32 lo;
    s32 actorX;
    s32 actorY;
    s32 targetY;

    act = &work->actor;
    GetEnemyTargetPosition(act, &x, &y, 0);

    if (x < (gBtlWork->xMin + 0x30) << 8) {
        d = x + 0x28;
    } else if (x > (gBtlWork->xMax - 0x30) << 8) {
        d = x - 0x28;
    } else {
        t = (work->actor.attackOffset + ((lo = -work->actor.attackRangeX) +
            GetRandom() % (work->actor.attackRangeX - lo + 1))) << 8;

        if (act->x < x) {
            d = x - t;
        } else {
            d = x + t;
        }
    }

    targetY = y;
    actorX = act->x;
    actorY = act->y;
    return GetAngle(actorX, actorY, d, targetY);
}

u8 task_emy_82_1(Emy82Work* work) {
    Emy82Work* w;
    BtlObj* act;

    w = work;
    act = &work->base.actor;
    if (_0800CBDC(&work->base)) {
        switch ((u16)(GetRandom() % 3U)) {
        case 0:
            work->base.state = 18;
            break;
        case 1:
            if (gBtlWork->enemyCount > 1) {
                work->base.state = 19;
            } else {
                work->base.state = 18;
            }
            break;
        case 2:
            work->base.state = 20;
            break;
        }
    }

    switch (work->base.state) {
    case 5:
        if (work->base.stateTimer == 0) {
            m4aSongNumStop(SONG_EF_RAPPA_CALL);
        }
        break;
    case 22:
        AnimChangeWithDef(w->base.def->animDef, &w->base.anim, 2, ANIM_FLAG_LOOP, w->base.tiles);
        if (act->z < act->groundZ && (gBtlWork->flags & BTL_FLAG_ENEMY_MOVE_ENABLED)) {
            act->x += gSineTable[work->base.angle] * work->base.speed >> 8;
            act->y += -gSineTable[work->base.angle + 64] * work->base.speed >> 8;
            if ((u16)((u32)GetRandom() % work->base.def->turnInterval) == 0) {
                s32 x;
                GetEnemyTargetPosition(act, &x, 0, 0);
                if (act->x > x) {
                    act->flags |= BTLOBJ_FLAG_FACING_LEFT;
                } else {
                    act->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
                }
            }
        } else {
            switch (AnimGetFrame(&work->base.anim)) {
            case 6:
                if (work->base.anim.timer > 2 && (u16)(GetRandom() % 15U) == 0) {
                    work->base.state = work->base.idleState;
                }
                break;
            case 1:
                if (work->base.anim.timer == 0) {
                    work->base.angle = GetEmyApproachAngle(&work->base);
                    TryEnemyCardUse(act);
                    work->base.vz = -0x3CC;
                }
                break;
            }
        }
        break;
    case 21:
        AnimChangeWithDef(w->base.def->animDef, &w->base.anim, 0, ANIM_FLAG_LOOP, w->base.tiles);
        if ((u16)((u32)GetRandom() % work->base.def->turnInterval) == 0) {
            s32 x;
            GetEnemyTargetPosition(act, &x, 0, 0);
            if (act->x > x) {
                act->flags |= BTLOBJ_FLAG_FACING_LEFT;
            } else {
                act->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
            }
        }
        switch (AnimGetGfxIndex(&work->base.anim)) {
        case 0:
            if (work->base.anim.timer == 5 && (u16)((u32)GetRandom() % work->base.def->moveInterval) == 0) {
                work->base.state = 22;
                work->base.angle = GetEmyApproachAngle(&work->base);
            }
            break;
        case 2:
            if (work->base.anim.timer == 0 && act->z >= act->groundZ) {
                work->base.vz = -0x4C0;
                TryEnemyCardUse(act);
            }
            break;
        }
        break;
    case 18:
        {
            s32 d;
            s32 currentX;
            s32 targetX;
            u32 frame;
            s32 hitX;
            if (work->base.stateTimer == 0) {
                AnimChangeWithDef(sEmy82AnimDefs, &w->base.anim, 3, 0, w->base.tiles);
                work->base.vz = -0x400;
            }
            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                targetX = 0x3000;
                currentX = act->x;
                d = currentX + targetX;
            } else {
                targetX = -0x3000;
                currentX = act->x;
                d = currentX + targetX;
            }
            targetX = act->originX;
            targetX -= d;
            targetX >>= 4;
            currentX += targetX;
            act->x = currentX;
            frame = AnimGetFrame(&work->base.anim);
            if (frame > 3) {
                work->base.vz = 0;
            }
            if (frame == 4) {
                if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    hitX = act->x - 0x1400;
                } else {
                    hitX = act->x + 0x1400;
                }
                if (ApplyAttackBox(0xDE, hitX, act->y, act->z + 0x800, 10, 10, 20)) {
                    m4aSongNumStart(SONG_BTL_MON_HIT00);
                }
            } else if (frame == 5) {
                if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    hitX = act->x - 0x1800;
                } else {
                    hitX = act->x + 0x1800;
                }
                if (ApplyAttackBox(0xDE, hitX, act->y, act->z - 0x2300, 10, 10, 10)) {
                    m4aSongNumStart(SONG_BTL_MON_HIT00);
                }
            }
            if (AnimIsFinished(&work->base.anim)) {
                work->base.state = 23;
            } else {
                work->base.stateTimer++;
            }
        }
        break;
    case 19:
        {
            u32 frame;
            if (work->base.stateTimer == 0) {
                AnimChangeWithDef(sEmy82AnimDefs, &w->base.anim, 4, 0, w->base.tiles);
            }
            frame = AnimGetFrame(&work->base.anim);
            if (frame > 1) {
                work->base.vz = 0;
            }
            if (work->base.anim.timer == 0) {
                switch (frame) {
                case 1:
                    work->base.vz = -0x100;
                    m4aSongNumStart(SONG_EF_RAPPA_CALL);
                    break;
                case 4:
                    {
                        BtlObj* best = 0;
                        BtlObj* actor;
                        s16 missing = 0;
                        for (actor = ListPoolFirst(&gBtlWork->pool); actor;
                             actor = ListPoolNext(&actor->node)) {
                            if (actor != act && !(actor->flags & BTLOBJ_FLAG_INTANGIBLE)) {
                                if (missing <= actor->maxHp - actor->hp) {
                                    missing = actor->maxHp - actor->hp;
                                    best = actor;
                                }
                            }
                        }
                        if (best) {
                            m4aSongNumStart(SONG_EF_CAREL00);
                            best->flags |= BTLOBJ_FLAG_HEAL_PENDING;
                            best->damage = 0xFFEC;
                        } else {
                            CreateBtlPopTask(act, 2);
                        }
                    }
                    break;
                }
            }
            if (AnimIsFinished(&work->base.anim)) {
                work->base.state = 23;
            } else {
                work->base.stateTimer++;
            }
        }
        break;
    case 20:
        {
            u32 frame;
            if (work->base.stateTimer == 0) {
                AnimChangeWithDef(sEmy82AnimDefs, &w->base.anim, 5, 0, w->base.tiles);
            }
            frame = AnimGetFrame(&work->base.anim);
            if ((u16)(frame - 2) <= 21) {
                work->base.vz = 0;
            }
            if (work->base.anim.timer == 0) {
                switch (frame) {
                case 1:
                    work->base.vz = -0x100;
                    m4aSongNumStart(SONG_EF_RAPPA_CALL);
                    break;
                case 24:
                    work->base.vz = -0x380;
                    if (gBtlWork->enemyCount <= 3 && (s16)w->spawnCount <= 2) {
                        u32 spawnFailure = 0;
                        s32 x;
                        s32 offset;
                        if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                            x = act->x;
                            offset = 0x2000;
                        } else {
                            x = act->x;
                            offset = -0x2000;
                        }
                        x += offset;
                        offset = act->y;
                        if (SpawnEnemy(9, x, offset, act->z - 0xC00) != spawnFailure) {
                            gBtlWork->pendingEnemies++;
                            w->spawnCount++;
                        } else {
                            CreateBtlPopTask(act, 2);
                        }
                    } else {
                        CreateBtlPopTask(act, 2);
                    }
                    break;
                }
            }
            if (AnimIsFinished(&work->base.anim)) {
                work->base.state = 23;
            } else {
                work->base.stateTimer++;
            }
        }
        break;
    case 23:
        AnimChangeWithDef(sEmy82AnimDefs, &w->base.anim, 0, 0, w->base.tiles);
        work->base.vz = 0;
        if (AnimIsFinished(&work->base.anim)) {
            work->base.state = 24;
        }
        break;
    case 24:
        AnimChangeWithDef(sEmy82AnimDefs, &w->base.anim, 1, 0, w->base.tiles);
        if (act->z >= act->groundZ) {
            work->base.state = 25;
        }
        break;
    case 25:
        AnimChangeWithDef(sEmy82AnimDefs, &w->base.anim, 2, 0, w->base.tiles);
        if (AnimGetFrame(&work->base.anim) == 1 && work->base.anim.timer == 0) {
            work->base.vz = -0x333;
        }
        if (AnimIsFinished(&work->base.anim)) {
            EmyReturnToIdle(&work->base);
        }
        break;
    }
    return _0800CDF0(&work->base);
}

void task_emy_82_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_82_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_83_0(Emy83Work* work, void* obj) {
    EmyInit(&work->base, &sEmy83Def, obj);
    work->task = 0;
    work->base.idleState = 0x16;
    TaskPoolInit(&work->tasks, 4);
}

u8 task_emy_83_1(Emy83Work* work) {
    Emy83Work* w;
    BtlObj* act;
    u16 r;
    u16 c;
    EmySpawn spawn;
    s32 pos;
    s32 x;
    s32 y;
    s32 z;
    u8 ret;

    w = work;
    act = &work->base.actor;

    if (_0800CBDC(&work->base)) {
        r = GetRandom();

        switch (r & 1) {
        case 0:
            work->base.state = 0x12;
            w->task = 0;
            break;
        case 1:
            work->base.state = 0x13;
            w->shotCount = 0;
            break;
        }
    }

    switch (work->base.state) {
    case 0x16:
        AnimChangeWithDef(w->base.def->animDef, &w->base.anim, 0, ANIM_FLAG_LOOP | ANIM_FLAG_RANDOM_START, w->base.tiles);
        TryEnemyCardUse(act);
        GetEnemyTargetPosition(act, &pos, 0, 0);

        if (act->x < pos) {
            act->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
        } else {
            act->flags |= BTLOBJ_FLAG_FACING_LEFT;
        }
        break;
    case 0x12:
        AnimChangeWithDef(sEmy83AnimDefs, &w->base.anim, 0, 0, w->base.tiles);
        c = work->base.anim.timer;

        if (c == 0) {
            switch (AnimGetFrame(&work->base.anim)) {
            case 3:
                GetEnemyTargetPosition(act, &w->targetX, &w->targetY, 0);
                break;
            case 5:
                spawn.x = w->targetX;
                spawn.y = w->targetY;
                spawn.z = c;
                w->task = TaskCreate(&w->tasks, &sTaskDescEmy83B, &spawn);
                break;
            }
        }

        if (AnimIsFinished(&work->base.anim) && !IsTaskActiveNamed(w->task, sTaskDescEmy83B.name)) {
            EmyReturnToIdle(&work->base);
        }
        break;
    case 0x13:
        AnimChangeWithDef(sEmy83AnimDefs, &w->base.anim, 1, 0, w->base.tiles);

        if (AnimIsFinished(&work->base.anim)) {
            work->base.state = 0x14;
        }
        break;
    case 0x14:
        AnimChangeWithDef(sEmy83AnimDefs, &w->base.anim, 2, ANIM_FLAG_LOOP, w->base.tiles);

        if (AnimGetGfxIndex(&work->base.anim) == 6 && work->base.anim.timer == 0) {
            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                spawn.x = act->x - 0x1000;
                spawn.unk_12 = 1;
            } else {
                spawn.x = act->x + 0x1000;
                spawn.unk_12 = 0;
            }

            spawn.y = act->y;
            spawn.z = act->z - 0x1200;
            spawn.unk_14 = 0;
            TaskCreate(&w->tasks, &sTaskDescEmy83S, &spawn);
            spawn.unk_14 = 1;
            TaskCreate(&w->tasks, &sTaskDescEmy83S, &spawn);
            spawn.unk_14 = 2;
            TaskCreate(&w->tasks, &sTaskDescEmy83S, &spawn);
            w->shotCount++;
        }

        if (w->shotCount > 2 && AnimIsFinished(&work->base.anim)) {
            work->base.state = 0x15;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 0x15:
        AnimChangeWithDef(sEmy83AnimDefs, &w->base.anim, 3, 0, w->base.tiles);

        if (work->base.stateTimer > 0x28) {
            EmyReturnToIdle(&work->base);
        } else {
            work->base.stateTimer++;
        }
        break;
    }

    TaskPoolUpdate(&w->tasks);
    x = act->x;
    y = act->y;
    z = act->z;
    ret = _0800CDF0(&work->base);

    if (work->base.state != 0x0B) {
        act->x = x;
        act->y = y;
        act->z = z;
    }

    return ret;
}

void task_emy_83_2(Emy83Work* work) {
    EmyDraw(&work->base);
    TaskPoolDraw(&work->tasks);
}

void task_emy_83_3(Emy83Work* work) {
    TaskPoolDestroy(&work->tasks);
    EmyReleaseResources(&work->base);
}

void task_emy_83_b_0(Emy83bWork* work, EmySpawn* spawn) {
    work->state = 0;
    work->palette = LoadObjPalette(gEmy83Palette, 0x20);
    work->tiles = AllocObjTiles(0x80, gEmy8310bTiles);
    AnimInit(&work->anim, gEmy8310bAnims, gEmy8310bFrames);
    AnimStart(&work->anim, 0, 0);
    work->x = spawn->x;
    work->y = spawn->y;
    work->z = spawn->z;
    work->timer = 0;
    ColliderInit(&work->collider, 0x0C, 4, 0x10);
}

u8 task_emy_83_b_1(Emy83bWork* work) {
    if ((gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_ACTION) == 0) {
        return 0;
    }

    switch (work->state) {
    case 0:
        if (work->timer > 0x0F) {
            work->state = 1;
            work->timer = 0;
        } else {
            work->timer++;
        }
        break;
    case 1:
        if (work->timer == 0) {
            AnimStart(&work->anim, 1, 0);
        }

        if (AnimGetFrame(&work->anim) == 1 && work->anim.timer == 0) {
            if (ApplyAttackBox(0xE0, work->x, work->y, work->z, 4, 4, 0x10)) {
                m4aSongNumStart(SONG_BTL_HANE_HIT);
            }
        }

        if (work->timer > 0x1D) {
            work->state = 2;
            work->timer = 0;
        } else {
            work->timer++;
        }
        break;
    case 2:
    default:
        if (work->timer == 0) {
            AnimStart(&work->anim, 2, 0);
        }

        if (AnimIsFinished(&work->anim)) {
            return 0;
        }

        work->timer++;
        break;
    }

    ColliderSetPosition(&work->collider, work->x, work->y, work->z);
    AnimUpdate(&work->anim);
    return 1;
}

void task_emy_83_b_2(Emy83bWork* work) {
    void* gfx;
    u16 pri;
    s16 x;
    s16 y;

    gfx = AnimGetGfx(&work->anim);
    pri = GetBattleSpritePriorityFlags(work->y);
    WorldToScreen(&x, &y, work->x, work->y, work->z);
    DrawSprite(x, y, gfx, work->tiles, work->palette, 0, pri,
        -0x1004 - ((work->y + 0x400) >> 8) * 4);
}

void task_emy_83_b_3(Emy83bWork* work) {
    ColliderUnregister(&work->collider);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void task_emy_83_s_0(Emy83sWork* work, EmySpawn* spawn) {
    work->palette = LoadObjPalette(gEmy83Palette, 0x20);
    work->tiles = LoadObjTiles(gEmy8311bTiles, 0x40);
    work->x = spawn->x;
    work->y = spawn->y;
    work->z = spawn->z;
    work->vz = 0;
    work->frameCount = 0;

    if (spawn->unk_12 != 0) {
        work->vx = -(GetRandom() % 0x4CE + 0x133);
    } else {
        work->vx = GetRandom() % 0x4CE + 0x133;
    }

    work->vy = GetRandom() % 0x201 - 0x100;
    work->hitPhase = spawn->unk_14;
}

u8 task_emy_83_s_1(Emy83sWork* work) {
    s32 x;
    s32 y;

    if (gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_ACTION) {
        x = work->x + work->vx;
        work->x = x;
        y = work->y + work->vy;
        work->y = y;

        if (work->frameCount % 3 == work->hitPhase) {
            if (ApplyAttackBox(0xE1, x, y, work->z, 2, 2, 2) != 0) {
                m4aSongNumStart(SONG_BTL_KAMITUKI);
            }
        }

        work->z += work->vz;
        work->vz += 0x14;

        if (work->z < 0) {
            work->frameCount++;
            return 1;
        }
    }

    return 0;
}

void task_emy_83_s_2(Emy83sWork* work) {
    u16 pri;
    s16 x;
    s16 y;

    pri = GetBattleSpritePriorityFlags(work->y);
    WorldToScreen(&x, &y, work->x, work->y, work->z);
    DrawSprite(x, y, gEmy8311bFrame0, work->tiles, work->palette, 0, pri,
        -0x1004 - ((work->y + 0x400) >> 8) * 4);
    WorldToScreen(&x, &y, work->x, work->y, 0);
    DrawSprite(x, y, gEmy8311bFrame1, work->tiles, work->palette, 0, pri, -2);
}

void task_emy_83_s_3(Emy83sWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void task_emy_trump_h_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmyTrumpHDef, obj);
}

u8 task_emy_trump_h_1(EmyWork* work) {
    BtlObj* act;

    act = &work->actor;

    if (_0800CBDC(work)) {
        work->state = 0x13;
    }

    if (work->state == 3) {
        work->state = 0x12;
    }

    switch (work->state) {
    case 0x13:
        AnimChangeWithDef(&sEmyTrumpHAnimDef, &work->anim, 0, 0, work->tiles);
        EmyLungeAttack(work, 0x19, 8, 0x0A, 0x12B, 0x30, SONG_BTL_MON_SWORD00, 0x50, 0, 0x18);
        break;
    case 0x12:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(work->def->animDef, &work->anim, 0, 0, work->tiles);
            m4aSongNumStart(SONG_BTL_CARDDEATH);
        }

        work->scaleX = gSineTable[(u8)work->stateTimer + 0x40];
        work->stateTimer += 8;

        if (work->stateTimer > 0x13F) {
            DropEnemyPrizes(act);
            return 0;
        }

        work->stateTimer++;
        break;
    }

    return _0800CDF0(work);
}

void task_emy_trump_h_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_trump_h_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_trump_s_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmyTrumpSDef, obj);
}

u8 task_emy_trump_s_1(EmyWork* work) {
    BtlObj* act;

    act = &work->actor;

    if (_0800CBDC(work)) {
        work->state = 0x13;
    }

    if (work->state == 3) {
        work->state = 0x12;
    }

    switch (work->state) {
    case 0x13:
        AnimChangeWithDef(&sEmyTrumpSAnimDef, &work->anim, 0, 0, work->tiles);
        EmyLungeAttack(work, 0x14, 0x1E, 0x0A, 0x12A, 0x46, SONG_BTL_MON_SWORD01, 0x10, 0, 0x18);

        if (work->stateTimer == 0x14) {
            work->vz = -0x480;
        }
        break;
    case 0x12:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(work->def->animDef, &work->anim, 0, 0, work->tiles);
            m4aSongNumStart(SONG_BTL_CARDDEATH);
        }

        work->scaleX = gSineTable[(u8)work->stateTimer + 0x40];
        work->stateTimer += 8;

        if (work->stateTimer > 0x13F) {
            DropEnemyPrizes(act);
            return 0;
        }

        work->stateTimer++;
        break;
    }

    return _0800CDF0(work);
}

void task_emy_trump_s_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_trump_s_3(EmyWork* work) {
    EmyReleaseResources(work);
}

void task_emy_test_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmyTestDef, obj);
    work->actor.maxHp = 0xBB8;
    work->actor.hp = 0xBB8;
    work->actor.flags |= BTLOBJ_FLAG_NEVER_USES_CARDS;
}

u8 task_emy_test_1(EmyWork* work) {
    _0800CBDC(work);
    return _0800CDF0(work);
}

void task_emy_test_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_test_3(EmyWork* work) {
    EmyReleaseResources(work);
}

TaskDesc gTaskDescEmyTest = {
    "task_emy_test",
    (TaskInitFunc)task_emy_test_0,
    (TaskUpdateFunc)task_emy_test_1,
    (TaskDrawFunc)task_emy_test_2,
    (TaskDestroyFunc)task_emy_test_3,
    sizeof(EmyWork),
};
