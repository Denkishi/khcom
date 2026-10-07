#!/usr/bin/env python3
"""Sum the runner's `profile` output by function: play.py SCRIPT | profile.py [N]

Prints the N functions (default 30) the program counter was in most, with
their share of the instructions run. The BIOS line is mostly the wait for the
vertical blank, that is, the time left over.
"""
import bisect
import collections
import re
import sys
from pathlib import Path

MAP = Path(__file__).resolve().parents[2] / "build/eu/com_eu.map"
symbols = sorted((int(addr, 16), name) for addr, name in re.findall(r"^\s+0x(0[89][0-9a-f]{6})\s+(\w+)$", MAP.read_text(), re.M))
counts = collections.Counter()
for line in sys.stdin:
    match = re.match(r"prof (\w+) (\d+)", line)
    if not match:
        print(line, end="")
    elif match.group(1) in ("ram", "bios"):
        counts[match.group(1)] += int(match.group(2))
    else:
        i = bisect.bisect_right(symbols, (int(match.group(1), 16), "~")) - 1
        counts[symbols[i][1] if i >= 0 else match.group(1)] += int(match.group(2))
total = sum(counts.values())
for name, count in counts.most_common(int(sys.argv[1]) if len(sys.argv) > 1 else 30):
    print(f"{100 * count / total:5.1f}%  {name}")
