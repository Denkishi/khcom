#ifndef GUARD_CARD_MESSAGE_DATA_H
#define GUARD_CARD_MESSAGE_DATA_H

#include "text_types.h"
#include "types.h"

#ifdef VERSION_US
typedef u16 CardMessageText;
#elif defined(VERSION_JP)
typedef u8 CardMessageText;
#else
typedef LocalizedText CardMessageText;
#endif

enum CardMessageFlag {
    CARD_MSG_FLAG_CHOICE_AT_END = 0x1,
    CARD_MSG_FLAG_CHOICE_WINDOW = 0x2,
    CARD_MSG_FLAG_ALT_HIGHLIGHT = 0x4
};

typedef struct CardMessageDef {
    s32 portraitId;
    u32 positionIndex;
    u16 expressionId;
    u8 charDelay;
    const CardMessageText* text;
    u16 flags;
} CardMessageDef;

extern CardMessageDef gCardMessageDefs[];

#endif
