#ifndef GUARD_MODE_JIMINY_H
#define GUARD_MODE_JIMINY_H

#include "jiminy_records_data.h"
#include "battle_localized_data.h"
#include "battle_localized_assets.h"
#include "system_state.h"

#include "map_api.h"
#include "msg_api.h"
#include "mode.h"

#include "text.h"
#include "monsgage.h"
#include "obj_api.h"
#include "display.h"
#include "types.h"
#include "engine_math.h"
#include "game_state.h"
#include "text_types.h"
#include "jiminy_types.h"
#include "main.h"
#include "anim.h"
#include "obj.h"
#include "m4a.h"
#include "poo_api.h"
#ifdef VERSION_EU
extern u8 gUnkEu_08892334[];
extern u8 gUnk_09A3CDDC[];
#endif

extern JiminyWork* gJiminyWork;

extern TextChar gUnk_08159FE0[];
extern u8 gTalk0600Tiles[];
extern u8 gTalk2700Tiles[];
extern u8 gCard00Palette[];
extern u8 gTalk0600Palette[];
extern u8 gTalk2700Palette[];

void JiminyFreeRows(void);
u8 JiminyHandleListInput(void);
void JiminyReloadPlainRows(void);
void JiminyOpenList(s16 a, s16 b, u16** c, const u16* d, const u16* e, s16 f, s16 g, s16 h);

void JiminyDetailUpdate(void);
void JiminyOpenPlainList(s16 a, s16 b, u16** c, s16 d, s16 e, s16 f);
void SplitThreeDecimalDigits(s16 a, u8* out);

#ifdef VERSION_EU
extern u8 gUnkEu_099FBE00[];
#endif

void mode_jiminy_1(void);

#endif
