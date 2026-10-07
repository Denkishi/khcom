// The game as a Windows program: mGBA's core runs the ROM, and this is the
// window, the sound and the keys. Built by tools/pc/build.sh; the ROM is
// read from khcom.gba next to the program and the save kept in khcom.sav.
//
//   Arrows  move          X  A        Z  B
//   A / S   L / R         Enter  Start    Backspace  Select
//   F1      wide screen on and off        F11 or Alt+Enter  full screen
//   Tab     hold to run fast              Esc  quit
// A controller is read too.
#include <windows.h>
#include <mmsystem.h>
#include <xinput.h>

#include <mgba/core/core.h>
#include <mgba/core/blip_buf.h>
#include <mgba/core/log.h>
#include <mgba/core/serialize.h>
#include <mgba/gba/interface.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wide.h"

#define SAMPLE_RATE 48000
#define AUDIO_BLOCKS 8
#define AUDIO_BLOCK_SAMPLES 1024

static struct mCore* sCore;
static uint32_t* sVideo;
static uint32_t* sShown; // the picture as Windows wants it
static unsigned sWidth, sHeight; // of the core's picture
static HWND sWindow;
static int sFullscreen;
static WINDOWPLACEMENT sPlacement = { sizeof(WINDOWPLACEMENT) };
static HWAVEOUT sWave;
static WAVEHDR sBlocks[AUDIO_BLOCKS];
static int16_t sSamples[AUDIO_BLOCKS][AUDIO_BLOCK_SAMPLES * 2];
static int sBlock;
static int16_t sPending[AUDIO_BLOCK_SAMPLES * 2];
static int sPendingCount;

static void quiet(struct mLogger* logger, int category, enum mLogLevel level, const char* format, va_list args) {
    (void)logger; (void)category; (void)level; (void)format; (void)args;
}

static struct mLogger sLogger = { .log = quiet };

#ifndef WIDE_FLAG
#define WIDE_FLAG 0 // the address of the game's gRogueWide, given by the build
#endif

static void toggle_fullscreen(void) {
    DWORD style = GetWindowLong(sWindow, GWL_STYLE);
    if (!sFullscreen) {
        MONITORINFO info = { sizeof(info) };
        GetWindowPlacement(sWindow, &sPlacement);
        GetMonitorInfo(MonitorFromWindow(sWindow, MONITOR_DEFAULTTOPRIMARY), &info);
        SetWindowLong(sWindow, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW);
        SetWindowPos(sWindow, HWND_TOP, info.rcMonitor.left, info.rcMonitor.top, info.rcMonitor.right - info.rcMonitor.left,
                     info.rcMonitor.bottom - info.rcMonitor.top, SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
    } else {
        SetWindowLong(sWindow, GWL_STYLE, style | WS_OVERLAPPEDWINDOW);
        SetWindowPlacement(sWindow, &sPlacement);
        SetWindowPos(sWindow, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
    }
    sFullscreen = !sFullscreen;
}

// The part of the core's picture that is shown: all of it with the wide
// screen on, the middle 240 columns without.
static void shown_part(int* x, int* width) {
    // The game says when it draws for the wider picture: in battle. Elsewhere
    // its backgrounds are no wider than its own screen and would repeat.
    if (gWideOn && sCore->busRead8(sCore, WIDE_FLAG)) {
        *x = 0;
        *width = sWidth;
    } else {
        *x = (sWidth - GBA_VIDEO_HORIZONTAL_PIXELS) / 2;
        *width = GBA_VIDEO_HORIZONTAL_PIXELS;
    }
}

static void paint(HDC dc) {
    RECT client;
    BITMAPINFO info;
    int x, width, scale, w, h, cw, ch;
    unsigned i;

    shown_part(&x, &width);
    GetClientRect(sWindow, &client);
    cw = client.right;
    ch = client.bottom;
    // The largest whole multiple that fits, so that the pixels stay square.
    scale = cw / width < ch / (int)sHeight ? cw / width : ch / (int)sHeight;
    if (scale < 1) {
        scale = 1;
    }
    w = width * scale;
    h = sHeight * scale;
    // The core's colours have red and blue the other way round.
    for (i = 0; i < sWidth * sHeight; i++) {
        uint32_t c = sVideo[i];
        sShown[i] = ((c & 0xFF) << 16) | (c & 0xFF00) | ((c >> 16) & 0xFF);
    }
    memset(&info, 0, sizeof(info));
    info.bmiHeader.biSize = sizeof(info.bmiHeader);
    info.bmiHeader.biWidth = sWidth;
    info.bmiHeader.biHeight = -(int)sHeight;
    info.bmiHeader.biPlanes = 1;
    info.bmiHeader.biBitCount = 32;
    info.bmiHeader.biCompression = BI_RGB;
    if (w < cw || h < ch) {
        RECT bar = { 0, 0, cw, (ch - h) / 2 };
        HBRUSH black = (HBRUSH)GetStockObject(BLACK_BRUSH);
        FillRect(dc, &bar, black);
        bar.top = (ch - h) / 2 + h;
        bar.bottom = ch;
        FillRect(dc, &bar, black);
        bar.top = 0;
        bar.right = (cw - w) / 2;
        FillRect(dc, &bar, black);
        bar.left = (cw - w) / 2 + w;
        bar.right = cw;
        FillRect(dc, &bar, black);
    }
    StretchDIBits(dc, (cw - w) / 2, (ch - h) / 2, w, h, x, 0, width, sHeight, sShown, &info, DIB_RGB_COLORS, SRCCOPY);
}

static LRESULT CALLBACK window_proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) {
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_SYSKEYDOWN:
        if (wparam == VK_RETURN && (lparam & (1 << 29))) {
            toggle_fullscreen();
            return 0;
        }
        break;
    case WM_KEYDOWN:
        if (lparam & (1 << 30)) {
            break; // held, not pressed
        }
        if (wparam == VK_F11) {
            toggle_fullscreen();
        } else if (wparam == VK_F1) {
            gWideOn = !gWideOn;
        } else if (wparam == VK_ESCAPE) {
            DestroyWindow(window);
        }
        return 0;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC dc = BeginPaint(window, &ps);
        paint(dc);
        EndPaint(window, &ps);
        return 0;
    }
    case WM_ERASEBKGND:
        return 1;
    }
    return DefWindowProc(window, message, wparam, lparam);
}

static unsigned read_keys(void) {
    static const int map[10] = { 'X', 'Z', VK_BACK, VK_RETURN, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, 'S', 'A' };
    unsigned keys = 0;
    XINPUT_STATE pad;
    int i;

    if (GetForegroundWindow() != sWindow) {
        return 0;
    }
    for (i = 0; i < 10; i++) {
        if (GetAsyncKeyState(map[i]) & 0x8000) {
            keys |= 1u << i;
        }
    }
    if (XInputGetState(0, &pad) == ERROR_SUCCESS) {
        WORD b = pad.Gamepad.wButtons;
        if (b & XINPUT_GAMEPAD_A) keys |= 1 << 0;
        if (b & (XINPUT_GAMEPAD_B | XINPUT_GAMEPAD_X)) keys |= 1 << 1;
        if (b & XINPUT_GAMEPAD_BACK) keys |= 1 << 2;
        if (b & XINPUT_GAMEPAD_START) keys |= 1 << 3;
        if ((b & XINPUT_GAMEPAD_DPAD_RIGHT) || pad.Gamepad.sThumbLX > 14000) keys |= 1 << 4;
        if ((b & XINPUT_GAMEPAD_DPAD_LEFT) || pad.Gamepad.sThumbLX < -14000) keys |= 1 << 5;
        if ((b & XINPUT_GAMEPAD_DPAD_UP) || pad.Gamepad.sThumbLY > 14000) keys |= 1 << 6;
        if ((b & XINPUT_GAMEPAD_DPAD_DOWN) || pad.Gamepad.sThumbLY < -14000) keys |= 1 << 7;
        if (b & XINPUT_GAMEPAD_RIGHT_SHOULDER) keys |= 1 << 8;
        if (b & XINPUT_GAMEPAD_LEFT_SHOULDER) keys |= 1 << 9;
    }
    return keys;
}

static void audio_open(void) {
    WAVEFORMATEX format;
    int i;

    memset(&format, 0, sizeof(format));
    format.wFormatTag = WAVE_FORMAT_PCM;
    format.nChannels = 2;
    format.nSamplesPerSec = SAMPLE_RATE;
    format.wBitsPerSample = 16;
    format.nBlockAlign = 4;
    format.nAvgBytesPerSec = SAMPLE_RATE * 4;
    if (waveOutOpen(&sWave, WAVE_MAPPER, &format, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) {
        sWave = 0;
        return;
    }
    for (i = 0; i < AUDIO_BLOCKS; i++) {
        sBlocks[i].lpData = (LPSTR)sSamples[i];
        sBlocks[i].dwBufferLength = sizeof(sSamples[i]);
        sBlocks[i].dwFlags = WHDR_DONE;
    }
}

// How many blocks wait to be played: the less, the nearer the sound is to running dry.
static int audio_queued(void) {
    int i, count = 0;
    for (i = 0; i < AUDIO_BLOCKS; i++) {
        if (!(sBlocks[i].dwFlags & WHDR_DONE)) {
            count++;
        }
    }
    return count;
}

// Takes what the core has made this frame; whole blocks go to the sound card.
static void audio_frame(int fast) {
    blip_t* left = sCore->getAudioChannel(sCore, 0);
    blip_t* right = sCore->getAudioChannel(sCore, 1);
    int available = blip_samples_avail(left);

    while (available > 0) {
        int take = AUDIO_BLOCK_SAMPLES - sPendingCount;
        if (take > available) {
            take = available;
        }
        blip_read_samples(left, sPending + sPendingCount * 2, take, 1);
        blip_read_samples(right, sPending + sPendingCount * 2 + 1, take, 1);
        sPendingCount += take;
        available -= take;
        if (sPendingCount == AUDIO_BLOCK_SAMPLES) {
            WAVEHDR* block = &sBlocks[sBlock];
            sPendingCount = 0;
            // With no block free, or when running fast, the sound is dropped rather than kept late.
            if (sWave && !fast && (block->dwFlags & WHDR_DONE)) {
                if (block->dwFlags & WHDR_PREPARED) {
                    waveOutUnprepareHeader(sWave, block, sizeof(*block));
                }
                memcpy(sSamples[sBlock], sPending, sizeof(sPending));
                block->dwFlags = 0;
                waveOutPrepareHeader(sWave, block, sizeof(*block));
                waveOutWrite(sWave, block, sizeof(*block));
                sBlock = (sBlock + 1) % AUDIO_BLOCKS;
            }
        }
    }
}

static void beside_program(char* out, const char* name) {
    char* slash;
    GetModuleFileNameA(NULL, out, MAX_PATH);
    slash = strrchr(out, '\\');
    strcpy(slash ? slash + 1 : out, name);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPSTR command, int show) {
    WNDCLASSA class;
    char rom[MAX_PATH], save[MAX_PATH];
    LARGE_INTEGER frequency, next, now;
    double frame;
    RECT rect;
    MSG message;
    int running = 1;

    (void)previous; (void)command;
    beside_program(rom, "khcom.gba");
    beside_program(save, "khcom.sav");
    mLogSetDefaultLogger(&sLogger);
    sCore = mCoreFind(rom);
    if (!sCore) {
        MessageBoxA(NULL, "khcom.gba non trovato accanto al programma.", "Kingdom Hearts CoM Roguelite", MB_ICONERROR);
        return 1;
    }
    sCore->init(sCore);
    mCoreInitConfig(sCore, NULL);
    sCore->desiredVideoDimensions(sCore, &sWidth, &sHeight);
    sVideo = calloc(sWidth * sHeight, sizeof(*sVideo));
    sShown = calloc(sWidth * sHeight, sizeof(*sShown));
    sCore->setVideoBuffer(sCore, (color_t*)sVideo, sWidth);
    sCore->setAudioBufferSize(sCore, AUDIO_BLOCK_SAMPLES);
    if (!mCoreLoadFile(sCore, rom)) {
        MessageBoxA(NULL, "khcom.gba non si carica.", "Kingdom Hearts CoM Roguelite", MB_ICONERROR);
        return 1;
    }
    mCoreLoadSaveFile(sCore, save, false);
    sCore->reset(sCore);
    blip_set_rates(sCore->getAudioChannel(sCore, 0), sCore->frequency(sCore), SAMPLE_RATE);
    blip_set_rates(sCore->getAudioChannel(sCore, 1), sCore->frequency(sCore), SAMPLE_RATE);
    audio_open();

    memset(&class, 0, sizeof(class));
    class.lpfnWndProc = window_proc;
    class.hInstance = instance;
    class.hCursor = LoadCursor(NULL, IDC_ARROW);
    class.lpszClassName = "khcom";
    RegisterClassA(&class);
    rect.left = rect.top = 0;
    rect.right = sWidth * 3;
    rect.bottom = sHeight * 3;
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
    sWindow = CreateWindowA("khcom", "Kingdom Hearts: Chain of Memories - Roguelite", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                            rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, instance, NULL);
    ShowWindow(sWindow, show);

    timeBeginPeriod(1);
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&next);
    frame = frequency.QuadPart / 59.7275;
    while (running) {
        int fast;
        HDC dc;

        while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
            if (message.message == WM_QUIT) {
                running = 0;
            }
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        fast = GetForegroundWindow() == sWindow && (GetAsyncKeyState(VK_TAB) & 0x8000);
        sCore->setKeys(sCore, read_keys());
        sCore->runFrame(sCore);
        audio_frame(fast);
        dc = GetDC(sWindow);
        paint(dc);
        ReleaseDC(sWindow, dc);
        if (fast) {
            QueryPerformanceCounter(&next);
            continue;
        }
        // One frame of the console's time, a little less when the sound is
        // about to run dry and a little more when too much of it waits.
        next.QuadPart += (LONGLONG)(frame * (audio_queued() < 2 ? 0.98 : audio_queued() > 5 ? 1.02 : 1.0));
        QueryPerformanceCounter(&now);
        if (now.QuadPart > next.QuadPart + (LONGLONG)(frame * 4)) {
            next = now; // far behind: no catching up
        }
        while (now.QuadPart < next.QuadPart) {
            LONGLONG left = (next.QuadPart - now.QuadPart) * 1000 / frequency.QuadPart;
            if (left > 2) {
                Sleep((DWORD)(left - 1));
            }
            QueryPerformanceCounter(&now);
        }
    }
    timeEndPeriod(1);
    // The core keeps the save in the file as the game writes it; closing it lets go of the file.
    mCoreConfigDeinit(&sCore->config);
    sCore->deinit(sCore);
    return 0;
}
