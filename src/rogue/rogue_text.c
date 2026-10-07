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
ROGUE_TEXT(sAxel12, "Nel menu, Grillario mostra\x1Fla tua run e Salvarapido\x1Fla mette in pausa.");
ROGUE_TEXT(sAxel13, "Got it memorized?");

// Two pages for each event, in the order of the ROGUE_EVENT_ ids.
ROGUE_TEXT(sBelle0, "Sora! Hai l'aria di chi ne\x1Fha passate tante. Siediti,\x1Flascia che mi occupi di te.");
ROGUE_TEXT(sBelle1, "Dimmi tu di cosa hai\x1Fpi\xF9 bisogno.");
ROGUE_TEXT(sLeon0, "Sei ancora in piedi. Bene.\x1FMa la forza vera ha\x1Fsempre un prezzo.");
ROGUE_TEXT(sLeon1, "Decidi tu quanto sei\x1F" "disposto a pagare.");
ROGUE_TEXT(sYuffie0, "Ehi, Sora! Guarda cos'ha\x1F\"trovato\" la grande ninja\x1FYuffie!");
ROGUE_TEXT(sYuffie1, "Te ne lascio una. Ma una\x1Fsola, e scegli in fretta!");
ROGUE_TEXT(sMoogle0, "Kup\xF2! Bottega di sintesi\x1F" "aperta, kup\xF2!");
ROGUE_TEXT(sMoogle1, "Per te, un lavoretto\x1Fgratis. Quale, kup\xF2?");
ROGUE_TEXT(sJack0, "Sora! Arrivi a proposito\x1Fper il mio nuovo, terrificante\x1F" "esperimento!");
ROGUE_TEXT(sJack1, "Pu\xF2 andare benissimo...\x1Fo malissimo. Non \xE8\x1Fmeraviglioso?");
ROGUE_TEXT(sHercules0, "Un eroe non smette mai\x1F" "di allenarsi. Fil me lo\x1Fripete ogni giorno.");
ROGUE_TEXT(sHercules1, "Dai, ti mostro qualcosa.\x1F" "Cosa vuoi imparare?");
ROGUE_TEXT(sTigger0, "Uh-uh-uh! Saltare \xE8 ci\xF2\x1F" "che i Tigri sanno fare\x1Fmeglio!");
ROGUE_TEXT(sTigger1, "Vuoi che te lo insegni?\x1FO preferisci altro?");
ROGUE_TEXT(sRiku0, "Sora. Ne hai fatta di\x1Fstrada. Vediamo se sei\x1F" "davvero pi\xF9 forte.");
ROGUE_TEXT(sRiku1, "Un duello, come sull'isola.\x1FO hai paura di perdere?");
ROGUE_TEXT(sLexaeus0, "Fermo. Voglio misurare\x1Fla tua forza con le\x1Fmie mani.");
ROGUE_TEXT(sLexaeus1, "Accetta, oppure\x1Fvattene. Non insister\xF2.");
ROGUE_TEXT(sReplica0, "Ti aspettavo, Sora.\x1FStavolta non te la\x1F" "cavi a buon mercato.");
ROGUE_TEXT(sReplica1, "Combatti, o lasciami\x1Fqualcosa di tuo.");
ROGUE_TEXT(sJafar0, "Ah, il ragazzo della chiave.\x1FUn uomo saggio sa\x1Friconoscere un affare.");
ROGUE_TEXT(sJafar1, "Il potere ha un prezzo.\x1FModico. Scegli.");
ROGUE_TEXT(sOogie0, "Ah ah ah! Guarda chi\x1F" "c'\xE8! Ti va di tentare\x1Fla sorte, moccioso?");
ROGUE_TEXT(sOogie1, "Un tiro di dadi. Io\x1Fnon baro quasi mai!");
ROGUE_TEXT(sAnsem0, "Tutti i mondi iniziano\x1Fnell'oscurit\xE0, e cos\xEC\x1F" "finiscono.");
ROGUE_TEXT(sAnsem1, "Aprile il tuo cuore.\x1FTi dar\xE0 molto. In\x1F" "cambio di poco.");
ROGUE_TEXT(sSally0, "Oh, Sora. Ho preparato\x1F" "delle pozioni nuove. Non\x1Fso bene cosa facciano.");
ROGUE_TEXT(sSally1, "Vuoi provarne una\x1Fsulle tue carte?");
ROGUE_TEXT(sJiminy0, "Sora! Ho annotato tutto\x1Fnel diario. Lascia che\x1Fti dia un consiglio.");
ROGUE_TEXT(sJiminy1, "Che cosa ti sarebbe\x1Fpi\xF9 utile?");

#define AXEL_PORTRAIT 20
#define EVENT_PAGES(portrait, a, b) { portrait, 3, 0, 3, 0, &a, 0, 0 }, { portrait, 3, 0, 3, 0, &b, 0, 0 }

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
    { AXEL_PORTRAIT, 3, 0, 3, 0, &sAxel13, 0, 0 },
    EVENT_PAGES(53, sBelle0, sBelle1),
    EVENT_PAGES(31, sLeon0, sLeon1),
    EVENT_PAGES(37, sYuffie0, sYuffie1),
    EVENT_PAGES(7, sMoogle0, sMoogle1),
    EVENT_PAGES(11, sJack0, sJack1),
    EVENT_PAGES(46, sHercules0, sHercules1),
    EVENT_PAGES(59, sTigger0, sTigger1),
    EVENT_PAGES(26, sRiku0, sRiku1),
    EVENT_PAGES(57, sLexaeus0, sLexaeus1),
    EVENT_PAGES(27, sReplica0, sReplica1),
    EVENT_PAGES(16, sJafar0, sJafar1),
    EVENT_PAGES(12, sOogie0, sOogie1),
    EVENT_PAGES(56, sAnsem0, sAnsem1),
    EVENT_PAGES(18, sSally0, sSally1),
    EVENT_PAGES(6, sJiminy0, sJiminy1),
};

const CardMessageDef* RogueCardMessageDef(u16 id) {
    if (id >= ROGUE_MSG_BASE) {
        return &sMessages[id - ROGUE_MSG_BASE];
    }

    return &gCardMessageDefs[id];
}
