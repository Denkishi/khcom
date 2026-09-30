#ifndef GUARD_MODE_DEBUG_H
#define GUARD_MODE_DEBUG_H

#include "registration_data.h"
#include "card_api.h"
#include "pallet.h"
#include "save_api.h"
#include "obj_api.h"
#include "display.h"
#include "types.h"
#include "main.h"
#include "anim.h"
#include "mode.h"
#include "key.h"
#include "m4a.h"
#include "battle_actor.h"
typedef struct DebugWork {
    s8 cursor;
    s8 page;
    u8 unk_02[0x02];
    void* tiles;
    void* palette;
    AnimState anim;
} DebugWork;

extern const char gUnk_08F68604[];
extern const char gVersionString[];
extern Mode gModeChkbtl;
extern Mode gModeChksnd;

#endif /* GUARD_MODE_DEBUG_H */
