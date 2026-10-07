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
    OUT.write_text("\n".join(out))
    print(f"wrote {OUT.name}: {len(GADGETS)} gadgets")


if __name__ == "__main__":
    main()
