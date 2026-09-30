#ifndef GUARD_CHARA_H
#define GUARD_CHARA_H

#include "registration_data.h"

#include "mode_sio_api.h"








#include "chara_types.h"

#include "card_api.h"
#include "card_deck.h"

#include "chara_api.h"
#include "mode_test_api.h"

#include "sio_api.h"
#include "util.h"
#include "m4a_song.h"
#include "fade.h"
#include "btl_effect.h"
#include "display.h"
#include "battle_actor.h"
#include "types.h"
#include "engine_math.h"
#include "game_state.h"
#include "taskpool.h"
#include "gba/syscall.h"
#include "key.h"
#include "malloc.h"
#include "game.h"
#include "mode.h"
#include "pallet.h"

typedef struct MaskFadeWork {
    u8* tiles;
    u16 tileCount;
    u16 stepDelay;
    s16 step;
    s16 timer;
    u8 tileBuffer[0x20];
    u8 maskedTile[0x20];
    s8 patterns[0x1F4];
} MaskFadeWork;

typedef struct ChgCardObjWork {
    s16 timer;
    s16 unk_02;
    s8 state;
    u8 unk_05[0x03];
    s32* x;
    s32* y;
    s32* scaleX;
    s32* scaleY;
    u8* angle;
    u8* visible;
    s32 targetX;
    s32 targetY;
    s16 delay;
    u8 flipAngleY;
    u8 flipAngleX;
    s16 scale;
    u8 unk_2E[0x02];
    s32 decel;
    s32 speed;
    s32 dirX;
    s32 dirY;
    s32 distance;
} ChgCardObjWork;

typedef struct ChgCardObjParam {
    s32* x;
    s32* y;
    s32* scaleX;
    s32* scaleY;
    u8* angle;
    u8* visible;
    s32 targetX;
    s32 targetY;
    u16 delay;
} ChgCardObjParam;

typedef struct CharaObj {
    u32 x;
    u32 y;
    u32 z;
    u32 tilesAddr;
    u16 tileCount;
    u8 unk_12[0x02];
    u32 tilesAddr2;
    u16 tileCount2;
    u8 unk_1A[0x02];
    u32 tilesAddr3;
    u16 tileCount3;
    u8 unk_22[0x02];
    u32 paletteAddr;
    u16 paletteSize;
    u8 unk_2A[0x02];
    u32 tilesAddr4;
    u16 tileCount4;
    u8 unk_32[0x02];
    u32 paletteAddr2;
    u16 paletteSize2;
    s16 fadeLevel;
    s32 bgFxVz;
    s16 fadeTick;
    s16 timer;
    u8 state;
    u8 unk_45;
    u16 savedPalette[0x400];
    u16 fadedPalette[0x400];
    void (*callback)(void);
    struct BtlObj* prizeObj;
    u16 bankFadeEnabled[32];
    u16 flags;
    u8 unk_1092[0x02];
} CharaObj;

typedef struct CharaPrizeArgs {
    s32 x;
    s32 y;
    s32 z;
    u8 unk_0C[0x14];
} CharaPrizeArgs;

typedef struct MaskFadeArgs {
    u8* tiles;
    u32 tileCount : 16;
    u32 stepDelay : 16;
} MaskFadeArgs;

void task_chara_mask_fade_0(MaskFadeWork* work, MaskFadeArgs* args);
u8 task_chara_mask_fade_1(MaskFadeWork* work);
void task_chara_mask_fade_2(void);
void task_chara_mask_fade_3(void);
void task_chgCardObj_0(ChgCardObjWork* work, ChgCardObjParam* param);
u8 task_chgCardObj_1(ChgCardObjWork* work);
void task_chgCardObj_2(void);
void task_chgCardObj_3(void);
u8 SioConnectUpdateAuto(void);
void DebugLogClear(void);
void DebugLogAdd(u16 a, u16 b, u16 c, u16 d);
void DebugLogResetSeq(void);
void DebugLogNextSeq(void);
void VBlankTimerStart(void);
void VBlankTimerUpdate(void);
void SioAutoConnectStart(void);
u8 SioAutoConnectUpdate(void);
void SioAutoConnectOnConnect(void);
s32 SioConnectSend(void);
s32 SioConnectRecv(void);
s32 SioConnectSendAuto(void);
s32 SioConnectRecvAuto(void);
void SioCommandClearSend(void);
void SioCommandClearRecv(void);
void SioSyncInit(void (*a)(void));
s32 SioSyncSend(void);
s32 SioSyncRecv(void);
void CharaObjFree(void);
void CharaObjSetBankFadeEnabled(u16 a, u8 b);
void RequestTileRowsCopy(u8* src, u8* dst, u16 size, s16 count);

void FreeLinkSendDeck(void);
void FreeLinkPartnerDeck(void);

#endif /* GUARD_CHARA_H */
