#!/bin/sh
# Builds the headless test runner against an mGBA checkout built in build/mgba/b.
set -e
cd "$(dirname "$0")/../.."
gcc -O2 -o build/emu_run tools/emu/run.c -Ibuild/mgba/include -Ibuild/mgba/b/include \
    -DM_CORE_GBA build/mgba/b/libmgba.a -lm -lpthread $(pkg-config --libs zlib libpng 2>/dev/null)
