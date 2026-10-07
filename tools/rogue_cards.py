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
]


def symbol_offsets():
    text = MAP.read_text()
    return {name: int(addr, 16) - 0x08000000 for addr, name in re.findall(r"^\s+0x(0[89][0-9a-f]{6})\s+(\w+)$", text, re.M)}


def base_cards():
    """The EU symbols and the numbers of the first card of every original kind."""
    entries = CATALOG.read_text().split("\n    {\n")
    entries[0] = entries[0].lstrip(" {\n")
    bases = {}
    for kind in range(45):
        entry = entries[kind * 10]
        symbols = re.search(r"#elif defined\(VERSION_EU\)\n(.*?)\n#endif", entry, re.S).group(1)
        symbols = [x.strip().lstrip("&") for x in symbols.split(",") if x.strip()]
        numbers = " ".join(entry.split("#endif")[-1].split())
        fields = re.match(r"(\d+), (0x[0-9a-fA-F]+), \d+, \{0, 0, 0\}, (0x[0-9a-fA-F]+), (\d+), (\d+), 0, (\d+), \{(.*?)\}", numbers)
        bases[kind] = (symbols, fields.groups())
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
    for name, italian, sheet, box, base, cp_bonus in CARDS:
        (frame, _tiles, _palette, _name, small_frame, small_tiles, small_palette), fields = bases[base]
        index, flags, action, group, kind_type, cp, trailer = fields
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
    table += ["", f"#define ROGUE_CARD_TABLE_KINDS {len(CARDS)}", ""]
    OUT.write_text("\n".join(art))
    OUT_TABLE.write_text("\n".join(table))
    print(f"wrote {OUT.relative_to(ROOT)} and {OUT_TABLE.relative_to(ROOT)}: {len(CARDS)} cards")


if __name__ == "__main__":
    main()
