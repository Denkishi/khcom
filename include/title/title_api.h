#ifndef GUARD_TITLE_API_H
#define GUARD_TITLE_API_H

#include "types.h"

void TitleCopyToPaletteBuffer(u16 slot, void* src, u16 size);
void TitleLoadPaletteBuffer();
u8 IsTitleObjSlideDone();

#endif
