#ifndef GUARD_SIO_H
#define GUARD_SIO_H

#include "display.h"
#include "sio_api.h"
#include "types.h"
#include "sio_types.h"
#include "gba/syscall.h"
#include "intr.h"
#include "engine.h"
#include "gba/io_reg.h"

u16 IsVBlankIntrLive(void);
void SioInit(void);
void func_08006E70(void);
void SioStop(void);
void SioCheckParent(void);
void SioInitTimer(void);
void SioQueueSendFrame(u16* frame);
void SioReadRecvFrame(u16 (*frame)[2]);
void SioVBlankUpdate(void);
void SioTimer3Intr(void);
void SioSerialIntr(void);
void SioStartTransfer(void);
u8 SioHandshake(void);
void SioRecvWord(void);
void SioSendWord(void);
void SioStopTimer(void);
void SioFinishTransfer(void);
void SioResetSendQueue(void);
void SioResetRecvQueue(void);
void SioClearRegs(void);

void VBlankIntr(void);
void HBlankIntrDummy(void);
void VCountIntrDummy(void);
void SerialIntrDummy(void);
void VBlankIntrSio(void);

#endif /* GUARD_SIO_H */
