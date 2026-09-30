#ifndef GUARD_MODE_MOVIE_H
#define GUARD_MODE_MOVIE_H

#include "registration_data.h"

#include "movie.h"
#include "movie_text.h"
#include "msg_api.h"
#include "display.h"
#include "pallet.h"
#include "obj_api.h"
#include "types.h"
#include "mode.h"
#include "gba/syscall.h"
#include "malloc.h"
#include "sprite.h"
#include "main.h"
#include "engine.h"
#include "util.h"
#include "m4a.h"

typedef struct MovieSub {
    s16 frame;
    s16 x;
    TextChar* text;
    u8 line;
    u8 unk_09;
    u16 duration;
    u16 palette;
    u16 unk_0E;
} MovieSub;

extern vu16 gMovieModeState;
extern s32 gMovieId;
extern u16 gUnk_02034940;
extern volatile s16 gMovieFrame;
extern volatile s16 gMovieSubIndex;
extern volatile u16 gMovieSubCount;
extern MovieSub* volatile gMovieSubUpper;
extern MovieSub* volatile gMovieSubLower;
extern MovieSub* gMovieSubs;
extern volatile s16 gMovieSubUpperTimer;
extern volatile u16 gMovieSubUpperLength;
enum MovieFlag {
    MOVIE_FLAG_UPPER_SUB_PENDING = 0x1,
    MOVIE_FLAG_LOWER_SUB_PENDING = 0x2,
    MOVIE_FLAG_SOFT_RESET = 0x4,
    MOVIE_FLAG_PLAYING = 0x8
};

extern volatile u16 gMovieFlags;
extern volatile u16 gMovieSubUpperAlpha;
extern volatile s16 gMovieSubLowerTimer;
extern volatile u16 gMovieSubLowerLength;
extern volatile u16 gMovieSubLowerAlpha;
extern u8 gUnk_0815C3EC[];
extern u8 gUnk_084E0F34[];
extern u8 gUnk_084F4660[];
extern u8 gUnk_0855CCB4[];
extern u8 gUnk_086FBA14[];
extern MovieSub gUnk_0886AB40[];
extern MovieSub gUnk_0886AB90[];
extern MovieSub gUnk_0886AC70[];
extern u8 sMovieHeapName[];
extern u8 gUnk_09614718[];

void* GetIwramHeapStart(void);
u32 GetIwramHeapSize(void);
void MovieVBlankIntr(void);
s32 HandleMovieFrame(s32 arg);

#ifndef VERSION_JP
extern u16 gMovieSubUpperWidths[];
extern u16 gMovieSubLowerWidths[];
#endif

#ifdef VERSION_EU
extern MovieSub gUnkEu_0883E040[];
extern MovieSub gUnkEu_0883E070[];
extern MovieSub gUnkEu_0883E150[];
extern MovieSub gUnkEu_0883E454[];
extern MovieSub gUnkEu_0883E494[];
extern MovieSub gUnkEu_0883E574[];
extern MovieSub gUnkEu_0883E8D4[];
extern MovieSub gUnkEu_0883E914[];
extern MovieSub gUnkEu_0883E9F4[];
extern MovieSub gUnkEu_0883ECE8[];
extern MovieSub gUnkEu_0883ED28[];
extern MovieSub gUnkEu_0883EE08[];
extern MovieSub gUnkEu_0883F0F8[];
extern MovieSub gUnkEu_0883F138[];
extern MovieSub gUnkEu_0883F218[];
#endif

#endif
