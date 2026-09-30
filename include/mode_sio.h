#ifndef GUARD_MODE_SIO_H
#define GUARD_MODE_SIO_H

#include "mode_deck.h"
#include "card_def_data.h"
#include "registration_data.h"

#include "card_description_data.h"

#include "chara_types.h"

#include "chara_api.h"
#include "map_api.h"
#include "mode_sio_api.h"

#include "mode_test_api.h"

#include "pallet.h"
#include "sio_api.h"
#include "save_api.h"

#include "engine_math.h"

#include "card_deck.h"
#include "card_api.h"

#include "text.h"
#include "fade.h"
#include "obj_api.h"
#include "display.h"
#include "types.h"
#include "game_state.h"
#include "card_types.h"
#include "text_types.h"
#include "key.h"
#include "malloc.h"
#include "anim.h"
#include "mode.h"
#include "taskpool.h"
#include "m4a.h"
#include "poo_api.h"
typedef struct SioWorldEntry {
    void* tiles;
    u16 tilesSize;
    u16 unk_06;
    void* map;
    u16 mapSize;
    u16 unk_0E;
    void* palette;
    u16 paletteSize;
    u16 unk_16;
    void* text;
    u8 world;
    u8 unk_1D;
    u16 textX;
} SioWorldEntry;

typedef struct SioChgCardPos {
    s16 x;
    s16 y;
    s8 owner;
    s8 up;
    s8 down;
    s8 left;
    s8 right;
    u8 unk_09[3];
} SioChgCardPos;

typedef struct SioAnimDef {
    void* gfxTable;
    void* anims;
    void* tiles;
    u8 animId;
} SioAnimDef;

#ifdef VERSION_JP
#define SIO_ERROR_TEXT_SLOTS 98
#else
#ifdef VERSION_EU
#define SIO_ERROR_TEXT_SLOTS 216
#else
#define SIO_ERROR_TEXT_SLOTS 108
#endif
#endif

#ifdef VERSION_EU
#define SIO_CONNECT_TEXT_SLOTS 180
#else
#define SIO_CONNECT_TEXT_SLOTS 0x5A
#endif

typedef struct SioBtlConnectWork {
    u16 unk_00;
    s16 timer;
    s8 state;
    u8 textSlotCount;
    u8 unk_06[2];
    TextSlot textSlots[SIO_CONNECT_TEXT_SLOTS];
    void* palette;
} SioBtlConnectWork;

typedef struct SioErrorWork {
    u8 unk_00;
    u8 unk_01;
    u16 unk_02;
    u16 unk_04;
    u8 textSlotCount;
    u8 unk_07;
    TextSlot textSlots[SIO_ERROR_TEXT_SLOTS];
    void* palette;
} SioErrorWork;

typedef struct SioCardTaskArg {
    s32* x;
    s32* y;
    s32* scaleX;
    s32* scaleY;
    u8* angle;
    s8* visible;
    s32 targetX;
    s32 targetY;
    u16 delay;
    u8 unk_22[2];
} SioCardTaskArg;

typedef struct SioChgCardWork {
    u8 unk_000;
    s8 state;
    s16 blinkPhase;
    s16 timer;
    u8 unk_006[2];
    void* unk_008[4];
    void* gfx[2];
    AnimState anim[2];
    void* tiles;
    void* palette;
    void* gfx2;
    AnimState anim2;
    s8 cursorVisible;
    u8 unk_075;
    s16 cursor;
    s16 nextCursor;
    s16 x;
    s16 y;
    u8 unk_07E[2];
    void* tiles2;
    void* palette2;
    void* gfx3;
    AnimState anim3;
    s8 ready;
    s8 cardVisible[10];
    u8 unk_0AF;
    s32 x2[10];
    s32 y2[10];
    void* tiles3[10];
    void* palette3[10];
    void* gfx4[10];
    void* tiles4;
    void* palette4;
    void* gfx5[10];
    s32 scaleX[10];
    s32 scaleY[10];
    u8 angle[10];
    u16 offeredCard;
    void* tiles5;
    void* gfx6;
    s8 messageVisible;
    u8 textSlotCount;
    u8 unk_20E[2];
    TextSlot textSlots[42];
    s8 cardInfoVisible;
    u8 textSlotCount2;
    u8 unk_362[2];
    TextSlot textSlots2[20];
    s16 receiveOk;
    u16 collectionBackup[0x3E7];
    u64 obtainedCardKindsBackup;
    s16 x3;
    s16 y3;
    s8 leaveDelay;
    u8 unk_BE1[3];
    TaskPool tasks;
} SioChgCardWork;

typedef struct SioBtlCardgetWork {
    s8 state;
    u8 unk_01;
    u16 unk_02;
    s16 timer;
    s8 lost;
    u8 unk_07;
    void* tiles;
    void* tiles2;
    void* palette;
    void* palette2;
    void* gfx;
    void* gfx2;
    s32 unk_20;
    s32 unk_24;
    void* tiles3;
    void* tiles4;
    void* palette3;
    void* palette4;
    void* gfx3;
    void* gfx4;
    u8 unk_40[4];
} SioBtlCardgetWork;

typedef struct SioBtlOptionWork {
    s8 cursor;
    u8 returnState;
    s8 state;
    u8 unk_003;
    s16 fadeLevel;
    s16 timer;
    void* unk_008[4];
    void* gfx6[2];
    AnimState anim2[2];
    u8 textSlotCount;
    u8 unk_051[3];
    TextSlot textSlots[20];
#ifdef VERSION_EU
    TextSlot unkEu_0F4[20];
#endif
    void* palette7;
    u8 textSlotCount2;
    u8 unk_0F9[3];
    TextSlot textSlots2[10];
#ifdef VERSION_EU
    TextSlot unkEu_1EC[10];
#endif
    void* palette8;
    u8 textSlotCount3;
    u8 unk_151[3];
    TextSlot textSlots3[10];
#ifdef VERSION_EU
    TextSlot unkEu_294[10];
#endif
    void* palette9;
    void* tiles;
    void* palette;
    void* gfx;
    s8 menuOpen;
    u8 unk_1B5[3];
    void* tiles2;
    void* palette2;
    void* gfx2;
    AnimState anim;
    s32 y;
    s8 cursorVisible;
    u8 unk_1E1[3];
    void* tiles4;
    void* palette4;
    void* gfx4;
    void* gfx7;
    void* gfx8;
    s8 handicapMarkerVisible;
    u8 unk_1F9;
    u16 frameCount;
    void* tiles5[2];
    void* gfx5[2];
    void* palette5[2];
    s8 handicaps[2];
    s8 handicap;
    s8 player1Ready;
    s8 player2Ready;
    u8 unk_219;
    u16 modeArg;
    void* tiles3;
    void* palette3;
    void* gfx3;
    s8 messageVisible;
    u8 textSlotCount4;
    u8 unk_22A[2];
    TextSlot textSlots4[60];
#ifdef VERSION_EU
    TextSlot unkEu_54C[60];
#endif
    void* palette6;
    s8 worldChangeState;
    u8 unk_411;
    s16 x;
    s16 y2;
    s8 leaveDelay;
    s8 worldEntry;
    u16 unk_418;
    u8 unk_41A[2];
} SioBtlOptionWork;

extern u8 gUnk_0815A2BE[];
extern u8 gUnk_08159E4A[];
extern u8 gUnk_08159EC4[];
extern u8 gUnk_0815A20C[];
extern u8 gUnk_0815A3C0[];
extern u8 gUnk_0815A404[];
extern u8 gUnk_0815A428[];
extern u8 gUnk_0815A4B6[];
extern u8 gUnk_0815B3FA[];
extern u8 gUnk_0815A23C[];
extern u8 gUnk_0815B3D4[];
extern u8 gSor1ff00Tiles[];
extern u8 gSoraPalette[];
extern u8 gSor1fl26Tiles[];
extern u8 gUnk_0815A394[];
extern u8 gCard00Palette[];
extern u8 gUnk_0962B090[];
extern u8 gUnk_0962CAFC[];
extern u8 gUnk_0962D196[];
extern u8 gUnk_0962BEDA[];
extern u8 gUnk_0962D7C0[];
extern u8 gUnk_0962D900[];
extern u8 gUnk_0962DEA8[];
extern u8 gUnk_0962DBA0[];
extern u8 gUnk_096B2524[];
extern u8 gUnk_096FBA04[];
extern u8 gUnk_096FAC64[];
extern u8 gUnk_096FBAA4[];
extern u8 gUnk_096FBAC4[];
extern u8 gUnk_096FBC04[];
extern u8 gUnk_096FBCC4[];
extern u8 gUnk_096FBD24[];
extern u8 gUnk_096FBD44[];
extern u8 gUnk_096FBD64[];
extern u8 gUnk_096FBDA4[];
extern u8 gUnk_096FBDE4[];
extern u8 gUnk_096FBE04[];
extern u8 gUnk_096FBE24[];
extern u8 gUnk_096FBF04[];
extern Mode gModeDeckExchange;

void mode_sio_btl_connect_0(s32 arg);
void mode_sio_btl_connect_1(void);
void mode_sio_btl_connect_2(void);
void SioBtlConnectOnConnect(void);
void SioBtlConnectOnCancel(void);
void SioInitWorldList(void);
void SetSioBtlOptionAnimation(u16 a, u16 b, u16 c);
void mode_sio_btl_option_0(s32 arg);
void SioBtlOptionLoadBg(void);
void SioBtlOptionInitObjs(void);
void SioBtlOptionLoadWorld(void);
void SioBtlOptionFadeIn(void);
void SioBtlOptionWaitStart(void);
void SioBtlOptionHandleIdle(void);
void SioBtlOptionHandleMenu(void);
void SioBtlOptionSetHandicap(void);
void SioBtlOptionChangeWorld(void);
void SioBtlOptionWaitReady(void);
void SioBtlOptionConfirm(void);
void SioBtlOptionStartDeckExchange(void);
void SioBtlOptionWaitDeckExchange(void);
void SioBtlOptionResumeCommands(void);
void func_080B041C(void);
void SioBtlOptionSyncStart(void);
void SioBtlOptionStartBattle(void);
void SioBtlOptionDraw(void);
void SioBtlOptionCheckReady(void);
void SioBtlOptionRecvWorld(void);
void SioBtlOptionSyncDeckNames(void);
void SioBtlOptionDrawStats(void);
void SioApplyBattleSettings(void);
void SioBtlOptionSyncHandicaps(void);
void SioBtlOptionUpdateHandicapGauges(u16 a, u16 b);
void SioBtlOptionCancelReady(void);
void mode_sio_btl_cardget_0(s32 arg);
void SioBtlCardgetLoadBgTiles(void);
void SioBtlCardgetLoadBg(void);
void SioBtlCardgetShowResult(void);
void mode_sio_btl_cardget_1(void);
void mode_sio_chg_connect_0(s32 arg);
void mode_sio_chg_connect_1(void);
void mode_sio_chg_connect_2(void);
void SioChgConnectOnConnect(void);
void SioChgConnectOnCancel(void);
void SioChgConnectStartTrade(void);
void mode_sio_chg_card_0(s32 arg);
void SioChgCardLoadBg(void);
void SioChgCardInitObjs(void);
void mode_sio_chg_card_1(void);
void SioChgCardWaitStart(void);
void SioChgCardSelect(void);
void SioChgCardConfirm(void);
void SioChgCardTryTrade(void);
void SioChgCardWaitTradeResult(void);
void SioChgCardTradeFailed(void);
void SioChgCardStartMove(void);
void SioChgCardSave(void);
void SioChgCardWaitMove(void);
void func_080B2AE8(void);
void func_080B2B48(void);
void SioChgCardRestart(void);
void SioChgCardDraw(void);
void SioChgCardRecvSlots(void);
void SioChgCardSetSlot(u16 a);
void SioChgCardSetSlotId(u16 a);
void SioChgCardReturnCard(void);
s8 SioChgCardHasOwnCards(void);
s8 SioChgCardSlotsEmpty(void);
void SioChgCardShowInfo(void);
void SioChgCardHideInfo(void);
s16 AddCardToCollection(u16 a);
void SioChgCardDrawPointTotals(void);
void SioChgCardHandleInput(void);
void SioChgCardCancelReady(void);
void SioChgCardCreateMoveTasks(void);
void SioChgCardBackupCollection(void);
void SioChgCardRestoreCollection(void);
s16 SioChgCardReceiveCards(void);
void SioChgCardReturnOwnCards(void);
void func_080B3DF8(void);
void mode_sioError_0(s32 arg);
void mode_sioError_1(void);
void SioErrorDraw(void);
void mode_sioError_2(void);
void SetSioChgCardAnimation(u16 a, u16 b, u16 c);
void SioBtlCardgetDraw(void);
void SioBtlCardgetLoad1PWin(void);
void SioBtlCardgetLoad2PWin(void);
void SioBtlOptionPlayWorldBgm(void);

#endif /* GUARD_MODE_SIO_H */
