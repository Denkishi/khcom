/* Headless test runner: plays a ROM through a script of inputs on the mGBA core.
 *
 *   run ROM SCRIPT [SAVE]
 *
 * Script lines:
 *   wait N            run N frames with no keys held
 *   press KEYS [N]    hold KEYS (e.g. A, START, UP+B) for N frames (default 2), then release for 2
 *   hold KEYS N       hold KEYS for N frames without the release
 *   shot FILE.ppm     write the current frame
 *   peek8|peek16|peek32 ADDR [LABEL]
 *   poke8|poke16|poke32 ADDR VALUE
 *   pokeat32 PTR OFFSET VALUE    write VALUE at OFFSET from the pointer stored at PTR
 *   peekat32 PTR OFFSET [LABEL]  read at OFFSET from the pointer stored at PTR
 */
#include <mgba/core/config.h>
#include <mgba/core/core.h>
#include <mgba/core/log.h>
#include <mgba-util/vfs.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char* const KEY_NAMES[] = { "A", "B", "SELECT", "START", "RIGHT", "LEFT", "UP", "DOWN", "R", "L" };

static void quiet(struct mLogger* logger, int category, enum mLogLevel level, const char* format, va_list args) {
    (void)logger; (void)category; (void)level; (void)format; (void)args;
}

static struct mLogger sLogger = { .log = quiet };

static unsigned parse_keys(char* text) {
    unsigned keys = 0;
    char* name;
    for (name = strtok(text, "+"); name; name = strtok(NULL, "+")) {
        unsigned i;
        for (i = 0; i < 10; i++) {
            if (!strcmp(name, KEY_NAMES[i])) {
                keys |= 1u << i;
                break;
            }
        }
        if (i == 10) {
            fprintf(stderr, "unknown key %s\n", name);
            exit(1);
        }
    }
    return keys;
}

static void run(struct mCore* core, unsigned keys, int frames) {
    while (frames-- > 0) {
        core->setKeys(core, keys);
        core->runFrame(core);
    }
}

int main(int argc, char** argv) {
    struct mCore* core;
    unsigned width, height;
    uint32_t* video;
    FILE* script;
    char line[256];

    if (argc < 3) {
        fprintf(stderr, "usage: run ROM SCRIPT [SAVE]\n");
        return 1;
    }
    mLogSetDefaultLogger(&sLogger);
    core = mCoreFind(argv[1]);
    if (!core) {
        fprintf(stderr, "cannot open %s\n", argv[1]);
        return 1;
    }
    core->init(core);
    mCoreInitConfig(core, NULL);
    core->desiredVideoDimensions(core, &width, &height);
    video = malloc(width * height * sizeof(*video));
    core->setVideoBuffer(core, (color_t*)video, width);
    if (!mCoreLoadFile(core, argv[1])) {
        fprintf(stderr, "cannot load %s\n", argv[1]);
        return 1;
    }
    if (argc > 3) {
        mCoreLoadSaveFile(core, argv[3], false);
    }
    core->reset(core);

    script = fopen(argv[2], "r");
    if (!script) {
        fprintf(stderr, "cannot open %s\n", argv[2]);
        return 1;
    }
    while (fgets(line, sizeof(line), script)) {
        char command[32], a[128], b[64], c[64];
        int count = sscanf(line, "%31s %127s %63s %63s", command, a, b, c);
        if (count < 1 || command[0] == '#') {
            continue;
        }
        if (!strcmp(command, "wait")) {
            run(core, 0, atoi(a));
        } else if (!strcmp(command, "press")) {
            run(core, parse_keys(a), count > 2 ? atoi(b) : 2);
            run(core, 0, 2);
        } else if (!strcmp(command, "hold")) {
            run(core, parse_keys(a), atoi(b));
        } else if (!strcmp(command, "shot")) {
            FILE* out = fopen(a, "wb");
            unsigned i;
            fprintf(out, "P6\n%u %u\n255\n", width, height);
            for (i = 0; i < width * height; i++) {
                unsigned char rgb[3] = { video[i] & 0xFF, (video[i] >> 8) & 0xFF, (video[i] >> 16) & 0xFF };
                fwrite(rgb, 1, 3, out);
            }
            fclose(out);
        } else if (!strncmp(command, "peek", 4) && command[4] != 'a') {
            uint32_t addr = strtoul(a, NULL, 16);
            int bits = atoi(command + 4);
            uint32_t value = bits == 8 ? core->busRead8(core, addr) : bits == 16 ? core->busRead16(core, addr) : core->busRead32(core, addr);
            printf("%s %08x = %x\n", count > 2 ? b : "peek", addr, value);
        } else if (!strcmp(command, "peekat32")) {
            uint32_t base = core->busRead32(core, strtoul(a, NULL, 16));
            uint32_t addr = base + strtoul(b, NULL, 16);
            printf("%s %08x = %x\n", count > 3 ? c : "peek", addr, core->busRead32(core, addr));
        } else if (!strcmp(command, "pokeat32")) {
            uint32_t base = core->busRead32(core, strtoul(a, NULL, 16));
            core->busWrite32(core, base + strtoul(b, NULL, 16), strtoul(c, NULL, 0));
        } else if (!strncmp(command, "poke", 4)) {
            uint32_t addr = strtoul(a, NULL, 16);
            uint32_t value = strtoul(b, NULL, 0);
            int bits = atoi(command + 4);
            if (bits == 8) {
                core->busWrite8(core, addr, value);
            } else if (bits == 16) {
                core->busWrite16(core, addr, value);
            } else {
                core->busWrite32(core, addr, value);
            }
        } else {
            fprintf(stderr, "unknown command %s\n", command);
            return 1;
        }
    }
    return 0;
}
