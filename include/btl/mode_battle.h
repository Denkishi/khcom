#ifndef GUARD_MODE_BATTLE_H
#define GUARD_MODE_BATTLE_H

#include "types.h"

struct ObjPalette;
struct ObjTiles;
#ifdef VERSION_EU
#include "save_api.h"
#include "battle_localized_assets.h"
#endif

void UpdateBattleState();

#ifdef VERSION_EU
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
#endif

#endif /* GUARD_MODE_BATTLE_H */
