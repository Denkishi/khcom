#!/usr/bin/env python3
"""The gadget relics: relics that add something to how a battle plays.

    python3 tools/rogue_gadgets.py

Writes src/rogue/rogue_gadget_table.inc from the list below. Each gadget is
when it goes off (a trigger and its number), what it does (an effect and its
two numbers) and after how many frames; src/rogue/rogue_gadget.c does the
rest. Names and texts are Italian, cp1252; a text is two lines of about
twenty letters, split at the bar.
"""
from pathlib import Path

OUT = Path(__file__).resolve().parents[1] / "src/rogue/rogue_gadget_table.inc"

# Moves, as in enum RogueMove.
CHAKRAM, NEEDLES, PETALS, SHARDS, FIREBALL, BURST, ROCK, BOMB, WATER, WIND, MAGNET, FIREWALL, SCYTHE = range(13)
PLAIN, FIRE, ICE, THUNDER = range(4)

# (name, text, trigger, number, effect, a, b, delay)
GADGETS = [
    # Things that circle Sora and hit what they touch.
    ("Lune ardenti", "Due chakram di fuoco|ti girano attorno", "START", 0, "ORBIT", CHAKRAM, 2, 0),
    ("Corona di gelo", "Tre aghi di ghiaccio|ti girano attorno", "START", 0, "ORBIT", NEEDLES, 3, 0),
    ("Falci custodi", "Due falci di petali|ti girano attorno", "START", 0, "ORBIT", SCYTHE, 2, 0),
    ("Bomba satellite", "Una bomba ti gira|attorno, larga", "START", 0, "ORBIT", BOMB, 1, 0),
    ("Sciame", "Cinque aghi ti girano|attorno, vicini", "START", 0, "ORBIT", NEEDLES, 5, 0),
    # Things that happen on their own, every so often.
    ("Scheggia paziente", "Ogni 6 secondi una scheggia|si forma e parte da sola", "TIMER", 36, "SHARD", NEEDLES, 90, 0),
    ("Temporale", "Ogni 8 secondi un fulmine|su un nemico", "TIMER", 48, "BOLT", 0, 0, 0),
    ("Pioggia di braci", "Ogni 7 secondi tre fiamme|cadono sul bersaglio", "TIMER", 42, "RAIN", BURST, 3, 0),
    ("Battito", "Ogni 5 secondi un'onda|d'urto attorno a te", "TIMER", 30, "SHOCK", PLAIN, 30, 0),
    ("Mina", "Ogni 6 secondi lasci|una bomba dove sei", "TIMER", 36, "AT_SORA", BOMB, 0, 0),
    ("Respiro", "Ogni 10 secondi|recuperi 2 PV", "TIMER", 60, "HEAL", 2, 0, 0),
    ("Polo magnetico", "Ogni 9 secondi i nemici|vengono attirati", "TIMER", 54, "CAST", MAGNET, 0, 0),
    ("Raffica", "Ogni 4 secondi tre aghi|partono in avanti", "TIMER", 24, "CAST", NEEDLES, 0, 0),
    # The dodge.
    ("Scia di fuoco", "La schivata lascia|fiamme dietro di te", "DODGE_STEP", 7, "AT_SORA", BURST, 0, 0),
    ("Scatto gelido", "Dove finisce la schivata|spuntano ghiacci", "DODGE", 0, "AT_SORA", ROCK, 0, 26),
    ("Passo fulmineo", "Schivando, un fulmine|colpisce il bersaglio", "DODGE", 0, "BOLT", 0, 0, 0),
    ("Schivata esplosiva", "Schivando lasci|una bomba", "DODGE", 0, "AT_SORA", BOMB, 0, 0),
    ("Vortice di fuga", "Schivando alzi|un turbine", "DODGE", 0, "AT_SORA", WIND, 0, 0),
    ("Capriola affilata", "A fine schivata|lanci due falci", "DODGE", 0, "CAST", SCYTHE, 0, 26),
    # Jumping and landing.
    ("Atterraggio sismico", "Atterrando scateni|un'onda d'urto", "LAND", 0, "SHOCK", PLAIN, 35, 0),
    ("Salto di fiamma", "Saltando lasci|una vampa a terra", "JUMP", 0, "AT_SORA", BURST, 0, 0),
    ("Caduta gelida", "Atterrando spuntano|ghiacci attorno", "LAND", 0, "AT_SORA", SHARDS, 0, 0),
    ("Tuono dall'alto", "Il salto in aria chiama|un fulmine sul bersaglio", "AIR_JUMP", 0, "BOLT", 0, 0, 0),
    ("Ali di petali", "Il salto in aria|sparge petali", "AIR_JUMP", 0, "AT_SORA", PETALS, 0, 0),
    ("Pioggia d'aghi", "Saltando lanci|tre aghi", "JUMP", 0, "CAST", NEEDLES, 0, 8),
    # Every so many hits of a combo.
    ("Spuntoni", "Ogni 6 colpi di fila il|ghiaccio rilancia in aria", "HIT_N", 6, "AT_TARGET", ROCK, 0, 0),
    ("Colpo magnetico", "Ogni 7 colpi di fila|i nemici si radunano", "HIT_N", 7, "AT_TARGET", MAGNET, 0, 0),
    ("Eco di lama", "Ogni 5 colpi di fila|partono due falci", "HIT_N", 5, "CAST", SCYTHE, 0, 0),
    ("Onda crescente", "Ogni 10 colpi di fila|una grande onda d'urto", "HIT_N", 10, "SHOCK", PLAIN, 70, 0),
    ("Chakram di ritorno", "Ogni 4 colpi di fila|parte un chakram", "HIT_N", 4, "CAST", CHAKRAM, 0, 0),
    ("Petardo", "Ogni 3 colpi di fila|una bomba sul nemico", "HIT_N", 3, "AT_TARGET", BOMB, 0, 0),
    # The combo's last hit.
    ("Finale glaciale", "Il colpo finale alza|ghiacci che bloccano", "FINISHER", 0, "AT_TARGET", ROCK, 1, 0),
    ("Finale tonante", "Il colpo finale chiama|un fulmine", "FINISHER", 0, "BOLT", 0, 0, 6),
    ("Finale a ventaglio", "Il colpo finale lancia|un globo di fuoco", "FINISHER", 0, "CAST", FIREBALL, 0, 0),
    ("Finale magnetico", "Il colpo finale attira|tutti i nemici", "FINISHER", 0, "AT_TARGET", MAGNET, 0, 0),
    # Being hit.
    ("Contraccolpo", "Quando vieni colpito|un'onda d'urto", "HURT", 0, "SHOCK", PLAIN, 40, 0),
    ("Pelle di ghiaccio", "Quando vieni colpito|ghiacci tutt'attorno", "HURT", 0, "AT_SORA", SHARDS, 1, 0),
    ("Ira ardente", "Quando vieni colpito|lanci un globo di fuoco", "HURT", 0, "CAST", FIREBALL, 0, 10),
    ("Scarica difensiva", "Quando vieni colpito un|fulmine sul bersaglio", "HURT", 0, "BOLT", 0, 0, 0),
    # A kill.
    ("Reazione a catena", "Un nemico sconfitto|esplode in fiamme", "KILL", 0, "AT_SPOT", BURST, 0, 4),
    ("Raccolto", "Ogni nemico sconfitto|ti cura di 2 PV", "KILL", 0, "HEAL", 2, 0, 0),
    ("Schegge d'anima", "Un nemico sconfitto ti|fa lanciare tre aghi", "KILL", 0, "CAST", NEEDLES, 0, 6),
    ("Tuono vendicatore", "Un nemico sconfitto|chiama un fulmine", "KILL", 0, "BOLT", 1, 0, 10),
    # Cards.
    ("Ricarica esplosiva", "Finita la ricarica|un'onda di fuoco", "RELOAD", 0, "SHOCK", FIRE, 30, 0),
    ("Ricarica gelida", "Finita la ricarica|un'onda di gelo", "RELOAD", 0, "SHOCK", ICE, 30, 0),
    ("Zero assoluto", "Giocare una carta 0|scatena un'onda di gelo", "ZERO", 0, "SHOCK", ICE, 45, 0),
    ("Carta carica", "Ogni 5 carte giocate|un globo di fuoco", "CARD_N", 5, "CAST", FIREBALL, 0, 0),
    ("Carta rotta", "Spezzare una carta|chiama un fulmine", "BREAK", 0, "BOLT", 0, 0, 0),
    # The battle itself.
    ("Apertura", "A inizio battaglia|un turbine attorno a te", "START", 0, "AT_SORA", WIND, 0, 200),
    ("Ultimo sangue", "Sotto un quarto dei PV|onde di fuoco continue", "LOW_HP", 12, "SHOCK", FIRE, 25, 0),
    # Turning the hand with L and R.
    ("Mescolata affilata", "Ogni 3 giri di mano|parte una falce", "ROTATE", 3, "CAST", SCYTHE, 0, 0),
    ("Dita svelte", "Girare la mano ti|rende più veloce", "ROTATE", 1, "HASTE", 30, 15, 0),
    ("Mano pesante", "Girare la mano ti|costa 1 PV, +40% danno", "ROTATE", 1, "PACT", 40, 20, 0),
    ("Dazio", "Girare la mano ti|costa 1 PV", "ROTATE", 1, "HURT", 1, 0, 0),
    ("Cartomante", "Ogni 4 giri di mano la|prossima carta vale +2", "ROTATE", 4, "VALUE", 2, 0, 0),
    ("Giro di fulmini", "Ogni 6 giri di mano|un fulmine", "ROTATE", 6, "BOLT", 0, 0, 0),
    ("Prestigiatore", "Ogni 5 giri di mano|qualche frammento", "ROTATE", 5, "SHARDS", 1, 0, 0),
    # Stocking cards and the other buttons.
    ("Riserva carica", "Mettere in riserva|una carta: +25% danno", "STOCK", 0, "BUFF", 25, 40, 0),
    ("Riserva gelida", "Mettere in riserva|una carta: gelo attorno", "STOCK", 0, "AT_SORA", SHARDS, 1, 0),
    ("Riserva tesa", "Mettere in riserva una|carta: ricarica rapida", "STOCK", 0, "RELOAD", 100, 60, 0),
    ("Cambio mazzo", "SELECT scatena|un'onda d'urto", "SELECT", 0, "SHOCK", PLAIN, 30, 0),
    ("Segnale", "SELECT attira|i nemici", "SELECT", 0, "CAST", MAGNET, 0, 0),
    # Locking on.
    ("Mirino", "Agganciando un nemico|gli parte un ago", "LOCK", 0, "SHARD", NEEDLES, 4, 0),
    ("Marchio", "Agganciando un nemico|+20% danno per poco", "LOCK", 0, "BUFF", 20, 30, 0),
    ("Occhio del tuono", "Ogni 3 agganci|un fulmine", "LOCK", 3, "BOLT", 0, 0, 0),
    # Standing, running, staying in the air.
    ("Meditazione", "Stando fermo 3 secondi|recuperi 2 PV", "IDLE", 30, "HEAL", 2, 0, 0),
    ("Concentrazione", "Stando fermo 2 secondi|+50% danno per poco", "IDLE", 20, "BUFF", 50, 30, 0),
    ("Torretta", "Stando fermo 2 secondi|lanci tre aghi", "IDLE", 20, "CAST", NEEDLES, 0, 0),
    ("Radici", "Stando fermo 4 secondi|ghiacci attorno a te", "IDLE", 40, "AT_SORA", ROCK, 0, 0),
    ("Pigrizia", "Stando fermo 3 secondi|perdi 1 PV, +80% danno", "IDLE", 30, "PACT", 80, 40, 0),
    ("Corsa ardente", "Correndo lasci|fiamme dietro di te", "RUN", 8, "AT_SORA", BURST, 0, 0),
    ("Rincorsa", "Correndo 2 secondi|+30% danno per poco", "RUN", 20, "BUFF", 30, 30, 0),
    ("Maratoneta", "Correndo 5 secondi|recuperi 1 PV", "RUN", 50, "HEAL", 1, 0, 0),
    ("Vento in poppa", "Correndo 1 secondo|vai più veloce", "RUN", 10, "HASTE", 25, 20, 0),
    ("Semina", "Correndo 3 secondi|lasci una bomba", "RUN", 30, "AT_SORA", BOMB, 0, 0),
    ("Bombardiere", "In aria, ogni secondo|sganci una bomba", "AIRTIME", 10, "AT_SORA", BOMB, 0, 0),
    ("Falco", "In aria, ogni secondo|lanci tre aghi", "AIRTIME", 10, "CAST", NEEDLES, 0, 0),
    ("Nuvola", "In aria, ogni 2 secondi|un fulmine", "AIRTIME", 20, "BOLT", 0, 0, 0),
    ("Leggerezza", "In aria fai il|30% di danno in più", "AIRTIME", 3, "BUFF", 30, 6, 0),
    # Combos, beyond every so many hits.
    ("Chiusura", "Una combo da 5 o più|finisce con un'onda", "COMBO_END", 5, "SHOCK", PLAIN, 45, 0),
    ("Dividendo", "Una combo da 8 o più|ti cura di 3 PV", "COMBO_END", 8, "HEAL", 3, 0, 0),
    ("Incasso", "Una combo da 10 o più|lascia frammenti", "COMBO_END", 10, "SHARDS", 2, 0, 0),
    ("Strascico", "Una combo da 6 o più|finisce con un fulmine", "COMBO_END", 6, "BOLT", 0, 0, 0),
    ("Giocoliere", "Colpire un nemico in aria|lancia una falce", "AIR_HIT", 2, "CAST", SCYTHE, 0, 0),
    ("Contraerea", "Ogni 3 colpi a un nemico|in aria, un fulmine", "AIR_HIT", 3, "BOLT", 0, 0, 0),
    ("Pallavolo", "Ogni 4 colpi a un nemico|in aria, ghiaccio sotto", "AIR_HIT", 4, "AT_TARGET", ROCK, 0, 0),
    ("Primo sangue", "Il primo colpo della|battaglia: +60% danno", "FIRST_HIT", 0, "BUFF", 60, 60, 0),
    ("Biglietto da visita", "Il primo colpo della|battaglia chiama un fulmine", "FIRST_HIT", 0, "BOLT", 0, 0, 4),
    ("Rompighiaccio", "Il primo colpo della|battaglia blocca tutti", "FIRST_HIT", 0, "STOP_ALL", 0, 0, 0),
    # The enemy's cards and Sora's.
    ("Contromossa", "Quando il nemico gioca|una carta, un ago parte", "ENEMY_CARD", 1, "SHARD", NEEDLES, 4, 0),
    ("Lettura", "Ogni 3 carte nemiche la|tua prossima vale +1", "ENEMY_CARD", 3, "VALUE", 1, 0, 0),
    ("Nervi saldi", "Ogni 4 carte nemiche|recuperi 1 PV", "ENEMY_CARD", 4, "HEAL", 1, 0, 0),
    ("Rivalsa", "Se ti spezzano una carta|un'onda d'urto", "BROKEN", 0, "SHOCK", PLAIN, 50, 0),
    ("Orgoglio ferito", "Se ti spezzano una carta|+50% danno per poco", "BROKEN", 0, "BUFF", 50, 40, 0),
    ("Carta gelida", "Se ti spezzano una carta|ghiacci attorno", "BROKEN", 0, "AT_SORA", SHARDS, 1, 0),
    ("Colpo di grazia", "Spezzare una carta dà|+40% danno per poco", "BREAK", 0, "BUFF", 40, 30, 0),
    ("Bottino", "Spezzare una carta|lascia frammenti", "BREAK", 0, "SHARDS", 1, 0, 0),
    ("Spezzacatene", "Spezzare una carta|blocca tutti i nemici", "BREAK", 0, "STOP_ALL", 0, 0, 0),
    ("Nove", "Giocare un 9|scatena un'onda di fuoco", "NINE", 0, "SHOCK", FIRE, 60, 0),
    ("Asso", "Giocare un 9: la|prossima carta vale +3", "NINE", 0, "VALUE", 3, 0, 0),
    ("Zero termico", "Giocare uno 0|blocca tutti i nemici", "ZERO", 0, "STOP_ALL", 0, 0, 0),
    ("Zero carico", "Giocare uno 0: +50%|danno per poco", "ZERO", 0, "BUFF", 50, 30, 0),
    ("Arcanista", "Ogni magia giocata|lascia un ghiaccio", "SPELL", 1, "AT_TARGET", SHARDS, 0, 8),
    ("Risonanza", "Ogni 2 magie giocate|un fulmine", "SPELL", 2, "BOLT", 0, 0, 8),
    ("Catalizzatore", "Ogni 3 magie giocate la|prossima carta vale +2", "SPELL", 3, "VALUE", 2, 0, 0),
    ("Spadaccino", "Ogni 6 Keyblade giocate|una falce doppia", "ATTACK_CARD", 6, "CAST", SCYTHE, 0, 0),
    ("Maestro d'armi", "Ogni 8 Keyblade giocate|+40% danno per poco", "ATTACK_CARD", 8, "BUFF", 40, 40, 0),
    ("Fanfara", "Chiamare un alleato|scatena un'onda d'urto", "SUMMON", 0, "SHOCK", PLAIN, 50, 14),
    ("Scorta", "Chiamare un alleato|ti cura di 3 PV", "SUMMON", 0, "HEAL", 3, 0, 0),
    ("Ingresso tonante", "Chiamare un alleato|chiama anche un fulmine", "SUMMON", 0, "BOLT", 0, 0, 14),
    ("Ricarica curativa", "Finita la ricarica|recuperi 2 PV", "RELOAD", 0, "HEAL", 2, 0, 0),
    ("Ricarica furiosa", "Finita la ricarica|+40% danno per poco", "RELOAD", 0, "BUFF", 40, 40, 0),
    ("Ricarica in fuga", "Finita la ricarica|vai più veloce", "RELOAD", 0, "HASTE", 40, 40, 0),
    ("Carta veloce", "Ogni 4 carte giocate|vai più veloce", "CARD_N", 4, "HASTE", 30, 20, 0),
    ("Carta pesante", "Ogni carta ti rallenta|ma dà +15% danno", "CARD_N", 1, "WEIGHT", 15, 20, 0),
    # Prizes, health, time.
    ("Avaro", "Ogni 3 premi raccolti|+30% danno per poco", "PRIZE", 3, "BUFF", 30, 30, 0),
    ("Goloso", "Ogni 5 premi raccolti|recuperi 1 PV", "PRIZE", 5, "HEAL", 1, 0, 0),
    ("Calamita di premi", "Ogni 4 premi raccolti|una scheggia parte", "PRIZE", 4, "SHARD", NEEDLES, 10, 0),
    ("Intoccabile", "5 secondi senza subire|colpi: +40% danno", "UNHURT", 50, "BUFF", 40, 50, 0),
    ("Calma", "8 secondi senza subire|colpi: recuperi 2 PV", "UNHURT", 80, "HEAL", 2, 0, 0),
    ("Guardia alta", "6 secondi senza subire|colpi: uno scudo breve", "UNHURT", 60, "SHIELD", 20, 0, 0),
    ("Salute di ferro", "Coi PV al massimo|+25% danno", "FULL_HP", 5, "BUFF", 25, 6, 0),
    ("Esuberanza", "Coi PV al massimo, ogni|4 secondi un'onda d'urto", "FULL_HP", 40, "SHOCK", PLAIN, 30, 0),
    ("Adrenalina", "Quando vieni colpito|vai più veloce", "HURT", 0, "HASTE", 40, 30, 0),
    ("Riflesso", "Quando vieni colpito|uno scudo breve", "HURT", 0, "SHIELD", 12, 0, 0),
    ("Sete di sangue", "Ogni nemico sconfitto|+30% danno per poco", "KILL", 0, "BUFF", 30, 40, 0),
    ("Bottino di guerra", "Ogni nemico sconfitto|lascia frammenti", "KILL", 0, "SHARDS", 1, 0, 0),
    ("Slancio di caccia", "Ogni nemico sconfitto|ti rende più veloce", "KILL", 0, "HASTE", 30, 30, 0),
    ("Finale rapido", "Il colpo finale ti|rende più veloce", "FINISHER", 0, "HASTE", 30, 20, 0),
    ("Finale in riserva", "Il colpo finale: la|prossima carta vale +1", "FINISHER", 0, "VALUE", 1, 0, 0),
]

# Fusions: a run that has both relics of a pair gets, in place of what each
# does, one thing that neither does. (first, second, name of the fusion,
# trigger, number, effect, a, b, delay); the relics are named as above.
FUSIONS = [
    ("Lune ardenti", "Corona di gelo", "START", 0, "ORBIT", FIREBALL, 2 | 0x80, 0),
    ("Falci custodi", "Sciame", "START", 0, "ORBIT", SCYTHE, 6, 0),
    ("Scheggia paziente", "Raffica", "TIMER", 30, "VOLLEY", NEEDLES, 3, 0),
    ("Temporale", "Pioggia di braci", "TIMER", 50, "RAIN", FIREBALL, 4, 0),
    ("Scia di fuoco", "Scatto gelido", "DODGE_STEP", 5, "AT_SORA", WATER, 0, 0),
    ("Atterraggio sismico", "Caduta gelida", "LAND", 0, "AT_SORA", ROCK, 1, 0),
    ("Spuntoni", "Petardo", "HIT_N", 4, "AT_TARGET", WATER, 0, 0),
    ("Finale tonante", "Finale glaciale", "FINISHER", 0, "RAIN", ROCK, 3, 0),
    ("Contraccolpo", "Pelle di ghiaccio", "HURT", 0, "SHOCK", ICE, 70, 0),
    ("Reazione a catena", "Tuono vendicatore", "KILL", 0, "AT_SPOT", WIND, 0, 4),
    ("Ricarica esplosiva", "Ricarica gelida", "RELOAD", 0, "SHOCK", THUNDER, 60, 0),
    ("Battito", "Polo magnetico", "TIMER", 45, "AT_SORA", MAGNET, 0, 0),
    ("Mina", "Schivata esplosiva", "DODGE", 0, "RAIN", BOMB, 3, 0),
    ("Chakram di ritorno", "Eco di lama", "HIT_N", 4, "AT_TARGET", PETALS, 0, 0),
    ("Salto di fiamma", "Ali di petali", "AIR_JUMP", 0, "AT_SORA", FIREWALL, 0, 0),
    ("Corsa ardente", "Semina", "RUN", 12, "AT_SORA", FIREWALL, 0, 0),
    ("Bombardiere", "Falco", "AIRTIME", 8, "RAIN", NEEDLES, 3, 0),
    ("Torretta", "Radici", "IDLE", 20, "VOLLEY", NEEDLES, 4, 0),
    ("Mescolata affilata", "Giro di fulmini", "ROTATE", 4, "AT_TARGET", SCYTHE, 0, 0),
    ("Contromossa", "Mirino", "ENEMY_CARD", 1, "VOLLEY", NEEDLES, 2, 0),
]



def c_string(text):
    out = ""
    for ch in text:
        if ch == "|":
            out += '\\x1F" "'
        elif ord(ch) < 128:
            out += ch
        else:
            out += '\\x%02X" "' % ord(ch.encode("cp1252"))
    return out


def main():
    out = ["// Generated by tools/rogue_gadgets.py. Do not edit.", ""]
    for index, (name, text, *_rest) in enumerate(GADGETS):
        out.append(f'static const u8 sGadgetName{index}[] = "{c_string(name)}";')
        out.append(f'static const u8 sGadgetText{index}[] = "{c_string(text)}";')
    out += ["", "static const RogueGadgetDef sGadgets[ROGUE_GADGETS] = {"]
    for index, (name, _text, trigger, number, effect, a, b, delay) in enumerate(GADGETS):
        out.append(f"    {{ sGadgetName{index}, sGadgetText{index}, GADGET_ON_{trigger}, {number}, GADGET_DO_{effect}, {a}, {b}, {delay} }}, // {name}")
    out += ["};", "", f"typedef char RogueGadgets_check[({len(GADGETS)} == ROGUE_GADGETS) ? 1 : -1];", ""]
    names = [g[0] for g in GADGETS]
    out += [f"#define ROGUE_FUSIONS {len(FUSIONS)}", "", "static const RogueFusionDef sFusions[ROGUE_FUSIONS] = {"]
    for first, second, trigger, number, effect, a, b, delay in FUSIONS:
        out.append(f"    {{ {names.index(first)}, {names.index(second)}, {{ 0, 0, GADGET_ON_{trigger}, {number}, GADGET_DO_{effect}, {a}, {b}, {delay} }} }}, // {first} + {second}")
    out += ["};", ""]
    OUT.write_text("\n".join(out))
    print(f"wrote {OUT.name}: {len(GADGETS)} gadgets, {len(FUSIONS)} fusions")


if __name__ == "__main__":
    main()
