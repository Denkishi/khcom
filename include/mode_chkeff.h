#include "registration_data.h"
#ifndef GUARD_MODE_CHKEFF_H
#define GUARD_MODE_CHKEFF_H

#include "bg_animation_data.h"

#include "card_api.h"

#include "fade.h"
#include "display.h"
#include "types.h"
#include "taskpool.h"
#include "main.h"
#include "mode.h"
#include "key.h"

typedef struct ChkEffWork {
    TaskPool pool;
    s16 effectIndex;
    u8 paused;
    u8 unk_17;
    u16 scrollX;
    u16 scrollY;
    u8 rotation;
    u8 unk_1D[0x03];
    s32 scale;
    u16 alphaA;
    u16 alphaB;
} ChkEffWork;

void mode_chkeff_0(void);
void mode_chkeff_1(void);
void mode_chkeff_2(void);
extern const char gChkEffPauseText[];
extern const char gChkEffPauseBlankText[];
extern const char gChkEffBlankLineText[];
extern const char gChkEffAlphaALabel[];
extern const char gChkEffAlphaBLabel[];
extern const char gChkEffScaleLabel[];
extern const char gChkEffNumLabel[];
extern const char gChkEffPicLabel[];
extern const char gChkEffFrameLabel[];

#endif /* GUARD_MODE_CHKEFF_H */
