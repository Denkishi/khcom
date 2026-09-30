#ifndef GUARD_BTL4_H
#define GUARD_BTL4_H

#include "battle_localized_data.h"

#include "display.h"

#include "card_api.h"

#include "obj_api.h"
#include "battle_actor.h"
#include "types.h"
#include "battle_work.h"
#include "game_state.h"
#include "anim.h"
typedef struct BtlPopSrc {
    s32 x;
    s32 y;
    s32 z;
    u8 unk_0C[0x06];
    s16 number;
} BtlPopSrc;

typedef struct BtlPopCbWork {
    void* tiles;
    void* palette;
    void* gfx;
    s32 x;
    s32 y;
    s32 z;
    s16 timer;
    u8 unk_1A[0x02];
} BtlPopCbWork;

typedef struct BtlExpWork {
    void* palette;
    void* tiles;
    void* tiles2[6];
    void* gfx;
    void* gfx2[6];
    s16 timer;
    u8 level;
    u8 unk_3F;
    u16 gainedExp;
    u8 unk_42[0x02];
    u32 lastExp;
    u32 state;
} BtlExpWork;

typedef struct BtlVslockonWork {
    void* tiles;
    void* palette;
    AnimState anim;
    void* gfx;
} BtlVslockonWork;

typedef struct BtlHpothWork {
    s32 hpRatio;
    u8 firstUpdate;
    u8 unk_05[0x03];
    void* palette2;
    void* palette;
    void* tiles;
    void* tiles2;
    void* tiles3;
    void* tiles4;
    void* gfx;
    void* gfx2;
    void* gfx3;
    AnimState anim2;
    AnimState anim;
    u8 unk_5C;
    u8 unk_5D;
    s16 timer;
    s16 prevHp;
    s16 displayHp;
    s16 gaugeSize;
    u8 unk_66[0x02];
    u32 gaugeMode;
} BtlHpothWork;

extern u8 gUnk_08B1D8BC[];
extern u8 gUnk_08B1FCBC[];
extern u8 gUnk_08B1FCCC[];
extern u8 gUnk_08B1FCDC[];
extern u8 gUnk_08B1FCEC[];
extern u8 gUnk_08B1FCFC[];
extern u8 gUnk_08B1FD0C[];
extern u8 gUnk_08B1FD1C[];
extern u8 gUnk_08B1FD2C[];
extern u8 gUnk_08B1FD3C[];
extern u8 gUnk_08B1FD4C[];
extern u8 gUnk_08B1FD66[];
extern u8 gUnk_08B25EF0[];
extern u8 gBStatesPalette[];
extern u8 gUnk_096FAC64[];

void CreatePersistentSysmsgwinTask(void* a, u16 b);

void task_btl_pop_cb_0(BtlPopCbWork* work, BtlPopSrc* src);
s32 task_btl_pop_cb_1(BtlPopCbWork* work);
void task_btl_pop_cb_2(BtlPopCbWork* work);
void task_btl_pop_cb_3(BtlPopCbWork* work);
void* GetExpDigitGfx(s32 digit, u8 leading);
void BtlExpSetNumber(BtlExpWork* work, u32 value);
void task_btl_exp_0(BtlExpWork* work);
s32 task_btl_exp_1(BtlExpWork* work);
void task_btl_exp_2(BtlExpWork* work);
void task_btl_exp_3(BtlExpWork* work);
void task_btl_vslockon_0(BtlVslockonWork* work);
s32 task_btl_vslockon_1(BtlVslockonWork* work);
void task_btl_vslockon_2(BtlVslockonWork* work);
void task_btl_vslockon_3(BtlVslockonWork* work);
void task_btl_hpoth_0(BtlHpothWork* work);
s32 task_btl_hpoth_1(BtlHpothWork* work);
void task_btl_hpoth_2(BtlHpothWork* work);
void task_btl_hpoth_3(BtlHpothWork* work);

#endif /* GUARD_BTL4_H */
