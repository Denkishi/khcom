#include "task_descriptors.h"
#include "map_api.h"
#include "fld.h"
#include "gba/keys.h"
#include "task_animation_assets.h"
#include "sprites_btl.h"
#include "sprites_evt.h"
#include "sprites_fld.h"
#include "sprites_riku.h"
#include "sprites_sora.h"
#include "world_types.h"
#include "fade.h"
#include "songs.h"
#include <stdlib.h>
#include "fld_tasks.h"

static const AnimDef sFldSoraAnimDefs[15][5] = {
    { { gSor1bb00Frames, gSor1bb00Anims, gSor1bb00Tiles, 0, { 0, 0, 0 } }, { gSor1ff00Frames, gSor1ff00Anims, gSor1ff00Tiles, 0, { 0, 0, 0 } }, { gSor1fl00Frames, gSor1fl00Anims, gSor1fl00Tiles, 0, { 0, 0, 0 } }, { gSor1ll00Frames, gSor1ll00Anims, gSor1ll00Tiles, 0, { 0, 0, 0 } }, { gSor1bl00Frames, gSor1bl00Anims, gSor1bl00Tiles, 0, { 0, 0, 0 } } },
    { { gSor1bb01Frames, gSor1bb01Anims, gSor1bb01Tiles, 0, { 0, 0, 0 } }, { gSor1ff01Frames, gSor1ff01Anims, gSor1ff01Tiles, 0, { 0, 0, 0 } }, { gSor1fl01Frames, gSor1fl01Anims, gSor1fl01Tiles, 0, { 0, 0, 0 } }, { gSor1ll01Frames, gSor1ll01Anims, gSor1ll01Tiles, 0, { 0, 0, 0 } }, { gSor1bl01Frames, gSor1bl01Anims, gSor1bl01Tiles, 0, { 0, 0, 0 } } },
    { { gSor1bb02Frames, gSor1bb02Anims, gSor1bb02Tiles, 0, { 0, 0, 0 } }, { gSor1ff02Frames, gSor1ff02Anims, gSor1ff02Tiles, 0, { 0, 0, 0 } }, { gSor1fl02Frames, gSor1fl02Anims, gSor1fl02Tiles, 0, { 0, 0, 0 } }, { gSor1ll02Frames, gSor1ll02Anims, gSor1ll02Tiles, 0, { 0, 0, 0 } }, { gSor1bl02Frames, gSor1bl02Anims, gSor1bl02Tiles, 0, { 0, 0, 0 } } },
    { { gSor1bb03Frames, gSor1bb03Anims, gSor1bb03Tiles, 0, { 0, 0, 0 } }, { gSor1ff03Frames, gSor1ff03Anims, gSor1ff03Tiles, 0, { 0, 0, 0 } }, { gSor1fl03Frames, gSor1fl03Anims, gSor1fl03Tiles, 0, { 0, 0, 0 } }, { gSor1ll03Frames, gSor1ll03Anims, gSor1ll03Tiles, 0, { 0, 0, 0 } }, { gSor1bl03Frames, gSor1bl03Anims, gSor1bl03Tiles, 0, { 0, 0, 0 } } },
    { { gSor1bb03Frames, gSor1bb03Anims, gSor1bb03Tiles, 1, { 0, 0, 0 } }, { gSor1ff03Frames, gSor1ff03Anims, gSor1ff03Tiles, 1, { 0, 0, 0 } }, { gSor1fl03Frames, gSor1fl03Anims, gSor1fl03Tiles, 1, { 0, 0, 0 } }, { gSor1ll03Frames, gSor1ll03Anims, gSor1ll03Tiles, 1, { 0, 0, 0 } }, { gSor1bl03Frames, gSor1bl03Anims, gSor1bl03Tiles, 1, { 0, 0, 0 } } },
    { { gSor1bb03Frames, gSor1bb03Anims, gSor1bb03Tiles, 2, { 0, 0, 0 } }, { gSor1ff03Frames, gSor1ff03Anims, gSor1ff03Tiles, 2, { 0, 0, 0 } }, { gSor1fl03Frames, gSor1fl03Anims, gSor1fl03Tiles, 2, { 0, 0, 0 } }, { gSor1ll03Frames, gSor1ll03Anims, gSor1ll03Tiles, 2, { 0, 0, 0 } }, { gSor1bl03Frames, gSor1bl03Anims, gSor1bl03Tiles, 2, { 0, 0, 0 } } },
    { { gSor1bb03Frames, gSor1bb03Anims, gSor1bb03Tiles, 3, { 0, 0, 0 } }, { gSor1ff03Frames, gSor1ff03Anims, gSor1ff03Tiles, 3, { 0, 0, 0 } }, { gSor1fl03Frames, gSor1fl03Anims, gSor1fl03Tiles, 3, { 0, 0, 0 } }, { gSor1ll03Frames, gSor1ll03Anims, gSor1ll03Tiles, 3, { 0, 0, 0 } }, { gSor1bl03Frames, gSor1bl03Anims, gSor1bl03Tiles, 3, { 0, 0, 0 } } },
    { { gSor1bb03Frames, gSor1bb03Anims, gSor1bb03Tiles, 4, { 0, 0, 0 } }, { gSor1ff03Frames, gSor1ff03Anims, gSor1ff03Tiles, 4, { 0, 0, 0 } }, { gSor1fl03Frames, gSor1fl03Anims, gSor1fl03Tiles, 4, { 0, 0, 0 } }, { gSor1ll03Frames, gSor1ll03Anims, gSor1ll03Tiles, 4, { 0, 0, 0 } }, { gSor1bl03Frames, gSor1bl03Anims, gSor1bl03Tiles, 4, { 0, 0, 0 } } },
    { { gSor1bl05Frames, gSor1bl05Anims, gSor1bl05Tiles, 0, { 0, 0, 0 } }, { gSor1bl05Frames, gSor1bl05Anims, gSor1bl05Tiles, 0, { 0, 0, 0 } }, { gSor1bl05Frames, gSor1bl05Anims, gSor1bl05Tiles, 0, { 0, 0, 0 } }, { gSor1bl05Frames, gSor1bl05Anims, gSor1bl05Tiles, 0, { 0, 0, 0 } }, { gSor1bl05Frames, gSor1bl05Anims, gSor1bl05Tiles, 0, { 0, 0, 0 } } },
    { { gSor1bb11Frames, gSor1bb11Anims, gSor1bb11Tiles, 0, { 0, 0, 0 } }, { gSor1bl11Frames, gSor1bl11Anims, gSor1bl11Tiles, 0, { 0, 0, 0 } }, { gSor1bl11Frames, gSor1bl11Anims, gSor1bl11Tiles, 0, { 0, 0, 0 } }, { gSor1bl11Frames, gSor1bl11Anims, gSor1bl11Tiles, 0, { 0, 0, 0 } }, { gSor1bl11Frames, gSor1bl11Anims, gSor1bl11Tiles, 0, { 0, 0, 0 } } },
    { { gSor1bb11Frames, gSor1bb11Anims, gSor1bb11Tiles, 1, { 0, 0, 0 } }, { gSor1bl11Frames, gSor1bl11Anims, gSor1bl11Tiles, 1, { 0, 0, 0 } }, { gSor1bl11Frames, gSor1bl11Anims, gSor1bl11Tiles, 1, { 0, 0, 0 } }, { gSor1bl11Frames, gSor1bl11Anims, gSor1bl11Tiles, 1, { 0, 0, 0 } }, { gSor1bl11Frames, gSor1bl11Anims, gSor1bl11Tiles, 1, { 0, 0, 0 } } },
    { { gSor1bb11Frames, gSor1bb11Anims, gSor1bb11Tiles, 2, { 0, 0, 0 } }, { gSor1bl11Frames, gSor1bl11Anims, gSor1bl11Tiles, 2, { 0, 0, 0 } }, { gSor1bl11Frames, gSor1bl11Anims, gSor1bl11Tiles, 2, { 0, 0, 0 } }, { gSor1bl11Frames, gSor1bl11Anims, gSor1bl11Tiles, 2, { 0, 0, 0 } }, { gSor1bl11Frames, gSor1bl11Anims, gSor1bl11Tiles, 2, { 0, 0, 0 } } },
    { { gSor1bl15Frames, gSor1bl15Anims, gSor1bl15Tiles, 0, { 0, 0, 0 } }, { gSor1fl15Frames, gSor1fl15Anims, gSor1fl15Tiles, 0, { 0, 0, 0 } }, { gSor1fl15Frames, gSor1fl15Anims, gSor1fl15Tiles, 0, { 0, 0, 0 } }, { gSor1fl15Frames, gSor1fl15Anims, gSor1fl15Tiles, 0, { 0, 0, 0 } }, { gSor1bl15Frames, gSor1bl15Anims, gSor1bl15Tiles, 0, { 0, 0, 0 } } },
    { { gSor1bb10Frames, gSor1bb10Anims, gSor1bb10Tiles, 0, { 0, 0, 0 } }, { gSor1ff10Frames, gSor1ff10Anims, gSor1ff10Tiles, 0, { 0, 0, 0 } }, { gSor1fl10Frames, gSor1fl10Anims, gSor1fl10Tiles, 0, { 0, 0, 0 } }, { gSor1ll10Frames, gSor1ll10Anims, gSor1ll10Tiles, 0, { 0, 0, 0 } }, { gSor1bl10Frames, gSor1bl10Anims, gSor1bl10Tiles, 0, { 0, 0, 0 } } },
    { { gSor1bb61Frames, gSor1bb61Anims, gSor1bb61Tiles, 0, { 0, 0, 0 } }, { gSor1ff61Frames, gSor1ff61Anims, gSor1ff61Tiles, 0, { 0, 0, 0 } }, { gSor1fl61Frames, gSor1fl61Anims, gSor1fl61Tiles, 0, { 0, 0, 0 } }, { gSor1ll61Frames, gSor1ll61Anims, gSor1ll61Tiles, 0, { 0, 0, 0 } }, { gSor1bl61Frames, gSor1bl61Anims, gSor1bl61Tiles, 0, { 0, 0, 0 } } },
};

static const u16 sFldSoraSounds[8][8] = {
    { SONG_SYS_SR_STONEL, SONG_SYS_SR_STONER, SONG_SYS_SR_STONEJP, SONG_SYS_SR_STONELD, SONG_SYS_SR_STONEL, SONG_SYS_SR_STONER, SONG_SYS_SR_STONELJP, 0 },
    { SONG_SYS_SR_STONEL, SONG_SYS_SR_STONER, SONG_SYS_SR_STONEJP, SONG_SYS_SR_STONELD, SONG_SYS_SR_STONEL, SONG_SYS_SR_STONER, SONG_SYS_SR_STONELJP, 0 },
    { SONG_SYS_SR_MUDL, SONG_SYS_SR_MUDR, SONG_SYS_SR_MUDJP, SONG_SYS_SR_MUDLD, SONG_SYS_SR_MUDL, SONG_SYS_SR_MUDR, SONG_SYS_SR_MUDLJP, 0 },
    { SONG_SYS_SR_MUDL, SONG_SYS_SR_MUDR, SONG_SYS_SR_MUDJP, SONG_SYS_SR_MUDLD, SONG_SYS_SR_MUDL, SONG_SYS_SR_MUDR, SONG_SYS_SR_MUDLJP, 0 },
    { SONG_SYS_SR_FOOTL, SONG_SYS_SR_FOOTR, SONG_SYS_SR_JUMP, SONG_SYS_SR_LAND, SONG_SYS_SR_GRASSUP, SONG_SYS_SR_GRASSUP, SONG_SYS_SR_GRASSJP, 0 },
    { SONG_SYS_SR_STONEL, SONG_SYS_SR_STONER, SONG_SYS_SR_STONEJP, SONG_SYS_SR_STONELD, SONG_SYS_SR_STONEL, SONG_SYS_SR_STONER, SONG_SYS_SR_STONELJP, 0 },
    { SONG_SYS_SR_STONEL, SONG_SYS_SR_STONER, SONG_SYS_SR_STONEJP, SONG_SYS_SR_STONELD, SONG_SYS_SR_STONEL, SONG_SYS_SR_STONER, SONG_SYS_SR_STONELJP, 0 },
    { SONG_SYS_SR_FOOTL, SONG_SYS_SR_FOOTR, SONG_SYS_SR_JUMP, SONG_SYS_SR_LAND, SONG_SYS_SR_STONEL, SONG_SYS_SR_STONER, SONG_SYS_SR_STONELJP, 0 },
};

TaskDesc gTaskDescFldSora = {
    "task_fld_sora",
    (TaskInitFunc)task_fld_sora_0,
    (TaskUpdateFunc)task_fld_sora_1,
    (TaskDrawFunc)task_fld_sora_2,
    (TaskDestroyFunc)task_fld_sora_3,
    sizeof(FldWork),
};

static const AnimDef sFldRikuAnimDefs[15][5] = {
    { { gUnk_09EDF4C0, gUnk_09EDF4C4, gUnk_08933A34, 0, { 0, 0, 0 } }, { gRikuFf00Frames, gRikuFf00Anims, gRikuFf00Tiles, 0, { 0, 0, 0 } }, { gRikuFl00Frames, gRikuFl00Anims, gRikuFl00Tiles, 0, { 0, 0, 0 } }, { gUnk_09EDF4C8, gUnk_09EDF4CC, gUnk_08933D94, 0, { 0, 0, 0 } }, { gRikuBl00Frames, gRikuBl00Anims, gRikuBl00Tiles, 0, { 0, 0, 0 } } },
    { { gUnk_09EDF4F4, gUnk_09EDF514, gUnk_08935BC2, 0, { 0, 0, 0 } }, { gUnk_09EDF4D0, gUnk_09EDF4F0, gUnk_0893416A, 0, { 0, 0, 0 } }, { gRik1fl01Frames, gRik1fl01Anims, gRik1fl01Tiles, 0, { 0, 0, 0 } }, { gRik1ll01Frames, gRik1ll01Anims, gRik1ll01Tiles, 0, { 0, 0, 0 } }, { gRik1bl01Frames, gRik1bl01Anims, gRik1bl01Tiles, 0, { 0, 0, 0 } } },
    { { gRik1bb02Frames, gRik1bb02Anims, gRik1bb02Tiles, 0, { 0, 0, 0 } }, { gRik1ff02Frames, gRik1ff02Anims, gRik1ff02Tiles, 0, { 0, 0, 0 } }, { gRik1fl02Frames, gRik1fl02Anims, gRik1fl02Tiles, 0, { 0, 0, 0 } }, { gRik1ll02Frames, gRik1ll02Anims, gRik1ll02Tiles, 0, { 0, 0, 0 } }, { gRik1bl02Frames, gRik1bl02Anims, gRik1bl02Tiles, 0, { 0, 0, 0 } } },
    { { gRik1bb03Frames, gRik1bb03Anims, gRik1bb03Tiles, 0, { 0, 0, 0 } }, { gRik1ff03Frames, gRik1ff03Anims, gRik1ff03Tiles, 0, { 0, 0, 0 } }, { gRik1fl03Frames, gRik1fl03Anims, gRik1fl03Tiles, 0, { 0, 0, 0 } }, { gRik1ll03Frames, gRik1ll03Anims, gRik1ll03Tiles, 0, { 0, 0, 0 } }, { gRik1bl03Frames, gRik1bl03Anims, gRik1bl03Tiles, 0, { 0, 0, 0 } } },
    { { gRik1bb03Frames, gRik1bb03Anims, gRik1bb03Tiles, 1, { 0, 0, 0 } }, { gRik1ff03Frames, gRik1ff03Anims, gRik1ff03Tiles, 1, { 0, 0, 0 } }, { gRik1fl03Frames, gRik1fl03Anims, gRik1fl03Tiles, 1, { 0, 0, 0 } }, { gRik1ll03Frames, gRik1ll03Anims, gRik1ll03Tiles, 1, { 0, 0, 0 } }, { gRik1bl03Frames, gRik1bl03Anims, gRik1bl03Tiles, 1, { 0, 0, 0 } } },
    { { gRik1bb03Frames, gRik1bb03Anims, gRik1bb03Tiles, 2, { 0, 0, 0 } }, { gRik1ff03Frames, gRik1ff03Anims, gRik1ff03Tiles, 2, { 0, 0, 0 } }, { gRik1fl03Frames, gRik1fl03Anims, gRik1fl03Tiles, 2, { 0, 0, 0 } }, { gRik1ll03Frames, gRik1ll03Anims, gRik1ll03Tiles, 2, { 0, 0, 0 } }, { gRik1bl03Frames, gRik1bl03Anims, gRik1bl03Tiles, 2, { 0, 0, 0 } } },
    { { gRik1bb03Frames, gRik1bb03Anims, gRik1bb03Tiles, 3, { 0, 0, 0 } }, { gRik1ff03Frames, gRik1ff03Anims, gRik1ff03Tiles, 3, { 0, 0, 0 } }, { gRik1fl03Frames, gRik1fl03Anims, gRik1fl03Tiles, 3, { 0, 0, 0 } }, { gRik1ll03Frames, gRik1ll03Anims, gRik1ll03Tiles, 3, { 0, 0, 0 } }, { gRik1bl03Frames, gRik1bl03Anims, gRik1bl03Tiles, 3, { 0, 0, 0 } } },
    { { gRik1bb03Frames, gRik1bb03Anims, gRik1bb03Tiles, 4, { 0, 0, 0 } }, { gRik1ff03Frames, gRik1ff03Anims, gRik1ff03Tiles, 4, { 0, 0, 0 } }, { gRik1fl03Frames, gRik1fl03Anims, gRik1fl03Tiles, 4, { 0, 0, 0 } }, { gRik1ll03Frames, gRik1ll03Anims, gRik1ll03Tiles, 4, { 0, 0, 0 } }, { gRik1bl03Frames, gRik1bl03Anims, gRik1bl03Tiles, 4, { 0, 0, 0 } } },
    { { gUnk_09EDF5F4, gUnk_09EDF60C, gUnk_0893DCDC, 0, { 0, 0, 0 } }, { gUnk_09EDF5F4, gUnk_09EDF60C, gUnk_0893DCDC, 0, { 0, 0, 0 } }, { gUnk_09EDF5F4, gUnk_09EDF60C, gUnk_0893DCDC, 0, { 0, 0, 0 } }, { gUnk_09EDF5F4, gUnk_09EDF60C, gUnk_0893DCDC, 0, { 0, 0, 0 } }, { gUnk_09EDF5F4, gUnk_09EDF60C, gUnk_0893DCDC, 0, { 0, 0, 0 } } },
    { { gUnk_09EDF640, gUnk_09EDF660, gUnk_08940D90, 0, { 0, 0, 0 } }, { gUnk_09EDF614, gUnk_09EDF634, gUnk_0893F080, 0, { 0, 0, 0 } }, { gUnk_09EDF614, gUnk_09EDF634, gUnk_0893F080, 0, { 0, 0, 0 } }, { gUnk_09EDF614, gUnk_09EDF634, gUnk_0893F080, 0, { 0, 0, 0 } }, { gUnk_09EDF614, gUnk_09EDF634, gUnk_0893F080, 0, { 0, 0, 0 } } },
    { { gUnk_09EDF640, gUnk_09EDF660, gUnk_08940D90, 1, { 0, 0, 0 } }, { gUnk_09EDF614, gUnk_09EDF634, gUnk_0893F080, 1, { 0, 0, 0 } }, { gUnk_09EDF614, gUnk_09EDF634, gUnk_0893F080, 1, { 0, 0, 0 } }, { gUnk_09EDF614, gUnk_09EDF634, gUnk_0893F080, 1, { 0, 0, 0 } }, { gUnk_09EDF614, gUnk_09EDF634, gUnk_0893F080, 1, { 0, 0, 0 } } },
    { { gUnk_09EDF640, gUnk_09EDF660, gUnk_08940D90, 2, { 0, 0, 0 } }, { gUnk_09EDF614, gUnk_09EDF634, gUnk_0893F080, 2, { 0, 0, 0 } }, { gUnk_09EDF614, gUnk_09EDF634, gUnk_0893F080, 2, { 0, 0, 0 } }, { gUnk_09EDF614, gUnk_09EDF634, gUnk_0893F080, 2, { 0, 0, 0 } }, { gUnk_09EDF614, gUnk_09EDF634, gUnk_0893F080, 2, { 0, 0, 0 } } },
    { { gUnk_09EDF680, gUnk_09EDF68C, gUnk_089434C8, 0, { 0, 0, 0 } }, { gUnk_09EDF66C, gUnk_09EDF678, gUnk_089429AE, 0, { 0, 0, 0 } }, { gUnk_09EDF66C, gUnk_09EDF678, gUnk_089429AE, 0, { 0, 0, 0 } }, { gUnk_09EDF66C, gUnk_09EDF678, gUnk_089429AE, 0, { 0, 0, 0 } }, { gUnk_09EDF680, gUnk_09EDF68C, gUnk_089434C8, 0, { 0, 0, 0 } } },
    { { gRik1bb10Frames, gRik1bb10Anims, gRik1bb10Tiles, 0, { 0, 0, 0 } }, { gRik1ff10Frames, gRik1ff10Anims, gRik1ff10Tiles, 0, { 0, 0, 0 } }, { gRik1fl10Frames, gRik1fl10Anims, gRik1fl10Tiles, 0, { 0, 0, 0 } }, { gRikuBt11Frames, gRikuBt11Anims, gRikuBt11Tiles, 0, { 0, 0, 0 } }, { gRik1bl10Frames, gRik1bl10Anims, gRik1bl10Tiles, 0, { 0, 0, 0 } } },
    { { gRikuBb17Frames, gRikuBb17Anims, gRikuBb17Tiles, 0, { 0, 0, 0 } }, { gRikuFf17Frames, gRikuFf17Anims, gRikuFf17Tiles, 0, { 0, 0, 0 } }, { gRikuFl17Frames, gRikuFl17Anims, gRikuFl17Tiles, 0, { 0, 0, 0 } }, { gRikuLl17Frames, gRikuLl17Anims, gRikuLl17Tiles, 0, { 0, 0, 0 } }, { gRikuBl17Frames, gRikuBl17Anims, gRikuBl17Tiles, 0, { 0, 0, 0 } } },
};

static const u16 sFldRikuSounds[8][8] = {
    { SONG_SYS_SR_STONEL, SONG_SYS_SR_STONER, SONG_SYS_SR_STONEJP, SONG_SYS_SR_STONELD, SONG_SYS_SR_STONEL, SONG_SYS_SR_STONER, SONG_SYS_SR_STONELJP, 0 },
    { SONG_SYS_SR_STONEL, SONG_SYS_SR_STONER, SONG_SYS_SR_STONEJP, SONG_SYS_SR_STONELD, SONG_SYS_SR_STONEL, SONG_SYS_SR_STONER, SONG_SYS_SR_STONELJP, 0 },
    { SONG_SYS_SR_MUDL, SONG_SYS_SR_MUDR, SONG_SYS_SR_MUDJP, SONG_SYS_SR_MUDLD, SONG_SYS_SR_MUDL, SONG_SYS_SR_MUDR, SONG_SYS_SR_MUDLJP, 0 },
    { SONG_SYS_SR_MUDL, SONG_SYS_SR_MUDR, SONG_SYS_SR_MUDJP, SONG_SYS_SR_MUDLD, SONG_SYS_SR_MUDL, SONG_SYS_SR_MUDR, SONG_SYS_SR_MUDLJP, 0 },
    { SONG_SYS_SR_FOOTL, SONG_SYS_SR_FOOTR, SONG_SYS_SR_JUMP, SONG_SYS_SR_LAND, SONG_SYS_SR_GRASSUP, SONG_SYS_SR_GRASSUP, SONG_SYS_SR_GRASSJP, 0 },
    { SONG_SYS_SR_STONEL, SONG_SYS_SR_STONER, SONG_SYS_SR_STONEJP, SONG_SYS_SR_STONELD, SONG_SYS_SR_STONEL, SONG_SYS_SR_STONER, SONG_SYS_SR_STONELJP, 0 },
    { SONG_SYS_SR_STONEL, SONG_SYS_SR_STONER, SONG_SYS_SR_STONEJP, SONG_SYS_SR_STONELD, SONG_SYS_SR_STONEL, SONG_SYS_SR_STONER, SONG_SYS_SR_STONELJP, 0 },
    { SONG_SYS_SR_FOOTL, SONG_SYS_SR_FOOTR, SONG_SYS_SR_JUMP, SONG_SYS_SR_LAND, SONG_SYS_SR_STONEL, SONG_SYS_SR_STONER, SONG_SYS_SR_STONELJP, 0 },
};

void FldSoraSetAngleFromDpad(FldActor* act) {
    if ((GetKeysHeld() & DPAD_LEFT) && (GetKeysHeld() & DPAD_DOWN)) {
        act->angle = 173;
    } else if ((GetKeysHeld() & DPAD_UP) && (GetKeysHeld() & DPAD_LEFT)) {
        act->angle = 211;
    } else if ((GetKeysHeld() & DPAD_UP) && (GetKeysHeld() & DPAD_RIGHT)) {
        act->angle = 45;
    } else if ((GetKeysHeld() & DPAD_RIGHT) && (GetKeysHeld() & DPAD_DOWN)) {
        act->angle = 83;
    } else if ((GetKeysHeld() & DPAD_DOWN) && GetKeyReleaseTime(DPAD_LEFT) <= 4) {
        act->angle = 173;
    } else if ((GetKeysHeld() & DPAD_DOWN) && GetKeyReleaseTime(DPAD_RIGHT) <= 4) {
        act->angle = 83;
    } else if ((GetKeysHeld() & DPAD_UP) && GetKeyReleaseTime(DPAD_LEFT) <= 4) {
        act->angle = 211;
    } else if ((GetKeysHeld() & DPAD_UP) && GetKeyReleaseTime(DPAD_RIGHT) <= 4) {
        act->angle = 45;
    } else if ((GetKeysHeld() & DPAD_LEFT) && GetKeyReleaseTime(DPAD_UP) <= 4) {
        act->angle = 211;
    } else if ((GetKeysHeld() & DPAD_LEFT) && GetKeyReleaseTime(DPAD_DOWN) <= 4) {
        act->angle = 173;
    } else if ((GetKeysHeld() & DPAD_RIGHT) && GetKeyReleaseTime(DPAD_UP) <= 4) {
        act->angle = 45;
    } else if ((GetKeysHeld() & DPAD_RIGHT) && GetKeyReleaseTime(DPAD_DOWN) <= 4) {
        act->angle = 83;
    } else if (GetKeysHeld() & DPAD_DOWN) {
        act->angle = 128;
    } else if (GetKeysHeld() & DPAD_UP) {
        act->angle = 0;
    } else if (GetKeysHeld() & DPAD_LEFT) {
        act->angle = 192;
    } else if (GetKeysHeld() & DPAD_RIGHT) {
        act->angle = 64;
    }
}

u8 FldSoraCheckBlocked(FldPos* p) {
    FldPos a;
    FldPos b;
    s32 v1;
    s32 v2;

    a = *p;
    b = *p;
    a.y -= 1536;
    b.y += 1536;

    v1 = GetFldPosGround(&a);
    if (v1 > a.ground) {
        a.ground = v1;
    }
    v2 = GetFldPosGround(&b);
    if (v2 > b.ground) {
        b.ground = v2;
    }

    if (IsFldPosBlocked(&a) != 0) {
        return 1;
    }

    if (IsFldPosBlocked(&b) != 0) {
        return 1;
    }
    p->ground = v2 > v1 ? v1 : v2;
    return 0;
}

s32 FldSoraProbeGround(FldPos* p) {
    FldPos a;
    FldPos b;
    s32 v1;
    s32 v2;

    a = *p;
    b = *p;
    a.y -= 1536;
    b.y += 1536;
    v1 = GetFldPosGround(&a);
    v2 = GetFldPosGround(&b);
    if (v2 > v1) {
        v2 = v1;
    }
    return v2;
}

u8 FldSoraCheckClimb(FldPos* p, FldWork* work) {
    FldPos a;
    FldPos b;
    u8 r;

    a = *p;
    b = *p;
    a.y -= 1536;
    b.y += 1536;

    r = _080DFE1C(&a);
    if (r != 0) {
        work->targetX = a.x;
        work->targetY = a.y;
        return r;
    }
    r = _080DFE1C(&b);
    if (r != 0) {
        work->targetX = b.x;
        work->targetY = b.y;
        return r;
    }
    return 0;
}

u8 FldSoraCheckDoorAhead(FldActor* act) {
    FldPos a;

    a = act->fieldPosition;
    a.x += gSineTable[act->angle] * 8;
    a.y -= gSineTable[act->angle + 64] * 8;

    if (MapFindOpenDoor(&a) != 0) {
        return 1;
    }
    return 0;
}

s32 FldSoraGetGround(FldWork* work) {
    FldActor* act;
    s32 v;

    act = &gFieldState->actor;

    if (work->collider.standFlags & COLLIDER_STAND_OVER_PLATFORM) {
        if (act->fieldPosition.ground < work->collider.platformZ) {
            v = act->fieldPosition.ground;
        } else {
            v = work->collider.platformZ;
        }

        work->onCollider = 1;
    } else {
        work->onCollider = 0;
        v = act->fieldPosition.ground;
    }

    return v;
}

void FldSoraTurn(FldActor* act) {
    u8 old = act->angle;

    FldSoraSetAngleFromDpad(act);

    if (old != act->angle) {
        s32 v;

        if (abs((s8)GetAngleDiff(old, act->angle)) > 100) {
            v = 0;
        } else {
            v = act->speed >> 1;
        }
        act->speed = v;
    }
}

void FldSoraSetAnim(FldWork* work, s32 a, s32 b) {
    const FldAnimDef* e;
    u16 flags = b;
    s32 idx;

    switch (gFieldState->actor.angle) {
    case 45:
        idx = 4;
        work->flags |= FLD_FLAG_HFLIP;
        break;
    case 64:
        idx = 3;
        work->flags |= FLD_FLAG_HFLIP;
        break;
    case 83:
        idx = 2;
        work->flags |= FLD_FLAG_HFLIP;
        break;
    case 128:
        idx = 1;
        work->flags &= ~FLD_FLAG_HFLIP;
        break;
    case 173:
        idx = 2;
        work->flags &= ~FLD_FLAG_HFLIP;
        break;
    case 192:
        idx = 3;
        work->flags &= ~FLD_FLAG_HFLIP;
        break;
    case 211:
        idx = 4;
        work->flags &= ~FLD_FLAG_HFLIP;
        break;
    case 0:
    default:
        idx = 0;
        work->flags &= ~FLD_FLAG_HFLIP;
        break;
    }

    if (work->animAction == a) {
        flags |= 4;
    }
    work->animAction = a;

    e = &sFldSoraAnimDefs[a][idx];
    AnimChangeWithTables(&work->anim, e->animId, flags, e->anims, e->gfxTable);
    SetObjTileSource(work->tiles, e->tiles);
}

void task_fld_sora_0(FldWork* work) {
    FldActor* act;

    act = &gFieldState->actor;
    work->tiles = AllocObjTiles(0x500, 0);
    work->palette = LoadObjPalette(gSoraPalette, 32);
    act->height = 16;
    work->onCollider = 0;
    work->unk_9C = 0;
    work->unk_9D = 0;
    work->unk_9E = 0;
    work->timer = 0;
    work->flags = FLD_FLAG_RESTORE_STATE;
    work->animAction = 16;
    act->unk_32 = 0;
    act->kind = 0;

    if (gGameState.fieldResume != 0) {
        act->fieldPosition = gGameState.fieldPosition;
        act->angle = gGameState.fieldAngle;
        act->speed = gGameState.fieldSpeed;
        work->state = gGameState.fieldState;
        work->vz = gGameState.fieldVz;
        work->targetX = gGameState.fieldTargetX;
        work->targetY = gGameState.fieldTargetY;
        work->targetZ = gGameState.fieldTargetZ;
    } else {
        act->fieldPosition.x = gFieldState->spawnX;
        act->fieldPosition.y = gFieldState->spawnY;
        act->fieldPosition.z = 0;
        act->angle = gFieldState->spawnAngle;
        FldPosInitGround(&act->fieldPosition);
        act->fieldPosition.z = act->fieldPosition.ground;
        act->fieldPosition.y -= act->fieldPosition.ground;
        act->speed = 0;
        work->state = 0;
        work->vz = 0;
    }

    AnimInit(&work->anim, 0, 0);
    FldSoraSetAnim(work, 0, 1);
    work->gfx = AnimGetGfx(&work->anim);

    switch (gGameState.world) {
    case WORLD_NEVER_LAND:
        work->sounds = sFldSoraSounds[1];
        break;
    case WORLD_ATLANTICA:
        work->sounds = sFldSoraSounds[2];
        break;
    case WORLD_MONSTRO:
        work->sounds = sFldSoraSounds[3];
        break;
    case WORLD_WONDERLAND:
        work->sounds = sFldSoraSounds[4];
        break;
    case WORLD_HALLOWEEN_TOWN:
        work->sounds = sFldSoraSounds[5];
        break;
    case 0:
    case WORLD_OLYMPUS_COLISEUM:
    case WORLD_CASTLE_OBLIVION:
        work->sounds = sFldSoraSounds[6];
        break;
    case WORLD_DESTINY_ISLANDS:
        work->sounds = sFldSoraSounds[7];
        break;
    default:
        work->sounds = sFldSoraSounds[0];
        break;
    }

    TaskPoolInit(&work->tasks, 2);
    TaskCreate(&work->tasks, &gTaskDescFldShadow, &gFieldState->actor);
    ColliderInit(&work->collider, 1, 4, 32);
    ColliderSetPosition(&work->collider, act->fieldPosition.x, act->fieldPosition.y, act->fieldPosition.z);
}
u8 FldSoraWaitRoomCreate(FldWork* work, void* task) {
    FldActor* act;
    s16* p;
    s32 flags;

    act = &gFieldState->actor;
    flags = gFieldState->flags;

    if (flags & FIELD_FLAG_CARD_POSE) {
        FldSoraSetAnim(work, 12, 0);
    } else if (flags & FIELD_FLAG_AUTO_WALK) {
        FldSoraSetAnim(work, 1, 1);
    } else {
        FldSoraSetAnim(work, 0, 1);
    }

    if ((gFieldState->flags & FIELD_FLAG_ROOM_CREATE) == 0) {
        FadeSetPaletteExcluded(work->palette->index + 16, 0);
        work->state = 0;
        work->timer = 0;
        SetTaskUpdate(task, (TaskUpdateFunc)task_fld_sora_1);
        TaskPoolUpdate(&work->tasks);
    } else {
        p = &work->timer;

        if (*p == 0) {
            FadeSetPaletteExcluded(work->palette->index + 16, 1);
            act->speed = 0;
            work->onCollider = 0;
        }

        TaskPoolUpdate(&work->tasks);
        work->gfx = AnimUpdate(&work->anim);
        ColliderSetPosition(&work->collider, act->fieldPosition.x, act->fieldPosition.y, act->fieldPosition.z);
        (*p)++;
    }

    return 1;
}
u8 FldSoraGmkJump(FldWork* work, void* task) {
    FldActor* act;
    s32 x;
    s32 y;
    s32 z;

    act = &gFieldState->actor;
    x = act->fieldPosition.x;
    y = act->fieldPosition.y;
    gFieldState->lockonTarget = 0;

    switch (work->state) {
    case 13:
        m4aSongNumStart(SONG_SYS_GIMICJP);
        work->state = 14;
        work->vz = -0x800;
        work->timer = 0;
        act->speed = 0;
        work->targetX = work->collider.platformX;
        work->targetY = work->collider.platformY;
    case 14:
        if (work->vz > -0x300) {
            FldSoraSetAnim(work, 11, 0);
            act->speed = 0x180;
            act->fieldPosition.x += gSineTable[act->angle] * act->speed >> 8;
            act->fieldPosition.y += -gSineTable[act->angle + 64] * act->speed >> 8;
        } else {
            FldSoraSetAnim(work, 4, 0);
            act->fieldPosition.x += (work->targetX - act->fieldPosition.x) >> 3;
            act->fieldPosition.y += (work->targetY - act->fieldPosition.y) >> 3;
        }

        work->vz = (work->targetZ - (z = act->fieldPosition.z + 0xF00)) >> 3;
        act->fieldPosition.z += work->vz;
        work->vz += 0x42;

        if (work->vz >= 0) {
            work->timer = 0;
            work->state = 4;
            work->flags |= FLD_FLAG_NO_AIR_TURN;
            SetTaskUpdate(task, (TaskUpdateFunc)FldSoraJump);
        } else {
            work->timer++;
        }

        break;
    }

    if (FldSoraCheckBlocked(&act->fieldPosition) != 0) {
        act->fieldPosition.x = x;
        act->fieldPosition.y = y;
    }

    ColliderSetPosition(&work->collider, act->fieldPosition.x, act->fieldPosition.y, act->fieldPosition.z);
    MapSetCameraTarget(act->fieldPosition.x, act->fieldPosition.y + act->fieldPosition.z);
    work->gfx = AnimUpdate(&work->anim);
    TaskPoolUpdate(&work->tasks);
    return 1;
}
u8 FldSoraJump(FldWork* work, void* task) {
    FldPos p1;
    FldPos p2;
    s32 sx;
    s32 sy;
    s32 nx;
    s32 ny;
    s32 z;
    FldActor* act;

    act = &gFieldState->actor;
    z = FldSoraGetGround(work);
    sx = act->fieldPosition.x;
    sy = act->fieldPosition.y;
    gFieldState->lockonTarget = 0;

    if ((work->flags & FLD_FLAG_NO_AIR_TURN) == 0) {
        FldSoraTurn(act);
    }

    switch (work->state) {
    case 12:
        if (work->timer == 0) {
            gFieldState->lockonTarget = 0;
            FldSoraSetAnim(work, 14, 0);
        }

        act->fieldPosition.x += gSineTable[act->angle] * act->speed >> 8;
        act->fieldPosition.y += -gSineTable[act->angle + 64] * act->speed >> 8;

        if (AnimGetFrame(&work->anim) > 3) {
            act->fieldPosition.z += work->vz;
            work->vz += 66;

            if (act->fieldPosition.z > z) {
                act->fieldPosition.z = z;
                work->vz = 0;
            }
        } else {
            work->vz = 0;
        }

        act->speed -= 38;

        if (act->speed < 0) {
            act->speed = 0;
        }

        switch (AnimGetFrame(&work->anim)) {
        case 3:
        case 4:
            switch (act->angle) {
            case 45:
            case 211:
                nx = act->fieldPosition.x + gSineTable[act->angle] * 12;
                ny = act->fieldPosition.y + -gSineTable[act->angle + 64] * 12;
                break;
            case 64:
            case 192:
                nx = act->fieldPosition.x + gSineTable[act->angle] * 27;
                ny = act->fieldPosition.y + -gSineTable[act->angle + 64] * 27;
                break;
            case 0:
            case 83:
            case 128:
            case 173:
            default:
                nx = act->fieldPosition.x + gSineTable[act->angle] * 20;
                ny = act->fieldPosition.y + -gSineTable[act->angle + 64] * 20;
                break;
            }

            SetMapAttackBox(nx, ny, act->fieldPosition.z - 0x800);
            break;
        }

        if (AnimIsFinished(&work->anim) != 0) {
            if (work->vz < 0) {
                work->state = 3;
            } else {
                work->state = 4;
            }
        } else {
            work->timer++;
        }

        break;
    case 2:
        if (work->timer == 0) {
            FldSoraSetAnim(work, 3, 0);
            act->speed >>= 1;
        }

        act->fieldPosition.x += gSineTable[act->angle] * act->speed >> 8;
        act->fieldPosition.y += -gSineTable[act->angle + 64] * act->speed >> 8;

        if (work->timer > 3) {
            work->targetZ = gMapRoomState->jumpGmkHeight;

            if (work->targetZ == 0) {
                if (GetRandom() % 2 != 0) {
                    m4aSongNumStart(SONG_SYS_SR_I_VO00);
                } else {
                    m4aSongNumStart(SONG_SYS_SR_I_VO01);
                }

                work->state = 3;
                work->vz = -1331;
                act->speed <<= 1;
                work->timer = 0;
                act->fieldPosition.z += work->vz;
                work->vz += 66;
            } else {
                act->angle = gMapRoomState->jumpGmkAngle;
                work->targetZ = act->fieldPosition.z - work->targetZ;
                work->state = 13;
                SetTaskUpdate(task, (TaskUpdateFunc)FldSoraGmkJump);
                work->timer = 0;
            }
        } else {
            work->timer++;
        }

        break;
    case 3:
        if ((GetKeysHeld() & DPAD_ANY) != 0) {
            act->speed += 17;

            if (act->speed > 512) {
                act->speed = 512;
            }
        } else {
            act->speed -= 38;

            if (act->speed < 0) {
                act->speed = 0;
            }
        }

        if (work->vz > -512) {
            FldSoraSetAnim(work, 5, 0);
        } else {
            FldSoraSetAnim(work, 4, 0);
        }

        act->fieldPosition.x += gSineTable[act->angle] * act->speed >> 8;
        act->fieldPosition.y += -gSineTable[act->angle + 64] * act->speed >> 8;
        act->fieldPosition.z += work->vz;
        work->vz += 66;

        if (work->vz < 0) {
            if ((GetKeysHeld() & B_BUTTON) == 0) {
                work->vz += 64;
            }
        }

        if ((GetKeysPressed() & A_BUTTON) != 0) {
            work->timer = 0;
            work->state = 12;
        } else if (work->vz > 0) {
            work->timer = 0;
            work->state = 4;
        } else {
            work->timer++;
        }

        break;
    case 4:
        if ((GetKeysHeld() & DPAD_ANY) != 0) {
            act->speed += 17;

            if (act->speed > 512) {
                act->speed = 512;
            }
        } else {
            act->speed -= 38;

            if (act->speed < 0) {
                act->speed = 0;
            }
        }

        if (work->vz < 0x200) {
            FldSoraSetAnim(work, 5, 0);
        } else {
            FldSoraSetAnim(work, 6, 0);
        }

        act->fieldPosition.x += gSineTable[act->angle] * act->speed >> 8;
        act->fieldPosition.y += -gSineTable[act->angle + 64] * act->speed >> 8;
        act->fieldPosition.z += work->vz;
        work->vz += 66;

        if ((GetKeysPressed() & A_BUTTON) != 0) {
            work->timer = 0;
            work->state = 12;
        } else if (act->fieldPosition.z > z) {
            act->fieldPosition.z = z;
            work->vz = 0;

            if (work->state != 5) {
                work->state = 5;
                work->timer = 0;
            }
        }

        break;
    case 5:
        if (work->timer == 0) {
            FldSoraSetAnim(work, 7, 0);
            m4aSongNumStart(work->sounds[3]);
        }

        act->speed = 0;

        if ((GetKeysPressed() & B_BUTTON) != 0) {
            work->flags &= ~FLD_FLAG_NO_AIR_TURN;
            work->timer = 0;
            work->state = 2;
        } else if (work->timer > 6) {
            gFieldState->flags &= ~FIELD_FLAG_PLAYER_JUMPING;
            work->flags &= ~FLD_FLAG_NO_AIR_TURN;
            work->state = 0;
            work->timer = 0;
            SetTaskUpdate(task, (TaskUpdateFunc)task_fld_sora_1);
        } else {
            work->timer++;
        }

        break;
    }

    if (work->collider.colliding != 0) {
        switch ((u32)work->collider.otherType) {
        case 3:
        case 5:
        case 11:
            break;
        default:
            if ((work->collider.standFlags & COLLIDER_STAND_OVER_PLATFORM) == 0) {
                act->speed = 230 * act->speed >> 8;
                act->fieldPosition.x += work->collider.pushX;
                act->fieldPosition.y += work->collider.pushY;
            }
            break;
        }
    }

    if (FldSoraCheckBlocked(&act->fieldPosition) != 0) {
        act->fieldPosition.x = sx;
        act->fieldPosition.y = sy;

        switch (FldSoraCheckClimb(&act->fieldPosition, work)) {
        case 2:
            work->timer = 0;
            work->state = 6;
            act->angle = 211;
            SetTaskUpdate(task, (TaskUpdateFunc)FldSoraClimb);
            break;
        case 1:
            work->timer = 0;
            work->state = 6;
            act->angle = 45;
            SetTaskUpdate(task, (TaskUpdateFunc)FldSoraClimb);
            break;
        default:
            if (work->state == 4 && act->fieldPosition.ground - act->fieldPosition.z > 0xFFF) {
                p1 = act->fieldPosition;
                p1.y -= 0x400;
                p1.z = act->fieldPosition.z - 0x3000;
                p2 = p1;
                p2.z += 768;

                if (FldSoraCheckBlocked(&p1) == 0 && FldSoraCheckBlocked(&p2) != 0) {
                    work->timer = 0;
                    work->state = 8;
                    gFieldState->lockonTarget = 0;
                    SetTaskUpdate(task, (TaskUpdateFunc)FldSoraHangLedge);
                }
            } else {
                act->speed = 230 * act->speed >> 8;
            }
            break;
        }
    }

    ColliderSetPosition(&work->collider, act->fieldPosition.x, act->fieldPosition.y, act->fieldPosition.z);
    MapSetCameraTarget(act->fieldPosition.x, act->fieldPosition.y + act->fieldPosition.z);
    work->gfx = AnimUpdate(&work->anim);
    TaskPoolUpdate(&work->tasks);

    if ((gFieldState->flags & FIELD_FLAG_ROOM_CREATE) != 0) {
        work->timer = 0;
        SetTaskUpdate(task, (TaskUpdateFunc)FldSoraWaitRoomCreate);
        TaskPoolUpdate(&work->tasks);
    }

    return 1;
}
u8 FldSoraClimb(FldWork* work, void* task) {
    FldActor* act;
    FldPos p;
    s32 x;
    s32 y;
    s32 limit;
    s32 d;
    s32 ny;
    s32 nx;
    s32 tx;
    s32 ty;

    act = &gFieldState->actor;
    limit = FldSoraGetGround(work);
    x = act->fieldPosition.x;
    y = act->fieldPosition.y;
    gFieldState->lockonTarget = 0;

    switch (work->state) {
    case 6:
        if (work->timer == 0) {
            work->targetZ = (act->fieldPosition.z >> 12) << 12;
            work->timer++;
            tx = (work->targetX >> 11) / 4;
            ty = (work->targetY >> 11) / 2;
            nx = (tx << 13) | 0x1000;
            ny = (ty << 12) | 0x800;
            x = nx;
            act->fieldPosition.x = nx;
            y = ny;
            act->fieldPosition.y = ny;
            m4aSongNumStart(work->sounds[5]);
            act->fieldPosition.ground = GetFldPosGround(&act->fieldPosition);
        }

        FldSoraSetAnim(work, 8, 1);
        work->anim.frame = ((act->fieldPosition.z >> 8) + 4) & 31;
        work->gfx = AnimGetGfx(&work->anim);

        if (work->anim.timer == 0) {
            switch (work->anim.frame) {
            case 8:
                m4aSongNumStart(work->sounds[4]);
                break;
            case 24:
                m4aSongNumStart(work->sounds[5]);
                break;
            }
        }

        d = (((work->targetZ >> 12) << 12) - act->fieldPosition.z) >> 1;

        if (abs(d) <= 24) {
            d = 0;
        } else if (d > 384) {
            d = 384;
        } else if (d < -384) {
            d = -384;
        }

        act->fieldPosition.z += d;

        if (d < 0) {
            act->fieldPosition.x += gSineTable[act->angle];
            act->fieldPosition.y -= gSineTable[act->angle + 64];
            p = act->fieldPosition;
            p.z = work->targetZ - 0x2800;

            if (FldSoraCheckBlocked(&p) == 0) {
                act->speed = 204;
                work->vz = -0x580;
                work->flags |= FLD_FLAG_NO_AIR_TURN;
                work->state = 7;
                work->timer = 0;
                m4aSongNumStart(work->sounds[6]);
            }
        } else if (d > 0) {
            if (act->fieldPosition.z >= limit) {
                act->fieldPosition.z = limit;
                act->angle += 0x80;
                act->fieldPosition.x += gSineTable[act->angle] * 10;
                act->fieldPosition.y += -gSineTable[act->angle + 64] * 10;
                FldSoraSetAnim(work, 0, 1);
                work->gfx = AnimGetGfx(&work->anim);
                work->state = 0;
                work->timer = 0;
                SetTaskUpdate(task, (TaskUpdateFunc)task_fld_sora_1);
            }
        } else if (d == 0) {
            if ((GetKeysHeld() & DPAD_UP) || ((GetKeysHeld() & DPAD_LEFT) && act->angle == 0xD3) ||
                ((GetKeysHeld() & DPAD_RIGHT) && act->angle == 0x2D)) {
                work->targetZ = ((work->targetZ >> 12) - 1) << 12;
            } else if ((GetKeysHeld() & DPAD_DOWN) || ((GetKeysHeld() & DPAD_RIGHT) && act->angle == 0xD3) ||
                       ((GetKeysHeld() & DPAD_LEFT) && act->angle == 0x2D)) {
                work->targetZ = ((work->targetZ >> 12) + 1) << 12;
            }
        }

        if (GetKeysPressed() & B_BUTTON) {
            work->vz = 0;
            work->timer = 0;
            work->state = 4;
            act->angle += 0x80;
            act->speed = 0x80;
            work->flags |= FLD_FLAG_NO_AIR_TURN;
            act->fieldPosition.x += gSineTable[act->angle] * 10;
            act->fieldPosition.y += -gSineTable[act->angle + 64] * 10;
            FldSoraSetAnim(work, 6, 0);
            work->gfx = AnimGetGfx(&work->anim);
            SetTaskUpdate(task, (TaskUpdateFunc)FldSoraJump);
        }

        break;
    case 7:
        FldSoraSetAnim(work, 11, 0);
        act->fieldPosition.x += gSineTable[act->angle] * act->speed >> 8;
        act->fieldPosition.y += -gSineTable[act->angle + 64] * act->speed >> 8;
        work->vz += 0x42;
        act->fieldPosition.z += work->vz;

        if (work->vz > 0) {
            work->timer = 0;
            work->state = 4;
            SetTaskUpdate(task, (TaskUpdateFunc)FldSoraJump);
        } else {
            work->timer++;
        }

        work->gfx = AnimUpdate(&work->anim);
        break;
    }

    if (FldSoraCheckBlocked(&act->fieldPosition) != 0) {
        act->fieldPosition.x = x;
        act->fieldPosition.y = y;
    }

    ColliderSetPosition(&work->collider, act->fieldPosition.x, act->fieldPosition.y, act->fieldPosition.z);
    MapSetCameraTarget(act->fieldPosition.x, act->fieldPosition.y + act->fieldPosition.z);
    TaskPoolUpdate(&work->tasks);
    return 1;
}
u8 FldSoraLedgeInput(FldWork* work, void* task) {
    FldActor* act;

    act = &gFieldState->actor;

    if ((GetKeysPressed() & B_BUTTON) || (GetKeysPressed() & DPAD_DOWN) ||
        (act->angle == 0xD3 && (GetKeysPressed() & DPAD_RIGHT)) ||
        (act->angle == 0x2D && (GetKeysPressed() & DPAD_LEFT))) {
        work->timer = 0;
        work->state = 4;
        work->vz = 0;
        act->angle += 0x80;
        gFieldState->lockonTarget = 0;
        SetTaskUpdate(task, (TaskUpdateFunc)FldSoraJump);
        return 1;
    }

    if ((GetKeysHeld() & DPAD_UP) ||
        (act->angle == 0xD3 && (GetKeysHeld() & DPAD_LEFT)) ||
        (act->angle == 0x2D && (GetKeysHeld() & DPAD_RIGHT))) {
        work->timer = 0;
        work->state = 10;
        act->speed = 0x133;
        work->vz = -0x5C0;
        work->flags |= FLD_FLAG_NO_AIR_TURN;
        m4aSongNumStart(SONG_SYS_SR_CATJP);
        gFieldState->lockonTarget = 0;
        return 1;
    }

    return 0;
}
u8 FldSoraHangLedge(FldWork* work, void* task) {
    FldActor* act;
    FldPos p;
    u8 ret;
    s32 x;
    s32 y;

    act = &gFieldState->actor;
    ret = 0;
    x = act->fieldPosition.x;
    y = act->fieldPosition.y;
    gFieldState->lockonTarget = 0;

    switch (work->state) {
    case 8:
        if (work->timer == 0) {
            p = act->fieldPosition;
            p.y -= 0xA00;
            act->fieldPosition.z = GetFldPosGround(&p) + 0x2B00;
            m4aSongNumStart(SONG_SYS_SR_CATCH);
            act->angle = GetLedgeAngleAt(act->fieldPosition.x, act->fieldPosition.y, act->fieldPosition.z);
            FldSoraSetAnim(work, 9, 0);
        }

        if (work->timer > 15) {
            ret = FldSoraLedgeInput(work, task);
        }

        act->fieldPosition.x += gSineTable[act->angle];
        act->fieldPosition.y -= gSineTable[act->angle + 64];

        if (AnimIsFinished(&work->anim) != 0 && ret == 0) {
            work->state = 9;
        } else {
            work->timer++;
        }

        break;
    case 9:
        FldSoraSetAnim(work, 10, 0);
        FldSoraLedgeInput(work, task);
        break;
    case 10:
        FldSoraSetAnim(work, 11, 0);
        act->fieldPosition.x += gSineTable[act->angle] * act->speed >> 8;
        act->fieldPosition.y += -gSineTable[act->angle + 64] * act->speed >> 8;
        act->fieldPosition.z += work->vz;
        work->vz += 0x42;

        if (work->vz > 0) {
            work->timer = 0;
            work->state = 4;
            SetTaskUpdate(task, (TaskUpdateFunc)FldSoraJump);
        } else {
            work->timer++;
        }

        break;
    }

    work->gfx = AnimUpdate(&work->anim);

    if (FldSoraCheckBlocked(&act->fieldPosition) != 0) {
        act->fieldPosition.x = x;
        act->fieldPosition.y = y;
    }

    ColliderSetPosition(&work->collider, act->fieldPosition.x, act->fieldPosition.y, act->fieldPosition.z);
    MapSetCameraTarget(act->fieldPosition.x, act->fieldPosition.y + act->fieldPosition.z);
    TaskPoolUpdate(&work->tasks);
    return 1;
}
u8 FldSoraWalkOut(FldWork* work, void* task) {
    FldActor* act;

    act = &gFieldState->actor;

    switch (work->state) {
    case 15:
        if (work->timer == 0) {
            work->flags |= FLD_FLAG_WALK_OUT;
            act->angle = 45;
            FldSoraSetAnim(work, 2, 1);

            if (gGameState.floor == 0) {
                act->fieldPosition.x = 0x32000;
            } else {
                act->fieldPosition.x = 0x22000;
            }

            act->fieldPosition.y = 0xF000;
            work->steps = 30;
            act->fieldPosition.z = 0;
            act->fieldPosition.ground = 0;
            work->targetX = act->fieldPosition.x + 0x2000;
            work->targetY = act->fieldPosition.y - 0x1000;
            work->targetZ = act->fieldPosition.ground - 0x2800;
        }

        if (work->steps > 0) {
            ApproachValue(&act->fieldPosition.x, work->targetX, work->steps);
            ApproachValue(&act->fieldPosition.y, work->targetY, work->steps);
            ApproachValue(&act->fieldPosition.z, work->targetZ, work->steps);
            act->fieldPosition.ground = act->fieldPosition.z;
            work->steps--;
        }

        if (work->anim.timer == 0) {
            switch (work->anim.frame) {
            case 3:
                m4aSongNumStart(work->sounds[0]);
                break;
            case 7:
                m4aSongNumStart(work->sounds[1]);
                break;
            }
        }

        if (work->steps <= 0) {
            work->timer = 0;

            if (work->flags & FLD_FLAG_TO_WORLD_SELECT) {
                work->state = 16;
            } else {
                work->state = 17;
            }
        } else {
            work->timer++;
        }

        break;
    case 16:
        if (work->timer == 0) {
            work->steps = 25;
            work->targetX = act->fieldPosition.x + 0x2000;
            work->targetY = act->fieldPosition.y - 0x1000;
        }

        if (work->steps > 0) {
            ApproachValue(&act->fieldPosition.x, work->targetX, work->steps);
            ApproachValue(&act->fieldPosition.y, work->targetY, work->steps);
            work->steps--;
        }

        if (work->anim.timer == 0) {
            switch (work->anim.frame) {
            case 3:
                m4aSongNumStart(work->sounds[0]);
                break;
            case 7:
                m4aSongNumStart(work->sounds[1]);
                break;
            }
        }

        if (work->steps <= 0) {
            work->timer = 0;
            work->state = 18;
        } else {
            work->timer++;
        }

        break;
    case 17:
        if (work->timer == 0) {
            work->steps = 25;
            work->targetX = act->fieldPosition.x + 0x2000;
            work->targetY = act->fieldPosition.y - 0x1000;
        }

        if (work->steps > 0) {
            ApproachValue(&act->fieldPosition.x, work->targetX, work->steps);
            ApproachValue(&act->fieldPosition.y, work->targetY, work->steps);
            work->steps--;
        }

        if (work->anim.timer == 0) {
            switch (work->anim.frame) {
            case 3:
                m4aSongNumStart(work->sounds[0]);
                break;
            case 7:
                m4aSongNumStart(work->sounds[1]);
                break;
            }
        }

        if (work->steps <= 0) {
            work->timer = 0;
            work->state = 19;
        } else {
            work->timer++;
        }

        break;
    case 18:
        if (work->timer == 0) {
            FldSoraSetAnim(work, 12, 0);
            FadeSetPaletteExcluded(work->palette->index + 16, 1);
        }

        if (work->timer == 40) {
            CreateWorldSelBeforeTask(&work->tasks, act->fieldPosition.x, act->fieldPosition.y, act->fieldPosition.z);
        }

        if (work->timer > 140) {
            work->timer = 0;
            work->state = 19;
        } else {
            work->timer++;
        }

        break;
    case 19:
        EndMapWalkOut();
        break;
    }

    ColliderSetPosition(&work->collider, act->fieldPosition.x, act->fieldPosition.y, act->fieldPosition.z);
    MapSetCameraTarget(act->fieldPosition.x, act->fieldPosition.y + act->fieldPosition.z);
    work->gfx = AnimUpdate(&work->anim);
    TaskPoolUpdate(&work->tasks);
    return 1;
}
u8 FldSoraAttack(FldWork* work, void* task) {
    FldActor* act;
    s32 x;
    s32 y;
    s32 nx;
    s32 ny;

    act = &gFieldState->actor;
    x = act->fieldPosition.x;
    y = act->fieldPosition.y;

    if (work->state == 11) {
        if (work->timer == 0) {
            FldSoraSetAnim(work, 13, 0);
            act->speed = 0;
            gFieldState->lockonTarget = 0;
            work->steps = 0;
            m4aSongNumStart(SONG_SYS_SR_AT_VO00);
        }

        if (work->anim.timer == 0) {
            switch (act->angle) {
            case 173:
                switch (AnimGetFrame(&work->anim)) {
                case 0:
                    act->fieldPosition.x -= 0x500;
                    act->fieldPosition.y += 0x400;
                    break;
                case 1:
                    act->fieldPosition.x -= 0x200;
                    break;
                case 2:
                    act->fieldPosition.x -= 0x300;
                    break;
                }

                break;
            case 83:
                switch (AnimGetFrame(&work->anim)) {
                case 0:
                    act->fieldPosition.x += 0x500;
                    act->fieldPosition.y += 0x400;
                    break;
                case 1:
                    act->fieldPosition.x += 0x200;
                    break;
                case 2:
                    act->fieldPosition.x += 0x300;
                    break;
                }

                break;
            case 211:
                switch (AnimGetFrame(&work->anim)) {
                case 0:
                    act->fieldPosition.x -= 0x500;
                    act->fieldPosition.y -= 0x200;
                    break;
                case 1:
                    act->fieldPosition.x -= 0x500;
                    break;
                case 2:
                    act->fieldPosition.x -= 0x200;
                    break;
                }

                break;
            case 45:
                switch (AnimGetFrame(&work->anim)) {
                case 0:
                    act->fieldPosition.x += 0x500;
                    act->fieldPosition.y -= 0x200;
                    break;
                case 1:
                    act->fieldPosition.x += 0x500;
                    break;
                case 2:
                    act->fieldPosition.x += 0x200;
                    break;
                }

                break;
            case 128:
                switch (AnimGetFrame(&work->anim)) {
                case 0:
                    act->fieldPosition.x -= 0x300;
                    act->fieldPosition.y += 0x400;
                    break;
                case 1:
                    act->fieldPosition.x += 0x100;
                    act->fieldPosition.y += 0x100;
                    break;
                case 2:
                    act->fieldPosition.y += 0x200;
                    break;
                case 3:
                    act->fieldPosition.y += 0x100;
                    break;
                }

                break;
            case 64:
                switch (AnimGetFrame(&work->anim)) {
                case 0:
                    act->fieldPosition.x += 0x700;
                    act->fieldPosition.y += 0x100;
                    break;
                case 1:
                    act->fieldPosition.x += 0x300;
                    break;
                case 2:
                    act->fieldPosition.x += 0x200;
                    break;
                }

                break;
            case 192:
                switch (AnimGetFrame(&work->anim)) {
                case 0:
                    act->fieldPosition.x -= 0x700;
                    act->fieldPosition.y += 0x100;
                    break;
                case 1:
                    act->fieldPosition.x -= 0x300;
                    break;
                case 2:
                    act->fieldPosition.x -= 0x200;
                    break;
                }

                break;
            case 0:
                switch (AnimGetFrame(&work->anim)) {
                case 0:
                    act->fieldPosition.y -= 0x400;
                    break;
                case 1:
                    act->fieldPosition.y -= 0x400;
                    break;
                case 2:
                    act->fieldPosition.x -= 0x100;
                    act->fieldPosition.y += 0x100;
                    break;
                case 3:
                    act->fieldPosition.y -= 0x100;
                    break;
                }

                break;
            }
        }

        if (AnimGetFrame(&work->anim) == 2) {
            switch (act->angle) {
            case 45:
            case 211:
                nx = act->fieldPosition.x + gSineTable[act->angle] * 12;
                ny = act->fieldPosition.y + -gSineTable[act->angle + 64] * 12;
                break;
            case 64:
            case 192:
                nx = act->fieldPosition.x + gSineTable[act->angle] * 27;
                ny = act->fieldPosition.y + -gSineTable[act->angle + 64] * 27;
                break;
            case 0:
            case 83:
            case 128:
            case 173:
            default:
                nx = act->fieldPosition.x + gSineTable[act->angle] * 20;
                ny = act->fieldPosition.y + -gSineTable[act->angle + 64] * 20;
                break;
            }

            SetMapAttackBox(nx, ny, act->fieldPosition.z - 0x800);
        }

        if (AnimIsFinished(&work->anim) != 0) {
            switch (act->angle) {
            case 173:
                act->fieldPosition.x -= 0x200;
                act->fieldPosition.y += 0x200;
                break;
            case 83:
                act->fieldPosition.x += 0x200;
                act->fieldPosition.y += 0x200;
                break;
            case 45:
            case 211:
                act->fieldPosition.y -= 0x400;
                break;
            case 128:
                act->fieldPosition.y += 0x200;
                break;
            case 0:
                act->fieldPosition.y -= 0x200;
                break;
            }

            FldSoraSetAnim(work, 0, 0);
            work->state = 0;
            SetTaskUpdate(task, (TaskUpdateFunc)task_fld_sora_1);
        } else {
            work->timer++;
        }
    }

    if (work->collider.colliding != 0) {
        switch ((u32)work->collider.otherType) {
        case 5:
        case 3:
        case 11:
            break;
        default:
            if ((work->collider.standFlags & COLLIDER_STAND_OVER_PLATFORM) == 0) {
                act->fieldPosition.x += work->collider.pushX;
                act->fieldPosition.y += work->collider.pushY;
            }

            break;
        }
    }

    if (FldSoraCheckBlocked(&act->fieldPosition) != 0) {
        act->fieldPosition.x = x;
        act->fieldPosition.y = y;
    }

    ColliderSetPosition(&work->collider, act->fieldPosition.x, act->fieldPosition.y, act->fieldPosition.z);
    MapSetCameraTarget(act->fieldPosition.x, act->fieldPosition.y + act->fieldPosition.z);
    work->gfx = AnimUpdate(&work->anim);
    TaskPoolUpdate(&work->tasks);

    if (gFieldState->flags & FIELD_FLAG_ROOM_CREATE) {
        work->timer = 0;
        SetTaskUpdate(task, (TaskUpdateFunc)FldSoraWaitRoomCreate);
    }

    return 1;
}
u8 task_fld_sora_1(FldWork* work, void* task) {
    FldPos p1;
    FldPos p2;
    FldPos p3;
    FldPos p4;
    s32 sx;
    s32 sy;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 dw;
    s32 z;
    s32 r;
    u8 a;
    u8 b;
    FldActor* act;

    act = &gFieldState->actor;

    if ((work->flags & FLD_FLAG_RESTORE_STATE) != 0) {
        work->flags &= ~FLD_FLAG_RESTORE_STATE;

        switch (work->state) {
        case 12:
            work->state = 3;
        case 2:
        case 3:
        case 4:
            gFieldState->flags |= FIELD_FLAG_PLAYER_JUMPING;
        case 5:
            SetTaskUpdate(task, (TaskUpdateFunc)FldSoraJump);
            gFieldState->lockonTarget = 0;
            break;
        case 6:
        case 7:
            SetTaskUpdate(task, (TaskUpdateFunc)FldSoraClimb);
            gFieldState->lockonTarget = 0;
            work->timer = 1;
            break;
        case 8:
        case 9:
        case 10:
            SetTaskUpdate(task, (TaskUpdateFunc)FldSoraHangLedge);
            gFieldState->lockonTarget = 0;
            break;
        default:
            work->state = 0;
            break;
        }

        ColliderSetPosition(&work->collider, act->fieldPosition.x, act->fieldPosition.y, act->fieldPosition.z);
        MapSetCameraTarget(act->fieldPosition.x, act->fieldPosition.y + act->fieldPosition.z);
        work->gfx = AnimUpdate(&work->anim);
        TaskPoolUpdate(&work->tasks);
        return 1;
    } else if (GetMapWalkOutMode() != 0) {
        work->timer = 0;
        SetTaskUpdate(task, (TaskUpdateFunc)FldSoraWalkOut);
        TaskPoolUpdate(&work->tasks);
        work->state = 15;

        if (GetMapWalkOutMode() == 1) {
            work->flags |= FLD_FLAG_TO_WORLD_SELECT;
        }

        return 1;
    } else if ((gFieldState->flags & FIELD_FLAG_ROOM_CREATE) != 0) {
        work->timer = 0;
        SetTaskUpdate(task, (TaskUpdateFunc)FldSoraWaitRoomCreate);
        TaskPoolUpdate(&work->tasks);
        return 1;
    } else {
        sx = act->fieldPosition.x;
        sy = act->fieldPosition.y;

        if (work->state <= 1) {
            if ((gFieldState->flags & 0x4000) == 0) {
                FldSoraTurn(act);
            }

            if ((gFieldState->flags & 0x4000) == 0 && (GetKeysHeld() & DPAD_ANY) != 0) {
                act->speed += 128;
                FldSoraSetAnim(work, 2, 1);

                if (act->speed > 0x266) {
                    act->speed = 0x266;
                }

                if (work->anim.timer == 0) {
                    switch (work->anim.frame) {
                    case 3:
                        m4aSongNumStart(work->sounds[0]);
                        break;
                    case 7:
                        m4aSongNumStart(work->sounds[1]);
                        break;
                    }
                }
            } else {
                FldSoraSetAnim(work, 0, 1);
                act->speed -= 128;

                if (act->speed < 0) {
                    act->speed = 0;
                }
            }

            act->fieldPosition.x += gSineTable[act->angle] * act->speed >> 8;
            act->fieldPosition.y += -gSineTable[act->angle + 64] * act->speed >> 8;

            if ((GetKeysPressed() & B_BUTTON) != 0) {
                gFieldState->lockonTarget = 0;
                gFieldState->flags |= FIELD_FLAG_PLAYER_JUMPING;
                work->timer = 0;
                work->state = 2;
                SetTaskUpdate(task, (TaskUpdateFunc)FldSoraJump);
                m4aSongNumStart(work->sounds[2]);
            } else if ((GetKeysPressed() & A_BUTTON) != 0) {
                work->timer = 0;
                gFieldState->lockonTarget = 0;
                work->state = 11;
                SetTaskUpdate(task, (TaskUpdateFunc)FldSoraAttack);
            }
        } else if (AnimIsFinished(&work->anim) != 0) {
            work->state = 0;
        }

        if (work->collider.colliding != 0) {
            switch ((u32)work->collider.otherType) {
            case 3:
            case 5:
            case 11:
                break;
            default:
                if ((work->collider.standFlags & COLLIDER_STAND_OVER_PLATFORM) == 0) {
                    act->speed = 230 * act->speed >> 8;
                    act->fieldPosition.x += work->collider.pushX;
                    act->fieldPosition.y += work->collider.pushY;
                }
                break;
            }
        }

        if (FldSoraCheckBlocked(&act->fieldPosition) != 0) {
            act->fieldPosition.x = sx;
            act->fieldPosition.y = sy;
            r = FldSoraCheckClimb(&act->fieldPosition, work);

            if (r != 0) {
                switch (r) {
                case 2:
                    work->timer = 0;
                    work->state = 6;
                    act->angle = 211;
                    gFieldState->lockonTarget = 0;
                    SetTaskUpdate(task, (TaskUpdateFunc)FldSoraClimb);
                    break;
                case 1:
                    work->timer = 0;
                    work->state = 6;
                    act->angle = 45;
                    gFieldState->lockonTarget = 0;
                    SetTaskUpdate(task, (TaskUpdateFunc)FldSoraClimb);
                    break;
                }
            } else {
                if (FldSoraCheckDoorAhead(act) != 0) {
                    FadeSetPaletteExcluded(work->palette->index + 16, 1);
                    gFieldState->flags |= FIELD_FLAG_EXIT_ROOM;
                    return 1;
                }

                switch (act->angle) {
                case 173:
                    dx = -256;
                    dy = 0;
                    dz = 0;
                    dw = 384;
                    break;
                case 83:
                    dx = 256;
                    dy = 0;
                    dz = 0;
                    dw = 384;
                    break;
                case 211:
                    dx = -256;
                    dy = 0;
                    dz = 0;
                    dw = -384;
                    break;
                case 45:
                    dx = 256;
                    dy = 0;
                    dz = 0;
                    dw = -384;
                    break;
                case 128:
                    dx = -512;
                    dy = 192;
                    dz = 512;
                    dw = 192;
                    break;
                case 0:
                    dx = -512;
                    dy = -192;
                    dz = 512;
                    dw = -192;
                    break;
                case 64:
                    dx = 384;
                    dy = -307;
                    dz = 384;
                    dw = 307;
                    break;
                case 192:
                    dx = -384;
                    dy = -307;
                    dz = -384;
                    dw = 307;
                    break;
                default:
                    dw = 0;
                    dz = 0;
                    dy = 0;
                    dx = 0;
                    break;
                }

                p2 = act->fieldPosition;
                p1 = p2;
                p1.x += dx;
                p1.y += dy;
                p2.x += dz;
                p2.y += dw;
                a = FldSoraCheckBlocked(&p1);
                b = FldSoraCheckBlocked(&p2);

                if (a != 0) {
                    if (b == 0) {
                        p3 = act->fieldPosition;
                        p3.x += dz;
                        p3.y += dw;
                        p3.ground = FldSoraProbeGround(&p3);

                        if (p3.ground >= p3.z) {
                            act->fieldPosition = p3;
                        }
                    }
                } else if (b != 0) {
                    p4 = act->fieldPosition;
                    p4.x += dx;
                    p4.y += dy;
                    p4.ground = FldSoraProbeGround(&p4);

                    if (p4.ground >= p4.z) {
                        act->fieldPosition = p4;
                    }
                }

                act->speed = 0;
            }
        }

        z = FldSoraGetGround(work);

        if (act->fieldPosition.ground == 0x100000) {
            act->fieldPosition.ground = act->fieldPosition.z;
        } else if (z != act->fieldPosition.z) {
            act->speed >>= 2;
            work->vz = 0;
            work->timer = 0;
            gFieldState->lockonTarget = 0;
            gFieldState->flags |= FIELD_FLAG_PLAYER_JUMPING;
            work->state = 4;
            SetTaskUpdate(task, (TaskUpdateFunc)FldSoraJump);
        } else if (z != act->fieldPosition.ground) {
            gFieldState->lockonTarget = 0;
        }
    }

    ColliderSetPosition(&work->collider, act->fieldPosition.x, act->fieldPosition.y, act->fieldPosition.z);
    MapSetCameraTarget(act->fieldPosition.x, act->fieldPosition.y + act->fieldPosition.z);
    work->gfx = AnimUpdate(&work->anim);
    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_fld_sora_2(FldWork* work) {
    FldActor* act;
    u16 depth;
    s32 pri;
    s32 x;
    s32 y;
    s32 z;

    act = &gFieldState->actor;
    pri = (work->flags & FLD_FLAG_HFLIP) ? 0x801 : 0x800;

    if (work->onCollider != 0) {
        depth = -0x1006 - (work->collider.platformY >> 8) * 4;

        if (work->collider.penetration <= work->collider.radius) {
            act->shadowPriority = 0;
            act->shadowZ = GetFldPosGround(&act->fieldPosition);
        } else {
            act->shadowZ = work->collider.platformZ;
            act->shadowPriority = depth + 1;
        }
    } else {
        depth = -0x1004 - (act->fieldPosition.y >> 8) * 4;

        if (work->flags & FLD_FLAG_WALK_OUT) {
            act->shadowZ = act->fieldPosition.ground;
        } else {
            act->shadowZ = GetFldPosGround(&act->fieldPosition);
        }

        if (act->shadowZ != act->fieldPosition.ground) {
            act->shadowPriority = 0;
        } else {
            act->shadowPriority = depth + 1;
        }
    }

    x = (act->fieldPosition.x >> 8) - (gFieldState->x >> 8);
    y = (act->fieldPosition.y >> 8) + (act->fieldPosition.z >> 8) - (gFieldState->y >> 8);
    DrawSprite(x, y, work->gfx, work->tiles, work->palette, 0, pri, depth);
    TaskPoolDraw(&work->tasks);
}

void task_fld_sora_3(FldWork* work) {
    FldActor* act;

    act = &gFieldState->actor;
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);

    if (gGameState.fieldResume != 0) {
        gGameState.fieldSpeed = act->speed;
        gGameState.fieldPosition = act->fieldPosition;
        gGameState.fieldAngle = act->angle;
        gGameState.fieldState = work->state;
        gGameState.fieldVz = work->vz;
        gGameState.fieldTargetX = work->targetX;
        gGameState.fieldTargetY = work->targetY;
        gGameState.fieldTargetZ = work->targetZ;
    } else {
        gGameState.fieldAngle = act->angle;
    }

    TaskPoolDestroy(&work->tasks);
}

void FldRikuSetAngleFromDpad(FldActor* act) {
    if ((GetKeysHeld() & DPAD_LEFT) && (GetKeysHeld() & DPAD_DOWN)) {
        act->angle = 0xAD;
    } else if ((GetKeysHeld() & DPAD_UP) && (GetKeysHeld() & DPAD_LEFT)) {
        act->angle = 0xD3;
    } else if ((GetKeysHeld() & DPAD_UP) && (GetKeysHeld() & DPAD_RIGHT)) {
        act->angle = 0x2D;
    } else if ((GetKeysHeld() & DPAD_RIGHT) && (GetKeysHeld() & DPAD_DOWN)) {
        act->angle = 0x53;
    } else if ((GetKeysHeld() & DPAD_DOWN) && GetKeyReleaseTime(DPAD_LEFT) <= 4) {
        act->angle = 0xAD;
    } else if ((GetKeysHeld() & DPAD_DOWN) && GetKeyReleaseTime(DPAD_RIGHT) <= 4) {
        act->angle = 0x53;
    } else if ((GetKeysHeld() & DPAD_UP) && GetKeyReleaseTime(DPAD_LEFT) <= 4) {
        act->angle = 0xD3;
    } else if ((GetKeysHeld() & DPAD_UP) && GetKeyReleaseTime(DPAD_RIGHT) <= 4) {
        act->angle = 0x2D;
    } else if ((GetKeysHeld() & DPAD_LEFT) && GetKeyReleaseTime(DPAD_UP) <= 4) {
        act->angle = 0xD3;
    } else if ((GetKeysHeld() & DPAD_LEFT) && GetKeyReleaseTime(DPAD_DOWN) <= 4) {
        act->angle = 0xAD;
    } else if ((GetKeysHeld() & DPAD_RIGHT) && GetKeyReleaseTime(DPAD_UP) <= 4) {
        act->angle = 0x2D;
    } else if ((GetKeysHeld() & DPAD_RIGHT) && GetKeyReleaseTime(DPAD_DOWN) <= 4) {
        act->angle = 0x53;
    } else if (GetKeysHeld() & DPAD_DOWN) {
        act->angle = 0x80;
    } else if (GetKeysHeld() & DPAD_UP) {
        act->angle = 0;
    } else if (GetKeysHeld() & DPAD_LEFT) {
        act->angle = 0xC0;
    } else if (GetKeysHeld() & DPAD_RIGHT) {
        act->angle = 0x40;
    }
}

u8 FldRikuCheckBlocked(FldPos* p) {
    FldPos a;
    FldPos b;
    s32 lo;
    s32 hi;
    s32 v;

    a = *p;
    b = *p;
    a.y -= 0x600;
    b.y += 0x600;

    lo = GetFldPosGround(&a);

    if (lo > a.ground) {
        a.ground = lo;
    }

    hi = GetFldPosGround(&b);

    if (hi > b.ground) {
        b.ground = hi;
    }

    if (IsFldPosBlocked(&a) != 0 || IsFldPosBlocked(&b) != 0) {
        return 1;
    }

    v = hi;

    if (v > lo) {
        v = lo;
    }

    p->ground = v;
    return 0;
}

s32 FldRikuProbeGround(FldPos* p) {
    FldPos a;
    FldPos b;
    s32 lo;
    s32 hi;

    a = *p;
    b = *p;
    a.y -= 0x600;
    b.y += 0x600;

    lo = GetFldPosGround(&a);
    hi = GetFldPosGround(&b);

    if (hi > lo) {
        hi = lo;
    }

    return hi;
}

u8 FldRikuCheckClimb(FldPos* p, FldWork* work) {
    FldPos a;
    FldPos b;
    u8 hit;

    a = *p;
    b = *p;
    a.y -= 0x600;
    b.y += 0x600;

    hit = _080DFE1C(&a);

    if (hit != 0) {
        work->targetX = a.x;
        work->targetY = a.y;
        return hit;
    }

    hit = _080DFE1C(&b);

    if (hit != 0) {
        work->targetX = b.x;
        work->targetY = b.y;
        return hit;
    }

    return 0;
}

u8 FldRikuCheckDoorAhead(FldActor* act) {
    FldPos v;

    v = act->fieldPosition;
    v.x += gSineTable[act->angle] * 8;
    v.y -= gSineTable[act->angle + 64] * 8;

    if (MapFindOpenDoor(&v) != 0) {
        return 1;
    }

    return 0;
}

s32 FldRikuGetGround(FldWork* work) {
    FldActor* act;
    s32 v;

    act = &gFieldState->actor;

    if (work->collider.standFlags & COLLIDER_STAND_OVER_PLATFORM) {
        if (act->fieldPosition.ground < work->collider.platformZ) {
            v = act->fieldPosition.ground;
        } else {
            v = work->collider.platformZ;
        }

        work->onCollider = 1;
    } else {
        work->onCollider = 0;
        v = act->fieldPosition.ground;
    }

    return v;
}

void FldRikuTurn(FldActor* act) {
    u8 dir;
    s32 diff;

    dir = act->angle;
    FldRikuSetAngleFromDpad(act);

    if (dir != act->angle) {
        diff = (s8)GetAngleDiff(dir, act->angle);

        if (diff < 0) {
            diff = -diff;
        }

        if (diff > 100) {
            act->speed = 0;
        } else {
            act->speed = act->speed >> 1;
        }
    }
}

void FldRikuSetAnim(FldWork* work, s32 index, u16 flags) {
    const FldAnimDef* def;
    s32 dir;

    switch (gFieldState->actor.angle) {
    case 0x2D:
        dir = 4;
        work->flags |= FLD_FLAG_HFLIP;
        break;
    case 0x40:
        dir = 3;
        work->flags |= FLD_FLAG_HFLIP;
        break;
    case 0x53:
        dir = 2;
        work->flags |= FLD_FLAG_HFLIP;
        break;
    case 0x80:
        dir = 1;
        work->flags &= ~FLD_FLAG_HFLIP;
        break;
    case 0xAD:
        dir = 2;
        work->flags &= ~FLD_FLAG_HFLIP;
        break;
    case 0xC0:
        dir = 3;
        work->flags &= ~FLD_FLAG_HFLIP;
        break;
    case 0xD3:
        dir = 4;
        work->flags &= ~FLD_FLAG_HFLIP;
        break;
    case 0x00:
    default:
        dir = 0;
        work->flags &= ~FLD_FLAG_HFLIP;
        break;
    }

    if (work->animAction == index) {
        flags |= 4;
    }

    work->animAction = index;
    def = &sFldRikuAnimDefs[index][dir];
    AnimChangeWithTables(&work->anim, def->animId, flags, def->anims, def->gfxTable);
    SetObjTileSource(work->tiles, def->tiles);
}

void task_fld_riku_0(FldWork* work) {
    FldActor* act;

    act = &gFieldState->actor;
    work->tiles = AllocObjTiles(0xA00, 0);
    work->palette = LoadObjPalette(gRikuPalette, 32);
    act->height = 16;
    work->onCollider = 0;
    work->unk_9C = 0;
    work->unk_9D = 0;
    work->unk_9E = 0;
    work->timer = 0;
    work->flags = FLD_FLAG_RESTORE_STATE;
    work->animAction = 16;
    act->unk_32 = 0;
    act->kind = 0;

    if (gGameState.fieldResume != 0) {
        act->fieldPosition = gGameState.fieldPosition;
        act->angle = gGameState.fieldAngle;
        act->speed = gGameState.fieldSpeed;
        work->state = gGameState.fieldState;
        work->vz = gGameState.fieldVz;
        work->targetX = gGameState.fieldTargetX;
        work->targetY = gGameState.fieldTargetY;
        work->targetZ = gGameState.fieldTargetZ;
    } else {
        act->fieldPosition.x = gFieldState->spawnX;
        act->fieldPosition.y = gFieldState->spawnY;
        act->fieldPosition.z = 0;
        act->angle = gFieldState->spawnAngle;
        FldPosInitGround(&act->fieldPosition);
        act->fieldPosition.z = act->fieldPosition.ground;
        act->fieldPosition.y -= act->fieldPosition.ground;
        act->speed = 0;
        work->state = 0;
        work->vz = 0;
    }

    AnimInit(&work->anim, 0, 0);
    FldRikuSetAnim(work, 0, 1);
    work->gfx = AnimGetGfx(&work->anim);

    switch (gGameState.world) {
    case WORLD_NEVER_LAND:
        work->sounds = sFldRikuSounds[1];
        break;
    case WORLD_ATLANTICA:
        work->sounds = sFldRikuSounds[2];
        break;
    case WORLD_MONSTRO:
        work->sounds = sFldRikuSounds[3];
        break;
    case WORLD_WONDERLAND:
        work->sounds = sFldRikuSounds[4];
        break;
    case WORLD_HALLOWEEN_TOWN:
        work->sounds = sFldRikuSounds[5];
        break;
    case 0:
    case WORLD_OLYMPUS_COLISEUM:
    case WORLD_CASTLE_OBLIVION:
        work->sounds = sFldRikuSounds[6];
        break;
    case WORLD_DESTINY_ISLANDS:
        work->sounds = sFldRikuSounds[7];
        break;
    default:
        work->sounds = sFldRikuSounds[0];
        break;
    }

    TaskPoolInit(&work->tasks, 2);
    TaskCreate(&work->tasks, &gTaskDescFldShadow, &gFieldState->actor);
    ColliderInit(&work->collider, 1, 4, 32);
    ColliderSetPosition(&work->collider, act->fieldPosition.x, act->fieldPosition.y, act->fieldPosition.z);
}
u8 FldRikuWaitRoomCreate(FldWork* work, void* task) {
    FldActor* act;
    s16* p;
    s32 flags;

    act = &gFieldState->actor;
    flags = gFieldState->flags;

    if (flags & FIELD_FLAG_CARD_POSE) {
        FldRikuSetAnim(work, 12, 0);
    } else if (flags & FIELD_FLAG_AUTO_WALK) {
        FldRikuSetAnim(work, 1, 1);
    } else {
        FldRikuSetAnim(work, 0, 1);
    }

    if ((gFieldState->flags & FIELD_FLAG_ROOM_CREATE) == 0) {
        FadeSetPaletteExcluded(work->palette->index + 16, 0);
        work->state = 0;
        work->timer = 0;
        SetTaskUpdate(task, (TaskUpdateFunc)task_fld_riku_1);
        TaskPoolUpdate(&work->tasks);
    } else {
        p = &work->timer;

        if (*p == 0) {
            FadeSetPaletteExcluded(work->palette->index + 16, 1);
            act->speed = 0;
            work->onCollider = 0;
        }

        TaskPoolUpdate(&work->tasks);
        work->gfx = AnimUpdate(&work->anim);
        ColliderSetPosition(&work->collider, act->fieldPosition.x, act->fieldPosition.y, act->fieldPosition.z);
        (*p)++;
    }

    return 1;
}
u8 FldRikuGmkJump(FldWork* work, void* task) {
    FldActor* act;
    s32 x;
    s32 y;
    s32 z;

    act = &gFieldState->actor;
    x = act->fieldPosition.x;
    y = act->fieldPosition.y;
    gFieldState->lockonTarget = 0;

    switch (work->state) {
    case 13:
        m4aSongNumStart(SONG_SYS_GIMICJP);
        work->state = 14;
        work->vz = -0x800;
        work->timer = 0;
        act->speed = 0;
        work->targetX = work->collider.platformX;
        work->targetY = work->collider.platformY;
        break;
    case 14:
        if (work->vz > -0x300) {
            FldRikuSetAnim(work, 11, 0);
            act->speed = 0x180;
            act->fieldPosition.x += gSineTable[act->angle] * act->speed >> 8;
            act->fieldPosition.y += -gSineTable[act->angle + 64] * act->speed >> 8;
        } else {
            FldRikuSetAnim(work, 4, 0);
            act->fieldPosition.x += (work->targetX - act->fieldPosition.x) >> 3;
            act->fieldPosition.y += (work->targetY - act->fieldPosition.y) >> 3;
        }

        work->vz = (work->targetZ - (z = act->fieldPosition.z + 0xF00)) >> 3;
        act->fieldPosition.z += work->vz;
        work->vz += 0x42;

        if (work->vz >= 0) {
            work->timer = 0;
            work->state = 4;
            work->flags |= FLD_FLAG_NO_AIR_TURN;
            SetTaskUpdate(task, (TaskUpdateFunc)FldRikuJump);
        } else {
            work->timer++;
        }

        break;
    }

    if (FldRikuCheckBlocked(&act->fieldPosition) != 0) {
        act->fieldPosition.x = x;
        act->fieldPosition.y = y;
    }

    ColliderSetPosition(&work->collider, act->fieldPosition.x, act->fieldPosition.y, act->fieldPosition.z);
    MapSetCameraTarget(act->fieldPosition.x, act->fieldPosition.y + act->fieldPosition.z);
    work->gfx = AnimUpdate(&work->anim);
    TaskPoolUpdate(&work->tasks);
    return 1;
}
u8 FldRikuJump(FldWork* work, void* task) {
    FldPos p1;
    FldPos p2;
    s32 sx;
    s32 sy;
    s32 nx;
    s32 ny;
    s32 z;
    FldActor* act;

    act = &gFieldState->actor;
    z = FldRikuGetGround(work);
    sx = act->fieldPosition.x;
    sy = act->fieldPosition.y;
    gFieldState->lockonTarget = 0;

    if ((work->flags & FLD_FLAG_NO_AIR_TURN) == 0) {
        FldRikuTurn(act);
    }

    switch (work->state) {
    case 12:
        if (work->timer == 0) {
            gFieldState->lockonTarget = 0;
            FldRikuSetAnim(work, 14, 0);
        }

        act->fieldPosition.x += gSineTable[act->angle] * act->speed >> 8;
        act->fieldPosition.y += -gSineTable[act->angle + 64] * act->speed >> 8;

        if (AnimGetFrame(&work->anim) > 3) {
            act->fieldPosition.z += work->vz;
            work->vz += 66;

            if (act->fieldPosition.z > z) {
                act->fieldPosition.z = z;
                work->vz = 0;
            }
        } else {
            work->vz = 0;
        }

        act->speed -= 38;

        if (act->speed < 0) {
            act->speed = 0;
        }

        switch (AnimGetFrame(&work->anim)) {
        case 1:
            switch (act->angle) {
            case 45:
            case 211:
                nx = act->fieldPosition.x + gSineTable[act->angle] * 12;
                ny = act->fieldPosition.y + -gSineTable[act->angle + 64] * 12;
                break;
            case 64:
            case 192:
                nx = act->fieldPosition.x + gSineTable[act->angle] * 27;
                ny = act->fieldPosition.y + -gSineTable[act->angle + 64] * 27;
                break;
            case 0:
            case 83:
            case 128:
            case 173:
            default:
                nx = act->fieldPosition.x + gSineTable[act->angle] * 20;
                ny = act->fieldPosition.y + -gSineTable[act->angle + 64] * 20;
                break;
            }

            SetMapAttackBox(nx, ny, act->fieldPosition.z - 0x800);
            break;
        }

        if (AnimIsFinished(&work->anim) != 0) {
            if (work->vz < 0) {
                work->state = 3;
            } else {
                work->state = 4;
            }
        } else {
            work->timer++;
        }

        break;
    case 2:
        if (work->timer == 0) {
            FldRikuSetAnim(work, 3, 0);
            act->speed >>= 1;
        }

        act->fieldPosition.x += gSineTable[act->angle] * act->speed >> 8;
        act->fieldPosition.y += -gSineTable[act->angle + 64] * act->speed >> 8;

        if (work->timer > 3) {
            work->targetZ = gMapRoomState->jumpGmkHeight;

            if (work->targetZ == 0) {
                if (GetRandom() % 2 != 0) {
                    m4aSongNumStart(SONG_SND_225);
                } else {
                    m4aSongNumStart(SONG_SND_226);
                }

                work->state = 3;
                work->vz = -1536;
                act->speed <<= 1;
                work->timer = 0;
                act->fieldPosition.z += work->vz;
                work->vz += 66;
            } else {
                act->angle = gMapRoomState->jumpGmkAngle;
                work->targetZ = act->fieldPosition.z - work->targetZ;
                work->state = 13;
                SetTaskUpdate(task, (TaskUpdateFunc)FldRikuGmkJump);
                work->timer = 0;
            }
        } else {
            work->timer++;
        }

        break;
    case 3:
        if ((GetKeysHeld() & DPAD_ANY) != 0) {
            act->speed += 17;

            if (act->speed > 512) {
                act->speed = 512;
            }
        } else {
            act->speed -= 38;

            if (act->speed < 0) {
                act->speed = 0;
            }
        }

        if (work->vz > -512) {
            FldRikuSetAnim(work, 5, 0);
        } else {
            FldRikuSetAnim(work, 4, 0);
        }

        act->fieldPosition.x += gSineTable[act->angle] * act->speed >> 8;
        act->fieldPosition.y += -gSineTable[act->angle + 64] * act->speed >> 8;
        act->fieldPosition.z += work->vz;
        work->vz += 66;

        if (work->vz < 0) {
            if ((GetKeysHeld() & B_BUTTON) == 0) {
                work->vz += 64;
            }
        }

        if ((GetKeysPressed() & A_BUTTON) != 0) {
            work->timer = 0;
            work->state = 12;
        } else if (work->vz > 0) {
            work->timer = 0;
            work->state = 4;
        } else {
            work->timer++;
        }

        break;
    case 4:
        if ((GetKeysHeld() & DPAD_ANY) != 0) {
            act->speed += 17;

            if (act->speed > 512) {
                act->speed = 512;
            }
        } else {
            act->speed -= 38;

            if (act->speed < 0) {
                act->speed = 0;
            }
        }

        if (work->vz < 0x200) {
            FldRikuSetAnim(work, 5, 0);
        } else {
            FldRikuSetAnim(work, 6, 0);
        }

        act->fieldPosition.x += gSineTable[act->angle] * act->speed >> 8;
        act->fieldPosition.y += -gSineTable[act->angle + 64] * act->speed >> 8;
        act->fieldPosition.z += work->vz;
        work->vz += 66;

        if ((GetKeysPressed() & A_BUTTON) != 0) {
            work->timer = 0;
            work->state = 12;
        } else if (act->fieldPosition.z > z) {
            act->fieldPosition.z = z;
            work->vz = 0;

            if (work->state != 5) {
                work->state = 5;
                work->timer = 0;
            }
        }

        break;
    case 5:
        if (work->timer == 0) {
            FldRikuSetAnim(work, 7, 0);
            m4aSongNumStart(work->sounds[3]);
        }

        act->speed = 0;

        if ((GetKeysPressed() & B_BUTTON) != 0) {
            work->flags &= ~FLD_FLAG_NO_AIR_TURN;
            work->timer = 0;
            work->state = 2;
        } else if (work->timer > 6) {
            gFieldState->flags &= ~FIELD_FLAG_PLAYER_JUMPING;
            work->flags &= ~FLD_FLAG_NO_AIR_TURN;
            work->state = 0;
            work->timer = 0;
            SetTaskUpdate(task, (TaskUpdateFunc)task_fld_riku_1);
        } else {
            work->timer++;
        }

        break;
    }

    if (work->collider.colliding != 0) {
        switch ((u32)work->collider.otherType) {
        case 3:
        case 5:
        case 11:
            break;
        default:
            if ((work->collider.standFlags & COLLIDER_STAND_OVER_PLATFORM) == 0) {
                act->speed = 230 * act->speed >> 8;
                act->fieldPosition.x += work->collider.pushX;
                act->fieldPosition.y += work->collider.pushY;
            }
            break;
        }
    }

    if (FldRikuCheckBlocked(&act->fieldPosition) != 0) {
        act->fieldPosition.x = sx;
        act->fieldPosition.y = sy;

        switch (FldRikuCheckClimb(&act->fieldPosition, work)) {
        case 2:
            work->timer = 0;
            work->state = 6;
            act->angle = 211;
            SetTaskUpdate(task, (TaskUpdateFunc)FldRikuClimb);
            break;
        case 1:
            work->timer = 0;
            work->state = 6;
            act->angle = 45;
            SetTaskUpdate(task, (TaskUpdateFunc)FldRikuClimb);
            break;
        default:
            if (work->state == 4 && act->fieldPosition.ground - act->fieldPosition.z > 0xFFF) {
                p1 = act->fieldPosition;
                p1.y -= 0x400;
                p1.z = act->fieldPosition.z - 0x3000;
                p2 = p1;
                p2.z += 768;

                if (FldRikuCheckBlocked(&p1) == 0 && FldRikuCheckBlocked(&p2) != 0) {
                    work->timer = 0;
                    work->state = 8;
                    gFieldState->lockonTarget = 0;
                    SetTaskUpdate(task, (TaskUpdateFunc)FldRikuHangLedge);
                }
            } else {
                act->speed = 230 * act->speed >> 8;
            }
            break;
        }
    }

    ColliderSetPosition(&work->collider, act->fieldPosition.x, act->fieldPosition.y, act->fieldPosition.z);
    MapSetCameraTarget(act->fieldPosition.x, act->fieldPosition.y + act->fieldPosition.z);
    work->gfx = AnimUpdate(&work->anim);
    TaskPoolUpdate(&work->tasks);

    if ((gFieldState->flags & FIELD_FLAG_ROOM_CREATE) != 0) {
        work->timer = 0;
        SetTaskUpdate(task, (TaskUpdateFunc)FldRikuWaitRoomCreate);
    }

    return 1;
}
u8 FldRikuClimb(FldWork* work, void* task) {
    FldActor* act;
    FldPos p;
    s32 x;
    s32 y;
    s32 limit;
    s32 d;
    s32 ny;
    s32 nx;
    s32 tx;
    s32 ty;

    act = &gFieldState->actor;
    limit = FldRikuGetGround(work);
    x = act->fieldPosition.x;
    y = act->fieldPosition.y;
    gFieldState->lockonTarget = 0;

    switch (work->state) {
    case 6:
        if (work->timer == 0) {
            work->targetZ = (act->fieldPosition.z >> 12) << 12;
            work->timer++;
            tx = (work->targetX >> 11) / 4;
            ty = (work->targetY >> 11) / 2;
            nx = (tx << 13) | 0x1000;
            ny = (ty << 12) | 0x800;
            x = nx;
            act->fieldPosition.x = nx;
            y = ny;
            act->fieldPosition.y = ny;
            m4aSongNumStart(work->sounds[5]);
            act->fieldPosition.ground = GetFldPosGround(&act->fieldPosition);
        }

        FldRikuSetAnim(work, 8, 1);
        work->anim.frame = ((act->fieldPosition.z >> 8) + 4) & 31;
        work->gfx = AnimGetGfx(&work->anim);

        if (work->anim.timer == 0) {
            switch (work->anim.frame) {
            case 8:
                m4aSongNumStart(work->sounds[4]);
                break;
            case 24:
                m4aSongNumStart(work->sounds[5]);
                break;
            }
        }

        d = (((work->targetZ >> 12) << 12) - act->fieldPosition.z) >> 1;

        if (abs(d) <= 24) {
            d = 0;
        } else if (d > 384) {
            d = 384;
        } else if (d < -384) {
            d = -384;
        }

        act->fieldPosition.z += d;

        if (d < 0) {
            act->fieldPosition.x += gSineTable[act->angle];
            act->fieldPosition.y -= gSineTable[act->angle + 64];
            p = act->fieldPosition;
            p.z = work->targetZ - 0x2800;

            if (FldRikuCheckBlocked(&p) == 0) {
                act->speed = 204;
                work->vz = -0x580;
                work->flags |= FLD_FLAG_NO_AIR_TURN;
                work->state = 7;
                work->timer = 0;
                m4aSongNumStart(work->sounds[6]);
            }
        } else if (d > 0) {
            if (act->fieldPosition.z >= limit) {
                act->fieldPosition.z = limit;
                act->angle += 0x80;
                act->fieldPosition.x += gSineTable[act->angle] * 10;
                act->fieldPosition.y += -gSineTable[act->angle + 64] * 10;
                FldRikuSetAnim(work, 0, 1);
                work->gfx = AnimGetGfx(&work->anim);
                work->state = 0;
                work->timer = 0;
                SetTaskUpdate(task, (TaskUpdateFunc)task_fld_riku_1);
            }
        } else if (d == 0) {
            if ((GetKeysHeld() & DPAD_UP) || ((GetKeysHeld() & DPAD_LEFT) && act->angle == 0xD3) ||
                ((GetKeysHeld() & DPAD_RIGHT) && act->angle == 0x2D)) {
                work->targetZ = ((work->targetZ >> 12) - 1) << 12;
            } else if ((GetKeysHeld() & DPAD_DOWN) || ((GetKeysHeld() & DPAD_RIGHT) && act->angle == 0xD3) ||
                       ((GetKeysHeld() & DPAD_LEFT) && act->angle == 0x2D)) {
                work->targetZ = ((work->targetZ >> 12) + 1) << 12;
            }
        }

        if (GetKeysPressed() & B_BUTTON) {
            work->vz = 0;
            work->timer = 0;
            work->state = 4;
            act->angle += 0x80;
            act->speed = 0x80;
            work->flags |= FLD_FLAG_NO_AIR_TURN;
            act->fieldPosition.x += gSineTable[act->angle] * 10;
            act->fieldPosition.y += -gSineTable[act->angle + 64] * 10;
            FldRikuSetAnim(work, 6, 0);
            work->gfx = AnimGetGfx(&work->anim);
            SetTaskUpdate(task, (TaskUpdateFunc)FldRikuJump);
        }

        break;
    case 7:
        FldRikuSetAnim(work, 11, 0);
        act->fieldPosition.x += gSineTable[act->angle] * act->speed >> 8;
        act->fieldPosition.y += -gSineTable[act->angle + 64] * act->speed >> 8;
        work->vz += 0x42;
        act->fieldPosition.z += work->vz;

        if (work->vz > 0) {
            work->timer = 0;
            work->state = 4;
            SetTaskUpdate(task, (TaskUpdateFunc)FldRikuJump);
        } else {
            work->timer++;
        }

        work->gfx = AnimUpdate(&work->anim);
        break;
    }

    if (FldRikuCheckBlocked(&act->fieldPosition) != 0) {
        act->fieldPosition.x = x;
        act->fieldPosition.y = y;
    }

    ColliderSetPosition(&work->collider, act->fieldPosition.x, act->fieldPosition.y, act->fieldPosition.z);
    MapSetCameraTarget(act->fieldPosition.x, act->fieldPosition.y + act->fieldPosition.z);
    TaskPoolUpdate(&work->tasks);
    return 1;
}
u8 FldRikuLedgeInput(FldWork* work, void* task) {
    FldActor* act;

    act = &gFieldState->actor;

    if ((GetKeysPressed() & B_BUTTON) || (GetKeysPressed() & DPAD_DOWN) ||
        (act->angle == 0xD3 && (GetKeysPressed() & DPAD_RIGHT)) ||
        (act->angle == 0x2D && (GetKeysPressed() & DPAD_LEFT))) {
        work->timer = 0;
        work->state = 4;
        work->vz = 0;
        act->angle += 0x80;
        gFieldState->lockonTarget = 0;
        SetTaskUpdate(task, (TaskUpdateFunc)FldRikuJump);
        return 1;
    }

    if ((GetKeysHeld() & DPAD_UP) ||
        (act->angle == 0xD3 && (GetKeysHeld() & DPAD_LEFT)) ||
        (act->angle == 0x2D && (GetKeysHeld() & DPAD_RIGHT))) {
        work->timer = 0;
        work->state = 10;
        act->speed = 0x133;
        work->vz = -0x5C0;
        work->flags |= FLD_FLAG_NO_AIR_TURN;
        m4aSongNumStart(SONG_SYS_SR_CATJP);
        gFieldState->lockonTarget = 0;
        return 1;
    }

    return 0;
}
u8 FldRikuHangLedge(FldWork* work, void* task) {
    FldActor* act;
    FldPos p;
    u8 ret;
    s32 x;
    s32 y;

    act = &gFieldState->actor;
    ret = 0;
    x = act->fieldPosition.x;
    y = act->fieldPosition.y;
    gFieldState->lockonTarget = 0;

    switch (work->state) {
    case 8:
        if (work->timer == 0) {
            p = act->fieldPosition;
            p.y -= 0xA00;
            act->fieldPosition.z = GetFldPosGround(&p) + 0x2B00;
            m4aSongNumStart(SONG_SYS_SR_CATCH);
            act->angle = GetLedgeAngleAt(act->fieldPosition.x, act->fieldPosition.y, act->fieldPosition.z);
            FldRikuSetAnim(work, 9, 0);
        }

        if (work->timer > 15) {
            ret = FldRikuLedgeInput(work, task);
        }

        act->fieldPosition.x += gSineTable[act->angle];
        act->fieldPosition.y -= gSineTable[act->angle + 64];

        if (AnimIsFinished(&work->anim) != 0 && ret == 0) {
            work->state = 9;
        } else {
            work->timer++;
        }

        break;
    case 9:
        FldRikuSetAnim(work, 10, 0);
        FldRikuLedgeInput(work, task);
        break;
    case 10:
        FldRikuSetAnim(work, 11, 0);
        act->fieldPosition.x += gSineTable[act->angle] * act->speed >> 8;
        act->fieldPosition.y += -gSineTable[act->angle + 64] * act->speed >> 8;
        act->fieldPosition.z += work->vz;
        work->vz += 0x42;

        if (work->vz > 0) {
            work->timer = 0;
            work->state = 4;
            SetTaskUpdate(task, (TaskUpdateFunc)FldRikuJump);
        } else {
            work->timer++;
        }

        break;
    }

    work->gfx = AnimUpdate(&work->anim);

    if (FldRikuCheckBlocked(&act->fieldPosition) != 0) {
        act->fieldPosition.x = x;
        act->fieldPosition.y = y;
    }

    ColliderSetPosition(&work->collider, act->fieldPosition.x, act->fieldPosition.y, act->fieldPosition.z);
    MapSetCameraTarget(act->fieldPosition.x, act->fieldPosition.y + act->fieldPosition.z);
    TaskPoolUpdate(&work->tasks);
    return 1;
}
u8 FldRikuWalkOut(FldWork* work, void* task) {
    FldActor* act;

    act = &gFieldState->actor;

    switch (work->state) {
    case 15:
        if (work->timer == 0) {
            work->flags |= FLD_FLAG_WALK_OUT;
            act->angle = 45;
            FldRikuSetAnim(work, 2, 1);

            act->fieldPosition.x = 0x22000;
            act->fieldPosition.y = 0xF000;
            work->steps = 30;
            act->fieldPosition.z = 0;
            act->fieldPosition.ground = 0;
            work->targetX = act->fieldPosition.x + 0x2000;
            work->targetY = act->fieldPosition.y - 0x1000;
            work->targetZ = act->fieldPosition.ground - 0x2800;
        }

        if (work->steps > 0) {
            ApproachValue(&act->fieldPosition.x, work->targetX, work->steps);
            ApproachValue(&act->fieldPosition.y, work->targetY, work->steps);
            ApproachValue(&act->fieldPosition.z, work->targetZ, work->steps);
            act->fieldPosition.ground = act->fieldPosition.z;
            work->steps--;
        }

        if (work->anim.timer == 0) {
            switch (work->anim.frame) {
            case 3:
                m4aSongNumStart(work->sounds[0]);
                break;
            case 7:
                m4aSongNumStart(work->sounds[1]);
                break;
            }
        }

        if (work->steps <= 0) {
            work->timer = 0;

            if (work->flags & FLD_FLAG_TO_WORLD_SELECT) {
                work->state = 16;
            } else {
                work->state = 17;
            }
        } else {
            work->timer++;
        }

        break;
    case 16:
        if (work->timer == 0) {
            work->steps = 25;
            work->targetX = act->fieldPosition.x + 0x2000;
            work->targetY = act->fieldPosition.y - 0x1000;
        }

        if (work->steps > 0) {
            ApproachValue(&act->fieldPosition.x, work->targetX, work->steps);
            ApproachValue(&act->fieldPosition.y, work->targetY, work->steps);
            work->steps--;
        }

        if (work->anim.timer == 0) {
            switch (work->anim.frame) {
            case 3:
                m4aSongNumStart(work->sounds[0]);
                break;
            case 7:
                m4aSongNumStart(work->sounds[1]);
                break;
            }
        }

        if (work->steps <= 0) {
            work->timer = 0;
            work->state = 18;
        } else {
            work->timer++;
        }

        break;
    case 17:
        if (work->timer == 0) {
            work->steps = 25;
            work->targetX = act->fieldPosition.x + 0x2000;
            work->targetY = act->fieldPosition.y - 0x1000;
        }

        if (work->steps > 0) {
            ApproachValue(&act->fieldPosition.x, work->targetX, work->steps);
            ApproachValue(&act->fieldPosition.y, work->targetY, work->steps);
            work->steps--;
        }

        if (work->anim.timer == 0) {
            switch (work->anim.frame) {
            case 3:
                m4aSongNumStart(work->sounds[0]);
                break;
            case 7:
                m4aSongNumStart(work->sounds[1]);
                break;
            }
        }

        if (work->steps <= 0) {
            work->timer = 0;
            work->state = 19;
        } else {
            work->timer++;
        }

        break;
    case 18:
        if (work->timer == 0) {
            FldRikuSetAnim(work, 12, 0);
            FadeSetPaletteExcluded(work->palette->index + 16, 1);
        }

        if (work->timer == 40) {
            CreateWorldSelBeforeTask(&work->tasks, act->fieldPosition.x, act->fieldPosition.y, act->fieldPosition.z);
        }

        if (work->timer > 140) {
            work->timer = 0;
            work->state = 19;
        } else {
            work->timer++;
        }

        break;
    case 19:
        EndMapWalkOut();
        break;
    }

    ColliderSetPosition(&work->collider, act->fieldPosition.x, act->fieldPosition.y, act->fieldPosition.z);
    MapSetCameraTarget(act->fieldPosition.x, act->fieldPosition.y + act->fieldPosition.z);
    work->gfx = AnimUpdate(&work->anim);
    TaskPoolUpdate(&work->tasks);
    return 1;
}
u8 FldRikuAttack(FldWork* work, void* task) {
    FldActor* act;
    s32 x;
    s32 y;
    s32 nx;
    s32 ny;

    act = &gFieldState->actor;
    x = act->fieldPosition.x;
    y = act->fieldPosition.y;

    if (work->state == 11) {
        if (work->timer == 0) {
            FldRikuSetAnim(work, 13, 0);
            act->speed = 0;
            gFieldState->lockonTarget = 0;
            work->steps = 0;
            m4aSongNumStart(SONG_SND_227);
        }

        if (work->anim.timer == 0) {
            switch (act->angle) {
            case 173:
                switch (AnimGetFrame(&work->anim)) {
                case 0:
                    act->fieldPosition.x -= 0x500;
                    act->fieldPosition.y += 0x400;
                    break;
                case 1:
                    act->fieldPosition.x -= 0x200;
                    break;
                case 2:
                    act->fieldPosition.x -= 0x300;
                    break;
                }

                break;
            case 83:
                switch (AnimGetFrame(&work->anim)) {
                case 0:
                    act->fieldPosition.x += 0x500;
                    act->fieldPosition.y += 0x400;
                    break;
                case 1:
                    act->fieldPosition.x += 0x200;
                    break;
                case 2:
                    act->fieldPosition.x += 0x300;
                    break;
                }

                break;
            case 211:
                switch (AnimGetFrame(&work->anim)) {
                case 0:
                    act->fieldPosition.x -= 0x500;
                    act->fieldPosition.y -= 0x200;
                    break;
                case 1:
                    act->fieldPosition.x -= 0x500;
                    break;
                case 2:
                    act->fieldPosition.x -= 0x200;
                    break;
                }

                break;
            case 45:
                switch (AnimGetFrame(&work->anim)) {
                case 0:
                    act->fieldPosition.x += 0x500;
                    act->fieldPosition.y -= 0x200;
                    break;
                case 1:
                    act->fieldPosition.x += 0x500;
                    break;
                case 2:
                    act->fieldPosition.x += 0x200;
                    break;
                }

                break;
            case 128:
                switch (AnimGetFrame(&work->anim)) {
                case 0:
                    act->fieldPosition.x -= 0x300;
                    act->fieldPosition.y += 0x400;
                    break;
                case 1:
                    act->fieldPosition.x += 0x100;
                    act->fieldPosition.y += 0x100;
                    break;
                case 2:
                    act->fieldPosition.y += 0x200;
                    break;
                case 3:
                    act->fieldPosition.y += 0x100;
                    break;
                }

                break;
            case 64:
                switch (AnimGetFrame(&work->anim)) {
                case 0:
                    act->fieldPosition.x += 0x700;
                    act->fieldPosition.y += 0x100;
                    break;
                case 1:
                    act->fieldPosition.x += 0x300;
                    break;
                case 2:
                    act->fieldPosition.x += 0x200;
                    break;
                }

                break;
            case 192:
                switch (AnimGetFrame(&work->anim)) {
                case 0:
                    act->fieldPosition.x -= 0x700;
                    act->fieldPosition.y += 0x100;
                    break;
                case 1:
                    act->fieldPosition.x -= 0x300;
                    break;
                case 2:
                    act->fieldPosition.x -= 0x200;
                    break;
                }

                break;
            case 0:
                switch (AnimGetFrame(&work->anim)) {
                case 0:
                    act->fieldPosition.y -= 0x400;
                    break;
                case 1:
                    act->fieldPosition.y -= 0x400;
                    break;
                case 2:
                    act->fieldPosition.x -= 0x100;
                    act->fieldPosition.y += 0x100;
                    break;
                case 3:
                    act->fieldPosition.y -= 0x100;
                    break;
                }

                break;
            }
        }

        if (AnimGetFrame(&work->anim) == 3) {
            switch (act->angle) {
            case 45:
            case 211:
                nx = act->fieldPosition.x + gSineTable[act->angle] * 12;
                ny = act->fieldPosition.y + -gSineTable[act->angle + 64] * 12;
                break;
            case 64:
            case 192:
                nx = act->fieldPosition.x + gSineTable[act->angle] * 27;
                ny = act->fieldPosition.y + -gSineTable[act->angle + 64] * 27;
                break;
            case 0:
            case 83:
            case 128:
            case 173:
            default:
                nx = act->fieldPosition.x + gSineTable[act->angle] * 20;
                ny = act->fieldPosition.y + -gSineTable[act->angle + 64] * 20;
                break;
            }

            SetMapAttackBox(nx, ny, act->fieldPosition.z - 0x800);
        }

        if (AnimIsFinished(&work->anim) != 0) {
            switch (act->angle) {
            case 173:
                act->fieldPosition.x -= 0x200;
                act->fieldPosition.y += 0x200;
                break;
            case 83:
                act->fieldPosition.x += 0x200;
                act->fieldPosition.y += 0x200;
                break;
            case 45:
            case 211:
                act->fieldPosition.y -= 0x400;
                break;
            case 128:
                act->fieldPosition.y += 0x200;
                break;
            case 0:
                act->fieldPosition.y -= 0x200;
                break;
            }

            FldRikuSetAnim(work, 0, 0);
            work->state = 0;
            SetTaskUpdate(task, (TaskUpdateFunc)task_fld_riku_1);
        } else {
            work->timer++;
        }
    }

    if (work->collider.colliding != 0) {
        switch ((u32)work->collider.otherType) {
        case 5:
        case 3:
        case 11:
            break;
        default:
            if ((work->collider.standFlags & COLLIDER_STAND_OVER_PLATFORM) == 0) {
                act->fieldPosition.x += work->collider.pushX;
                act->fieldPosition.y += work->collider.pushY;
            }

            break;
        }
    }

    if (FldRikuCheckBlocked(&act->fieldPosition) != 0) {
        act->fieldPosition.x = x;
        act->fieldPosition.y = y;
    }

    ColliderSetPosition(&work->collider, act->fieldPosition.x, act->fieldPosition.y, act->fieldPosition.z);
    MapSetCameraTarget(act->fieldPosition.x, act->fieldPosition.y + act->fieldPosition.z);
    work->gfx = AnimUpdate(&work->anim);
    TaskPoolUpdate(&work->tasks);

    if (gFieldState->flags & FIELD_FLAG_ROOM_CREATE) {
        work->timer = 0;
        SetTaskUpdate(task, (TaskUpdateFunc)FldRikuWaitRoomCreate);
        TaskPoolUpdate(&work->tasks);
    }

    return 1;
}
u8 task_fld_riku_1(FldWork* work, void* task) {
    FldPos p1;
    FldPos p2;
    FldPos p3;
    FldPos p4;
    s32 sx;
    s32 sy;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 dw;
    s32 z;
    s32 r;
    u8 a;
    u8 b;
    FldActor* act;

    act = &gFieldState->actor;

    if ((work->flags & FLD_FLAG_RESTORE_STATE) != 0) {
        work->flags &= ~FLD_FLAG_RESTORE_STATE;

        switch (work->state) {
        case 12:
            work->state = 3;
        case 2:
        case 3:
        case 4:
        case 5:
            SetTaskUpdate(task, (TaskUpdateFunc)FldRikuJump);
            gFieldState->lockonTarget = 0;
            break;
        case 6:
        case 7:
            SetTaskUpdate(task, (TaskUpdateFunc)FldRikuClimb);
            gFieldState->lockonTarget = 0;
            work->timer = 1;
            break;
        case 8:
        case 9:
        case 10:
            SetTaskUpdate(task, (TaskUpdateFunc)FldRikuHangLedge);
            gFieldState->lockonTarget = 0;
            break;
        default:
            work->state = 0;
            break;
        }

        ColliderSetPosition(&work->collider, act->fieldPosition.x, act->fieldPosition.y, act->fieldPosition.z);
        MapSetCameraTarget(act->fieldPosition.x, act->fieldPosition.y + act->fieldPosition.z);
        work->gfx = AnimUpdate(&work->anim);
        TaskPoolUpdate(&work->tasks);
        return 1;
    } else if (GetMapWalkOutMode() != 0) {
        work->timer = 0;
        SetTaskUpdate(task, (TaskUpdateFunc)FldRikuWalkOut);
        TaskPoolUpdate(&work->tasks);
        work->state = 15;

        if (GetMapWalkOutMode() == 1) {
            work->flags |= FLD_FLAG_TO_WORLD_SELECT;
        }

        return 1;
    } else if ((gFieldState->flags & FIELD_FLAG_ROOM_CREATE) != 0) {
        work->timer = 0;
        SetTaskUpdate(task, (TaskUpdateFunc)FldRikuWaitRoomCreate);
        TaskPoolUpdate(&work->tasks);
        return 1;
    } else {
        sx = act->fieldPosition.x;
        sy = act->fieldPosition.y;

        if (work->state <= 1) {
            if ((gFieldState->flags & 0x4000) == 0) {
                FldRikuTurn(act);
            }

            if ((gFieldState->flags & 0x4000) == 0 && (GetKeysHeld() & DPAD_ANY) != 0) {
                act->speed += 128;
                FldRikuSetAnim(work, 2, 1);

                if (act->speed > 0x300) {
                    act->speed = 0x300;
                }

                if (work->anim.timer == 0) {
                    switch (work->anim.frame) {
                    case 3:
                        m4aSongNumStart(work->sounds[0]);
                        break;
                    case 7:
                        m4aSongNumStart(work->sounds[1]);
                        break;
                    }
                }
            } else {
                FldRikuSetAnim(work, 0, 1);
                act->speed -= 128;

                if (act->speed < 0) {
                    act->speed = 0;
                }
            }

            act->fieldPosition.x += gSineTable[act->angle] * act->speed >> 8;
            act->fieldPosition.y += -gSineTable[act->angle + 64] * act->speed >> 8;

            if ((GetKeysPressed() & B_BUTTON) != 0) {
                gFieldState->flags |= FIELD_FLAG_PLAYER_JUMPING;
                gFieldState->lockonTarget = 0;
                work->timer = 0;
                work->state = 2;
                SetTaskUpdate(task, (TaskUpdateFunc)FldRikuJump);
                m4aSongNumStart(work->sounds[2]);
            } else if ((GetKeysPressed() & A_BUTTON) != 0) {
                work->timer = 0;
                gFieldState->lockonTarget = 0;
                work->state = 11;
                SetTaskUpdate(task, (TaskUpdateFunc)FldRikuAttack);
            }
        } else if (AnimIsFinished(&work->anim) != 0) {
            work->state = 0;
        }

        if (work->collider.colliding != 0) {
            switch ((u32)work->collider.otherType) {
            case 3:
            case 5:
            case 11:
                break;
            default:
                if ((work->collider.standFlags & COLLIDER_STAND_OVER_PLATFORM) == 0) {
                    act->speed = 230 * act->speed >> 8;
                    act->fieldPosition.x += work->collider.pushX;
                    act->fieldPosition.y += work->collider.pushY;
                }
                break;
            }
        }

        if (FldRikuCheckBlocked(&act->fieldPosition) != 0) {
            act->fieldPosition.x = sx;
            act->fieldPosition.y = sy;
            r = FldRikuCheckClimb(&act->fieldPosition, work);

            if (r != 0) {
                switch (r) {
                case 2:
                    work->timer = 0;
                    work->state = 6;
                    act->angle = 211;
                    gFieldState->lockonTarget = 0;
                    SetTaskUpdate(task, (TaskUpdateFunc)FldRikuClimb);
                    break;
                case 1:
                    work->timer = 0;
                    work->state = 6;
                    act->angle = 45;
                    gFieldState->lockonTarget = 0;
                    SetTaskUpdate(task, (TaskUpdateFunc)FldRikuClimb);
                    break;
                }
            } else {
                if (FldRikuCheckDoorAhead(act) != 0) {
                    FadeSetPaletteExcluded(work->palette->index + 16, 1);
                    gFieldState->flags |= FIELD_FLAG_EXIT_ROOM;
                    return 1;
                }

                switch (act->angle) {
                case 173:
                    dx = -256;
                    dy = 0;
                    dz = 0;
                    dw = 384;
                    break;
                case 83:
                    dx = 256;
                    dy = 0;
                    dz = 0;
                    dw = 384;
                    break;
                case 211:
                    dx = -256;
                    dy = 0;
                    dz = 0;
                    dw = -384;
                    break;
                case 45:
                    dx = 256;
                    dy = 0;
                    dz = 0;
                    dw = -384;
                    break;
                case 128:
                    dx = -512;
                    dy = 192;
                    dz = 512;
                    dw = 192;
                    break;
                case 0:
                    dx = -512;
                    dy = -192;
                    dz = 512;
                    dw = -192;
                    break;
                case 64:
                    dx = 384;
                    dy = -307;
                    dz = 384;
                    dw = 307;
                    break;
                case 192:
                    dx = -384;
                    dy = -307;
                    dz = -384;
                    dw = 307;
                    break;
                default:
                    dw = 0;
                    dz = 0;
                    dy = 0;
                    dx = 0;
                    break;
                }

                p2 = act->fieldPosition;
                p1 = p2;
                p1.x += dx;
                p1.y += dy;
                p2.x += dz;
                p2.y += dw;
                a = FldRikuCheckBlocked(&p1);
                b = FldRikuCheckBlocked(&p2);

                if (a != 0) {
                    if (b == 0) {
                        p3 = act->fieldPosition;
                        p3.x += dz;
                        p3.y += dw;
                        p3.ground = FldRikuProbeGround(&p3);

                        if (p3.ground >= p3.z) {
                            act->fieldPosition = p3;
                        }
                    }
                } else if (b != 0) {
                    p4 = act->fieldPosition;
                    p4.x += dx;
                    p4.y += dy;
                    p4.ground = FldRikuProbeGround(&p4);

                    if (p4.ground >= p4.z) {
                        act->fieldPosition = p4;
                    }
                }

                act->speed = 0;
            }
        }

        z = FldRikuGetGround(work);

        if (act->fieldPosition.ground == 0x100000) {
            act->fieldPosition.ground = act->fieldPosition.z;
        } else if (z != act->fieldPosition.z) {
            act->speed >>= 2;
            work->vz = 0;
            work->timer = 0;
            gFieldState->lockonTarget = 0;
            gFieldState->flags |= FIELD_FLAG_PLAYER_JUMPING;
            work->state = 4;
            SetTaskUpdate(task, (TaskUpdateFunc)FldRikuJump);
        } else if (z != act->fieldPosition.ground) {
            gFieldState->lockonTarget = 0;
        }
    }

    ColliderSetPosition(&work->collider, act->fieldPosition.x, act->fieldPosition.y, act->fieldPosition.z);
    MapSetCameraTarget(act->fieldPosition.x, act->fieldPosition.y + act->fieldPosition.z);
    work->gfx = AnimUpdate(&work->anim);
    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_fld_riku_2(FldWork* work) {
    FldActor* act;
    u16 depth;
    s32 pri;
    s32 x;
    s32 y;
    s32 z;

    act = &gFieldState->actor;
    pri = (work->flags & FLD_FLAG_HFLIP) ? 0x801 : 0x800;

    if (work->onCollider != 0) {
        depth = -0x1006 - (work->collider.platformY >> 8) * 4;

        if (work->collider.penetration <= work->collider.radius) {
            act->shadowPriority = 0;
            act->shadowZ = GetFldPosGround(&act->fieldPosition);
        } else {
            act->shadowZ = work->collider.platformZ;
            act->shadowPriority = depth + 1;
        }
    } else {
        depth = -0x1004 - (act->fieldPosition.y >> 8) * 4;

        if (work->flags & FLD_FLAG_WALK_OUT) {
            act->shadowZ = act->fieldPosition.ground;
        } else {
            act->shadowZ = GetFldPosGround(&act->fieldPosition);
        }

        if (act->shadowZ != act->fieldPosition.ground) {
            act->shadowPriority = 0;
        } else {
            act->shadowPriority = depth + 1;
        }
    }

    x = (act->fieldPosition.x >> 8) - (gFieldState->x >> 8);
    y = (act->fieldPosition.y >> 8) + (act->fieldPosition.z >> 8) - (gFieldState->y >> 8);
    DrawSprite(x, y, work->gfx, work->tiles, work->palette, 0, pri, depth);
    TaskPoolDraw(&work->tasks);
}

void task_fld_riku_3(FldWork* work) {
    FldActor* act;

    act = &gFieldState->actor;
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);

    if (gGameState.fieldResume != 0) {
        gGameState.fieldSpeed = act->speed;
        gGameState.fieldPosition = act->fieldPosition;
        gGameState.fieldAngle = act->angle;
        gGameState.fieldState = work->state;
        gGameState.fieldVz = work->vz;
        gGameState.fieldTargetX = work->targetX;
        gGameState.fieldTargetY = work->targetY;
        gGameState.fieldTargetZ = work->targetZ;
    } else {
        gGameState.fieldAngle = act->angle;
    }

    TaskPoolDestroy(&work->tasks);
}

void task_fld_shadow_0(FldShadowWork* work, FldObj* obj) {
    work->actor = obj;
    work->x = obj->fieldPosition.x;
    work->y = obj->fieldPosition.y;
    work->tiles = LoadObjTiles(gUnk_08B22BBC, 0x100);
    work->palette = LoadObjPalette(gUnk_08F69BE4, 32);
    AnimInit(&work->anim, gUnk_09EE1384, gUnk_09EE1380);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
}

s32 task_fld_shadow_1(FldShadowWork* work) {
    work->x = work->actor->fieldPosition.x;
    work->y = work->actor->fieldPosition.y;
    return 1;
}

void task_fld_shadow_2(FldShadowWork* work) {
    FldObj* obj;
    void* spr;
    s32 z;
    s32 size;
    ObjAffine* sprite;
    s32 x;
    s32 y;

    obj = work->actor;

    if (obj->shadowPriority == 0) {
        return;
    }

    spr = AnimUpdate(&work->anim);
    z = obj->shadowZ;

    if (obj->fieldPosition.z >= z) {
        sprite = 0;
    } else {
        size = 0x100 - (z - obj->fieldPosition.z) / 128;

        if (size <= 0x18) {
            size = 0x19;
        }

        sprite = AllocObjAffine(0, size, size, 0);
    }

    x = (work->x >> 8) - (gFieldState->x >> 8);
    y = (work->y >> 8) + (z >> 8) - (gFieldState->y >> 8);
    DrawSprite(x, y, spr, work->tiles, work->palette, sprite, 0x800, obj->shadowPriority);
}

void task_fld_shadow_3(FldShadowWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

TaskDesc gTaskDescFldRiku = {
    "task_fld_riku",
    (TaskInitFunc)task_fld_riku_0,
    (TaskUpdateFunc)task_fld_riku_1,
    (TaskDrawFunc)task_fld_riku_2,
    (TaskDestroyFunc)task_fld_riku_3,
    sizeof(FldWork),
};

TaskDesc gTaskDescFldShadow = {
    "task_fld_shadow",
    (TaskInitFunc)task_fld_shadow_0,
    (TaskUpdateFunc)task_fld_shadow_1,
    (TaskDrawFunc)task_fld_shadow_2,
    (TaskDestroyFunc)task_fld_shadow_3,
    sizeof(FldShadowWork),
};
