#ifndef GUARD_SIO_API_H
#define GUARD_SIO_API_H

#include "types.h"
#include "sio_types.h"

void SioReset();
u32 SioRunStateMachine(u8* a, u16* b, u16 (*c)[2]);
u32 SioTransferFrames(u8* a, u16* b, u16 (*c)[2]);
void SioShutdown();
u8 SioIsConnected();

extern u8 gSioLastSendCount;
extern s16 gSioErrorFrameCount;
extern u16 gSioRecvFrame[4][2];
extern u32 gSioErrorStatus;
extern s32 (*gSioLinkRecvCallback)();
extern u8 gSioPlayerCount;
extern u8 gSioLastRecvCount;
extern s32 (*gSioLinkSendCallback)();
extern u16 gSioCommandRecv[4][2];
extern u32 gSioStatus;
extern u8 gUnk_02039824;
extern u32 gSioPlayerId;
extern u8 gSioHandshakeRequest;
extern SioWork gSioWork;
extern u16 gSioCommandSend[4];
extern u8 gSioLinkResult;
extern u16 gSioSendFrame[4];

#endif
