#!/usr/bin/env python3
"""Pose a sprite that comes in pieces on a skeleton and write its frames.

    build/venv/bin/python tools/rogue_rig.py

The sheet in mod_assets/sephiroth_ffrk.png is a figure cut into pieces, with
the whole figure under them. The pieces are found on the sheet, each is
looked for on the whole figure to learn where it goes, and they are grouped
into bones that turn on pivots. An animation is a few poses, an angle and a
shift for each bone, with the frames between them worked out. Writes, in
mod_assets/sephiroth/: rest.png (the figure put back together, to compare
with the sheet's), sheet.png (every frame, an animation a row) and a GIF of
each animation, enlarged.
"""
import math
from pathlib import Path

import numpy as np
from PIL import Image

ROOT = Path(__file__).resolve().parents[1]
SHEET = ROOT / "mod_assets/sephiroth_ffrk.png"
OUT = ROOT / "mod_assets/sephiroth"
CELL = (176, 128)
ORIGIN = (60, 34)  # where the whole figure's top left corner goes in a cell
BACKGROUND = (64, 128, 128)

# The bones: the pieces each carries, by their number on the sheet read in
# rows, and the pivot it turns on, in the whole figure's own coordinates.
BONES = {
    "wing": ([1, 12, 11, 48, 20, 8, 2, 4, 13], (27, 22)),
    "tail": ([31, 15, 45, 40, 37, 38, 10, 41, 26, 39, 6, 36, 47, 5, 18, 3, 23, 25], (30, 44)),
    "skirt": ([14, 27, 7, 9, 51, 42, 53, 32, 46, 52], (40, 44)),
    "legs": ([43, 29, 19], (36, 60)),
    "body": ([16, 34, 49, 35, 33, 44, 30, 22, 21, 50, 17, 24], (36, 44)),
    "head": ([28], (38, 17)),
    "sword": ([0], (41, 40)),
}
# What turns with what: a bone not listed turns with the whole figure only.
PARENT = {"head": "body", "wing": "body", "sword": "body"}

REST = {}


def pose(**changes):
    out = dict(REST)
    out.update(changes)
    return out


# Each animation: (pose, sixtieths of a second to the next pose); it loops.
# A pose gives a bone degrees, clockwise, or (degrees, x, y) to shift it too.
ANIMATIONS = {
    # Standing: he breathes, the wing opens and closes, the coat stirs.
    "idle": [
        (pose(), 24),
        (pose(wing=-9, tail=4, skirt=-3, body=(0, 0, 1), sword=2), 24),
    ],
    # The swing: the blade goes up and back, comes down across, and holds.
    "slash": [
        (pose(sword=-95, body=(-4, 0, 0), wing=-14, head=-3), 10),
        (pose(sword=-120, body=(-6, 0, 0), wing=-18, head=-4, tail=5), 6),
        (pose(sword=35, body=(8, 2, 1), wing=10, head=4, tail=-8, skirt=6), 4),
        (pose(sword=28, body=(6, 2, 1), wing=6, head=3, tail=-5, skirt=4), 12),
        (pose(), 10),
    ],
    # Hit: he rocks back.
    "hurt": [
        (pose(body=(-9, -3, 0), head=-8, wing=14, sword=-14, tail=-9, skirt=-9), 8),
        (pose(body=(-4, -1, 0), head=-3, wing=6, sword=-6, tail=-4, skirt=-4), 10),
    ],
}


def find_pieces(indices, opaque):
    """The boxes of the sheet's pieces, read in rows; the last is the whole figure."""
    height, width = indices.shape
    seen = np.zeros((height, width), bool)
    boxes = []
    for y in range(height):
        for x in range(width):
            if seen[y, x] or not opaque[y, x]:
                continue
            stack = [(x, y)]
            seen[y, x] = True
            x0 = x1 = x
            y0 = y1 = y
            count = 0
            while stack:
                cx, cy = stack.pop()
                count += 1
                x0, x1, y0, y1 = min(x0, cx), max(x1, cx), min(y0, cy), max(y1, cy)
                for dx in (-1, 0, 1):
                    for dy in (-1, 0, 1):
                        nx, ny = cx + dx, cy + dy
                        if 0 <= nx < width and 0 <= ny < height and not seen[ny, nx] and opaque[ny, nx]:
                            seen[ny, nx] = True
                            stack.append((nx, ny))
            if count > 6:
                boxes.append((x0, y0, x1 + 1, y1 + 1))
    boxes.sort(key=lambda b: (b[1] // 12, b[0]))
    return boxes[:-1], boxes[-1]


def fit(indices, opaque, pieces, whole):
    """Where each piece goes on the whole figure, and how much of it shows there."""
    pad = 12
    x0, y0, x1, y1 = whole
    ref = np.full((y1 - y0 + 2 * pad, x1 - x0 + 2 * pad), -1, int)
    ref[pad:-pad, pad:-pad] = np.where(opaque[y0:y1, x0:x1], indices[y0:y1, x0:x1], -1)
    placed = []
    for box in pieces:
        piece = indices[box[1]:box[3], box[0]:box[2]].astype(int)
        mask = opaque[box[1]:box[3], box[0]:box[2]]
        score = np.zeros((ref.shape[0] - piece.shape[0] + 1, ref.shape[1] - piece.shape[1] + 1))
        ys, xs = np.nonzero(mask)
        for yy, xx in zip(ys, xs):
            score += ref[yy:yy + score.shape[0], xx:xx + score.shape[1]] == piece[yy, xx]
        score /= len(ys)
        at = np.unravel_index(score.argmax(), score.shape)
        placed.append((int(at[1]) - pad, int(at[0]) - pad, float(score[at])))
    return placed


class Rig:
    def __init__(self):
        sheet = Image.open(SHEET)
        indices = np.array(sheet).astype(int)
        self.rgba = sheet.convert("RGBA")
        opaque = np.array(self.rgba)[:, :, 3] > 0
        self.pieces, self.whole = find_pieces(indices, opaque)
        self.placed = fit(indices, opaque, self.pieces, self.whole)
        self.images = [self.rgba.crop(box) for box in self.pieces]
        self.bone_of = {}
        for bone, (numbers, _pivot) in BONES.items():
            for number in numbers:
                self.bone_of[number] = bone
        missing = [n for n in range(len(self.pieces)) if n not in self.bone_of]
        if missing:
            raise SystemExit(f"pieces in no bone: {missing}")
        # The less of a piece shows on the whole figure, the further back it is.
        self.order = sorted(range(len(self.pieces)), key=lambda n: self.placed[n][2])

    def transform(self, bone, pose_):
        """The bone's turn and shift, with its parent's: a point's place on the cell."""
        chain = []
        while bone is not None:
            chain.append(bone)
            bone = PARENT.get(bone)

        def apply(x, y):
            for name in chain:
                value = pose_.get(name, 0)
                angle, sx, sy = value if isinstance(value, tuple) else (value, 0, 0)
                px, py = BONES[name][1]
                cos, sin = math.cos(math.radians(angle)), math.sin(math.radians(angle))
                dx, dy = x - px, y - py
                x, y = px + dx * cos - dy * sin + sx, py + dx * sin + dy * cos + sy
            return x, y

        return apply

    def draw(self, pose_):
        frame = Image.new("RGBA", CELL, (0, 0, 0, 0))
        for number in self.order:
            image = self.images[number]
            px, py, _score = self.placed[number]
            apply = self.transform(self.bone_of[number], pose_)
            # Where the piece's corners and its x and y steps land: the turn
            # is the same all over it, so each pixel of the cell can ask the
            # piece what is there, and no holes open.
            ox, oy = apply(px, py)
            ax, ay = apply(px + 1, py)
            bx, by = apply(px, py + 1)
            ux, uy, vx, vy = ax - ox, ay - oy, bx - ox, by - oy
            corners = [apply(px + cx, py + cy) for cx in (0, image.width) for cy in (0, image.height)]
            x0 = int(min(c[0] for c in corners)) - 1
            x1 = int(max(c[0] for c in corners)) + 2
            y0 = int(min(c[1] for c in corners)) - 1
            y1 = int(max(c[1] for c in corners)) + 2
            for y in range(y0, y1):
                for x in range(x0, x1):
                    cx, cy = x + ORIGIN[0], y + ORIGIN[1]
                    if not (0 <= cx < CELL[0] and 0 <= cy < CELL[1]):
                        continue
                    dx, dy = x + 0.5 - ox, y + 0.5 - oy
                    sx = dx * ux + dy * uy
                    sy = dx * vx + dy * vy
                    if 0 <= sx < image.width and 0 <= sy < image.height:
                        pixel = image.getpixel((int(sx), int(sy)))
                        if pixel[3]:
                            frame.putpixel((cx, cy), pixel)
        return frame


def between(a, b, t):
    out = {}
    for key in set(a) | set(b):
        va, vb = a.get(key, 0), b.get(key, 0)
        va = va if isinstance(va, tuple) else (va, 0, 0)
        vb = vb if isinstance(vb, tuple) else (vb, 0, 0)
        # Eased, so that a pose is left and reached gently.
        s = t * t * (3 - 2 * t)
        out[key] = tuple(x + (y - x) * s for x, y in zip(va, vb))
    return out


def frames_of(rig, name, step=4):
    keys = ANIMATIONS[name]
    out = []
    for index, (pose_, length) in enumerate(keys):
        following = keys[(index + 1) % len(keys)][0]
        for i in range(0, length, step):
            out.append(rig.draw(between(pose_, following, i / length)))
    return out


def flat(frame):
    image = Image.new("RGB", frame.size, BACKGROUND)
    image.paste(frame, (0, 0), frame)
    return image


def main():
    OUT.mkdir(parents=True, exist_ok=True)
    rig = Rig()
    rest = rig.draw({})
    whole = rig.rgba.crop(rig.whole)
    compare = Image.new("RGB", (CELL[0] * 2, CELL[1]), BACKGROUND)
    compare.paste(whole, ORIGIN, whole)
    compare.paste(rest, (CELL[0], 0), rest)
    compare.resize((compare.width * 3, compare.height * 3), Image.NEAREST).save(OUT / "rest.png")
    rows = {name: frames_of(rig, name) for name in ANIMATIONS}
    sheet = Image.new("RGB", (CELL[0] * max(len(r) for r in rows.values()), CELL[1] * len(rows)), BACKGROUND)
    for row, frames in enumerate(rows.values()):
        for column, frame in enumerate(frames):
            sheet.paste(flat(frame), (column * CELL[0], row * CELL[1]))
    sheet.save(OUT / "sheet.png")
    for name, frames in rows.items():
        big = [flat(f).resize((CELL[0] * 3, CELL[1] * 3), Image.NEAREST) for f in frames]
        big[0].save(OUT / f"{name}.gif", save_all=True, append_images=big[1:], duration=66, loop=0)
    print(f"wrote {OUT}: {', '.join(f'{name} {len(frames)}' for name, frames in rows.items())} frames")


if __name__ == "__main__":
    main()
