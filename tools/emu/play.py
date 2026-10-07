#!/usr/bin/env python3
"""Run a test script on the built ROM: play.py SCRIPT [SHEET.png [SAVE]]

Wraps the headless runner: @symbol in the script becomes the symbol's address
from the link map (@symbol+N adds a hex offset, @symbol.field the offset of a
field of the mod's structs), `debug COMMAND [ARG]` queues one of the test
commands of rogue_debug.c, `include FILE` pulls in another
script, and the screenshots the script takes are tiled into SHEET.png. With
SAVE the cartridge save is kept in that file, otherwise it is not kept at all.
"""
import re
import subprocess
import sys
import tempfile
from pathlib import Path

from fields import offsets

ROOT = Path(__file__).resolve().parents[2]
MAP = ROOT / "build/eu/com_eu.map"
ROM = ROOT / "build/eu/com_eu.gba"

symbols = {name: int(addr, 16) for addr, name in re.findall(r"^\s+0x([0-9a-f]{8})\s+(\w+)$", MAP.read_text(), re.M)}


fields = offsets()
DEBUG = ["none", "room", "battle", "reward", "relic", "floor", "win", "hurt", "hit", "attack", "finisher", "tag", "enemytag", "move"]


def resolve(match):
    if match.group(3):
        return f"{symbols[match.group(1)] + fields[match.group(1) + '.' + match.group(3)]:08x}"
    return f"{symbols[match.group(1)] + int(match.group(2) or '0', 16):08x}"


def load(path):
    lines = []
    for line in Path(path).read_text().splitlines():
        if line.startswith("include "):
            lines += load(Path(path).parent / line.split()[1])
        elif line.startswith("debug "):
            words = line.split()
            base = symbols["gRogueDebug"]
            lines.append(f"poke8 {base + 1:08x} {words[2] if len(words) > 2 else 0}")
            lines.append(f"poke8 {base:08x} {DEBUG.index(words[1])}")
        else:
            lines.append(re.sub(r"@(\w+)(?:\+(\w+)|\.(\w+))?", resolve, line))
    return lines


lines = load(sys.argv[1])
with tempfile.NamedTemporaryFile("w", suffix=".txt", delete=False) as f:
    f.write("\n".join(lines) + "\n")
subprocess.run([ROOT / "build/emu_run", ROM, f.name] + sys.argv[3:4], check=True)
shots = [line.split()[1] for line in lines if line.startswith("shot ")]
if len(sys.argv) > 2 and shots:
    # The contact sheet needs Pillow, which lives in the build's virtualenv.
    venv = ROOT / "build/venv/bin/python"
    python = venv if venv.exists() else sys.executable
    subprocess.run([python, Path(__file__).with_name("sheet.py"), sys.argv[2]] + shots, check=True)
