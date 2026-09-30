#include "macros.h"
#include "registration_data.h"
#include "chara_api.h"
#include "display.h"
#include "pallet.h"
#include "sio_api.h"
#include "util.h"
#include "chara.h"
#include "gba/keys.h"
#include "system_state.h"

u32 gDebugLogC[100] EWRAM_COMMON(16);
u32 gVBlankTimerElapsed EWRAM_COMMON(4);
s16 gSioCancelTimer EWRAM_COMMON(4);
s16 gSioAutoConnectTimer EWRAM_COMMON(4);
void (*gSioCancelCallback)(void) EWRAM_COMMON(4);
u32 gVBlankTimerBase EWRAM_COMMON(4);
s16 gSioAutoConnectState EWRAM_COMMON(8);
u32 gDebugLogSeq EWRAM_COMMON(4);
u32 gDebugLogB[100] EWRAM_COMMON(16);
u32 gDebugLogA[100] EWRAM_COMMON(16);
u32 gDebugLogD[100] EWRAM_COMMON(16);
u16 gDebugLogIndex EWRAM_COMMON(4);
s8 gLinkDecksAllocated EWRAM_COMMON(4);
u16 gSioExchangeSeqEnd EWRAM_COMMON(4);
Deck* gSioSendDeck EWRAM_COMMON(4);
s8 gSioHandshakeDone EWRAM_COMMON(4);
s8 gSioHandshakeConfirm EWRAM_COMMON(4);
u16 gSioRelayKeysB EWRAM_COMMON(4);
s8 gSioConnectRetries EWRAM_COMMON(4);
u16* gSioExchangeSendData EWRAM_COMMON(4);
#ifdef VERSION_EU
u16 gRandomPartnerATimer EWRAM_COMMON(4);
#endif
u16 gSioExchangeSeq EWRAM_COMMON(4);
Deck* gSioRecvDeck EWRAM_COMMON(4);
#ifdef VERSION_EU
u16 gRandomPartnerDpadTimer EWRAM_COMMON(4);
#endif
u16* gSioExchangeRecvData EWRAM_COMMON(4);
s8 gSioConnectAccepted EWRAM_COMMON(4);
#ifdef VERSION_EU
u16 gRandomPartnerDpad EWRAM_COMMON(4);
#endif
s8 gSioHandshakeAck EWRAM_COMMON(4);
s8 gSioConnected EWRAM_COMMON(4);
void (*gSioConnectCallback)(void) EWRAM_COMMON(4);
u16 gSioConnectId EWRAM_COMMON(4);
u16 gSioRelayKeysA EWRAM_COMMON(4);
u16 gUnk_0203C3B8 EWRAM_COMMON(4);

u8 gMaskFadeTileMasks[1440] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0x0F, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xF0,
    0xF0, 0x0F, 0xFF, 0xFF, 0x0F, 0xF0, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 0x0F, 0xF0, 0xFF, 0xFF, 0xF0,
    0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xF0, 0x0F, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xF0,
    0xF0, 0x0F, 0xFF, 0x0F, 0x0F, 0xF0, 0xFF, 0x0F, 0x0F, 0x0F, 0xFF, 0x0F, 0xF0, 0x0F, 0xFF, 0xF0,
    0xF0, 0xFF, 0x0F, 0xFF, 0xF0, 0x0F, 0xF0, 0xFF, 0xF0, 0x0F, 0xFF, 0xF0, 0xFF, 0x0F, 0xFF, 0xF0,
    0xF0, 0x0F, 0x0F, 0x0F, 0x0F, 0xF0, 0xFF, 0x0F, 0x0F, 0x0F, 0xF0, 0x00, 0xF0, 0x0F, 0xFF, 0xF0,
    0x00, 0xFF, 0x0F, 0xFF, 0x00, 0x00, 0xF0, 0xFF, 0xF0, 0x0F, 0xFF, 0xF0, 0xF0, 0x0F, 0xFF, 0x00,
    0xF0, 0x00, 0x0F, 0x0F, 0x0F, 0xF0, 0x0F, 0x0F, 0x0F, 0x0F, 0xF0, 0x00, 0xF0, 0x0F, 0xF0, 0xF0,
    0x00, 0xF0, 0x0F, 0xF0, 0x00, 0x00, 0xF0, 0x0F, 0x00, 0x0F, 0x0F, 0xF0, 0xF0, 0x0F, 0xFF, 0x00,
    0x00, 0x00, 0x0F, 0x0F, 0x00, 0xF0, 0x0F, 0x0F, 0x00, 0x0F, 0xF0, 0x00, 0xF0, 0x0F, 0x00, 0xF0,
    0x00, 0xF0, 0x0F, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0xF0, 0x0F, 0x0F, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0xF0, 0x00, 0xF0, 0x0F, 0x00, 0xF0,
    0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x0F, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0xF0, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0x0F, 0xFF, 0xF0, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 0xFF, 0x0F, 0xFF,
    0xF0, 0xFF, 0xFF, 0x0F, 0x0F, 0xFF, 0xFF, 0x0F, 0xF0, 0xFF, 0xF0, 0xFF, 0xF0, 0xFF, 0x0F, 0xFF,
    0xFF, 0x0F, 0xFF, 0xF0, 0x0F, 0xF0, 0xFF, 0xF0, 0xFF, 0xFF, 0x0F, 0xF0, 0xFF, 0xFF, 0x0F, 0xFF,
    0xF0, 0xF0, 0xFF, 0x0F, 0x0F, 0xF0, 0xF0, 0x0F, 0xF0, 0xF0, 0xF0, 0xFF, 0xF0, 0x0F, 0x0F, 0xFF,
    0xFF, 0x0F, 0x0F, 0xF0, 0x0F, 0xF0, 0xFF, 0xF0, 0x0F, 0xFF, 0x0F, 0xF0, 0xFF, 0xF0, 0x0F, 0xFF,
    0x00, 0xF0, 0xF0, 0x0F, 0x0F, 0xF0, 0x00, 0x0F, 0xF0, 0xF0, 0xF0, 0xFF, 0x00, 0x0F, 0x0F, 0x0F,
    0xFF, 0x0F, 0x00, 0xF0, 0x0F, 0xF0, 0xFF, 0xF0, 0x0F, 0xFF, 0x0F, 0xF0, 0xF0, 0xF0, 0x0F, 0x0F,
    0x00, 0xF0, 0xF0, 0x0F, 0x0F, 0xF0, 0x00, 0x00, 0xF0, 0xF0, 0xF0, 0x00, 0x00, 0x0F, 0x00, 0x0F,
    0xFF, 0x0F, 0x00, 0x00, 0x0F, 0xF0, 0x0F, 0xF0, 0x0F, 0x0F, 0x0F, 0xF0, 0xF0, 0xF0, 0x0F, 0x00,
    0x00, 0xF0, 0xF0, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00,
    0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x0F, 0x0F, 0x0F, 0xF0, 0xF0, 0x00, 0x0F, 0x00,
    0x00, 0xF0, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0xF0, 0x00, 0x00, 0x0F, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0xFF, 0xF0,
    0xFF, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xF0, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x0F, 0xF0, 0xFF, 0xFF, 0xFF, 0xF0, 0xF0, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0x0F, 0x0F, 0xFF, 0xF0,
    0xF0, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xF0, 0x0F, 0xFF, 0xFF, 0xF0, 0xFF, 0x0F,
    0x0F, 0xF0, 0xFF, 0x0F, 0xFF, 0xF0, 0xF0, 0xFF, 0xFF, 0xFF, 0xF0, 0xF0, 0x00, 0x0F, 0xF0, 0xF0,
    0xF0, 0x0F, 0xFF, 0x0F, 0xF0, 0xFF, 0x00, 0xFF, 0xF0, 0xF0, 0x0F, 0xFF, 0xFF, 0xF0, 0xF0, 0x0F,
    0x0F, 0xF0, 0xF0, 0x0F, 0x0F, 0xF0, 0xF0, 0xFF, 0xF0, 0xFF, 0xF0, 0xF0, 0x00, 0x0F, 0x00, 0xF0,
    0x00, 0x0F, 0xF0, 0x0F, 0x00, 0xFF, 0x00, 0xFF, 0xF0, 0xF0, 0x0F, 0xFF, 0xF0, 0xF0, 0xF0, 0x0F,
    0x00, 0xF0, 0xF0, 0x0F, 0x0F, 0xF0, 0xF0, 0x0F, 0xF0, 0x00, 0xF0, 0xF0, 0x00, 0x0F, 0x00, 0xF0,
    0x00, 0x0F, 0x00, 0x0F, 0x00, 0x0F, 0x00, 0xF0, 0xF0, 0xF0, 0x0F, 0xFF, 0xF0, 0xF0, 0x00, 0x0F,
    0x00, 0x00, 0xF0, 0x0F, 0x00, 0xF0, 0xF0, 0x0F, 0x00, 0x00, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0xF0,
    0x00, 0x0F, 0x00, 0x00, 0x00, 0x0F, 0x00, 0xF0, 0x00, 0xF0, 0x0F, 0xF0, 0xF0, 0xF0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0,
    0x00, 0x0F, 0x00, 0x00, 0x00, 0x0F, 0x00, 0xF0, 0x00, 0x00, 0x0F, 0x00, 0xF0, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xF0, 0x0F, 0xF0, 0xFF, 0xFF, 0xF0, 0x0F, 0xFF, 0xFF, 0xFF, 0x0F, 0x0F, 0xFF, 0xFF, 0xFF, 0x0F,
    0x0F, 0x0F, 0xF0, 0xFF, 0x0F, 0xF0, 0x0F, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF,
    0xF0, 0x0F, 0xF0, 0x0F, 0x00, 0xF0, 0x0F, 0x0F, 0xF0, 0xF0, 0x0F, 0x0F, 0x0F, 0x0F, 0xF0, 0x00,
    0x0F, 0x0F, 0x00, 0xF0, 0x0F, 0xF0, 0x0F, 0xF0, 0xFF, 0x0F, 0x0F, 0xFF, 0xFF, 0x0F, 0x0F, 0xF0,
    0x00, 0x0F, 0x00, 0x00, 0x00, 0xF0, 0x0F, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x00, 0xF0, 0x00,
    0x0F, 0x0F, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0x00, 0x00, 0xF0, 0x0F, 0x0F, 0x0F, 0x00,
    0x00, 0x0F, 0x00, 0x00, 0x00, 0xF0, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x00,
    0x0F, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00,
    0x00, 0x0F, 0x00, 0x00, 0x00, 0xF0, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00,
    0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00,
    0x00, 0x0F, 0x00, 0x00, 0x00, 0xF0, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00,
    0x00, 0x0F, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xF0, 0xF0, 0xFF, 0xFF, 0x0F,
    0x0F, 0xFF, 0x0F, 0xFF, 0xFF, 0xF0, 0xF0, 0xFF, 0x0F, 0xF0, 0xFF, 0x0F, 0x0F, 0x0F, 0xFF, 0x0F,
    0x00, 0x0F, 0xF0, 0x0F, 0x0F, 0xF0, 0xFF, 0x0F, 0x00, 0xF0, 0xF0, 0xF0, 0xF0, 0xFF, 0xF0, 0x00,
    0x0F, 0xF0, 0x0F, 0xFF, 0x0F, 0x00, 0xF0, 0xFF, 0x0F, 0xF0, 0xFF, 0x0F, 0x0F, 0x0F, 0x0F, 0x00,
    0x00, 0x00, 0x00, 0x0F, 0x00, 0xF0, 0xF0, 0x00, 0x00, 0xF0, 0xF0, 0xF0, 0xF0, 0x00, 0x00, 0x00,
    0x0F, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0xF0, 0xF0, 0x0F, 0x0F, 0x0F, 0x0F, 0x00,
    0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00,
    0x0F, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x0F, 0x0F, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x0F, 0x0F, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static CharaObj* gCharaObj;
static TaskPool gCharaTaskPool;

void task_chara_mask_fade_0(MaskFadeWork* work, MaskFadeArgs* args) {
    s32 i;

    work->tiles = args->tiles;
    work->tileCount = args->tileCount;
    work->timer = 0;
    work->step = 1;
    work->stepDelay = args->stepDelay;

    for (i = 0; i < work->tileCount; i++) {
        work->patterns[i] = GetRandom() % 5;
    }
}

u8 task_chara_mask_fade_1(MaskFadeWork* work) {
    s32 i;
    s32 j;

    if (++work->timer > work->stepDelay) {
        work->timer = 0;

        for (i = 0; i < work->tileCount; i++) {
            CpuFastSet(work->tiles + i * 32, work->tileBuffer, 8);

            for (j = 0; j <= 31; j++) {
                work->maskedTile[j] = work->tileBuffer[j] & gMaskFadeTileMasks[j + work->step * 32 + work->patterns[i] * 288];
            }
            CpuFastSet(work->maskedTile, work->tiles + i * 32, 8);
        }
        work->step++;
        if (work->step > 8) {
            work->step = 0;
            return 0;
        }
    }
    return 1;
}

void task_chara_mask_fade_2(void) {
}

void task_chara_mask_fade_3(void) {
}

void task_chgCardObj_0(ChgCardObjWork* work, ChgCardObjParam* param) {
    s32 x;
    s32 y;

    work->x = param->x;
    work->y = param->y;
    work->scaleX = param->scaleX;
    work->scaleY = param->scaleY;
    work->angle = param->angle;
    work->visible = param->visible;
    work->targetX = param->targetX;
    work->targetY = param->targetY;
    work->delay = param->delay;
    work->scale = 0x100;
    work->flipAngleY = 0;
    work->flipAngleX = 0;
    work->speed = 0x300;
    work->decel = 2;
    x = work->targetX - *work->x;
    y = work->targetY - *work->y;
    work->distance = NormalizeVector2D8(&x, &y);
    work->dirX = -x;
    work->dirY = -y;
    work->timer = 0;
    work->unk_02 = 0;
    work->state = 0;
}

static inline u8 ChgCardRotation(ChgCardObjWork* work, u8 rotation) {
    u8 phase;

    if (work->scale < 0) {
        phase = -rotation;
    } else {
        phase = rotation;
    }
    return phase;
}

u8 task_chgCardObj_1(ChgCardObjWork* work) {
    u8 phase;
    u8 zero;
    u8 angleA;
    s32 x;
    s32 y;
    s32* p10;
    s32* p14;

    switch (work->state) {
    case 0:
        if (work->timer >= work->delay) {
            work->timer = 0;
            work->state++;
        } else {
            work->timer++;
        }
        break;
    case 1:
        *work->x += (work->dirX * work->speed) >> 8;
        *work->y += (work->dirY * work->speed) >> 8;
        *work->angle += 32;
        angleA = work->flipAngleY + ((64 - work->flipAngleY) >> 4);
        zero = 0;
        work->flipAngleY = angleA;
        work->flipAngleX = zero;
        work->distance = VectorLength2D(work->targetX - *work->x, work->targetY - *work->y);
        work->speed -= work->decel;
        work->decel += 2;
        phase = ChgCardRotation(work, 128);
        p10 = work->scaleX;
        *p10 = (-gSineTable[((work->flipAngleX + phase) & 0xFF) + 64] * work->scale) >> 8;
        p14 = work->scaleY;
        *p14 = (-gSineTable[((work->flipAngleY + 128) & 0xFF) + 64] * work->scale) >> 8;

        if (*p10 >= -2 && *p10 <= 2) {
            *p10 = 2;
        }

        if (*p14 >= -2 && *p14 <= 2) {
            *p14 = 2;
        }

        if (work->speed < 0) {
            x = work->targetX - *work->x;
            y = work->targetY - *work->y;
            NormalizeVector2D8(&x, &y);
            work->dirX = -x;
            work->dirY = -y;

            if (work->distance <= 0x7FF) {
                m4aSongNumStart(SONG_SYS_ITEMGET);
                *work->visible = zero;
                return 0;
            }
        }
        break;
    }
    return 1;
}

void task_chgCardObj_2(void) {
}

void task_chgCardObj_3(void) {
}

u8 SioConnectUpdate(void) {
    u32* p;

    p = &gSioStatus;
    *p = SioRunStateMachine(&gSioHandshakeRequest, gSioSendFrame, gSioRecvFrame);
    gSioPlayerId = gSioStatus & 3;
    gSioPlayerCount = (gSioStatus & 0x1C) >> 2;
    gUnk_02039824 = (gSioStatus & 0xE00) >> 9;

    if ((gSioStatus & 0x40) && gSioPlayerId <= 1) {
        SioConnectSend();

        if ((gSioStatus & 0x100) == 0) {
            gSioLinkResult = SioConnectRecv();
        }

        if (gSioStatus & 0x7F0000) {
            if (gSioConnected == 1) {
                gSioErrorFrameCount++;
                if (gSioErrorFrameCount > 180) {
                    gSioLinkResult = 1;
                }
            }
        }

        if (gSioLinkResult == 1) {
            gSystemFlags &= 0xFFFE;
            gSioErrorStatus = gSioStatus;
            ModeRequest(&gModeSioError, 0);
            return gSioLinkResult;
        }
    } else {
        if (GetKeysPressed() & B_BUTTON) {
            gSioCancelTimer = 10;
        }

        if (gSioCancelTimer > 0) {
            gSioCancelTimer--;
            if (gSioCancelTimer == 0) {
                SioShutdown();

                if (gSioCancelCallback != 0) {
                    gSioCancelCallback();
                }
            }
        }
    }
    return gSioLinkResult;
}

u8 SioLinkUpdate(void) {
    u32* p;

    p = &gSioStatus;
    *p = SioTransferFrames(&gSioHandshakeRequest, gSioSendFrame, gSioRecvFrame);
    gSioPlayerId = gSioStatus & 3;
    gSioPlayerCount = (gSioStatus & 0x1C) >> 2;
    gUnk_02039824 = (gSioStatus & 0xE00) >> 9;

    if ((gSioStatus & 0x40) && gSioPlayerId <= 1) {
        if (gSioLinkRecvCallback != 0) {
            gSioLinkResult = gSioLinkRecvCallback();
        }

        if (gSioLinkSendCallback != 0) {
            gSioLinkSendCallback();
        }

        if (gSioStatus & 0x7F0000) {
            if (gSioConnected == 1) {
                gSioErrorFrameCount++;
                if (gSioErrorFrameCount > 180) {
                    gSystemFlags &= 0xFFFE;
                    gSioErrorStatus = gSioStatus;
                    ModeRequest(&gModeSioError, 0);
                    gSioLinkResult = 1;
                }
            }
        }
    }
    return gSioLinkResult;
}


u8 SioConnectUpdateAuto(void) {
    u32* p;

    p = &gSioStatus;
    *p = SioRunStateMachine(&gSioHandshakeRequest, gSioSendFrame, gSioRecvFrame);
    gSioPlayerId = gSioStatus & 3;
    gSioPlayerCount = (gSioStatus & 0x1C) >> 2;
    gUnk_02039824 = (gSioStatus & 0xE00) >> 9;

    if ((gSioStatus & 0x40) && gSioPlayerId <= 1) {
        SioConnectSendAuto();

        if ((gSioStatus & 0x100) == 0) {
            gSioLinkResult = SioConnectRecvAuto();
        }

        if (gSioStatus & 0x7F0000) {
            if (gSioConnected == 1) {
                gSioErrorFrameCount++;
                if (gSioErrorFrameCount > 180) {
                    gSioLinkResult = 1;
                }
            }
        }

        if (gSioLinkResult == 1) {
            gSystemFlags &= 0xFFFE;
            gSioErrorStatus = gSioStatus;
            ModeRequest(&gModeSioError, 0);
            return gSioLinkResult;
        }
    }
    return gSioLinkResult;
}

void FreeLinkDecks(void) {
    FreeLinkSendDeck();
    FreeLinkPartnerDeck();
}

void SioLinkClose(void) {
    if (gSystemFlags & 1) {
        SioShutdown();
        gSystemFlags &= 0xFFFE;
    }

    if (gSystemFlags & 0x10) {
        gSystemFlags &= 0xFFEF;
    }

    if (gLinkDecksAllocated == 1) {
        FreeLinkDecks();
        gLinkDecksAllocated = 0;
    }
}

void DebugLogClear(void) {
    s32 i;

    for (i = 0; i < 100; i++) {
        gDebugLogA[i] = 0;
        gDebugLogB[i] = 0;
        gDebugLogC[i] = 0;
        gDebugLogD[i] = 0;
    }
    gDebugLogIndex = 0;
    gDebugLogSeq = 0;
}

void DebugLogAdd(u16 a, u16 b, u16 c, u16 d) {
    gDebugLogA[gDebugLogIndex] = (gDebugLogSeq << 24) | a;
    gDebugLogB[gDebugLogIndex] = (gDebugLogSeq << 24) | b;
    gDebugLogC[gDebugLogIndex] = (gDebugLogSeq << 24) | c;
    gDebugLogD[gDebugLogIndex] = (gDebugLogSeq << 24) | d;
    gDebugLogIndex++;
    if (gDebugLogIndex > 99) {
        gDebugLogIndex = 0;
    }
    DebugLogNextSeq();
}

void DebugLogResetSeq(void) {
    gDebugLogSeq = 0;
}

void DebugLogNextSeq(void) {
    gDebugLogSeq = (gDebugLogSeq + 1) & 0xFF;
}

void VBlankTimerStart(void) {
    gVBlankTimerElapsed = 0;
    gVBlankTimerBase = gVBlankCounter;
}

void VBlankTimerUpdate(void) {
    gVBlankTimerElapsed = (gVBlankCounter - gVBlankTimerBase) & 0xFFFF;
}

u8 SioHasError(void) {
    if (gSioStatus & 0x7F0000) {
        return 1;
    }
    return 0;
}

void SioAutoConnectStart(void) {
    SioReset();
    SioConnectInit(SioAutoConnectOnConnect, 0, 0);
    gSioAutoConnectState = 0;
    gSioAutoConnectTimer = 0;
}

u8 SioAutoConnectUpdate(void) {
    switch (gSioAutoConnectState) {
    case 0:
        SioConnectUpdateAuto();
        break;
    case 1:
        gSioAutoConnectTimer++;
        if (gSioAutoConnectTimer > 4) {
            gSioAutoConnectTimer = 0;
            SioSetLinkCallbacks(SioKeySyncSend, SioKeySyncRecv);
            gSystemFlags |= 1;
            gSystemFlags &= 0xFFEF;
            gSioAutoConnectState++;
        }
        break;
    case 2:
        gSioAutoConnectTimer++;
        if (gSioAutoConnectTimer > 4) {
            gSioSendFrame[1] = 0x2811;

            if (gSioRecvFrame[1][0] == 0x2811 && gSioRecvFrame[1][1] == gSioRecvFrame[1][0]) {
                gSioAutoConnectTimer = 0;
                gSioAutoConnectState++;
            }
        }
        break;
    default:
        return 1;
    }
    return 0;
}

void SioAutoConnectOnConnect(void) {
    gSioAutoConnectState = 1;
}

void SioConnectInit(void (*a)(void), void (*b)(void), u8 c) {
#ifdef VERSION_JP
    gSioConnectId = (c & 0xF) | 0xC0F0;
#else
#ifdef VERSION_EU
    gSioConnectId = (c & 0xF) | 0xC2F0;
#else
    gSioConnectId = (c & 0xF) | 0xC1F0;
#endif
#endif
    gSioConnectAccepted = 0;
    gSioConnected = 0;
    gSioConnectRetries = 0;
    gSioConnectCallback = a;
    gSioCancelCallback = b;
    gSioCancelTimer = 0;
    gSioSendFrame[0] = 0xDDDD;
    gSioSendFrame[1] = 0xDDDD;
}

s32 SioConnectSend(void) {
    u16* param;
    u16* send;
    s32 i;

    if (gSioConnected == 0) {
        if (gSioConnectAccepted == 0) {
            if (GetKeysPressed() & A_BUTTON) {
                gSioSendFrame[0] = 0xFEFE;
                send = gSioSendFrame;
                param = &gSioConnectId;
            } else if (GetKeysPressed() & B_BUTTON) {
                gSioSendFrame[0] = 0xAFAF;
                send = gSioSendFrame;
                param = &gSioConnectId;
            } else {
                send = gSioSendFrame;
                param = &gSioConnectId;

                for (i = 0; i < 4; i++) {
                    gSioSendFrame[i] = 0;
                }
            }
            send[1] = *param;
        } else {
            gSioSendFrame[0] = 0xECEC;
        }
    } else {
        for (i = 0; i < 4; i++) {
            gSioSendFrame[i] = 0;
        }
    }
    return 0;
}
s32 SioConnectRecv(void) {
    u16 c;
    u16 v;

    if (gSioConnected == 0) {
        if (gSioConnectAccepted == 0) {
            if (gSioRecvFrame[0][0] == 0xFEFE || gSioRecvFrame[0][1] == 0xFEFE) {
                if (gSioRecvFrame[1][0] == gSioConnectId && gSioRecvFrame[1][1] == gSioRecvFrame[1][0]) {
                    gSioConnectAccepted = 1;
                }
            } else {
                c = 0xAFAF;
                if (gSioRecvFrame[0][0] == c || gSioRecvFrame[0][1] == c) {
                    SioShutdown();
                    v = gSioPlayerId == 0 ? gSioRecvFrame[0][0] : gSioRecvFrame[0][1];
                    if (v == c) {
                        if (gSioCancelCallback != 0) {
                            gSioCancelCallback();
                        }
                    }
                }
            }
        } else if (gSioRecvFrame[0][0] == 0xECEC) {
            gSioConnected = 1;

            if (gSioConnectCallback != 0) {
                gSioConnectCallback();
            }
        } else {
            gSioConnectRetries++;
            if (gSioConnectRetries > 10) {
                return 1;
            }
        }
    }
    return 0;
}

s32 SioConnectSendAuto(void) {
    s32 i;

    if (gSioConnected == 0) {
        if (gSioConnectAccepted == 0) {
            gSioSendFrame[0] = 0xFEFE;
        } else {
            gSioSendFrame[0] = 0xECEC;
        }
    } else {
        for (i = 0; i < 4; i++) {
            gSioSendFrame[i] = 0;
        }
    }
    return 0;
}

s32 SioConnectRecvAuto(void) {
    if (gSioConnected == 0) {
        if (gSioConnectAccepted == 0) {
            if (gSioRecvFrame[0][0] == 0xFEFE || gSioRecvFrame[0][1] == 0xFEFE) {
                gSioConnectAccepted = 1;
            }
        } else if (gSioRecvFrame[0][0] == 0xECEC) {
            gSioConnected = 1;

            if (gSioConnectCallback != 0) {
                gSioConnectCallback();
            }
        } else {
            gSioConnectRetries++;
            if (gSioConnectRetries > 10) {
                return 1;
            }
        }
    }
    return 0;
}

void SioCommandReset(void) {
    SioCommandClearSend();
    SioCommandClearRecv();
}

void SioCommandClearSend(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        gSioCommandSend[i] = 0;
    }
}

void SioCommandClearRecv(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 2; j++) {
            gSioCommandRecv[i][j] = 0;
        }
    }
}


s32 SioCommandSend(void) {
    gSioCommandSend[0] = 0xACD;
    gSioSendFrame[0] = gSioCommandSend[0];
    gSioSendFrame[1] = gSioCommandSend[1];
    gSioSendFrame[2] = gSioCommandSend[2];
    gSioSendFrame[3] = gSioCommandSend[3];
    SioCommandClearSend();
    return 0;
}

s32 SioCommandRecv(void) {
    if (gSioRecvFrame[0][0] == 0xACD) {
        gSioCommandRecv[0][0] = gSioRecvFrame[0][0];
        gSioCommandRecv[1][0] = gSioRecvFrame[1][0];
        gSioCommandRecv[2][0] = gSioRecvFrame[2][0];
        gSioCommandRecv[3][0] = gSioRecvFrame[3][0];
    }

    if (gSioRecvFrame[0][1] == 0xACD) {
        gSioCommandRecv[0][1] = gSioRecvFrame[0][1];
        gSioCommandRecv[1][1] = gSioRecvFrame[1][1];
        gSioCommandRecv[2][1] = gSioRecvFrame[2][1];
        gSioCommandRecv[3][1] = gSioRecvFrame[3][1];
    }
    return 0;
}

void SioSetLinkCallbacks(s32 (*a)(void), s32 (*b)(void)) {
    s32 i;
    s32 j;
    s32 (**pb)(void);
    u16* p1;
    u16* p2;
    s32 (**pa)(void);

    gSioConnectRetries = 0;
    gSioErrorStatus = 0;
    gSioLinkResult = 0;
    pa = &gSioLinkSendCallback;
    pb = &gSioLinkRecvCallback;
    p1 = &gSioRelayKeysA;
    p2 = &gSioRelayKeysB;

    for (i = 0; i < 4; i++) {
        gSioSendFrame[i] = 0;
    }

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            gSioRecvFrame[j][i] = 0;
        }
    }

    *pa = a;
    *pb = b;
    *p1 = 0;
    *p2 = 0;
}


s32 SioKeySyncSend(void) {
    if (gSioPlayerId == 0) {
        gSioSendFrame[0] = 0xACD;
        gSioSendFrame[1] = GetKeysHeld() & KEYS_MASK;
        gSioSendFrame[2] = gSioRelayKeysA;
        gSioSendFrame[3] = gSioRelayKeysB;
    } else {
        gSioSendFrame[0] = 0xACD;
        gSioSendFrame[1] = GetKeysHeld() & KEYS_MASK;
        gSioSendFrame[2] = 0x1234;
        gSioSendFrame[3] = 0x3456;
    }
    return 0;
}

s32 SioKeySyncRecv(void) {
    if (gSioPlayerId == 0) {
        if (gSioRecvFrame[0][0] == 0xACD && gSioRecvFrame[0][1] == gSioRecvFrame[0][0]) {
            gSioRelayKeysA = gSioRecvFrame[1][0];
            gSioRelayKeysB = gSioRecvFrame[1][1];
            gSioStatus &= ~0x100;
        } else {
            gSioStatus |= 0x100;
        }

        if (gSioRecvFrame[0][0] == 0xACD) {
            SioKeyStateUpdateA(gSioRecvFrame[2][0]);
            SioKeyStateUpdateB(gSioRecvFrame[3][0]);
            gSioStatus &= ~0x100;
        } else {
            gSioStatus |= 0x100;
        }
    } else {
        if (gSioRecvFrame[0][0] == 0xACD) {
            SioKeyStateUpdateA(gSioRecvFrame[2][0]);
            SioKeyStateUpdateB(gSioRecvFrame[3][0]);
            gSioStatus &= ~0x100;
        } else {
            gSioStatus |= 0x100;
        }
    }
    return 0;
}


void SioPrepareDeckExchange(void) {
    Deck* a;
    Deck* b;

    a = CreateLinkSendDeck();
    gSioSendDeck = a;
    b = CreateLinkPartnerDeck();
    gSioRecvDeck = b;
    gLinkDecksAllocated = 1;
    gSioExchangeSeqEnd = 59;
    gSioExchangeSeq = 1;
    gSioHandshakeAck = 0;
    gSioHandshakeDone = 0;
    gSioHandshakeConfirm = 0;
    gUnk_0203C3B8 = 0;
    gSioExchangeSendData = (u16*)gSioSendDeck;
    gSioExchangeRecvData = (u16*)gSioRecvDeck;
}


s32 SioExchangeSend(void) {
    u16 n;

    if (gSioHandshakeDone == 0) {
        if (gSioHandshakeAck == 0) {
            gSioSendFrame[0] = 0x1BFE;
        } else {
            gSioSendFrame[0] = 0xC5A0;
        }
    } else {
        if (gSioExchangeSeq <= 3) {
            gSioSendFrame[0] = 0xACD;
            gSioSendFrame[1] = 0xDDDD;
            gSioSendFrame[2] = 0xDDDD;
            gSioSendFrame[3] = 0xDDDD;
        } else if (gSioExchangeSeq <= gSioExchangeSeqEnd) {
            n = gSioExchangeSeq - 3;
            gSioSendFrame[0] = 0xACD;
            gSioSendFrame[1] = gSioExchangeSeq;
            gSioSendFrame[2] = gSioExchangeSendData[n * 2 - 2];
            gSioSendFrame[3] = gSioExchangeSendData[n * 2 - 1];
        } else {
            gSioSendFrame[0] = 0xACD;
            gSioSendFrame[1] = gSioExchangeSeq;
            gSioSendFrame[2] = 0;
            gSioSendFrame[3] = 0;
        }
        gSioExchangeSeq++;
    }
    return 0;
}


s32 SioExchangeRecv(void) {
    u16 n;

    if (gSioHandshakeDone == 0) {
        if (gSioHandshakeAck == 0) {
            if (gSioRecvFrame[0][0] == 0x1BFE || gSioRecvFrame[0][1] == 0x1BFE) {
                gSioHandshakeAck = 1;
            }
        } else if (gSioRecvFrame[0][0] == 0xC5A0 && gSioRecvFrame[0][1] == gSioRecvFrame[0][0]) {
            gSioHandshakeDone = 1;
            gSioExchangeSeq = 1;
        }
    } else if (gSioPlayerId == 0) {
        if (gSioRecvFrame[1][1] != 0xDDDD && gSioRecvFrame[1][1] > 3) {
            if (gSioRecvFrame[1][1] > gSioExchangeSeqEnd) {
                return 2;
            }
            n = gSioRecvFrame[1][1] - 3;
            gSioExchangeRecvData[n * 2 - 2] = gSioRecvFrame[2][1];
            gSioExchangeRecvData[n * 2 - 1] = gSioRecvFrame[3][1];
        }
    } else {
        if (gSioRecvFrame[1][0] != 0xDDDD && gSioRecvFrame[1][0] > 3) {
            if (gSioRecvFrame[1][0] > gSioExchangeSeqEnd) {
                return 2;
            }
            n = gSioRecvFrame[1][0] - 3;
            gSioExchangeRecvData[n * 2 - 2] = gSioRecvFrame[2][0];
            gSioExchangeRecvData[n * 2 - 1] = gSioRecvFrame[3][0];
        }
    }
    return 0;
}


#ifdef VERSION_EU
void eu_080C24D8(void) {
    s32 i;
    s16 count;

    count = 112;
    for (i = 0; i < count; i++) {
        gSioExchangeRecvData[i] = gSioExchangeSendData[i];
    }
}
#endif

void SioPrepareCharaLinkExchange(void) {
    s32 i;
    CharaLinkData* send;
    u16* recv;

    send = &gCharaLinkSend;
    recv = (u16*)&gCharaLinkRecv;
    send->hp = gGameState.hp;
    gCharaLinkSend.maxHp = gGameState.progression.maxHp;
    gCharaLinkSend.level = gGameState.progression.level;
    gCharaLinkSend.winCount = gSioWinCount;
    gCharaLinkSend.loseCount = gSioLoseCount;
    gCharaLinkSend.ap = gGameState.progression.ap;
    gCharaLinkSend.learnedStocks = gGameState.progression.learnedStocks;
    gCharaLinkSend.learnedStocks2 = gGameState.progression.learnedStocks2;
    gCharaLinkSend.worldFlags = 0;

    for (i = 0; i < 13; i++) {
        if ((u8)(gGameState.floors[i].world - 1) <= 11) {
            gCharaLinkSend.worldFlags |= 1 << gGameState.floors[i].world;
        }
    }

    if (gSioPlayerId == 0) {
        SeedRandom(gFrameCounter & 0xFFFF);
        gCharaLinkSend.seed = GetRandom() % 0xFFFF;
    } else {
        gCharaLinkSend.seed = 0;
    }
    gSioExchangeSeqEnd = 11;
    gSioExchangeSeq = 1;
    gSioHandshakeAck = 0;
    gSioHandshakeDone = 0;
    gSioHandshakeConfirm = 0;
    gSioExchangeSendData = (u16*)send;
    gSioExchangeRecvData = recv;
}

void SioSyncInit(void (*a)(void)) {
    gSioHandshakeAck = 0;
    gSioHandshakeDone = 0;
    gSioHandshakeConfirm = 0;
    gSioConnectCallback = a;
}

s32 SioSyncSend(void) {
    if (gSioHandshakeDone == 0) {
        if (gSioHandshakeAck == 0) {
            gSioSendFrame[0] = 0xFEFE;
        } else if (gSioHandshakeConfirm == 0) {
            gSioSendFrame[0] = 0xECEC;
        } else {
            gSioSendFrame[0] = 0xDF89;
        }
    }
    return 0;
}

s32 SioSyncRecv(void) {
    if (gSioHandshakeDone == 0) {
        if (gSioHandshakeAck == 0) {
            if (gSioRecvFrame[0][0] == 0xFEFE || gSioRecvFrame[0][1] == 0xFEFE) {
                gSioHandshakeAck = 1;
            }
        } else if (gSioRecvFrame[0][0] != 0xDF89) {
            if (gSioPlayerId == 0 && gSioRecvFrame[0][0] == 0xECEC &&
                gSioRecvFrame[0][1] == gSioRecvFrame[0][0]) {
                gSioHandshakeConfirm = 1;
            }
        } else {
            if (gSioConnectCallback != 0) {
                gSioConnectCallback();
            }
            gSioHandshakeDone = 1;
        }
    }
    return 0;
}

#ifdef VERSION_EU
s32 eu_080C273C(void) {
    return 0;
}

s32 eu_080C2740(void) {
    u16 held;
    u16 keys;
    u16 r;

    held = GetKeysHeld() & KEYS_MASK;
    keys = 0;

    if (gRandomPartnerDpadTimer != 0) {
        keys = gRandomPartnerDpad;
        gRandomPartnerDpadTimer--;
    } else {
        gRandomPartnerDpadTimer = GetRandom() % 91 + 30;

        r = GetRandom();
        switch (r & 7) {
        case 0:
            gRandomPartnerDpad = 0x10;
            break;
        case 1:
            gRandomPartnerDpad = 0x20;
            break;
        case 2:
            gRandomPartnerDpad = 0x40;
            break;
        case 3:
            gRandomPartnerDpad = 0x80;
            break;
        case 4:
            gRandomPartnerDpad = 0x50;
            break;
        case 5:
            gRandomPartnerDpad = 0x90;
            break;
        case 6:
            gRandomPartnerDpad = 0x60;
            break;
        case 7:
            gRandomPartnerDpad = 0xA0;
            break;
        }
    }

    if (gRandomPartnerATimer != 0) {
        keys |= 1;
        gRandomPartnerATimer--;
    } else {
        gRandomPartnerATimer = GetRandom() % 61 + 60;
    }

    if ((u16)(GetRandom() % 30) == 0) {
        keys |= 0x200;
    }

    if ((u16)(GetRandom() % 50) == 0) {
        keys |= 0x300;
    }
    SioKeyStateUpdateA(held);
    SioKeyStateUpdateB(keys);
    return 0;
}
#endif

void CharaObjInitDefeat2(CharaObjParam2* param) {
    s32 i;

    gCharaObj = EwramAlloc(sizeof(CharaObj));
    gCharaObj->tilesAddr = param->tilesAddr;
    gCharaObj->tileCount = param->tileCount;
    gCharaObj->paletteAddr = param->paletteAddr;
    gCharaObj->paletteSize = param->paletteSize;
    gCharaObj->x = param->x;
    gCharaObj->y = param->y;
    gCharaObj->z = param->z;
    gCharaObj->fadeLevel = 0;
    gCharaObj->bgFxVz = -76;
    gCharaObj->fadeTick = 0;
    gCharaObj->timer = 0;
    gCharaObj->state = 0;
    gCharaObj->callback = param->callback;
    gCharaObj->tilesAddr4 = 0;
    gCharaObj->tileCount4 = 0;
    gCharaObj->paletteAddr2 = 0;
    gCharaObj->paletteSize2 = 0;
    gCharaObj->prizeObj = param->prizeObj;

    for (i = 0; i < 32; i++) {
        gCharaObj->bankFadeEnabled[i] = 0;
    }
    TaskPoolInit(&gCharaTaskPool, 2);
}

u8 CharaObjUpdateDefeat2(void) {
    CharaPrizeArgs prize;
    MaskFadeArgs fade;

    switch (gCharaObj->state) {
    case 0:
        if (!BgFxIsActive()) {
            gCharaObj->state++;
        }
        break;
    case 1:
        if (++gCharaObj->timer > 59) {
            gCharaObj->timer = 0;
            gCharaObj->state++;
        }
        break;
    case 2:
        CpuSet((void*)0x05000000, gCharaObj->savedPalette, 0x200);
        BgFxStartCharaDefeat(gCharaObj->x, gCharaObj->y + gCharaObj->z - 0x1000);
        m4aSongNumStart(SONG_EF_BOSS_DEAD1);
        gCharaObj->state++;
        break;
    case 3:
        gCharaObj->fadeLevel++;
        FadePaletteToBlack(gCharaObj->savedPalette, (u16*)0x05000000, 320, gCharaObj->fadeLevel);
        if (++gCharaObj->timer > 9) {
            gCharaObj->timer = 0;
            gCharaObj->state++;
        }
        break;
    case 4:
        gCharaObj->fadeLevel = 0;
        CpuSet((void*)0x05000000, gCharaObj->fadedPalette, 0x200);
        gCharaObj->state++;
        break;
    case 5:
        if (++gCharaObj->timer > 89) {
            gCharaObj->timer = 0;
            gCharaObj->state++;
        }
        break;
    case 6:
        if (gCharaObj->fadeTick > 1) {
            gCharaObj->fadeTick = 0;
            gCharaObj->fadeLevel++;
        }
        gCharaObj->fadeTick++;
        if (gCharaObj->paletteSize != 0) {
            FadePaletteToWhite((u16*)gCharaObj->paletteAddr, (u16*)gCharaObj->paletteAddr, gCharaObj->paletteSize, gCharaObj->fadeLevel);
        }
        if (gCharaObj->timer == 20) {
            BgAnimStop();
            m4aSongNumStart(SONG_EF_BOSS_DEAD2);
            fade.tiles = (u8*)gCharaObj->tilesAddr;
            fade.tileCount = gCharaObj->tileCount;
            fade.stepDelay = 1;
            TaskCreate(&gCharaTaskPool, &gTaskDescCharaMaskFade, &fade);
        }
        if (++gCharaObj->timer > 39) {
            gCharaObj->timer = 0;
            m4aSongNumStop(SONG_EF_BOSS_DEAD2);
            gCharaObj->state++;
        }
        break;
    case 7:
        gCharaObj->fadeLevel = 0;
        gCharaObj->fadeTick = 0;
        m4aSongNumStart(SONG_EF_BOSS_DEAD3);
        FadeStartOut(2, 20);
        FadeLock();
        gCharaObj->state++;
        break;
    case 8:
        if (gCharaObj->fadeTick > 1) {
            gCharaObj->fadeTick = 0;
            gCharaObj->fadeLevel++;
        }
        gCharaObj->fadeTick++;
        if (++gCharaObj->timer > 37) {
            gCharaObj->timer = 0;
            gCharaObj->state++;
        }
        break;
    case 9:
        if (++gCharaObj->timer > 20) {
            gCharaObj->timer = 0;
            gCharaObj->state++;
        }
        break;
    case 10:
        gCharaObj->fadeTick = 0;
        if (gCharaObj->callback != 0) {
            gCharaObj->callback();
        }
        gCharaObj->state++;
        break;
    case 11:
        gCharaObj->fadeLevel -= 2;
        FadePaletteToWhite(gCharaObj->fadedPalette, (u16*)0x05000000, 1024, gCharaObj->fadeLevel);
        if (++gCharaObj->timer > 8) {
            gCharaObj->timer = 0;
            gCharaObj->state++;
        }
        break;
    case 12:
        BgFxStartCharaDefeatEnd(gCharaObj->x, gCharaObj->y + gCharaObj->z - 0x1000);
        prize.x = gCharaObj->x;
        prize.y = gCharaObj->y;
        prize.z = gCharaObj->z;
        CreateBossPrizeCardTask(&gBtlWork->taskPools[0], &prize);
        DropBossPrizes(gCharaObj->prizeObj);
        gCharaObj->state++;
        break;
    case 13:
        BgFxAddPosition(76, 0, gCharaObj->bgFxVz);
        if (++gCharaObj->timer > 79) {
            gCharaObj->timer = 0;
            gCharaObj->state++;
        }
        break;
    case 14:
        gCharaObj->bgFxVz = 0;
        gCharaObj->state++;
        break;
    case 15:
        BgFxAddPosition(0, 0, gCharaObj->bgFxVz);
        gCharaObj->bgFxVz -= 25;
        if (++gCharaObj->timer > 39) {
            gCharaObj->timer = 0;
            gCharaObj->state++;
        }
        break;
    case 16:
        BgAnimStop();
        gCharaObj->fadeLevel = 11;
        gCharaObj->state++;
        break;
    case 17:
        gCharaObj->fadeLevel--;
        FadePaletteToBlack(gCharaObj->savedPalette, (u16*)0x05000000, 320, gCharaObj->fadeLevel);
        if (++gCharaObj->timer > 10) {
            gCharaObj->timer = 0;
            CharaObjFree();
            gCharaObj->state++;
        }
        break;
    default:
        return 0;
    }
    TaskPoolUpdate(&gCharaTaskPool);
    TaskPoolDraw(&gCharaTaskPool);
    return 1;
}

void CharaObjFree(void) {
    EwramFree(gCharaObj);
    TaskPoolDestroy(&gCharaTaskPool);
}

void CharaObjInitDefeat(CharaObjParam* param) {
    s32 i;
    u16 idx;

    gCharaObj = EwramAlloc(sizeof(CharaObj));
    gCharaObj->flags = 0;
    gCharaObj->tilesAddr = param->tilesAddr;
    gCharaObj->tileCount = param->tileCount;
    gCharaObj->tilesAddr2 = param->tilesAddr2;
    gCharaObj->tileCount2 = param->tileCount2;
    gCharaObj->tilesAddr3 = param->tilesAddr3;
    gCharaObj->tileCount3 = param->tileCount3;
    gCharaObj->paletteAddr = param->paletteAddr;
    gCharaObj->paletteSize = param->paletteSize;
    gCharaObj->tilesAddr4 = param->tilesAddr4;
    gCharaObj->tileCount4 = param->tileCount4;
    gCharaObj->paletteAddr2 = param->paletteAddr2;
    gCharaObj->paletteSize2 = param->paletteSize2;
    gCharaObj->x = param->x;
    gCharaObj->y = param->y;
    gCharaObj->z = param->z;
    gCharaObj->fadeLevel = 0;
    gCharaObj->bgFxVz = -76;
    gCharaObj->fadeTick = 0;
    gCharaObj->timer = 0;
    gCharaObj->state = 0;
    gCharaObj->callback = param->callback;
    gCharaObj->prizeObj = param->prizeObj;
    gCharaObj->flags = param->flags;

    for (i = 0; i < 10; i++) {
        gCharaObj->bankFadeEnabled[i] = 1;
    }

    for (i = 10; i < 32; i++) {
        gCharaObj->bankFadeEnabled[i] = 0;
    }
    idx = gCharaObj->paletteAddr >> 5;

    if (gCharaObj->paletteSize == 32) {
        gCharaObj->bankFadeEnabled[(s16)idx] = 1;
    }
    TaskPoolInit(&gCharaTaskPool, 4);
}

void CharaObjSetBankFadeEnabled(u16 a, u8 b) {
    if (a <= 31) {
        gCharaObj->bankFadeEnabled[a] = b;
    }
}

u8 CharaObjUpdateDefeat(void) {
    s32 i;
    CharaPrizeArgs prize;
    MaskFadeArgs fade0;
    MaskFadeArgs fade1;
    MaskFadeArgs fade2;
    MaskFadeArgs fade3;

    switch (gCharaObj->state) {
    case 0:
        if (!BgFxIsActive()) {
            gCharaObj->state++;
        }
        break;
    case 1:
        if (++gCharaObj->timer > 59) {
            gCharaObj->timer = 0;
            gCharaObj->state++;
        }
        break;
    case 2:
        BgFxStartCharaDefeat(gCharaObj->x, gCharaObj->y + gCharaObj->z - 0x1000);
        m4aSongNumStart(SONG_EF_BOSS_DEAD1);
        for (i = 0; i < 32; i++) {
            SetPaletteBankFadeEnabled(i, gCharaObj->bankFadeEnabled[i]);
        }
        gCharaObj->state++;
        break;
    case 3:
        CpuSet((void*)0x05000000, gCharaObj->savedPalette, 0x200);
        gCharaObj->state++;
        break;
    case 4:
        gCharaObj->fadeLevel++;
        FadeAllPalettesToBlack(gCharaObj->savedPalette, gCharaObj->fadeLevel);
        if (++gCharaObj->timer > 9) {
            gCharaObj->timer = 0;
            gCharaObj->state++;
        }
        break;
    case 5:
        gCharaObj->fadeLevel = 0;
        gCharaObj->state++;
        break;
    case 6:
        if (++gCharaObj->timer > 89) {
            gCharaObj->timer = 0;
            gCharaObj->state++;
        }
        break;
    case 7:
        if (gCharaObj->fadeTick > 1) {
            gCharaObj->fadeTick = 0;
            gCharaObj->fadeLevel++;
        }
        gCharaObj->fadeTick++;
        if (gCharaObj->timer == 20) {
            BgAnimStop();
            m4aSongNumStart(SONG_EF_BOSS_DEAD2);
            fade0.tiles = (u8*)gCharaObj->tilesAddr;
            fade0.tileCount = gCharaObj->tileCount;
            fade0.stepDelay = 1;
            if (fade0.tileCount != 0) {
                TaskCreate(&gCharaTaskPool, &gTaskDescCharaMaskFade, &fade0);
            }
            fade1.tiles = (u8*)gCharaObj->tilesAddr2;
            fade1.tileCount = gCharaObj->tileCount2;
            fade1.stepDelay = 1;
            if (fade1.tileCount != 0) {
                TaskCreate(&gCharaTaskPool, &gTaskDescCharaMaskFade, &fade1);
            }
            fade2.tiles = (u8*)gCharaObj->tilesAddr3;
            fade2.tileCount = gCharaObj->tileCount3;
            fade2.stepDelay = 1;
            if (fade2.tileCount != 0) {
                TaskCreate(&gCharaTaskPool, &gTaskDescCharaMaskFade, &fade2);
            }
            fade3.tiles = (u8*)gCharaObj->tilesAddr4;
            fade3.tileCount = gCharaObj->tileCount4;
            fade3.stepDelay = 1;
            if (fade3.tileCount != 0) {
                TaskCreate(&gCharaTaskPool, &gTaskDescCharaMaskFade, &fade3);
            }
        }
        if (gCharaObj->paletteSize != 0) {
            FadePaletteToWhite((u16*)gCharaObj->paletteAddr, (u16*)gCharaObj->paletteAddr, gCharaObj->paletteSize, gCharaObj->fadeLevel);
        }
        if (gCharaObj->paletteSize2 != 0) {
            FadePaletteToWhite((u16*)gCharaObj->paletteAddr2, (u16*)gCharaObj->paletteAddr2, gCharaObj->paletteSize2, gCharaObj->fadeLevel);
        }
        if (++gCharaObj->timer > 39) {
            gCharaObj->timer = 0;
            m4aSongNumStop(SONG_EF_BOSS_DEAD2);
            gCharaObj->state++;
        }
        break;
    case 8:
        gCharaObj->fadeLevel = 0;
        gCharaObj->fadeTick = 0;
        m4aSongNumStart(SONG_EF_BOSS_DEAD3);
        FadeStartOut(2, 20);
        FadeLock();
        gCharaObj->state++;
        break;
    case 9:
        if (gCharaObj->fadeTick > 1) {
            gCharaObj->fadeTick = 0;
            gCharaObj->fadeLevel++;
        }
        gCharaObj->fadeTick++;
        if (++gCharaObj->timer > 37) {
            gCharaObj->timer = 0;
            gCharaObj->state++;
        }
        break;
    case 10:
        if (++gCharaObj->timer > 20) {
            gCharaObj->timer = 0;
            gCharaObj->state++;
        }
        break;
    case 11:
        gCharaObj->fadeTick = 0;
        if (gCharaObj->callback != 0) {
            gCharaObj->callback();
        }
        gCharaObj->fadeLevel = 32;
        gCharaObj->state++;
        break;
    case 12:
        FadeAllPalettesToWhite(gCharaObj->savedPalette, gCharaObj->fadeLevel);
        if ((gCharaObj->fadeLevel -= 2) <= 0) {
            gCharaObj->fadeLevel = 0;
            gCharaObj->timer = 0;
            gCharaObj->state++;
        }
        break;
    case 13:
        FadeAllPalettesToBlack(gCharaObj->savedPalette, gCharaObj->fadeLevel);
        if ((gCharaObj->fadeLevel += 2) > 11) {
            gCharaObj->fadeLevel = 12;
            gCharaObj->timer = 0;
            gCharaObj->state++;
        }
        break;
    case 14:
        prize.x = gCharaObj->x;
        prize.y = gCharaObj->y;
        prize.z = gCharaObj->z;
        CreateBossPrizeCardTask(&gBtlWork->taskPools[0], &prize);
        DropBossPrizes(gCharaObj->prizeObj);
        if ((gCharaObj->flags & 1) == 0) {
            BgFxStartCharaDefeatEnd(gCharaObj->x, gCharaObj->y + gCharaObj->z - 0x1000);
            gCharaObj->timer = 0;
            gCharaObj->state++;
        } else {
            gCharaObj->fadeLevel = 12;
            gCharaObj->timer = 0;
            gCharaObj->state = 19;
        }
        break;
    case 15:
        BgFxAddPosition(76, 0, gCharaObj->bgFxVz);
        if (++gCharaObj->timer > 79) {
            gCharaObj->timer = 0;
            gCharaObj->state++;
        }
        break;
    case 16:
        gCharaObj->bgFxVz = 0;
        gCharaObj->state++;
        break;
    case 17:
        BgFxAddPosition(0, 0, gCharaObj->bgFxVz);
        gCharaObj->bgFxVz -= 25;
        if (++gCharaObj->timer > 39) {
            gCharaObj->timer = 0;
            gCharaObj->state++;
        }
        break;
    case 18:
        BgAnimStop();
        gCharaObj->fadeLevel = 12;
        gCharaObj->state++;
        break;
    case 19:
        gCharaObj->fadeLevel--;
        FadeAllPalettesToBlack(gCharaObj->savedPalette, gCharaObj->fadeLevel);
        if (gCharaObj->fadeLevel <= 0) {
            gCharaObj->fadeLevel = 0;
            gCharaObj->timer = 0;
            CharaObjFree();
            gCharaObj->state++;
        }
        break;
    default:
        return 0;
    }
    TaskPoolUpdate(&gCharaTaskPool);
    TaskPoolDraw(&gCharaTaskPool);
    return 1;
}

void RequestTileRowsCopy(u8* src, u8* dst, u16 size, s16 count) {
    s32 i;
    s32 n;

    i = count;
    n = i;
    for (i = 0; i < n; i++) {
        RequestDma3Copy(src + i * 0x400, dst + i * 0x400, size * 32);
    }
}

void RequestMapRowsCopy(u8* src, u8* dst, u16 size, s16 count) {
    s32 i;
    s32 n;

    i = count;
    n = i;
    for (i = 0; i < n; i++) {
        RequestDma3Copy(src + i * 0x40, dst + i * 0x40, size * 2);
    }
}

TaskDesc gTaskDescCharaMaskFade = {
    "task_chara_mask_fade",
    (TaskInitFunc)task_chara_mask_fade_0,
    (TaskUpdateFunc)task_chara_mask_fade_1,
    (TaskDrawFunc)task_chara_mask_fade_2,
    (TaskDestroyFunc)task_chara_mask_fade_3,
    sizeof(MaskFadeWork),
};

TaskDesc gTaskDescChgCardObj = {
    "task_chgCardObj",
    (TaskInitFunc)task_chgCardObj_0,
    (TaskUpdateFunc)task_chgCardObj_1,
    (TaskDrawFunc)task_chgCardObj_2,
    (TaskDestroyFunc)task_chgCardObj_3,
    sizeof(ChgCardObjWork),
};
