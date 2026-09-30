#include "registration_data.h"
#include "mode_chkbtl.h"
#include "mode_backupstat.h"
#include "gba/keys.h"
#include "mode_test_api.h"

const char* gBackupStatStateNames[3] = {
    "\x82\xC8\x82\xB5\x81\x40",
    "\x82\xB1\x82\xED\x82\xEA",
    "\x82\xA0\x82\xE8\x81\x40",
};

const BackupStatEntry gBackupStatEntryTable[6] = {
    {"\x82\x72\x82\x78\x82\x72\x82\x73\x82\x64\x82\x6C\x81\x40", 2},
    {"\x82\x72\x82\x6E\x82\x71\x82\x60\x81\x40\x81\x40\x82\x50", 64},
    {"\x82\x72\x82\x6E\x82\x71\x82\x60\x81\x40\x81\x40\x82\x51", 64},
    {"\x82\x71\x82\x68\x82\x6A\x82\x74\x81\x40\x81\x40\x82\x50", 512},
    {"\x82\x71\x82\x68\x82\x6A\x82\x74\x81\x40\x81\x40\x82\x51", 512},
    {"\x82\x72\x82\x74\x82\x72\x82\x6F\x82\x64\x82\x6D\x82\x63", 4},
};

s8 gBackupStatCursor;
s8 gBackupStatCount;
const BackupStatEntry* gBackupStatEntries;
s16 gBackupStatStates[12];

void mode_backupstat_0(void) {
    s32 i;
    s32 j;

    SetBgMode0();
    SetupBg(0, 0, 15, 0);
    EnableBg(0);
    DebugTextInit(0, 0x5400, 0x500);
    DebugTextLoadPalette(0, gWhitePalette, 32, 15);
    gBackupStatCursor = 0;
    DebugTextPrint(0, 0, 2, "\x81\x84");
    gBackupStatCount = 6;
    gBackupStatEntries = gBackupStatEntryTable;

    for (i = 0; i < gBackupStatCount; i++) {
        for (j = 0; j <= 1; j++) {
            switch (i) {
            case 0:
                gBackupStatStates[i * 2 + j] = SaveCheckHeaderSlot(j);
                break;
            case 1:
                gBackupStatStates[i * 2 + j] = SaveCheckFileLargeSlot(0, j);
                break;
            case 2:
                gBackupStatStates[i * 2 + j] = SaveCheckFileLargeSlot(1, j);
                break;
            case 3:
                gBackupStatStates[i * 2 + j] = SaveCheckFileSmallSlot(0, j);
                break;
            case 4:
                gBackupStatStates[i * 2 + j] = SaveCheckFileSmallSlot(1, j);
                break;
            case 5:
                gBackupStatStates[i * 2 + j] = SaveCheckSystemSlot(j);
                break;
            }
        }
    }

    for (i = 0; i < gBackupStatCount * 2; i++) {
        DebugTextPrint(12, i * 9, 2, gBackupStatEntries[i / 2].name);

        switch (i % 2) {
        case 0:
            DebugTextPrint(75, i * 9, 2, "\x81\x7C\x82\x50");
            break;
        case 1:
            DebugTextPrint(75, i * 9, 2, "\x81\x7C\x82\x51");
            break;
        }
        DebugTextPrint(120, i * 9, 2, gBackupStatStateNames[gBackupStatStates[i]]);
    }
}

void BackupStatApplyState(void) {
    u16 slot;

    slot = gBackupStatCursor % 2;

    switch (gBackupStatCursor / 2) {
    case 0:
        SaveSetHeaderState(slot, gBackupStatStates[gBackupStatCursor]);
        break;
    case 1:
        SaveSetFileLargeState(0, slot, gBackupStatStates[gBackupStatCursor]);
        break;
    case 2:
        SaveSetFileLargeState(1, slot, gBackupStatStates[gBackupStatCursor]);
        break;
    case 3:
        SaveSetFileSmallState(0, slot, gBackupStatStates[gBackupStatCursor]);
        break;
    case 4:
        SaveSetFileSmallState(1, slot, gBackupStatStates[gBackupStatCursor]);
        break;
    case 5:
        SaveSetSystemState(slot, gBackupStatStates[gBackupStatCursor]);
        break;
    }
    DebugTextPrint(120, gBackupStatCursor * 9, 2, gBackupStatStateNames[gBackupStatStates[gBackupStatCursor]]);
}

void mode_backupstat_1(void) {
    u8 prev;

    prev = gBackupStatCursor;

    if (GetKeysRepeat() & DPAD_UP) {
        gBackupStatCursor--;
    } else if (GetKeysRepeat() & DPAD_DOWN) {
        gBackupStatCursor++;
    }

    if (prev != gBackupStatCursor) {
        if (gBackupStatCursor < 0) {
            gBackupStatCursor = gBackupStatCount * 2 - 1;
        } else if (gBackupStatCursor >= gBackupStatCount * 2) {
            gBackupStatCursor = 0;
        }
        DebugTextPrint(0, prev * 9, 2, "\x81\x40");
        DebugTextPrint(0, gBackupStatCursor * 9, 2, "\x81\x84");
    }

    if ((GetKeysPressed() & DPAD_LEFT) != 0) {
        if (--gBackupStatStates[gBackupStatCursor] < 0) {
            gBackupStatStates[gBackupStatCursor] = 2;
        }
        BackupStatApplyState();
    } else if (GetKeysPressed() & DPAD_RIGHT) {
        if (++gBackupStatStates[gBackupStatCursor] > 2) {
            gBackupStatStates[gBackupStatCursor] = 0;
        }
        BackupStatApplyState();
    }

    if (GetKeysPressed() & (A_BUTTON | B_BUTTON | SELECT_BUTTON | START_BUTTON)) {
        ModeRequest(&gModeDebug, 0);
    } else {
        DebugTextDraw(0);
        DebugTextClear();
    }
}

void mode_backupstat_2(void) {
    DebugTextDestroy();
}

Mode gModeBackupstat = {
    "mode_backupstat",
    (ModeInitFunc)mode_backupstat_0,
    mode_backupstat_1,
    mode_backupstat_2,
};
