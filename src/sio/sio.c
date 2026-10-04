#include "macros.h"
#include "intr.h"
#include "sio.h"
#include "gba/io_reg.h"
#include "system_state.h"
#include "gba/macro.h"
#include "gba/syscall.h"
#include "sio_types.h"
#include <stddef.h>
#include "types.h"

u8 gSioLastSendCount EWRAM_COMMON(4);
s16 gSioErrorFrameCount EWRAM_COMMON(4);
u16 gSioRecvFrame[4][2] EWRAM_COMMON(16);
u32 gSioErrorStatus EWRAM_COMMON(4);
s32 (*gSioLinkRecvCallback)() EWRAM_COMMON(8);
u8 gSioPlayerCount EWRAM_COMMON(4);
u8 gSioLastRecvCount EWRAM_COMMON(4);
s32 (*gSioLinkSendCallback)() EWRAM_COMMON(4);
u16 gSioCommandRecv[4][2] EWRAM_COMMON(16);
u32 gSioStatus EWRAM_COMMON(4);
u8 gUnk_02039824 EWRAM_COMMON(4);
u32 gSioPlayerId EWRAM_COMMON(4);
u8 gSioHandshakeRequest EWRAM_COMMON(4);
SioWork gSioWork EWRAM_COMMON(16);
u16 gSioCommandSend[4] EWRAM_COMMON(8);
u8 gSioLinkResult EWRAM_COMMON(4);
u16 gSioSendFrame[4] EWRAM_COMMON(8);

static u8 sSioChecksumReady;
static u16 sSioSavedIme;
static u8 sSioIdleVBlanks;
static u8 sSioSendEmpty;
static u8 sSioPauseTimer;
static u8 sSioPrevPlayerCount;
static s8 sSioAutoStartDone;
static u16 sSioSendNonzero;
static u16 sSioRecvNonzero;

u16 IsVBlankIntrLive() {
    if (REG_IME & 1) {
        if (REG_DISPSTAT & DISPSTAT_VBLANK_INTR) {
            if (REG_IE & INTR_FLAG_VBLANK) {
                if (!(REG_DISPCNT & DISPCNT_FORCED_BLANK)) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

void SetVBlankCallback(IntrFunc fn) {
    gVBlankCallback = fn;

    if (!IsVBlankIntrLive()) {
        *gIntrTableVBlank = fn;
    }
}

void ResetVBlankCallback() {
    *gIntrTableVBlank = VBlankIntr;
    gVBlankCallback = VBlankIntr;
}

void SetVCountCallback(IntrFunc fn) {
    gVCountCallback = fn;

    if (!IsVBlankIntrLive()) {
        *gIntrTableVCount = fn;
    }
}

void ResetVCountCallback() {
    *gIntrTableVCount = VCountIntrDummy;
    gVCountCallback = VCountIntrDummy;
}

void SetHBlankCallback(IntrFunc fn) {
    gHBlankCallback = fn;

    if (!IsVBlankIntrLive()) {
        *gIntrTableHBlank = fn;
    }
}

void ResetHBlankCallback() {
    *gIntrTableHBlank = HBlankIntrDummy;
    gHBlankCallback = HBlankIntrDummy;
}

void SetSerialCallback(IntrFunc fn) {
    *gIntrTableSerial = fn;
}

void ResetSerialCallback() {
    *gIntrTableSerial = SerialIntrDummy;
}

void SetTimer3Callback(IntrFunc fn) {
    *gIntrTableTimer3 = fn;
}

void ResetTimer3Callback() {
    *gIntrTableTimer3 = SerialIntrDummy;
}

void SioInit() {
    u16* p;
    u16 ime;

    p = &sSioSavedIme;
    ime = REG_IME;
    REG_IME = 0;
    REG_IE &= ~(INTR_FLAG_TIMER3 | INTR_FLAG_SERIAL);
    REG_IME = ime;
    REG_RCNT = 0;
    REG_SIOCNT = SIO_MULTI_MODE;
    REG_SIOCNT |= (SIO_INTR_ENABLE | SIO_115200_BPS);
    *p = REG_IME;
    SetVBlankCallback(VBlankIntrSio);
    SetSerialCallback(SioSerialIntr);
    SetTimer3Callback(SioTimer3Intr);
    REG_IME = 0;
    REG_IE |= INTR_FLAG_SERIAL;
    REG_IME = *p;
    REG_SIOMLT_SEND = 0;
    *(u64*)REG_ADDR_SIOMULTI0 = 0;
    CpuFill32(0, &gSioWork, sizeof(SioWork));
    sSioIdleVBlanks = 0;
    sSioSendEmpty = 0;
    sSioPrevPlayerCount = 0;
    gSioLastSendCount = 0;
    gSioLastRecvCount = 0;
    gSioStatus = 0;
    gSioErrorFrameCount = 0;
    gSioErrorStatus = 0;
    gSioPlayerId = 0;
    gSioPlayerCount = 0;
    gUnk_02039824 = 0;
    gSioHandshakeRequest = 0;
    gSioLinkResult = 0;
    sSioAutoStartDone = 0;
    sSioChecksumReady = 0;
    sSioSendNonzero = 0;
    sSioRecvNonzero = 0;
    gSioLinkSendCallback = NULL;
    gSioLinkRecvCallback = NULL;
}

void SioReset() {
    SioInit();
    SioStop();
}

void func_08006E70() {
}

void SioStop() {
    sSioSavedIme = REG_IME;
    REG_IME = 0;
    REG_IE &= ~(INTR_FLAG_TIMER3 | INTR_FLAG_SERIAL);
    REG_IME = sSioSavedIme;
    REG_SIOCNT = 0;
    REG_TM3CNT_H = 0;
    REG_IF = (INTR_FLAG_TIMER3 | INTR_FLAG_SERIAL);
    CpuFill32(0, &gSioWork, sizeof(SioWork));
}

u32 SioRunStateMachine(u8* a, u16* b, u16 (*c)[2]) {
    u32 r;
    u32 v;
    u32 w;
    u32 t0, t1, t2, t3, t4, t5;

    switch (gSioWork.state) {
    case 0:
        SioStop();
        gSioWork.state = 1;
        break;
    case 1:
        SioInit();
        gSioWork.state = 2;
        break;
    case 2:
        switch (*a) {
        default:
            SioCheckParent();

            if (sSioAutoStartDone == 0) {
                if (gSioWork.isParent != 0 && gSioWork.playerCount == 2) {
                    gSioWork.startPending = 1;
                    sSioAutoStartDone = -1;
                }
            }

            break;
        case 1:
            if (gSioWork.isParent != 0 && gSioWork.playerCount == 2) {
                gSioWork.startPending = 1;
            }

            sSioAutoStartDone = -1;
            break;
        case 2:
            gSioWork.state = 0;
            REG_SIOMLT_SEND = 0;
            break;
        }

        break;
    case 3:
        SioInitTimer();
        gSioWork.state = 4;
    case 4:
        if (!gSioWork.paused) {
            SioQueueSendFrame(b);
        }

        SioReadRecvFrame(c);
        break;
    }

    *a = 0;
    r = gSioWork.playerId | (gSioWork.playerCount << 2);

    if (gSioWork.isParent == 8) {
        r |= 0x20;
    }

    t0 = gSioWork.recvEmpty << 8;
    t1 = gSioWork.unk_11 << 9;
    t2 = gSioWork.hardwareError << 16;
    t3 = gSioWork.checksumError << 17;
    t4 = gSioWork.queueFull << 18;
    t5 = gSioWork.timeout << 20;

    if (gSioWork.state == 4) {
        v = r | 0x40 | t0 | t1 | t2 | t3 | t4 | t5;
    } else {
        v = r | t0 | t1 | t2 | t3 | t4 | t5;
    }

    w = v;

    if (gSioWork.playerId > 1) {
        w |= 0x400000;
    }

    return w;
}

u32 SioTransferFrames(u8* a, u16* b, u16 (*c)[2]) {
    u32 r;
    u32 v;
    u32 w;
    u32 t0, t1, t2, t3, t4, t5;

    if (gSioWork.state == 4) {
        if (!gSioWork.paused) {
            SioQueueSendFrame(b);
        }

        SioReadRecvFrame(c);
    }

    r = gSioWork.playerId | (gSioWork.playerCount << 2);

    if (gSioWork.isParent == 8) {
        r |= 0x20;
    }

    t0 = gSioWork.recvEmpty << 8;
    t1 = gSioWork.unk_11 << 9;
    t2 = gSioWork.hardwareError << 16;
    t3 = gSioWork.checksumError << 17;
    t4 = gSioWork.queueFull << 18;
    t5 = gSioWork.timeout << 20;

    if (gSioWork.state == 4) {
        v = r | 0x40 | t0 | t1 | t2 | t3 | t4 | t5;
    } else {
        v = r | t0 | t1 | t2 | t3 | t4 | t5;
    }

    w = v;

    if (gSioWork.playerId > 1) {
        w |= 0x400000;
    }

    return w;
}

void SioCheckParent() {
    if (((*(vu32*)REG_ADDR_SIOCNT) & (SIO_MULTI_SI | SIO_MULTI_SD)) == SIO_MULTI_SD && gSioWork.playerId == 0) {
        gSioWork.isParent = 8;
    } else {
        gSioWork.isParent = 0;
    }
}

void SioInitTimer() {
    if (gSioWork.isParent != 0) {
        REG_TM3CNT_L = 0xFF2D;
        REG_TM3CNT_H = (TIMER_INTR_ENABLE | TIMER_64CLK);
        sSioSavedIme = REG_IME;
        REG_IME = 0;
        REG_IE |= INTR_FLAG_TIMER3;
        REG_IME = sSioSavedIme;
    }
}

void SioQueueSendFrame(u16* frame) {
    u8 idx;
    u8 i;

    sSioSavedIme = REG_IME;
    REG_IME = 0;

    if (gSioWork.sendCount < 32) {
        idx = gSioWork.sendCount + gSioWork.sendReadIdx;

        if (idx > 31) {
            idx -= 32;
        }

        for (i = 0; i < 4; i++) {
            sSioSendNonzero |= *frame;
            gSioWork.sendBuf[i][idx] = *frame;
            *frame = 0;
            frame++;
        }
    } else {
        gSioWork.queueFull |= 1;
    }

    if (sSioSendNonzero != 0) {
        gSioWork.sendCount++;
        sSioSendNonzero = 0;
    }

    REG_IME = sSioSavedIme;
    gSioLastSendCount = gSioWork.sendCount;
}

void SioReadRecvFrame(u16 (*frame)[2]) {
    u8 i;
    u8 j;

    sSioSavedIme = REG_IME;
    REG_IME = 0;

    if (gSioWork.recvCount == 0) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < gSioWork.playerCount; j++) {
                frame[i][j] = 0;
            }
        }

        gSioWork.recvEmpty = 1;
    } else {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < gSioWork.playerCount; j++) {
                frame[i][j] = gSioWork.recvBuf[j][i][gSioWork.recvReadIdx];
            }
        }

        gSioWork.recvCount--;
        gSioWork.recvReadIdx++;

        if (gSioWork.recvReadIdx > 31) {
            gSioWork.recvReadIdx = 0;
        }

        gSioWork.recvEmpty = 0;
    }

    REG_IME = sSioSavedIme;
}

void SioVBlankUpdate() {
    if (gSioWork.paused) {
        sSioPauseTimer--;

        if (sSioPauseTimer != 0) {
            return;
        }

        gSioWork.paused = 0;
    }

    if (gSioWork.isParent != 0) {
        if (gSioWork.state == 2) {
            SioStartTransfer();
        } else if (gSioWork.state == 4) {
            if (gSioWork.transferCount <= 4) {
                if (gSioWork.hardwareError != 0) {
                    SioStartTransfer();
                } else {
                    gSioWork.timeout = 1;
                }
            } else if (gSioWork.timeout == 0) {
                gSioWork.transferCount = 0;
                SioStartTransfer();
            }
        }
    } else if (gSioWork.state == 4 || gSioWork.state == 2) {
        sSioIdleVBlanks++;

        if (sSioIdleVBlanks > 6) {
            if (gSioWork.state == 4) {
                gSioWork.timeout = 2;
            }

            if (gSioWork.state == 2) {
                gSioWork.playerId = 0;
                gSioWork.playerCount = 0;
                gSioWork.unk_11 = 0;
            }
        }
    }
}

void SioTimer3Intr() {
    SioStopTimer();
    SioStartTransfer();
}

void SioSerialIntr() {
    u32 cnt;

    cnt = (*(vu32*)REG_ADDR_SIOCNT);
    gSioWork.playerId = (cnt << 26) >> 30;

    switch (gSioWork.state) {
    case 4:
        if (cnt & SIO_ERROR) {
            gSioWork.hardwareError = 1;
        }

        SioRecvWord();
        SioSendWord();
        SioFinishTransfer();
        break;
    case 2:
        if (SioHandshake()) {
            if (gSioWork.isParent != 0) {
                gSioWork.state = 3;
                gSioWork.transferCount = 4;
            } else {
                gSioWork.state = 4;
            }
        }

        break;
    }

    gSioWork.transferCount++;
    sSioIdleVBlanks = 0;

    if (gSioWork.transferCount == 4) {
        gSioLastRecvCount = gSioWork.recvCount;
    }
}

void SioStartTransfer() {
    REG_SIOCNT |= SIO_START;
}

u8 SioHandshake() {
    u8 count;
    u16 min;
    u8 i;

    count = 0;
    min = 0xFFFF;

    if (gSioWork.startPending == 1) {
        REG_SIOMLT_SEND = 0x8FFF;
    } else {
        REG_SIOMLT_SEND = 0xD5E0;
    }

    gSioWork.startPending = 0;
    *(u64*)gSioWork.recv = *(u64*)REG_ADDR_SIOMULTI0;

    for (i = 0; i < 2; i++) {
        if ((gSioWork.recv[i] & ~3) == 0xD5E0 || gSioWork.recv[i] == 0x8FFF) {
            count++;

            if (min > gSioWork.recv[i] && gSioWork.recv[i] != 0) {
                min = gSioWork.recv[i];
            }
        } else if (gSioWork.recv[i] == 0xFFFF) {
            if (i == gSioWork.playerId) {
                count = 0;
            }
        } else {
            count = 0;
            break;
        }
    }

    gSioWork.playerCount = count;

    if (gSioWork.playerCount == 2) {
        if (gSioWork.playerCount == sSioPrevPlayerCount && gSioWork.recv[0] == 0x8FFF) {
            return 1;
        }

        if (gSioWork.playerCount == 2) {
            gSioWork.unk_11 = (min & 3) + 1;
        } else {
            gSioWork.unk_11 = 0;
        }
    } else {
        gSioWork.unk_11 = 0;
    }

    sSioPrevPlayerCount = gSioWork.playerCount;
    return 0;
}

void SioRecvWord() {
    u16 buf[4];
    u8 i;
    u8 idx;

    *(u64*)buf = *(u64*)REG_ADDR_SIOMULTI0;

    if (gSioWork.sendWordIdx == 0) {
        for (i = 0; i < gSioWork.playerCount; i++) {
            if (gSioWork.checksum != buf[i] && sSioChecksumReady) {
                gSioWork.checksumError = 1;
            }
        }

        gSioWork.checksum = 0;
        sSioChecksumReady = 1;
    } else {
        idx = gSioWork.recvReadIdx + gSioWork.recvCount;

        if (idx > 31) {
            idx -= 32;
        }

        if (gSioWork.recvCount < 32) {
            for (i = 0; i < gSioWork.playerCount; i++) {
                gSioWork.checksum += buf[i];
                sSioRecvNonzero |= buf[i];
                gSioWork.recvBuf[i][gSioWork.recvWordIdx][idx] = buf[i];

                if (gSioWork.sendWordIdx == 1 && !gSioWork.paused && (buf[i] & 0x1000)) {
                    gSioWork.paused = 1;
                    sSioPauseTimer = 5;
                }
            }
        } else {
            gSioWork.queueFull |= 2;
        }

        gSioWork.recvWordIdx++;

        if (gSioWork.recvWordIdx == 4 && sSioRecvNonzero != 0) {
            gSioWork.recvCount++;
            sSioRecvNonzero = 0;
        }
    }
}

void SioSendWord() {
    if (gSioWork.sendWordIdx == 4) {
        REG_SIOMLT_SEND = gSioWork.checksum;

        if (!sSioSendEmpty) {
            gSioWork.sendCount--;
            gSioWork.sendReadIdx++;

            if (gSioWork.sendReadIdx > 31) {
                gSioWork.sendReadIdx = 0;
            }
        } else {
            sSioSendEmpty = 0;
        }
    } else {
        if (gSioWork.sendWordIdx == 0 && gSioWork.sendCount == 0) {
            sSioSendEmpty = 1;
        }

        if (sSioSendEmpty) {
            REG_SIOMLT_SEND = 0;
        } else {
            REG_SIOMLT_SEND = gSioWork.sendBuf[gSioWork.sendWordIdx][gSioWork.sendReadIdx];
        }

        if (!gSioWork.paused && gSioWork.sendWordIdx == 0 && gSioWork.recvCount > 3) {
            REG_SIOMLT_SEND |= 0x1000;
        }

        gSioWork.sendWordIdx++;
    }
}

void SioStopTimer() {
    if (gSioWork.isParent != 0) {
        REG_TM3CNT_H &= ~TIMER_ENABLE;
        REG_TM3CNT_L = 0xFF2D;
    }
}

void SioFinishTransfer() {
    if (gSioWork.recvWordIdx == 4) {
        gSioWork.sendWordIdx = 0;
        gSioWork.recvWordIdx = 0;
    } else if (gSioWork.isParent != 0) {
        REG_TM3CNT_H |= TIMER_ENABLE;
    }
}

void SioResetSendQueue() {
    u8 i;
    u8 j;

    gSioWork.sendCount = 0;
    gSioWork.sendReadIdx = 0;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 32; j++) {
            gSioWork.sendBuf[i][j] = 0xEFFF;
        }
    }
}

void SioResetRecvQueue() {
    u8 i;
    u8 j;
    u8 k;

    gSioWork.recvCount = 0;
    gSioWork.recvReadIdx = 0;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            for (k = 0; k < 32; k++) {
                gSioWork.recvBuf[i][j][k] = 0xEFFF;
            }
        }
    }
}

void SioClearRegs() {
    REG_RCNT = 0;
    REG_SIOCNT = 0;
    REG_SIODATA8 = 0;
    *(vu16*)REG_ADDR_SIODATA32 = 0;
    REG_SIOMLT_SEND = 0;
    REG_SIOMLT_RECV = 0;
    REG_SIOMULTI0 = 0;
    REG_SIOMULTI1 = 0;
    REG_SIOMULTI2 = 0;
    REG_SIOMULTI3 = 0;
}

void SioShutdown() {
    SioClearRegs();
    REG_IME = 0;
    ResetVBlankCallback();
    ResetSerialCallback();
    ResetTimer3Callback();
    REG_IE = (INTR_FLAG_VBLANK | INTR_FLAG_GAMEPAK);
    REG_DISPSTAT = DISPSTAT_VBLANK_INTR;
    REG_IME = 1;
    SioStop();
}

u8 SioIsConnected() {
    if (gSioWork.state == 4) {
        return 1;
    }

    return 0;
}
