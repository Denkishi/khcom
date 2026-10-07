#!/usr/bin/env python3
"""Offsets of the fields of the mod's global structs, for play.py's @symbol.field.

The offsets come from the compiler: a C file with one offsetof per field is
compiled to assembly and the constants are read back from it. Each is stored
plus one, because a zero would be emitted as blank space instead of a word.
"""
import re
import subprocess
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
STRUCTS = {"gRogue": "RogueRun", "gRogueMeta": "RogueMeta", "gRogueDebug": "RogueDebug"}


def field_names(header, struct):
    body = re.search(r"typedef struct %s \{(.*?)\} %s;" % (struct, struct), header, re.S).group(1)
    return re.findall(r"^\s+[\w ]+?\**\s*(\w+)(?:\[[^\]]*\])?;", body, re.M)


def offsets():
    header = (ROOT / "include/rogue.h").read_text()
    lines = ['#include <stddef.h>', '#include "rogue.h"']
    names = []
    for symbol, struct in STRUCTS.items():
        for field in field_names(header, struct):
            names.append((symbol, field))
            lines.append(f"const unsigned int off_{symbol}_{field} = offsetof({struct}, {field}) + 1;")
    with tempfile.TemporaryDirectory() as tmp:
        source = Path(tmp) / "offsets.c"
        source.write_text("\n".join(lines) + "\n")
        asm = subprocess.run(
            ["arm-none-eabi-gcc", "-S", "-mthumb", "-fshort-enums", "-I", ROOT / "include", "-I", ROOT / "tools/agbcc/include",
             "-DVERSION_EU", "-w", "-o", "-", source],
            check=True, capture_output=True, text=True).stdout
    found = dict(re.findall(r"^off_(\w+):\s*\n\s*\.word\s+(\d+)", asm, re.M))
    return {f"{symbol}.{field}": int(found[f"{symbol}_{field}"]) - 1 for symbol, field in names}


if __name__ == "__main__":
    for name, offset in offsets().items():
        print(f"{name} {offset:#x}")
