#!/usr/bin/env python3
"""Turn the custom Mickey sheet into a battle sprite set that stands in for Sora's.

    build/venv/bin/python tools/rogue_sprites.py

Writes src/rogue/rogue_mickey_art.c. Sora's code reads the frame an animation
is on and waits for it to finish, so Mickey gets one animation for each of
Sora's with the same number of frames and the same durations; only the
pictures differ. The pictures of an animation load into Sora's tile block, so
each animation uses as many poses as fit there. Needs the original ROM in
roms/ and a built link map.
"""
import json
import re
import struct
import sys
from pathlib import Path

from PIL import Image, ImageDraw

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import sprite_sheet  # noqa: E402

BASEROM = ROOT / "roms/B8CP.gba"
MAP = ROOT / "build/eu/com_eu.map"
SOURCE = ROOT / "src/btl/btl.c"
FIELD_SOURCE = ROOT / "src/map/fld.c"
BLOCK_TILES = 100  # Sora's tile block, 0xC80 bytes
HUB_TILES = 40  # the hub's tile block for the hero, 0x500 bytes
HUB_WALK_FRAMES = 10
SHAPES = [(4, 4), (4, 2), (2, 4), (2, 2), (4, 1), (1, 4), (2, 1), (1, 2), (1, 1)]

# The characters. For each: its sheet and how to read it (the area the
# sprites are in as top, bottom, right edge and, for a sheet of two columns,
# where the second starts; the least a sprite is, in pixels and in height;
# how much two sprites of a row overlap in height), where its face for the
# HP bar is, and its poses, as row.column of the sheet's sprites.
CHARACTERS = {
    "Mickey": dict(
        sheet="mickey_kh2.png", area=(385, 0, 0, 365), min_pixels=40, min_height=0, row_overlap=8, face=(6, 6, 56, 56),
        idle=["13.0"], run=["7.0", "7.2", "7.4", "7.6"], rise=["11.6"], fall=["7.5"], land=["8.2"],
        cast=["13.0", "10.1", "11.7", "10.1"], hurt=["5.6"], down=["5.6", "5.4"], rise_up=["5.4", "13.0"], dodge=["7.4", "7.2"],
        hub_stand=["2.0"], hub_walk=["4.1", "4.5"], field_jump=["11.6"], field_swing=["8.4"],
        swings=[["13.0", "8.3", "8.4", "8.5"], ["9.1", "9.4", "9.5"], ["10.2", "11.5", "11.3", "11.1"], ["7.6", "7.3", "9.3"],
                ["11.7", "11.4", "8.2"], ["12.6", "12.5", "12.7"], ["10.0", "8.4", "8.6"]],
    ),
    # A whole set in the game's own style, made from Sora's: nearly every
    # animation of his has its frames here.
    "Roxas": dict(
        sheet="roxas_sheet.png", area=(100, 2150, 1000, 0), min_pixels=80, min_height=20, row_overlap=10, face="0.8",
        idle=["0.0", "0.2", "0.4", "0.6"], run=["2.0", "2.2", "2.4", "2.6"], rise=["4.1"], fall=["6.0"], land=["6.3"],
        cast=["27.0", "27.2", "27.3", "27.5"], hurt=["25.1"], down=["25.3", "25.6"], rise_up=["25.8", "0.0"], dodge=["7.0", "7.2"],
        hub_stand=["0.8"], hub_walk=["3.0", "3.4"], field_jump=["4.1"], field_swing=["9.2"],
        swings=[["9.0", "9.2", "9.4", "9.5"], ["10.0", "10.2", "10.3"], ["11.0", "11.2", "11.4", "11.6"], ["19.0", "19.1", "19.3"],
                ["12.0", "12.2", "12.4", "12.5"], ["13.0", "13.2", "13.4", "13.5"], ["14.0", "14.2", "14.4", "14.6"]],
    ),
}


def use(name):
    """Makes one character the one the rest of the tool works on."""
    global PREFIX, SHEET, OUT, AREA, MIN_PIXELS, MIN_HEIGHT, ROW_OVERLAP, FACE
    global IDLE, RUN, RISE, FALL, LAND, CAST, HURT, DOWN, RISE_UP, DODGE, HUB_STAND, HUB_WALK, FIELD_JUMP, FIELD_SWING, SWINGS
    c = CHARACTERS[name]
    PREFIX = name
    SHEET = ROOT / "mod_assets" / c["sheet"]
    OUT = ROOT / f"src/rogue/rogue_{name.lower()}_art.c"
    AREA, MIN_PIXELS, MIN_HEIGHT, ROW_OVERLAP, FACE = c["area"], c["min_pixels"], c["min_height"], c["row_overlap"], c["face"]
    IDLE, RUN, RISE, FALL, LAND, CAST = c["idle"], c["run"], c["rise"], c["fall"], c["land"], c["cast"]
    HURT, DOWN, RISE_UP, DODGE = c["hurt"], c["down"], c["rise_up"], c["dodge"]
    HUB_STAND, HUB_WALK, FIELD_JUMP, FIELD_SWING, SWINGS = c["hub_stand"], c["hub_walk"], c["field_jump"], c["field_swing"], c["swings"]


def battle_poses(index):
    """The poses for one of the 77 entries of gBtlSoraAnimDefs."""
    if index <= 1:
        return IDLE
    if index <= 36:
        return SWINGS[(index - 2) // 5]
    if index in (38, 39, 40, 41):
        return DODGE
    if index == 42 or 47 <= index <= 50:
        return CAST
    if index == 43 or index == 51:
        return HURT
    if index in (44, 45):
        return DOWN
    if index == 46:
        return RISE_UP
    return SWINGS[index % len(SWINGS)]


def field_poses(index):
    """The poses for one of the rows of gUnk_0813C89C, Sora in the rooms of the map."""
    if index == 0:
        return HUB_STAND
    if index in (1, 2):
        return HUB_WALK
    if 3 <= index <= 7:
        return FIELD_JUMP
    if 9 <= index <= 11:
        return FIELD_SWING
    return HUB_STAND


def direction_poses(index):
    """The poses for one of the rows of gUnk_0813BEFC: running, then a jump."""
    return [RUN, RISE, RISE, FALL, FALL, LAND][index]


def segment(image):
    """The sprites of the sheet as rows of boxes; in a sheet of two columns, the left column first."""
    width, height = image.size
    px = image.load()
    background = px[0, 0]
    top, bottom, right, split = AREA
    bottom = bottom or height
    right = right or width
    seen = set()
    boxes = []
    for y in range(top, bottom):
        for x in range(right):
            if (x, y) in seen or px[x, y] == background:
                continue
            stack = [(x, y)]
            seen.add((x, y))
            x0 = x1 = x
            y0 = y1 = y
            count = 0
            while stack:
                cx, cy = stack.pop()
                count += 1
                x0, x1, y0, y1 = min(x0, cx), max(x1, cx), min(y0, cy), max(y1, cy)
                for dx in range(-2, 3):
                    for dy in range(-2, 3):
                        nx, ny = cx + dx, cy + dy
                        if 0 <= nx < right and top <= ny < bottom and (nx, ny) not in seen and px[nx, ny] != background:
                            seen.add((nx, ny))
                            stack.append((nx, ny))
            if count > MIN_PIXELS and y1 - y0 >= MIN_HEIGHT:
                boxes.append((x0, y0, x1 + 1, y1 + 1))
    rows = []
    sides = ([b for b in boxes if b[0] < split], [b for b in boxes if b[0] >= split]) if split else (boxes,)
    for side in sides:
        side.sort(key=lambda b: b[3])
        group = []
        for box in side:
            anchor = group[-1][-1] if group and split else group[-1][0] if group else None
            if group and box[1] < anchor[3] - ROW_OVERLAP and (not split or abs(box[3] - group[-1][0][3]) < 30):
                group[-1].append(box)
            else:
                group.append([box])
        rows += [sorted(row) for row in group]
    return rows, background


class Poses:
    def __init__(self):
        image = Image.open(SHEET).convert("RGB")
        self.rows, background = segment(image)
        crops = {}
        for r, row in enumerate(self.rows):
            for c, box in enumerate(row):
                crops[f"{r}.{c}"] = image.crop(box).transpose(Image.FLIP_LEFT_RIGHT)  # Sora's sprites face left
        used = sorted({name for poses in [IDLE, RUN, RISE, FALL, LAND, CAST, HURT, DOWN, RISE_UP, DODGE, HUB_STAND, HUB_WALK,
                                          FIELD_JUMP, FIELD_SWING] + SWINGS for name in poses})
        self.crops = crops
        strip = Image.new("RGB", (sum(crops[n].width for n in used), max(crops[n].height for n in used)), background)
        x = 0
        for name in used:
            strip.paste(crops[name], (x, 0))
            x += crops[name].width
        # Fifteen colours and the transparent one, which the background takes.
        quantized = strip.quantize(16, method=Image.MEDIANCUT, dither=Image.NONE)
        palette = quantized.getpalette()[:48]
        colours = [tuple(palette[i * 3:i * 3 + 3]) for i in range(16)]
        clear = min(range(16), key=lambda i: sum((a - b) ** 2 for a, b in zip(colours[i], background)))
        order = [clear] + [i for i in range(16) if i != clear]
        self.palette = [colours[i] for i in order]
        remap = {old: new for new, old in enumerate(order)}
        self.pixels = {}
        x = 0
        data = quantized.load()
        for name in used:
            crop = crops[name]
            rows = [[0 if crop.getpixel((cx, cy)) == background else remap[data[x + cx, cy]] or self.darkest() for cx in range(crop.width)]
                    for cy in range(crop.height)]
            self.pixels[name] = rows
            x += crop.width

    def darkest(self):
        return min(range(1, 16), key=lambda i: sum(self.palette[i]))

    def anchor(self, name):
        """Where the pose stands: under its feet, which are black as nothing else low in it is."""
        rows = self.pixels[name]
        black = self.darkest()
        low = max(y for y, row in enumerate(rows) if black in row)
        xs = [x for row in rows[max(0, low - 7):low + 1] for x, v in enumerate(row) if v == black]
        return sum(xs) // len(xs), low + 1

    def pieces(self, name):
        """The pose cut into OBJs on an 8x8 grid, leaving out the empty cells."""
        rows = self.pixels[name]
        ax, ay = self.anchor(name)
        height, width = len(rows), len(rows[0])
        cols, lines = (width + 7) // 8, (height + 7) // 8
        full = {(cx, cy) for cy in range(lines) for cx in range(cols)
                if any(rows[y][x] for y in range(cy * 8, min(cy * 8 + 8, height)) for x in range(cx * 8, min(cx * 8 + 8, width)))}
        pieces = []
        for w, h in SHAPES:
            for cy in range(lines):
                for cx in range(cols):
                    cells = {(cx + i, cy + j) for i in range(w) for j in range(h)}
                    if cells <= full:
                        full -= cells
                        pieces.append({"w": w * 8, "h": h * 8, "x": cx * 8 - ax, "y": cy * 8 - ay, "hflip": 0, "vflip": 0, "pal": 0,
                                       "prio": 0, "layer": 0})
        return pieces

    def tiles(self, name):
        return sum(p["w"] * p["h"] // 64 for p in self.pieces(name))

    def encode(self, names):
        """The OAM frames and the tile block for a set of poses."""
        frames = [self.pieces(name) for name in names]
        everything = [p for frame in frames for p in frame]
        x0 = min(p["x"] for p in everything)
        y0 = min(p["y"] for p in everything)
        layout = {"cell": [max(p["x"] + p["w"] for p in everything) - x0, max(p["y"] + p["h"] for p in everything) - y0],
                  "anchor": [-x0, -y0], "columns": len(frames), "frames": frames}
        sheet = sprite_sheet.Sheet(layout)
        layer = sheet.blank()
        for index, name in enumerate(names):
            rows = self.pixels[name]
            ax, ay = self.anchor(name)
            ox, oy = sheet.origin(index)
            for y, row in enumerate(rows):
                for x, value in enumerate(row):
                    layer[(oy + y - ay) * sheet.width + ox + x - ax] = value
        return sprite_sheet.encode(layout, [layer])


def fit(poses, names, block=BLOCK_TILES):
    """As many of the poses, the first and the last among them, as fit the tile block."""
    names = list(names)
    while sum(poses.tiles(n) for n in dict.fromkeys(names)) > block and len(names) > 1:
        names.pop(len(names) // 2)
    if sum(poses.tiles(n) for n in dict.fromkeys(names)) > block:
        raise SystemExit(f"pose {names[0]} alone does not fit the tile block")
    return names


def sora_animations():
    """The frames, as (picture, duration), of each entry of Sora's two tables."""
    text = MAP.read_text()
    symbols = {name: int(addr, 16) - 0x08000000 for addr, name in re.findall(r"^\s+0x(0[89][0-9a-f]{6})\s+(\w+)$", text, re.M)}
    rom = BASEROM.read_bytes()
    source = SOURCE.read_text()
    tables = []
    for name in ("gBtlSoraAnimDefs", "gUnk_0813BEFC", "gUnk_0813C89C"):
        if name == "gUnk_0813C89C":
            source = FIELD_SOURCE.read_text()
        body = source[source.index(f"const AnimDef {name}"):]
        body = body[:body.index("\n};")]
        entries = []
        for anims, anim_id in re.findall(r"\{ g\w+Frames, (g\w+Anims), g\w+Tiles, (\d+),", body):
            header = struct.unpack_from("<I", rom, symbols[anims] + 4 * int(anim_id))[0] - 0x08000000
            first, second, count = struct.unpack_from("<3H", rom, header)
            frames = [struct.unpack_from("<2H", rom, header + 6 + 4 * i) for i in range(count)]
            entries.append((first, second, frames))
        tables.append(entries)
    if len(tables[0]) != 77 or len(tables[1]) != 30 or len(tables[2]) != 75:
        raise SystemExit("Sora's animation tables are not the size expected")
    return tables


def words(values, per_line=12):
    lines = []
    for i in range(0, len(values), per_line):
        lines.append("    " + ", ".join(f"0x{v:04X}" for v in values[i:i + per_line]) + ",")
    return "\n".join(lines)


def build():
    poses = Poses()
    battle, directions, field = sora_animations()
    out = ['// Generated by tools/rogue_sprites.py from mod_assets/mickey_kh2.png. Do not edit.',
           '#include "rogue.h"', '#include "anim.h"', '']
    colours = [(r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10) for r, g, b in poses.palette]
    out += ["const u16 gRogueMickeyPalette[16] = {", words(colours, 8), "};", ""]
    sets = {}
    total = 0

    def sprite_set(names):
        nonlocal total
        key = tuple(names)
        if key not in sets:
            oam, block = poses.encode(names)
            number = len(sets)
            sets[key] = number
            total += len(block)
            out.append(f"static const u8 sTiles{number}[] __attribute__((aligned(4))) = {{")
            out.append("\n".join("    " + ", ".join(f"0x{b:02X}" for b in block[i:i + 16]) + "," for i in range(0, len(block), 16)))
            out.append("};")
            for index, frame in enumerate(oam):
                out.append(f"static const u16 sSet{number}Frame{index}[] = {{")
                out.append(words(sprite_sheet.frame_words(frame)))
                out.append("};")
            out.append(f"static const void* const sSet{number}Frames[] = {{ "
                       + ", ".join(f"sSet{number}Frame{i}" for i in range(len(oam))) + " };")
            out.append("")
        return sets[key]

    def table(label, entries, choose, block=BLOCK_TILES):
        defs = []
        for index, (first, second, frames) in enumerate(entries):
            names = fit(poses, choose(index), block)
            unique = list(dict.fromkeys(names))
            number = sprite_set(unique)
            pictures = list(dict.fromkeys(picture for picture, _ in frames))
            # Sora's pictures in the order they first show, spread over the poses.
            spread = {}
            for position, picture in enumerate(pictures):
                step = position * (len(names) - 1) // (len(pictures) - 1) if len(pictures) > 1 else 0
                spread[picture] = unique.index(names[min(step, len(names) - 1)])
            values = [first, second, len(frames)] + [v for picture, duration in frames for v in (spread[picture], duration)]
            out.append(f"static const u16 s{label}Anim{index}[] = {{")
            out.append(words(values))
            out.append("};")
            defs.append(number)
        out.append(f"static const void* const s{label}Anims[] = {{ " + ", ".join(f"s{label}Anim{i}" for i in range(len(entries))) + " };")
        out.append("")
        return defs

    battle_sets = table("Battle", battle, battle_poses)
    direction_sets = table("Direction", directions, lambda index: direction_poses(index // 5))
    field_sets = table("Field", field, lambda index: field_poses(index // 5), HUB_TILES)
    out.append("// One for each entry of gUnk_0813C89C, Sora in the rooms of the map.")
    out.append(f"const AnimDef gRogueMickeyFieldDefs[{len(field)}] = {{")
    for index, number in enumerate(field_sets):
        out.append(f"    {{ (void*)sSet{number}Frames, (void*)sFieldAnims, (void*)sTiles{number}, {index}, {{ 0, 0, 0 }} }},")
    out.append("};")
    out.append("")
    out.append("// One for each entry of gBtlSoraAnimDefs.")
    out.append(f"const AnimDef gRogueMickeyAnimDefs[{len(battle)}] = {{")
    for index, number in enumerate(battle_sets):
        out.append(f"    {{ (void*)sSet{number}Frames, (void*)sBattleAnims, (void*)sTiles{number}, {index}, {{ 0, 0, 0 }} }},")
    out.append("};")
    out.append("")
    out.append("// One for each entry of gUnk_0813BEFC, Sora's running and jumping in five directions.")
    out.append(f"const AnimDef gRogueMickeyDirectionDefs[{len(directions)}] = {{")
    for index, number in enumerate(direction_sets):
        out.append(f"    {{ (void*)sSet{number}Frames, (void*)sDirectionAnims, (void*)sTiles{number}, {index}, {{ 0, 0, 0 }} }},")
    out.append("};")
    # The hub's own two: standing, and a walk of its poses in turn.
    first, second = battle[0][0], battle[0][1]
    hub = []
    for index, names in enumerate((HUB_STAND, HUB_WALK)):
        names = fit(poses, names, HUB_TILES)
        hub.append(sprite_set(names))
        values = [first, second, len(names)] + [v for i in range(len(names)) for v in (i, HUB_WALK_FRAMES)]
        out.append(f"static const u16 sHubAnim{index}[] = {{")
        out.append(words(values))
        out.append("};")
    out.append("static const void* const sHubAnims[] = { sHubAnim0, sHubAnim1 };")
    out.append("")
    out.append("// Standing and walking in the hub.")
    out.append("const AnimDef gRogueMickeyHubDefs[2] = {")
    for index, number in enumerate(hub):
        out.append(f"    {{ (void*)sSet{number}Frames, (void*)sHubAnims, (void*)sTiles{number}, {index}, {{ 0, 0, 0 }} }},")
    out.append("};")
    # The face in the corner of the battle screen: the first of the sheet's
    # portraits, shrunk into the 32x32 piece of Sora's (his second, small piece
    # is left empty). It has a palette of its own.
    sheet = Image.open(SHEET).convert("RGB")
    if isinstance(FACE, str):
        # No portrait on the sheet: the head of a pose, twice its size.
        crop = poses.crops[FACE]
        head = Image.new("RGB", (16, 16), sheet.getpixel((0, 0)))
        head.paste(crop.crop((0, 3, min(crop.width, 16), 19)), ((16 - min(crop.width, 16)) // 2, 0))
        face = head.resize((32, 32), Image.NEAREST)
    else:
        face = sheet.crop(FACE).resize((32, 32), Image.LANCZOS)
    quantized = face.quantize(15, method=Image.MEDIANCUT, dither=Image.NONE)
    flat = quantized.getpalette()[:45]
    face_palette = [(0, 0, 0)] + [tuple(flat[i * 3:i * 3 + 3]) for i in range(15)]
    data = quantized.load()
    white = sheet.getpixel((0, 0))
    rows = [[0 if sum(abs(a - b) for a, b in zip(face.getpixel((x, y)), white)) < 24 else data[x, y] + 1 for x in range(32)]
            for y in range(32)]
    tiles = sprite_sheet.rows_tiles([bytes(row) for row in rows], 32, 32) + bytes(4 * 32)
    out.append("// The portrait by the HP bar.")
    out.append(f"const u8 gRogueMickeyFaceTiles[{len(tiles)}] __attribute__((aligned(4))) = {{")
    out.append("\n".join("    " + ", ".join(f"0x{b:02X}" for b in tiles[i:i + 16]) + "," for i in range(0, len(tiles), 16)))
    out.append("};")
    colours = [(r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10) for r, g, b in face_palette]
    out += ["const u16 gRogueMickeyFacePalette[16] = {", words(colours, 8), "};", ""]
    # The names in the text above are Mickey's, the first this was written for.
    OUT.write_text(("\n".join(out) + "\n").replace("gRogueMickey", "gRogue" + PREFIX).replace("mickey_kh2.png", SHEET.name))
    preview(poses)
    worst = max(len(poses.pieces(name)) for name in poses.pixels)
    print(f"{PREFIX}: {len(sets)} sprite sets, {total // 1024} KiB of tiles, at most {worst} OBJs a pose")


def preview(poses):
    """GIFs of the character's poses in turn, as the game will show them: to look at before playing."""
    folder = ROOT / "mod_assets" / f"{PREFIX.lower()}_preview"
    folder.mkdir(exist_ok=True)
    cell, origin = (96, 80), (48, 66)
    groups = [("idle", IDLE), ("run", RUN), ("jump", RISE + FALL + LAND), ("cast", CAST), ("hurt", HURT + DOWN + RISE_UP),
              ("dodge", DODGE), ("hub", HUB_STAND + HUB_WALK)] + [(f"swing{i + 1}", swing) for i, swing in enumerate(SWINGS)]
    reel = []
    for label, names in groups:
        frames = []
        for name in names:
            image = Image.new("RGB", cell, (64, 128, 128))
            ax, ay = poses.anchor(name)
            for y, row in enumerate(poses.pixels[name]):
                for x, value in enumerate(row):
                    if value and 0 <= origin[0] + x - ax < cell[0] and 0 <= origin[1] + y - ay < cell[1]:
                        image.putpixel((origin[0] + x - ax, origin[1] + y - ay), poses.palette[value])
            big = image.resize((cell[0] * 4, cell[1] * 4), Image.NEAREST)
            ImageDraw.Draw(big).text((6, 4), label, fill=(255, 255, 255))
            frames += [big] * 2
        frames[0].save(folder / f"{label}.gif", save_all=True, append_images=frames[1:], duration=70, loop=0)
        reel += frames * (3 if len(frames) < 8 else 2)
    reel[0].save(folder / "preview.gif", save_all=True, append_images=reel[1:], duration=70, loop=0)
    return folder


def main():
    for name in CHARACTERS:
        use(name)
        build()


if __name__ == "__main__":
    main()
