/**
 * formation_data.c
 * Enemy Formation Data
 */

#include "formation_data.h"
#include "formation_types.h"

#ifdef VERSION_EU
#define FORMATION_LIST_DROP 1
#else
#define FORMATION_LIST_DROP 0
#endif

static const BtlFormStep sBtlFormShadow8Steps[] = {
    { 0, 25, -25, 0, 0 },
    { 0, 65, -12, 0, 1 },
    { 0, 85, 12, 0, 2 },
    { 0, 55, 25, 0, 3 },
    { 0, -55, 25, 0, 4 },
    { 0, -85, 12, 0, 5 },
    { 0, -65, -12, 0, 6 },
    { 0, -25, -25, 0, 7 },
};

static const BtlFormEntry sBtlFormShadow8 = { 8, sBtlFormShadow8Steps, 60 };

static const BtlFormStep sBtlFormShadow7Steps[] = {
    { 0, 90, 0, 0, 0 },
    { 0, 55, 25, 0, 1 },
    { 0, 40, 0, 0, 2 },
    { 0, 25, -25, 0, 3 },
    { 0, -25, -25, 0, 4 },
    { 0, -55, 25, 0, 5 },
    { 0, -64, 0, 0, 6 },
};

static const BtlFormEntry sBtlFormShadow7 = { 7, sBtlFormShadow7Steps, 60 };

static const BtlFormStep sBtlFormShadow6ASteps[] = {
    { 0, 25, -25, 0, 0 },
    { 0, 40, 0, 0, 1 },
    { 0, 25, 25, 0, 2 },
    { 0, -25, 25, 0, 3 },
    { 0, -40, 0, 0, 4 },
    { 0, -25, -25, 0, 5 },
};

static const BtlFormEntry sBtlFormShadow6A = { 6, sBtlFormShadow6ASteps, 60 };

static const BtlFormStep sBtlFormShadow6BSteps[] = {
    { 0, 25, -25, 0, 0 },
    { 0, 40, 0, 0, 1 },
    { 0, 55, 25, 0, 2 },
    { 0, -55, -25, 0, 3 },
    { 0, -40, 0, 0, 4 },
    { 0, -25, 25, 0, 5 },
};

const BtlFormEntry gBtlFormShadow6B = { 6, sBtlFormShadow6BSteps, 60 };

static const BtlFormStep sBtlFormShadow6CSteps[] = {
    { 0, 90, 0, 0, 0 },
    { 0, 64, 0, 0, 1 },
    { 0, 40, 0, 0, 2 },
    { 0, -40, 0, 0, 3 },
    { 0, -64, 0, 0, 4 },
    { 0, -90, 0, 0, 5 },
};

const BtlFormEntry gBtlFormShadow6C = { 6, sBtlFormShadow6CSteps, 60 };

static const BtlFormStep sBtlFormShadow5ASteps[] = {
    { 0, 25, -25, 0, 0 },
    { 0, 40, 0, 0, 1 },
    { 0, 55, 25, 0, 2 },
    { 0, 65, -12, 0, 3 },
    { 0, 85, 12, 0, 4 },
};

const BtlFormEntry gBtlFormShadow5A = { 5, sBtlFormShadow5ASteps, 60 };

static const BtlFormStep sBtlFormShadow5BSteps[] = {
    { 0, 25, -25, 0, 0 },
    { 0, 55, 25, 0, 1 },
    { 0, 90, 0, 0, 2 },
    { 0, -65, -12, 0, 3 },
    { 0, -85, 12, 0, 4 },
};

static const BtlFormEntry sBtlFormShadow5B = { 5, sBtlFormShadow5BSteps, 60 };

static const BtlFormStep sBtlFormShadow5CSteps[] = {
    { 0, 65, -12, 0, 0 },
    { 0, 85, 12, 0, 1 },
    { 0, -25, -25, 0, 2 },
    { 0, -40, 0, 0, 3 },
    { 0, -55, 25, 0, 4 },
};

static const BtlFormEntry sBtlFormShadow5C = { 5, sBtlFormShadow5CSteps, 60 };

static const BtlFormStep sBtlFormShadow5DSteps[] = {
    { 0, 25, -25, 0, 0 },
    { 0, 65, -12, 0, 1 },
    { 0, 90, 0, 0, 2 },
    { 0, 85, 12, 0, 3 },
    { 0, 55, 25, 0, 4 },
};

static const BtlFormEntry sBtlFormShadow5D = { 5, sBtlFormShadow5DSteps, 60 };

static const BtlFormStep sBtlFormShadow4ASteps[] = {
    { 0, 25, -25, 0, 0 },
    { 0, 55, 25, 0, 1 },
    { 0, 65, -12, 0, 2 },
    { 0, 85, 12, 0, 3 },
};

static const BtlFormEntry sBtlFormShadow4A = { 4, sBtlFormShadow4ASteps, 60 };

static const BtlFormStep sBtlFormShadow4BSteps[] = {
    { 0, 40, 0, 0, 0 },
    { 0, 65, -12, 0, 1 },
    { 0, 85, 12, 0, 2 },
    { 0, 90, 0, 0, 3 },
};

static const BtlFormEntry sBtlFormShadow4B = { 4, sBtlFormShadow4BSteps, 60 };

static const BtlFormStep sBtlFormShadow4CSteps[] = {
    { 0, 65, -12, 0, 0 },
    { 0, 85, 12, 0, 1 },
    { 0, -65, -12, 0, 2 },
    { 0, -85, 12, 0, 3 },
};

static const BtlFormEntry sBtlFormShadow4C = { 4, sBtlFormShadow4CSteps, 60 };

static const BtlFormStep sBtlFormShadow4DSteps[] = {
    { 0, -55, 25, 0, 0 },
    { 0, -85, 12, 0, 1 },
    { 0, -65, -12, 0, 2 },
    { 0, -25, -25, 0, 3 },
};

static const BtlFormEntry sBtlFormShadow4D = { 4, sBtlFormShadow4DSteps, 60 };

static const BtlFormStep sBtlFormShadow3ASteps[] = {
    { 0, 40, 0, 0, 0 },
    { 0, 65, -12, 0, 1 },
    { 0, 85, 12, 0, 2 },
};

static const BtlFormEntry sBtlFormShadow3A = { 3, sBtlFormShadow3ASteps, 60 };

static const BtlFormStep sBtlFormShadow3BSteps[] = {
    { 0, 65, -12, 0, 0 },
    { 0, 85, 12, 0, 1 },
    { 0, 90, 0, 0, 2 },
};

static const BtlFormEntry sBtlFormShadow3B = { 3, sBtlFormShadow3BSteps, 60 };

static const BtlFormStep sBtlFormShadow3CSteps[] = {
    { 0, 65, -12, 0, 0 },
    { 0, 85, 12, 0, 1 },
    { 0, -40, 0, 0, 2 },
};

static const BtlFormEntry sBtlFormShadow3C = { 3, sBtlFormShadow3CSteps, 60 };

static const BtlFormStep sBtlFormShadow3DSteps[] = {
    { 0, 25, -25, 0, 0 },
    { 0, 64, 0, 0, 1 },
    { 0, 55, 25, 0, 2 },
};

static const BtlFormEntry sBtlFormShadow3D = { 3, sBtlFormShadow3DSteps, 60 };

static const BtlFormStep sBtlFormShadow3ESteps[] = {
    { 0, -25, 25, 0, 0 },
    { 0, -64, 0, 0, 1 },
    { 0, -55, -25, 0, 2 },
};

static const BtlFormEntry sBtlFormShadow3E = { 3, sBtlFormShadow3ESteps, 60 };

static const BtlFormStep sBtlFormShadow3FSteps[] = {
    { 0, -65, -12, 0, 0 },
    { 0, -85, 12, 0, 1 },
    { 0, 40, 0, 0, 2 },
};

static const BtlFormEntry sBtlFormShadow3F = { 3, sBtlFormShadow3FSteps, 60 };

static const BtlFormStep sBtlFormShadow2ASteps[] = {
    { 0, 65, -12, 0, 0 },
    { 0, 85, 12, 0, 1 },
};

static const BtlFormEntry sBtlFormShadow2A = { 2, sBtlFormShadow2ASteps, 60 };

static const BtlFormStep sBtlFormShadow2BSteps[] = {
    { 0, 25, -25, 0, 0 },
    { 0, 55, 25, 0, 1 },
};

static const BtlFormEntry sBtlFormShadow2B = { 2, sBtlFormShadow2BSteps, 60 };

static const BtlFormStep sBtlFormShadow2CSteps[] = {
    { 0, 40, 0, 0, 0 },
    { 0, -40, 0, 0, 1 },
};

static const BtlFormEntry sBtlFormShadow2C = { 2, sBtlFormShadow2CSteps, 60 };

static const BtlFormStep sBtlFormShadow2DSteps[] = {
    { 0, 40, 0, 0, 0 },
    { 0, 90, 0, 0, 1 },
};

static const BtlFormEntry sBtlFormShadow2D = { 2, sBtlFormShadow2DSteps, 60 };

static const BtlFormStep sBtlFormShadow2ESteps[] = {
    { 0, -65, -12, 0, 0 },
    { 0, -85, 12, 0, 1 },
};

static const BtlFormEntry sBtlFormShadow2E = { 2, sBtlFormShadow2ESteps, 60 };

static const BtlFormStep sBtlFormShadow2FSteps[] = {
    { 0, -55, 25, 0, 0 },
    { 0, -25, -25, 0, 1 },
};

static const BtlFormEntry sBtlFormShadow2F = { 2, sBtlFormShadow2FSteps, 60 };

static const BtlFormStep sBtlFormShadow1Steps[] = {
    { 0, 64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormShadow1 = { 1, sBtlFormShadow1Steps, 60 };

static const BtlFormStep sBtlFormRedNocturne5Steps[] = {
    { 1, 25, -25, -30, 0 },
    { 1, 40, 0, -30, 1 },
    { 1, 55, 25, -30, 2 },
    { 1, 65, -12, -40, 3 },
    { 1, 85, 12, -40, 4 },
};

const BtlFormEntry gBtlFormRedNocturne5 = { 5, sBtlFormRedNocturne5Steps, 60 };

static const BtlFormStep sBtlFormRedNocturne4Steps[] = {
    { 1, 25, -25, -30, 0 },
    { 1, 55, 25, -30, 1 },
    { 1, 65, -12, -40, 2 },
    { 1, 85, 12, -40, 3 },
};

static const BtlFormEntry sBtlFormRedNocturne4 = { 4, sBtlFormRedNocturne4Steps, 60 };

static const BtlFormStep sBtlFormRedNocturne3ASteps[] = {
    { 1, 40, 0, -30, 0 },
    { 1, 65, -12, -40, 1 },
    { 1, 85, 12, -40, 2 },
};

const BtlFormEntry gBtlFormRedNocturne3A = { 3, sBtlFormRedNocturne3ASteps, 60 };

static const BtlFormStep sBtlFormRedNocturne3BSteps[] = {
    { 1, 65, -12, -40, 0 },
    { 1, 85, 12, -40, 1 },
    { 1, -40, 0, -30, 2 },
};

static const BtlFormEntry sBtlFormRedNocturne3B = { 3, sBtlFormRedNocturne3BSteps, 60 };

static const BtlFormStep sBtlFormRedNocturne2ASteps[] = {
    { 1, 65, -12, -40, 0 },
    { 1, 85, 12, -40, 1 },
};

static const BtlFormEntry sBtlFormRedNocturne2A = { 2, sBtlFormRedNocturne2ASteps, 60 };

static const BtlFormStep sBtlFormRedNocturne2BSteps[] = {
    { 1, -65, -12, -40, 0 },
    { 1, -85, 12, -40, 1 },
};

static const BtlFormEntry sBtlFormRedNocturne2B = { 2, sBtlFormRedNocturne2BSteps, 60 };

static const BtlFormStep sBtlFormRedNocturne1ASteps[] = {
    { 1, 64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormRedNocturne1A = { 1, sBtlFormRedNocturne1ASteps, 60 };

static const BtlFormStep sBtlFormRedNocturne1BSteps[] = {
    { 1, 25, -25, -30, 0 },
};

static const BtlFormEntry sBtlFormRedNocturne1B = { 1, sBtlFormRedNocturne1BSteps, 60 };

static const BtlFormStep sBtlFormRedNocturne1CSteps[] = {
    { 1, -25, -25, -30, 0 },
};

const BtlFormEntry gBtlFormRedNocturne1C = { 1, sBtlFormRedNocturne1CSteps, 60 };

static const BtlFormStep sBtlFormRedNocturne1DSteps[] = {
    { 1, 55, 25, -30, 0 },
};

const BtlFormEntry gBtlFormRedNocturne1D = { 1, sBtlFormRedNocturne1DSteps, 60 };

static const BtlFormStep sBtlFormRedNocturne1ESteps[] = {
    { 1, -55, 25, -30, 0 },
};

const BtlFormEntry gBtlFormRedNocturne1E = { 1, sBtlFormRedNocturne1ESteps, 60 };

static const BtlFormStep sBtlFormBlueRhapsody5Steps[] = {
    { 2, 25, -25, -30, 0 },
    { 2, 55, 25, -30, 1 },
    { 2, 90, 0, -50, 2 },
    { 2, -65, -12, -40, 3 },
    { 2, -85, 12, -40, 4 },
};

const BtlFormEntry gBtlFormBlueRhapsody5 = { 5, sBtlFormBlueRhapsody5Steps, 60 };

static const BtlFormStep sBtlFormBlueRhapsody4Steps[] = {
    { 2, 40, 0, -30, 0 },
    { 2, 65, -12, -40, 1 },
    { 2, 85, 12, -40, 2 },
    { 2, 90, 0, -50, 3 },
};

static const BtlFormEntry sBtlFormBlueRhapsody4 = { 4, sBtlFormBlueRhapsody4Steps, 60 };

static const BtlFormStep sBtlFormBlueRhapsody3Steps[] = {
    { 2, 65, -12, -40, 0 },
    { 2, 85, 12, -40, 1 },
    { 2, 90, 0, -50, 2 },
};

static const BtlFormEntry sBtlFormBlueRhapsody3 = { 3, sBtlFormBlueRhapsody3Steps, 60 };

static const BtlFormStep sBtlFormBlueRhapsody2ASteps[] = {
    { 2, 25, -25, -30, 0 },
    { 2, 55, 25, -30, 1 },
};

static const BtlFormEntry sBtlFormBlueRhapsody2A = { 2, sBtlFormBlueRhapsody2ASteps, 60 };

static const BtlFormStep sBtlFormBlueRhapsody2BSteps[] = {
    { 2, -65, -12, -40, 0 },
    { 2, -85, 12, -40, 1 },
};

static const BtlFormEntry sBtlFormBlueRhapsody2B = { 2, sBtlFormBlueRhapsody2BSteps, 60 };

static const BtlFormStep sBtlFormBlueRhapsody2CSteps[] = {
    { 2, -55, 25, -30, 0 },
    { 2, -25, -25, -30, 1 },
};

static const BtlFormEntry sBtlFormBlueRhapsody2C = { 2, sBtlFormBlueRhapsody2CSteps, 60 };

static const BtlFormStep sBtlFormBlueRhapsody1ASteps[] = {
    { 2, 64, 0, -50, 0 },
};

const BtlFormEntry gBtlFormBlueRhapsody1A = { 1, sBtlFormBlueRhapsody1ASteps, 60 };

static const BtlFormStep sBtlFormBlueRhapsody1BSteps[] = {
    { 2, 40, 0, -30, 0 },
};

static const BtlFormEntry sBtlFormBlueRhapsody1B = { 1, sBtlFormBlueRhapsody1BSteps, 60 };

static const BtlFormStep sBtlFormBlueRhapsody1CSteps[] = {
    { 2, -64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormBlueRhapsody1C = { 1, sBtlFormBlueRhapsody1CSteps, 60 };

static const BtlFormStep sBtlFormBlueRhapsody1DSteps[] = {
    { 2, 25, -25, -30, 0 },
};

const BtlFormEntry gBtlFormBlueRhapsody1D = { 1, sBtlFormBlueRhapsody1DSteps, 60 };

static const BtlFormStep sBtlFormBlueRhapsody1ESteps[] = {
    { 2, -25, -25, -30, 0 },
};

const BtlFormEntry gBtlFormBlueRhapsody1E = { 1, sBtlFormBlueRhapsody1ESteps, 60 };

static const BtlFormStep sBtlFormBlueRhapsody1FSteps[] = {
    { 2, 55, 25, -30, 0 },
};

const BtlFormEntry gBtlFormBlueRhapsody1F = { 1, sBtlFormBlueRhapsody1FSteps, 60 };

static const BtlFormStep sBtlFormBlueRhapsody1GSteps[] = {
    { 2, -55, 25, -30, 0 },
};

static const BtlFormEntry sBtlFormBlueRhapsody1G = { 1, sBtlFormBlueRhapsody1GSteps, 60 };

static const BtlFormStep sBtlFormYellowOpera5Steps[] = {
    { 3, 65, -12, -40, 0 },
    { 3, 85, 12, -40, 1 },
    { 3, -25, -25, -30, 2 },
    { 3, -40, 0, -30, 3 },
    { 3, -55, 25, -30, 4 },
};

const BtlFormEntry gBtlFormYellowOpera5 = { 5, sBtlFormYellowOpera5Steps, 60 };

static const BtlFormStep sBtlFormYellowOpera4Steps[] = {
    { 3, 65, -12, -40, 0 },
    { 3, 85, 12, -40, 1 },
    { 3, -65, -12, -40, 2 },
    { 3, -85, 12, -40, 3 },
};

static const BtlFormEntry sBtlFormYellowOpera4 = { 4, sBtlFormYellowOpera4Steps, 60 };

static const BtlFormStep sBtlFormYellowOpera3ASteps[] = {
    { 3, 65, -12, -40, 0 },
    { 3, 85, 12, -40, 1 },
    { 3, -40, 0, -30, 2 },
};

static const BtlFormEntry sBtlFormYellowOpera3A = { 3, sBtlFormYellowOpera3ASteps, 60 };

static const BtlFormStep sBtlFormYellowOpera3BSteps[] = {
    { 3, -25, 25, -30, 0 },
    { 3, -64, 0, -50, 1 },
    { 3, -55, -25, -30, 2 },
};

static const BtlFormEntry sBtlFormYellowOpera3B = { 3, sBtlFormYellowOpera3BSteps, 60 };

static const BtlFormStep sBtlFormYellowOpera2ASteps[] = {
    { 3, 65, -12, -40, 0 },
    { 3, 85, 12, -40, 1 },
};

const BtlFormEntry gBtlFormYellowOpera2A = { 2, sBtlFormYellowOpera2ASteps, 60 };

static const BtlFormStep sBtlFormYellowOpera2BSteps[] = {
    { 3, 25, -25, -30, 0 },
    { 3, 55, 25, -30, 1 },
};

static const BtlFormEntry sBtlFormYellowOpera2B = { 2, sBtlFormYellowOpera2BSteps, 60 };

static const BtlFormStep sBtlFormYellowOpera2CSteps[] = {
    { 3, 40, 0, -30, 0 },
    { 3, -40, 0, -30, 1 },
};

const BtlFormEntry gBtlFormYellowOpera2C = { 2, sBtlFormYellowOpera2CSteps, 60 };

static const BtlFormStep sBtlFormYellowOpera2DSteps[] = {
    { 3, 40, 0, -30, 0 },
    { 3, 90, 0, -50, 1 },
};

static const BtlFormEntry sBtlFormYellowOpera2D = { 2, sBtlFormYellowOpera2DSteps, 60 };

static const BtlFormStep sBtlFormYellowOpera2ESteps[] = {
    { 3, -65, -12, -40, 0 },
    { 3, -85, 12, -40, 1 },
};

static const BtlFormEntry sBtlFormYellowOpera2E = { 2, sBtlFormYellowOpera2ESteps, 60 };

static const BtlFormStep sBtlFormYellowOpera2FSteps[] = {
    { 3, -55, 25, -30, 0 },
    { 3, -25, -25, -30, 1 },
};

static const BtlFormEntry sBtlFormYellowOpera2F = { 2, sBtlFormYellowOpera2FSteps, 60 };

static const BtlFormStep sBtlFormYellowOpera1ASteps[] = {
    { 3, 64, 0, -50, 0 },
};

const BtlFormEntry gBtlFormYellowOpera1A = { 1, sBtlFormYellowOpera1ASteps, 60 };

static const BtlFormStep sBtlFormYellowOpera1BSteps[] = {
    { 3, 25, -25, -30, 0 },
};

const BtlFormEntry gBtlFormYellowOpera1B = { 1, sBtlFormYellowOpera1BSteps, 60 };

static const BtlFormStep sBtlFormYellowOpera1CSteps[] = {
    { 3, -25, -25, -30, 0 },
};

static const BtlFormEntry sBtlFormYellowOpera1C = { 1, sBtlFormYellowOpera1CSteps, 60 };

static const BtlFormStep sBtlFormYellowOpera1DSteps[] = {
    { 3, 55, 25, -30, 0 },
};

const BtlFormEntry gBtlFormYellowOpera1D = { 1, sBtlFormYellowOpera1DSteps, 60 };

static const BtlFormStep sBtlFormYellowOpera1ESteps[] = {
    { 3, -55, 25, -30, 0 },
};

const BtlFormEntry gBtlFormYellowOpera1E = { 1, sBtlFormYellowOpera1ESteps, 60 };

static const BtlFormStep sBtlFormGreenRequiem5Steps[] = {
    { 4, 65, -12, -40, 0 },
    { 4, 85, 12, -40, 1 },
    { 4, -25, -25, -30, 2 },
    { 4, -40, 0, -30, 3 },
    { 4, -55, 25, -30, 4 },
};

const BtlFormEntry gBtlFormGreenRequiem5 = { 5, sBtlFormGreenRequiem5Steps, 60 };

static const BtlFormStep sBtlFormGreenRequiem4Steps[] = {
    { 4, 65, -12, -40, 0 },
    { 4, 85, 12, -40, 1 },
    { 4, -65, -12, -40, 2 },
    { 4, -85, 12, -40, 3 },
};

static const BtlFormEntry sBtlFormGreenRequiem4 = { 4, sBtlFormGreenRequiem4Steps, 60 };

static const BtlFormStep sBtlFormGreenRequiem3ASteps[] = {
    { 4, 65, -12, -40, 0 },
    { 4, 85, 12, -40, 1 },
    { 4, -40, 0, -30, 2 },
};

const BtlFormEntry gBtlFormGreenRequiem3A = { 3, sBtlFormGreenRequiem3ASteps, 60 };

static const BtlFormStep sBtlFormGreenRequiem3BSteps[] = {
    { 4, -65, -12, -40, 0 },
    { 4, -85, 12, -40, 1 },
    { 4, 40, 0, -30, 2 },
};

static const BtlFormEntry sBtlFormGreenRequiem3B = { 3, sBtlFormGreenRequiem3BSteps, 60 };

static const BtlFormStep sBtlFormGreenRequiem2ASteps[] = {
    { 4, 65, -12, -40, 0 },
    { 4, 85, 12, -40, 1 },
};

static const BtlFormEntry sBtlFormGreenRequiem2A = { 2, sBtlFormGreenRequiem2ASteps, 60 };

static const BtlFormStep sBtlFormGreenRequiem2BSteps[] = {
    { 4, 25, -25, -30, 0 },
    { 4, 55, 25, -30, 1 },
};

const BtlFormEntry gBtlFormGreenRequiem2B = { 2, sBtlFormGreenRequiem2BSteps, 60 };

static const BtlFormStep sBtlFormGreenRequiem2CSteps[] = {
    { 4, 40, 0, -30, 0 },
    { 4, -40, 0, -30, 1 },
};

static const BtlFormEntry sBtlFormGreenRequiem2C = { 2, sBtlFormGreenRequiem2CSteps, 60 };

static const BtlFormStep sBtlFormGreenRequiem2DSteps[] = {
    { 4, -65, -12, -40, 0 },
    { 4, -85, 12, -40, 1 },
};

static const BtlFormEntry sBtlFormGreenRequiem2D = { 2, sBtlFormGreenRequiem2DSteps, 60 };

static const BtlFormStep sBtlFormGreenRequiem2ESteps[] = {
    { 4, -55, 25, -30, 0 },
    { 4, -25, -25, -30, 1 },
};

static const BtlFormEntry sBtlFormGreenRequiem2E = { 2, sBtlFormGreenRequiem2ESteps, 60 };

static const BtlFormStep sBtlFormGreenRequiem1ASteps[] = {
    { 4, 64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormGreenRequiem1A = { 1, sBtlFormGreenRequiem1ASteps, 60 };

static const BtlFormStep sBtlFormGreenRequiem1BSteps[] = {
    { 4, 25, -25, -30, 0 },
};

const BtlFormEntry gBtlFormGreenRequiem1B = { 1, sBtlFormGreenRequiem1BSteps, 60 };

static const BtlFormStep sBtlFormGreenRequiem1CSteps[] = {
    { 4, -25, -25, -30, 0 },
};

const BtlFormEntry gBtlFormGreenRequiem1C = { 1, sBtlFormGreenRequiem1CSteps, 60 };

static const BtlFormStep sBtlFormGreenRequiem1DSteps[] = {
    { 4, 55, 25, -30, 0 },
};

static const BtlFormEntry sBtlFormGreenRequiem1D = { 1, sBtlFormGreenRequiem1DSteps, 60 };

static const BtlFormStep sBtlFormGreenRequiem1ESteps[] = {
    { 4, -55, 25, -30, 0 },
};

const BtlFormEntry gBtlFormGreenRequiem1E = { 1, sBtlFormGreenRequiem1ESteps, 60 };

static const BtlFormStep sBtlFormSeaNeon6Steps[] = {
    { 5, 25, -25, -30, 0 },
    { 5, 40, 0, -30, 1 },
    { 5, 25, 25, -30, 2 },
    { 5, -25, 25, -30, 3 },
    { 5, -40, 0, -30, 4 },
    { 5, -25, -25, -30, 5 },
};

static const BtlFormEntry sBtlFormSeaNeon6 = { 6, sBtlFormSeaNeon6Steps, 60 };

static const BtlFormStep sBtlFormSeaNeon5Steps[] = {
    { 5, 25, -25, -30, 0 },
    { 5, 40, 0, -30, 1 },
    { 5, 55, 25, -30, 2 },
    { 5, 65, -12, -40, 3 },
    { 5, 85, 12, -40, 4 },
};

const BtlFormEntry gBtlFormSeaNeon5 = { 5, sBtlFormSeaNeon5Steps, 60 };

static const BtlFormStep sBtlFormSeaNeon4ASteps[] = {
    { 5, 25, -25, -30, 0 },
    { 5, 55, 25, -30, 1 },
    { 5, 65, -12, -40, 2 },
    { 5, 85, 12, -40, 3 },
};

static const BtlFormEntry sBtlFormSeaNeon4A = { 4, sBtlFormSeaNeon4ASteps, 60 };

static const BtlFormStep sBtlFormSeaNeon4BSteps[] = {
    { 5, 65, -12, -40, 0 },
    { 5, 85, 12, -40, 1 },
    { 5, -65, -12, -40, 2 },
    { 5, -85, 12, -40, 3 },
};

static const BtlFormEntry sBtlFormSeaNeon4B = { 4, sBtlFormSeaNeon4BSteps, 60 };

static const BtlFormStep sBtlFormSeaNeon3ASteps[] = {
    { 5, 40, 0, -30, 0 },
    { 5, 65, -12, -40, 1 },
    { 5, 85, 12, -40, 2 },
};

static const BtlFormEntry sBtlFormSeaNeon3A = { 3, sBtlFormSeaNeon3ASteps, 60 };

static const BtlFormStep sBtlFormSeaNeon3BSteps[] = {
    { 5, -25, 25, -30, 0 },
    { 5, -64, 0, -50, 1 },
    { 5, -55, -25, -30, 2 },
};

const BtlFormEntry gBtlFormSeaNeon3B = { 3, sBtlFormSeaNeon3BSteps, 60 };

static const BtlFormStep sBtlFormSeaNeon2Steps[] = {
    { 5, 65, -12, -40, 0 },
    { 5, 85, 12, -40, 1 },
};

const BtlFormEntry gBtlFormSeaNeon2 = { 2, sBtlFormSeaNeon2Steps, 60 };

static const BtlFormStep sBtlFormSeaNeon1Steps[] = {
    { 5, 64, 0, -50, 0 },
};

const BtlFormEntry gBtlFormSeaNeon1 = { 1, sBtlFormSeaNeon1Steps, 60 };

static const BtlFormStep sBtlFormWhiteMushroom4Steps[] = {
    { 6, 65, -12, 0, 0 },
    { 6, 85, 12, 0, 1 },
    { 6, -65, -12, 0, 2 },
    { 6, -85, 12, 0, 3 },
};

static const BtlFormEntry sBtlFormWhiteMushroom4 = { 4, sBtlFormWhiteMushroom4Steps, 60 };

static const BtlFormStep sBtlFormWhiteMushroom3Steps[] = {
    { 6, 40, 0, 0, 0 },
    { 6, 65, -12, 0, 1 },
    { 6, 85, 12, 0, 2 },
};

const BtlFormEntry gBtlFormWhiteMushroom3 = { 3, sBtlFormWhiteMushroom3Steps, 60 };

static const BtlFormStep sBtlFormWhiteMushroom2ASteps[] = {
    { 6, 25, -25, 0, 0 },
    { 6, 55, 25, 0, 1 },
};

const BtlFormEntry gBtlFormWhiteMushroom2A = { 2, sBtlFormWhiteMushroom2ASteps, 60 };

static const BtlFormStep sBtlFormWhiteMushroom2BSteps[] = {
    { 6, 40, 0, 0, 0 },
    { 6, -40, 0, 0, 1 },
};

static const BtlFormEntry sBtlFormWhiteMushroom2B = { 2, sBtlFormWhiteMushroom2BSteps, 60 };

static const BtlFormStep sBtlFormWhiteMushroom1Steps[] = {
    { 6, 64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormWhiteMushroom1 = { 1, sBtlFormWhiteMushroom1Steps, 60 };

static const BtlFormStep sBtlFormBlackFungus4Steps[] = {
    { 7, 65, -12, 0, 0 },
    { 7, 85, 12, 0, 1 },
    { 7, -65, -12, 0, 2 },
    { 7, -85, 12, 0, 3 },
};

static const BtlFormEntry sBtlFormBlackFungus4 = { 4, sBtlFormBlackFungus4Steps, 60 };

static const BtlFormStep sBtlFormBlackFungus3Steps[] = {
    { 7, 65, -12, 0, 0 },
    { 7, 85, 12, 0, 1 },
    { 7, -40, 0, 0, 2 },
};

const BtlFormEntry gBtlFormBlackFungus3 = { 3, sBtlFormBlackFungus3Steps, 60 };

static const BtlFormStep sBtlFormBlackFungus2ASteps[] = {
    { 7, 65, -12, 0, 0 },
    { 7, 85, 12, 0, 1 },
};

const BtlFormEntry gBtlFormBlackFungus2A = { 2, sBtlFormBlackFungus2ASteps, 60 };

static const BtlFormStep sBtlFormBlackFungus2BSteps[] = {
    { 7, 40, 0, 0, 0 },
    { 7, -40, 0, 0, 1 },
};

static const BtlFormEntry sBtlFormBlackFungus2B = { 2, sBtlFormBlackFungus2BSteps, 60 };

static const BtlFormStep sBtlFormBlackFungus1Steps[] = {
    { 7, 64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormBlackFungus1 = { 1, sBtlFormBlackFungus1Steps, 60 };

static const BtlFormStep sBtlFormSoldier6Steps[] = {
    { 9, 25, -25, 0, 0 },
    { 9, 40, 0, 0, 1 },
    { 9, 55, 25, 0, 2 },
    { 9, -55, -25, 0, 3 },
    { 9, -40, 0, 0, 4 },
    { 9, -25, 25, 0, 5 },
};

static const BtlFormEntry sBtlFormSoldier6 = { 6, sBtlFormSoldier6Steps, 60 };

static const BtlFormStep sBtlFormSoldier5ASteps[] = {
    { 9, 25, -25, 0, 0 },
    { 9, 55, 25, 0, 1 },
    { 9, 90, 0, 0, 2 },
    { 9, -65, -12, 0, 3 },
    { 9, -85, 12, 0, 4 },
};

const BtlFormEntry gBtlFormSoldier5A = { 5, sBtlFormSoldier5ASteps, 60 };

static const BtlFormStep sBtlFormSoldier5BSteps[] = {
    { 9, 65, -12, -40, 0 },
    { 9, 85, 12, -40, 1 },
    { 9, -25, -25, -30, 2 },
    { 9, -40, 0, -30, 3 },
    { 9, -55, 25, -30, 4 },
};

const BtlFormEntry gBtlFormSoldier5B = { 5, sBtlFormSoldier5BSteps, 60 };

static const BtlFormStep sBtlFormSoldier4ASteps[] = {
    { 9, 25, -25, 0, 0 },
    { 9, 55, 25, 0, 1 },
    { 9, 65, -12, 0, 2 },
    { 9, 85, 12, 0, 3 },
};

const BtlFormEntry gBtlFormSoldier4A = { 4, sBtlFormSoldier4ASteps, 60 };

static const BtlFormStep sBtlFormSoldier4BSteps[] = {
    { 9, 40, 0, -30, 0 },
    { 9, 65, -12, -40, 1 },
    { 9, 85, 12, -40, 2 },
    { 9, 90, 0, -50, 3 },
};

static const BtlFormEntry sBtlFormSoldier4B = { 4, sBtlFormSoldier4BSteps, 60 };

static const BtlFormStep sBtlFormSoldier4CSteps[] = {
    { 9, 65, -12, 0, 0 },
    { 9, 85, 12, 0, 1 },
    { 9, -65, -12, 0, 2 },
    { 9, -85, 12, 0, 3 },
};

static const BtlFormEntry sBtlFormSoldier4C = { 4, sBtlFormSoldier4CSteps, 60 };

static const BtlFormStep sBtlFormSoldier3ASteps[] = {
    { 9, 40, 0, -30, 0 },
    { 9, 65, -12, -40, 1 },
    { 9, 85, 12, -40, 2 },
};

const BtlFormEntry gBtlFormSoldier3A = { 3, sBtlFormSoldier3ASteps, 60 };

static const BtlFormStep sBtlFormSoldier3BSteps[] = {
    { 9, 65, -12, 0, 0 },
    { 9, 85, 12, 0, 1 },
    { 9, 90, 0, 0, 2 },
};

const BtlFormEntry gBtlFormSoldier3B = { 3, sBtlFormSoldier3BSteps, 60 };

static const BtlFormStep sBtlFormSoldier3CSteps[] = {
    { 9, 65, -12, -40, 0 },
    { 9, 85, 12, -40, 1 },
    { 9, -40, 0, -30, 2 },
};

const BtlFormEntry gBtlFormSoldier3C = { 3, sBtlFormSoldier3CSteps, 60 };

static const BtlFormStep sBtlFormSoldier3DSteps[] = {
    { 9, 25, -25, 0, 0 },
    { 9, 64, 0, 0, 1 },
    { 9, 55, 25, 0, 2 },
};

static const BtlFormEntry sBtlFormSoldier3D = { 3, sBtlFormSoldier3DSteps, 60 };

static const BtlFormStep sBtlFormSoldier3ESteps[] = {
    { 9, -25, 25, 0, 0 },
    { 9, -64, 0, 0, 1 },
    { 9, -55, -25, 0, 2 },
};

static const BtlFormEntry sBtlFormSoldier3E = { 3, sBtlFormSoldier3ESteps, 60 };

static const BtlFormStep sBtlFormSoldier2ASteps[] = {
    { 9, 65, -12, 0, 0 },
    { 9, 85, 12, 0, 1 },
};

static const BtlFormEntry sBtlFormSoldier2A = { 2, sBtlFormSoldier2ASteps, 60 };

static const BtlFormStep sBtlFormSoldier2BSteps[] = {
    { 9, 25, -25, -30, 0 },
    { 9, 55, 25, -30, 1 },
};

static const BtlFormEntry sBtlFormSoldier2B = { 2, sBtlFormSoldier2BSteps, 60 };

static const BtlFormStep sBtlFormSoldier2CSteps[] = {
    { 9, 40, 0, 0, 0 },
    { 9, -40, 0, 0, 1 },
};

static const BtlFormEntry sBtlFormSoldier2C = { 2, sBtlFormSoldier2CSteps, 60 };

static const BtlFormStep sBtlFormSoldier2DSteps[] = {
    { 9, -65, -12, 0, 0 },
    { 9, -85, 12, 0, 1 },
};

static const BtlFormEntry sBtlFormSoldier2D = { 2, sBtlFormSoldier2DSteps, 60 };

static const BtlFormStep sBtlFormSoldier1ASteps[] = {
    { 9, 64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormSoldier1A = { 1, sBtlFormSoldier1ASteps, 60 };

static const BtlFormStep sBtlFormSoldier1BSteps[] = {
    { 9, 40, 0, 0, 0 },
};

const BtlFormEntry gBtlFormSoldier1B = { 1, sBtlFormSoldier1BSteps, 60 };

static const BtlFormStep sBtlFormSoldier1CSteps[] = {
    { 9, -64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormSoldier1C = { 1, sBtlFormSoldier1CSteps, 60 };

static const BtlFormStep sBtlFormSoldier1DSteps[] = {
    { 9, -40, 0, 0, 0 },
};

const BtlFormEntry gBtlFormSoldier1D = { 1, sBtlFormSoldier1DSteps, 60 };

static const BtlFormStep sBtlFormPowerwild3Steps[] = {
    { 10, 40, 0, 0, 0 },
    { 10, 65, -12, 0, 1 },
    { 10, 85, 12, 0, 2 },
};

static const BtlFormEntry sBtlFormPowerwild3 = { 3, sBtlFormPowerwild3Steps, 60 };

static const BtlFormStep sBtlFormPowerwild2ASteps[] = {
    { 10, 25, -25, 0, 0 },
    { 10, 55, 25, 0, 1 },
};

static const BtlFormEntry sBtlFormPowerwild2A = { 2, sBtlFormPowerwild2ASteps, 60 };

static const BtlFormStep sBtlFormPowerwild2BSteps[] = {
    { 10, -65, -12, 0, 0 },
    { 10, -85, 12, 0, 1 },
};

static const BtlFormEntry sBtlFormPowerwild2B = { 2, sBtlFormPowerwild2BSteps, 60 };

static const BtlFormStep sBtlFormPowerwild1Steps[] = {
    { 10, 64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormPowerwild1 = { 1, sBtlFormPowerwild1Steps, 60 };

static const BtlFormStep sBtlFormBouncywild3Steps[] = {
    { 11, 65, -12, 0, 0 },
    { 11, 85, 12, 0, 1 },
    { 11, 90, 0, 0, 2 },
};

static const BtlFormEntry sBtlFormBouncywild3 = { 3, sBtlFormBouncywild3Steps, 60 };

static const BtlFormStep sBtlFormBouncywild2ASteps[] = {
    { 11, 40, 0, 0, 0 },
    { 11, -40, 0, 0, 1 },
};

static const BtlFormEntry sBtlFormBouncywild2A = { 2, sBtlFormBouncywild2ASteps, 60 };

static const BtlFormStep sBtlFormBouncywild2BSteps[] = {
    { 11, -55, 25, 0, 0 },
    { 11, -25, -25, 0, 1 },
};

static const BtlFormEntry sBtlFormBouncywild2B = { 2, sBtlFormBouncywild2BSteps, 60 };

static const BtlFormStep sBtlFormBouncywild1Steps[] = {
    { 11, 64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormBouncywild1 = { 1, sBtlFormBouncywild1Steps, 60 };

static const BtlFormStep sBtlFormAirSoldier4ASteps[] = {
    { 12, 25, -25, -30, 0 },
    { 12, 55, 25, -30, 1 },
    { 12, 65, -12, -40, 2 },
    { 12, 85, 12, -40, 3 },
};

static const BtlFormEntry sBtlFormAirSoldier4A = { 4, sBtlFormAirSoldier4ASteps, 60 };

static const BtlFormStep sBtlFormAirSoldier4BSteps[] = {
    { 12, 65, -12, -40, 0 },
    { 12, 85, 12, -40, 1 },
    { 12, -65, -12, -40, 2 },
    { 12, -85, 12, -40, 3 },
};

static const BtlFormEntry sBtlFormAirSoldier4B = { 4, sBtlFormAirSoldier4BSteps, 60 };

static const BtlFormStep sBtlFormAirSoldier3ASteps[] = {
    { 12, 65, -12, -40, 0 },
    { 12, 85, 12, -40, 1 },
    { 12, 90, 0, -50, 2 },
};

static const BtlFormEntry sBtlFormAirSoldier3A = { 3, sBtlFormAirSoldier3ASteps, 60 };

static const BtlFormStep sBtlFormAirSoldier3BSteps[] = {
    { 12, 65, -12, -40, 0 },
    { 12, 85, 12, -40, 1 },
    { 12, -40, 0, -30, 2 },
};

static const BtlFormEntry sBtlFormAirSoldier3B = { 3, sBtlFormAirSoldier3BSteps, 60 };

static const BtlFormStep sBtlFormAirSoldier2ASteps[] = {
    { 12, 40, 0, -30, 0 },
    { 12, -40, 0, -30, 1 },
};

static const BtlFormEntry sBtlFormAirSoldier2A = { 2, sBtlFormAirSoldier2ASteps, 60 };

static const BtlFormStep sBtlFormAirSoldier2BSteps[] = {
    { 12, -55, 25, -30, 0 },
    { 12, -25, -25, -30, 1 },
};

static const BtlFormEntry sBtlFormAirSoldier2B = { 2, sBtlFormAirSoldier2BSteps, 60 };

static const BtlFormStep sBtlFormAirSoldier1Steps[] = {
    { 12, 64, 0, -50, 0 },
};

const BtlFormEntry gBtlFormAirSoldier1 = { 1, sBtlFormAirSoldier1Steps, 60 };

static const BtlFormStep sBtlFormBandit5Steps[] = {
    { 13, 25, -25, 0, 0 },
    { 13, 55, 25, 0, 1 },
    { 13, 90, 0, 0, 2 },
    { 13, -65, -12, 0, 3 },
    { 13, -85, 12, 0, 4 },
};

const BtlFormEntry gBtlFormBandit5 = { 5, sBtlFormBandit5Steps, 60 };

static const BtlFormStep sBtlFormBandit4ASteps[] = {
    { 13, 25, -25, 0, 0 },
    { 13, 55, 25, 0, 1 },
    { 13, 65, -12, 0, 2 },
    { 13, 85, 12, 0, 3 },
};

const BtlFormEntry gBtlFormBandit4A = { 4, sBtlFormBandit4ASteps, 60 };

static const BtlFormStep sBtlFormBandit4BSteps[] = {
    { 13, 65, -12, 0, 0 },
    { 13, 85, 12, 0, 1 },
    { 13, -65, -12, 0, 2 },
    { 13, -85, 12, 0, 3 },
};

static const BtlFormEntry sBtlFormBandit4B = { 4, sBtlFormBandit4BSteps, 60 };

static const BtlFormStep sBtlFormBandit3Steps[] = {
    { 13, 65, -12, 0, 0 },
    { 13, 85, 12, 0, 1 },
    { 13, -40, 0, 0, 2 },
};

const BtlFormEntry gBtlFormBandit3 = { 3, sBtlFormBandit3Steps, 60 };

static const BtlFormStep sBtlFormBandit2ASteps[] = {
    { 13, 25, -25, 0, 0 },
    { 13, 55, 25, 0, 1 },
};

static const BtlFormEntry sBtlFormBandit2A = { 2, sBtlFormBandit2ASteps, 60 };

static const BtlFormStep sBtlFormBandit2BSteps[] = {
    { 13, -55, 25, 0, 0 },
    { 13, -25, -25, 0, 1 },
};

static const BtlFormEntry sBtlFormBandit2B = { 2, sBtlFormBandit2BSteps, 60 };

static const BtlFormStep sBtlFormBandit1ASteps[] = {
    { 13, 64, 0, 0, 0 },
};

const BtlFormEntry gBtlFormBandit1A = { 1, sBtlFormBandit1ASteps, 60 };

static const BtlFormStep sBtlFormBandit1BSteps[] = {
    { 13, 40, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormBandit1B = { 1, sBtlFormBandit1BSteps, 60 };

static const BtlFormStep sBtlFormBarrelSpider3Steps[] = {
    { 14, 40, 0, 0, 0 },
    { 14, 65, -12, 0, 1 },
    { 14, 85, 12, 0, 2 },
};

static const BtlFormEntry sBtlFormBarrelSpider3 = { 3, sBtlFormBarrelSpider3Steps, 60 };

static const BtlFormStep sBtlFormBarrelSpider2ASteps[] = {
    { 14, 65, -12, 0, 0 },
    { 14, 85, 12, 0, 1 },
};

static const BtlFormEntry sBtlFormBarrelSpider2A = { 2, sBtlFormBarrelSpider2ASteps, 60 };

static const BtlFormStep sBtlFormBarrelSpider2BSteps[] = {
    { 14, 40, 0, 0, 0 },
    { 14, -40, 0, 0, 1 },
};

static const BtlFormEntry sBtlFormBarrelSpider2B = { 2, sBtlFormBarrelSpider2BSteps, 60 };

static const BtlFormStep sBtlFormBarrelSpider2CSteps[] = {
    { 14, -65, -12, 0, 0 },
    { 14, -85, 12, 0, 1 },
};

static const BtlFormEntry sBtlFormBarrelSpider2C = { 2, sBtlFormBarrelSpider2CSteps, 60 };

static const BtlFormStep sBtlFormBarrelSpider1ASteps[] = {
    { 14, 64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormBarrelSpider1A = { 1, sBtlFormBarrelSpider1ASteps, 60 };

static const BtlFormStep sBtlFormBarrelSpider1BSteps[] = {
    { 14, -64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormBarrelSpider1B = { 1, sBtlFormBarrelSpider1BSteps, 60 };

static const BtlFormStep sBtlFormSearchGhost3Steps[] = {
    { 15, 65, -12, -40, 0 },
    { 15, 85, 12, -40, 1 },
    { 15, 90, 0, -50, 2 },
};

static const BtlFormEntry sBtlFormSearchGhost3 = { 3, sBtlFormSearchGhost3Steps, 60 };

static const BtlFormStep sBtlFormSearchGhost2ASteps[] = {
    { 15, 25, -25, -30, 0 },
    { 15, 55, 25, -30, 1 },
};

static const BtlFormEntry sBtlFormSearchGhost2A = { 2, sBtlFormSearchGhost2ASteps, 60 };

static const BtlFormStep sBtlFormSearchGhost2BSteps[] = {
    { 15, 40, 0, -30, 0 },
    { 15, -40, 0, -30, 1 },
};

static const BtlFormEntry sBtlFormSearchGhost2B = { 2, sBtlFormSearchGhost2BSteps, 60 };

static const BtlFormStep sBtlFormSearchGhost2CSteps[] = {
    { 15, -65, -12, -40, 0 },
    { 15, -85, 12, -40, 1 },
};

static const BtlFormEntry sBtlFormSearchGhost2C = { 2, sBtlFormSearchGhost2CSteps, 60 };

static const BtlFormStep sBtlFormSearchGhost1ASteps[] = {
    { 15, 64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormSearchGhost1A = { 1, sBtlFormSearchGhost1ASteps, 60 };

static const BtlFormStep sBtlFormSearchGhost1BSteps[] = {
    { 15, -64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormSearchGhost1B = { 1, sBtlFormSearchGhost1BSteps, 60 };

static const BtlFormStep sBtlFormScrewdiver2ASteps[] = {
    { 16, 65, -12, -40, 0 },
    { 16, 85, 12, -40, 1 },
};

static const BtlFormEntry sBtlFormScrewdiver2A = { 2, sBtlFormScrewdiver2ASteps, 60 };

static const BtlFormStep sBtlFormScrewdiver2BSteps[] = {
    { 16, -55, 25, -30, 0 },
    { 16, -25, -25, -30, 1 },
};

static const BtlFormEntry sBtlFormScrewdiver2B = { 2, sBtlFormScrewdiver2BSteps, 60 };

static const BtlFormStep sBtlFormScrewdiver1ASteps[] = {
    { 16, 64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormScrewdiver1A = { 1, sBtlFormScrewdiver1ASteps, 60 };

static const BtlFormStep sBtlFormScrewdiver1BSteps[] = {
    { 16, -64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormScrewdiver1B = { 1, sBtlFormScrewdiver1BSteps, 60 };

static const BtlFormStep sBtlFormScrewdiver1CSteps[] = {
    { 16, 25, -25, -30, 0 },
};

static const BtlFormEntry sBtlFormScrewdiver1C = { 1, sBtlFormScrewdiver1CSteps, 60 };

static const BtlFormStep sBtlFormScrewdiver1DSteps[] = {
    { 16, -25, -25, -30, 0 },
};

static const BtlFormEntry sBtlFormScrewdiver1D = { 1, sBtlFormScrewdiver1DSteps, 60 };

static const BtlFormStep sBtlFormScrewdiver1ESteps[] = {
    { 16, 55, 25, -30, 0 },
};

static const BtlFormEntry sBtlFormScrewdiver1E = { 1, sBtlFormScrewdiver1ESteps, 60 };

static const BtlFormStep sBtlFormScrewdiver1FSteps[] = {
    { 16, -55, 25, -30, 0 },
};

static const BtlFormEntry sBtlFormScrewdiver1F = { 1, sBtlFormScrewdiver1FSteps, 60 };

static const BtlFormStep sBtlFormWightKnight3Steps[] = {
    { 17, 65, -12, 0, 0 },
    { 17, 85, 12, 0, 1 },
    { 17, -40, 0, 0, 2 },
};

const BtlFormEntry gBtlFormWightKnight3 = { 3, sBtlFormWightKnight3Steps, 60 };

static const BtlFormStep sBtlFormWightKnight2ASteps[] = {
    { 17, 25, -25, 0, 0 },
    { 17, 55, 25, 0, 1 },
};

static const BtlFormEntry sBtlFormWightKnight2A = { 2, sBtlFormWightKnight2ASteps, 60 };

static const BtlFormStep sBtlFormWightKnight2BSteps[] = {
    { 17, 40, 0, 0, 0 },
    { 17, -40, 0, 0, 1 },
};

const BtlFormEntry gBtlFormWightKnight2B = { 2, sBtlFormWightKnight2BSteps, 60 };

static const BtlFormStep sBtlFormWightKnight2CSteps[] = {
    { 17, 65, -12, 0, 0 },
    { 17, 85, 12, 0, 1 },
};

static const BtlFormEntry sBtlFormWightKnight2C = { 2, sBtlFormWightKnight2CSteps, 60 };

static const BtlFormStep sBtlFormWightKnight2DSteps[] = {
    { 17, -55, 25, 0, 0 },
    { 17, -25, -25, 0, 1 },
};

static const BtlFormEntry sBtlFormWightKnight2D = { 2, sBtlFormWightKnight2DSteps, 60 };

static const BtlFormStep sBtlFormWightKnight1ASteps[] = {
    { 17, 64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormWightKnight1A = { 1, sBtlFormWightKnight1ASteps, 60 };

static const BtlFormStep sBtlFormWightKnight1BSteps[] = {
    { 17, -64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormWightKnight1B = { 1, sBtlFormWightKnight1BSteps, 60 };

static const BtlFormStep sBtlFormGargoyle3Steps[] = {
    { 18, 40, 0, -30, 0 },
    { 18, 65, -12, -40, 1 },
    { 18, 85, 12, -40, 2 },
};

static const BtlFormEntry sBtlFormGargoyle3 = { 3, sBtlFormGargoyle3Steps, 60 };

static const BtlFormStep sBtlFormGargoyle2ASteps[] = {
    { 18, 25, -25, -30, 0 },
    { 18, 55, 25, -30, 1 },
};

static const BtlFormEntry sBtlFormGargoyle2A = { 2, sBtlFormGargoyle2ASteps, 60 };

static const BtlFormStep sBtlFormGargoyle2BSteps[] = {
    { 18, -55, 25, -30, 0 },
    { 18, -25, -25, -30, 1 },
};

static const BtlFormEntry sBtlFormGargoyle2B = { 2, sBtlFormGargoyle2BSteps, 60 };

static const BtlFormStep sBtlFormGargoyle1ASteps[] = {
    { 18, 64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormGargoyle1A = { 1, sBtlFormGargoyle1ASteps, 60 };

static const BtlFormStep sBtlFormGargoyle1BSteps[] = {
    { 18, -64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormGargoyle1B = { 1, sBtlFormGargoyle1BSteps, 60 };

static const BtlFormStep sBtlFormPirate5Steps[] = {
    { 19, 25, -25, 0, 0 },
    { 19, 40, 0, 0, 1 },
    { 19, 55, 25, 0, 2 },
    { 19, 65, -12, 0, 3 },
    { 19, 85, 12, 0, 4 },
};

const BtlFormEntry gBtlFormPirate5 = { 5, sBtlFormPirate5Steps, 60 };

static const BtlFormStep sBtlFormPirate4Steps[] = {
    { 19, 65, -12, 0, 0 },
    { 19, 85, 12, 0, 1 },
    { 19, -65, -12, 0, 2 },
    { 19, -85, 12, 0, 3 },
};

const BtlFormEntry gBtlFormPirate4 = { 4, sBtlFormPirate4Steps, 60 };

static const BtlFormStep sBtlFormPirate3ASteps[] = {
    { 19, 65, -12, 0, 0 },
    { 19, 85, 12, 0, 1 },
    { 19, 90, 0, 0, 2 },
};

static const BtlFormEntry sBtlFormPirate3A = { 3, sBtlFormPirate3ASteps, 60 };

static const BtlFormStep sBtlFormPirate3BSteps[] = {
    { 19, -65, -12, 0, 0 },
    { 19, -85, 12, 0, 1 },
    { 19, 40, 0, 0, 2 },
};

static const BtlFormEntry sBtlFormPirate3B = { 3, sBtlFormPirate3BSteps, 60 };

static const BtlFormStep sBtlFormPirate2ASteps[] = {
    { 19, 65, -12, 0, 0 },
    { 19, 85, 12, 0, 1 },
};

const BtlFormEntry gBtlFormPirate2A = { 2, sBtlFormPirate2ASteps, 60 };

static const BtlFormStep sBtlFormPirate2BSteps[] = {
    { 19, -65, -12, 0, 0 },
    { 19, -85, 12, 0, 1 },
};

const BtlFormEntry gBtlFormPirate2B = { 2, sBtlFormPirate2BSteps, 60 };

static const BtlFormStep sBtlFormPirate2CSteps[] = {
    { 19, 40, 0, 0, 0 },
    { 19, -40, 0, 0, 1 },
};

static const BtlFormEntry sBtlFormPirate2C = { 2, sBtlFormPirate2CSteps, 60 };

static const BtlFormStep sBtlFormPirate1Steps[] = {
    { 19, 64, 0, 0, 0 },
};

const BtlFormEntry gBtlFormPirate1 = { 1, sBtlFormPirate1Steps, 60 };

static const BtlFormStep sBtlFormAirPirate2ASteps[] = {
    { 20, 25, -25, -30, 0 },
    { 20, 55, 25, -30, 1 },
};

static const BtlFormEntry sBtlFormAirPirate2A = { 2, sBtlFormAirPirate2ASteps, 60 };

static const BtlFormStep sBtlFormAirPirate2BSteps[] = {
    { 20, 40, 0, -30, 0 },
    { 20, -40, 0, -30, 1 },
};

static const BtlFormEntry sBtlFormAirPirate2B = { 2, sBtlFormAirPirate2BSteps, 60 };

static const BtlFormStep sBtlFormAirPirate2CSteps[] = {
    { 20, -55, 25, -30, 0 },
    { 20, -25, -25, -30, 1 },
};

static const BtlFormEntry sBtlFormAirPirate2C = { 2, sBtlFormAirPirate2CSteps, 60 };

static const BtlFormStep sBtlFormAirPirate1ASteps[] = {
    { 20, 64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormAirPirate1A = { 1, sBtlFormAirPirate1ASteps, 60 };

static const BtlFormStep sBtlFormAirPirate1BSteps[] = {
    { 20, -64, 0, -50, 0 },
};

const BtlFormEntry gBtlFormAirPirate1B = { 1, sBtlFormAirPirate1BSteps, 60 };

static const BtlFormStep sBtlFormAirPirate1CSteps[] = {
    { 20, 25, -25, -30, 0 },
};

static const BtlFormEntry sBtlFormAirPirate1C = { 1, sBtlFormAirPirate1CSteps, 60 };

static const BtlFormStep sBtlFormDarkball2ASteps[] = {
    { 21, 65, -12, -40, 0 },
    { 21, 85, 12, -40, 1 },
};

const BtlFormEntry gBtlFormDarkball2A = { 2, sBtlFormDarkball2ASteps, 60 };

static const BtlFormStep sBtlFormDarkball2BSteps[] = {
    { 21, 25, -25, -30, 0 },
    { 21, 55, 25, -30, 1 },
};

static const BtlFormEntry sBtlFormDarkball2B = { 2, sBtlFormDarkball2BSteps, 60 };

static const BtlFormStep sBtlFormDarkball2CSteps[] = {
    { 21, 40, 0, -30, 0 },
    { 21, -40, 0, -30, 1 },
};

static const BtlFormEntry sBtlFormDarkball2C = { 2, sBtlFormDarkball2CSteps, 60 };

static const BtlFormStep sBtlFormDarkball2DSteps[] = {
    { 21, 40, 0, -30, 0 },
    { 21, 90, 0, -50, 1 },
};

static const BtlFormEntry sBtlFormDarkball2D = { 2, sBtlFormDarkball2DSteps, 60 };

static const BtlFormStep sBtlFormDarkball2ESteps[] = {
    { 21, -65, -12, -40, 0 },
    { 21, -85, 12, -40, 1 },
};

static const BtlFormEntry sBtlFormDarkball2E = { 2, sBtlFormDarkball2ESteps, 60 };

static const BtlFormStep sBtlFormDarkball2FSteps[] = {
    { 21, -55, 25, -30, 0 },
    { 21, -25, -25, -30, 1 },
};

static const BtlFormEntry sBtlFormDarkball2F = { 2, sBtlFormDarkball2FSteps, 60 };

static const BtlFormStep sBtlFormDarkball1ASteps[] = {
    { 21, 64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormDarkball1A = { 1, sBtlFormDarkball1ASteps, 60 };

static const BtlFormStep sBtlFormDarkball1BSteps[] = {
    { 21, -64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormDarkball1B = { 1, sBtlFormDarkball1BSteps, 60 };

static const BtlFormStep sBtlFormDarkball1CSteps[] = {
    { 21, 25, -25, -30, 0 },
};

static const BtlFormEntry sBtlFormDarkball1C = { 1, sBtlFormDarkball1CSteps, 60 };

static const BtlFormStep sBtlFormDarkball1DSteps[] = {
    { 21, -25, -25, -30, 0 },
};

static const BtlFormEntry sBtlFormDarkball1D = { 1, sBtlFormDarkball1DSteps, 60 };

static const BtlFormStep sBtlFormDarkball1ESteps[] = {
    { 21, 55, 25, -30, 0 },
};

static const BtlFormEntry sBtlFormDarkball1E = { 1, sBtlFormDarkball1ESteps, 60 };

static const BtlFormStep sBtlFormDarkball1FSteps[] = {
    { 21, -55, 25, -30, 0 },
};

static const BtlFormEntry sBtlFormDarkball1F = { 1, sBtlFormDarkball1FSteps, 60 };

static const BtlFormStep sBtlFormWyvern2Steps[] = {
    { 22, 65, -12, -40, 0 },
    { 22, 85, 12, -40, 1 },
};

static const BtlFormEntry sBtlFormWyvern2 = { 2, sBtlFormWyvern2Steps, 60 };

static const BtlFormStep sBtlFormWyvern1ASteps[] = {
    { 22, 64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormWyvern1A = { 1, sBtlFormWyvern1ASteps, 60 };

static const BtlFormStep sBtlFormWyvern1BSteps[] = {
    { 22, -64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormWyvern1B = { 1, sBtlFormWyvern1BSteps, 60 };

static const BtlFormStep sBtlFormWizard3Steps[] = {
    { 23, 65, -12, -40, 0 },
    { 23, 85, 12, -40, 1 },
    { 23, 90, 0, -50, 2 },
};

const BtlFormEntry gBtlFormWizard3 = { 3, sBtlFormWizard3Steps, 60 };

static const BtlFormStep sBtlFormWizard2Steps[] = {
    { 23, 40, 0, -30, 0 },
    { 23, -40, 0, -30, 1 },
};

static const BtlFormEntry sBtlFormWizard2 = { 2, sBtlFormWizard2Steps, 60 };

static const BtlFormStep sBtlFormWizard1ASteps[] = {
    { 23, 64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormWizard1A = { 1, sBtlFormWizard1ASteps, 60 };

static const BtlFormStep sBtlFormWizard1BSteps[] = {
    { 23, -64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormWizard1B = { 1, sBtlFormWizard1BSteps, 60 };

static const BtlFormStep sBtlFormNeoshadow3ASteps[] = {
    { 24, 40, 0, 0, 0 },
    { 24, 65, -12, 0, 1 },
    { 24, 85, 12, 0, 2 },
};

const BtlFormEntry gBtlFormNeoshadow3A = { 3, sBtlFormNeoshadow3ASteps, 60 };

static const BtlFormStep sBtlFormNeoshadow3BSteps[] = {
    { 24, 65, -12, 0, 0 },
    { 24, 85, 12, 0, 1 },
    { 24, -40, 0, 0, 2 },
};

static const BtlFormEntry sBtlFormNeoshadow3B = { 3, sBtlFormNeoshadow3BSteps, 60 };

static const BtlFormStep sBtlFormNeoshadow2Steps[] = {
    { 24, 65, -12, 0, 0 },
    { 24, 85, 12, 0, 1 },
};

static const BtlFormEntry sBtlFormNeoshadow2 = { 2, sBtlFormNeoshadow2Steps, 60 };

static const BtlFormStep sBtlFormNeoshadow1ASteps[] = {
    { 24, 64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormNeoshadow1A = { 1, sBtlFormNeoshadow1ASteps, 60 };

static const BtlFormStep sBtlFormNeoshadow1BSteps[] = {
    { 24, -64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormNeoshadow1B = { 1, sBtlFormNeoshadow1BSteps, 60 };

static const BtlFormStep sBtlFormLargeBody2ASteps[] = {
    { 25, 65, -12, 0, 0 },
    { 25, 85, 12, 0, 1 },
};

const BtlFormEntry gBtlFormLargeBody2A = { 2, sBtlFormLargeBody2ASteps, 60 };

static const BtlFormStep sBtlFormLargeBody2BSteps[] = {
    { 25, 40, 0, 0, 0 },
    { 25, -40, 0, 0, 1 },
};

static const BtlFormEntry sBtlFormLargeBody2B = { 2, sBtlFormLargeBody2BSteps, 60 };

static const BtlFormStep sBtlFormLargeBody1ASteps[] = {
    { 25, 64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormLargeBody1A = { 1, sBtlFormLargeBody1ASteps, 60 };

static const BtlFormStep sBtlFormLargeBody1BSteps[] = {
    { 25, -64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormLargeBody1B = { 1, sBtlFormLargeBody1BSteps, 60 };

static const BtlFormStep sBtlFormFatBandit2ASteps[] = {
    { 26, 25, -25, 0, 0 },
    { 26, 55, 25, 0, 1 },
};

const BtlFormEntry gBtlFormFatBandit2A = { 2, sBtlFormFatBandit2ASteps, 60 };

static const BtlFormStep sBtlFormFatBandit2BSteps[] = {
    { 26, 40, 0, 0, 0 },
    { 26, -40, 0, 0, 1 },
};

static const BtlFormEntry sBtlFormFatBandit2B = { 2, sBtlFormFatBandit2BSteps, 60 };

static const BtlFormStep sBtlFormFatBandit1ASteps[] = {
    { 26, -64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormFatBandit1A = { 1, sBtlFormFatBandit1ASteps, 60 };

static const BtlFormStep sBtlFormFatBandit1BSteps[] = {
    { 26, 64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormFatBandit1B = { 1, sBtlFormFatBandit1BSteps, 60 };

static const BtlFormStep sBtlFormAquatank2Steps[] = {
    { 27, 65, -12, -40, 0 },
    { 27, 85, 12, -40, 1 },
};

const BtlFormEntry gBtlFormAquatank2 = { 2, sBtlFormAquatank2Steps, 60 };

static const BtlFormStep sBtlFormAquatank1ASteps[] = {
    { 27, 64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormAquatank1A = { 1, sBtlFormAquatank1ASteps, 60 };

static const BtlFormStep sBtlFormAquatank1BSteps[] = {
    { 27, -64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormAquatank1B = { 1, sBtlFormAquatank1BSteps, 60 };

static const BtlFormStep sBtlFormDefender2Steps[] = {
    { 28, 25, -25, 0, 0 },
    { 28, 55, 25, 0, 1 },
};

static const BtlFormEntry sBtlFormDefender2 = { 2, sBtlFormDefender2Steps, 60 };

static const BtlFormStep sBtlFormDefender1Steps[] = {
    { 28, 64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormDefender1 = { 1, sBtlFormDefender1Steps, 60 };

static const BtlFormStep sBtlFormTornadoStep5ASteps[] = {
    { 29, 25, -25, 0, 0 },
    { 29, 40, 0, 0, 1 },
    { 29, 55, 25, 0, 2 },
    { 29, 65, -12, 0, 3 },
    { 29, 85, 12, 0, 4 },
};

const BtlFormEntry gBtlFormTornadoStep5A = { 5, sBtlFormTornadoStep5ASteps, 60 };

static const BtlFormStep sBtlFormTornadoStep5BSteps[] = {
    { 29, 25, -25, 0, 0 },
    { 29, 55, 25, 0, 1 },
    { 29, 90, 0, 0, 2 },
    { 29, -65, -12, 0, 3 },
    { 29, -85, 12, 0, 4 },
};

static const BtlFormEntry sBtlFormTornadoStep5B = { 5, sBtlFormTornadoStep5BSteps, 60 };

static const BtlFormStep sBtlFormTornadoStep4Steps[] = {
    { 29, 25, -25, 0, 0 },
    { 29, 55, 25, 0, 1 },
    { 29, 65, -12, 0, 2 },
    { 29, 85, 12, 0, 3 },
};

const BtlFormEntry gBtlFormTornadoStep4 = { 4, sBtlFormTornadoStep4Steps, 60 };

static const BtlFormStep sBtlFormTornadoStep3ASteps[] = {
    { 29, 40, 0, 0, 0 },
    { 29, 65, -12, 0, 1 },
    { 29, 85, 12, 0, 2 },
};

static const BtlFormEntry sBtlFormTornadoStep3A = { 3, sBtlFormTornadoStep3ASteps, 60 };

static const BtlFormStep sBtlFormTornadoStep3BSteps[] = {
    { 29, 25, -25, 0, 0 },
    { 29, 64, 0, 0, 1 },
    { 29, 55, 25, 0, 2 },
};

static const BtlFormEntry sBtlFormTornadoStep3B = { 3, sBtlFormTornadoStep3BSteps, 60 };

static const BtlFormStep sBtlFormTornadoStep3CSteps[] = {
    { 29, -25, 25, 0, 0 },
    { 29, -64, 0, 0, 1 },
    { 29, -55, -25, 0, 2 },
};

static const BtlFormEntry sBtlFormTornadoStep3C = { 3, sBtlFormTornadoStep3CSteps, 60 };

static const BtlFormStep sBtlFormTornadoStep2ASteps[] = {
    { 29, 65, -12, 0, 0 },
    { 29, 85, 12, 0, 1 },
};

const BtlFormEntry gBtlFormTornadoStep2A = { 2, sBtlFormTornadoStep2ASteps, 60 };

static const BtlFormStep sBtlFormTornadoStep2BSteps[] = {
    { 29, 40, 0, 0, 0 },
    { 29, -40, 0, 0, 1 },
};

static const BtlFormEntry sBtlFormTornadoStep2B = { 2, sBtlFormTornadoStep2BSteps, 60 };

static const BtlFormStep sBtlFormTornadoStep2CSteps[] = {
    { 29, -65, -12, 0, 0 },
    { 29, -85, 12, 0, 1 },
};

static const BtlFormEntry sBtlFormTornadoStep2C = { 2, sBtlFormTornadoStep2CSteps, 60 };

static const BtlFormStep sBtlFormTornadoStep2DSteps[] = {
    { 29, -55, 25, 0, 0 },
    { 29, -25, -25, 0, 1 },
};

const BtlFormEntry gBtlFormTornadoStep2D = { 2, sBtlFormTornadoStep2DSteps, 60 };

static const BtlFormStep sBtlFormTornadoStep1Steps[] = {
    { 29, 64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormTornadoStep1 = { 1, sBtlFormTornadoStep1Steps, 60 };

static const BtlFormStep sBtlFormCrescendo5Steps[] = {
    { 30, 25, -25, 0, 0 },
    { 30, 40, 0, 0, 1 },
    { 30, 55, 25, 0, 2 },
    { 30, 65, -12, 0, 3 },
    { 30, 85, 12, 0, 4 },
};

static const BtlFormEntry sBtlFormCrescendo5 = { 5, sBtlFormCrescendo5Steps, 60 };

static const BtlFormStep sBtlFormCrescendo4Steps[] = {
    { 30, 25, -25, 0, 0 },
    { 30, 55, 25, 0, 1 },
    { 30, 65, -12, 0, 2 },
    { 30, 85, 12, 0, 3 },
};

const BtlFormEntry gBtlFormCrescendo4 = { 4, sBtlFormCrescendo4Steps, 60 };

static const BtlFormStep sBtlFormCrescendo3ASteps[] = {
    { 30, 40, 0, 0, 0 },
    { 30, 65, -12, 0, 1 },
    { 30, 85, 12, 0, 2 },
};

const BtlFormEntry gBtlFormCrescendo3A = { 3, sBtlFormCrescendo3ASteps, 60 };

static const BtlFormStep sBtlFormCrescendo3BSteps[] = {
    { 30, 25, -25, 0, 0 },
    { 30, 64, 0, 0, 1 },
    { 30, 55, 25, 0, 2 },
};

static const BtlFormEntry sBtlFormCrescendo3B = { 3, sBtlFormCrescendo3BSteps, 60 };

static const BtlFormStep sBtlFormCrescendo3CSteps[] = {
    { 30, -25, 25, 0, 0 },
    { 30, -64, 0, 0, 1 },
    { 30, -55, -25, 0, 2 },
};

static const BtlFormEntry sBtlFormCrescendo3C = { 3, sBtlFormCrescendo3CSteps, 60 };

static const BtlFormStep sBtlFormCrescendo2ASteps[] = {
    { 30, 65, -12, 0, 0 },
    { 30, 85, 12, 0, 1 },
};

static const BtlFormEntry sBtlFormCrescendo2A = { 2, sBtlFormCrescendo2ASteps, 60 };

static const BtlFormStep sBtlFormCrescendo2BSteps[] = {
    { 30, -65, -12, 0, 0 },
    { 30, -85, 12, 0, 1 },
};

static const BtlFormEntry sBtlFormCrescendo2B = { 2, sBtlFormCrescendo2BSteps, 60 };

static const BtlFormStep sBtlFormCrescendo2CSteps[] = {
    { 30, -55, 25, 0, 0 },
    { 30, -25, -25, 0, 1 },
};

static const BtlFormEntry sBtlFormCrescendo2C = { 2, sBtlFormCrescendo2CSteps, 60 };

static const BtlFormStep sBtlFormCrescendo1Steps[] = {
    { 30, 64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormCrescendo1 = { 1, sBtlFormCrescendo1Steps, 60 };

static const BtlFormStep sBtlFormCreeperPlant6Steps[] = {
    { 31, 25, -25, 0, 0 },
    { 31, 40, 0, 0, 1 },
    { 31, 25, 25, 0, 2 },
    { 31, -25, 25, 0, 3 },
    { 31, -40, 0, 0, 4 },
    { 31, -25, -25, 0, 5 },
};

static const BtlFormEntry sBtlFormCreeperPlant6 = { 6, sBtlFormCreeperPlant6Steps, 60 };

static const BtlFormStep sBtlFormCreeperPlant5ASteps[] = {
    { 31, 25, -25, 0, 0 },
    { 31, 40, 0, 0, 1 },
    { 31, 55, 25, 0, 2 },
    { 31, 65, -12, 0, 3 },
    { 31, 85, 12, 0, 4 },
};

const BtlFormEntry gBtlFormCreeperPlant5A = { 5, sBtlFormCreeperPlant5ASteps, 60 };

static const BtlFormStep sBtlFormCreeperPlant5BSteps[] = {
    { 31, 25, -25, 0, 0 },
    { 31, 55, 25, 0, 1 },
    { 31, 90, 0, 0, 2 },
    { 31, -65, -12, 0, 3 },
    { 31, -85, 12, 0, 4 },
};

static const BtlFormEntry sBtlFormCreeperPlant5B = { 5, sBtlFormCreeperPlant5BSteps, 60 };

static const BtlFormStep sBtlFormCreeperPlant4Steps[] = {
    { 31, 25, -25, 0, 0 },
    { 31, 55, 25, 0, 1 },
    { 31, 65, -12, 0, 2 },
    { 31, 85, 12, 0, 3 },
};

static const BtlFormEntry sBtlFormCreeperPlant4 = { 4, sBtlFormCreeperPlant4Steps, 60 };

static const BtlFormStep sBtlFormCreeperPlant3ASteps[] = {
    { 31, 40, 0, 0, 0 },
    { 31, 65, -12, 0, 1 },
    { 31, 85, 12, 0, 2 },
};

const BtlFormEntry gBtlFormCreeperPlant3A = { 3, sBtlFormCreeperPlant3ASteps, 60 };

static const BtlFormStep sBtlFormCreeperPlant3BSteps[] = {
    { 31, -65, -12, 0, 0 },
    { 31, -85, 12, 0, 1 },
    { 31, 40, 0, 0, 2 },
};

static const BtlFormEntry sBtlFormCreeperPlant3B = { 3, sBtlFormCreeperPlant3BSteps, 60 };

static const BtlFormStep sBtlFormCreeperPlant2ASteps[] = {
    { 31, 65, -12, 0, 0 },
    { 31, 85, 12, 0, 1 },
};

static const BtlFormEntry sBtlFormCreeperPlant2A = { 2, sBtlFormCreeperPlant2ASteps, 60 };

static const BtlFormStep sBtlFormCreeperPlant1Steps[] = {
    { 31, 64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormCreeperPlant1 = { 1, sBtlFormCreeperPlant1Steps, 60 };

static const BtlFormStep sBtlFormCreeperPlant2BSteps[] = {
    { 31, 40, 0, 0, 0 },
    { 31, -40, 0, 0, 1 },
};

static const BtlFormEntry sBtlFormCreeperPlant2B = { 2, sBtlFormCreeperPlant2BSteps, 60 };

static const BtlFormStep sBtlFormCreeperPlant2CSteps[] = {
    { 31, -65, -12, 0, 0 },
    { 31, -85, 12, 0, 1 },
};

static const BtlFormEntry sBtlFormCreeperPlant2C = { 2, sBtlFormCreeperPlant2CSteps, 60 };

static const BtlFormStep sBtlFormCardSoldierSpade3Steps[] = {
    { 46, 65, -12, 0, 0 },
    { 46, 85, 12, 0, 1 },
    { 46, -40, 0, 0, 2 },
};

static const BtlFormEntry sBtlFormCardSoldierSpade3 = { 3, sBtlFormCardSoldierSpade3Steps, 60 };

static const BtlFormStep sBtlFormCardSoldierSpade2Steps[] = {
    { 46, -55, 25, 0, 0 },
    { 46, -25, -25, 0, 1 },
};

static const BtlFormEntry sBtlFormCardSoldierSpade2 = { 2, sBtlFormCardSoldierSpade2Steps, 60 };

static const BtlFormStep sBtlFormCardSoldierSpade1Steps[] = {
    { 46, 64, 0, 0, 0 },
};

const BtlFormEntry gBtlFormCardSoldierSpade1 = { 1, sBtlFormCardSoldierSpade1Steps, 60 };

static const BtlFormStep sBtlFormCardSoldierHeart3Steps[] = {
    { 47, 65, -12, 0, 0 },
    { 47, 85, 12, 0, 1 },
    { 47, 90, 0, 0, 2 },
};

const BtlFormEntry gBtlFormCardSoldierHeart3 = { 3, sBtlFormCardSoldierHeart3Steps, 60 };

static const BtlFormStep sBtlFormCardSoldierHeart2Steps[] = {
    { 47, 25, -25, 0, 0 },
    { 47, 55, 25, 0, 1 },
};

const BtlFormEntry gBtlFormCardSoldierHeart2 = { 2, sBtlFormCardSoldierHeart2Steps, 60 };

static const BtlFormStep sBtlFormCardSoldierHeart1Steps[] = {
    { 47, 64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormCardSoldierHeart1 = { 1, sBtlFormCardSoldierHeart1Steps, 60 };

static const BtlFormList sBtlFormLists[144] = {
    { 14, &gBtlFormListEntries[0], 256 },
    { 4, &gBtlFormListEntries[14], 256 },
    { 1, &gBtlFormListEntries[18], 256 },
    { 2, &gBtlFormListEntries[19], 256 },
    { 5, &gBtlFormListEntries[21], 256 },
    { 1, &gBtlFormListEntries[26], 256 },
    { 1, &gBtlFormListEntries[27], 256 },
    { 1, &gBtlFormListEntries[28], 256 },
    { 1, &gBtlFormListEntries[29], 256 },
    { 1, &gBtlFormListEntries[30], 256 },
    { 1, &gBtlFormListEntries[31], 256 },
    { 2, &gBtlFormListEntries[32], 256 },
    { 2, &gBtlFormListEntries[34], 266 },
    { 3, &gBtlFormListEntries[36], 256 },
    { 3, &gBtlFormListEntries[39], 256 },
    { 3, &gBtlFormListEntries[42], 256 },
    { 4, &gBtlFormListEntries[45], 256 },
    { 1, &gBtlFormListEntries[49], 256 },
    { 3, &gBtlFormListEntries[50], 256 },
    { 4, &gBtlFormListEntries[53], 256 },
    { 4, &gBtlFormListEntries[57], 256 },
    { 2, &gBtlFormListEntries[61], 256 },
    { 1, &gBtlFormListEntries[63], 256 },
    { 3, &gBtlFormListEntries[64], 256 },
    { 2, &gBtlFormListEntries[67], 256 },
    { 2, &gBtlFormListEntries[69], 256 },
    { 3, &gBtlFormListEntries[71], 256 },
    { 3, &gBtlFormListEntries[74], 256 },
    { 3, &gBtlFormListEntries[77], 256 },
    { 3, &gBtlFormListEntries[80], 256 },
    { 3, &gBtlFormListEntries[83], 256 },
    { 4, &gBtlFormListEntries[86], 256 },
    { 3, &gBtlFormListEntries[90], 256 },
    { 3, &gBtlFormListEntries[93], 256 },
    { 2, &gBtlFormListEntries[96], 256 },
    { 4, &gBtlFormListEntries[98], 256 },
    { 3, &gBtlFormListEntries[102], 256 },
    { 3, &gBtlFormListEntries[105], 256 },
    { 3, &gBtlFormListEntries[108], 256 },
    { 4, &gBtlFormListEntries[111], 256 },
    { 3, &gBtlFormListEntries[115], 256 },
    { 3, &gBtlFormListEntries[118], 256 },
    { 2, &gBtlFormListEntries[121], 256 },
    { 3, &gBtlFormListEntries[123], 256 },
    { 4, &gBtlFormListEntries[126], 256 },
    { 4, &gBtlFormListEntries[130], 256 },
    { 4, &gBtlFormListEntries[134], 256 },
    { 3, &gBtlFormListEntries[138], 256 },
    { 3, &gBtlFormListEntries[141], 256 },
    { 4, &gBtlFormListEntries[144], 256 },
    { 6, &gBtlFormListEntries[148], 256 },
    { 3, &gBtlFormListEntries[154], 256 },
    { 3, &gBtlFormListEntries[157], 256 },
    { 2, &gBtlFormListEntries[160], 256 },
    { 2, &gBtlFormListEntries[162], 256 },
    { 3, &gBtlFormListEntries[164], 256 },
    { 3, &gBtlFormListEntries[167], 256 },
    { 1, &gBtlFormListEntries[170], 256 },
    { 4, &gBtlFormListEntries[171], 256 },
    { 5, &gBtlFormListEntries[175], 256 },
    { 4, &gBtlFormListEntries[180], 256 },
    { 4, &gBtlFormListEntries[184], 256 },
    { 3, &gBtlFormListEntries[188], 256 },
    { 2, &gBtlFormListEntries[191], 256 },
    { 2, &gBtlFormListEntries[193], 256 },
    { 3, &gBtlFormListEntries[195], 256 },
    { 4, &gBtlFormListEntries[198], 256 },
    { 3, &gBtlFormListEntries[202], 256 },
    { 1, &gBtlFormListEntries[205], 256 },
    { 2, &gBtlFormListEntries[206], 256 },
    { 5, &gBtlFormListEntries[208], 256 },
    { 1, &gBtlFormListEntries[213], 64 },
    { 2, &gBtlFormListEntries[214], 128 },
    { 2, &gBtlFormListEntries[216], 256 },
    { 2, &gBtlFormListEntries[218], 256 },
    { 2, &gBtlFormListEntries[220], 256 },
    { 2, &gBtlFormListEntries[222], 256 },
    { 3, &gBtlFormListEntries[224], 256 },
    { 3, &gBtlFormListEntries[227], 256 },
    { 4, &gBtlFormListEntries[230], 256 },
    { 2, &gBtlFormListEntries[234], 256 },
    { 2, &gBtlFormListEntries[236], 256 },
    { 4, &gBtlFormListEntries[238], 256 },
    { 3, &gBtlFormListEntries[242], 256 },
    { 4, &gBtlFormListEntries[245], 256 },
    { 5, &gBtlFormListEntries[249], 256 },
    { 3, &gBtlFormListEntries[254], 256 },
    { 5, &gBtlFormListEntries[257], 256 },
    { 3, &gBtlFormListEntries[262], 256 },
    { 4, &gBtlFormListEntries[265], 256 },
    { 4, &gBtlFormListEntries[269], 256 },
    { 4, &gBtlFormListEntries[273], 256 },
    { 5, &gBtlFormListEntries[277], 256 },
    { 3, &gBtlFormListEntries[282], 256 },
    { 3, &gBtlFormListEntries[285], 256 },
    { 2, &gBtlFormListEntries[288], 256 },
    { 2, &gBtlFormListEntries[290], 256 },
    { 3, &gBtlFormListEntries[292], 256 },
    { 4, &gBtlFormListEntries[295], 256 },
    { 4, &gBtlFormListEntries[299], 256 },
    { 4, &gBtlFormListEntries[303], 256 },
    { 2, &gBtlFormListEntries[307], 256 },
    { 3, &gBtlFormListEntries[309], 256 },
    { 3, &gBtlFormListEntries[312], 256 },
    { 3, &gBtlFormListEntries[315], 256 },
    { 3, &gBtlFormListEntries[318], 256 },
    { 3, &gBtlFormListEntries[321], 256 },
    { 3, &gBtlFormListEntries[324], 256 },
    { 3, &gBtlFormListEntries[327], 256 },
    { 2, &gBtlFormListEntries[330], 256 },
    { 3, &gBtlFormListEntries[332], 256 },
    { 4, &gBtlFormListEntries[335], 256 },
    { 3, &gBtlFormListEntries[339], 256 },
    { 3, &gBtlFormListEntries[342], 256 },
    { 3, &gBtlFormListEntries[345], 256 },
    { 2, &gBtlFormListEntries[348], 256 },
    { 4, &gBtlFormListEntries[350], 256 },
    { 4, &gBtlFormListEntries[354], 256 },
    { 4, &gBtlFormListEntries[358], 256 },
    { 4, &gBtlFormListEntries[362], 256 },
    { 4, &gBtlFormListEntries[366], 256 },
    { 4, &gBtlFormListEntries[370], 256 },
    { 3, &gBtlFormListEntries[374], 256 },
#ifdef VERSION_EU
    { 6, &gBtlFormListEntries[377], 164 },
#else
    { 6, &gBtlFormListEntries[377], 256 },
#endif
    { 5, &gBtlFormListEntries[383], 256 },
    { 3, &gBtlFormListEntries[388], 256 },
#ifdef VERSION_EU
    { 8, &gBtlFormListEntries[391], 256 },
#else
    { 9, &gBtlFormListEntries[391], 256 },
#endif
    { 4, &gBtlFormListEntries[400 - FORMATION_LIST_DROP], 256 },
    { 4, &gBtlFormListEntries[404 - FORMATION_LIST_DROP], 256 },
#ifdef VERSION_EU
    { 8, &gBtlFormListEntries[408 - FORMATION_LIST_DROP], 196 },
#else
    { 8, &gBtlFormListEntries[408 - FORMATION_LIST_DROP], 256 },
#endif
    { 5, &gBtlFormListEntries[416 - FORMATION_LIST_DROP], 256 },
    { 3, &gBtlFormListEntries[421 - FORMATION_LIST_DROP], 256 },
    { 2, &gBtlFormListEntries[424 - FORMATION_LIST_DROP], 256 },
    { 1, &gBtlFormListEntries[426 - FORMATION_LIST_DROP], 256 },
    { 1, &gBtlFormListEntries[427 - FORMATION_LIST_DROP], 256 },
    { 2, &gBtlFormListEntries[428 - FORMATION_LIST_DROP], 256 },
    { 1, &gBtlFormListEntries[430 - FORMATION_LIST_DROP], 256 },
    { 2, &gBtlFormListEntries[431 - FORMATION_LIST_DROP], 256 },
    { 2, &gBtlFormListEntries[433 - FORMATION_LIST_DROP], 256 },
    { 1, &gBtlFormListEntries[435 - FORMATION_LIST_DROP], 256 },
    { 1, &gBtlFormListEntries[436 - FORMATION_LIST_DROP], 256 },
    { 3, &gBtlFormListEntries[437 - FORMATION_LIST_DROP], 256 },
    { 3, &gBtlFormListEntries[440 - FORMATION_LIST_DROP], 256 },
    { 3, &gBtlFormListEntries[443 - FORMATION_LIST_DROP], 256 },
};

const BtlFormEntry* gBtlFormListEntries[] = {
    &sBtlFormShadow8,
    &sBtlFormShadow4D,
    &sBtlFormShadow2F,
    &sBtlFormShadow6A,
    &sBtlFormShadow4C,
    &sBtlFormShadow3F,
    &sBtlFormShadow2C,
    &sBtlFormShadow4C,
    &sBtlFormShadow3E,
    &sBtlFormShadow2D,
    &sBtlFormShadow4D,
    &sBtlFormShadow3C,
    &sBtlFormShadow7,
    &sBtlFormShadow1,
    &sBtlFormCardSoldierSpade3,
    &sBtlFormCardSoldierHeart1,
    &sBtlFormCardSoldierSpade2,
    &sBtlFormCardSoldierHeart1,
    &sBtlFormBarrelSpider3,
    &sBtlFormBarrelSpider3,
    &sBtlFormBarrelSpider2C,
    &sBtlFormBarrelSpider3,
    &sBtlFormBarrelSpider2B,
    &sBtlFormBarrelSpider1A,
    &sBtlFormBarrelSpider2A,
    &sBtlFormBarrelSpider1B,
    &sBtlFormWhiteMushroom1,
    &sBtlFormWhiteMushroom2B,
    &sBtlFormWhiteMushroom4,
    &sBtlFormBlackFungus1,
    &sBtlFormBlackFungus2B,
    &sBtlFormBlackFungus4,
    &sBtlFormShadow4A,
    &sBtlFormLargeBody1A,
    &sBtlFormCreeperPlant2A,
    &sBtlFormSoldier3E,
    &sBtlFormRedNocturne2A,
    &sBtlFormCrescendo2B,
    &sBtlFormLargeBody1A,
    &sBtlFormSoldier3D,
    &sBtlFormCreeperPlant2C,
    &sBtlFormCrescendo2A,
    &sBtlFormShadow2A,
    &sBtlFormLargeBody1A,
    &sBtlFormRedNocturne4,
    &sBtlFormShadow2A,
    &sBtlFormSoldier2D,
    &sBtlFormLargeBody1A,
    &sBtlFormLargeBody1B,
    &sBtlFormCrescendo5,
    &sBtlFormCreeperPlant2B,
    &sBtlFormShadow3F,
    &sBtlFormRedNocturne3B,
    &sBtlFormRedNocturne3B,
    &sBtlFormLargeBody1B,
    &sBtlFormLargeBody1A,
    &sBtlFormShadow3C,
    &sBtlFormRedNocturne4,
    &sBtlFormCrescendo2A,
    &sBtlFormCrescendo2B,
    &sBtlFormSoldier4C,
    &sBtlFormShadow5C,
    &sBtlFormSoldier2B,
    &sBtlFormSoldier6,
    &sBtlFormShadow2B,
    &sBtlFormAirSoldier3B,
    &sBtlFormShadow2F,
    &sBtlFormSoldier2D,
    &sBtlFormAirSoldier3A,
    &sBtlFormAirSoldier4B,
    &sBtlFormAirSoldier2A,
    &sBtlFormShadow3D,
    &sBtlFormSoldier3E,
    &sBtlFormAirSoldier2A,
    &sBtlFormShadow3D,
    &sBtlFormShadow4D,
    &sBtlFormShadow5B,
    &sBtlFormSoldier4B,
    &sBtlFormShadow2F,
    &sBtlFormShadow2E,
    &sBtlFormAirSoldier2B,
    &sBtlFormShadow3C,
    &sBtlFormShadow3D,
    &sBtlFormAirSoldier4A,
    &sBtlFormSoldier2D,
    &sBtlFormShadow3D,
    &sBtlFormShadow2F,
    &sBtlFormDarkball2D,
    &sBtlFormShadow2E,
    &sBtlFormDarkball1A,
    &sBtlFormTornadoStep3B,
    &sBtlFormDarkball1F,
    &sBtlFormDarkball1D,
    &sBtlFormCrescendo3C,
    &sBtlFormDarkball1C,
    &sBtlFormDarkball1E,
    &sBtlFormCreeperPlant4,
    &sBtlFormDarkball2E,
    &sBtlFormTornadoStep2B,
    &sBtlFormCrescendo2B,
    &sBtlFormTornadoStep1,
    &sBtlFormCrescendo1,
    &sBtlFormShadow2C,
    &sBtlFormCreeperPlant6,
    &sBtlFormShadow4C,
    &sBtlFormCreeperPlant4,
    &sBtlFormTornadoStep2C,
    &sBtlFormTornadoStep1,
    &sBtlFormCreeperPlant4,
    &sBtlFormCrescendo2C,
    &sBtlFormTornadoStep1,
    &sBtlFormDarkball2D,
    &sBtlFormShadow5C,
    &sBtlFormDarkball1C,
    &sBtlFormDarkball1E,
    &sBtlFormTornadoStep3C,
    &sBtlFormCrescendo3B,
    &sBtlFormCreeperPlant3B,
    &sBtlFormShadow3A,
    &sBtlFormLargeBody1A,
    &sBtlFormPowerwild2A,
    &sBtlFormBlueRhapsody3,
    &sBtlFormPowerwild3,
    &sBtlFormPowerwild2A,
    &sBtlFormLargeBody1A,
    &sBtlFormPowerwild2B,
    &sBtlFormBlueRhapsody3,
    &sBtlFormBouncywild2A,
    &sBtlFormBlueRhapsody2B,
    &sBtlFormBlueRhapsody1C,
    &sBtlFormPowerwild2A,
    &sBtlFormBouncywild1,
    &sBtlFormPowerwild2A,
    &sBtlFormBouncywild1,
    &sBtlFormLargeBody1A,
    &sBtlFormBouncywild2B,
    &sBtlFormLargeBody1B,
    &sBtlFormBlueRhapsody2A,
    &sBtlFormBouncywild3,
    &sBtlFormLargeBody1A,
    &sBtlFormBlueRhapsody2A,
    &sBtlFormShadow4C,
    &sBtlFormPowerwild3,
    &sBtlFormLargeBody2B,
    &sBtlFormShadow5C,
    &sBtlFormBlueRhapsody2A,
    &sBtlFormLargeBody1A,
    &sBtlFormBlueRhapsody2C,
    &sBtlFormBlueRhapsody4,
    &sBtlFormShadow3D,
    &sBtlFormPowerwild1,
    &sBtlFormPowerwild2A,
    &sBtlFormBouncywild2A,
    &sBtlFormBouncywild2B,
    &sBtlFormShadow4A,
    &sBtlFormGreenRequiem2C,
    &sBtlFormYellowOpera2E,
    &sBtlFormAirSoldier2B,
    &sBtlFormSearchGhost2A,
    &sBtlFormTornadoStep2B,
    &sBtlFormLargeBody1A,
    &sBtlFormTornadoStep3C,
    &sBtlFormYellowOpera4,
    &sBtlFormGreenRequiem4,
    &sBtlFormShadow3B,
    &sBtlFormAirSoldier2B,
    &sBtlFormLargeBody1B,
    &sBtlFormSearchGhost3,
    &sBtlFormYellowOpera3B,
    &sBtlFormYellowOpera2D,
    &sBtlFormTornadoStep5B,
    &sBtlFormLargeBody2B,
    &sBtlFormGreenRequiem4,
    &sBtlFormLargeBody1A,
    &sBtlFormGreenRequiem2E,
    &sBtlFormShadow5D,
    &sBtlFormShadow4D,
    &sBtlFormShadow3D,
    &sBtlFormShadow2F,
    &sBtlFormShadow1,
    &sBtlFormAirSoldier4B,
    &sBtlFormSearchGhost1A,
    &sBtlFormSearchGhost1B,
    &sBtlFormSearchGhost1A,
    &sBtlFormShadow2A,
    &sBtlFormWightKnight1A,
    &sBtlFormShadow2E,
    &sBtlFormWightKnight1B,
    &sBtlFormSearchGhost1A,
    &sBtlFormCreeperPlant3B,
    &sBtlFormGargoyle1B,
    &sBtlFormWightKnight2C,
    &sBtlFormCreeperPlant2B,
    &sBtlFormGargoyle3,
    &sBtlFormSearchGhost2C,
    &sBtlFormShadow4C,
    &sBtlFormCreeperPlant2B,
    &sBtlFormSearchGhost2A,
    &sBtlFormGargoyle2A,
    &sBtlFormWightKnight1B,
    &sBtlFormGargoyle1A,
    &sBtlFormWightKnight1A,
    &sBtlFormShadow5B,
    &sBtlFormGargoyle2B,
    &sBtlFormSearchGhost1B,
    &sBtlFormCreeperPlant5B,
    &sBtlFormCreeperPlant3B,
    &sBtlFormWightKnight2A,
    &sBtlFormGargoyle2A,
    &sBtlFormWightKnight2D,
    &sBtlFormShadow4C,
    &sBtlFormGargoyle2B,
    &sBtlFormWightKnight2A,
    &sBtlFormShadow3D,
    &sBtlFormRedNocturne1A,
    &sBtlFormShadow2B,
    &sBtlFormShadow2B,
    &sBtlFormBlueRhapsody2A,
    &sBtlFormRedNocturne2A,
    &sBtlFormBlueRhapsody2A,
    &sBtlFormSoldier1A,
    &sBtlFormShadow2B,
    &sBtlFormSoldier1C,
    &sBtlFormRedNocturne2A,
    &sBtlFormShadow2C,
    &sBtlFormSoldier1A,
    &sBtlFormSoldier1C,
    &sBtlFormSoldier1A,
    &sBtlFormSoldier1C,
    &sBtlFormBlueRhapsody2A,
    &sBtlFormShadow2B,
    &sBtlFormBlueRhapsody1B,
    &sBtlFormRedNocturne1A,
    &sBtlFormSoldier2C,
    &sBtlFormShadow4C,
    &sBtlFormSoldier2A,
    &sBtlFormSeaNeon4A,
    &sBtlFormDarkball2E,
    &sBtlFormScrewdiver2A,
    &sBtlFormAquatank1A,
    &sBtlFormScrewdiver1B,
    &sBtlFormScrewdiver1A,
    &sBtlFormDarkball2C,
    &sBtlFormDarkball1B,
    &sBtlFormDarkball1A,
    &sBtlFormSearchGhost2A,
    &sBtlFormSeaNeon3A,
    &sBtlFormScrewdiver1A,
    &sBtlFormAquatank1B,
    &sBtlFormDarkball1A,
    &sBtlFormSearchGhost1B,
    &sBtlFormDarkball1A,
    &sBtlFormSearchGhost1B,
    &sBtlFormDarkball1A,
    &sBtlFormSeaNeon6,
    &sBtlFormDarkball1A,
    &sBtlFormDarkball1B,
    &sBtlFormAquatank1A,
    &sBtlFormScrewdiver1C,
    &sBtlFormScrewdiver1D,
    &sBtlFormScrewdiver1E,
    &sBtlFormScrewdiver1F,
    &sBtlFormSeaNeon4B,
    &sBtlFormSearchGhost2B,
    &sBtlFormAquatank1A,
    &sBtlFormScrewdiver2A,
    &sBtlFormDarkball1B,
    &sBtlFormDarkball1A,
    &sBtlFormScrewdiver1B,
    &sBtlFormSeaNeon4A,
    &sBtlFormScrewdiver2B,
    &sBtlFormAquatank1A,
    &sBtlFormScrewdiver1B,
    &sBtlFormShadow2E,
    &sBtlFormBandit1B,
    &sBtlFormFatBandit1B,
    &sBtlFormBandit2A,
    &sBtlFormYellowOpera2B,
    &sBtlFormGreenRequiem2E,
    &sBtlFormFatBandit1B,
    &sBtlFormGreenRequiem2A,
    &sBtlFormYellowOpera2E,
    &sBtlFormShadow3F,
    &sBtlFormAirSoldier3B,
    &sBtlFormShadow3F,
    &sBtlFormAirSoldier4A,
    &sBtlFormGreenRequiem1A,
    &sBtlFormGreenRequiem1A,
    &sBtlFormFatBandit2B,
    &sBtlFormFatBandit1B,
    &sBtlFormBandit4B,
    &sBtlFormGreenRequiem2C,
    &sBtlFormShadow4A,
    &sBtlFormAirSoldier2A,
    &sBtlFormYellowOpera4,
    &sBtlFormShadow3D,
    &sBtlFormAirSoldier2A,
    &sBtlFormBandit2A,
    &sBtlFormFatBandit1B,
    &sBtlFormBandit2A,
    &sBtlFormGreenRequiem3B,
    &sBtlFormYellowOpera3A,
    &sBtlFormBandit2B,
    &sBtlFormBandit4B,
    &sBtlFormFatBandit1A,
    &sBtlFormBandit2A,
    &sBtlFormFatBandit1B,
    &sBtlFormShadow3D,
    &sBtlFormPirate3A,
    &sBtlFormAirPirate2A,
    &sBtlFormDarkball1B,
    &sBtlFormDarkball1A,
    &sBtlFormShadow4B,
    &sBtlFormCrescendo2B,
    &sBtlFormPirate2C,
    &sBtlFormShadow4C,
    &sBtlFormDarkball2F,
    &sBtlFormDarkball1A,
    &sBtlFormAirPirate2B,
    &sBtlFormCrescendo3B,
    &sBtlFormAirPirate1C,
    &sBtlFormPirate3A,
    &sBtlFormDarkball1B,
    &sBtlFormDarkball1A,
    &sBtlFormPirate3A,
    &sBtlFormAirPirate2C,
    &sBtlFormPirate3B,
    &sBtlFormShadow5B,
    &sBtlFormPirate3B,
    &sBtlFormPirate2C,
    &sBtlFormDarkball2D,
    &sBtlFormCrescendo3C,
    &sBtlFormAirPirate2C,
    &sBtlFormPirate3A,
    &sBtlFormAirPirate1A,
    &sBtlFormShadow4D,
    &sBtlFormDarkball1C,
    &sBtlFormDarkball1C,
    &sBtlFormDarkball1E,
    &sBtlFormShadow6A,
    &sBtlFormDefender1,
    &sBtlFormTornadoStep2C,
    &sBtlFormWyvern2,
    &sBtlFormWizard1B,
    &sBtlFormDarkball2D,
    &sBtlFormTornadoStep3A,
    &sBtlFormWyvern1B,
    &sBtlFormWyvern1A,
    &sBtlFormDefender2,
    &sBtlFormWizard2,
    &sBtlFormShadow4C,
    &sBtlFormWizard2,
    &sBtlFormShadow2B,
    &sBtlFormShadow2F,
    &sBtlFormWyvern2,
    &sBtlFormDarkball1B,
    &sBtlFormDarkball1A,
    &sBtlFormDarkball1B,
    &sBtlFormDefender1,
    &sBtlFormWyvern1B,
    &sBtlFormDefender1,
    &sBtlFormWizard1B,
    &sBtlFormDarkball2B,
    &sBtlFormTornadoStep3C,
    &sBtlFormDarkball1C,
    &sBtlFormDarkball1E,
    &sBtlFormShadow5C,
    &sBtlFormDefender1,
    &sBtlFormWizard1B,
    &sBtlFormDefender1,
    &sBtlFormShadow4C,
    &sBtlFormWizard2,
    &sBtlFormShadow4A,
    &sBtlFormDarkball2F,
    &sBtlFormShadow5B,
    &sBtlFormNeoshadow2,
    &sBtlFormNeoshadow1A,
    &sBtlFormDefender1,
    &sBtlFormRedNocturne1B,
    &sBtlFormBlueRhapsody1G,
    &sBtlFormYellowOpera1C,
    &sBtlFormGreenRequiem1D,
    &sBtlFormWizard2,
    &sBtlFormDarkball2C,
    &sBtlFormDarkball1C,
    &sBtlFormDarkball1E,
    &sBtlFormDarkball1F,
    &sBtlFormDarkball2F,
    &sBtlFormWyvern2,
    &sBtlFormDefender2,
    &sBtlFormYellowOpera4,
    &sBtlFormRedNocturne2A,
    &sBtlFormBlueRhapsody2A,
    &sBtlFormYellowOpera2F,
    &sBtlFormGreenRequiem2D,
#ifndef VERSION_EU
    &sBtlFormWizard1A,
#endif
    &sBtlFormGreenRequiem2A,
    &sBtlFormYellowOpera2B,
    &sBtlFormBlueRhapsody2C,
    &sBtlFormRedNocturne2B,
    &sBtlFormWyvern2,
    &sBtlFormNeoshadow1A,
    &sBtlFormNeoshadow1B,
    &sBtlFormDefender1,
    &sBtlFormShadow4C,
    &sBtlFormWizard2,
    &sBtlFormNeoshadow1B,
    &sBtlFormNeoshadow1A,
    &sBtlFormDefender1,
    &sBtlFormRedNocturne1B,
    &sBtlFormBlueRhapsody1G,
    &sBtlFormYellowOpera1C,
    &sBtlFormGreenRequiem1D,
#ifdef VERSION_EU
    &sBtlFormNeoshadow2,
    &sBtlFormWizard1A,
    &sBtlFormWyvern1B,
#else
    &sBtlFormWizard1A,
    &sBtlFormWyvern1B,
    &sBtlFormNeoshadow2,
#endif
    &sBtlFormNeoshadow3B,
    &sBtlFormNeoshadow2,
    &sBtlFormShadow4C,
    &sBtlFormShadow2F,
    &sBtlFormNeoshadow1A,
    &sBtlFormShadow3A,
    &sBtlFormDarkball1A,
    &sBtlFormDarkball1B,
    &sBtlFormDefender1,
    &sBtlFormShadow4C,
    &sBtlFormWyvern2,
    &sBtlFormTornadoStep3A,
    &sBtlFormWyvern1A,
    &sBtlFormWizard1A,
    &sBtlFormWizard2,
    &sBtlFormShadow2C,
    &sBtlFormWizard2,
    &sBtlFormDefender1,
    &sBtlFormWizard1B,
    &sBtlFormDarkball2B,
    &sBtlFormShadow5C,
    &sBtlFormSoldier1A,
    &sBtlFormTornadoStep1,
    &sBtlFormRedNocturne1A,
    &sBtlFormSoldier1A,
    &sBtlFormCrescendo1,
    &sBtlFormRedNocturne1A,
    &sBtlFormSoldier1A,
    &sBtlFormCreeperPlant1,
    &sBtlFormRedNocturne1A,
};

const BtlFormList* gBtlFormListByBattleId[147] = {
    &sBtlFormLists[31],
    &sBtlFormLists[32],
    &sBtlFormLists[33],
    &sBtlFormLists[34],
    &sBtlFormLists[35],
    &sBtlFormLists[36],
    &sBtlFormLists[37],
    &sBtlFormLists[38],
    &sBtlFormLists[39],
    &sBtlFormLists[40],
    &sBtlFormLists[71],
    &sBtlFormLists[72],
    &sBtlFormLists[73],
    &sBtlFormLists[74],
    &sBtlFormLists[75],
    &sBtlFormLists[76],
    &sBtlFormLists[77],
    &sBtlFormLists[78],
    &sBtlFormLists[79],
    &sBtlFormLists[80],
    &sBtlFormLists[11],
    &sBtlFormLists[12],
    &sBtlFormLists[13],
    &sBtlFormLists[14],
    &sBtlFormLists[15],
    &sBtlFormLists[16],
    &sBtlFormLists[17],
    &sBtlFormLists[18],
    &sBtlFormLists[19],
    &sBtlFormLists[20],
    &sBtlFormLists[41],
    &sBtlFormLists[42],
    &sBtlFormLists[43],
    &sBtlFormLists[44],
    &sBtlFormLists[45],
    &sBtlFormLists[46],
    &sBtlFormLists[47],
    &sBtlFormLists[48],
    &sBtlFormLists[49],
    &sBtlFormLists[50],
    &sBtlFormLists[91],
    &sBtlFormLists[92],
    &sBtlFormLists[93],
    &sBtlFormLists[94],
    &sBtlFormLists[95],
    &sBtlFormLists[96],
    &sBtlFormLists[97],
    &sBtlFormLists[98],
    &sBtlFormLists[99],
    &sBtlFormLists[100],
    &sBtlFormLists[81],
    &sBtlFormLists[82],
    &sBtlFormLists[83],
    &sBtlFormLists[84],
    &sBtlFormLists[85],
    &sBtlFormLists[86],
    &sBtlFormLists[87],
    &sBtlFormLists[88],
    &sBtlFormLists[89],
    &sBtlFormLists[90],
    &sBtlFormLists[61],
    &sBtlFormLists[62],
    &sBtlFormLists[63],
    &sBtlFormLists[64],
    &sBtlFormLists[65],
    &sBtlFormLists[66],
    &sBtlFormLists[67],
    &sBtlFormLists[68],
    &sBtlFormLists[69],
    &sBtlFormLists[70],
    &sBtlFormLists[101],
    &sBtlFormLists[102],
    &sBtlFormLists[103],
    &sBtlFormLists[104],
    &sBtlFormLists[105],
    &sBtlFormLists[106],
    &sBtlFormLists[107],
    &sBtlFormLists[108],
    &sBtlFormLists[109],
    &sBtlFormLists[110],
    &sBtlFormLists[51],
    &sBtlFormLists[52],
    &sBtlFormLists[53],
    &sBtlFormLists[54],
    &sBtlFormLists[55],
    &sBtlFormLists[56],
    &sBtlFormLists[57],
    &sBtlFormLists[58],
    &sBtlFormLists[59],
    &sBtlFormLists[60],
    &sBtlFormLists[21],
    &sBtlFormLists[22],
    &sBtlFormLists[23],
    &sBtlFormLists[24],
    &sBtlFormLists[25],
    &sBtlFormLists[26],
    &sBtlFormLists[27],
    &sBtlFormLists[28],
    &sBtlFormLists[29],
    &sBtlFormLists[30],
    &sBtlFormLists[111],
    &sBtlFormLists[112],
    &sBtlFormLists[113],
    &sBtlFormLists[114],
    &sBtlFormLists[115],
    &sBtlFormLists[116],
    &sBtlFormLists[117],
    &sBtlFormLists[118],
    &sBtlFormLists[119],
    &sBtlFormLists[120],
    &sBtlFormLists[121],
    &sBtlFormLists[122],
    &sBtlFormLists[123],
    &sBtlFormLists[124],
    &sBtlFormLists[125],
    &sBtlFormLists[126],
    &sBtlFormLists[127],
    &sBtlFormLists[128],
    &sBtlFormLists[129],
    &sBtlFormLists[130],
    &sBtlFormLists[1],
    &sBtlFormLists[0],
    &sBtlFormLists[63],
    &sBtlFormLists[96],
    &sBtlFormLists[91],
    &sBtlFormLists[2],
    &sBtlFormLists[3],
    &sBtlFormLists[4],
    &sBtlFormLists[5],
    &sBtlFormLists[6],
    &sBtlFormLists[7],
    &sBtlFormLists[8],
    &sBtlFormLists[9],
    &sBtlFormLists[10],
    &sBtlFormLists[131],
    &sBtlFormLists[132],
    &sBtlFormLists[133],
    &sBtlFormLists[134],
    &sBtlFormLists[135],
    &sBtlFormLists[136],
    &sBtlFormLists[137],
    &sBtlFormLists[138],
    &sBtlFormLists[139],
    &sBtlFormLists[140],
    &sBtlFormLists[141],
    &sBtlFormLists[142],
    &sBtlFormLists[143],
};
