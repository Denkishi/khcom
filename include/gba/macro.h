#ifndef GUARD_GBA_MACRO_H
#define GUARD_GBA_MACRO_H

#include "gba/io_reg.h"
#include "gba/syscall.h"
#include "types.h"

#define CpuCopy32(src, dest, size) CpuSet(src, dest, ((size) / 4) | CPU_SET_32BIT)
#define CpuFill32(value, dest, size)                                              \
{                                                                                 \
    vu32 tmp = (vu32)(value);                                                     \
    CpuSet((void*)&tmp, dest, CPU_SET_32BIT | CPU_SET_SRC_FIXED | ((size) / 4));  \
}

#define DmaSet(dmaNum, src, dest, control)       \
{                                                \
    vu32* dmaRegs = (vu32*)REG_ADDR_DMA##dmaNum; \
    dmaRegs[0] = (vu32)(src);                    \
    dmaRegs[1] = (vu32)(dest);                   \
    dmaRegs[2] = (vu32)(control);                \
    dmaRegs[2];                                  \
}

#define DmaCopy32(dmaNum, src, dest, size) \
    DmaSet(dmaNum, src, dest, ((DMA_ENABLE | DMA_32BIT) << 16) | ((size) / 4))
#define DmaFill32(dmaNum, value, dest, size)                                                   \
{                                                                                              \
    vu32 tmp = (vu32)(value);                                                                  \
    DmaSet(dmaNum, &tmp, dest, ((DMA_ENABLE | DMA_32BIT | DMA_SRC_FIXED) << 16) | ((size) / 4)); \
}

#endif
