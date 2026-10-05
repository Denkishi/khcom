#ifndef GUARD_MODE_JIMINY_H
#define GUARD_MODE_JIMINY_H

#include "types.h"
#include "text_types.h"
#include "jiminy_types.h"

extern TextChar gJiminyChooseEntryText[];

void JiminyFreeRows();
u8 JiminyHandleListInput();
void JiminyReloadPlainRows();
void JiminyOpenList(s16 a, s16 b, const u16* const* c, const u16* d, const u16* e, s16 f, s16 g, s16 h);

void JiminyDetailUpdate();
void JiminyOpenPlainList(s16 a, s16 b, const u16* const* c, s16 d, s16 e, s16 f);
void SplitThreeDecimalDigits(s16 a, u8* out);

#ifdef VERSION_EU
extern u8 gUnkEu_099FBE00[];
#endif

void mode_jiminy_1();

#endif
