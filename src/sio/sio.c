#include "macros.h"
#include "display.h"
#include "intr.h"
#include "sio_api.h"
#include "sio.h"
#include "gba/io_reg.h"
#include "system_state.h"

u8 gSioLastSendCount EWRAM_COMMON(4);
s16 gSioErrorFrameCount EWRAM_COMMON(4);
u16 gSioRecvFrame[4][2] EWRAM_COMMON(16);
u32 gSioErrorStatus EWRAM_COMMON(4);
s32 (*gSioLinkRecvCallback)(void) EWRAM_COMMON(8);
u8 gSioPlayerCount EWRAM_COMMON(4);
u8 gSioLastRecvCount EWRAM_COMMON(4);
s32 (*gSioLinkSendCallback)(void) EWRAM_COMMON(4);
u16 gSioCommandRecv[4][2] EWRAM_COMMON(16);
u32 gSioStatus EWRAM_COMMON(4);
u8 gUnk_02039824 EWRAM_COMMON(4);
u32 gSioPlayerId EWRAM_COMMON(4);
u8 gSioHandshakeRequest EWRAM_COMMON(4);
SioWork gSioWork EWRAM_COMMON(16);
u16 gSioCommandSend[4] EWRAM_COMMON(8);
u8 gSioLinkResult EWRAM_COMMON(4);
u16 gSioSendFrame[4] EWRAM_COMMON(8);

u8 gSioChecksumReady;
u16 gSioSavedIme;
u8 gSioIdleVBlanks;
u8 gSioSendEmpty;
u8 gSioPauseTimer;
u8 gSioPrevPlayerCount;
s8 gSioAutoStartDone;
u16 gSioSendNonzero;
u16 gSioRecvNonzero;

u16 IsVBlankIntrLive(void) {
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

void ResetVBlankCallback(void) {
    *gIntrTableVBlank = VBlankIntr;
    gVBlankCallback = VBlankIntr;
}

void SetVCountCallback(IntrFunc fn) {
    gVCountCallback = fn;

    if (!IsVBlankIntrLive()) {
        *gIntrTableVCount = fn;
    }
}

void ResetVCountCallback(void) {
    *gIntrTableVCount = VCountIntrDummy;
    gVCountCallback = VCountIntrDummy;
}

void SetHBlankCallback(IntrFunc fn) {
    gHBlankCallback = fn;

    if (!IsVBlankIntrLive()) {
        *gIntrTableHBlank = fn;
    }
}

void ResetHBlankCallback(void) {
    *gIntrTableHBlank = HBlankIntrDummy;
    gHBlankCallback = HBlankIntrDummy;
}

void SetSerialCallback(IntrFunc fn) {
    *gIntrTableSerial = fn;
}

void ResetSerialCallback(void) {
    *gIntrTableSerial = SerialIntrDummy;
}

void SetTimer3Callback(IntrFunc fn) {
    *gIntrTableTimer3 = fn;
}

void ResetTimer3Callback(void) {
    *gIntrTableTimer3 = SerialIntrDummy;
}

void SioInit(void) {
    u16* p;
    u16 ime;
    u32 zero;

    p = &gSioSavedIme;
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
    zero = 0;
    CpuSet(&zero, &gSioWork, (sizeof(SioWork) / 4) | CPU_SET_SRC_FIXED | CPU_SET_32BIT);
    gSioIdleVBlanks = 0;
    gSioSendEmpty = 0;
    gSioPrevPlayerCount = 0;
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
    gSioAutoStartDone = 0;
    gSioChecksumReady = 0;
    gSioSendNonzero = 0;
    gSioRecvNonzero = 0;
    gSioLinkSendCallback = 0;
    gSioLinkRecvCallback = 0;
}

void SioReset(void) {
    SioInit();
    SioStop();
}

void func_08006E70(void) {
}

void SioStop(void) {
    u32 zero;

    gSioSavedIme = REG_IME;
    REG_IME = 0;
    REG_IE &= ~(INTR_FLAG_TIMER3 | INTR_FLAG_SERIAL);
    REG_IME = gSioSavedIme;
    REG_SIOCNT = 0;
    REG_TM3CNT_H = 0;
    REG_IF = (INTR_FLAG_TIMER3 | INTR_FLAG_SERIAL);
    zero = 0;
    CpuSet(&zero, &gSioWork, (sizeof(SioWork) / 4) | CPU_SET_SRC_FIXED | CPU_SET_32BIT);
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

            if (gSioAutoStartDone == 0) {
                if (gSioWork.isParent != 0 && gSioWork.playerCount == 2) {
                    gSioWork.startPending = 1;
                    gSioAutoStartDone = -1;
                }
            }

            break;
        case 1:
            if (gSioWork.isParent != 0 && gSioWork.playerCount == 2) {
                gSioWork.startPending = 1;
            }

            gSioAutoStartDone = -1;
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
        if (gSioWork.paused == 0) {
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
        if (gSioWork.paused == 0) {
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

void SioCheckParent(void) {
    if (((*(vu32*)REG_ADDR_SIOCNT) & (SIO_MULTI_SI | SIO_MULTI_SD)) == SIO_MULTI_SD && gSioWork.playerId == 0) {
        gSioWork.isParent = 8;
    } else {
        gSioWork.isParent = 0;
    }
}

void SioInitTimer(void) {
    if (gSioWork.isParent != 0) {
        REG_TM3CNT_L = 0xFF2D;
        REG_TM3CNT_H = (TIMER_INTR_ENABLE | TIMER_64CLK);
        gSioSavedIme = REG_IME;
        REG_IME = 0;
        REG_IE |= INTR_FLAG_TIMER3;
        REG_IME = gSioSavedIme;
    }
}

void SioQueueSendFrame(u16* frame) {
    u8 idx;
    u8 i;

    gSioSavedIme = REG_IME;
    REG_IME = 0;

    if (gSioWork.sendCount < 32) {
        idx = gSioWork.sendCount + gSioWork.sendReadIdx;

        if (idx > 31) {
            idx -= 32;
        }

        for (i = 0; i < 4; i++) {
            gSioSendNonzero |= *frame;
            gSioWork.sendBuf[i][idx] = *frame;
            *frame = 0;
            frame++;
        }
    } else {
        gSioWork.queueFull |= 1;
    }

    if (gSioSendNonzero != 0) {
        gSioWork.sendCount++;
        gSioSendNonzero = 0;
    }

    REG_IME = gSioSavedIme;
    gSioLastSendCount = gSioWork.sendCount;
}

void SioReadRecvFrame(u16 (*frame)[2]) {
    u8 i;
    u8 j;

    gSioSavedIme = REG_IME;
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

    REG_IME = gSioSavedIme;
}

void SioVBlankUpdate(void) {
    if (gSioWork.paused != 0) {
        gSioPauseTimer--;

        if (gSioPauseTimer != 0) {
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
        gSioIdleVBlanks++;

        if (gSioIdleVBlanks > 6) {
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

void SioTimer3Intr(void) {
    SioStopTimer();
    SioStartTransfer();
}

void SioSerialIntr(void) {
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
    gSioIdleVBlanks = 0;

    if (gSioWork.transferCount == 4) {
        gSioLastRecvCount = gSioWork.recvCount;
    }
}

void SioStartTransfer(void) {
    REG_SIOCNT |= SIO_START;
}

u8 SioHandshake(void) {
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
        if (gSioWork.playerCount == gSioPrevPlayerCount && gSioWork.recv[0] == 0x8FFF) {
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

    gSioPrevPlayerCount = gSioWork.playerCount;
    return 0;
}

void SioRecvWord(void) {
    u16 buf[4];
    u8 i;
    u8 idx;

    *(u64*)buf = *(u64*)REG_ADDR_SIOMULTI0;

    if (gSioWork.sendWordIdx == 0) {
        for (i = 0; i < gSioWork.playerCount; i++) {
            if (gSioWork.checksum != buf[i] && gSioChecksumReady != 0) {
                gSioWork.checksumError = 1;
            }
        }

        gSioWork.checksum = 0;
        gSioChecksumReady = 1;
    } else {
        idx = gSioWork.recvReadIdx + gSioWork.recvCount;

        if (idx > 31) {
            idx -= 32;
        }

        if (gSioWork.recvCount < 32) {
            for (i = 0; i < gSioWork.playerCount; i++) {
                gSioWork.checksum += buf[i];
                gSioRecvNonzero |= buf[i];
                gSioWork.recvBuf[i][gSioWork.recvWordIdx][idx] = buf[i];

                if (gSioWork.sendWordIdx == 1 && gSioWork.paused == 0 && (buf[i] & 0x1000)) {
                    gSioWork.paused = 1;
                    gSioPauseTimer = 5;
                }
            }
        } else {
            gSioWork.queueFull |= 2;
        }

        gSioWork.recvWordIdx++;

        if (gSioWork.recvWordIdx == 4 && gSioRecvNonzero != 0) {
            gSioWork.recvCount++;
            gSioRecvNonzero = 0;
        }
    }
}

void SioSendWord(void) {
    if (gSioWork.sendWordIdx == 4) {
        REG_SIOMLT_SEND = gSioWork.checksum;

        if (gSioSendEmpty == 0) {
            gSioWork.sendCount--;
            gSioWork.sendReadIdx++;

            if (gSioWork.sendReadIdx > 31) {
                gSioWork.sendReadIdx = 0;
            }
        } else {
            gSioSendEmpty = 0;
        }
    } else {
        if (gSioWork.sendWordIdx == 0 && gSioWork.sendCount == 0) {
            gSioSendEmpty = 1;
        }

        if (gSioSendEmpty != 0) {
            REG_SIOMLT_SEND = 0;
        } else {
            REG_SIOMLT_SEND = gSioWork.sendBuf[gSioWork.sendWordIdx][gSioWork.sendReadIdx];
        }

        if (gSioWork.paused == 0 && gSioWork.sendWordIdx == 0 && gSioWork.recvCount > 3) {
            REG_SIOMLT_SEND |= 0x1000;
        }

        gSioWork.sendWordIdx++;
    }
}

void SioStopTimer(void) {
    if (gSioWork.isParent != 0) {
        REG_TM3CNT_H &= ~TIMER_ENABLE;
        REG_TM3CNT_L = 0xFF2D;
    }
}

void SioFinishTransfer(void) {
    if (gSioWork.recvWordIdx == 4) {
        gSioWork.sendWordIdx = 0;
        gSioWork.recvWordIdx = 0;
    } else if (gSioWork.isParent != 0) {
        REG_TM3CNT_H |= TIMER_ENABLE;
    }
}

void SioResetSendQueue(void) {
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

void SioResetRecvQueue(void) {
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

void SioClearRegs(void) {
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

void SioShutdown(void) {
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

u8 SioIsConnected(void) {
    if (gSioWork.state == 4) {
        return 1;
    }

    return 0;
}
