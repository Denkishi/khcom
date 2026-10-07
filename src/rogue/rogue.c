#include "rogue.h"
#include "registration_data.h"
#include "save.h"
#include "system_state.h"

// Boot: repairs the save blocks the copyright screen used to check, then goes
// straight to the title. Language select and both copyright screens are gone.
static void RogueBoot_Init(s32 arg) {
    if (SaveRepairHeader() == 1) {
        SaveClearHeader();
        SaveClearSystem();
        SaveClearFileLarge(0);
        SaveClearFileLarge(1);
        SaveClearFileSmall(0);
        SaveClearFileSmall(1);
    }

    if (SaveRepairFileLarge(0) == 1) {
        SaveClearFileLarge(0);
    }

    if (SaveRepairFileLarge(1) == 1) {
        SaveClearFileLarge(1);
    }

    if (SaveRepairFileSmall(0) == 1) {
        SaveClearFileSmall(0);
    }

    if (SaveRepairFileSmall(1) == 1) {
        SaveClearFileSmall(1);
    }

    if (SaveRepairSystem() == 1) {
        SaveClearSystem();
    }

    gLanguage = ROGUE_LANGUAGE;
}

static void RogueBoot_Update(void) {
    ModeRequest(&gModeTitle, 0);
}

static void RogueBoot_Exit(void) {
}

Mode gModeRogueBoot = {
    "mode_rogue_boot",
    RogueBoot_Init,
    RogueBoot_Update,
    RogueBoot_Exit,
};
