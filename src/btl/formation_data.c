/**
 * formation_data.c
 * Enemy Formation Data
 */

#include "formation_data.h"
#include "formation_types.h"
#include "enemy_ids.h"

#ifdef VERSION_EU
#define FORMATION_LIST_DROP 1
#else
#define FORMATION_LIST_DROP 0
#endif

static const BtlFormStep sBtlFormShadow8Steps[] = {
    { ENEMY_SHADOW, 25, -25, 0, 0 },
    { ENEMY_SHADOW, 65, -12, 0, 1 },
    { ENEMY_SHADOW, 85, 12, 0, 2 },
    { ENEMY_SHADOW, 55, 25, 0, 3 },
    { ENEMY_SHADOW, -55, 25, 0, 4 },
    { ENEMY_SHADOW, -85, 12, 0, 5 },
    { ENEMY_SHADOW, -65, -12, 0, 6 },
    { ENEMY_SHADOW, -25, -25, 0, 7 },
};

static const BtlFormEntry sBtlFormShadow8 = { 8, sBtlFormShadow8Steps, 60 };

static const BtlFormStep sBtlFormShadow7Steps[] = {
    { ENEMY_SHADOW, 90, 0, 0, 0 },
    { ENEMY_SHADOW, 55, 25, 0, 1 },
    { ENEMY_SHADOW, 40, 0, 0, 2 },
    { ENEMY_SHADOW, 25, -25, 0, 3 },
    { ENEMY_SHADOW, -25, -25, 0, 4 },
    { ENEMY_SHADOW, -55, 25, 0, 5 },
    { ENEMY_SHADOW, -64, 0, 0, 6 },
};

static const BtlFormEntry sBtlFormShadow7 = { 7, sBtlFormShadow7Steps, 60 };

static const BtlFormStep sBtlFormShadow6ASteps[] = {
    { ENEMY_SHADOW, 25, -25, 0, 0 },
    { ENEMY_SHADOW, 40, 0, 0, 1 },
    { ENEMY_SHADOW, 25, 25, 0, 2 },
    { ENEMY_SHADOW, -25, 25, 0, 3 },
    { ENEMY_SHADOW, -40, 0, 0, 4 },
    { ENEMY_SHADOW, -25, -25, 0, 5 },
};

static const BtlFormEntry sBtlFormShadow6A = { 6, sBtlFormShadow6ASteps, 60 };

static const BtlFormStep sBtlFormShadow6BSteps[] = {
    { ENEMY_SHADOW, 25, -25, 0, 0 },
    { ENEMY_SHADOW, 40, 0, 0, 1 },
    { ENEMY_SHADOW, 55, 25, 0, 2 },
    { ENEMY_SHADOW, -55, -25, 0, 3 },
    { ENEMY_SHADOW, -40, 0, 0, 4 },
    { ENEMY_SHADOW, -25, 25, 0, 5 },
};

const BtlFormEntry gBtlFormShadow6B = { 6, sBtlFormShadow6BSteps, 60 };

static const BtlFormStep sBtlFormShadow6CSteps[] = {
    { ENEMY_SHADOW, 90, 0, 0, 0 },
    { ENEMY_SHADOW, 64, 0, 0, 1 },
    { ENEMY_SHADOW, 40, 0, 0, 2 },
    { ENEMY_SHADOW, -40, 0, 0, 3 },
    { ENEMY_SHADOW, -64, 0, 0, 4 },
    { ENEMY_SHADOW, -90, 0, 0, 5 },
};

const BtlFormEntry gBtlFormShadow6C = { 6, sBtlFormShadow6CSteps, 60 };

static const BtlFormStep sBtlFormShadow5ASteps[] = {
    { ENEMY_SHADOW, 25, -25, 0, 0 },
    { ENEMY_SHADOW, 40, 0, 0, 1 },
    { ENEMY_SHADOW, 55, 25, 0, 2 },
    { ENEMY_SHADOW, 65, -12, 0, 3 },
    { ENEMY_SHADOW, 85, 12, 0, 4 },
};

const BtlFormEntry gBtlFormShadow5A = { 5, sBtlFormShadow5ASteps, 60 };

static const BtlFormStep sBtlFormShadow5BSteps[] = {
    { ENEMY_SHADOW, 25, -25, 0, 0 },
    { ENEMY_SHADOW, 55, 25, 0, 1 },
    { ENEMY_SHADOW, 90, 0, 0, 2 },
    { ENEMY_SHADOW, -65, -12, 0, 3 },
    { ENEMY_SHADOW, -85, 12, 0, 4 },
};

static const BtlFormEntry sBtlFormShadow5B = { 5, sBtlFormShadow5BSteps, 60 };

static const BtlFormStep sBtlFormShadow5CSteps[] = {
    { ENEMY_SHADOW, 65, -12, 0, 0 },
    { ENEMY_SHADOW, 85, 12, 0, 1 },
    { ENEMY_SHADOW, -25, -25, 0, 2 },
    { ENEMY_SHADOW, -40, 0, 0, 3 },
    { ENEMY_SHADOW, -55, 25, 0, 4 },
};

static const BtlFormEntry sBtlFormShadow5C = { 5, sBtlFormShadow5CSteps, 60 };

static const BtlFormStep sBtlFormShadow5DSteps[] = {
    { ENEMY_SHADOW, 25, -25, 0, 0 },
    { ENEMY_SHADOW, 65, -12, 0, 1 },
    { ENEMY_SHADOW, 90, 0, 0, 2 },
    { ENEMY_SHADOW, 85, 12, 0, 3 },
    { ENEMY_SHADOW, 55, 25, 0, 4 },
};

static const BtlFormEntry sBtlFormShadow5D = { 5, sBtlFormShadow5DSteps, 60 };

static const BtlFormStep sBtlFormShadow4ASteps[] = {
    { ENEMY_SHADOW, 25, -25, 0, 0 },
    { ENEMY_SHADOW, 55, 25, 0, 1 },
    { ENEMY_SHADOW, 65, -12, 0, 2 },
    { ENEMY_SHADOW, 85, 12, 0, 3 },
};

static const BtlFormEntry sBtlFormShadow4A = { 4, sBtlFormShadow4ASteps, 60 };

static const BtlFormStep sBtlFormShadow4BSteps[] = {
    { ENEMY_SHADOW, 40, 0, 0, 0 },
    { ENEMY_SHADOW, 65, -12, 0, 1 },
    { ENEMY_SHADOW, 85, 12, 0, 2 },
    { ENEMY_SHADOW, 90, 0, 0, 3 },
};

static const BtlFormEntry sBtlFormShadow4B = { 4, sBtlFormShadow4BSteps, 60 };

static const BtlFormStep sBtlFormShadow4CSteps[] = {
    { ENEMY_SHADOW, 65, -12, 0, 0 },
    { ENEMY_SHADOW, 85, 12, 0, 1 },
    { ENEMY_SHADOW, -65, -12, 0, 2 },
    { ENEMY_SHADOW, -85, 12, 0, 3 },
};

static const BtlFormEntry sBtlFormShadow4C = { 4, sBtlFormShadow4CSteps, 60 };

static const BtlFormStep sBtlFormShadow4DSteps[] = {
    { ENEMY_SHADOW, -55, 25, 0, 0 },
    { ENEMY_SHADOW, -85, 12, 0, 1 },
    { ENEMY_SHADOW, -65, -12, 0, 2 },
    { ENEMY_SHADOW, -25, -25, 0, 3 },
};

static const BtlFormEntry sBtlFormShadow4D = { 4, sBtlFormShadow4DSteps, 60 };

static const BtlFormStep sBtlFormShadow3ASteps[] = {
    { ENEMY_SHADOW, 40, 0, 0, 0 },
    { ENEMY_SHADOW, 65, -12, 0, 1 },
    { ENEMY_SHADOW, 85, 12, 0, 2 },
};

static const BtlFormEntry sBtlFormShadow3A = { 3, sBtlFormShadow3ASteps, 60 };

static const BtlFormStep sBtlFormShadow3BSteps[] = {
    { ENEMY_SHADOW, 65, -12, 0, 0 },
    { ENEMY_SHADOW, 85, 12, 0, 1 },
    { ENEMY_SHADOW, 90, 0, 0, 2 },
};

static const BtlFormEntry sBtlFormShadow3B = { 3, sBtlFormShadow3BSteps, 60 };

static const BtlFormStep sBtlFormShadow3CSteps[] = {
    { ENEMY_SHADOW, 65, -12, 0, 0 },
    { ENEMY_SHADOW, 85, 12, 0, 1 },
    { ENEMY_SHADOW, -40, 0, 0, 2 },
};

static const BtlFormEntry sBtlFormShadow3C = { 3, sBtlFormShadow3CSteps, 60 };

static const BtlFormStep sBtlFormShadow3DSteps[] = {
    { ENEMY_SHADOW, 25, -25, 0, 0 },
    { ENEMY_SHADOW, 64, 0, 0, 1 },
    { ENEMY_SHADOW, 55, 25, 0, 2 },
};

static const BtlFormEntry sBtlFormShadow3D = { 3, sBtlFormShadow3DSteps, 60 };

static const BtlFormStep sBtlFormShadow3ESteps[] = {
    { ENEMY_SHADOW, -25, 25, 0, 0 },
    { ENEMY_SHADOW, -64, 0, 0, 1 },
    { ENEMY_SHADOW, -55, -25, 0, 2 },
};

static const BtlFormEntry sBtlFormShadow3E = { 3, sBtlFormShadow3ESteps, 60 };

static const BtlFormStep sBtlFormShadow3FSteps[] = {
    { ENEMY_SHADOW, -65, -12, 0, 0 },
    { ENEMY_SHADOW, -85, 12, 0, 1 },
    { ENEMY_SHADOW, 40, 0, 0, 2 },
};

static const BtlFormEntry sBtlFormShadow3F = { 3, sBtlFormShadow3FSteps, 60 };

static const BtlFormStep sBtlFormShadow2ASteps[] = {
    { ENEMY_SHADOW, 65, -12, 0, 0 },
    { ENEMY_SHADOW, 85, 12, 0, 1 },
};

static const BtlFormEntry sBtlFormShadow2A = { 2, sBtlFormShadow2ASteps, 60 };

static const BtlFormStep sBtlFormShadow2BSteps[] = {
    { ENEMY_SHADOW, 25, -25, 0, 0 },
    { ENEMY_SHADOW, 55, 25, 0, 1 },
};

static const BtlFormEntry sBtlFormShadow2B = { 2, sBtlFormShadow2BSteps, 60 };

static const BtlFormStep sBtlFormShadow2CSteps[] = {
    { ENEMY_SHADOW, 40, 0, 0, 0 },
    { ENEMY_SHADOW, -40, 0, 0, 1 },
};

static const BtlFormEntry sBtlFormShadow2C = { 2, sBtlFormShadow2CSteps, 60 };

static const BtlFormStep sBtlFormShadow2DSteps[] = {
    { ENEMY_SHADOW, 40, 0, 0, 0 },
    { ENEMY_SHADOW, 90, 0, 0, 1 },
};

static const BtlFormEntry sBtlFormShadow2D = { 2, sBtlFormShadow2DSteps, 60 };

static const BtlFormStep sBtlFormShadow2ESteps[] = {
    { ENEMY_SHADOW, -65, -12, 0, 0 },
    { ENEMY_SHADOW, -85, 12, 0, 1 },
};

static const BtlFormEntry sBtlFormShadow2E = { 2, sBtlFormShadow2ESteps, 60 };

static const BtlFormStep sBtlFormShadow2FSteps[] = {
    { ENEMY_SHADOW, -55, 25, 0, 0 },
    { ENEMY_SHADOW, -25, -25, 0, 1 },
};

static const BtlFormEntry sBtlFormShadow2F = { 2, sBtlFormShadow2FSteps, 60 };

static const BtlFormStep sBtlFormShadow1Steps[] = {
    { ENEMY_SHADOW, 64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormShadow1 = { 1, sBtlFormShadow1Steps, 60 };

static const BtlFormStep sBtlFormRedNocturne5Steps[] = {
    { ENEMY_RED_NOCTURNE, 25, -25, -30, 0 },
    { ENEMY_RED_NOCTURNE, 40, 0, -30, 1 },
    { ENEMY_RED_NOCTURNE, 55, 25, -30, 2 },
    { ENEMY_RED_NOCTURNE, 65, -12, -40, 3 },
    { ENEMY_RED_NOCTURNE, 85, 12, -40, 4 },
};

const BtlFormEntry gBtlFormRedNocturne5 = { 5, sBtlFormRedNocturne5Steps, 60 };

static const BtlFormStep sBtlFormRedNocturne4Steps[] = {
    { ENEMY_RED_NOCTURNE, 25, -25, -30, 0 },
    { ENEMY_RED_NOCTURNE, 55, 25, -30, 1 },
    { ENEMY_RED_NOCTURNE, 65, -12, -40, 2 },
    { ENEMY_RED_NOCTURNE, 85, 12, -40, 3 },
};

static const BtlFormEntry sBtlFormRedNocturne4 = { 4, sBtlFormRedNocturne4Steps, 60 };

static const BtlFormStep sBtlFormRedNocturne3ASteps[] = {
    { ENEMY_RED_NOCTURNE, 40, 0, -30, 0 },
    { ENEMY_RED_NOCTURNE, 65, -12, -40, 1 },
    { ENEMY_RED_NOCTURNE, 85, 12, -40, 2 },
};

const BtlFormEntry gBtlFormRedNocturne3A = { 3, sBtlFormRedNocturne3ASteps, 60 };

static const BtlFormStep sBtlFormRedNocturne3BSteps[] = {
    { ENEMY_RED_NOCTURNE, 65, -12, -40, 0 },
    { ENEMY_RED_NOCTURNE, 85, 12, -40, 1 },
    { ENEMY_RED_NOCTURNE, -40, 0, -30, 2 },
};

static const BtlFormEntry sBtlFormRedNocturne3B = { 3, sBtlFormRedNocturne3BSteps, 60 };

static const BtlFormStep sBtlFormRedNocturne2ASteps[] = {
    { ENEMY_RED_NOCTURNE, 65, -12, -40, 0 },
    { ENEMY_RED_NOCTURNE, 85, 12, -40, 1 },
};

static const BtlFormEntry sBtlFormRedNocturne2A = { 2, sBtlFormRedNocturne2ASteps, 60 };

static const BtlFormStep sBtlFormRedNocturne2BSteps[] = {
    { ENEMY_RED_NOCTURNE, -65, -12, -40, 0 },
    { ENEMY_RED_NOCTURNE, -85, 12, -40, 1 },
};

static const BtlFormEntry sBtlFormRedNocturne2B = { 2, sBtlFormRedNocturne2BSteps, 60 };

static const BtlFormStep sBtlFormRedNocturne1ASteps[] = {
    { ENEMY_RED_NOCTURNE, 64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormRedNocturne1A = { 1, sBtlFormRedNocturne1ASteps, 60 };

static const BtlFormStep sBtlFormRedNocturne1BSteps[] = {
    { ENEMY_RED_NOCTURNE, 25, -25, -30, 0 },
};

static const BtlFormEntry sBtlFormRedNocturne1B = { 1, sBtlFormRedNocturne1BSteps, 60 };

static const BtlFormStep sBtlFormRedNocturne1CSteps[] = {
    { ENEMY_RED_NOCTURNE, -25, -25, -30, 0 },
};

const BtlFormEntry gBtlFormRedNocturne1C = { 1, sBtlFormRedNocturne1CSteps, 60 };

static const BtlFormStep sBtlFormRedNocturne1DSteps[] = {
    { ENEMY_RED_NOCTURNE, 55, 25, -30, 0 },
};

const BtlFormEntry gBtlFormRedNocturne1D = { 1, sBtlFormRedNocturne1DSteps, 60 };

static const BtlFormStep sBtlFormRedNocturne1ESteps[] = {
    { ENEMY_RED_NOCTURNE, -55, 25, -30, 0 },
};

const BtlFormEntry gBtlFormRedNocturne1E = { 1, sBtlFormRedNocturne1ESteps, 60 };

static const BtlFormStep sBtlFormBlueRhapsody5Steps[] = {
    { ENEMY_BLUE_RHAPSODY, 25, -25, -30, 0 },
    { ENEMY_BLUE_RHAPSODY, 55, 25, -30, 1 },
    { ENEMY_BLUE_RHAPSODY, 90, 0, -50, 2 },
    { ENEMY_BLUE_RHAPSODY, -65, -12, -40, 3 },
    { ENEMY_BLUE_RHAPSODY, -85, 12, -40, 4 },
};

const BtlFormEntry gBtlFormBlueRhapsody5 = { 5, sBtlFormBlueRhapsody5Steps, 60 };

static const BtlFormStep sBtlFormBlueRhapsody4Steps[] = {
    { ENEMY_BLUE_RHAPSODY, 40, 0, -30, 0 },
    { ENEMY_BLUE_RHAPSODY, 65, -12, -40, 1 },
    { ENEMY_BLUE_RHAPSODY, 85, 12, -40, 2 },
    { ENEMY_BLUE_RHAPSODY, 90, 0, -50, 3 },
};

static const BtlFormEntry sBtlFormBlueRhapsody4 = { 4, sBtlFormBlueRhapsody4Steps, 60 };

static const BtlFormStep sBtlFormBlueRhapsody3Steps[] = {
    { ENEMY_BLUE_RHAPSODY, 65, -12, -40, 0 },
    { ENEMY_BLUE_RHAPSODY, 85, 12, -40, 1 },
    { ENEMY_BLUE_RHAPSODY, 90, 0, -50, 2 },
};

static const BtlFormEntry sBtlFormBlueRhapsody3 = { 3, sBtlFormBlueRhapsody3Steps, 60 };

static const BtlFormStep sBtlFormBlueRhapsody2ASteps[] = {
    { ENEMY_BLUE_RHAPSODY, 25, -25, -30, 0 },
    { ENEMY_BLUE_RHAPSODY, 55, 25, -30, 1 },
};

static const BtlFormEntry sBtlFormBlueRhapsody2A = { 2, sBtlFormBlueRhapsody2ASteps, 60 };

static const BtlFormStep sBtlFormBlueRhapsody2BSteps[] = {
    { ENEMY_BLUE_RHAPSODY, -65, -12, -40, 0 },
    { ENEMY_BLUE_RHAPSODY, -85, 12, -40, 1 },
};

static const BtlFormEntry sBtlFormBlueRhapsody2B = { 2, sBtlFormBlueRhapsody2BSteps, 60 };

static const BtlFormStep sBtlFormBlueRhapsody2CSteps[] = {
    { ENEMY_BLUE_RHAPSODY, -55, 25, -30, 0 },
    { ENEMY_BLUE_RHAPSODY, -25, -25, -30, 1 },
};

static const BtlFormEntry sBtlFormBlueRhapsody2C = { 2, sBtlFormBlueRhapsody2CSteps, 60 };

static const BtlFormStep sBtlFormBlueRhapsody1ASteps[] = {
    { ENEMY_BLUE_RHAPSODY, 64, 0, -50, 0 },
};

const BtlFormEntry gBtlFormBlueRhapsody1A = { 1, sBtlFormBlueRhapsody1ASteps, 60 };

static const BtlFormStep sBtlFormBlueRhapsody1BSteps[] = {
    { ENEMY_BLUE_RHAPSODY, 40, 0, -30, 0 },
};

static const BtlFormEntry sBtlFormBlueRhapsody1B = { 1, sBtlFormBlueRhapsody1BSteps, 60 };

static const BtlFormStep sBtlFormBlueRhapsody1CSteps[] = {
    { ENEMY_BLUE_RHAPSODY, -64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormBlueRhapsody1C = { 1, sBtlFormBlueRhapsody1CSteps, 60 };

static const BtlFormStep sBtlFormBlueRhapsody1DSteps[] = {
    { ENEMY_BLUE_RHAPSODY, 25, -25, -30, 0 },
};

const BtlFormEntry gBtlFormBlueRhapsody1D = { 1, sBtlFormBlueRhapsody1DSteps, 60 };

static const BtlFormStep sBtlFormBlueRhapsody1ESteps[] = {
    { ENEMY_BLUE_RHAPSODY, -25, -25, -30, 0 },
};

const BtlFormEntry gBtlFormBlueRhapsody1E = { 1, sBtlFormBlueRhapsody1ESteps, 60 };

static const BtlFormStep sBtlFormBlueRhapsody1FSteps[] = {
    { ENEMY_BLUE_RHAPSODY, 55, 25, -30, 0 },
};

const BtlFormEntry gBtlFormBlueRhapsody1F = { 1, sBtlFormBlueRhapsody1FSteps, 60 };

static const BtlFormStep sBtlFormBlueRhapsody1GSteps[] = {
    { ENEMY_BLUE_RHAPSODY, -55, 25, -30, 0 },
};

static const BtlFormEntry sBtlFormBlueRhapsody1G = { 1, sBtlFormBlueRhapsody1GSteps, 60 };

static const BtlFormStep sBtlFormYellowOpera5Steps[] = {
    { ENEMY_YELLOW_OPERA, 65, -12, -40, 0 },
    { ENEMY_YELLOW_OPERA, 85, 12, -40, 1 },
    { ENEMY_YELLOW_OPERA, -25, -25, -30, 2 },
    { ENEMY_YELLOW_OPERA, -40, 0, -30, 3 },
    { ENEMY_YELLOW_OPERA, -55, 25, -30, 4 },
};

const BtlFormEntry gBtlFormYellowOpera5 = { 5, sBtlFormYellowOpera5Steps, 60 };

static const BtlFormStep sBtlFormYellowOpera4Steps[] = {
    { ENEMY_YELLOW_OPERA, 65, -12, -40, 0 },
    { ENEMY_YELLOW_OPERA, 85, 12, -40, 1 },
    { ENEMY_YELLOW_OPERA, -65, -12, -40, 2 },
    { ENEMY_YELLOW_OPERA, -85, 12, -40, 3 },
};

static const BtlFormEntry sBtlFormYellowOpera4 = { 4, sBtlFormYellowOpera4Steps, 60 };

static const BtlFormStep sBtlFormYellowOpera3ASteps[] = {
    { ENEMY_YELLOW_OPERA, 65, -12, -40, 0 },
    { ENEMY_YELLOW_OPERA, 85, 12, -40, 1 },
    { ENEMY_YELLOW_OPERA, -40, 0, -30, 2 },
};

static const BtlFormEntry sBtlFormYellowOpera3A = { 3, sBtlFormYellowOpera3ASteps, 60 };

static const BtlFormStep sBtlFormYellowOpera3BSteps[] = {
    { ENEMY_YELLOW_OPERA, -25, 25, -30, 0 },
    { ENEMY_YELLOW_OPERA, -64, 0, -50, 1 },
    { ENEMY_YELLOW_OPERA, -55, -25, -30, 2 },
};

static const BtlFormEntry sBtlFormYellowOpera3B = { 3, sBtlFormYellowOpera3BSteps, 60 };

static const BtlFormStep sBtlFormYellowOpera2ASteps[] = {
    { ENEMY_YELLOW_OPERA, 65, -12, -40, 0 },
    { ENEMY_YELLOW_OPERA, 85, 12, -40, 1 },
};

const BtlFormEntry gBtlFormYellowOpera2A = { 2, sBtlFormYellowOpera2ASteps, 60 };

static const BtlFormStep sBtlFormYellowOpera2BSteps[] = {
    { ENEMY_YELLOW_OPERA, 25, -25, -30, 0 },
    { ENEMY_YELLOW_OPERA, 55, 25, -30, 1 },
};

static const BtlFormEntry sBtlFormYellowOpera2B = { 2, sBtlFormYellowOpera2BSteps, 60 };

static const BtlFormStep sBtlFormYellowOpera2CSteps[] = {
    { ENEMY_YELLOW_OPERA, 40, 0, -30, 0 },
    { ENEMY_YELLOW_OPERA, -40, 0, -30, 1 },
};

const BtlFormEntry gBtlFormYellowOpera2C = { 2, sBtlFormYellowOpera2CSteps, 60 };

static const BtlFormStep sBtlFormYellowOpera2DSteps[] = {
    { ENEMY_YELLOW_OPERA, 40, 0, -30, 0 },
    { ENEMY_YELLOW_OPERA, 90, 0, -50, 1 },
};

static const BtlFormEntry sBtlFormYellowOpera2D = { 2, sBtlFormYellowOpera2DSteps, 60 };

static const BtlFormStep sBtlFormYellowOpera2ESteps[] = {
    { ENEMY_YELLOW_OPERA, -65, -12, -40, 0 },
    { ENEMY_YELLOW_OPERA, -85, 12, -40, 1 },
};

static const BtlFormEntry sBtlFormYellowOpera2E = { 2, sBtlFormYellowOpera2ESteps, 60 };

static const BtlFormStep sBtlFormYellowOpera2FSteps[] = {
    { ENEMY_YELLOW_OPERA, -55, 25, -30, 0 },
    { ENEMY_YELLOW_OPERA, -25, -25, -30, 1 },
};

static const BtlFormEntry sBtlFormYellowOpera2F = { 2, sBtlFormYellowOpera2FSteps, 60 };

static const BtlFormStep sBtlFormYellowOpera1ASteps[] = {
    { ENEMY_YELLOW_OPERA, 64, 0, -50, 0 },
};

const BtlFormEntry gBtlFormYellowOpera1A = { 1, sBtlFormYellowOpera1ASteps, 60 };

static const BtlFormStep sBtlFormYellowOpera1BSteps[] = {
    { ENEMY_YELLOW_OPERA, 25, -25, -30, 0 },
};

const BtlFormEntry gBtlFormYellowOpera1B = { 1, sBtlFormYellowOpera1BSteps, 60 };

static const BtlFormStep sBtlFormYellowOpera1CSteps[] = {
    { ENEMY_YELLOW_OPERA, -25, -25, -30, 0 },
};

static const BtlFormEntry sBtlFormYellowOpera1C = { 1, sBtlFormYellowOpera1CSteps, 60 };

static const BtlFormStep sBtlFormYellowOpera1DSteps[] = {
    { ENEMY_YELLOW_OPERA, 55, 25, -30, 0 },
};

const BtlFormEntry gBtlFormYellowOpera1D = { 1, sBtlFormYellowOpera1DSteps, 60 };

static const BtlFormStep sBtlFormYellowOpera1ESteps[] = {
    { ENEMY_YELLOW_OPERA, -55, 25, -30, 0 },
};

const BtlFormEntry gBtlFormYellowOpera1E = { 1, sBtlFormYellowOpera1ESteps, 60 };

static const BtlFormStep sBtlFormGreenRequiem5Steps[] = {
    { ENEMY_GREEN_REQUIEM, 65, -12, -40, 0 },
    { ENEMY_GREEN_REQUIEM, 85, 12, -40, 1 },
    { ENEMY_GREEN_REQUIEM, -25, -25, -30, 2 },
    { ENEMY_GREEN_REQUIEM, -40, 0, -30, 3 },
    { ENEMY_GREEN_REQUIEM, -55, 25, -30, 4 },
};

const BtlFormEntry gBtlFormGreenRequiem5 = { 5, sBtlFormGreenRequiem5Steps, 60 };

static const BtlFormStep sBtlFormGreenRequiem4Steps[] = {
    { ENEMY_GREEN_REQUIEM, 65, -12, -40, 0 },
    { ENEMY_GREEN_REQUIEM, 85, 12, -40, 1 },
    { ENEMY_GREEN_REQUIEM, -65, -12, -40, 2 },
    { ENEMY_GREEN_REQUIEM, -85, 12, -40, 3 },
};

static const BtlFormEntry sBtlFormGreenRequiem4 = { 4, sBtlFormGreenRequiem4Steps, 60 };

static const BtlFormStep sBtlFormGreenRequiem3ASteps[] = {
    { ENEMY_GREEN_REQUIEM, 65, -12, -40, 0 },
    { ENEMY_GREEN_REQUIEM, 85, 12, -40, 1 },
    { ENEMY_GREEN_REQUIEM, -40, 0, -30, 2 },
};

const BtlFormEntry gBtlFormGreenRequiem3A = { 3, sBtlFormGreenRequiem3ASteps, 60 };

static const BtlFormStep sBtlFormGreenRequiem3BSteps[] = {
    { ENEMY_GREEN_REQUIEM, -65, -12, -40, 0 },
    { ENEMY_GREEN_REQUIEM, -85, 12, -40, 1 },
    { ENEMY_GREEN_REQUIEM, 40, 0, -30, 2 },
};

static const BtlFormEntry sBtlFormGreenRequiem3B = { 3, sBtlFormGreenRequiem3BSteps, 60 };

static const BtlFormStep sBtlFormGreenRequiem2ASteps[] = {
    { ENEMY_GREEN_REQUIEM, 65, -12, -40, 0 },
    { ENEMY_GREEN_REQUIEM, 85, 12, -40, 1 },
};

static const BtlFormEntry sBtlFormGreenRequiem2A = { 2, sBtlFormGreenRequiem2ASteps, 60 };

static const BtlFormStep sBtlFormGreenRequiem2BSteps[] = {
    { ENEMY_GREEN_REQUIEM, 25, -25, -30, 0 },
    { ENEMY_GREEN_REQUIEM, 55, 25, -30, 1 },
};

const BtlFormEntry gBtlFormGreenRequiem2B = { 2, sBtlFormGreenRequiem2BSteps, 60 };

static const BtlFormStep sBtlFormGreenRequiem2CSteps[] = {
    { ENEMY_GREEN_REQUIEM, 40, 0, -30, 0 },
    { ENEMY_GREEN_REQUIEM, -40, 0, -30, 1 },
};

static const BtlFormEntry sBtlFormGreenRequiem2C = { 2, sBtlFormGreenRequiem2CSteps, 60 };

static const BtlFormStep sBtlFormGreenRequiem2DSteps[] = {
    { ENEMY_GREEN_REQUIEM, -65, -12, -40, 0 },
    { ENEMY_GREEN_REQUIEM, -85, 12, -40, 1 },
};

static const BtlFormEntry sBtlFormGreenRequiem2D = { 2, sBtlFormGreenRequiem2DSteps, 60 };

static const BtlFormStep sBtlFormGreenRequiem2ESteps[] = {
    { ENEMY_GREEN_REQUIEM, -55, 25, -30, 0 },
    { ENEMY_GREEN_REQUIEM, -25, -25, -30, 1 },
};

static const BtlFormEntry sBtlFormGreenRequiem2E = { 2, sBtlFormGreenRequiem2ESteps, 60 };

static const BtlFormStep sBtlFormGreenRequiem1ASteps[] = {
    { ENEMY_GREEN_REQUIEM, 64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormGreenRequiem1A = { 1, sBtlFormGreenRequiem1ASteps, 60 };

static const BtlFormStep sBtlFormGreenRequiem1BSteps[] = {
    { ENEMY_GREEN_REQUIEM, 25, -25, -30, 0 },
};

const BtlFormEntry gBtlFormGreenRequiem1B = { 1, sBtlFormGreenRequiem1BSteps, 60 };

static const BtlFormStep sBtlFormGreenRequiem1CSteps[] = {
    { ENEMY_GREEN_REQUIEM, -25, -25, -30, 0 },
};

const BtlFormEntry gBtlFormGreenRequiem1C = { 1, sBtlFormGreenRequiem1CSteps, 60 };

static const BtlFormStep sBtlFormGreenRequiem1DSteps[] = {
    { ENEMY_GREEN_REQUIEM, 55, 25, -30, 0 },
};

static const BtlFormEntry sBtlFormGreenRequiem1D = { 1, sBtlFormGreenRequiem1DSteps, 60 };

static const BtlFormStep sBtlFormGreenRequiem1ESteps[] = {
    { ENEMY_GREEN_REQUIEM, -55, 25, -30, 0 },
};

const BtlFormEntry gBtlFormGreenRequiem1E = { 1, sBtlFormGreenRequiem1ESteps, 60 };

static const BtlFormStep sBtlFormSeaNeon6Steps[] = {
    { ENEMY_SEA_NEON, 25, -25, -30, 0 },
    { ENEMY_SEA_NEON, 40, 0, -30, 1 },
    { ENEMY_SEA_NEON, 25, 25, -30, 2 },
    { ENEMY_SEA_NEON, -25, 25, -30, 3 },
    { ENEMY_SEA_NEON, -40, 0, -30, 4 },
    { ENEMY_SEA_NEON, -25, -25, -30, 5 },
};

static const BtlFormEntry sBtlFormSeaNeon6 = { 6, sBtlFormSeaNeon6Steps, 60 };

static const BtlFormStep sBtlFormSeaNeon5Steps[] = {
    { ENEMY_SEA_NEON, 25, -25, -30, 0 },
    { ENEMY_SEA_NEON, 40, 0, -30, 1 },
    { ENEMY_SEA_NEON, 55, 25, -30, 2 },
    { ENEMY_SEA_NEON, 65, -12, -40, 3 },
    { ENEMY_SEA_NEON, 85, 12, -40, 4 },
};

const BtlFormEntry gBtlFormSeaNeon5 = { 5, sBtlFormSeaNeon5Steps, 60 };

static const BtlFormStep sBtlFormSeaNeon4ASteps[] = {
    { ENEMY_SEA_NEON, 25, -25, -30, 0 },
    { ENEMY_SEA_NEON, 55, 25, -30, 1 },
    { ENEMY_SEA_NEON, 65, -12, -40, 2 },
    { ENEMY_SEA_NEON, 85, 12, -40, 3 },
};

static const BtlFormEntry sBtlFormSeaNeon4A = { 4, sBtlFormSeaNeon4ASteps, 60 };

static const BtlFormStep sBtlFormSeaNeon4BSteps[] = {
    { ENEMY_SEA_NEON, 65, -12, -40, 0 },
    { ENEMY_SEA_NEON, 85, 12, -40, 1 },
    { ENEMY_SEA_NEON, -65, -12, -40, 2 },
    { ENEMY_SEA_NEON, -85, 12, -40, 3 },
};

static const BtlFormEntry sBtlFormSeaNeon4B = { 4, sBtlFormSeaNeon4BSteps, 60 };

static const BtlFormStep sBtlFormSeaNeon3ASteps[] = {
    { ENEMY_SEA_NEON, 40, 0, -30, 0 },
    { ENEMY_SEA_NEON, 65, -12, -40, 1 },
    { ENEMY_SEA_NEON, 85, 12, -40, 2 },
};

static const BtlFormEntry sBtlFormSeaNeon3A = { 3, sBtlFormSeaNeon3ASteps, 60 };

static const BtlFormStep sBtlFormSeaNeon3BSteps[] = {
    { ENEMY_SEA_NEON, -25, 25, -30, 0 },
    { ENEMY_SEA_NEON, -64, 0, -50, 1 },
    { ENEMY_SEA_NEON, -55, -25, -30, 2 },
};

const BtlFormEntry gBtlFormSeaNeon3B = { 3, sBtlFormSeaNeon3BSteps, 60 };

static const BtlFormStep sBtlFormSeaNeon2Steps[] = {
    { ENEMY_SEA_NEON, 65, -12, -40, 0 },
    { ENEMY_SEA_NEON, 85, 12, -40, 1 },
};

const BtlFormEntry gBtlFormSeaNeon2 = { 2, sBtlFormSeaNeon2Steps, 60 };

static const BtlFormStep sBtlFormSeaNeon1Steps[] = {
    { ENEMY_SEA_NEON, 64, 0, -50, 0 },
};

const BtlFormEntry gBtlFormSeaNeon1 = { 1, sBtlFormSeaNeon1Steps, 60 };

static const BtlFormStep sBtlFormWhiteMushroom4Steps[] = {
    { ENEMY_WHITE_MUSHROOM, 65, -12, 0, 0 },
    { ENEMY_WHITE_MUSHROOM, 85, 12, 0, 1 },
    { ENEMY_WHITE_MUSHROOM, -65, -12, 0, 2 },
    { ENEMY_WHITE_MUSHROOM, -85, 12, 0, 3 },
};

static const BtlFormEntry sBtlFormWhiteMushroom4 = { 4, sBtlFormWhiteMushroom4Steps, 60 };

static const BtlFormStep sBtlFormWhiteMushroom3Steps[] = {
    { ENEMY_WHITE_MUSHROOM, 40, 0, 0, 0 },
    { ENEMY_WHITE_MUSHROOM, 65, -12, 0, 1 },
    { ENEMY_WHITE_MUSHROOM, 85, 12, 0, 2 },
};

const BtlFormEntry gBtlFormWhiteMushroom3 = { 3, sBtlFormWhiteMushroom3Steps, 60 };

static const BtlFormStep sBtlFormWhiteMushroom2ASteps[] = {
    { ENEMY_WHITE_MUSHROOM, 25, -25, 0, 0 },
    { ENEMY_WHITE_MUSHROOM, 55, 25, 0, 1 },
};

const BtlFormEntry gBtlFormWhiteMushroom2A = { 2, sBtlFormWhiteMushroom2ASteps, 60 };

static const BtlFormStep sBtlFormWhiteMushroom2BSteps[] = {
    { ENEMY_WHITE_MUSHROOM, 40, 0, 0, 0 },
    { ENEMY_WHITE_MUSHROOM, -40, 0, 0, 1 },
};

static const BtlFormEntry sBtlFormWhiteMushroom2B = { 2, sBtlFormWhiteMushroom2BSteps, 60 };

static const BtlFormStep sBtlFormWhiteMushroom1Steps[] = {
    { ENEMY_WHITE_MUSHROOM, 64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormWhiteMushroom1 = { 1, sBtlFormWhiteMushroom1Steps, 60 };

static const BtlFormStep sBtlFormBlackFungus4Steps[] = {
    { ENEMY_BLACK_FUNGUS, 65, -12, 0, 0 },
    { ENEMY_BLACK_FUNGUS, 85, 12, 0, 1 },
    { ENEMY_BLACK_FUNGUS, -65, -12, 0, 2 },
    { ENEMY_BLACK_FUNGUS, -85, 12, 0, 3 },
};

static const BtlFormEntry sBtlFormBlackFungus4 = { 4, sBtlFormBlackFungus4Steps, 60 };

static const BtlFormStep sBtlFormBlackFungus3Steps[] = {
    { ENEMY_BLACK_FUNGUS, 65, -12, 0, 0 },
    { ENEMY_BLACK_FUNGUS, 85, 12, 0, 1 },
    { ENEMY_BLACK_FUNGUS, -40, 0, 0, 2 },
};

const BtlFormEntry gBtlFormBlackFungus3 = { 3, sBtlFormBlackFungus3Steps, 60 };

static const BtlFormStep sBtlFormBlackFungus2ASteps[] = {
    { ENEMY_BLACK_FUNGUS, 65, -12, 0, 0 },
    { ENEMY_BLACK_FUNGUS, 85, 12, 0, 1 },
};

const BtlFormEntry gBtlFormBlackFungus2A = { 2, sBtlFormBlackFungus2ASteps, 60 };

static const BtlFormStep sBtlFormBlackFungus2BSteps[] = {
    { ENEMY_BLACK_FUNGUS, 40, 0, 0, 0 },
    { ENEMY_BLACK_FUNGUS, -40, 0, 0, 1 },
};

static const BtlFormEntry sBtlFormBlackFungus2B = { 2, sBtlFormBlackFungus2BSteps, 60 };

static const BtlFormStep sBtlFormBlackFungus1Steps[] = {
    { ENEMY_BLACK_FUNGUS, 64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormBlackFungus1 = { 1, sBtlFormBlackFungus1Steps, 60 };

static const BtlFormStep sBtlFormSoldier6Steps[] = {
    { ENEMY_SOLDIER, 25, -25, 0, 0 },
    { ENEMY_SOLDIER, 40, 0, 0, 1 },
    { ENEMY_SOLDIER, 55, 25, 0, 2 },
    { ENEMY_SOLDIER, -55, -25, 0, 3 },
    { ENEMY_SOLDIER, -40, 0, 0, 4 },
    { ENEMY_SOLDIER, -25, 25, 0, 5 },
};

static const BtlFormEntry sBtlFormSoldier6 = { 6, sBtlFormSoldier6Steps, 60 };

static const BtlFormStep sBtlFormSoldier5ASteps[] = {
    { ENEMY_SOLDIER, 25, -25, 0, 0 },
    { ENEMY_SOLDIER, 55, 25, 0, 1 },
    { ENEMY_SOLDIER, 90, 0, 0, 2 },
    { ENEMY_SOLDIER, -65, -12, 0, 3 },
    { ENEMY_SOLDIER, -85, 12, 0, 4 },
};

const BtlFormEntry gBtlFormSoldier5A = { 5, sBtlFormSoldier5ASteps, 60 };

static const BtlFormStep sBtlFormSoldier5BSteps[] = {
    { ENEMY_SOLDIER, 65, -12, -40, 0 },
    { ENEMY_SOLDIER, 85, 12, -40, 1 },
    { ENEMY_SOLDIER, -25, -25, -30, 2 },
    { ENEMY_SOLDIER, -40, 0, -30, 3 },
    { ENEMY_SOLDIER, -55, 25, -30, 4 },
};

const BtlFormEntry gBtlFormSoldier5B = { 5, sBtlFormSoldier5BSteps, 60 };

static const BtlFormStep sBtlFormSoldier4ASteps[] = {
    { ENEMY_SOLDIER, 25, -25, 0, 0 },
    { ENEMY_SOLDIER, 55, 25, 0, 1 },
    { ENEMY_SOLDIER, 65, -12, 0, 2 },
    { ENEMY_SOLDIER, 85, 12, 0, 3 },
};

const BtlFormEntry gBtlFormSoldier4A = { 4, sBtlFormSoldier4ASteps, 60 };

static const BtlFormStep sBtlFormSoldier4BSteps[] = {
    { ENEMY_SOLDIER, 40, 0, -30, 0 },
    { ENEMY_SOLDIER, 65, -12, -40, 1 },
    { ENEMY_SOLDIER, 85, 12, -40, 2 },
    { ENEMY_SOLDIER, 90, 0, -50, 3 },
};

static const BtlFormEntry sBtlFormSoldier4B = { 4, sBtlFormSoldier4BSteps, 60 };

static const BtlFormStep sBtlFormSoldier4CSteps[] = {
    { ENEMY_SOLDIER, 65, -12, 0, 0 },
    { ENEMY_SOLDIER, 85, 12, 0, 1 },
    { ENEMY_SOLDIER, -65, -12, 0, 2 },
    { ENEMY_SOLDIER, -85, 12, 0, 3 },
};

static const BtlFormEntry sBtlFormSoldier4C = { 4, sBtlFormSoldier4CSteps, 60 };

static const BtlFormStep sBtlFormSoldier3ASteps[] = {
    { ENEMY_SOLDIER, 40, 0, -30, 0 },
    { ENEMY_SOLDIER, 65, -12, -40, 1 },
    { ENEMY_SOLDIER, 85, 12, -40, 2 },
};

const BtlFormEntry gBtlFormSoldier3A = { 3, sBtlFormSoldier3ASteps, 60 };

static const BtlFormStep sBtlFormSoldier3BSteps[] = {
    { ENEMY_SOLDIER, 65, -12, 0, 0 },
    { ENEMY_SOLDIER, 85, 12, 0, 1 },
    { ENEMY_SOLDIER, 90, 0, 0, 2 },
};

const BtlFormEntry gBtlFormSoldier3B = { 3, sBtlFormSoldier3BSteps, 60 };

static const BtlFormStep sBtlFormSoldier3CSteps[] = {
    { ENEMY_SOLDIER, 65, -12, -40, 0 },
    { ENEMY_SOLDIER, 85, 12, -40, 1 },
    { ENEMY_SOLDIER, -40, 0, -30, 2 },
};

const BtlFormEntry gBtlFormSoldier3C = { 3, sBtlFormSoldier3CSteps, 60 };

static const BtlFormStep sBtlFormSoldier3DSteps[] = {
    { ENEMY_SOLDIER, 25, -25, 0, 0 },
    { ENEMY_SOLDIER, 64, 0, 0, 1 },
    { ENEMY_SOLDIER, 55, 25, 0, 2 },
};

static const BtlFormEntry sBtlFormSoldier3D = { 3, sBtlFormSoldier3DSteps, 60 };

static const BtlFormStep sBtlFormSoldier3ESteps[] = {
    { ENEMY_SOLDIER, -25, 25, 0, 0 },
    { ENEMY_SOLDIER, -64, 0, 0, 1 },
    { ENEMY_SOLDIER, -55, -25, 0, 2 },
};

static const BtlFormEntry sBtlFormSoldier3E = { 3, sBtlFormSoldier3ESteps, 60 };

static const BtlFormStep sBtlFormSoldier2ASteps[] = {
    { ENEMY_SOLDIER, 65, -12, 0, 0 },
    { ENEMY_SOLDIER, 85, 12, 0, 1 },
};

static const BtlFormEntry sBtlFormSoldier2A = { 2, sBtlFormSoldier2ASteps, 60 };

static const BtlFormStep sBtlFormSoldier2BSteps[] = {
    { ENEMY_SOLDIER, 25, -25, -30, 0 },
    { ENEMY_SOLDIER, 55, 25, -30, 1 },
};

static const BtlFormEntry sBtlFormSoldier2B = { 2, sBtlFormSoldier2BSteps, 60 };

static const BtlFormStep sBtlFormSoldier2CSteps[] = {
    { ENEMY_SOLDIER, 40, 0, 0, 0 },
    { ENEMY_SOLDIER, -40, 0, 0, 1 },
};

static const BtlFormEntry sBtlFormSoldier2C = { 2, sBtlFormSoldier2CSteps, 60 };

static const BtlFormStep sBtlFormSoldier2DSteps[] = {
    { ENEMY_SOLDIER, -65, -12, 0, 0 },
    { ENEMY_SOLDIER, -85, 12, 0, 1 },
};

static const BtlFormEntry sBtlFormSoldier2D = { 2, sBtlFormSoldier2DSteps, 60 };

static const BtlFormStep sBtlFormSoldier1ASteps[] = {
    { ENEMY_SOLDIER, 64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormSoldier1A = { 1, sBtlFormSoldier1ASteps, 60 };

static const BtlFormStep sBtlFormSoldier1BSteps[] = {
    { ENEMY_SOLDIER, 40, 0, 0, 0 },
};

const BtlFormEntry gBtlFormSoldier1B = { 1, sBtlFormSoldier1BSteps, 60 };

static const BtlFormStep sBtlFormSoldier1CSteps[] = {
    { ENEMY_SOLDIER, -64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormSoldier1C = { 1, sBtlFormSoldier1CSteps, 60 };

static const BtlFormStep sBtlFormSoldier1DSteps[] = {
    { ENEMY_SOLDIER, -40, 0, 0, 0 },
};

const BtlFormEntry gBtlFormSoldier1D = { 1, sBtlFormSoldier1DSteps, 60 };

static const BtlFormStep sBtlFormPowerwild3Steps[] = {
    { ENEMY_POWERWILD, 40, 0, 0, 0 },
    { ENEMY_POWERWILD, 65, -12, 0, 1 },
    { ENEMY_POWERWILD, 85, 12, 0, 2 },
};

static const BtlFormEntry sBtlFormPowerwild3 = { 3, sBtlFormPowerwild3Steps, 60 };

static const BtlFormStep sBtlFormPowerwild2ASteps[] = {
    { ENEMY_POWERWILD, 25, -25, 0, 0 },
    { ENEMY_POWERWILD, 55, 25, 0, 1 },
};

static const BtlFormEntry sBtlFormPowerwild2A = { 2, sBtlFormPowerwild2ASteps, 60 };

static const BtlFormStep sBtlFormPowerwild2BSteps[] = {
    { ENEMY_POWERWILD, -65, -12, 0, 0 },
    { ENEMY_POWERWILD, -85, 12, 0, 1 },
};

static const BtlFormEntry sBtlFormPowerwild2B = { 2, sBtlFormPowerwild2BSteps, 60 };

static const BtlFormStep sBtlFormPowerwild1Steps[] = {
    { ENEMY_POWERWILD, 64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormPowerwild1 = { 1, sBtlFormPowerwild1Steps, 60 };

static const BtlFormStep sBtlFormBouncywild3Steps[] = {
    { ENEMY_BOUNCYWILD, 65, -12, 0, 0 },
    { ENEMY_BOUNCYWILD, 85, 12, 0, 1 },
    { ENEMY_BOUNCYWILD, 90, 0, 0, 2 },
};

static const BtlFormEntry sBtlFormBouncywild3 = { 3, sBtlFormBouncywild3Steps, 60 };

static const BtlFormStep sBtlFormBouncywild2ASteps[] = {
    { ENEMY_BOUNCYWILD, 40, 0, 0, 0 },
    { ENEMY_BOUNCYWILD, -40, 0, 0, 1 },
};

static const BtlFormEntry sBtlFormBouncywild2A = { 2, sBtlFormBouncywild2ASteps, 60 };

static const BtlFormStep sBtlFormBouncywild2BSteps[] = {
    { ENEMY_BOUNCYWILD, -55, 25, 0, 0 },
    { ENEMY_BOUNCYWILD, -25, -25, 0, 1 },
};

static const BtlFormEntry sBtlFormBouncywild2B = { 2, sBtlFormBouncywild2BSteps, 60 };

static const BtlFormStep sBtlFormBouncywild1Steps[] = {
    { ENEMY_BOUNCYWILD, 64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormBouncywild1 = { 1, sBtlFormBouncywild1Steps, 60 };

static const BtlFormStep sBtlFormAirSoldier4ASteps[] = {
    { ENEMY_AIR_SOLDIER, 25, -25, -30, 0 },
    { ENEMY_AIR_SOLDIER, 55, 25, -30, 1 },
    { ENEMY_AIR_SOLDIER, 65, -12, -40, 2 },
    { ENEMY_AIR_SOLDIER, 85, 12, -40, 3 },
};

static const BtlFormEntry sBtlFormAirSoldier4A = { 4, sBtlFormAirSoldier4ASteps, 60 };

static const BtlFormStep sBtlFormAirSoldier4BSteps[] = {
    { ENEMY_AIR_SOLDIER, 65, -12, -40, 0 },
    { ENEMY_AIR_SOLDIER, 85, 12, -40, 1 },
    { ENEMY_AIR_SOLDIER, -65, -12, -40, 2 },
    { ENEMY_AIR_SOLDIER, -85, 12, -40, 3 },
};

static const BtlFormEntry sBtlFormAirSoldier4B = { 4, sBtlFormAirSoldier4BSteps, 60 };

static const BtlFormStep sBtlFormAirSoldier3ASteps[] = {
    { ENEMY_AIR_SOLDIER, 65, -12, -40, 0 },
    { ENEMY_AIR_SOLDIER, 85, 12, -40, 1 },
    { ENEMY_AIR_SOLDIER, 90, 0, -50, 2 },
};

static const BtlFormEntry sBtlFormAirSoldier3A = { 3, sBtlFormAirSoldier3ASteps, 60 };

static const BtlFormStep sBtlFormAirSoldier3BSteps[] = {
    { ENEMY_AIR_SOLDIER, 65, -12, -40, 0 },
    { ENEMY_AIR_SOLDIER, 85, 12, -40, 1 },
    { ENEMY_AIR_SOLDIER, -40, 0, -30, 2 },
};

static const BtlFormEntry sBtlFormAirSoldier3B = { 3, sBtlFormAirSoldier3BSteps, 60 };

static const BtlFormStep sBtlFormAirSoldier2ASteps[] = {
    { ENEMY_AIR_SOLDIER, 40, 0, -30, 0 },
    { ENEMY_AIR_SOLDIER, -40, 0, -30, 1 },
};

static const BtlFormEntry sBtlFormAirSoldier2A = { 2, sBtlFormAirSoldier2ASteps, 60 };

static const BtlFormStep sBtlFormAirSoldier2BSteps[] = {
    { ENEMY_AIR_SOLDIER, -55, 25, -30, 0 },
    { ENEMY_AIR_SOLDIER, -25, -25, -30, 1 },
};

static const BtlFormEntry sBtlFormAirSoldier2B = { 2, sBtlFormAirSoldier2BSteps, 60 };

static const BtlFormStep sBtlFormAirSoldier1Steps[] = {
    { ENEMY_AIR_SOLDIER, 64, 0, -50, 0 },
};

const BtlFormEntry gBtlFormAirSoldier1 = { 1, sBtlFormAirSoldier1Steps, 60 };

static const BtlFormStep sBtlFormBandit5Steps[] = {
    { ENEMY_BANDIT, 25, -25, 0, 0 },
    { ENEMY_BANDIT, 55, 25, 0, 1 },
    { ENEMY_BANDIT, 90, 0, 0, 2 },
    { ENEMY_BANDIT, -65, -12, 0, 3 },
    { ENEMY_BANDIT, -85, 12, 0, 4 },
};

const BtlFormEntry gBtlFormBandit5 = { 5, sBtlFormBandit5Steps, 60 };

static const BtlFormStep sBtlFormBandit4ASteps[] = {
    { ENEMY_BANDIT, 25, -25, 0, 0 },
    { ENEMY_BANDIT, 55, 25, 0, 1 },
    { ENEMY_BANDIT, 65, -12, 0, 2 },
    { ENEMY_BANDIT, 85, 12, 0, 3 },
};

const BtlFormEntry gBtlFormBandit4A = { 4, sBtlFormBandit4ASteps, 60 };

static const BtlFormStep sBtlFormBandit4BSteps[] = {
    { ENEMY_BANDIT, 65, -12, 0, 0 },
    { ENEMY_BANDIT, 85, 12, 0, 1 },
    { ENEMY_BANDIT, -65, -12, 0, 2 },
    { ENEMY_BANDIT, -85, 12, 0, 3 },
};

static const BtlFormEntry sBtlFormBandit4B = { 4, sBtlFormBandit4BSteps, 60 };

static const BtlFormStep sBtlFormBandit3Steps[] = {
    { ENEMY_BANDIT, 65, -12, 0, 0 },
    { ENEMY_BANDIT, 85, 12, 0, 1 },
    { ENEMY_BANDIT, -40, 0, 0, 2 },
};

const BtlFormEntry gBtlFormBandit3 = { 3, sBtlFormBandit3Steps, 60 };

static const BtlFormStep sBtlFormBandit2ASteps[] = {
    { ENEMY_BANDIT, 25, -25, 0, 0 },
    { ENEMY_BANDIT, 55, 25, 0, 1 },
};

static const BtlFormEntry sBtlFormBandit2A = { 2, sBtlFormBandit2ASteps, 60 };

static const BtlFormStep sBtlFormBandit2BSteps[] = {
    { ENEMY_BANDIT, -55, 25, 0, 0 },
    { ENEMY_BANDIT, -25, -25, 0, 1 },
};

static const BtlFormEntry sBtlFormBandit2B = { 2, sBtlFormBandit2BSteps, 60 };

static const BtlFormStep sBtlFormBandit1ASteps[] = {
    { ENEMY_BANDIT, 64, 0, 0, 0 },
};

const BtlFormEntry gBtlFormBandit1A = { 1, sBtlFormBandit1ASteps, 60 };

static const BtlFormStep sBtlFormBandit1BSteps[] = {
    { ENEMY_BANDIT, 40, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormBandit1B = { 1, sBtlFormBandit1BSteps, 60 };

static const BtlFormStep sBtlFormBarrelSpider3Steps[] = {
    { ENEMY_BARREL_SPIDER, 40, 0, 0, 0 },
    { ENEMY_BARREL_SPIDER, 65, -12, 0, 1 },
    { ENEMY_BARREL_SPIDER, 85, 12, 0, 2 },
};

static const BtlFormEntry sBtlFormBarrelSpider3 = { 3, sBtlFormBarrelSpider3Steps, 60 };

static const BtlFormStep sBtlFormBarrelSpider2ASteps[] = {
    { ENEMY_BARREL_SPIDER, 65, -12, 0, 0 },
    { ENEMY_BARREL_SPIDER, 85, 12, 0, 1 },
};

static const BtlFormEntry sBtlFormBarrelSpider2A = { 2, sBtlFormBarrelSpider2ASteps, 60 };

static const BtlFormStep sBtlFormBarrelSpider2BSteps[] = {
    { ENEMY_BARREL_SPIDER, 40, 0, 0, 0 },
    { ENEMY_BARREL_SPIDER, -40, 0, 0, 1 },
};

static const BtlFormEntry sBtlFormBarrelSpider2B = { 2, sBtlFormBarrelSpider2BSteps, 60 };

static const BtlFormStep sBtlFormBarrelSpider2CSteps[] = {
    { ENEMY_BARREL_SPIDER, -65, -12, 0, 0 },
    { ENEMY_BARREL_SPIDER, -85, 12, 0, 1 },
};

static const BtlFormEntry sBtlFormBarrelSpider2C = { 2, sBtlFormBarrelSpider2CSteps, 60 };

static const BtlFormStep sBtlFormBarrelSpider1ASteps[] = {
    { ENEMY_BARREL_SPIDER, 64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormBarrelSpider1A = { 1, sBtlFormBarrelSpider1ASteps, 60 };

static const BtlFormStep sBtlFormBarrelSpider1BSteps[] = {
    { ENEMY_BARREL_SPIDER, -64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormBarrelSpider1B = { 1, sBtlFormBarrelSpider1BSteps, 60 };

static const BtlFormStep sBtlFormSearchGhost3Steps[] = {
    { ENEMY_SEARCH_GHOST, 65, -12, -40, 0 },
    { ENEMY_SEARCH_GHOST, 85, 12, -40, 1 },
    { ENEMY_SEARCH_GHOST, 90, 0, -50, 2 },
};

static const BtlFormEntry sBtlFormSearchGhost3 = { 3, sBtlFormSearchGhost3Steps, 60 };

static const BtlFormStep sBtlFormSearchGhost2ASteps[] = {
    { ENEMY_SEARCH_GHOST, 25, -25, -30, 0 },
    { ENEMY_SEARCH_GHOST, 55, 25, -30, 1 },
};

static const BtlFormEntry sBtlFormSearchGhost2A = { 2, sBtlFormSearchGhost2ASteps, 60 };

static const BtlFormStep sBtlFormSearchGhost2BSteps[] = {
    { ENEMY_SEARCH_GHOST, 40, 0, -30, 0 },
    { ENEMY_SEARCH_GHOST, -40, 0, -30, 1 },
};

static const BtlFormEntry sBtlFormSearchGhost2B = { 2, sBtlFormSearchGhost2BSteps, 60 };

static const BtlFormStep sBtlFormSearchGhost2CSteps[] = {
    { ENEMY_SEARCH_GHOST, -65, -12, -40, 0 },
    { ENEMY_SEARCH_GHOST, -85, 12, -40, 1 },
};

static const BtlFormEntry sBtlFormSearchGhost2C = { 2, sBtlFormSearchGhost2CSteps, 60 };

static const BtlFormStep sBtlFormSearchGhost1ASteps[] = {
    { ENEMY_SEARCH_GHOST, 64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormSearchGhost1A = { 1, sBtlFormSearchGhost1ASteps, 60 };

static const BtlFormStep sBtlFormSearchGhost1BSteps[] = {
    { ENEMY_SEARCH_GHOST, -64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormSearchGhost1B = { 1, sBtlFormSearchGhost1BSteps, 60 };

static const BtlFormStep sBtlFormScrewdiver2ASteps[] = {
    { ENEMY_SCREWDIVER, 65, -12, -40, 0 },
    { ENEMY_SCREWDIVER, 85, 12, -40, 1 },
};

static const BtlFormEntry sBtlFormScrewdiver2A = { 2, sBtlFormScrewdiver2ASteps, 60 };

static const BtlFormStep sBtlFormScrewdiver2BSteps[] = {
    { ENEMY_SCREWDIVER, -55, 25, -30, 0 },
    { ENEMY_SCREWDIVER, -25, -25, -30, 1 },
};

static const BtlFormEntry sBtlFormScrewdiver2B = { 2, sBtlFormScrewdiver2BSteps, 60 };

static const BtlFormStep sBtlFormScrewdiver1ASteps[] = {
    { ENEMY_SCREWDIVER, 64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormScrewdiver1A = { 1, sBtlFormScrewdiver1ASteps, 60 };

static const BtlFormStep sBtlFormScrewdiver1BSteps[] = {
    { ENEMY_SCREWDIVER, -64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormScrewdiver1B = { 1, sBtlFormScrewdiver1BSteps, 60 };

static const BtlFormStep sBtlFormScrewdiver1CSteps[] = {
    { ENEMY_SCREWDIVER, 25, -25, -30, 0 },
};

static const BtlFormEntry sBtlFormScrewdiver1C = { 1, sBtlFormScrewdiver1CSteps, 60 };

static const BtlFormStep sBtlFormScrewdiver1DSteps[] = {
    { ENEMY_SCREWDIVER, -25, -25, -30, 0 },
};

static const BtlFormEntry sBtlFormScrewdiver1D = { 1, sBtlFormScrewdiver1DSteps, 60 };

static const BtlFormStep sBtlFormScrewdiver1ESteps[] = {
    { ENEMY_SCREWDIVER, 55, 25, -30, 0 },
};

static const BtlFormEntry sBtlFormScrewdiver1E = { 1, sBtlFormScrewdiver1ESteps, 60 };

static const BtlFormStep sBtlFormScrewdiver1FSteps[] = {
    { ENEMY_SCREWDIVER, -55, 25, -30, 0 },
};

static const BtlFormEntry sBtlFormScrewdiver1F = { 1, sBtlFormScrewdiver1FSteps, 60 };

static const BtlFormStep sBtlFormWightKnight3Steps[] = {
    { ENEMY_WIGHT_KNIGHT, 65, -12, 0, 0 },
    { ENEMY_WIGHT_KNIGHT, 85, 12, 0, 1 },
    { ENEMY_WIGHT_KNIGHT, -40, 0, 0, 2 },
};

const BtlFormEntry gBtlFormWightKnight3 = { 3, sBtlFormWightKnight3Steps, 60 };

static const BtlFormStep sBtlFormWightKnight2ASteps[] = {
    { ENEMY_WIGHT_KNIGHT, 25, -25, 0, 0 },
    { ENEMY_WIGHT_KNIGHT, 55, 25, 0, 1 },
};

static const BtlFormEntry sBtlFormWightKnight2A = { 2, sBtlFormWightKnight2ASteps, 60 };

static const BtlFormStep sBtlFormWightKnight2BSteps[] = {
    { ENEMY_WIGHT_KNIGHT, 40, 0, 0, 0 },
    { ENEMY_WIGHT_KNIGHT, -40, 0, 0, 1 },
};

const BtlFormEntry gBtlFormWightKnight2B = { 2, sBtlFormWightKnight2BSteps, 60 };

static const BtlFormStep sBtlFormWightKnight2CSteps[] = {
    { ENEMY_WIGHT_KNIGHT, 65, -12, 0, 0 },
    { ENEMY_WIGHT_KNIGHT, 85, 12, 0, 1 },
};

static const BtlFormEntry sBtlFormWightKnight2C = { 2, sBtlFormWightKnight2CSteps, 60 };

static const BtlFormStep sBtlFormWightKnight2DSteps[] = {
    { ENEMY_WIGHT_KNIGHT, -55, 25, 0, 0 },
    { ENEMY_WIGHT_KNIGHT, -25, -25, 0, 1 },
};

static const BtlFormEntry sBtlFormWightKnight2D = { 2, sBtlFormWightKnight2DSteps, 60 };

static const BtlFormStep sBtlFormWightKnight1ASteps[] = {
    { ENEMY_WIGHT_KNIGHT, 64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormWightKnight1A = { 1, sBtlFormWightKnight1ASteps, 60 };

static const BtlFormStep sBtlFormWightKnight1BSteps[] = {
    { ENEMY_WIGHT_KNIGHT, -64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormWightKnight1B = { 1, sBtlFormWightKnight1BSteps, 60 };

static const BtlFormStep sBtlFormGargoyle3Steps[] = {
    { ENEMY_GARGOYLE, 40, 0, -30, 0 },
    { ENEMY_GARGOYLE, 65, -12, -40, 1 },
    { ENEMY_GARGOYLE, 85, 12, -40, 2 },
};

static const BtlFormEntry sBtlFormGargoyle3 = { 3, sBtlFormGargoyle3Steps, 60 };

static const BtlFormStep sBtlFormGargoyle2ASteps[] = {
    { ENEMY_GARGOYLE, 25, -25, -30, 0 },
    { ENEMY_GARGOYLE, 55, 25, -30, 1 },
};

static const BtlFormEntry sBtlFormGargoyle2A = { 2, sBtlFormGargoyle2ASteps, 60 };

static const BtlFormStep sBtlFormGargoyle2BSteps[] = {
    { ENEMY_GARGOYLE, -55, 25, -30, 0 },
    { ENEMY_GARGOYLE, -25, -25, -30, 1 },
};

static const BtlFormEntry sBtlFormGargoyle2B = { 2, sBtlFormGargoyle2BSteps, 60 };

static const BtlFormStep sBtlFormGargoyle1ASteps[] = {
    { ENEMY_GARGOYLE, 64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormGargoyle1A = { 1, sBtlFormGargoyle1ASteps, 60 };

static const BtlFormStep sBtlFormGargoyle1BSteps[] = {
    { ENEMY_GARGOYLE, -64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormGargoyle1B = { 1, sBtlFormGargoyle1BSteps, 60 };

static const BtlFormStep sBtlFormPirate5Steps[] = {
    { ENEMY_PIRATE, 25, -25, 0, 0 },
    { ENEMY_PIRATE, 40, 0, 0, 1 },
    { ENEMY_PIRATE, 55, 25, 0, 2 },
    { ENEMY_PIRATE, 65, -12, 0, 3 },
    { ENEMY_PIRATE, 85, 12, 0, 4 },
};

const BtlFormEntry gBtlFormPirate5 = { 5, sBtlFormPirate5Steps, 60 };

static const BtlFormStep sBtlFormPirate4Steps[] = {
    { ENEMY_PIRATE, 65, -12, 0, 0 },
    { ENEMY_PIRATE, 85, 12, 0, 1 },
    { ENEMY_PIRATE, -65, -12, 0, 2 },
    { ENEMY_PIRATE, -85, 12, 0, 3 },
};

const BtlFormEntry gBtlFormPirate4 = { 4, sBtlFormPirate4Steps, 60 };

static const BtlFormStep sBtlFormPirate3ASteps[] = {
    { ENEMY_PIRATE, 65, -12, 0, 0 },
    { ENEMY_PIRATE, 85, 12, 0, 1 },
    { ENEMY_PIRATE, 90, 0, 0, 2 },
};

static const BtlFormEntry sBtlFormPirate3A = { 3, sBtlFormPirate3ASteps, 60 };

static const BtlFormStep sBtlFormPirate3BSteps[] = {
    { ENEMY_PIRATE, -65, -12, 0, 0 },
    { ENEMY_PIRATE, -85, 12, 0, 1 },
    { ENEMY_PIRATE, 40, 0, 0, 2 },
};

static const BtlFormEntry sBtlFormPirate3B = { 3, sBtlFormPirate3BSteps, 60 };

static const BtlFormStep sBtlFormPirate2ASteps[] = {
    { ENEMY_PIRATE, 65, -12, 0, 0 },
    { ENEMY_PIRATE, 85, 12, 0, 1 },
};

const BtlFormEntry gBtlFormPirate2A = { 2, sBtlFormPirate2ASteps, 60 };

static const BtlFormStep sBtlFormPirate2BSteps[] = {
    { ENEMY_PIRATE, -65, -12, 0, 0 },
    { ENEMY_PIRATE, -85, 12, 0, 1 },
};

const BtlFormEntry gBtlFormPirate2B = { 2, sBtlFormPirate2BSteps, 60 };

static const BtlFormStep sBtlFormPirate2CSteps[] = {
    { ENEMY_PIRATE, 40, 0, 0, 0 },
    { ENEMY_PIRATE, -40, 0, 0, 1 },
};

static const BtlFormEntry sBtlFormPirate2C = { 2, sBtlFormPirate2CSteps, 60 };

static const BtlFormStep sBtlFormPirate1Steps[] = {
    { ENEMY_PIRATE, 64, 0, 0, 0 },
};

const BtlFormEntry gBtlFormPirate1 = { 1, sBtlFormPirate1Steps, 60 };

static const BtlFormStep sBtlFormAirPirate2ASteps[] = {
    { ENEMY_AIR_PIRATE, 25, -25, -30, 0 },
    { ENEMY_AIR_PIRATE, 55, 25, -30, 1 },
};

static const BtlFormEntry sBtlFormAirPirate2A = { 2, sBtlFormAirPirate2ASteps, 60 };

static const BtlFormStep sBtlFormAirPirate2BSteps[] = {
    { ENEMY_AIR_PIRATE, 40, 0, -30, 0 },
    { ENEMY_AIR_PIRATE, -40, 0, -30, 1 },
};

static const BtlFormEntry sBtlFormAirPirate2B = { 2, sBtlFormAirPirate2BSteps, 60 };

static const BtlFormStep sBtlFormAirPirate2CSteps[] = {
    { ENEMY_AIR_PIRATE, -55, 25, -30, 0 },
    { ENEMY_AIR_PIRATE, -25, -25, -30, 1 },
};

static const BtlFormEntry sBtlFormAirPirate2C = { 2, sBtlFormAirPirate2CSteps, 60 };

static const BtlFormStep sBtlFormAirPirate1ASteps[] = {
    { ENEMY_AIR_PIRATE, 64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormAirPirate1A = { 1, sBtlFormAirPirate1ASteps, 60 };

static const BtlFormStep sBtlFormAirPirate1BSteps[] = {
    { ENEMY_AIR_PIRATE, -64, 0, -50, 0 },
};

const BtlFormEntry gBtlFormAirPirate1B = { 1, sBtlFormAirPirate1BSteps, 60 };

static const BtlFormStep sBtlFormAirPirate1CSteps[] = {
    { ENEMY_AIR_PIRATE, 25, -25, -30, 0 },
};

static const BtlFormEntry sBtlFormAirPirate1C = { 1, sBtlFormAirPirate1CSteps, 60 };

static const BtlFormStep sBtlFormDarkball2ASteps[] = {
    { ENEMY_DARKBALL, 65, -12, -40, 0 },
    { ENEMY_DARKBALL, 85, 12, -40, 1 },
};

const BtlFormEntry gBtlFormDarkball2A = { 2, sBtlFormDarkball2ASteps, 60 };

static const BtlFormStep sBtlFormDarkball2BSteps[] = {
    { ENEMY_DARKBALL, 25, -25, -30, 0 },
    { ENEMY_DARKBALL, 55, 25, -30, 1 },
};

static const BtlFormEntry sBtlFormDarkball2B = { 2, sBtlFormDarkball2BSteps, 60 };

static const BtlFormStep sBtlFormDarkball2CSteps[] = {
    { ENEMY_DARKBALL, 40, 0, -30, 0 },
    { ENEMY_DARKBALL, -40, 0, -30, 1 },
};

static const BtlFormEntry sBtlFormDarkball2C = { 2, sBtlFormDarkball2CSteps, 60 };

static const BtlFormStep sBtlFormDarkball2DSteps[] = {
    { ENEMY_DARKBALL, 40, 0, -30, 0 },
    { ENEMY_DARKBALL, 90, 0, -50, 1 },
};

static const BtlFormEntry sBtlFormDarkball2D = { 2, sBtlFormDarkball2DSteps, 60 };

static const BtlFormStep sBtlFormDarkball2ESteps[] = {
    { ENEMY_DARKBALL, -65, -12, -40, 0 },
    { ENEMY_DARKBALL, -85, 12, -40, 1 },
};

static const BtlFormEntry sBtlFormDarkball2E = { 2, sBtlFormDarkball2ESteps, 60 };

static const BtlFormStep sBtlFormDarkball2FSteps[] = {
    { ENEMY_DARKBALL, -55, 25, -30, 0 },
    { ENEMY_DARKBALL, -25, -25, -30, 1 },
};

static const BtlFormEntry sBtlFormDarkball2F = { 2, sBtlFormDarkball2FSteps, 60 };

static const BtlFormStep sBtlFormDarkball1ASteps[] = {
    { ENEMY_DARKBALL, 64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormDarkball1A = { 1, sBtlFormDarkball1ASteps, 60 };

static const BtlFormStep sBtlFormDarkball1BSteps[] = {
    { ENEMY_DARKBALL, -64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormDarkball1B = { 1, sBtlFormDarkball1BSteps, 60 };

static const BtlFormStep sBtlFormDarkball1CSteps[] = {
    { ENEMY_DARKBALL, 25, -25, -30, 0 },
};

static const BtlFormEntry sBtlFormDarkball1C = { 1, sBtlFormDarkball1CSteps, 60 };

static const BtlFormStep sBtlFormDarkball1DSteps[] = {
    { ENEMY_DARKBALL, -25, -25, -30, 0 },
};

static const BtlFormEntry sBtlFormDarkball1D = { 1, sBtlFormDarkball1DSteps, 60 };

static const BtlFormStep sBtlFormDarkball1ESteps[] = {
    { ENEMY_DARKBALL, 55, 25, -30, 0 },
};

static const BtlFormEntry sBtlFormDarkball1E = { 1, sBtlFormDarkball1ESteps, 60 };

static const BtlFormStep sBtlFormDarkball1FSteps[] = {
    { ENEMY_DARKBALL, -55, 25, -30, 0 },
};

static const BtlFormEntry sBtlFormDarkball1F = { 1, sBtlFormDarkball1FSteps, 60 };

static const BtlFormStep sBtlFormWyvern2Steps[] = {
    { ENEMY_WYVERN, 65, -12, -40, 0 },
    { ENEMY_WYVERN, 85, 12, -40, 1 },
};

static const BtlFormEntry sBtlFormWyvern2 = { 2, sBtlFormWyvern2Steps, 60 };

static const BtlFormStep sBtlFormWyvern1ASteps[] = {
    { ENEMY_WYVERN, 64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormWyvern1A = { 1, sBtlFormWyvern1ASteps, 60 };

static const BtlFormStep sBtlFormWyvern1BSteps[] = {
    { ENEMY_WYVERN, -64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormWyvern1B = { 1, sBtlFormWyvern1BSteps, 60 };

static const BtlFormStep sBtlFormWizard3Steps[] = {
    { ENEMY_WIZARD, 65, -12, -40, 0 },
    { ENEMY_WIZARD, 85, 12, -40, 1 },
    { ENEMY_WIZARD, 90, 0, -50, 2 },
};

const BtlFormEntry gBtlFormWizard3 = { 3, sBtlFormWizard3Steps, 60 };

static const BtlFormStep sBtlFormWizard2Steps[] = {
    { ENEMY_WIZARD, 40, 0, -30, 0 },
    { ENEMY_WIZARD, -40, 0, -30, 1 },
};

static const BtlFormEntry sBtlFormWizard2 = { 2, sBtlFormWizard2Steps, 60 };

static const BtlFormStep sBtlFormWizard1ASteps[] = {
    { ENEMY_WIZARD, 64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormWizard1A = { 1, sBtlFormWizard1ASteps, 60 };

static const BtlFormStep sBtlFormWizard1BSteps[] = {
    { ENEMY_WIZARD, -64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormWizard1B = { 1, sBtlFormWizard1BSteps, 60 };

static const BtlFormStep sBtlFormNeoshadow3ASteps[] = {
    { ENEMY_NEOSHADOW, 40, 0, 0, 0 },
    { ENEMY_NEOSHADOW, 65, -12, 0, 1 },
    { ENEMY_NEOSHADOW, 85, 12, 0, 2 },
};

const BtlFormEntry gBtlFormNeoshadow3A = { 3, sBtlFormNeoshadow3ASteps, 60 };

static const BtlFormStep sBtlFormNeoshadow3BSteps[] = {
    { ENEMY_NEOSHADOW, 65, -12, 0, 0 },
    { ENEMY_NEOSHADOW, 85, 12, 0, 1 },
    { ENEMY_NEOSHADOW, -40, 0, 0, 2 },
};

static const BtlFormEntry sBtlFormNeoshadow3B = { 3, sBtlFormNeoshadow3BSteps, 60 };

static const BtlFormStep sBtlFormNeoshadow2Steps[] = {
    { ENEMY_NEOSHADOW, 65, -12, 0, 0 },
    { ENEMY_NEOSHADOW, 85, 12, 0, 1 },
};

static const BtlFormEntry sBtlFormNeoshadow2 = { 2, sBtlFormNeoshadow2Steps, 60 };

static const BtlFormStep sBtlFormNeoshadow1ASteps[] = {
    { ENEMY_NEOSHADOW, 64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormNeoshadow1A = { 1, sBtlFormNeoshadow1ASteps, 60 };

static const BtlFormStep sBtlFormNeoshadow1BSteps[] = {
    { ENEMY_NEOSHADOW, -64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormNeoshadow1B = { 1, sBtlFormNeoshadow1BSteps, 60 };

static const BtlFormStep sBtlFormLargeBody2ASteps[] = {
    { ENEMY_LARGE_BODY, 65, -12, 0, 0 },
    { ENEMY_LARGE_BODY, 85, 12, 0, 1 },
};

const BtlFormEntry gBtlFormLargeBody2A = { 2, sBtlFormLargeBody2ASteps, 60 };

static const BtlFormStep sBtlFormLargeBody2BSteps[] = {
    { ENEMY_LARGE_BODY, 40, 0, 0, 0 },
    { ENEMY_LARGE_BODY, -40, 0, 0, 1 },
};

static const BtlFormEntry sBtlFormLargeBody2B = { 2, sBtlFormLargeBody2BSteps, 60 };

static const BtlFormStep sBtlFormLargeBody1ASteps[] = {
    { ENEMY_LARGE_BODY, 64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormLargeBody1A = { 1, sBtlFormLargeBody1ASteps, 60 };

static const BtlFormStep sBtlFormLargeBody1BSteps[] = {
    { ENEMY_LARGE_BODY, -64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormLargeBody1B = { 1, sBtlFormLargeBody1BSteps, 60 };

static const BtlFormStep sBtlFormFatBandit2ASteps[] = {
    { ENEMY_FAT_BANDIT, 25, -25, 0, 0 },
    { ENEMY_FAT_BANDIT, 55, 25, 0, 1 },
};

const BtlFormEntry gBtlFormFatBandit2A = { 2, sBtlFormFatBandit2ASteps, 60 };

static const BtlFormStep sBtlFormFatBandit2BSteps[] = {
    { ENEMY_FAT_BANDIT, 40, 0, 0, 0 },
    { ENEMY_FAT_BANDIT, -40, 0, 0, 1 },
};

static const BtlFormEntry sBtlFormFatBandit2B = { 2, sBtlFormFatBandit2BSteps, 60 };

static const BtlFormStep sBtlFormFatBandit1ASteps[] = {
    { ENEMY_FAT_BANDIT, -64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormFatBandit1A = { 1, sBtlFormFatBandit1ASteps, 60 };

static const BtlFormStep sBtlFormFatBandit1BSteps[] = {
    { ENEMY_FAT_BANDIT, 64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormFatBandit1B = { 1, sBtlFormFatBandit1BSteps, 60 };

static const BtlFormStep sBtlFormAquatank2Steps[] = {
    { ENEMY_AQUATANK, 65, -12, -40, 0 },
    { ENEMY_AQUATANK, 85, 12, -40, 1 },
};

const BtlFormEntry gBtlFormAquatank2 = { 2, sBtlFormAquatank2Steps, 60 };

static const BtlFormStep sBtlFormAquatank1ASteps[] = {
    { ENEMY_AQUATANK, 64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormAquatank1A = { 1, sBtlFormAquatank1ASteps, 60 };

static const BtlFormStep sBtlFormAquatank1BSteps[] = {
    { ENEMY_AQUATANK, -64, 0, -50, 0 },
};

static const BtlFormEntry sBtlFormAquatank1B = { 1, sBtlFormAquatank1BSteps, 60 };

static const BtlFormStep sBtlFormDefender2Steps[] = {
    { ENEMY_DEFENDER, 25, -25, 0, 0 },
    { ENEMY_DEFENDER, 55, 25, 0, 1 },
};

static const BtlFormEntry sBtlFormDefender2 = { 2, sBtlFormDefender2Steps, 60 };

static const BtlFormStep sBtlFormDefender1Steps[] = {
    { ENEMY_DEFENDER, 64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormDefender1 = { 1, sBtlFormDefender1Steps, 60 };

static const BtlFormStep sBtlFormTornadoStep5ASteps[] = {
    { ENEMY_TORNADO_STEP, 25, -25, 0, 0 },
    { ENEMY_TORNADO_STEP, 40, 0, 0, 1 },
    { ENEMY_TORNADO_STEP, 55, 25, 0, 2 },
    { ENEMY_TORNADO_STEP, 65, -12, 0, 3 },
    { ENEMY_TORNADO_STEP, 85, 12, 0, 4 },
};

const BtlFormEntry gBtlFormTornadoStep5A = { 5, sBtlFormTornadoStep5ASteps, 60 };

static const BtlFormStep sBtlFormTornadoStep5BSteps[] = {
    { ENEMY_TORNADO_STEP, 25, -25, 0, 0 },
    { ENEMY_TORNADO_STEP, 55, 25, 0, 1 },
    { ENEMY_TORNADO_STEP, 90, 0, 0, 2 },
    { ENEMY_TORNADO_STEP, -65, -12, 0, 3 },
    { ENEMY_TORNADO_STEP, -85, 12, 0, 4 },
};

static const BtlFormEntry sBtlFormTornadoStep5B = { 5, sBtlFormTornadoStep5BSteps, 60 };

static const BtlFormStep sBtlFormTornadoStep4Steps[] = {
    { ENEMY_TORNADO_STEP, 25, -25, 0, 0 },
    { ENEMY_TORNADO_STEP, 55, 25, 0, 1 },
    { ENEMY_TORNADO_STEP, 65, -12, 0, 2 },
    { ENEMY_TORNADO_STEP, 85, 12, 0, 3 },
};

const BtlFormEntry gBtlFormTornadoStep4 = { 4, sBtlFormTornadoStep4Steps, 60 };

static const BtlFormStep sBtlFormTornadoStep3ASteps[] = {
    { ENEMY_TORNADO_STEP, 40, 0, 0, 0 },
    { ENEMY_TORNADO_STEP, 65, -12, 0, 1 },
    { ENEMY_TORNADO_STEP, 85, 12, 0, 2 },
};

static const BtlFormEntry sBtlFormTornadoStep3A = { 3, sBtlFormTornadoStep3ASteps, 60 };

static const BtlFormStep sBtlFormTornadoStep3BSteps[] = {
    { ENEMY_TORNADO_STEP, 25, -25, 0, 0 },
    { ENEMY_TORNADO_STEP, 64, 0, 0, 1 },
    { ENEMY_TORNADO_STEP, 55, 25, 0, 2 },
};

static const BtlFormEntry sBtlFormTornadoStep3B = { 3, sBtlFormTornadoStep3BSteps, 60 };

static const BtlFormStep sBtlFormTornadoStep3CSteps[] = {
    { ENEMY_TORNADO_STEP, -25, 25, 0, 0 },
    { ENEMY_TORNADO_STEP, -64, 0, 0, 1 },
    { ENEMY_TORNADO_STEP, -55, -25, 0, 2 },
};

static const BtlFormEntry sBtlFormTornadoStep3C = { 3, sBtlFormTornadoStep3CSteps, 60 };

static const BtlFormStep sBtlFormTornadoStep2ASteps[] = {
    { ENEMY_TORNADO_STEP, 65, -12, 0, 0 },
    { ENEMY_TORNADO_STEP, 85, 12, 0, 1 },
};

const BtlFormEntry gBtlFormTornadoStep2A = { 2, sBtlFormTornadoStep2ASteps, 60 };

static const BtlFormStep sBtlFormTornadoStep2BSteps[] = {
    { ENEMY_TORNADO_STEP, 40, 0, 0, 0 },
    { ENEMY_TORNADO_STEP, -40, 0, 0, 1 },
};

static const BtlFormEntry sBtlFormTornadoStep2B = { 2, sBtlFormTornadoStep2BSteps, 60 };

static const BtlFormStep sBtlFormTornadoStep2CSteps[] = {
    { ENEMY_TORNADO_STEP, -65, -12, 0, 0 },
    { ENEMY_TORNADO_STEP, -85, 12, 0, 1 },
};

static const BtlFormEntry sBtlFormTornadoStep2C = { 2, sBtlFormTornadoStep2CSteps, 60 };

static const BtlFormStep sBtlFormTornadoStep2DSteps[] = {
    { ENEMY_TORNADO_STEP, -55, 25, 0, 0 },
    { ENEMY_TORNADO_STEP, -25, -25, 0, 1 },
};

const BtlFormEntry gBtlFormTornadoStep2D = { 2, sBtlFormTornadoStep2DSteps, 60 };

static const BtlFormStep sBtlFormTornadoStep1Steps[] = {
    { ENEMY_TORNADO_STEP, 64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormTornadoStep1 = { 1, sBtlFormTornadoStep1Steps, 60 };

static const BtlFormStep sBtlFormCrescendo5Steps[] = {
    { ENEMY_CRESCENDO, 25, -25, 0, 0 },
    { ENEMY_CRESCENDO, 40, 0, 0, 1 },
    { ENEMY_CRESCENDO, 55, 25, 0, 2 },
    { ENEMY_CRESCENDO, 65, -12, 0, 3 },
    { ENEMY_CRESCENDO, 85, 12, 0, 4 },
};

static const BtlFormEntry sBtlFormCrescendo5 = { 5, sBtlFormCrescendo5Steps, 60 };

static const BtlFormStep sBtlFormCrescendo4Steps[] = {
    { ENEMY_CRESCENDO, 25, -25, 0, 0 },
    { ENEMY_CRESCENDO, 55, 25, 0, 1 },
    { ENEMY_CRESCENDO, 65, -12, 0, 2 },
    { ENEMY_CRESCENDO, 85, 12, 0, 3 },
};

const BtlFormEntry gBtlFormCrescendo4 = { 4, sBtlFormCrescendo4Steps, 60 };

static const BtlFormStep sBtlFormCrescendo3ASteps[] = {
    { ENEMY_CRESCENDO, 40, 0, 0, 0 },
    { ENEMY_CRESCENDO, 65, -12, 0, 1 },
    { ENEMY_CRESCENDO, 85, 12, 0, 2 },
};

const BtlFormEntry gBtlFormCrescendo3A = { 3, sBtlFormCrescendo3ASteps, 60 };

static const BtlFormStep sBtlFormCrescendo3BSteps[] = {
    { ENEMY_CRESCENDO, 25, -25, 0, 0 },
    { ENEMY_CRESCENDO, 64, 0, 0, 1 },
    { ENEMY_CRESCENDO, 55, 25, 0, 2 },
};

static const BtlFormEntry sBtlFormCrescendo3B = { 3, sBtlFormCrescendo3BSteps, 60 };

static const BtlFormStep sBtlFormCrescendo3CSteps[] = {
    { ENEMY_CRESCENDO, -25, 25, 0, 0 },
    { ENEMY_CRESCENDO, -64, 0, 0, 1 },
    { ENEMY_CRESCENDO, -55, -25, 0, 2 },
};

static const BtlFormEntry sBtlFormCrescendo3C = { 3, sBtlFormCrescendo3CSteps, 60 };

static const BtlFormStep sBtlFormCrescendo2ASteps[] = {
    { ENEMY_CRESCENDO, 65, -12, 0, 0 },
    { ENEMY_CRESCENDO, 85, 12, 0, 1 },
};

static const BtlFormEntry sBtlFormCrescendo2A = { 2, sBtlFormCrescendo2ASteps, 60 };

static const BtlFormStep sBtlFormCrescendo2BSteps[] = {
    { ENEMY_CRESCENDO, -65, -12, 0, 0 },
    { ENEMY_CRESCENDO, -85, 12, 0, 1 },
};

static const BtlFormEntry sBtlFormCrescendo2B = { 2, sBtlFormCrescendo2BSteps, 60 };

static const BtlFormStep sBtlFormCrescendo2CSteps[] = {
    { ENEMY_CRESCENDO, -55, 25, 0, 0 },
    { ENEMY_CRESCENDO, -25, -25, 0, 1 },
};

static const BtlFormEntry sBtlFormCrescendo2C = { 2, sBtlFormCrescendo2CSteps, 60 };

static const BtlFormStep sBtlFormCrescendo1Steps[] = {
    { ENEMY_CRESCENDO, 64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormCrescendo1 = { 1, sBtlFormCrescendo1Steps, 60 };

static const BtlFormStep sBtlFormCreeperPlant6Steps[] = {
    { ENEMY_CREEPER_PLANT, 25, -25, 0, 0 },
    { ENEMY_CREEPER_PLANT, 40, 0, 0, 1 },
    { ENEMY_CREEPER_PLANT, 25, 25, 0, 2 },
    { ENEMY_CREEPER_PLANT, -25, 25, 0, 3 },
    { ENEMY_CREEPER_PLANT, -40, 0, 0, 4 },
    { ENEMY_CREEPER_PLANT, -25, -25, 0, 5 },
};

static const BtlFormEntry sBtlFormCreeperPlant6 = { 6, sBtlFormCreeperPlant6Steps, 60 };

static const BtlFormStep sBtlFormCreeperPlant5ASteps[] = {
    { ENEMY_CREEPER_PLANT, 25, -25, 0, 0 },
    { ENEMY_CREEPER_PLANT, 40, 0, 0, 1 },
    { ENEMY_CREEPER_PLANT, 55, 25, 0, 2 },
    { ENEMY_CREEPER_PLANT, 65, -12, 0, 3 },
    { ENEMY_CREEPER_PLANT, 85, 12, 0, 4 },
};

const BtlFormEntry gBtlFormCreeperPlant5A = { 5, sBtlFormCreeperPlant5ASteps, 60 };

static const BtlFormStep sBtlFormCreeperPlant5BSteps[] = {
    { ENEMY_CREEPER_PLANT, 25, -25, 0, 0 },
    { ENEMY_CREEPER_PLANT, 55, 25, 0, 1 },
    { ENEMY_CREEPER_PLANT, 90, 0, 0, 2 },
    { ENEMY_CREEPER_PLANT, -65, -12, 0, 3 },
    { ENEMY_CREEPER_PLANT, -85, 12, 0, 4 },
};

static const BtlFormEntry sBtlFormCreeperPlant5B = { 5, sBtlFormCreeperPlant5BSteps, 60 };

static const BtlFormStep sBtlFormCreeperPlant4Steps[] = {
    { ENEMY_CREEPER_PLANT, 25, -25, 0, 0 },
    { ENEMY_CREEPER_PLANT, 55, 25, 0, 1 },
    { ENEMY_CREEPER_PLANT, 65, -12, 0, 2 },
    { ENEMY_CREEPER_PLANT, 85, 12, 0, 3 },
};

static const BtlFormEntry sBtlFormCreeperPlant4 = { 4, sBtlFormCreeperPlant4Steps, 60 };

static const BtlFormStep sBtlFormCreeperPlant3ASteps[] = {
    { ENEMY_CREEPER_PLANT, 40, 0, 0, 0 },
    { ENEMY_CREEPER_PLANT, 65, -12, 0, 1 },
    { ENEMY_CREEPER_PLANT, 85, 12, 0, 2 },
};

const BtlFormEntry gBtlFormCreeperPlant3A = { 3, sBtlFormCreeperPlant3ASteps, 60 };

static const BtlFormStep sBtlFormCreeperPlant3BSteps[] = {
    { ENEMY_CREEPER_PLANT, -65, -12, 0, 0 },
    { ENEMY_CREEPER_PLANT, -85, 12, 0, 1 },
    { ENEMY_CREEPER_PLANT, 40, 0, 0, 2 },
};

static const BtlFormEntry sBtlFormCreeperPlant3B = { 3, sBtlFormCreeperPlant3BSteps, 60 };

static const BtlFormStep sBtlFormCreeperPlant2ASteps[] = {
    { ENEMY_CREEPER_PLANT, 65, -12, 0, 0 },
    { ENEMY_CREEPER_PLANT, 85, 12, 0, 1 },
};

static const BtlFormEntry sBtlFormCreeperPlant2A = { 2, sBtlFormCreeperPlant2ASteps, 60 };

static const BtlFormStep sBtlFormCreeperPlant1Steps[] = {
    { ENEMY_CREEPER_PLANT, 64, 0, 0, 0 },
};

static const BtlFormEntry sBtlFormCreeperPlant1 = { 1, sBtlFormCreeperPlant1Steps, 60 };

static const BtlFormStep sBtlFormCreeperPlant2BSteps[] = {
    { ENEMY_CREEPER_PLANT, 40, 0, 0, 0 },
    { ENEMY_CREEPER_PLANT, -40, 0, 0, 1 },
};

static const BtlFormEntry sBtlFormCreeperPlant2B = { 2, sBtlFormCreeperPlant2BSteps, 60 };

static const BtlFormStep sBtlFormCreeperPlant2CSteps[] = {
    { ENEMY_CREEPER_PLANT, -65, -12, 0, 0 },
    { ENEMY_CREEPER_PLANT, -85, 12, 0, 1 },
};

static const BtlFormEntry sBtlFormCreeperPlant2C = { 2, sBtlFormCreeperPlant2CSteps, 60 };

static const BtlFormStep sBtlFormCardSoldierSpade3Steps[] = {
    { ENEMY_CARD_SOLDIER_SPADE, 65, -12, 0, 0 },
    { ENEMY_CARD_SOLDIER_SPADE, 85, 12, 0, 1 },
    { ENEMY_CARD_SOLDIER_SPADE, -40, 0, 0, 2 },
};

static const BtlFormEntry sBtlFormCardSoldierSpade3 = { 3, sBtlFormCardSoldierSpade3Steps, 60 };

static const BtlFormStep sBtlFormCardSoldierSpade2Steps[] = {
    { ENEMY_CARD_SOLDIER_SPADE, -55, 25, 0, 0 },
    { ENEMY_CARD_SOLDIER_SPADE, -25, -25, 0, 1 },
};

static const BtlFormEntry sBtlFormCardSoldierSpade2 = { 2, sBtlFormCardSoldierSpade2Steps, 60 };

static const BtlFormStep sBtlFormCardSoldierSpade1Steps[] = {
    { ENEMY_CARD_SOLDIER_SPADE, 64, 0, 0, 0 },
};

const BtlFormEntry gBtlFormCardSoldierSpade1 = { 1, sBtlFormCardSoldierSpade1Steps, 60 };

static const BtlFormStep sBtlFormCardSoldierHeart3Steps[] = {
    { ENEMY_CARD_SOLDIER_HEART, 65, -12, 0, 0 },
    { ENEMY_CARD_SOLDIER_HEART, 85, 12, 0, 1 },
    { ENEMY_CARD_SOLDIER_HEART, 90, 0, 0, 2 },
};

const BtlFormEntry gBtlFormCardSoldierHeart3 = { 3, sBtlFormCardSoldierHeart3Steps, 60 };

static const BtlFormStep sBtlFormCardSoldierHeart2Steps[] = {
    { ENEMY_CARD_SOLDIER_HEART, 25, -25, 0, 0 },
    { ENEMY_CARD_SOLDIER_HEART, 55, 25, 0, 1 },
};

const BtlFormEntry gBtlFormCardSoldierHeart2 = { 2, sBtlFormCardSoldierHeart2Steps, 60 };

static const BtlFormStep sBtlFormCardSoldierHeart1Steps[] = {
    { ENEMY_CARD_SOLDIER_HEART, 64, 0, 0, 0 },
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
