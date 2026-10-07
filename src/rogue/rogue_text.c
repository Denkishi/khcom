#include "rogue.h"
#include "card_message_data.h"

// Text is cp1252 with the game's control bytes: \x1F new line, \x1D highlight,
// \x1E plain. Every language slot holds the Italian text.
#define ROGUE_TEXT(name, text) \
    static const u8 name##_It[] = text; \
    static const CardMessageText name = { { (u8*)name##_It, (u8*)name##_It, (u8*)name##_It, (u8*)name##_It, (u8*)name##_It } }

ROGUE_TEXT(sAxel0, "Ehi, Sora. Qui la storia\x1Fnon esiste: solo stanze,\x1Fporte e Heartless.");
ROGUE_TEXT(sAxel1, "Colpisci una porta col\x1F\x1DKeyblade\x1E: si apre da sola.\x1FLe carte mappa non servono.");
ROGUE_TEXT(sAxel2, "Ogni porta d\xE0 su una stanza\x1F" "diversa. Ogni piano finisce\x1F" "con un \x1D" "boss\x1E.");
ROGUE_TEXT(sAxel3, "Le porte restano chiuse\x1F" "finch\xE9 non vinci. Poi scegli\x1Funa \x1Dricompensa\x1E su tre.");
ROGUE_TEXT(sAxel4, "Il \x1Dmazzo\x1E \xE8 pescato a caso.\x1F" "Carte pi\xF9 forti si sbloccano\x1Fpiano dopo piano.");
ROGUE_TEXT(sAxel5, "Le \x1Dtecniche\x1E non ti tolgono\x1Fpi\xF9 la prima carta. Ne impari\x1F" "di nuove salendo di livello.");
ROGUE_TEXT(sAxel6, "I colpi sono pi\xF9 rapidi e\x1F" "dopo ognuno puoi saltare,\x1Fschivare o muoverti subito.");
ROGUE_TEXT(sAxel7, "In aria i colpi ti tengono\x1Fsu. Con \x1D" "Combo+\x1E la combo\x1Fsi allunga.");
ROGUE_TEXT(sAxel8, "Le carte nel mazzo salgono\x1F" "di livello vincendo. Due\x1F" "carte Lv3 si \x1D" "fondono\x1E.");
ROGUE_TEXT(sAxel9, "Pi\xF9 vai avanti, pi\xF9 picchiano.\x1FSe cadi la run finisce, ma i\x1F\x1D" "Frammenti\x1E raccolti restano.");
ROGUE_TEXT(sAxel10, "Batti l'ultimo boss e si apre\x1Fun \x1D" "capitolo\x1E nuovo: altri\x1Fmondi, nemici e carte.");
ROGUE_TEXT(sAxel11, "Riparlami per spendere i\x1F" "Frammenti in potenziamenti.\x1FTieni L per riascoltarmi.");
ROGUE_TEXT(sAxel12, "Got it memorized?");

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
    { AXEL_PORTRAIT, 3, 0, 3, 0, &sAxel9, 0, 0 },
    { AXEL_PORTRAIT, 3, 0, 3, 0, &sAxel10, 0, 0 },
    { AXEL_PORTRAIT, 3, 0, 3, 0, &sAxel11, 0, 0 },
    { AXEL_PORTRAIT, 3, 0, 3, 0, &sAxel12, 0, 0 },
};

const CardMessageDef* RogueCardMessageDef(u16 id) {
    if (id >= ROGUE_MSG_BASE) {
        return &sMessages[id - ROGUE_MSG_BASE];
    }

    return &gCardMessageDefs[id];
}
