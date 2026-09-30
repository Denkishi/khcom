#ifndef GUARD_PLAYER_PROGRESSION_TYPES_H
#define GUARD_PLAYER_PROGRESSION_TYPES_H

#include "types.h"

typedef struct PlayerProgression {
    s16 maxHp;
    s16 cp;
    s16 dp;
    s16 ap;
    u32 exp;
    u32 nextExp;
    u8 level;
    u8 unk_11[0x03];
    u64 learnedStocks;
    u64 learnedStocks2;
    u64 newStocks;
    u64 newStocks2;
    u64 obtainedCardKinds;
    u64 jiminyFlags[8];
    u32 mooglePoints;
    u16 levelMilestone;
    u16 unk_82;
    u16 friendFlags;
    u16 savedFriendFlags;
} PlayerProgression;

typedef char PlayerProgression_size[(sizeof(PlayerProgression) == 0x88) ? 1 : -1];

#endif
