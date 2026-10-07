#!/usr/bin/env python3
"""Turn pictures from the custom card sheets into the mod's card art.

    build/venv/bin/python tools/rogue_cards.py

Writes src/rogue/rogue_card_art.c and src/rogue/rogue_card_table.inc. Each
card gets what a vanilla card has: a 32x32 picture (16 tiles, 4bpp) with its
palette, and the 16x32 card shown in the hand and the deck (8 tiles) with a
palette of its own. Needs the original ROM in roms/ and a built link map.
"""
import re
from pathlib import Path

from PIL import Image

ROOT = Path(__file__).resolve().parents[1]
BASEROM = ROOT / "roms/B8CP.gba"
MAP = ROOT / "build/eu/com_eu.map"
CATALOG = ROOT / "src/card/card_catalog_defs.inc"
OUT = ROOT / "src/rogue/rogue_card_art.c"
OUT_TABLE = ROOT / "src/rogue/rogue_card_table.inc"
TRANSPARENT = (255, 0, 255)

# Each new card behaves as an original one, its base: it takes that card's
# action, sleight group and help text, with a picture, a name and a CP cost of
# its own. Listed in id order, ten ids a card from ROGUE_FIRST_CARD_KIND * 10:
# (C name, Italian name, sheet, box of the picture with its border, base card
# kind, CP added to the base's).
CARDS = [
    ("BondOfFlame", "Legame di fuoco", "extra_cards_1.png", (118, 340, 148, 374), 9, 10),
    ("TwoBecomeOne", "Due in uno", "extra_cards_1.png", (118, 395, 148, 428), 13, 10),
    ("HiddenDragon", "Drago celato", "extra_cards_1.png", (119, 283, 149, 316), 11, 10),
    ("FollowTheWind", "Segui il vento", "extra_cards_1.png", (118, 226, 150, 259), 7, 5),
    ("Monochrome", "Monocromia", "extra_cards_1.png", (118, 454, 148, 487), 12, 10),
    ("MidnightRoar", "Ruggito notturno", "extra_cards_2.png", (104, 136, 134, 170), 3, 10),
    ("TotalEclipse", "Eclissi totale", "extra_cards_2.png", (105, 200, 135, 234), 15, 10),
    ("GlimpseOfDarkness", "Sguardo oscuro", "extra_cards_2.png", (103, 264, 135, 298), 13, 15),
    ("MaverickFlare", "Vampa ribelle", "extra_cards_2.png", (105, 325, 137, 359), 9, 15),
    ("OminousBlight", "Rovina funesta", "extra_cards_2.png", (105, 384, 137, 418), 14, 10),
    ("LunarEclipse", "Eclissi lunare", "extra_cards_2.png", (106, 442, 138, 476), 6, 10),
    ("SilentDirge", "Nenia silente", "extra_cards_2.png", (107, 500, 139, 534), 4, 10),
    ("DreamSword", "Spada del sogno", "extra_cards_2.png", (107, 562, 139, 596), 0, 10),
    ("Water", "Acqua", "extra_cards_1.png", (136, 709, 170, 744), 18, 5),
    ("Wind", "Vento", "extra_cards_1.png", (131, 544, 165, 579), 23, 5),
    ("Magnet", "Magnete", "extra_cards_2.png", (125, 654, 157, 688), 21, 5),
    # From here on each card has an effect of its own, the last three fields:
    # what it does (a ROGUE_EFFECT_), two numbers for it and the bit of
    # gRogueMeta.bossMoves that unlocks it, 0 for none. They are cast as spells.
    ("HeroKey", "Chiave eroica", "extra_cards_1.png", (118, 165, 152, 199), 0, 10, "NONE", 0, 0, 0),
    ("Pluto", "Pluto", "extra_cards_1.png", (381, 107, 415, 140), 17, 0, "PLUTO", 38, 0, 0),
    ("Hunny", "Miele", "extra_cards_1.png", (134, 598, 168, 631), 17, 0, "HEAL", 77, 0, 0),
    ("Stitch", "Stitch", "extra_cards_1.png", (135, 654, 169, 688), 17, 10, "SHOCK", 3, 60, 0),
    ("HunnyBee", "Ape del miele", "extra_cards_1.png", (392, 198, 426, 230), 17, 0, "MOVE", 1, 0, 0),
    ("StealthSneak", "Furtilucertola", "extra_cards_1.png", (395, 249, 427, 285), 17, 5, "SHOCK", 0, 175, 0),
    ("SneakArmy", "Sgattaiolante", "extra_cards_1.png", (396, 303, 428, 337), 17, 0, "MOVE", 0, 0, 0),
    ("MissileDiver", "Sub missile", "extra_cards_1.png", (395, 359, 427, 393), 17, 0, "MOVE", 7, 0, 0),
    ("KurtZisa", "Kurt Zisa", "extra_cards_1.png", (394, 412, 426, 445), 17, 15, "MOVE", 9, 0, 0),
    ("VioletWaltz", "Valzer viola", "extra_cards_1.png", (394, 464, 430, 500), 17, 5, "MOVE", 10, 0, 0),
    ("TridentTail", "Coda tridente", "extra_cards_1.png", (395, 519, 429, 552), 17, 5, "MOVE", 4, 0, 0),
    ("Roxas", "Roxas", "extra_cards_1.png", (394, 572, 430, 607), 17, 20, "SHOCK", 0, 225, 0),
    ("Invisible", "Invisibile", "extra_cards_2.png", (325, 81, 357, 115), 17, 10, "SHOCK", 0, 200, 0),
    ("Orcus", "Orcus", "extra_cards_2.png", (326, 137, 358, 171), 17, 10, "MOVE", 5, 0, 0),
    ("AngelStar", "Stella angelica", "extra_cards_2.png", (325, 194, 357, 227), 17, 10, "MOVE", 9, 0, 0),
    ("JetBalloon", "Pallone jet", "extra_cards_2.png", (326, 249, 358, 283), 17, 0, "MOVE", 7, 0, 0),
    ("StealthSoldier", "Soldato furtivo", "extra_cards_2.png", (328, 302, 361, 337), 17, 5, "SHOCK", 2, 60, 0),
    ("OppositeArmor", "Armatura opposta", "extra_cards_2.png", (328, 360, 360, 394), 17, 15, "MOVE", 6, 0, 0),
    ("ArmoredTorso", "Torso corazzato", "extra_cards_2.png", (323, 454, 355, 488), 17, 5, "SHOCK", 0, 150, 0),
    ("Gauntlets", "Guanti", "extra_cards_2.png", (323, 512, 356, 545), 17, 5, "SHOCK", 1, 60, 0),
    ("Hammerlegs", "Gambe martello", "extra_cards_2.png", (325, 572, 357, 605), 17, 5, "MOVE", 6, 0, 0),
    ("PoweredArmor", "Armatura potenziata", "extra_cards_2.png", (321, 652, 355, 686), 17, 10, "MOVE", 5, 0, 0),
    ("GuardArmorO", "Guardia Omega", "extra_cards_2.png", (323, 724, 355, 757), 17, 20, "SHOCK", 0, 250, 0),
    # The boss moves as cards, with the picture of the boss's own enemy card
    # read from the original ROM: "rom" and the card's id.
    ("MoveChakram", "Chakram", "rom", 558, 17, 5, "MOVE", 0, 0, 4),
    ("MoveNeedles", "Aghi di ghiaccio", "rom", 560, 17, 5, "MOVE", 1, 0, 2),
    ("MovePetals", "Petali", "rom", 561, 17, 5, "MOVE", 2, 0, 8),
    ("MoveShards", "Schegge", "rom", 560, 17, 5, "MOVE", 3, 0, 2),
    ("MoveFireball", "Globo di fuoco", "rom", 551, 17, 5, "MOVE", 4, 0, 16),
    ("MoveRock", "Roccia", "rom", 563, 17, 10, "MOVE", 6, 0, 32),
    ("MoveBomb", "Bomba", "rom", 555, 17, 5, "MOVE", 7, 0, 64),
    ("MoveKnives", "Coltelli", "rom", 559, 17, 5, "KNIVES", 0, 0, 1),
    ("MovePillar", "Blocco di gelo", "rom", 560, 17, 10, "PILLAR", 0, 0, 2),
    ("MoveQuake", "Onda d'urto", "rom", 541, 17, 15, "SHOCK", 0, 250, 0),
]


# Icons for the rewards that are not cards, from the prizes sheet: (C name, box).
# They are drawn at twice their size in a card picture's 32x32.
ICON_SHEET = "prizes.png"
ICONS = [
    ("Shards", (76, 192, 88, 204)),  # munny
    ("Heal", (268, 18, 280, 30)),  # hunny orb
    ("MaxHp", (267, 68, 279, 80)),  # struggle orb
    ("Cp", (36, 267, 50, 281)),  # D-Link prize
    ("Combo", (44, 229, 56, 241)),  # drive orb
    ("Attack", (8, 403, 20, 415)),  # attack prize
    ("Relic", (519, 470, 534, 485)),  # keyblade medal
    ("Art", (521, 418, 538, 431)),  # command
    ("Reroll", (43, 148, 55, 160)),  # MP prize
    ("Item", (524, 57, 541, 74)),  # item box
]


# The ability tree's node icons, from the material icons sheet, in the order
# of the tree's grid: three branches of six. They share one palette, so that
# a node can be shown reached, locked or full by changing palette alone.
TREE_SHEET = "materials_1.png"
TREE_ICONS = [
    (465, 320, 479, 334), (465, 342, 479, 356), (465, 367, 479, 381), (624, 371, 638, 385), (624, 399, 638, 413), (624, 313, 638, 327),
    (19, 546, 33, 560), (106, 580, 120, 594), (512, 548, 526, 562), (331, 546, 345, 560), (430, 488, 444, 502), (430, 513, 444, 527),
    (624, 342, 638, 356), (465, 393, 479, 407), (184, 546, 198, 560), (657, 548, 671, 562), (622, 485, 636, 499), (438, 582, 452, 596),
]


def symbol_offsets():
    text = MAP.read_text()
    return {name: int(addr, 16) - 0x08000000 for addr, name in re.findall(r"^\s+0x(0[89][0-9a-f]{6})\s+(\w+)$", text, re.M)}


def base_cards():
    """The EU symbols and the numbers of the first card of every original kind."""
    entries = CATALOG.read_text().split("\n    {\n")
    entries[0] = entries[0].lstrip(" {\n")
    bases = {}
    for kind in list(range(45)) + [("id", n) for n in range(450, 566)]:
        entry = entries[kind * 10] if isinstance(kind, int) else entries[kind[1]]
        symbols = re.search(r"#elif defined\(VERSION_EU\)\n(.*?)\n#endif", entry, re.S).group(1)
        symbols = [x.strip().lstrip("&") for x in symbols.split(",") if x.strip()]
        numbers = " ".join(entry.split("#endif")[-1].split())
        fields = re.match(r"(\d+), (0x[0-9a-fA-F]+), \d+, \{0, 0, 0\}, (0x[0-9a-fA-F]+), (\d+), (\d+), 0, (\d+), \{(.*?)\}", numbers)
        bases[kind] = (symbols, fields.groups() if fields else None)
    return bases


def rom_palette(rom, offset):
    colors = []
    for i in range(16):
        value = rom[offset + 2 * i] | rom[offset + 2 * i + 1] << 8
        colors.append(((value & 31) << 3, (value >> 5 & 31) << 3, (value >> 10 & 31) << 3))
    return colors


def rom_tiles(rom, offset, count, columns, palette):
    image = Image.new("RGB", (columns * 8, count // columns * 8))
    for tile in range(count):
        for y in range(8):
            for x in range(8):
                byte = rom[offset + tile * 32 + y * 4 + x // 2]
                index = byte >> 4 if x & 1 else byte & 15
                color = TRANSPARENT if index == 0 else palette[index]
                image.putpixel((tile % columns * 8 + x, tile // columns * 8 + y), color)
    return image


def quantize(image):
    """Returns (indices, palette): index 0 is transparent, up to 15 colours follow."""
    opaque = [p for p in image.get_flattened_data() if p != TRANSPARENT]
    reduced = Image.new("RGB", (len(opaque), 1))
    reduced.putdata(opaque)
    reduced = reduced.quantize(15, method=Image.Quantize.MEDIANCUT, dither=Image.Dither.NONE)
    flat = reduced.getpalette()[:45]
    palette = [(0, 0, 0)] + [tuple(flat[i:i + 3]) for i in range(0, len(flat), 3)]
    palette += [(0, 0, 0)] * (16 - len(palette))
    it = iter(reduced.get_flattened_data())
    indices = [0 if p == TRANSPARENT else next(it) + 1 for p in image.get_flattened_data()]
    return indices, palette


def gba_tiles(indices, width, height):
    data = bytearray()
    for ty in range(0, height, 8):
        for tx in range(0, width, 8):
            for y in range(8):
                for x in range(0, 8, 2):
                    low = indices[(ty + y) * width + tx + x]
                    high = indices[(ty + y) * width + tx + x + 1]
                    data.append(low | high << 4)
    return bytes(data)


def gba_palette(palette):
    data = bytearray()
    for r, g, b in palette:
        value = r >> 3 | (g >> 3) << 5 | (b >> 3) << 10
        data += bytes((value & 0xFF, value >> 8))
    return bytes(data)


def c_array(name, data):
    lines = [f"const u8 {name}[{len(data)}] = {{"]
    for i in range(0, len(data), 16):
        lines.append("    " + ", ".join(f"0x{b:02X}" for b in data[i:i + 16]) + ",")
    lines.append("};")
    return "\n".join(lines)


def main():
    rom = BASEROM.read_bytes()
    offsets = symbol_offsets()
    bases = base_cards()
    art = ['// Generated by tools/rogue_cards.py from the sheets in mod_assets. Do not edit.',
           '#include "types.h"', ""]
    table = ['// Generated by tools/rogue_cards.py. Do not edit.', ""]
    effects = []
    for name, italian, sheet, box, base, cp_bonus, *effect in CARDS:
        effects.append(effect or ["NONE", 0, 0, 0])
        (frame, _tiles, _palette, _name, small_frame, small_tiles, small_palette), fields = bases[base]
        index, flags, action, group, kind_type, cp, trailer = fields
        if sheet == "rom":
            # The picture of an original card, with a border as the sheets' have.
            symbols = bases[("id", box)][0]
            picture = Image.new("RGB", (34, 34), (40, 40, 60))
            picture.paste(rom_tiles(rom, offsets[symbols[1]], 16, 4, rom_palette(rom, offsets[symbols[2]])), (1, 1))
            picture = Image.eval(picture, lambda v: v)
            for y in range(34):
                for x in range(34):
                    if picture.getpixel((x, y)) == TRANSPARENT:
                        picture.putpixel((x, y), (16, 16, 32))
        else:
            picture = Image.open(ROOT / "mod_assets" / sheet).convert("RGB").crop(box)
        big = Image.new("RGB", (32, 32), TRANSPARENT)
        big.paste(picture, ((32 - picture.width) // 2, (32 - picture.height) // 2))
        indices, palette = quantize(big)
        art += [c_array(f"gRogueCard{name}Tiles", gba_tiles(indices, 32, 32)),
                c_array(f"gRogueCard{name}Palette", gba_palette(palette)), ""]

        # The small card shown in the hand and the deck: the base card's own,
        # read from the original ROM, with the new picture shrunk into the
        # window under the crown. The value disc in the corner stays on top.
        small = rom_tiles(rom, offsets[small_tiles], 8, 2, rom_palette(rom, offsets[small_palette]))
        inner = picture.crop((2, 2, picture.width - 2, picture.height - 2)).resize((12, 13), Image.Resampling.BOX)
        for y in range(13):
            for x in range(12):
                target = (2 + x, 14 + y)
                if small.getpixel(target) != (0, 0, 0) or target[0] < 8 or target[1] < 22:
                    small.putpixel(target, inner.getpixel((x, y)))
        indices, palette = quantize(small)
        art += [c_array(f"gRogueCard{name}SmallTiles", gba_tiles(indices, 16, 32)),
                c_array(f"gRogueCard{name}SmallPalette", gba_palette(palette)), ""]

        encoded = "".join(c if ord(c) < 128 else "\\x%02X\" \"" % ord(c.encode("cp1252")) for c in italian)
        table += [f"// {italian}: behaves as original card kind {base}.",
                  f'static const u8 sName{name}_It[] = "{encoded}";',
                  f"static const LocalizedText sName{name} = {{ {{ (u8*)sName{name}_It, (u8*)sName{name}_It, (u8*)sName{name}_It, "
                  f"(u8*)sName{name}_It, (u8*)sName{name}_It }} }};",
                  f"extern const u8 gRogueCard{name}Tiles[], gRogueCard{name}Palette[], gRogueCard{name}SmallTiles[], "
                  f"gRogueCard{name}SmallPalette[];",
                  f"#define ROGUE_CARD_{name.upper()}(value) \\",
                  f"    {{ {frame}, (void*)gRogueCard{name}Tiles, (void*)gRogueCard{name}Palette, (void*)&sName{name}, {small_frame}, \\",
                  f"      (void*)gRogueCard{name}SmallTiles, (void*)gRogueCard{name}SmallPalette, \\",
                  f"      {index}, {flags}, value, {{ 0, 0, 0 }}, {action}, {group}, {kind_type}, 0, \\",
                  f"      {int(cp) + cp_bonus} + {(int(cp) + cp_bonus) // 10} * ((value) == 0 ? 9 : (value) - 1), {{ {trailer} }} }}",
                  ""]
    table += ["// The table entries, ten for each card.", "#define ROGUE_CARD_TABLE \\"]
    for name, *_ in CARDS:
        table.append("    " + ", ".join(f"ROGUE_CARD_{name.upper()}({v})" for v in range(10)) + ", \\")
    table[-1] = table[-1].rstrip(" \\").rstrip(",")
    table += ["", f"#define ROGUE_CARD_TABLE_KINDS {len(CARDS)}", "",
              "// What each card does beyond its base card: effect, two numbers, unlocking boss bit.",
              "#define ROGUE_CARD_EFFECTS \\"]
    for effect, a, b, unlock in effects:
        table.append(f"    {{ ROGUE_EFFECT_{effect}, {a}, {b}, {unlock} }}, \\")
    table[-1] = table[-1].rstrip(" \\").rstrip(",")
    table += [""]
    sheet = Image.open(ROOT / "mod_assets" / ICON_SHEET).convert("RGBA")
    for name, box in ICONS:
        icon = sheet.crop(box)
        icon = icon.resize((icon.width * 2, icon.height * 2), Image.Resampling.NEAREST)
        big = Image.new("RGB", (32, 32), TRANSPARENT)
        # The sheet's background is black, drawn or not: it is left out.
        solid = Image.new("RGB", icon.size, TRANSPARENT)
        mask = Image.eval(icon.convert("L"), lambda v: 255 if v > 0 else 0)
        solid.paste(icon.convert("RGB"), mask=mask)
        big.paste(solid, ((32 - icon.width) // 2, (32 - icon.height) // 2))
        indices, palette = quantize(big)
        art += [c_array(f"gRogueIcon{name}Tiles", gba_tiles(indices, 32, 32)),
                c_array(f"gRogueIcon{name}Palette", gba_palette(palette)), ""]
    # The tree icons: all on one strip, quantized together.
    sheet = Image.open(ROOT / "mod_assets" / TREE_SHEET).convert("RGB")
    strip = Image.new("RGB", (32 * len(TREE_ICONS), 32), TRANSPARENT)
    for index, box in enumerate(TREE_ICONS):
        icon = sheet.crop(box)
        icon = icon.resize((icon.width * 2, icon.height * 2), Image.Resampling.NEAREST)
        for y in range(icon.height):
            for x in range(icon.width):
                if sum(icon.getpixel((x, y))) >= 60:
                    strip.putpixel((index * 32 + 2 + x, 2 + y), icon.getpixel((x, y)))
    indices, palette = quantize(strip)
    tiles = bytearray()
    for index in range(len(TREE_ICONS)):
        one = [indices[y * strip.width + index * 32 + x] for y in range(32) for x in range(32)]
        tiles += gba_tiles(one, 32, 32)
    locked = [tuple((r + g + b) // 9 + 12 for _ in range(3)) for r, g, b in palette]
    full = [(min(255, r + 70), min(255, g + 60), min(255, b // 2 + 20)) for r, g, b in palette]
    art += [c_array("gRogueTreeIconTiles", bytes(tiles)), c_array("gRogueTreePalette", gba_palette(palette)),
            c_array("gRogueTreeLockedPalette", gba_palette(locked)), c_array("gRogueTreeFullPalette", gba_palette(full)), ""]
    OUT.write_text("\n".join(art))
    OUT_TABLE.write_text("\n".join(table))
    print(f"wrote {OUT.relative_to(ROOT)} and {OUT_TABLE.relative_to(ROOT)}: {len(CARDS)} cards")


if __name__ == "__main__":
    main()
