#include "rogue.h"
#include "card_message_data.h"

// Text is cp1252 with the game's control bytes: \x1F new line, \x1D highlight,
// \x1E plain. Every language slot holds the Italian text.
#define ROGUE_TEXT(name, text) \
    static const u8 name##_It[] = text; \
    static const CardMessageText name = { { (u8*)name##_It, (u8*)name##_It, (u8*)name##_It, (u8*)name##_It, (u8*)name##_It } }

ROGUE_TEXT(sAxel0, "Ehi, Sora. Qui la storia\x1Fnon esiste: solo stanze,\x1Fporte e Heartless.");
ROGUE_TEXT(sAxel1, "Colpisci una porta col\x1F\x1DKeyblade\x1E: si apre da sola.\x1FLe carte mappa non servono.");
ROGUE_TEXT(sAxel2, "Ogni porta d\xE0 su una stanza\x1F" "diversa. In fondo al piano\x1Fti aspetta un \x1D" "boss\x1E.");
ROGUE_TEXT(sAxel3, "Le porte restano chiuse\x1F" "finch\xE9 non vinci. Poi scegli\x1Funa \x1Dricompensa\x1E su tre.");
ROGUE_TEXT(sAxel4, "Il tuo \x1Dmazzo\x1E \xE8 pescato a\x1F" "caso a ogni run. Guardalo\x1F" "dal menu prima di partire.");
ROGUE_TEXT(sAxel5, "Le \x1Dtecniche\x1E le conosci gi\xE0\x1Ftutte, e non ti tolgono pi\xF9\x1Fla prima carta.");
ROGUE_TEXT(sAxel6, "I colpi si concatenano pi\xF9\x1Fin fretta. Con \x1D" "Combo+\x1E la\x1F" "combo si allunga.");
ROGUE_TEXT(sAxel7, "Pi\xF9 vai avanti, pi\xF9 picchiano.\x1FSe cadi, la run finisce e\x1Fsi ricomincia da capo.");
ROGUE_TEXT(sAxel8, "Got it memorized?");

#define AXEL_PORTRAIT 20

static const CardMessageDef sMessages[ROGUE_MSG_COUNT] = {
    { AXEL_PORTRAIT, 3, 0, 3, 0, &sAxel0, 0, 0 },
    { AXEL_PORTRAIT, 3, 0, 3, 0, &sAxel1, 0, 0 },
    { AXEL_PORTRAIT, 3, 0, 3, 0, &sAxel2, 0, 0 },
    { AXEL_PORTRAIT, 3, 0, 3, 0, &sAxel3, 0, 0 },
    { AXEL_PORTRAIT, 3, 0, 3, 0, &sAxel4, 0, 0 },
    { AXEL_PORTRAIT, 3, 0, 3, 0, &sAxel5, 0, 0 },
    { AXEL_PORTRAIT, 3, 0, 3, 0, &sAxel6, 0, 0 },
    { AXEL_PORTRAIT, 3, 0, 3, 0, &sAxel7, 0, 0 },
    { AXEL_PORTRAIT, 3, 0, 3, 0, &sAxel8, 0, 0 },
};

const CardMessageDef* RogueCardMessageDef(u16 id) {
    if (id >= ROGUE_MSG_BASE) {
        return &sMessages[id - ROGUE_MSG_BASE];
    }

    return &gCardMessageDefs[id];
}
