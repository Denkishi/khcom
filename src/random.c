#include "types.h"

u32 gRandSeed;
u8 gUnk_0203402C[4];
u32 gRandomState[4];

void SeedRand(u32 seed) {
    gRandSeed = seed;
}

u32 Rand(void) {
    gRandSeed = (gRandSeed * 0x41C64E6D + 12345) & 0x7FFF;
    return gRandSeed;
}

void SeedRandom(u32 seed) {
    SeedRand(seed);
    gRandomState[0] = Rand();
    gRandomState[1] = Rand();
    gRandomState[2] = Rand();
    gRandomState[3] = Rand();
}

u16 GetRandom(void) {
    u32 x;

    x = gRandomState[1];
    x <<= 1;

    if (gRandomState[0] & 0x80000000) {
        x++;
    }

    x <<= 1;

    if (gRandomState[0] & 0x40000000) {
        x++;
    }

    gRandomState[3] <<= 1;

    if (gRandomState[2] & 0x80000000) {
        gRandomState[3]++;
    }

    x ^= gRandomState[3];
    gRandomState[3] = gRandomState[2];
    gRandomState[2] = gRandomState[1];
    gRandomState[1] = gRandomState[0];
    gRandomState[0] = x;
    x &= 0x7FFF;
    return x;
}
