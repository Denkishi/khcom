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
ROGUE_TEXT(sAxel12, "Nel menu, \x1DMemoria\x1E mostra\x1Fla tua run e \x1DSalva e via\x1E\x1Fla mette in pausa.");
ROGUE_TEXT(sAxel13, "Ci\xF2 di cui hai tanto fa una\x1F\x1D" "build\x1E: elementi, lame, magie,\x1Fproiettili. E si sommano.");
ROGUE_TEXT(sAxel14, "Nelle stanze evento trovi\x1F" "amici e nemici: doni, patti,\x1F" "duelli. Scegli bene.");
ROGUE_TEXT(sAxel15, "Le \x1Dreliquie\x1E durano la run.\x1F" "Alcune cambiano ogni mossa:\x1F" "pi\xF9 colpi, ventaglio, eco...");
ROGUE_TEXT(sAxel16, "Le carte \x1Dnemico\x1E chiamano il\x1Floro mostro o boss a colpire\x1F" "al posto tuo, come un amico.");
ROGUE_TEXT(sAxel17, "Fuoco, gelo e tuono possono\x1Flasciare \x1Dustione\x1E, blocco\x1F" "e scarica sui nemici.");
ROGUE_TEXT(sAxel18, "Una carta si pu\xF2 \x1Dincantare\x1E:\x1Fl'effetto resta su di lei\x1F" "per tutta la run.");
ROGUE_TEXT(sAxel19, "Da me trovi l'\x1D" "albero\x1E delle\x1F" "abilit\xE0: tre rami, ogni nodo\x1F" "apre il successivo.");
ROGUE_TEXT(sAxel20, "I boss lasciano \x1DSigilli\x1E:\x1Fspendili da me in carte con\x1F" "cui partire sempre.");
ROGUE_TEXT(sAxel21, "Qui nell'hub, SELECT cambia\x1F" "\x1D" "eroe\x1E e L/R il livello\x1F" "di Oblio, se li hai.");
ROGUE_TEXT(sAxel22, "Got it memorized?");

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
ROGUE_TEXT(sWendy0, "Oh, Sora! Arrivi giusto\x1Fin tempo per una storia.\x1FNe conosco tante.");
ROGUE_TEXT(sWendy1, "Quale vuoi sentire\x1Fstavolta?");
ROGUE_TEXT(sBeast0, "Tu. Conosco quello\x1Fsguardo. Anche tu hai\x1Fqualcuno da proteggere.");
ROGUE_TEXT(sBeast1, "La rabbia d\xE0 forza.\x1FMa lascia il segno.");
ROGUE_TEXT(sTidus0, "Ehi, Sora! Scommetto che\x1Fnon mi batti ancora.\x1FGuarda che mossa!");
ROGUE_TEXT(sTidus1, "Te la insegno, se vuoi.\x1FO preferisci altro?");
ROGUE_TEXT(sSelphie0, "Sora! Facciamo cambio\x1F" "di carte? Dai, sar\xE0\x1F" "divertente!");
ROGUE_TEXT(sSelphie1, "Scegli tu come.\x1FNiente imbrogli, eh!");
// What each character in the hub says when their boon is picked, in the
// order of RogueBoon.
ROGUE_TEXT(sBoonBelle, "Abbi cura di te, Sora.\x1FPartirai con \x1D" "30 PV\x1E in pi\xF9.");
ROGUE_TEXT(sBoonMoogle, "Kup\xF2! Per la prossima run\x1Fti do \x1D" "due rilanci\x1E delle\x1Fricompense, kup\xF2!");
ROGUE_TEXT(sBoonLeon, "Affidati alla spada.\x1FIl tuo mazzo sar\xE0 quasi\x1Ftutto di \x1DKeyblade\x1E.");
ROGUE_TEXT(sBoonYuffie, "Roba da ninja! Il tuo\x1Fmazzo sar\xE0 pieno di\x1F\x1Dmagie\x1E. Fidati!");
ROGUE_TEXT(sBoonHercules, "Ti ho preparato a dovere.\x1FPartirai con \x1D" "Forza +2\x1E.");
ROGUE_TEXT(sBoonTigger, "Uh-uh-uh! Stavolta salti\x1F" "con me: parti col \x1Dsalto\x1F" "in aria\x1E!");
ROGUE_TEXT(sBoonJack, "Un regalo spaventoso!\x1FPartirai con una\x1F\x1Dreliquia\x1E a sorpresa.");
ROGUE_TEXT(sBoonKairi, "Kairi: Torna da me, Sora.\x1FPartirai con \x1D" "20 PV\x1E in pi\xF9\x1F" "e un \x1Drilancio\x1E.");
ROGUE_TEXT(sBoonNamine, "Namin\xE9: Riordino i tuoi\x1Fricordi. Avrai \x1D" "30 PC\x1E in\x1Fpi\xF9 per il mazzo.");
ROGUE_TEXT(sBoonAqua, "Aqua: La mia barriera ti\x1Fsalver\xE0 una volta da\x1Fun \x1D" "colpo fatale\x1E.");
ROGUE_TEXT(sBoonTerra, "Terra: La forza \xE8 tutto.\x1F\x1D" "Forza +1\x1E e \x1D" "colpi critici\x1E.");
ROGUE_TEXT(sBoonVentus, "Ventus: Pi\xF9 veloce del\x1Fvento! Un \x1Dsalto in aria\x1E\x1F" "e pi\xF9 danno lass\xF9.");
ROGUE_TEXT(sBoonVanitas, "Vanitas: Prendi l'oscurit\xE0.\x1F\x1D" "Forza +3\x1E, ma ogni colpo\x1Fti far\xE0 pi\xF9 male.");

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
    { AXEL_PORTRAIT, 3, 0, 3, 0, &sAxel14, 0, 0 },
    { AXEL_PORTRAIT, 3, 0, 3, 0, &sAxel15, 0, 0 },
    { AXEL_PORTRAIT, 3, 0, 3, 0, &sAxel16, 0, 0 },
    { AXEL_PORTRAIT, 3, 0, 3, 0, &sAxel17, 0, 0 },
    { AXEL_PORTRAIT, 3, 0, 3, 0, &sAxel18, 0, 0 },
    { AXEL_PORTRAIT, 3, 0, 3, 0, &sAxel19, 0, 0 },
    { AXEL_PORTRAIT, 3, 0, 3, 0, &sAxel20, 0, 0 },
    { AXEL_PORTRAIT, 3, 0, 3, 0, &sAxel21, 0, 0 },
    { AXEL_PORTRAIT, 3, 0, 3, 0, &sAxel22, 0, 0 },
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
    EVENT_PAGES(42, sWendy0, sWendy1),
    EVENT_PAGES(43, sBeast0, sBeast1),
    EVENT_PAGES(39, sTidus0, sTidus1),
    EVENT_PAGES(40, sSelphie0, sSelphie1),
    { 53, 3, 0, 3, 0, &sBoonBelle, 0, 0 },
    { 7, 3, 0, 3, 0, &sBoonMoogle, 0, 0 },
    { 31, 3, 0, 3, 0, &sBoonLeon, 0, 0 },
    { 37, 3, 0, 3, 0, &sBoonYuffie, 0, 0 },
    { 46, 3, 0, 3, 0, &sBoonHercules, 0, 0 },
    { 59, 3, 0, 3, 0, &sBoonTigger, 0, 0 },
    { 11, 3, 0, 3, 0, &sBoonJack, 0, 0 },
    // Their faces are the mod's, in the order tools/rogue_npcs.py has them.
    { ROGUE_FACE_FIRST + 4, 3, 0, 3, 0, &sBoonKairi, 0, 0 },
    { ROGUE_FACE_FIRST + 5, 3, 0, 3, 0, &sBoonNamine, 0, 0 },
    { ROGUE_FACE_FIRST + 0, 3, 0, 3, 0, &sBoonAqua, 0, 0 },
    { ROGUE_FACE_FIRST + 1, 3, 0, 3, 0, &sBoonTerra, 0, 0 },
    { ROGUE_FACE_FIRST + 2, 3, 0, 3, 0, &sBoonVentus, 0, 0 },
    { ROGUE_FACE_FIRST + 3, 3, 0, 3, 0, &sBoonVanitas, 0, 0 },
};

const CardMessageDef* RogueCardMessageDef(u16 id) {
    if (id >= ROGUE_MSG_BASE) {
        return &sMessages[id - ROGUE_MSG_BASE];
    }

    return &gCardMessageDefs[id];
}
