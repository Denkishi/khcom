#ifndef GUARD_TEXT_TYPES_H
#define GUARD_TEXT_TYPES_H

#include "types.h"

#ifdef VERSION_US
typedef u16 TextChar;
#else
typedef u8 TextChar;
#endif

typedef struct LocalizedText {
    const u8* strings[5];
} LocalizedText;

#ifdef VERSION_EU
#define LOCALIZED(name) (&name##ByLanguage)
#else
#define LOCALIZED(name) (name)
#endif

typedef struct TextSlot {
    void* tiles;
    u8 useAlternatePalette;
    s8 advance;
} TextSlot;

#endif
