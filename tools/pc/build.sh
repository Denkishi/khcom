#!/bin/sh
# Builds the Windows program: build/win/khcom.exe, with the ROM copied next
# to it as khcom.gba. Needs the zig compiler in the build's virtualenv
# (pip install ziglang) and mGBA's library built for Windows in build/win/b,
# see tools/pc/README.md. The program is built for the ROM it is copied
# with: it reads one of the game's variables, whose address changes with the ROM.
set -e
cd "$(dirname "$0")/../.."
flag=$(awk '$2 == "gRogueWide" { print $1 }' build/eu/com_eu.map)
build/win/zcc -O2 -DKHCOM_WIDE=24 -DWIDE_FLAG=$flag -o build/win/khcom.exe tools/pc/khcom_win.c tools/pc/wide.c -Itools/pc -Ibuild/mgba/include -Ibuild/win/b/include \
    -DM_CORE_GBA build/win/b/libmgba.a -lgdi32 -lwinmm -lxinput9_1_0 -lws2_32 -lshlwapi -lshell32 -lole32 -Wl,--subsystem,windows
cp build/eu/com_eu.gba build/win/khcom.gba
ls -la build/win/khcom.exe build/win/khcom.gba
