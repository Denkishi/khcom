#!/usr/bin/env python3
"""Turn a character's sprite sheet into a boss with a fight of its own.

    build/venv/bin/python tools/rogue_actors.py [Name ...]

Writes src/rogue/rogue_<name>_actor.c for each character and
include/rogue_actor_art.h for all of them. Unlike the heroes of
rogue_sprites.py, who must keep the timing of Sora's animations, a boss is
driven by the mod's own code (src/rogue/rogue_actor.c): each pose is a
picture of its own, loaded when it shows, and a clip is a list of poses with
how long each stays, how far the boss moves while it does and what happens
when it starts. The clips are also written as GIFs, to look at before
playing, in mod_assets/<name>_boss_preview/.
"""
import sys
from pathlib import Path

from PIL import Image, ImageDraw

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import rogue_sprites as rs  # noqa: E402
import sprite_sheet  # noqa: E402

HEADER = ROOT / "include/rogue_actor_art.h"
EVENTS = ["nothing", "hit", "special", "heavy", "blink", "throw", "seek", "cast", "behind", "over", "land", "flash", "heal"]


def P(pose, frames, move=0, lift=0, **event):
    """One step of a clip: a pose, the frames it stays, the pixels a frame the
    boss goes forward and up meanwhile, and what happens as it starts:
      hit=reach     a hit in front, reaching so many pixels
      heavy=reach   the same, half as strong again
      blink=reach   a hit made from beside Sora, wherever the boss was
      throw=MOVE    one of the moves of rogue_moves.c, thrown ahead
      seek=MOVE     the same set round Sora, closing on him one after the other
      cast=MOVE     the same made in front of the boss
      behind=1      the boss is on the far side of Sora, looking back
      over=1        for the next frames the boss is carried over where Sora stands
      land=reach    the boss is on the ground again, and hits all around
      flash=1       the screen flashes
      heal=1        the boss gets a sixth of its HP back
      special=n     what the boss's own code makes of it"""
    kind, arg = next(iter(event.items())) if event else ("nothing", 0)
    return (pose, frames, move, lift, EVENTS.index(kind), f"ROGUE_MOVE_{arg}" if isinstance(arg, str) else arg)


def loop(poses, frames):
    return [P(p, frames) for p in poses]


def row(r, columns, frames):
    return [P(f"{r}.{c}", frames) for c in columns]


SEPHIROTH = dict(
    sheet="sephiroth_mgssj2.png", area=(100, 5290, 0, 0), min_pixels=60, min_height=16, row_overlap=12, max_height=200,
    min_colours=5,
    clips=dict(
        idle=loop(["0.0", "0.1", "0.2", "0.3", "0.4", "0.3", "0.2", "0.1"], 7),
        run=loop(["3.0", "3.1", "3.2", "3.3", "3.4", "3.5", "3.6", "3.7"], 4),
        hurt=[P("35.0", 6), P("35.1", 12)],
        down=[P("36.0", 30)],
        guard=[P("8.0", 20)],
        # Three cuts, stepping in.
        slash=[P("9.0", 8), P("9.1", 5, move=3, hit=70), P("9.2", 5), P("9.3", 5, move=2, hit=60), P("9.4", 5), P("9.5", 4),
               P("9.6", 6, move=2, heavy=80), P("9.7", 10)],
        # A low sweep to one side and the other.
        sweep=[P("10.0", 8), P("10.1", 5, move=2, hit=80), P("10.2", 5), P("10.3", 6, hit=80), P("10.4", 10)],
        # A cut that rises and one that comes down.
        rise=[P("11.0", 8), P("11.2", 4, move=4), P("11.3", 5, hit=60), P("11.4", 5, move=3), P("11.5", 6, heavy=70), P("11.6", 12)],
        # The whole length of the sword, after a step that covers the ground.
        thrust=[P("5.0", 4, move=7), P("5.1", 5, move=7), P("13.0", 5, move=3), P("13.1", 10, heavy=100), P("17.0", 8)],
        # He stands with the sword sheathed; then he is past Sora, who is cut on the way.
        flash=[P("26.0", 26), P("26.1", 3, behind=1), P("26.2", 6, heavy=90), P("26.2", 16)],
        # Up, and down on the point of the sword where Sora stood.
        plunge=[P("6.0", 12, lift=5, over=1), P("27.0", 6, lift=-10), P("27.1", 2, land=44), P("27.1", 4, special=3), P("27.2", 8), P("27.3", 12)],
        # Shadow Flare: the dark gathers round Sora and closes on him.
        flare=[P("28.0", 5), P("28.1", 5), P("28.2", 6), P("29.0", 6), P("29.1", 24, seek="FIREBALL"), P("28.0", 8)],
        # A cut from above that sends a wave along the ground.
        wave=[P("19.0", 12), P("19.1", 4), P("19.2", 12, special=5), P("19.3", 10)],
        # Heartless Angel: he rises and calls it down. Left to finish, it takes all Sora has but one.
        angel=[P("33.0", 6, lift=2, special=6), P("33.1", 6, lift=2), P("33.2", 6, lift=2), P("33.3", 6, lift=2)]
        + loop(["34.0", "34.1", "34.2", "34.3"], 6) * 5 + [P("34.0", 8, special=7), P("33.0", 10, lift=-5)],
        # Eight cuts, each from somewhere else.
        octa=loop(["42.0", "42.1", "42.2", "42.3"], 4) * 2
        + [P("12.0", 4, blink=70), P("12.2", 3), P("12.4", 4, blink=70), P("21.1", 3), P("10.1", 4, blink=80),
           P("9.6", 3), P("11.3", 4, blink=60), P("13.1", 3), P("12.0", 4, blink=70), P("10.3", 3),
           P("12.4", 4, blink=70), P("21.1", 3), P("9.1", 4, blink=70), P("11.5", 8, blink=80), P("11.6", 16)],
        # The one wing, at half his HP.
        wing=[P("38.4", 6), P("38.5", 6), P("38.6", 6), P("38.7", 8), P("38.8", 8), P("38.9", 14, flash=1), P("38.10", 8), P("38.11", 8),
              P("38.12", 8), P("38.13", 12)],
    ),
    # Effects cut from the sheet by hand: box, scale, frames as (turns of 90 degrees, duration).
    fx=dict(Wave=dict(box=(627, 7148, 709, 7409), scale=0.2, frames=[(0, 60)])),
)

# Sora as he is on his second journey, from the sheet the hero of
# rogue_sprites.py is made from too. He throws the Keyblade.
SORA = dict(
    sheet="sora_kh2_ultimate.png", area=(100, 0, 1000, 0), min_pixels=80, min_height=20, row_overlap=10, max_height=200, min_colours=5,
    clips=dict(
        idle=row(0, range(8), 6),
        run=row(1, range(8), 4),
        hurt=[P("25.0", 6), P("25.1", 12)],
        combo=[P("5.0", 6), P("5.1", 4, move=2, hit=50), P("5.2", 4), P("5.3", 4, hit=50), P("5.4", 5), P("6.1", 4),
               P("6.2", 5, move=3, heavy=55), P("6.4", 8)],
        arcs=[P("7.0", 6), P("7.1", 4, move=3, hit=55), P("7.2", 5, hit=55), P("7.3", 4), P("8.3", 5, move=3, heavy=65), P("8.4", 5),
              P("8.5", 8)],
        rising=[P("10.0", 6), P("10.1", 4, move=2, hit=50), P("10.2", 5, heavy=55), P("10.3", 5), P("10.4", 8)],
        # Strike Raid: the Keyblade thrown, which comes back to his hand.
        raid=[P("14.0", 8), P("14.1", 5), P("14.2", 6, throw="RAID"), P("15.0", 30), P("15.2", 6), P("15.3", 8)],
        fire=[P("32.0", 6), P("32.1", 6), P("32.2", 8, seek="FIREBALL"), P("28.4", 16), P("28.0", 6)],
        ice=[P("28.0", 5), P("28.2", 5), P("28.4", 8, throw="NEEDLES"), P("28.5", 10), P("28.6", 6)],
        # Sonic Blade: he is through Sora before the cut shows.
        sonic=[P("24.0", 12), P("24.1", 3, behind=1), P("24.3", 6, heavy=60), P("24.5", 10)],
        # Cure, once, at half his HP.
        cure=[P("28.0", 6), P("28.2", 6), P("28.4", 10, heal=1), P("28.5", 12, flash=1), P("28.6", 8)],
        # The finisher, after that: cuts from every side.
        ars=[P("23.0", 5), P("23.1", 4), P("23.2", 4, blink=55), P("23.3", 4), P("23.4", 4, blink=60), P("23.5", 4), P("23.6", 5, blink=60),
             P("23.9", 4), P("23.10", 5, heavy=60), P("23.14", 10)],
    ),
    fx=dict(
        # The Keyblade as it flies, turning.
        Raid=dict(poses=["14.3", "14.4", "14.5", "14.6", "14.7", "14.8", "14.9", "14.10"], duration=2),
        # A ball of light, for Mickey's pearls and the lights the last Roxas calls.
        Pearl=dict(poses=["16.2"], duration=60),
    ),
)

ROXAS_SHEET = dict(sheet="roxas_sheet.png", area=(100, 0, 1000, 0), min_pixels=80, min_height=20, row_overlap=10, max_height=200,
                   min_colours=5)

# Roxas three times over, as the sheet has him. First as in Twilight Town:
# one Keyblade, and at half his HP the second.
ROXAS = dict(
    ROXAS_SHEET,
    clips=dict(
        idle=row(0, range(8), 6),
        run=row(2, range(8), 4),
        hurt=[P("19.0", 6), P("19.1", 12)],
        slash=[P("7.0", 6), P("7.1", 4, hit=50), P("7.2", 4), P("7.3", 5, hit=50), P("8.1", 4, move=3), P("8.2", 5, heavy=55), P("8.3", 8)],
        spin=[P("9.0", 6), P("9.1", 4, move=2, hit=55), P("9.2", 4), P("9.3", 4, hit=55), P("9.4", 5), P("9.5", 8)],
        upper=[P("10.0", 6), P("10.1", 4), P("10.2", 5, move=3, hit=45), P("10.3", 5, heavy=50), P("10.4", 6), P("10.5", 8)],
        raid=[P("6.0", 8), P("6.2", 5), P("6.3", 6, throw="RAID"), P("6.4", 30), P("6.5", 8)],
        dash=[P("5.0", 4, move=6), P("5.2", 4, move=6), P("5.4", 4, move=6), P("11.2", 4, hit=50), P("11.3", 8)],
        # The second Keyblade comes to his hand.
        dual=[P("42.0", 8), P("42.1", 8), P("42.2", 8), P("42.3", 10, flash=1), P("31.0", 8)],
        flurry=[P("36.0", 4, blink=50), P("36.1", 4), P("36.2", 4, blink=50), P("37.0", 4), P("37.1", 4, blink=50), P("38.1", 4),
                P("38.2", 4, blink=50), P("39.1", 6, heavy=55), P("39.3", 10)],
    ),
)

# In the coat of the Organization, with both Keyblades.
ROXAS_COAT = dict(
    ROXAS_SHEET,
    clips=dict(
        idle=row(53, range(4), 7),
        run=row(57, range(3), 4),
        hurt=[P("48.0", 6), P("48.1", 12)],
        combo=[P("54.3", 5), P("54.5", 4, hit=50), P("54.7", 4), P("54.8", 4, hit=55), P("54.9", 4), P("54.10", 4, hit=60), P("54.11", 4),
               P("54.12", 4, heavy=55), P("54.13", 6), P("54.14", 8)],
        wide=[P("58.3", 6), P("58.4", 4, move=3, hit=60), P("58.5", 5, hit=70), P("58.6", 5), P("58.7", 4, hit=60), P("58.8", 5, heavy=60),
              P("58.9", 8)],
        light=[P("59.0", 8), P("59.1", 4), P("59.2", 5, move=4, heavy=70), P("59.3", 5), P("59.4", 8)],
        dark=[P("59.4", 6), P("59.5", 4, move=3, hit=70), P("59.6", 4), P("59.7", 4, hit=60), P("59.8", 5, heavy=75), P("59.9", 5),
              P("59.10", 8)],
        raid=[P("49.0", 6), P("49.2", 5), P("49.3", 5, throw="RAID"), P("49.4", 30), P("49.7", 8)],
        step=[P("57.0", 12), P("57.1", 3, behind=1), P("58.5", 6, heavy=70), P("58.9", 10)],
        lights=[P("51.0", 6), P("51.1", 8), P("51.2", 20, seek="PEARL"), P("51.0", 8)],
        rage=[P("52.0", 6), P("52.2", 6), P("52.4", 6), P("52.6", 8, flash=1), P("52.8", 10)],
        flurry=[P("58.4", 4, blink=60), P("58.5", 3), P("59.2", 4, blink=70), P("59.3", 3), P("58.7", 4, blink=60), P("58.8", 3),
                P("59.5", 4, blink=70), P("59.6", 3), P("59.8", 6, blink=75), P("59.10", 12)],
    ),
)

# And with the hood up, as he fights at the end.
ROXAS_HOOD = dict(
    ROXAS_SHEET,
    clips=dict(
        idle=row(64, range(4), 7),
        run=row(66, range(8), 3),
        hurt=[P("60.0", 6), P("62.1", 12)],
        combo=[P("65.3", 5), P("65.5", 4, hit=50), P("65.7", 4), P("65.8", 4, hit=55), P("65.9", 4), P("65.10", 4, hit=60), P("65.11", 4),
               P("65.12", 4, heavy=55), P("65.13", 8)],
        arcs=[P("67.0", 6), P("67.1", 4, move=3, hit=70), P("67.2", 4), P("67.3", 4, hit=60), P("67.4", 5, heavy=70), P("67.5", 5),
              P("67.6", 6), P("67.7", 5, heavy=75), P("67.8", 8)],
        # He gathers himself, then goes through Sora turning.
        cyclone=row(73, range(4), 6)
        + [P("68.0", 4, move=4, hit=60), P("68.1", 4, move=4), P("68.2", 4, move=4, hit=60), P("68.3", 4, move=4), P("68.0", 4, move=4, hit=60),
           P("68.1", 4, move=4), P("68.2", 4, move=4, hit=60), P("68.3", 4, heavy=60), P("68.4", 12)],
        wide=[P("70.4", 6), P("70.5", 4, move=3, hit=70), P("70.6", 5), P("70.7", 4, hit=65), P("70.8", 5, heavy=70), P("70.9", 5),
              P("70.12", 4, hit=50), P("70.15", 8)],
        # Pillars of light all around him.
        pillars=[P("75.5", 8), P("75.6", 12), P("76.1", 4, land=60), P("76.1", 8, land=60), P("76.1", 14), P("76.0", 10)],
        lights=[P("75.0", 6), P("75.2", 6), P("75.4", 20, seek="PEARL"), P("75.0", 8)],
        step=[P("66.0", 10), P("66.3", 3, behind=1), P("70.5", 6, heavy=70), P("70.9", 10)],
        rage=row(73, range(4), 6) + [P("73.0", 6, flash=1)] + row(73, range(1, 4), 6),
        flurry=[P("72.1", 4, blink=50), P("72.3", 3), P("72.4", 4, blink=60), P("72.6", 3), P("72.8", 4, blink=55), P("72.10", 3),
                P("72.12", 4, blink=55), P("72.13", 3), P("68.0", 4, blink=60), P("68.2", 4), P("68.3", 6, heavy=60), P("68.4", 12)],
    ),
    fx=dict(Pillar=dict(box=(63, 6778, 95, 6882), scale=0.75, frames=[(0, 40)])),
)

ACTORS = {"Sephiroth": SEPHIROTH, "SoraKh2": SORA, "Roxas": ROXAS, "RoxasCoat": ROXAS_COAT, "RoxasHood": ROXAS_HOOD}


def use(actor):
    rs.SHEET = ROOT / "mod_assets" / actor["sheet"]
    rs.AREA, rs.MIN_PIXELS, rs.MIN_HEIGHT, rs.ROW_OVERLAP = actor["area"], actor["min_pixels"], actor["min_height"], actor["row_overlap"]
    rs.MAX_HEIGHT, rs.MIN_COLOURS = actor.get("max_height", 0), actor.get("min_colours", 0)
    rs.PALETTE = actor.get("palette")
    rs.SHAPES = [(8, 8), (8, 4), (4, 8), (4, 4), (4, 2), (2, 4), (2, 2), (4, 1), (1, 4), (2, 1), (1, 2), (1, 1)]


def feet(poses, name, run=4):
    """Where a pose stands. The lowest thing in it may be the point of a
    sword, so the feet are the lowest row with a stretch of dark pixels side
    by side, which a blade seen at a slant does not have."""
    rows = poses.pixels[name]
    dark = {i for i, (r, g, b) in enumerate(poses.palette) if i and r + g + b < 200}

    def stretches(row):
        start = None
        for x, value in enumerate(list(row) + [0]):
            if value in dark:
                start = x if start is None else start
            elif start is not None:
                if x - start >= run:
                    yield start, x
                start = None

    solid = [y for y, row in enumerate(rows) if any(True for _ in stretches(row))]
    if not solid:
        return len(rows[0]) // 2, len(rows)
    low = max(solid)
    xs = sorted(x for row in rows[max(0, low - 15):low + 1] for a, b in stretches(row) for x in range(a, b))
    return xs[len(xs) // 2], low + 1


def c_bytes(name, data, linkage="static const"):
    lines = "\n".join("    " + ", ".join(f"0x{b:02X}" for b in data[i:i + 16]) + "," for i in range(0, len(data), 16))
    return f"{linkage} u8 {name}[{len(data)}] __attribute__((aligned(4))) = {{\n{lines}\n}};"


def c_palette(name, palette):
    colours = [(r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10) for r, g, b in palette]
    return f"const u16 {name}[16] = {{\n{rs.words(colours, 8)}\n}};"


def effect(name, sheet, spec, sprites=None):
    """An effect as a sprite the moves of rogue_moves.c can throw: tiles, palette, frames, one animation."""
    if "poses" in spec:
        # Sprites of the sheet in turn, as the poses of a clip are.
        key = sprites.background
        crops = {str(i): sprites.crops[pose] for i, pose in enumerate(spec["poses"])}
        spec = dict(spec, frames=[(0, spec["duration"])] * len(crops))
        return effect_code(name, crops, key, spec)
    crop = sheet.crop(spec["box"])
    background = sheet.getpixel((0, 0))
    mask = Image.new("L", crop.size)
    mask.putdata([0 if p == background else 255 for p in crop.getdata()])
    size = (max(1, round(crop.width * spec["scale"])), max(1, round(crop.height * spec["scale"])))
    small = crop.resize(size, Image.LANCZOS)
    small_mask = mask.resize(size, Image.LANCZOS)
    key = (255, 0, 255)
    small.putdata([p if m >= 128 else key for p, m in zip(small.getdata(), small_mask.getdata())])
    small = small.transpose(Image.FLIP_LEFT_RIGHT)
    crops = {}
    for index, (turns, _) in enumerate(spec["frames"]):
        crops[str(index)] = small.rotate(90 * turns, expand=True) if turns else small
    return effect_code(name, crops, key, spec)


def effect_code(name, crops, key, spec):
    names = list(crops)
    rs.PALETTE = None
    poses = rs.Poses(names, crops, key)
    strip = Image.new("RGB", (sum(c.width + 2 for c in crops.values()), max(c.height for c in crops.values())), (64, 128, 128))
    x = 0
    for n in names:
        for py, line in enumerate(poses.pixels[n]):
            for px, value in enumerate(line):
                if value:
                    strip.putpixel((x + px, py), poses.palette[value])
        x += crops[n].width + 2
    folder = ROOT / "mod_assets" / "fx_preview"
    folder.mkdir(exist_ok=True)
    strip.resize((strip.width * 3, strip.height * 3), Image.NEAREST).save(folder / f"{name}.png")
    for n in names:
        poses.anchors[n] = (crops[n].width // 2, crops[n].height // 2)
    oam, block = poses.encode(names)
    out = [c_bytes(f"gRogueFx{name}Tiles", block, "const"), c_palette(f"gRogueFx{name}Palette", poses.palette)]
    for index, frame in enumerate(oam):
        out.append(f"static const u16 sFx{name}Frame{index}[] = {{\n{rs.words(sprite_sheet.frame_words(frame))}\n}};")
    out.append(f"const void* const gRogueFx{name}Frames[] = {{ " + ", ".join(f"sFx{name}Frame{i}" for i in range(len(oam))) + " };")
    values = [0x40, 0x40, len(names)] + [v for i, (_, duration) in enumerate(spec["frames"]) for v in (i, duration)]
    out.append(f"static const u16 sFx{name}Anim[] = {{\n{rs.words(values)}\n}};")
    out.append(f"const void* const gRogueFx{name}Anims[] = {{ sFx{name}Anim }};")
    out.append("")
    declare = [f"extern const u8 gRogueFx{name}Tiles[{len(block)}];", f"extern const u16 gRogueFx{name}Palette[16];",
               f"extern const void* const gRogueFx{name}Frames[];", f"extern const void* const gRogueFx{name}Anims[];"]
    return out, declare


def build(name):
    actor = ACTORS[name]
    use(actor)
    clips = actor["clips"]
    used = list(dict.fromkeys(step[0] for clip in clips.values() for step in clip))
    poses = rs.Poses(used)
    for pose in used:
        poses.anchors[pose] = feet(poses, pose)
    poses.anchors.update(actor.get("anchors", {}))
    out = [f'// Generated by tools/rogue_actors.py from mod_assets/{actor["sheet"]}. Do not edit.',
           '#include "rogue.h"', '#include "anim.h"', '#include "rogue_actor_art.h"', '',
           c_palette(f"gRogue{name}ActorPalette", poses.palette), '',
           "static const u16 sPoseAnim[] = { 0x0040, 0x0040, 0x0001, 0x0000, 0x00FF };",
           "static const void* const sPoseAnims[] = { sPoseAnim };", ""]
    total = 0
    most = 0
    for index, pose in enumerate(used):
        oam, block = poses.encode([pose])
        total += len(block)
        most = max(most, len(block) // 32)
        out.append(c_bytes(f"sTiles{index}", block))
        out.append(f"static const u16 sFrame{index}[] = {{\n{rs.words(sprite_sheet.frame_words(oam[0]))}\n}};")
        out.append(f"static const void* const sFrames{index}[] = {{ sFrame{index} }};")
    out.append("")
    out.append(f"// One for each pose: a single picture, loaded into the boss's tile block when it shows.")
    out.append(f"const AnimDef gRogue{name}Poses[{len(used)}] = {{")
    for index in range(len(used)):
        out.append(f"    {{ (void*)sFrames{index}, (void*)sPoseAnims, (void*)sTiles{index}, 0, {{ 0, 0, 0 }} }},")
    out.append("};")
    out.append("")
    upper = "".join("_" + ch if ch.isupper() and i else ch for i, ch in enumerate(name)).upper()
    declare = [f"// {name}", f"#define ROGUE_{upper}_TILES {most}", "enum {"]
    for clip, steps in clips.items():
        declare.append(f"    ROGUE_{upper}_CLIP_{clip.upper()},")
        out.append(f"static const RogueClipStep sClip_{clip}[] = {{")
        for pose, frames, move, lift, event, arg in steps:
            out.append(f"    {{ {used.index(pose)}, {frames}, {move}, {lift}, {event}, {arg} }},")
        out.append("    { 0, 0, 0, 0, 0, 0 },")
        out.append("};")
    declare += [f"    ROGUE_{upper}_CLIPS", "};"]
    out.append(f"const RogueClipStep* const gRogue{name}Clips[ROGUE_{upper}_CLIPS] = {{")
    out.append("    " + ", ".join(f"sClip_{clip}" for clip in clips) + ",")
    out.append("};")
    out.append("")
    declare += [f"extern const u16 gRogue{name}ActorPalette[16];", f"extern const struct AnimDef gRogue{name}Poses[{len(used)}];",
                f"extern const RogueClipStep* const gRogue{name}Clips[ROGUE_{upper}_CLIPS];"]
    sheet = Image.open(rs.SHEET).convert("RGB")
    for fx, spec in actor.get("fx", {}).items():
        text, extra = effect(fx, sheet, spec, poses)
        out += text
        declare += extra
    (ROOT / f"src/rogue/rogue_{name.lower()}_actor.c").write_text("\n".join(out) + "\n")
    preview(name, poses, clips)
    worst = max(len(poses.pieces(p)) for p in used)
    print(f"{name}: {len(used)} poses, {total // 1024} KiB of tiles, at most {most} tiles and {worst} OBJs a pose")
    return declare


def preview(name, poses, clips):
    folder = ROOT / "mod_assets" / f"{name.lower()}_boss_preview"
    folder.mkdir(exist_ok=True)
    cell, ground = (240, 150), 128
    reel = []
    for label, steps in clips.items():
        frames = []
        x, z = 0, 0
        travel = sum(step[2] * step[1] for step in steps)
        start = cell[0] // 2 - travel // 2 * -1 if travel else cell[0] // 2  # the art faces left: forward is to the left
        for pose, count, move, lift, event, arg in steps:
            for _ in range(count):
                x -= move
                z += lift
                image = Image.new("RGB", cell, (64, 128, 128))
                ImageDraw.Draw(image).line((0, ground, cell[0], ground), fill=(48, 100, 100))
                ax, ay = poses.anchor(pose)
                ox, oy = start + x - ax, ground - z - ay
                for py, row in enumerate(poses.pixels[pose]):
                    for px, value in enumerate(row):
                        if value and 0 <= ox + px < cell[0] and 0 <= oy + py < cell[1]:
                            image.putpixel((ox + px, oy + py), poses.palette[value])
                big = image.resize((cell[0] * 2, cell[1] * 2), Image.NEAREST)
                ImageDraw.Draw(big).text((6, 4), label, fill=(255, 255, 255))
                frames.append(big)
        frames[0].save(folder / f"{label}.gif", save_all=True, append_images=frames[1:], duration=33, loop=0)
        reel += frames * (2 if len(frames) < 70 else 1)
    reel[0].save(folder / "preview.gif", save_all=True, append_images=reel[1:], duration=33, loop=0)


def main():
    names = sys.argv[1:] or list(ACTORS)
    declare = ["// Generated by tools/rogue_actors.py. Do not edit.", "#ifndef GUARD_ROGUE_ACTOR_ART_H", "#define GUARD_ROGUE_ACTOR_ART_H", "",
               '#include "rogue.h"', "", "struct AnimDef;", ""]
    if set(names) != set(ACTORS):
        raise SystemExit("the header lists every character: run without names")
    for name in names:
        declare += build(name) + [""]
    declare.append("#endif")
    HEADER.write_text("\n".join(declare) + "\n")


if __name__ == "__main__":
    main()
