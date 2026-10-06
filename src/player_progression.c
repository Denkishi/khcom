/**
 * player_progression.c
 * Player Progression
 */

#include "macros.h"
#include "ms_api.h"
#include "player_progression.h"
#include "battle.h"
#include "battle_work.h"
#include "bos_jf_shadow.h"
#include "bos4_api.h"
#include "game_state.h"
#include "player_progression_types.h"
#include "types.h"
#include <stddef.h>

static const EnemyBaseStats sEnemyBaseStats[54] = {
    { 33, 2, 3, 0 },
    { 35, 3, 3, 0 },
    { 35, 3, 3, 0 },
    { 35, 3, 3, 0 },
    { 40, 2, 3, 0 },
    { 50, 4, 4, 0 },
    { 198, 0, 3, 0 },
    { 74, 5, 1, 0 },
    { 40, 1, 3, 0 },
    { 60, 3, 5, 0 },
    { 70, 3, 5, 0 },
    { 50, 4, 5, 0 },
    { 80, 3, 5, 0 },
    { 80, 5, 5, 0 },
    { 60, 5, 5, 0 },
    { 60, 3, 5, 0 },
    { 80, 5, 8, 0 },
    { 70, 4, 8, 0 },
    { 80, 4, 5, 0 },
    { 70, 4, 8, 0 },
    { 60, 4, 8, 0 },
    { 70, 3, 10, 0 },
    { 70, 4, 10, 0 },
    { 50, 3, 10, 0 },
    { 74, 3, 10, 0 },
    { 100, 4, 10, 0 },
    { 120, 5, 10, 0 },
    { 130, 5, 10, 0 },
    { 90, 4, 13, 0 },
    { 70, 3, 8, 0 },
    { 70, 3, 8, 0 },
    { 60, 3, 8, 0 },
    { 200, 5, 48, 0 },
    { 500, 5, 93, 0 },
    { 500, 5, 93, 0 },
    { 400, 5, 173, 0 },
    { 550, 4, 93, 0 },
    { 600, 5, 173, 0 },
    { 600, 6, 195, 0 },
    { 500, 5, 93, 0 },
    { 660, 6, 313, 0 },
    { 500, 3, 133, 0 },
    { 400, 3, 173, 0 },
    { 250, 3, 77, 0 },
    { 400, 4, 93, 0 },
    { 500, 2, 75, 0 },
    { 80, 3, 5, 0 },
    { 100, 4, 7, 0 },
    { 313, 2, 75, 0 },
    { 500, 3, 75, 0 },
    { 500, 3, 75, 0 },
    { 500, 3, 113, 0 },
    { 500, 3, 133, 0 },
    { 500, 3, 133, 0 },
};

GameState gGameState EWRAM_COMMON(16);

void AdvanceLevelExpThreshold(PlayerProgression* progression) {
    s32 n = progression->level + 1;

    if (progression->level) {
        progression->nextExp = n * n * 3 + progression->nextExp;
    } else {
        progression->nextExp = n * n * 3 + progression->nextExp;
    }
}

void InitPlayerProgression() {
    PlayerProgression* p = &gGameState.progression;

    p->maxHp = 0x50;
    p->cp = 0x113;
    p->dp = 8;
    p->ap = 10;
    p->exp = 0;
    p->level = 1;
    p->learnedStocks = 0;
    p->learnedStocks2 = 0;
    p->newStocks = 0;
    p->newStocks2 = 0;
    p->obtainedCardKinds = 0;
    p->jiminyFlags[0] = 0;
    p->jiminyFlags[1] = 0;
    p->jiminyFlags[2] = 0;
    p->jiminyFlags[3] = 0;
    p->jiminyFlags[4] = 0;
    p->jiminyFlags[5] = 0;
    p->jiminyFlags[6] = 0;
    p->jiminyFlags[7] = 0;
    p->mooglePoints = 0;
    p->levelMilestone = 0;
    p->tutorialFlags = 0;
    p->friendFlags = 0;
    p->nextExp = 0x19;
    ResetSaveSliceE6C();
    ResetPooState();
    ClearMoogleShopFlags();
}

u8 LevelUp() {
    PlayerProgression* p = &gGameState.progression;

    if (p->level + gBtlWork->pendingLevelUps + 1 <= 99) {
        gBtlWork->pendingLevelUps++;
        p->level++;
        AdvanceLevelExpThreshold(p);
        return 1;
    } else {
        return 0;
    }
}

s32 LevelUpMaxHp() {
    gGameState.progression.maxHp += 15;

    if (gGameState.progression.maxHp > 560) {
        gGameState.progression.maxHp = 560;
    }

    return 15;
}

s32 LevelUpCp() {
    gGameState.progression.cp += 25;

    if (gGameState.progression.cp > 9999) {
        gGameState.progression.cp = 9999;
    }

    return 25;
}

s32 LevelUpDp() {
    gGameState.progression.dp += 2;

    if (gGameState.progression.dp > 999) {
        gGameState.progression.dp = 999;
    }

    return 2;
}

s32 LevelUpAp() {
    gGameState.progression.ap += 1;

    if (gGameState.progression.ap > 999) {
        gGameState.progression.ap = 999;
    }

    return 1;
}

void AddExp(u16 exp) {
    PlayerProgression* p = &gGameState.progression;

    p->exp += exp;
}

u8 CanLevelUp() {
    PlayerProgression* p = &gGameState.progression;

    if (p->exp >= p->nextExp) {
        return 1;
    }

    return 0;
}

const EnemyBaseStats* GetEnemyBaseStats(u16 i) {
    if (i > 0x35) {
        return NULL;
    }

    return &sEnemyBaseStats[i];
}

void LearnStock(u32 stock) {
    u8* q;
    u8* z;

    if (stock == 72) {
        z = (u8*)&gGameState;
        *(u64*)(z + offsetof(GameState, progression.learnedStocks)) = -1;
        *(u64*)(z + offsetof(GameState, progression.learnedStocks2)) = -1;
        return;
    }

    if (IsStockLearned(stock)) {
        return;
    }

    if (stock <= 0x1E) {
        q = (u8*)&gGameState;
        *(u64*)(q + offsetof(GameState, progression.learnedStocks)) |= 1LL << stock;
        *(u64*)(q + offsetof(GameState, progression.newStocks)) |= 1LL << stock;
    } else {
        stock -= 0x1F;
        q = (u8*)&gGameState;
        *(u64*)(q + offsetof(GameState, progression.learnedStocks2)) |= 1LL << stock;
        *(u64*)(q + offsetof(GameState, progression.newStocks2)) |= 1LL << stock;
    }
}

u8 IsStockLearned(u32 stock) {
    u64* p;
    u8* q;

    if (stock <= 0x1E) {
        q = (u8*)&gGameState;
        q += offsetof(GameState, progression.learnedStocks);
    } else {
        stock -= 0x1F;
        q = (u8*)&gGameState;
        q += offsetof(GameState, progression.learnedStocks2);
    }

    p = (u64*)q;

    if (*p & (1LL << stock)) {
        return 1;
    }

    return 0;
}

void SetCardKindObtained(s32 kind) {
    if (kind == 0x3A) {
        gGameState.progression.obtainedCardKinds = -1;
    } else {
        gGameState.progression.obtainedCardKinds |= 1LL << kind;
    }
}

u8 IsCardKindObtained(s32 kind) {
    if (gGameState.progression.obtainedCardKinds & (1LL << kind)) {
        return 1;
    }

    return 0;
}

u8 IsLinkStockLearned(u32 stock) {
    u64* p;
    u8* q;

    if (stock <= 0x1E) {
        q = (u8*)&gGameState;
        q += offsetof(GameState, linkLearnedStocks);
    } else {
        stock -= 0x1F;
        q = (u8*)&gGameState;
        q += offsetof(GameState, linkLearnedStocks2);
    }

    p = (u64*)q;

    if (*p & (1LL << stock)) {
        return 1;
    }

    return 0;
}

u8 IsLinkPartnerStockLearned(u32 stock) {
    u64* p;
    u8* q;

    if (stock <= 0x1E) {
        q = (u8*)&gGameState;
        q += offsetof(GameState, linkPartnerLearnedStocks);
    } else {
        stock -= 0x1F;
        q = (u8*)&gGameState;
        q += offsetof(GameState, linkPartnerLearnedStocks2);
    }

    p = (u64*)q;

    if (*p & (1LL << stock)) {
        return 1;
    }

    return 0;
}

u8 IsStockNew(u32 stock) {
    u64* p;
    u8* q;

    if (stock <= 0x1E) {
        q = (u8*)&gGameState;
        q += offsetof(GameState, progression.newStocks);
    } else {
        stock -= 0x1F;
        q = (u8*)&gGameState;
        q += offsetof(GameState, progression.newStocks2);
    }

    p = (u64*)q;

    if (*p & (1LL << stock)) {
        return 1;
    }

    return 0;
}

void ClearStockNew(u32 stock) {
    u64* p;
    u8* q;

    if (stock == 0x48) {
        GameState* s = &gGameState;
        s->progression.newStocks = 0;
        s->progression.newStocks2 = 0;
    } else {
        if (stock <= 0x1E) {
            q = (u8*)&gGameState;
            q += offsetof(GameState, progression.newStocks);
        } else {
            stock -= 0x1F;
            q = (u8*)&gGameState;
            q += offsetof(GameState, progression.newStocks2);
        }

        p = (u64*)q;
        *p &= ~(1LL << stock);
    }
}

void SetJiminyFlag(u32 flag) {
    GameState* state;

    if (flag == 250) {
        GameState* state = &gGameState;
        state->progression.jiminyFlags[0] = -1;
        state->progression.jiminyFlags[1] = -1;
        state->progression.jiminyFlags[2] = -1;
        state->progression.jiminyFlags[3] = -1;
        state->progression.jiminyFlags[4] = -1;
        state->progression.jiminyFlags[5] = -1;
        state->progression.jiminyFlags[6] = -1;
        state->progression.jiminyFlags[7] = -1;
        return;
    }

    if (IsJiminyFlagSet(flag)) {
        return;
    }

    if (flag <= 0x3F) {
        state = &gGameState;
        state->progression.jiminyFlags[0] |= 1ULL << flag;
        state->progression.jiminyFlags[4] |= 1ULL << flag;
    } else if (flag <= 0x7F) {
        flag -= 0x40;
        state = &gGameState;
        state->progression.jiminyFlags[1] |= 1ULL << flag;
        state->progression.jiminyFlags[5] |= 1ULL << flag;
    } else if (flag <= 0xBF) {
        flag -= 0x80;
        state = &gGameState;
        state->progression.jiminyFlags[2] |= 1ULL << flag;
        state->progression.jiminyFlags[6] |= 1ULL << flag;
    } else {
        flag -= 0xC0;
        state = &gGameState;
        state->progression.jiminyFlags[3] |= 1ULL << flag;
        state->progression.jiminyFlags[7] |= 1ULL << flag;
    }
}

u8 IsJiminyFlagSet(u32 flag) {
    u64* p;
    u8* q;

    if (flag <= 0x3F) {
        q = (u8*)&gGameState;
        q += offsetof(GameState, progression.jiminyFlags[0]);
    } else if (flag <= 0x7F) {
        flag -= 0x40;
        q = (u8*)&gGameState;
        q += offsetof(GameState, progression.jiminyFlags[1]);
    } else if (flag <= 0xBF) {
        flag -= 0x80;
        q = (u8*)&gGameState;
        q += offsetof(GameState, progression.jiminyFlags[2]);
    } else {
        flag -= 0xC0;
        q = (u8*)&gGameState;
        q += offsetof(GameState, progression.jiminyFlags[3]);
    }

    p = (u64*)q;

    if (*p & (1LL << flag)) {
        return 1;
    }

    return 0;
}

u8 IsJiminyFlagNew(u32 flag) {
    u64* p;
    u8* q;

    if (flag <= 0x3F) {
        q = (u8*)&gGameState;
        q += offsetof(GameState, progression.jiminyFlags[4]);
    } else if (flag <= 0x7F) {
        flag -= 0x40;
        q = (u8*)&gGameState;
        q += offsetof(GameState, progression.jiminyFlags[5]);
    } else if (flag <= 0xBF) {
        flag -= 0x80;
        q = (u8*)&gGameState;
        q += offsetof(GameState, progression.jiminyFlags[6]);
    } else {
        flag -= 0xC0;
        q = (u8*)&gGameState;
        q += offsetof(GameState, progression.jiminyFlags[7]);
    }

    p = (u64*)q;

    if (*p & (1LL << flag)) {
        return 1;
    }

    return 0;
}

void ClearJiminyFlagNew(u32 flag) {
    u64* p;
    u8* q;
    u8* z;

    if (flag == 250) {
        z = (u8*)&gGameState;
        *(u64*)(z + offsetof(GameState, progression.jiminyFlags[4])) = 0;
        *(u64*)(z + offsetof(GameState, progression.jiminyFlags[5])) = 0;
        *(u64*)(z + offsetof(GameState, progression.jiminyFlags[6])) = 0;
        *(u64*)(z + offsetof(GameState, progression.jiminyFlags[7])) = 0;
        return;
    }

    if (flag <= 0x3F) {
        q = (u8*)&gGameState;
        q += offsetof(GameState, progression.jiminyFlags[4]);
    } else if (flag <= 0x7F) {
        flag -= 0x40;
        q = (u8*)&gGameState;
        q += offsetof(GameState, progression.jiminyFlags[5]);
    } else if (flag <= 0xBF) {
        flag -= 0x80;
        q = (u8*)&gGameState;
        q += offsetof(GameState, progression.jiminyFlags[6]);
    } else {
        flag -= 0xC0;
        q = (u8*)&gGameState;
        q += offsetof(GameState, progression.jiminyFlags[7]);
    }

    p = (u64*)q;
    *p &= ~(1LL << flag);
}
