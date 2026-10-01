#ifndef GUARD_TITLE_API_H
#define GUARD_TITLE_API_H

#include "types.h"

void TitleCopyToPaletteBuffer(u16 a, void* b, u16 c);
void TitleLoadPaletteBuffer();
u8 IsTitleObjSlideDone();

#endif
