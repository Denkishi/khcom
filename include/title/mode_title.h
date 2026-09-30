#ifndef GUARD_MODE_TITLE_H
#define GUARD_MODE_TITLE_H

#include "registration_data.h"
#include "anim.h"
#include "card_api.h"
#include "title_api.h"
#include "save_api.h"
#include "display.h"
#include "obj_api.h"
#include "types.h"
#include "game_state.h"
#include "taskpool.h"
#include "intr.h"
#include "main.h"
#include "engine.h"
#include "m4a.h"
#include "battle_actor.h"
#include "gba/io_reg.h"

void TitleShowLogo(u16 a);
void TitleFinishIntro(void);
void TitleFadeOut(void);
void TitleExitToChoice(void);

extern s32 gTitleBgScale;
extern s32 gTitleBgX;
extern s32 gTitleBgY;

#endif /* GUARD_MODE_TITLE_H */
