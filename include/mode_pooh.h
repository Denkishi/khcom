#include "registration_data.h"
#ifndef GUARD_MODE_POOH_H
#define GUARD_MODE_POOH_H


#include "chara_types.h"

#include "prize_types.h"

#include "card_api.h"
#include "msg_api.h"
#include "mode_pooh_api.h"

#include "mode_test_api.h"

#include "anim.h"
#include <string.h>
#include "fade.h"
#include "btl_collision.h"
#include "obj_api.h"
#include "display.h"
#include "types.h"
#include "engine_math.h"
#include "game_state.h"
#include "taskpool.h"
#include "main.h"
#include "mode.h"
#include "obj.h"
#include "key.h"
#include "m4a.h"
#include "bos4_api.h"
#include "poo_api.h"


extern u32 gPoohAction;

extern u8 gPoohPalette[];
extern u8 gTrap0001Palette[];
extern u8 gTrap0002Palette[];
extern u8 gTrap0003Palette[];
extern const s8 gPoohLookOffsets[8][8];

void BackdropFadeToOriginal(u32 a, u16 b);
void BackdropFadeToAmount(u32 a, u16 b, u16 c);
u8 BackdropFadeIsActive(void);
void BackdropFadeFromAmount(u32 a, u16 b, u16 c);
void SetPooStartPositions(void);
void SetPooReentryPositions(void);
void mode_pooh_0(s32 arg);
void mode_pooh_1(void);
void mode_pooh_2(void);
u16 CountPooPrizes(void);
void SetPoohDir5Left(PoohWork* w);
void SetPoohDir8(PoohWork* w);
void SetPoohDir2(PoohWork* w);
void SetPoohDir3(PoohWork* w);
u8 IsAngleFacingRight(u8 a);
u8 GetPoohLookColumn(PoohWork* w);

#endif /* GUARD_MODE_POOH_H */
