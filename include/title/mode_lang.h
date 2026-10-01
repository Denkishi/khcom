#ifndef GUARD_MODE_LANG_H
#define GUARD_MODE_LANG_H

#include "types.h"

#ifdef VERSION_EU
struct ObjPalette;
struct ObjTiles;

enum LangFlag {
    LANG_FLAG_HIDE_CURSOR = 0x1
};

typedef struct LangWork {
    s16 cursor;
    s16 timer;
    u32 state;
    u16 flags;
    u32 language;
    struct ObjTiles* tiles;
    struct ObjPalette* palette;
} LangWork;

extern u16 gUnkEu_08F6A6DC[];
extern u16 gUnkEu_08F6A6FC[];
extern u8 gUnkEu_08F77180[];
extern u16 gUnkEu_08F7EBF8[];
extern u16 gUnkEu_08F7EFB0[];

void eu_08009CD0(s32 arg);
void mode_lang_1();
void mode_lang_2();
#endif

#endif /* GUARD_MODE_LANG_H */
