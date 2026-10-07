#include "rogue.h"
#include "anim.h"
#include "hum.h"
#include "sprite_palettes.h"

// Bosses that borrow another boss's fight. Mickey has no battle of his own
// in the game, only the sprites of his summon: he fights with Leon's moves
// and timing, drawn as himself.

extern const AnimDef gHumLeonAnimDefs[5];
extern const HumDef gHumLeonDef;
extern const AnimDef gSmnKingAnimDefs[3];

// Leon's five animations, standing and four actions, as the nearest of the
// three Mickey has.
static const AnimDef* const sMickeySlots[5] = {
    &gSmnKingAnimDefs[0], &gSmnKingAnimDefs[1], &gSmnKingAnimDefs[1], &gSmnKingAnimDefs[1], &gSmnKingAnimDefs[2],
};

// Leon's definition with Mickey's palette.
static const HumDef sMickeyDef = { 128, 0, gMickeyPalette, 0, { 41, 99, 64, 14, 40, 99, 0 } };

// The animation table and the slot in it for one of Leon's animations: his
// own, or Mickey's when Mickey stands in for him.
const AnimDef* RogueLeonAnim(u16 slot) {
    if (gRogue.bossSkin == ROGUE_SKIN_MICKEY) {
        return sMickeySlots[slot];
    }

    return &gHumLeonAnimDefs[slot];
}

const HumDef* RogueLeonDef(void) {
    if (gRogue.bossSkin == ROGUE_SKIN_MICKEY) {
        return &sMickeyDef;
    }

    return &gHumLeonDef;
}
