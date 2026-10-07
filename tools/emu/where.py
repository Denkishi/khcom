#!/usr/bin/env python3
"""Name the functions in the runner's `pc` output: play.py SCRIPT | where.py"""
import bisect
import collections
import re
import sys
from pathlib import Path

MAP = Path(__file__).resolve().parents[2] / "build/eu/com_eu.map"
symbols = sorted((int(addr, 16), name) for addr, name in re.findall(r"^\s+0x(0[89][0-9a-f]{6})\s+(\w+)$", MAP.read_text(), re.M))


def name(addr):
    i = bisect.bisect_right(symbols, (addr, "~")) - 1
    return symbols[i][1] if i >= 0 else hex(addr)


counts = collections.Counter()
for line in sys.stdin:
    match = re.match(r"pc ([0-9a-f]{8}) lr ([0-9a-f]{8})", line)
    if match:
        counts[(name(int(match.group(1), 16)), name(int(match.group(2), 16)))] += 1
    else:
        print(line, end="")
for (pc, lr), count in counts.most_common(12):
    print(f"{count:4} {pc} (lr {lr})")
