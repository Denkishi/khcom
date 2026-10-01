#ifndef GUARD_MODE_MOVIE_H
#define GUARD_MODE_MOVIE_H

#include "types.h"
#include "text_types.h"

typedef struct MovieSub {
    s16 frame;
    s16 x;
    const TextChar* text;
    u8 line;
    u8 unk_09;
    u16 duration;
    u16 palette;
    u16 unk_0E;
} MovieSub;

enum MovieFlag {
    MOVIE_FLAG_UPPER_SUB_PENDING = 0x1,
    MOVIE_FLAG_LOWER_SUB_PENDING = 0x2,
    MOVIE_FLAG_SOFT_RESET = 0x4,
    MOVIE_FLAG_PLAYING = 0x8
};

extern u16 gUnk_09614718[];

void* GetIwramHeapStart();
u32 GetIwramHeapSize();
void MovieVBlankIntr();
s32 HandleMovieFrame(s32 arg);

#endif
