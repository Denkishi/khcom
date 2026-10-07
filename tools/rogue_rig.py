#!/usr/bin/env python3
"""Draw a character in pieces, pose the pieces on a skeleton and write the frames.

    build/venv/bin/python tools/rogue_rig.py

A trial of making a sprite the game does not have, here Roxas, without an
artist: each piece of the body is a small grid of palette letters, a bone
holds each piece by a pivot, and an animation is a few poses (an angle for
each bone) with the frames between them worked out. Writes, in
mod_assets/roxas/: parts.png (the pieces), sheet.png (every frame, one
animation a row) and a GIF of each animation, enlarged, to look at.
"""
import math
from pathlib import Path

from PIL import Image

OUT = Path(__file__).resolve().parents[1] / "mod_assets/roxas"
CELL = (64, 64)
ORIGIN = (36, 50)  # where the hips are in a cell
BACKGROUND = (64, 128, 128)  # the teal the game's sheets use

# Fifteen colours and the transparent one, as a sprite of the game has. The
# outline is a dark blue rather than black, and each material has two or
# three tones, as on Sora's sheets.
PALETTE = {
    ".": None,
    "o": (28, 36, 60),      # outline
    "h": (152, 96, 24),     # hair, dark
    "H": (232, 172, 48),    # hair
    "Y": (255, 236, 128),   # hair, light
    "s": (216, 136, 96),    # skin, shadow
    "S": (255, 212, 168),   # skin
    "W": (248, 248, 248),   # white cloth
    "g": (176, 184, 204),   # white cloth, shadow
    "G": (104, 112, 140),   # grey
    "k": (44, 44, 60),      # black cloth
    "r": (208, 44, 44),     # red
    "b": (48, 96, 216),     # eyes
    "y": (240, 196, 56),    # keyblade guard
    "L": (208, 220, 244),   # keyblade blade
    "c": (204, 192, 164),   # trousers
}

# The pieces, facing left as the game's sprites do. Each is its grid and the
# pivot it turns on, as (x, y) in the grid.
PARTS = {
    "head": ([
        "......o.....oo......",
        ".....oHo...oHHo.oo..",
        "..oo.oHHo.oHYHooHHo.",
        ".oHHooHYHoHYYHHHYHo.",
        ".oHYHHHYYHHYYHHYYHo.",
        "..oHYYHYYYHYYHHYHHo.",
        ".ooHYYYYYYYYHHHHHho.",
        "oHHHYYYHHYYHHHHHHho.",
        "oHHHHHHHHHHHHHhhHho.",
        ".oHHhHHhhHHHhhhhhho.",
        ".ohhSShSShhhhhhhho..",
        "..oSSSSSSSshhhhho...",
        "..oSboSSSSSshhho....",
        "..oSboSSSSSssho.....",
        "..osSSSSSSSsso......",
        "...osSSSSSsso.......",
        "....oosssooo........",
        "......ooo...........",
    ], (8, 16)),
    "torso": ([
        "...ookkoo...",
        "..oWkkkkWo..",
        ".oWWWkrkWWo.",
        ".oWWWWrWWgo.",
        "oWWWWWWWWggo",
        "oWWgWWWWWggo",
        "oWWgWWWWgggo",
        ".oWgWWWWggo.",
        ".okWkWkWkWo.",
        ".oWkWkWkWko.",
        "..occcccco..",
        "...oooooo...",
    ], (6, 10)),
    "upper_arm": ([
        ".ooo.",
        "oWWWo",
        "oWWgo",
        "oWggo",
        ".oSso",
        ".oSso",
        "..oo.",
    ], (2, 1)),
    "forearm": ([
        ".oo..",
        "oSso.",
        "oSso.",
        "okWko",
        "oWkWo",
        "oSSso",
        "oSSso",
        ".ooo.",
    ], (2, 0)),
    "thigh": ([
        ".ooooo.",
        "occccko",
        "occcGko",
        "occcGko",
        "occGGko",
        ".ocGkko",
        "..oooo.",
    ], (3, 1)),
    "shin": ([
        ".oooo.",
        "ocGkko",
        "ocGkko",
        "ocGkko",
        ".oGkko",
        ".okkko",
        "..ooo.",
    ], (3, 0)),
    "foot": ([
        "....oooo..",
        ".oorrkkko.",
        "okrrrkkkko",
        "okkkkkkGGo",
        ".oooooooo.",
    ], (6, 0)),
    # The Kingdom Key, pointing up from the hand that holds it.
    "keyblade": ([
        ".ooooo.",
        "oLLoLLo",
        "oLooLLo",
        ".ooLLo.",
        "..oLLo.",
        "..oLLo.",
        "..oLLo.",
        "..oLLo.",
        "..oLLo.",
        "..oLLo.",
        "..oLLo.",
        "..oLLo.",
        "..oLLo.",
        "..oLLo.",
        "..oLLo.",
        "..oLLo.",
        "..oLLo.",
        ".ooLLoo",
        "oyyyyyo",
        "oyoooyo",
        "oyoGoyo",
        "oyoGoyo",
        "oyyyyyo",
        ".ooooo.",
    ], (3, 20)),
}

# The skeleton: each bone is the piece it carries, its parent, and where on
# the parent's piece its pivot sits. Listed in the order they are drawn, far
# side first.
BONES = [
    ("far_arm", "upper_arm", "torso", (9, 2)),
    ("far_forearm", "forearm", "far_arm", (2, 5)),
    ("far_thigh", "thigh", "hips", (2, 0)),
    ("far_shin", "shin", "far_thigh", (3, 5)),
    ("far_foot", "foot", "far_shin", (3, 5)),
    ("torso", "torso", "hips", (0, 0)),
    ("near_thigh", "thigh", "hips", (-2, 0)),
    ("near_shin", "shin", "near_thigh", (3, 5)),
    ("near_foot", "foot", "near_shin", (3, 5)),
    ("head", "head", "torso", (5, 1)),
    ("near_arm", "upper_arm", "torso", (2, 2)),
    ("keyblade", "keyblade", "near_forearm", (2, 6)),
    ("near_forearm", "forearm", "near_arm", (2, 5)),
]
# Bones whose parent is drawn after them need the parent's place first.
ORDER = ["torso", "head", "far_arm", "far_forearm", "near_arm", "near_forearm", "keyblade", "far_thigh", "far_shin", "far_foot",
         "near_thigh", "near_shin", "near_foot"]

# Poses: degrees for each bone, clockwise on the screen, relative to its
# parent; "hips" is the whole body's (x, y) shift. A bone left out is at 0.
REST = {"near_arm": 20, "near_forearm": 40, "keyblade": -100, "far_arm": -15, "far_forearm": 20, "near_thigh": 12, "near_shin": -10,
        "far_thigh": -14, "far_shin": 6}


def pose(**changes):
    out = dict(REST)
    out.update(changes)
    return out


# Each animation: a list of (pose, frames to reach the next pose); it loops.
ANIMATIONS = {
    "idle": [
        (pose(), 5),
        (pose(hips=(0, 1), torso=2, head=-2, near_arm=24, near_forearm=44, near_thigh=16, near_shin=-18, far_thigh=-18, far_shin=14), 5),
    ],
    "run": [
        (pose(torso=10, head=-6, near_thigh=55, near_shin=-20, far_thigh=-45, far_shin=-60, near_arm=-40, near_forearm=60, far_arm=45,
              far_forearm=50, keyblade=-70), 4),
        (pose(hips=(0, -2), torso=10, head=-6, near_thigh=5, near_shin=-50, far_thigh=5, far_shin=-10, near_arm=0, near_forearm=60,
              far_arm=0, far_forearm=50, keyblade=-80), 4),
        (pose(torso=10, head=-6, near_thigh=-45, near_shin=-60, far_thigh=55, far_shin=-20, near_arm=40, near_forearm=50, far_arm=-40,
              far_forearm=60, keyblade=-90), 4),
        (pose(hips=(0, -2), torso=10, head=-6, near_thigh=5, near_shin=-10, far_thigh=5, far_shin=-50, near_arm=0, near_forearm=60,
              far_arm=0, far_forearm=50, keyblade=-80), 4),
    ],
    # The swing: the blade goes up behind the head, comes down in front and
    # stays low for a moment. In the hand it lies along the arm (180) here,
    # where at rest it is held across.
    "swing": [
        (pose(torso=-10, head=6, near_arm=-200, near_forearm=-20, keyblade=170, far_arm=-40, near_thigh=20, far_thigh=-25), 3),
        (pose(torso=12, head=-8, near_arm=95, near_forearm=5, keyblade=185, far_arm=30, near_thigh=40, near_shin=-30, far_thigh=-35,
              far_shin=10, hips=(-2, 1)), 2),
        (pose(torso=18, head=-10, near_arm=55, near_forearm=10, keyblade=195, far_arm=40, near_thigh=44, near_shin=-36, far_thigh=-38,
              far_shin=12, hips=(-3, 2)), 4),
        (pose(), 3),
    ],
    "hurt": [
        (pose(torso=-18, head=14, near_arm=-60, near_forearm=-30, far_arm=-70, far_forearm=-20, near_thigh=-10, far_thigh=-30,
              hips=(3, 0), keyblade=-100), 4),
        (pose(torso=-10, head=8, near_arm=-30, far_arm=-40, hips=(2, 0), keyblade=-100), 4),
    ],
}


def image_of(rows):
    image = Image.new("RGBA", (len(rows[0]), len(rows)), (0, 0, 0, 0))
    for y, row in enumerate(rows):
        if len(row) != len(rows[0]):
            raise SystemExit(f"a row of a piece is {len(row)} wide, the first is {len(rows[0])}: {row}")
        for x, letter in enumerate(row):
            if PALETTE[letter] is not None:
                image.putpixel((x, y), PALETTE[letter] + (255,))
    return image


IMAGES = {name: image_of(rows) for name, (rows, _pivot) in PARTS.items()}


def place(pose_):
    """Where each bone's pivot is and how far it is turned, from the pose."""
    piece = {name: part for name, part, _parent, _at in BONES}
    parent = {name: parent_ for name, _part, parent_, _at in BONES}
    at = {name: at_ for name, _part, _parent, at_ in BONES}
    shift = pose_.get("hips", (0, 0))
    world = {"hips": (ORIGIN[0] + shift[0], ORIGIN[1] + shift[1], 0.0)}
    for name in ORDER:
        px, py, angle = world[parent[name]]
        ax, ay = at[name]
        if parent[name] != "hips":
            pivot = PARTS[piece[parent[name]]][1]
            ax, ay = ax - pivot[0], ay - pivot[1]
        cos, sin = math.cos(math.radians(angle)), math.sin(math.radians(angle))
        world[name] = (px + ax * cos - ay * sin, py + ax * sin + ay * cos, angle + pose_.get(name, 0))
    return world, piece


def draw(pose_):
    """One frame: every piece turned on its pivot and laid down, far side first."""
    world, piece = place(pose_)
    frame = Image.new("RGBA", CELL, (0, 0, 0, 0))
    for name, _part, _parent, _at in BONES:
        image = IMAGES[piece[name]]
        pivot = PARTS[piece[name]][1]
        x0, y0, angle = world[name]
        cos, sin = math.cos(math.radians(angle)), math.sin(math.radians(angle))
        # Each pixel of the frame asks the piece what is there: no holes.
        reach = max(image.size) + 2
        for y in range(int(y0) - reach, int(y0) + reach + 1):
            for x in range(int(x0) - reach, int(x0) + reach + 1):
                if not (0 <= x < CELL[0] and 0 <= y < CELL[1]):
                    continue
                dx, dy = x + 0.5 - x0, y + 0.5 - y0
                sx = dx * cos + dy * sin + pivot[0] + 0.5
                sy = -dx * sin + dy * cos + pivot[1] + 0.5
                if 0 <= sx < image.width and 0 <= sy < image.height:
                    pixel = image.getpixel((int(sx), int(sy)))
                    if pixel[3]:
                        frame.putpixel((x, y), pixel)
    return frame


def between(a, b, t):
    out = {}
    for key in set(a) | set(b):
        if key == "hips":
            ha, hb = a.get("hips", (0, 0)), b.get("hips", (0, 0))
            out["hips"] = (round(ha[0] + (hb[0] - ha[0]) * t), round(ha[1] + (hb[1] - ha[1]) * t))
        else:
            out[key] = a.get(key, 0) + (b.get(key, 0) - a.get(key, 0)) * t
    return out


def frames_of(name, step=2):
    """The animation's frames, one every `step` sixtieths of a second."""
    keys = ANIMATIONS[name]
    out = []
    for index, (pose_, length) in enumerate(keys):
        following = keys[(index + 1) % len(keys)][0]
        for i in range(0, length * 2, step):
            out.append(draw(between(pose_, following, i / (length * 2))))
    return out


def flat(frame):
    image = Image.new("RGB", frame.size, BACKGROUND)
    image.paste(frame, (0, 0), frame)
    return image


def main():
    OUT.mkdir(parents=True, exist_ok=True)
    parts = Image.new("RGB", (sum(i.width + 2 for i in IMAGES.values()) + 2, max(i.height for i in IMAGES.values()) + 4), BACKGROUND)
    x = 2
    for image in IMAGES.values():
        parts.paste(image, (x, 2), image)
        x += image.width + 2
    parts.resize((parts.width * 6, parts.height * 6), Image.NEAREST).save(OUT / "parts.png")
    rows = {name: frames_of(name) for name in ANIMATIONS}
    sheet = Image.new("RGB", (CELL[0] * max(len(r) for r in rows.values()), CELL[1] * len(rows)), BACKGROUND)
    for row, frames in enumerate(rows.values()):
        for column, frame in enumerate(frames):
            sheet.paste(flat(frame), (column * CELL[0], row * CELL[1]))
    sheet.save(OUT / "sheet.png")
    for name, frames in rows.items():
        big = [flat(f).resize((CELL[0] * 4, CELL[1] * 4), Image.NEAREST) for f in frames]
        big[0].save(OUT / f"{name}.gif", save_all=True, append_images=big[1:], duration=66, loop=0)
    print(f"wrote {OUT}: {', '.join(f'{name} {len(frames)}' for name, frames in rows.items())} frames")


if __name__ == "__main__":
    main()
