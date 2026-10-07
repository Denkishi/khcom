#!/usr/bin/env python3
"""Make the trailer: build/venv/bin/python tools/trailer.py [compose]

Each scene is a script for the test runner (tools/emu), played on the build
with the wider picture and recorded frame by frame; the trailer is a list of
cuts from those recordings with a line of text over each, put together here
and encoded with ffmpeg (pip install imageio-ffmpeg). The music is the game's
own, from the recording of one of the boss fights. With `compose` the scenes
are not played again, only cut. Writes mod_assets/trailer.mp4.
"""
import os
import subprocess
import sys
from pathlib import Path

import imageio_ffmpeg
from PIL import Image

ROOT = Path(__file__).resolve().parents[1]
WORK = ROOT / "build/trailer"
OUT = ROOT / "mod_assets/trailer.mp4"
# The words, in the order the game has them in rogue_hub.c: it writes them itself, see captions().
WORDS = ['KINGDOM HEARTS', 'CHAIN OF MEMORIES', 'ROGUELITE', 'Ogni run è diversa', 'Un hub da esplorare', 'Ogni porta, una carta', 'Tu scegli la stanza', 'Battaglie in 2D', 'Nuove mosse', 'Salta. Taglia. Tuffati.', 'Ogni mossa è una carta', 'Le mosse dei boss sono tue', 'Più di 180 reliquie', 'Nuovi eroi', 'Nuovi boss', 'Riuscirai a batterli?', 'CoM ROGUELITE', 'github.com/Denkishi/khcom']
WIDE, HIGH = 288, 160
SIZE = (1280, 720)

START = ["wait 600", "press START", "wait 120", "press START", "wait 200", "hold B 100", "wait 20"]
FLAT = ["wait 600", "poke8 @gRogueMeta.flags 23", "press START", "wait 120", "press START", "wait 200", "hold B 100", "wait 20"]


def combo():
    lines = FLAT + ["debug battle 0", "wait 300", "poke8 @gRogueDebug.god 1", "rec {rec}", "hold RIGHT 16"]
    for tech, wait in ((2, 34), (128, 40), (129, 40), (130, 44)):
        lines += ["press A", f"debug tech {tech}", f"wait {wait}"]
    lines += ["hold UP 3", "wait 14", "press A", "debug tech 66", "wait 26", "debug tech 67", "wait 40"]
    for tech, wait in ((192, 50), (194, 80), (195, 50)):
        lines += ["press A", f"debug tech {tech}", f"wait {wait}"]
    lines += ["debug tech 131", "wait 4", "debug hurt 5", "wait 40", "debug finisher", "wait 50", "rec off"]
    return lines


SCENES = {
    "hub": ["wait 600", "poke8 @gRogueMeta.boonsMet 254", "poke8 @gRogueMeta.wins 3", "poke8 @gRogueMeta.chapters 3", "press START", "wait 120",
            "rec {rec}", "hold LEFT 90", "hold UP 30", "hold RIGHT 170", "rec off"],
    "door": START + ["poke8 @gRogueDebug.strike 1", "rec {rec}", "wait 200", "press RIGHT", "wait 20", "press A", "wait 40", "press A", "wait 260",
                     "rec off"],
    "combo": combo(),
    "moves": START + ["debug battle 0", "wait 330", "poke8 @gRogueDebug.god 1", "rec {rec}"]
    + [line for move in (0, 2, 4, 6, 9, 11, 1, 12) for line in ("press A", f"debug move {move}", "wait 36")] + ["rec off"],
    "roxas": ["wait 600", "press START", "wait 120", "poke8 @gRogueMeta.chapters 3", "poke8 @gRogueMeta.hero 3", "press SELECT", "wait 30",
              "press START", "wait 200", "hold B 100", "wait 20", "debug battle 0", "wait 330", "poke8 @gRogueDebug.god 1", "rec {rec}",
              "press A", "wait 18", "press A", "wait 18", "debug finisher", "wait 60", "press A", "wait 18", "debug finisher", "wait 70", "rec off"],
    # The music: a boss fight left to run.
    "music": START + ["poke8 @gRogueDebug.god 1", "poke8 @gRogue.bossSkin 8", "debug battle 157", "wait 300", "rec {rec}", "wait 2200", "rec off"],
    "mickey": ["wait 600", "press START", "wait 120", "poke8 @gRogueMeta.flags 7", "press SELECT", "wait 30", "press START", "wait 200",
               "hold B 100", "wait 20", "debug battle 0", "wait 330", "poke8 @gRogueDebug.god 1", "rec {rec}", "hold RIGHT 12", "press A",
               "wait 18", "press A", "wait 18", "debug finisher", "wait 60", "press A", "wait 18", "debug finisher", "wait 70", "rec off"],
}


def boss(skin, force=0, frames=320):
    """A boss fight recorded from the moment one of its moves is asked for (0: whatever it does)."""
    return START + ["poke8 @gRogueDebug.god 1", f"poke8 @gRogue.bossSkin {skin}", "debug battle 157", "wait 330", "rec {rec}",
                    f"poke8 @gRogueDebug.bossForce {force}", f"wait {frames}", "rec off"]


SCENES.update({
    "seph_wing": boss(8, 16), "seph_octa": boss(8, 15), "seph_flare": boss(8, 12), "seph_plunge": boss(8, 11), "seph_wave": boss(8, 13),
    "sora2": boss(9, 0, 420), "coat": boss(11, 0, 420), "hood": boss(12, 0, 420),
})

# The cuts: a card of text (None, frames, big line, small line) or a piece of a
# scene (scene, first frame, frames, text over it, whether it is a battle and
# so shown at its full width, and how many times each frame is shown: 2 is
# slow motion). With None for the first frame the piece is the stretch of the
# scene in which most moves on the screen, found by busiest().
CUTS = [
    (None, 80, "KINGDOM HEARTS", "CHAIN OF MEMORIES"),
    (None, 45, "ROGUELITE", "Ogni run è diversa"),
    ("hub", 20, 120, "Un hub da esplorare", False, 1),
    ("door", 150, 60, "Ogni porta, una carta", False, 1),
    ("door", 330, 80, "Tu scegli la stanza", False, 1),
    ("combo", 14, 60, "Battaglie in 2D", True, 1),
    ("combo", 100, 60, "Nuove mosse", True, 1),
    ("combo", 190, 70, "Salta. Taglia. Tuffati.", True, 1),
    ("combo", 300, 60, "Ogni mossa è una carta", True, 1),
    ("moves", None, 60, "Le mosse dei boss sono tue", True, 1),
    ("moves", 150, 60, "Più di 180 reliquie", True, 1),
    ("roxas", None, 70, "Nuovi eroi", True, 1),
    ("mickey", None, 60, "", True, 1),
    ("seph_wing", None, 60, "Nuovi boss", True, 2),
    ("seph_octa", None, 90, "", True, 1),
    ("seph_flare", None, 70, "", True, 1),
    ("seph_plunge", None, 70, "", True, 1),
    ("seph_wave", None, 50, "", True, 1),
    ("sora2", None, 60, "", True, 1),
    ("coat", None, 60, "", True, 1),
    ("hood", None, 70, "Riuscirai a batterli?", True, 1),
    (None, 130, "CoM ROGUELITE", "github.com/Denkishi/khcom"),
]


def busiest(scene, count):
    """The first frame of the stretch of `count` frames of a scene in which the picture changes most."""
    import numpy
    data = numpy.fromfile(WORK / f"{scene}.rgb", dtype=numpy.uint8).reshape(-1, HIGH, WIDE, 4)[:, ::4, ::4, :3].astype(numpy.int16)
    change = numpy.abs(numpy.diff(data, axis=0)).sum(axis=(1, 2, 3)).astype(numpy.float64)
    # A flash of the whole screen is not action: no frame counts for more than three times the usual.
    change = numpy.minimum(change, 3 * numpy.median(change) + 1)
    sums = numpy.convolve(change, numpy.ones(count), "valid")
    return int(sums.argmax())


def record():
    WORK.mkdir(parents=True, exist_ok=True)
    for name, lines in SCENES.items():
        script = WORK / f"{name}.txt"
        script.write_text("\n".join(line.replace("{rec}", str(WORK / name)) for line in lines) + "\n")
        subprocess.run([sys.executable, ROOT / "tools/emu/play.py", script], check=True, stdout=subprocess.DEVNULL,
                       env=dict(os.environ, EMU_RUN=str(ROOT / "build/emu_run_wide")))
        print(name, (WORK / f"{name}.rgb").stat().st_size // (WIDE * HIGH * 4), "frames")


def captions():
    """Has the game write each line in its own letters on an empty screen, and keeps a picture of each."""
    lines = ["wait 600", "press START", "wait 120"]
    for n in range(len(WORDS)):
        lines += [f"poke8 @gRogueDebug.caption {n + 1}", "wait 4", f"shot {WORK}/caption{n}.ppm"]
    script = WORK / "captions.txt"
    script.write_text("\n".join(lines) + "\n")
    subprocess.run([sys.executable, ROOT / "tools/emu/play.py", script], check=True, stdout=subprocess.DEVNULL)
    for n in range(len(WORDS)):
        picture = Image.open(WORK / f"caption{n}.ppm").convert("RGB")
        box = picture.point(lambda v: 255 if v > 8 else 0).getbbox()
        picture = picture.crop(box).convert("RGBA")
        picture.putdata([(r, g, b, 0 if r + g + b < 24 else 255) for r, g, b, _ in picture.getdata()])
        picture.save(WORK / f"caption{n}.png")


def text(image, where, words, scale):
    """A line of the game's own writing, enlarged a whole number of times, centred at a height."""
    picture = Image.open(WORK / f"caption{WORDS.index(words)}.png")
    picture = picture.resize((picture.width * scale, picture.height * scale), Image.NEAREST)
    x = (SIZE[0] - picture.width) // 2
    # A dark edge of one of its own pixels all round, so that it reads over anything.
    edge = Image.new("RGBA", picture.size, (8, 8, 24, 255))
    for dx in (-scale, 0, scale):
        for dy in (-scale, 0, scale):
            image.paste(edge, (x + dx, where + dy), picture)
    image.paste(picture, (x, where), picture)


def frames():
    """Every frame of the trailer in turn, as bytes."""
    for cut in CUTS:
        if cut[0] is None:
            _, count, big, small = cut
            for i in range(count):
                image = Image.new("RGB", SIZE, (4, 6, 20))
                text(image, 250, big, 7)
                text(image, 400, small, 4)
                # The words come up out of the dark.
                if i < 16:
                    image = Image.blend(Image.new("RGB", SIZE, (4, 6, 20)), image, i / 16)
                yield image.tobytes()
            continue
        scene, first, count, words, wide, slow = cut
        size = WIDE * HIGH * 4
        if first is None:
            first = busiest(scene, count)
        with open(WORK / f"{scene}.rgb", "rb") as f:
            f.seek(first * size)
            for i in range(count):
                data = f.read(size)
                if len(data) < size:
                    break
                picture = Image.frombuffer("RGBX", (WIDE, HIGH), data, "raw", "RGBX", 0, 1).convert("RGB")
                if not wide:
                    picture = picture.crop((24, 0, 264, HIGH))
                scale = SIZE[1] // HIGH  # whole pixels
                picture = picture.resize((picture.width * scale, picture.height * scale), Image.NEAREST)
                image = Image.new("RGB", SIZE, (0, 0, 0))
                image.paste(picture, ((SIZE[0] - picture.width) // 2, (SIZE[1] - picture.height) // 2))
                if i < 3:
                    # A cut comes in from black over three frames.
                    image = Image.blend(Image.new("RGB", SIZE, (0, 0, 0)), image, (i + 1) / 4)
                if words:
                    text(image, 612, words, 5)
                for _ in range(slow):
                    yield image.tobytes()


def compose():
    total = sum(cut[1] if cut[0] is None else cut[2] * cut[5] for cut in CUTS)
    # The music: the boss fight's, from a little way in, for as long as the trailer lasts.
    music = WORK / "bed.pcm"
    with open(WORK / "music.pcm", "rb") as f:
        f.seek(48000 * 4 * 2)
        music.write_bytes(f.read(total * 48000 // 60 * 4))
    ffmpeg = imageio_ffmpeg.get_ffmpeg_exe()
    encoder = subprocess.Popen(
        [ffmpeg, "-y", "-loglevel", "error", "-f", "rawvideo", "-pix_fmt", "rgb24", "-s", f"{SIZE[0]}x{SIZE[1]}", "-r", "60", "-i", "-",
         "-f", "s16le", "-ar", "48000", "-ac", "2", "-i", str(music), "-c:v", "libx264", "-pix_fmt", "yuv420p", "-crf", "18",
         "-c:a", "aac", "-b:a", "160k", "-af", f"afade=t=out:st={total / 60 - 2}:d=2", "-shortest", str(OUT)],
        stdin=subprocess.PIPE)
    for frame in frames():
        encoder.stdin.write(frame)
    encoder.stdin.close()
    encoder.wait()
    print(f"{OUT}: {total / 60:.1f} s")


if __name__ == "__main__":
    if "compose" not in sys.argv:
        record()
    captions()
    compose()
