#ifndef GUARD_CHARA_API_H
#define GUARD_CHARA_API_H

#include "types.h"
#include "card_types.h"

struct CharaObjParam;
struct CharaObjParam2;

u8 SioConnectUpdate(void);
u8 SioLinkUpdate(void);
void FreeLinkDecks(void);
void SioLinkClose(void);
u8 SioHasError(void);
void SioConnectInit(void (*a)(void), void (*b)(void), u8 c);
void SioCommandReset(void);
s32 SioCommandSend(void);
s32 SioCommandRecv(void);
void SioSetLinkCallbacks(s32 (*a)(void), s32 (*b)(void));
s32 SioKeySyncSend(void);
s32 SioKeySyncRecv(void);
void SioPrepareDeckExchange(void);
s32 SioExchangeSend(void);
s32 SioExchangeRecv(void);
void SioPrepareCharaLinkExchange(void);
void CharaObjInitDefeat2(struct CharaObjParam2* param);
u8 CharaObjUpdateDefeat2(void);
void CharaObjInitDefeat(struct CharaObjParam* param);
u8 CharaObjUpdateDefeat(void);
void RequestMapRowsCopy(u8* src, u8* dst, u16 size, s16 count);

extern u32 gDebugLogC[100];
extern u32 gVBlankTimerElapsed;
extern s16 gSioCancelTimer;
extern s16 gSioAutoConnectTimer;
extern void (*gSioCancelCallback)(void);
extern u32 gVBlankTimerBase;
extern s16 gSioAutoConnectState;
extern u32 gDebugLogSeq;
extern u32 gDebugLogB[100];
extern u32 gDebugLogA[100];
extern u32 gDebugLogD[100];
extern u16 gDebugLogIndex;
extern s8 gLinkDecksAllocated;
extern u16 gSioExchangeSeqEnd;
extern Deck* gSioSendDeck;
extern s8 gSioHandshakeDone;
extern s8 gSioHandshakeConfirm;
extern u16 gSioRelayKeysB;
extern s8 gSioConnectRetries;
extern u16* gSioExchangeSendData;
#ifdef VERSION_EU
extern u16 gRandomPartnerATimer;
#endif
extern u16 gSioExchangeSeq;
extern Deck* gSioRecvDeck;
#ifdef VERSION_EU
extern u16 gRandomPartnerDpadTimer;
#endif
extern u16* gSioExchangeRecvData;
extern s8 gSioConnectAccepted;
#ifdef VERSION_EU
extern u16 gRandomPartnerDpad;
#endif
extern s8 gSioHandshakeAck;
extern s8 gSioConnected;
extern void (*gSioConnectCallback)(void);
extern u16 gSioConnectId;
extern u16 gSioRelayKeysA;
extern u16 gUnk_0203C3B8;

#endif
