#include "rogue.h"
#include "game_state.h"
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

extern const AnimDef gFrdBeastAnimDefs[2], gFrdJackAnimDefs[5], gFrdPanAnimDefs[4], gFrdGoofyAnimDefs[5], gFrdDonaldAnimDefs[6],
    gFrdAladdinAnimDefs[3];

// The friends who fight in Leon's place: where each one's animations are,
// which of them is the attack, and the palette. They stand with the first.
typedef struct RogueSkin {
    const AnimDef* anims;
    u8 attack;
    HumDef def;
} RogueSkin;

#define SKIN(anims, attack, palette) { anims, attack, { 128, 0, palette, 0, { 41, 99, 64, 14, 40, 99, 0 } } }

static const RogueSkin sSkins[ROGUE_SKINS - ROGUE_SKIN_BEAST] = {
    SKIN(gFrdBeastAnimDefs, 1, gBeastPalette), SKIN(gFrdJackAnimDefs, 3, gJackPalette), SKIN(gFrdPanAnimDefs, 2, gPeterPalette),
    SKIN(gFrdGoofyAnimDefs, 4, gGoofyPalette), SKIN(gFrdDonaldAnimDefs, 2, gDonaldPalette), SKIN(gFrdAladdinAnimDefs, 2, gAladdinPalette),
};

// The animation table and the slot in it for one of Leon's animations: his
// own, or those of whoever stands in for him.
const AnimDef* RogueLeonAnim(u16 slot) {
    if (gRogue.bossSkin == ROGUE_SKIN_MICKEY) {
        return sMickeySlots[slot];
    }

    if (gRogue.bossSkin >= ROGUE_SKIN_BEAST && gRogue.bossSkin < ROGUE_SKINS) {
        const RogueSkin* skin = &sSkins[gRogue.bossSkin - ROGUE_SKIN_BEAST];

        return &skin->anims[slot == 0 ? 0 : skin->attack];
    }

    return &gHumLeonAnimDefs[slot];
}

const HumDef* RogueLeonDef(void) {
    if (gRogue.bossSkin == ROGUE_SKIN_MICKEY) {
        return &sMickeyDef;
    }

    if (gRogue.bossSkin >= ROGUE_SKIN_BEAST && gRogue.bossSkin < ROGUE_SKINS) {
        return &sSkins[gRogue.bossSkin - ROGUE_SKIN_BEAST].def;
    }

    return &gHumLeonDef;
}

// The heroes. Each plays exactly as Sora does: for every animation of his
// there is one of theirs with the same frames, so only the pictures change.

extern const AnimDef gBtlSoraAnimDefs[77];
extern const AnimDef gRogueMickeyAnimDefs[77];
extern const AnimDef gRogueMickeyDirectionDefs[30];
extern const AnimDef gRogueMickeyFieldDefs[75];
extern const AnimDef gUnk_0813C89C[15][5];
extern const AnimDef gUnk_0813BEFC[6][5];

// Sora in the black clothes of his second journey: his own sprites with
// the reds turned to black and the blue to red. Worn after a first win.
static const u16 sSoraKh2Palette[16] = { 0x4208, 0x20E3, 0x49CB, 0x6ED4, 0x1063, 0x20C6, 0x3DAD, 0x167A, 0x37DF, 0x0029, 0x00D0, 0x11B5, 0x32BE, 0x5B7F, 0x1099, 0x7FFF };

u8 RogueHeroUnlocked(u8 hero) {
    if (hero == ROGUE_HERO_MICKEY) {
        return (gRogueMeta.flags & ROGUE_META_MICKEY) != 0;
    }

    if (hero == ROGUE_HERO_SORA_KH2) {
        return gRogueMeta.wins != 0;
    }

    if (hero == ROGUE_HERO_RIKU) {
        return (gRogueMeta.bossMoves & ROGUE_BOSS_MOVE_RIKU) != 0;
    }

    return hero == ROGUE_HERO_SORA;
}

// One of the hero's battle animations, numbered as Sora's are.
const AnimDef* RogueHeroAnim(u16 anim) {
    if (gRogueMeta.hero == ROGUE_HERO_MICKEY) {
        return &gRogueMickeyAnimDefs[anim];
    }

    return &gBtlSoraAnimDefs[anim];
}

// The same for running and jumping, which Sora has in five directions.
const AnimDef* RogueHeroDirection(u16 action, u16 direction) {
    if (gRogueMeta.hero == ROGUE_HERO_MICKEY) {
        return &gRogueMickeyDirectionDefs[action * 5 + direction];
    }

    return &gUnk_0813BEFC[action][direction];
}

// And for walking the rooms of the map.
const AnimDef* RogueHeroField(u16 action, u16 direction) {
    if (gRogueMeta.hero == ROGUE_HERO_MICKEY) {
        return &gRogueMickeyFieldDefs[action * 5 + direction];
    }

    return &gUnk_0813C89C[action][direction];
}

// The hero's palette, given the one Sora would have.
void* RogueHeroPalette(void* sora) {
    if (gRogueMeta.hero == ROGUE_HERO_MICKEY) {
        return (void*)gRogueMickeyPalette;
    }

    if (gRogueMeta.hero == ROGUE_HERO_SORA_KH2) {
        return (void*)sSoraKh2Palette;
    }

    return sora;
}

// The next hero unlocked after the one picked, for the hub's SELECT.
u8 RogueNextHero(void) {
    u8 hero = gRogueMeta.hero;

    do {
        hero = (hero + 1) % ROGUE_HEROES;
    } while (!RogueHeroUnlocked(hero));

    return hero;
}

// Riku is not a reskin: the game has his own way of fighting, with its combos
// and the dark mode, behind one flag of the game state. Called when a run
// starts, after the game state is reset.
void RogueApplyHero(void) {
    if (gRogueMeta.hero == ROGUE_HERO_RIKU) {
        gGameState.flags |= 8;
    } else {
        gGameState.flags &= ~8;
    }
}

// The face by the HP bar and its palette, given Sora's.
extern const u8 gRogueMickeyFaceTiles[];
extern const u16 gRogueMickeyFacePalette[16];

void* RogueHeroFace(void* sora) {
    if (gRogueMeta.hero == ROGUE_HERO_MICKEY) {
        return (void*)gRogueMickeyFaceTiles;
    }

    return sora;
}

void* RogueHeroFacePalette(void* sora) {
    if (gRogueMeta.hero == ROGUE_HERO_MICKEY) {
        return (void*)gRogueMickeyFacePalette;
    }

    return RogueHeroPalette(sora);
}
