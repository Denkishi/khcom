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
 *   pc N              print the program counter and link register on each of the next N frames
 *   poke8|poke16|poke32 ADDR VALUE
 *   pokeat8|pokeat32 PTR OFFSET VALUE    write VALUE at OFFSET from the pointer stored at PTR
 *   peekat32 PTR OFFSET [LABEL]  read at OFFSET from the pointer stored at PTR
 *   callers N LO HI  run N frames and print, as "prof ADDR SAMPLES", the return addresses seen while the
 *                     program counter was in LO..HI: who calls the functions there
 *   profile N [KEYS]  run N frames an instruction at a time and print where the program counter was:
 *                     "prof ADDR SAMPLES" for each word of ROM, and the totals for RAM and for the BIOS, where it idles
 */
#include <mgba/core/config.h>
#include <mgba/core/core.h>
#include <mgba/core/blip_buf.h>
#include <mgba/core/log.h>
#include <mgba/internal/arm/arm.h>
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

// Recording, for the trailer: while it is on, every frame run is written to
// PATH.rgb as the core gives it (4 bytes a pixel) and its sound to PATH.pcm
// (16 bits, two channels, 48000 a second). `rec PATH` starts it, `rec off` ends it.
static uint32_t* sVideo;
static unsigned sWidth, sHeight;
static FILE* sRecVideo;
static FILE* sRecAudio;

static void run(struct mCore* core, unsigned keys, int frames) {
    while (frames-- > 0) {
        core->setKeys(core, keys);
        core->runFrame(core);
        if (sRecVideo) {
            static int16_t samples[4096 * 2];
            struct blip_t* left = core->getAudioChannel(core, 0);
            struct blip_t* right = core->getAudioChannel(core, 1);
            int count = blip_samples_avail(left);
            if (count > 4096) {
                count = 4096;
            }
            blip_read_samples(left, samples, count, 1);
            blip_read_samples(right, samples + 1, count, 1);
            fwrite(samples, 4, count, sRecAudio);
            fwrite(sVideo, 4, sWidth * sHeight, sRecVideo);
        }
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
    sVideo = video;
    sWidth = width;
    sHeight = height;
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
        if (!strcmp(command, "rec")) {
            if (sRecVideo) {
                fclose(sRecVideo);
                fclose(sRecAudio);
                sRecVideo = NULL;
            }
            if (strcmp(a, "off")) {
                char path[160];
                snprintf(path, sizeof(path), "%s.rgb", a);
                sRecVideo = fopen(path, "wb");
                snprintf(path, sizeof(path), "%s.pcm", a);
                sRecAudio = fopen(path, "wb");
                blip_set_rates(core->getAudioChannel(core, 0), core->frequency(core), 48000);
                blip_set_rates(core->getAudioChannel(core, 1), core->frequency(core), 48000);
                blip_clear(core->getAudioChannel(core, 0));
                blip_clear(core->getAudioChannel(core, 1));
            }
        } else if (!strcmp(command, "wait")) {
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
        } else if (!strcmp(command, "pc")) {
            int n = atoi(a);
            while (n-- > 0) {
                struct ARMCore* cpu = core->cpu;
                run(core, 0, 1);
                printf("pc %08x lr %08x\n", cpu->gprs[15], cpu->gprs[14]);
            }
        } else if (!strcmp(command, "callers")) {
            static unsigned rom[0x2000000 / 4];
            struct ARMCore* cpu = core->cpu;
            uint32_t lo = strtoul(b, NULL, 16), hi = strtoul(c, NULL, 16);
            unsigned i;
            int n = atoi(a);
            memset(rom, 0, sizeof(rom));
            while (n-- > 0) {
                uint32_t frame = core->frameCounter(core);
                while (core->frameCounter(core) == frame) {
                    uint32_t pc = cpu->gprs[15], lr = cpu->gprs[14];
                    core->step(core);
                    if (pc >= lo && pc < hi && lr >= 0x08000000 && lr < 0x0A000000) {
                        rom[(lr - 0x08000000) / 4]++;
                    }
                }
            }
            for (i = 0; i < 0x2000000 / 4; i++) {
                if (rom[i]) {
                    printf("prof %08x %u\n", 0x08000000 + i * 4, rom[i]);
                }
            }
        } else if (!strcmp(command, "profile")) {
            static unsigned rom[0x2000000 / 4];
            static unsigned iwram[0x8000 / 64];
            unsigned ram = 0, bios = 0, i;
            struct ARMCore* cpu = core->cpu;
            int n = atoi(a);
            core->setKeys(core, count > 2 ? parse_keys(b) : 0);
            memset(rom, 0, sizeof(rom));
            memset(iwram, 0, sizeof(iwram));
            while (n-- > 0) {
                uint32_t frame = core->frameCounter(core);
                while (core->frameCounter(core) == frame) {
                    uint32_t pc = cpu->gprs[15];
                    core->step(core);
                    if (pc >= 0x08000000 && pc < 0x0A000000) {
                        rom[(pc - 0x08000000) / 4]++;
                    } else if (pc >> 24 == 3) {
                        iwram[(pc & 0x7FFF) / 64]++;
                        ram++;
                    } else if (pc < 0x4000) {
                        bios++;
                    } else {
                        ram++;
                    }
                }
            }
            for (i = 0; i < 0x2000000 / 4; i++) {
                if (rom[i]) {
                    printf("prof %08x %u\n", 0x08000000 + i * 4, rom[i]);
                }
            }
            for (i = 0; i < 0x8000 / 64; i++) {
                if (iwram[i]) {
                    printf("iwram %08x %u\n", 0x03000000 + i * 64, iwram[i]);
                }
            }
            printf("prof ram %u\nprof bios %u\n", ram, bios);
        } else if (!strcmp(command, "peekat32")) {
            uint32_t base = core->busRead32(core, strtoul(a, NULL, 16));
            uint32_t addr = base + strtoul(b, NULL, 16);
            printf("%s %08x = %x\n", count > 3 ? c : "peek", addr, core->busRead32(core, addr));
        } else if (!strcmp(command, "pokeat32")) {
            uint32_t base = core->busRead32(core, strtoul(a, NULL, 16));
            core->busWrite32(core, base + strtoul(b, NULL, 16), strtoul(c, NULL, 0));
        } else if (!strcmp(command, "pokeat8")) {
            uint32_t base = core->busRead32(core, strtoul(a, NULL, 16));
            core->busWrite8(core, base + strtoul(b, NULL, 16), strtoul(c, NULL, 0));
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
