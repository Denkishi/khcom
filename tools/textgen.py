#!/usr/bin/env python3
import argparse
import os
import sys
import unicodedata
from pathlib import Path

import yaml

YAML_LOADER = getattr(yaml, "CSafeLoader", yaml.SafeLoader)

ROOT = Path(__file__).resolve().parent.parent
POOL_DIR = ROOT / "config" / "text"
CHARMAP_DIR = ROOT / "config" / "charmaps"
VERSIONS = ("us", "jp", "eu")
ROM_BASE = 0x08000000
FIELD_WIDTHS = {"u8": 1, "u16": 2, "u32": 4, "ptr": 4}
DIRECTIVES = {1: ".byte", 2: ".hword", 4: ".4byte"}
SHOWN_SPACES = (" ", "\u3000")
HIDDEN_CATEGORIES = ("Cc", "Cf", "Cs", "Co", "Cn", "Zl", "Zp", "Zs")
BYTES_PER_LINE = 32


class TextError(Exception):
    pass


def load_yaml(path):
    with open(path, encoding="utf-8") as handle:
        return yaml.load(handle, Loader=YAML_LOADER)


def shown(char):
    if char in "{}":
        return False
    return char in SHOWN_SPACES or unicodedata.category(char) not in HIDDEN_CATEGORIES


def aligned(position, align):
    return (position + align - 1) // align * align


class Encoding:
    def __init__(self, name, doc):
        self.name = name
        self.width = doc["width"]
        self.codec = doc.get("codec")
        self.controls = {tag: self.pack(units) for tag, units in doc["controls"].items()}
        if "END" not in self.controls:
            raise TextError(f"{name}: an encoding needs an END control")
        self.sequences = sorted(self.controls.items(), key=lambda item: -len(item[1]))
        self.chars = {}
        self.codes = {}
        for unit, char in (doc.get("chars") or {}).items():
            if not isinstance(char, str) or len(char) != 1 or char in self.codes or not shown(char) or char == "\n":
                raise TextError(f"{name}: {unit:#x} maps to {char!r}, which is not one unique visible character")
            self.chars[unit] = char
            self.codes[char] = self.pack([unit])

    def pack(self, units):
        return b"".join(unit.to_bytes(self.width, "little") for unit in units)

    def escape(self, unit):
        return "{0x%0*X}" % (2 * self.width, unit)

    def codec_char(self, data):
        if not self.codec:
            return None
        try:
            char = data.decode(self.codec)
            if len(char) != 1 or char in self.codes or not shown(char) or char.encode(self.codec) != data:
                return None
        except UnicodeError:
            return None
        return char

    def decode(self, data):
        out = []
        position = 0
        while position < len(data):
            for tag, sequence in self.sequences:
                if data.startswith(sequence, position):
                    out.append("\n" if tag == "NL" else "{%s}" % tag)
                    position += len(sequence)
                    break
            else:
                position = self.decode_char(data, position, out)
        return "".join(out)

    def decode_char(self, data, position, out):
        unit = int.from_bytes(data[position:position + self.width], "little")
        if unit in self.chars:
            out.append(self.chars[unit])
            return position + self.width
        if self.width == 2:
            char = self.codec_char(bytes([unit])) if unit < 0x100 else None
            if char is not None:
                out.append(char)
                return position + 2
        else:
            for size in (2, 1):
                char = self.codec_char(data[position:position + size]) if position + size <= len(data) else None
                if char is not None:
                    out.append(char)
                    return position + size
        out.append(self.escape(unit))
        return position + self.width

    def encode(self, text, where):
        out = bytearray()
        position = 0
        while position < len(text):
            char = text[position]
            if char == "{":
                close = text.find("}", position)
                if close < 0:
                    raise TextError(f"{where}: unclosed {{")
                out += self.tag(text[position + 1:close], where)
                position = close + 1
                continue
            if char == "}":
                raise TextError(f"{where}: }} without {{")
            if char == "\n":
                out += self.tag("NL", where)
            else:
                out += self.char(char, where)
            position += 1
        return bytes(out)

    def tag(self, tag, where):
        if tag in self.controls:
            return self.controls[tag]
        if tag.startswith("0x") and len(tag) == 2 + 2 * self.width:
            try:
                return int(tag, 16).to_bytes(self.width, "little")
            except ValueError:
                pass
        raise TextError(f"{where}: {{{tag}}} is not a control or a {self.width}-byte escape of {self.name}")

    def char(self, char, where):
        if char in self.codes:
            return self.codes[char]
        try:
            data = char.encode(self.codec) if self.codec else b""
        except UnicodeError:
            data = b""
        if data and self.width == 1:
            return data
        if len(data) == 1 and self.width == 2:
            return data + b"\0"
        raise TextError(f"{where}: {char!r} (U+{ord(char):04X}) has no code in {self.name}")

    def terminated(self, data, start):
        end = self.controls["END"]
        position = start
        while position + len(end) <= len(data):
            if data.startswith(end, position):
                return position + len(end)
            position += self.width
        return None


def load_charmap(version):
    path = CHARMAP_DIR / f"{version}.yaml"
    return {name: Encoding(f"{version}/{name}", doc) for name, doc in load_yaml(path).items()}


def pool_encoding(pool, version, charmap):
    name = pool.object(version)["encoding"]
    if name not in charmap:
        raise TextError(f"{pool.name}: config/charmaps/{version}.yaml has no encoding {name}")
    return charmap[name]


class Pool:
    def __init__(self, path):
        self.path = Path(path)
        doc = load_yaml(self.path)
        for key in ("pool", "objects", "entries"):
            if key not in doc:
                raise TextError(f"{self.path}: missing {key}")
        self.name = doc["pool"]
        if self.name != self.path.stem:
            raise TextError(f"{self.path}: pool {self.name} must be named after its file")
        self.objects = doc["objects"]
        self.types = doc.get("types", {})
        self.listed = doc["entries"]
        for version in self.objects:
            if version not in VERSIONS:
                raise TextError(f"{self.name}: unknown version {version}")

    def object(self, version):
        return self.objects.get(version)

    def entries(self, version):
        if isinstance(self.listed, dict):
            items = self.listed.get(version, [])
        else:
            items = [item for item in self.listed if isinstance(item, str) or version in item.get("versions", VERSIONS)]
        entries = [{"name": item} if isinstance(item, str) else item for item in items]
        names = set()
        for entry in entries:
            if not entry["name"].isascii() or not entry["name"].isidentifier():
                raise TextError(f"{self.name}: {entry['name']!r} is not a symbol name")
            if entry["name"] in names:
                raise TextError(f"{self.name}: {version} lists {entry['name']} twice")
            names.add(entry["name"])
        return entries

    def texts(self, version):
        return [entry for entry in self.entries(version) if "record" not in entry]

    def source(self, version):
        return ROOT / "assets" / version / "text" / f"{self.name}.txt"

    def header(self, version):
        return ROOT / "build" / version / "gen" / f"{self.name}.h"

    def generated(self, version):
        obj = self.object(version)
        return None if obj is None else ROOT / "build" / version / "gen" / obj["name"]

    def fields(self, record):
        if record not in self.types:
            raise TextError(f"{self.name}: unknown record type {record}")
        offset, align, out = 0, 1, []
        for field in self.types[record]["fields"]:
            width = FIELD_WIDTHS[field["type"]]
            offset = aligned(offset, width)
            out.append((field, width, offset))
            offset += width * field.get("count", 1)
            align = max(align, width)
        return out, aligned(offset, align), align

    def align(self, entry, version):
        if "record" in entry:
            return self.fields(entry["record"])[2]
        return entry.get("align", self.object(version)["align"])


def load_pools(directory=POOL_DIR):
    return [Pool(path) for path in sorted(Path(directory).glob("*.yaml"))]


def write_if_changed(path, content):
    path = Path(path)
    data = content if isinstance(content, bytes) else content.encode("utf-8")
    if path.exists() and path.read_bytes() == data:
        return False
    path.parent.mkdir(parents=True, exist_ok=True)
    tmp = path.with_name(path.name + ".tmp")
    tmp.write_bytes(data)
    os.replace(tmp, path)
    return True


def parse_source(pool, version, text):
    entries = {}
    lines = text.split("\n")
    index = 0
    while index < len(lines):
        line = lines[index]
        index += 1
        if not line.strip() or line.startswith("#"):
            continue
        if not line.startswith("@") or not line[1:].isidentifier():
            raise TextError(f"{pool.source(version)}:{index}: expected an @entry line")
        name, first = line[1:], index
        body = []
        while True:
            if index >= len(lines):
                raise TextError(f"{pool.source(version)}:{first}: {name} has no {{END}}")
            line = lines[index]
            index += 1
            cut = line.find("{END}")
            if cut < 0:
                body.append(line)
                continue
            if line[cut + 5:].strip():
                raise TextError(f"{pool.source(version)}:{index}: text after {{END}}")
            body.append(line[:cut + 5])
            break
        if name in entries:
            raise TextError(f"{pool.source(version)}:{first}: {name} appears twice")
        entries[name] = ("\n".join(body), first)
    return entries


def read_source(pool, version, encoding):
    path = pool.source(version)
    if not path.exists():
        raise TextError(f"{path.relative_to(ROOT)} is missing; run python3 tools/extract_assets.py {version}")
    parsed = parse_source(pool, version, path.read_text(encoding="utf-8").replace("\r\n", "\n"))
    wanted = [entry["name"] for entry in pool.texts(version)]
    missing = [name for name in wanted if name not in parsed]
    extra = sorted(set(parsed) - set(wanted))
    if missing or extra:
        raise TextError(f"{path.relative_to(ROOT)}: entries differ from config/text/{pool.name}.yaml"
                        f" (missing {missing[:3]}, unknown {extra[:3]})")
    return {name: encoding.encode(text, f"{path.relative_to(ROOT)}:{line}") for name, (text, line) in parsed.items()}


def record_values(pool, entry):
    fields, _size, _align = pool.fields(entry["record"])
    out = []
    for field, width, offset in fields:
        count = field.get("count", 1)
        values = entry.get(field["name"], [0] * count if count > 1 else 0)
        values = values if isinstance(values, list) else [values]
        if len(values) != count:
            raise TextError(f"{pool.name}: {entry['name']}.{field['name']} needs {count} values")
        out.append((field, width, offset, values))
    return out


def layout(pool, version, data_of):
    obj = pool.object(version)
    position = obj["start"]
    placed = []
    for entry in pool.entries(version):
        start = aligned(position, pool.align(entry, version))
        size = pool.fields(entry["record"])[1] if "record" in entry else len(data_of(entry, start))
        placed.append((entry, start, size))
        position = start + size
    return placed, position


def decode(version, rom):
    charmap = load_charmap(version)
    checked = written = 0
    for pool in load_pools():
        obj = pool.object(version)
        if obj is None:
            continue
        encoding = pool_encoding(pool, version, charmap)

        def rom_at(address, size):
            return rom[address - ROM_BASE:address - ROM_BASE + size]

        def found(entry, start):
            if "record" in entry:
                return b""
            end = encoding.terminated(rom, start - ROM_BASE)
            if end is None or end + ROM_BASE > obj["end"]:
                raise TextError(f"{pool.name}: {version} {entry['name']} runs past the object end")
            return rom[start - ROM_BASE:end]

        placed, position = layout(pool, version, found)
        cursor = obj["start"]
        texts = []
        for entry, start, size in placed:
            if any(rom_at(cursor, start - cursor)):
                raise TextError(f"{pool.name}: {version} padding before {entry['name']} is not zero")
            data = rom_at(start, size)
            if "record" in entry:
                check_record(pool, version, entry, data)
            else:
                text = encoding.decode(data)
                where = f"{pool.name}: {version} {entry['name']}"
                if encoding.encode(text, where) != data:
                    raise TextError(f"{where} does not re-encode to the ROM bytes")
                texts.append((entry["name"], text))
            cursor = start + size
        if not position <= obj["end"] < position + 4 or any(rom_at(position, obj["end"] - position)):
            raise TextError(f"{pool.name}: {version} entries end at {position:#x}, object ends at {obj['end']:#x}")
        source = "\n".join(f"@{name}\n{text}\n" for name, text in texts)
        reparsed = parse_source(pool, version, source)
        if [(name, reparsed[name][0]) for name, _text in texts] != texts:
            raise TextError(f"{pool.name}: {version} source does not parse back to its entries")
        checked += 1
        written += write_if_changed(pool.source(version), source)
    return checked, written


def check_record(pool, version, entry, data):
    for field, width, offset, values in record_values(pool, entry):
        if field["type"] == "ptr":
            continue
        for index, value in enumerate(values):
            at = offset + index * width
            if int.from_bytes(data[at:at + width], "little") != value:
                raise TextError(f"{pool.name}: {version} {entry['name']}.{field['name']} differs from the ROM")


def byte_lines(data):
    return [f"\t.byte {','.join(str(b) for b in data[i:i + BYTES_PER_LINE])}" for i in range(0, len(data), BYTES_PER_LINE)]


def record_lines(pool, entry):
    lines, position = [], 0
    for field, width, offset, values in record_values(pool, entry):
        if offset > position:
            lines += byte_lines(bytes(offset - position))
        lines.append(f"\t{DIRECTIVES[width]} {', '.join(str(value) for value in values)}")
        position = offset + width * len(values)
    size = pool.fields(entry["record"])[1]
    if size > position:
        lines += byte_lines(bytes(size - position))
    return lines


def emit_object(pool, version, encoded, path):
    obj = pool.object(version)
    lines = ["\t.section .rodata"]
    if obj["start"] % 4 == 0:
        lines.append("\t.balign 4")
    elif obj["start"] % 2 == 0:
        lines.append("\t.balign 2")
    placed, position = layout(pool, version, lambda entry, _start: encoded[entry["name"]])
    cursor = obj["start"]
    for entry, start, size in placed:
        if start > cursor:
            lines += byte_lines(bytes(start - cursor))
        name = entry["name"]
        lines += [f"\t.global {name}", f"\t.type {name}, %object", f"{name}:"]
        lines += record_lines(pool, entry) if "record" in entry else byte_lines(encoded[name])
        lines.append(f"\t.size {name}, .-{name}")
        cursor = start + size
    if 0 < obj["end"] - position < 4:
        lines += byte_lines(bytes(obj["end"] - position))
    write_if_changed(path, "\n".join(lines) + "\n")


def emit_header(pool, version, path):
    guard = f"GUARD_GEN_{pool.name.upper()}_H"
    lines = [f"#ifndef {guard}", f"#define {guard}", "", '#include "types.h"']
    obj = pool.object(version)
    if obj is not None and obj.get("header"):
        lines.append(f'#include "{obj["header"]}"')
    declared = [entry["name"] for entry in pool.texts(version) if entry.get("declare", True)] if obj else []
    if declared:
        lines.append("")
        lines += [f"extern {obj['ctype']} {name}[];" for name in declared]
    lines += ["", "#endif"]
    write_if_changed(path, "\n".join(lines) + "\n")


def generate(version, manifest):
    pool = Pool(manifest)
    obj = pool.object(version)
    if obj is not None:
        encoding = pool_encoding(pool, version, load_charmap(version))
        emit_object(pool, version, read_source(pool, version, encoding), pool.generated(version))
    emit_header(pool, version, pool.header(version))


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("version", choices=VERSIONS)
    parser.add_argument("manifest")
    args = parser.parse_args()
    try:
        generate(args.version, args.manifest)
    except TextError as error:
        sys.exit(f"error: {error}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
