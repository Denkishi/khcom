# The game as a Windows program

`build/win/khcom.exe` is the game in a window of its own: mGBA's core runs
the ROM, `khcom_win.c` is the window, the sound, the keys and a controller.
It is not a port: the game is still the GBA program, run by an emulator
built into the program. The ROM is read from `khcom.gba` next to the program
and the save is kept in `khcom.sav` there.

    Arrows  move          X  A        Z  B
    A / S   L / R         Enter  Start    Backspace  Select
    F1      wide screen on and off        F11 or Alt+Enter  full screen
    Tab     hold to run fast              Esc  quit

## The wide screen

mGBA's software renderer is patched (`mgba-wide.patch`, against 0.10.5) to
draw 24 columns more on each side of the 240 the console has: 288 by 160,
close to 16:9. The game is not told: its backgrounds scroll and its sprites
are placed as ever, and the extra columns show what was already there just
off the screen. That works where the background is wider than the screen,
which is in battle; rooms and menus have backgrounds exactly as wide as the
screen, which would repeat at the edges. So the game sets `gRogueWide` while
a battle is on and the program shows the wide picture only then, and the
middle 240 columns otherwise. What the game itself leaves out stays out:
sprites wholly off its own screen are not drawn, so something walking in
from the side appears a little inside the edge, and the HUD sits where it
did, 24 columns in.

## Building

    build/venv/bin/pip install ziglang          # the cross compiler
    # mGBA's library for Windows, once, in build/win/b: see the cmake line below
    tools/pc/build.sh

`build/win/zcc`, `zcxx`, `zar` and `zranlib` are one-line scripts that run
`python -m ziglang cc|c++|ar|ranlib` (the first two with
`-target x86_64-windows-gnu`), and `build/win/toolchain.cmake` names them as
the compilers for a `CMAKE_SYSTEM_NAME` of `Windows`. The library is then
configured from `build/win/b` with

    cmake ../../mgba -DLIBMGBA_ONLY=ON -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake \
        -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_C_FLAGS=-DKHCOM_WIDE=24 -DBUILD_LTO=OFF -DBUILD_SHARED=OFF -DBUILD_STATIC=ON \
        -DM_CORE_GB=OFF -DUSE_DEBUGGERS=OFF -DUSE_GDB_STUB=OFF -DUSE_EDITLINE=OFF -DUSE_ELF=OFF \
        -DUSE_EPOXY=OFF -DUSE_FFMPEG=OFF -DUSE_LIBZIP=OFF -DUSE_LUA=OFF -DUSE_LZMA=OFF \
        -DUSE_MINIZIP=OFF -DUSE_PNG=OFF -DUSE_SQLITE3=OFF -DUSE_ZLIB=OFF -DUSE_DISCORD_RPC=OFF \
        -DENABLE_SCRIPTING=OFF

The program is built for the ROM it is copied with: it reads `gRogueWide`
at the address the link map gives, which changes from one build to the next.
Without `KHCOM_WIDE` the patched renderer draws exactly as before, which is
how the test runner in `tools/emu` is built.
