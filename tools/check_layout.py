#!/usr/bin/env python3
"""Record the vanilla link layout, and check that a modded link did not move it.

    check_layout.py record MAP LAYOUT
    check_layout.py check MAP LAYOUT [--moved OBJ ...] [--new OBJ ...]

The ROM still has data addressed by absolute symbols, so every vanilla input
section has to stay where the vanilla link put it. Units listed as --moved keep
their .rodata, .data and .bss in place but link their .text inside --region, the
vanilla unit whose .rodata slot the mod takes over; units listed as --new are
the mod's own and link there whole.
"""

import argparse
import re
import sys

SECTION_RE = re.compile(r"^ (\.text|\.rodata|\.data|\.bss)\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)\s+(\S+\.o)$", re.M)
ROM_END = 0x0A000000


def parse_map(path):
    layout = {}
    for section, addr, size, obj in SECTION_RE.findall(open(path).read()):
        if int(size, 16) == 0:
            continue
        key = (section, obj)
        if key in layout:
            sys.exit(f"error: {obj} has two {section} sections in {path}")
        layout[key] = (int(addr, 16), int(size, 16))
    return layout


def read_layout(path):
    layout = {}
    for line in open(path):
        section, obj, addr, size = line.split()
        layout[(section, obj)] = (int(addr, 16), int(size, 16))
    return layout


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("command", choices=("record", "check"))
    parser.add_argument("map")
    parser.add_argument("layout")
    parser.add_argument("--moved", nargs="*", default=[])
    parser.add_argument("--new", nargs="*", default=[])
    parser.add_argument("--region")
    parser.add_argument("--call-range", type=lambda value: int(value, 16), default=ROM_END)
    args = parser.parse_args()

    linked = parse_map(args.map)
    if args.command == "record":
        with open(args.layout, "w") as f:
            for (section, obj), (addr, size) in sorted(linked.items(), key=lambda item: item[1]):
                f.write(f"{section} {obj} {addr:#010x} {size:#x}\n")
        return

    vanilla = read_layout(args.layout)
    moved = set(args.moved)
    new = set(args.new)
    errors = []
    region = (0, ROM_END)
    for key, (addr, size) in vanilla.items():
        section, obj = key
        if section == ".text" and obj in moved:
            continue
        if obj == args.region:
            region = (addr, min(addr + size, args.call_range))
            continue
        if key not in linked:
            errors.append(f"{obj}({section}) is gone")
        elif linked[key] != (addr, size):
            now_addr, now_size = linked[key]
            errors.append(f"{obj}({section}) was {addr:#010x}+{size:#x}, is {now_addr:#010x}+{now_size:#x}")
    for key in linked:
        section, obj = key
        if key not in vanilla and obj not in new and section != ".bss":
            errors.append(f"{obj}({section}) is new in a vanilla unit")
    end = region[0]
    for (section, obj), (addr, size) in linked.items():
        if section == ".bss" or (obj not in new and not (section == ".text" and obj in moved)):
            continue
        if addr < region[0] or addr + size > region[1]:
            errors.append(f"{obj}({section}) at {addr:#010x}+{size:#x} is outside the mod region")
        end = max(end, addr + size)
    if errors:
        for error in errors[:20]:
            print(f"layout: {error}", file=sys.stderr)
        sys.exit(f"error: {len(errors)} sections moved from the vanilla layout")
    print(f"layout OK, mod uses {(end - region[0]) // 1024} KiB of {(region[1] - region[0]) // 1024} KiB")


if __name__ == "__main__":
    main()
