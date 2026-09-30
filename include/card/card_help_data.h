#ifndef GUARD_CARD_HELP_DATA_H
#define GUARD_CARD_HELP_DATA_H

#include "text_types.h"

#ifdef VERSION_US
typedef u16 CardHelpText;
#elif defined(VERSION_JP)
typedef u8 CardHelpText;
#else
typedef LocalizedText CardHelpText;
#endif

typedef struct CardHelpDef {
    CardHelpText** texts;
    u8 textCount;
    u8 unk_05[3];
} CardHelpDef;

#endif
