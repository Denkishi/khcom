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
from PIL import Image, ImageDraw

ROOT = Path(__file__).resolve().parents[1]
SHEET = ROOT / "mod_assets/sephiroth_ffrk.png"
OUT = ROOT / "mod_assets/sephiroth"
CELL = (256, 160)
ORIGIN = (88, 62)  # where the whole figure's top left corner goes in a cell
BACKGROUND = (64, 128, 128)
SWORD_HILT = (41, 40)  # the two ends of the blade on the whole figure, for its trail
SWORD_TIP = (128, 76)

# The bones: the pieces each carries, by their number on the sheet read in
# rows, and the pivot it turns on, in the whole figure's own coordinates.
BONES = {
    "wing_low": ([48, 20, 8, 2, 4, 13], (26, 24)),
    "wing_up": ([1, 12, 11], (27, 22)),
    "tail": ([31, 15, 45, 40, 37, 38, 10, 41, 26, 39, 6, 36, 47, 5, 18, 3, 23, 25], (30, 44)),
    "leg_far": ([19], (28, 62)),
    "leg_near": ([43, 29], (40, 56)),
    "skirt": ([14, 27, 7, 9, 51, 42, 53, 32, 46, 52], (40, 44)),
    "hips": ([49, 35, 33, 24], (36, 46)),
    "chest": ([16, 34, 44], (37, 36)),
    "arm": ([30, 22, 21, 50, 17], (27, 24)),
    "head": ([28], (38, 17)),
    "sword": ([0], SWORD_HILT),
}
# What turns with what. Everything turns with "root", the whole figure, whose
# pivot is between the feet.
PARENT = {"chest": "hips", "head": "chest", "wing_up": "chest", "wing_low": "chest", "arm": "chest", "sword": "chest",
          "tail": "hips", "skirt": "hips"}
ROOT_PIVOT = (36, 84)

REST = {}


def pose(**changes):
    out = dict(REST)
    out.update(changes)
    return out


def step(forward, **more):
    """A stride: the near leg `forward` pixels ahead, the far one as far behind."""
    return dict(leg_near=(forward * 2, forward, -abs(forward) // 3), leg_far=(-forward * 2, -forward, 0), **more)


# Each animation: (pose, sixtieths of a second to the next pose) and, for some,
# what else the frames from this pose show: "trail" the blade's sweep, "orb"
# a ball of darkness at (x, y, radius), "ring" a shock on the ground at
# (x, radius), "ward" the barrier of the counter at (x, y, size).
# A pose gives a bone degrees, clockwise, or (degrees, x, y) to shift it too.
# The figure faces right; the blade at rest points right and a little down, so
# a turn of -114 stands it up and one of 66 points it at the ground.
ANIMATIONS = {
    # Standing: he breathes with the chest, the wing opens and closes in two
    # parts, the coat stirs after the body.
    "idle": [
        (pose(), 26),
        (pose(chest=(2, 0, 1), head=-3, wing_up=-10, wing_low=-5, tail=4, skirt=-3, arm=4, sword=3), 26),
    ],
    "walk": [
        (pose(root=(0, 0, 0), chest=5, head=-3, wing_up=-4, wing_low=3, tail=5, skirt=-5, **step(5)), 10),
        (pose(root=(0, 0, -1), chest=4, head=-3, wing_up=-8, wing_low=-2, tail=2, skirt=-2, **step(0)), 10),
        (pose(root=(0, 0, 0), chest=5, head=-3, wing_up=-4, wing_low=3, tail=5, skirt=-5, **step(-5)), 10),
        (pose(root=(0, 0, -1), chest=4, head=-3, wing_up=-8, wing_low=-2, tail=2, skirt=-2, **step(0)), 10),
    ],
    # The dash: low and forward, wing and coat streaming, blade trailing.
    "dash": [
        (pose(root=(8, 0, 3), chest=20, head=-16, wing_up=28, wing_low=36, tail=-22, skirt=-26, arm=30, sword=138, **step(9)), 6),
        (pose(root=(9, 0, 2), chest=22, head=-17, wing_up=22, wing_low=30, tail=-17, skirt=-21, arm=34, sword=134, **step(-9)), 6),
    ],
    # A wide cut: up behind the head, down across, held low.
    "slash": [
        (pose(chest=-10, head=4, sword=-118, wing_up=-16, wing_low=-10, arm=-10, tail=5, **step(-3)), 8, {}),
        (pose(chest=-14, head=6, sword=-140, wing_up=-20, wing_low=-12, arm=-14, tail=7, **step(-4)), 4, {"trail": 1}),
        (pose(root=(0, 6, 1), chest=20, head=-10, sword=44, wing_up=14, wing_low=20, arm=24, tail=-12, skirt=8, **step(7)), 3, {"trail": 1}),
        (pose(root=(0, 6, 1), chest=17, head=-8, sword=38, wing_up=8, wing_low=12, arm=20, tail=-8, skirt=5, **step(7)), 12, {}),
        (pose(), 8, {}),
    ],
    # The thrust: drawn back, then the whole body behind the point.
    "thrust": [
        (pose(root=(0, -6, 0), chest=-16, head=8, sword=150, wing_up=-22, wing_low=-12, arm=-20, tail=8, **step(-5)), 12, {}),
        (pose(root=(0, -8, 1), chest=-18, head=9, sword=156, wing_up=-26, wing_low=-14, arm=-22, tail=10, **step(-6)), 3, {"trail": 1}),
        # (The blade turns with the chest and the whole body: -52 here is level.)
        (pose(root=(4, 34, 2), chest=24, head=-16, sword=-52, wing_up=30, wing_low=40, arm=36, tail=-26, skirt=-18, **step(12)), 3,
         {"trail": 1}),
        (pose(root=(4, 36, 2), chest=22, head=-14, sword=-50, wing_up=20, wing_low=28, arm=30, tail=-18, skirt=-12, **step(12)), 14, {}),
        (pose(), 10, {}),
    ],
    # A rising cut: from a crouch, the blade comes up in an arc and he with it.
    "rise": [
        (pose(root=(0, 0, 5), chest=18, head=-8, sword=70, wing_up=10, wing_low=16, tail=-8, **step(4)), 8, {}),
        (pose(root=(0, 0, 6), chest=22, head=-10, sword=80, wing_up=12, wing_low=20, tail=-10, **step(5)), 3, {"trail": 1}),
        (pose(root=(-6, 4, -22), chest=-16, head=8, sword=-150, wing_up=-34, wing_low=-24, arm=-30, tail=18, skirt=14, **step(-2)), 4,
         {"trail": 1}),
        (pose(root=(-8, 5, -30), chest=-20, head=10, sword=-170, wing_up=-40, wing_low=-28, arm=-34, tail=22, skirt=18, **step(-3)), 10,
         {}),
        (pose(root=(0, 4, -8), chest=6, sword=-20, wing_up=-20, wing_low=-10, tail=8), 8, {}),
        (pose(), 6, {}),
    ],
    # Eight cuts in a rush: he goes forward a step with each pair.
    "octaslash": [
        (pose(root=(6, 0, 2), chest=16, head=-10, sword=-110, wing_up=20, wing_low=28, tail=-16, **step(8)), 4, {"trail": 1}),
        (pose(root=(8, 8, 2), chest=24, head=-14, sword=50, wing_up=26, wing_low=34, tail=-20, **step(-8)), 3, {"trail": 1}),
        (pose(root=(6, 16, 2), chest=10, head=-8, sword=-80, wing_up=20, wing_low=28, tail=-16, **step(8)), 3, {"trail": 1}),
        (pose(root=(8, 24, 2), chest=26, head=-14, sword=64, wing_up=26, wing_low=34, tail=-20, **step(-8)), 3, {"trail": 1}),
        (pose(root=(6, 32, 2), chest=8, head=-6, sword=-130, wing_up=20, wing_low=28, tail=-16, **step(8)), 3, {"trail": 1}),
        (pose(root=(8, 40, 2), chest=28, head=-14, sword=30, wing_up=26, wing_low=34, tail=-20, **step(-8)), 3, {"trail": 1}),
        (pose(root=(4, 44, 1), chest=18, head=-10, sword=20, wing_up=10, wing_low=16, tail=-10, **step(6)), 12, {}),
        (pose(), 10, {}),
    ],
    # The plunge: he leaps, turns the point down and comes down on it.
    "plunge": [
        (pose(root=(0, 0, 5), chest=14, head=-6, sword=30, wing_up=8, wing_low=14, **step(3)), 6, {}),
        (pose(root=(-4, 6, -36), chest=-12, head=6, sword=-70, wing_up=-42, wing_low=-30, arm=-30, tail=20, skirt=16,
              leg_near=(-30, 2, -6), leg_far=(24, -2, -3)), 10, {}),
        (pose(root=(0, 10, -40), chest=6, head=-4, sword=62, wing_up=-50, wing_low=-36, arm=10, tail=24, skirt=20,
              leg_near=(-34, 2, -7), leg_far=(28, -2, -4)), 5, {"trail": 1}),
        (pose(root=(4, 12, 2), chest=22, head=-12, sword=66, wing_up=18, wing_low=26, arm=20, tail=-14, skirt=-10, **step(4)), 4,
         {"trail": 1, "ring": (150, 2)}),
        (pose(root=(4, 12, 2), chest=20, head=-10, sword=66, wing_up=10, wing_low=16, arm=18, tail=-8, skirt=-6, **step(4)), 12,
         {"ring": (150, 26)}),
        (pose(), 10, {}),
    ],
    # The dark spell: the wing spreads, the hand comes up, the ball swells and goes.
    "flare": [
        (pose(chest=-6, head=3, wing_up=-30, wing_low=-18, arm=-70, sword=30, tail=6), 10, {"orb": (176, 84, 1)}),
        (pose(chest=-9, head=5, wing_up=-44, wing_low=-28, arm=-96, sword=36, tail=9), 18, {"orb": (176, 82, 5)}),
        (pose(chest=-10, head=5, wing_up=-48, wing_low=-30, arm=-100, sword=38, tail=10), 6, {"orb": (176, 80, 11)}),
        (pose(root=(0, 3, 0), chest=14, head=-8, wing_up=10, wing_low=18, arm=-30, sword=20, tail=-8, skirt=6), 10, {"orb": (190, 82, 11)}),
        (pose(root=(0, 3, 0), chest=10, head=-6, wing_up=4, wing_low=8, arm=-10, sword=10, tail=-4), 8, {"orb": (250, 84, 9)}),
        (pose(), 8, {}),
    ],
    # The counter: the blade stood up before him, a ward of darkness around.
    "counter": [
        (pose(chest=-4, head=2, sword=-100, wing_up=-12, wing_low=-6, arm=-8), 6, {"ward": (150, 96, 4)}),
        (pose(chest=-6, head=3, sword=-114, wing_up=-18, wing_low=-10, arm=-12), 20, {"ward": (150, 96, 30)}),
        (pose(chest=-5, head=2, sword=-112, wing_up=-14, wing_low=-8, arm=-10), 6, {"ward": (150, 96, 34)}),
        (pose(), 8, {}),
    ],
    # Hit: he rocks back, everything following late.
    "hurt": [
        (pose(root=(-10, -5, 0), chest=-16, head=-12, wing_up=20, wing_low=28, sword=-24, tail=-12, skirt=-14, arm=-20, **step(-3)), 8),
        (pose(root=(-5, -3, 0), chest=-8, head=-5, wing_up=10, wing_low=14, sword=-10, tail=-6, skirt=-7, arm=-8, **step(-2)), 12),
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
        flat_palette = sheet.getpalette()
        used = sorted({int(v) for v in np.unique(np.array(sheet)) if np.array(self.rgba)[np.array(sheet) == v][:, 3].any()})
        self.colours = [tuple(flat_palette[v * 3:v * 3 + 3]) for v in used]
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

        chain.append("root")

        def apply(x, y):
            for name in chain:
                value = pose_.get(name, 0)
                angle, sx, sy = value if isinstance(value, tuple) else (value, 0, 0)
                px, py = ROOT_PIVOT if name == "root" else BONES[name][1]
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

    def blade(self, pose_):
        """Where the two ends of the blade are on the cell in a pose."""
        apply = self.transform("sword", pose_)
        return [(x + ORIGIN[0], y + ORIGIN[1]) for x, y in (apply(*SWORD_HILT), apply(*SWORD_TIP))]

    def colour(self, wanted):
        """The colour of the sheet's own palette nearest to one wanted."""
        return min(self.colours, key=lambda c: sum((a - b) ** 2 for a, b in zip(c, wanted))) + (255,)


def effects(rig, frame, pose_, before, extra):
    """What a frame shows besides the figure, drawn in the figure's own colours."""
    draw = ImageDraw.Draw(frame)
    light, mid, dark = rig.colour((230, 240, 255)), rig.colour((60, 90, 200)), rig.colour((30, 30, 70))
    if extra.get("trail") and before is not None:
        # The blade's sweep: the ground between where it was and where it is,
        # solid by the blade and thinning behind.
        old, new = rig.blade(before), rig.blade(pose_)
        under = Image.new("RGBA", frame.size, (0, 0, 0, 0))
        ImageDraw.Draw(under).polygon([old[0], old[1], new[1], new[0]], fill=mid)
        half = [((o[0] + n[0]) / 2, (o[1] + n[1]) / 2) for o, n in zip(old, new)]
        ImageDraw.Draw(under).polygon([half[0], half[1], new[1], new[0]], fill=light)
        pixels = under.load()
        for y in range(frame.height):
            for x in range(frame.width):
                if pixels[x, y][3] and pixels[x, y] == mid and (x + y) & 1:
                    pixels[x, y] = (0, 0, 0, 0)  # the older half is a checker
        under.paste(frame, (0, 0), frame)
        frame.paste(under, (0, 0))
    if "orb" in extra:
        x, y, radius = extra["orb"]
        if radius >= 1:
            draw.ellipse([x - radius, y - radius, x + radius, y + radius], fill=dark, outline=mid)
            if radius >= 4:
                draw.ellipse([x - radius // 2, y - radius // 2 - 1, x + radius // 3, y + radius // 3 - 1], fill=mid)
                draw.point((x - radius // 3, y - radius // 3), fill=light)
    if "ring" in extra:
        x, radius = extra["ring"]
        ground = ORIGIN[1] + ROOT_PIVOT[1]
        if radius >= 2:
            draw.ellipse([x - radius, ground - radius // 4, x + radius, ground + radius // 4], outline=light)
            if radius >= 12:
                draw.ellipse([x - radius + 3, ground - radius // 4 + 1, x + radius - 3, ground + radius // 4 - 1], outline=mid)
    if "ward" in extra:
        x, y, size = extra["ward"]
        if size >= 3:
            for k, colour in ((0, mid), (3, light)):
                points = [(x + (size - k) * math.cos(math.radians(a)) * 0.8, y + (size - k) * math.sin(math.radians(a))) for a in range(0, 360, 60)]
                draw.polygon(points, outline=colour)


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


def frames_of(rig, name, every=3):
    """The animation's frames, one every `every` sixtieths of a second."""
    keys = ANIMATIONS[name]
    out = []
    before = None
    for index, key in enumerate(keys):
        pose_, length = key[0], key[1]
        extra = key[2] if len(key) > 2 else {}
        following = keys[(index + 1) % len(keys)]
        after = following[2] if len(following) > 2 else {}
        for i in range(0, length, every):
            t = i / length
            now = between(pose_, following[0], t)
            # What grows or moves does so along with the pose.
            shown = dict(extra)
            for kind in ("orb", "ring", "ward"):
                if kind in extra and kind in after:
                    shown[kind] = tuple(round(a + (b - a) * t) for a, b in zip(extra[kind], after[kind]))
            frame = rig.draw(now)
            effects(rig, frame, now, before, shown)
            out.append(frame)
            before = now
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
    compare.resize((compare.width * 2, compare.height * 2), Image.NEAREST).save(OUT / "rest.png")
    rows = {name: frames_of(rig, name) for name in ANIMATIONS}
    sheet = Image.new("RGB", (CELL[0] * max(len(r) for r in rows.values()), CELL[1] * len(rows)), BACKGROUND)
    for row, frames in enumerate(rows.values()):
        for column, frame in enumerate(frames):
            sheet.paste(flat(frame), (column * CELL[0], row * CELL[1]))
    sheet.save(OUT / "sheet.png")
    for name, frames in rows.items():
        big = [flat(f).resize((CELL[0] * 2, CELL[1] * 2), Image.NEAREST) for f in frames]
        big[0].save(OUT / f"{name}.gif", save_all=True, append_images=big[1:], duration=50, loop=0)
    # One GIF with every animation in turn, its name over it, to look through.
    reel = []
    for name, frames in rows.items():
        for frame in frames * (2 if len(frames) < 12 else 1):
            image = flat(frame).resize((CELL[0] * 2, CELL[1] * 2), Image.NEAREST)
            ImageDraw.Draw(image).text((8, 6), name, fill=(255, 255, 255))
            reel.append(image)
    reel[0].save(OUT / "preview.gif", save_all=True, append_images=reel[1:], duration=50, loop=0)
    print(f"wrote {OUT}: {', '.join(f'{name} {len(frames)}' for name, frames in rows.items())} frames")


if __name__ == "__main__":
    main()
