#include "rogue.h"
#include "rogue_ui.h"
#include "anim.h"
#include "engine_math.h"
#include "obj_api.h"
#include "sprite.h"

// The look the mod's menus share, made of the game's own pieces: the plates
// and the pointing glove of the pause menu. An entry of a menu is a plate
// with its name written over it in the game's font; the one chosen turns
// orange, slides out and has the glove by it.

extern u8 gUnk_09991944[], gUnk_09991964[], gUnk_099919A4[], gUnk_098A8628[];
extern u8 gUnk_09EF8D58[], gUnk_09EF8D48[];
extern const u8 gRoguePlateTiles[];

// A plate: three 32x16 pieces side by side.
static const u16 sPlateFrame[] = {
    3, 0x4000, 0x8000, 0, 0x4000, 0x8020, 8, 0x4000, 0x8040, 16, 0,
};

void RogueUiInit(RogueUi* ui) {
    ui->plateTiles = LoadObjTiles((void*)gRoguePlateTiles, 24 * 32);
    ui->platePalette = LoadObjPalette(gUnk_09991944, 32);
    ui->chosenPalette = LoadObjPalette(gUnk_09991964, 32);
    ui->gloveTiles = AllocObjTiles(0x120, gUnk_098A8628);
    ui->glovePalette = LoadObjPalette(gUnk_099919A4, 32);
    AnimInit(&ui->glove, gUnk_09EF8D58, gUnk_09EF8D48);
    AnimStart(&ui->glove, 2, 1);
    ui->gloveY = -1;
}

void RogueUiExit(RogueUi* ui) {
    ReleaseObjTiles(ui->plateTiles);
    ReleaseObjPalette(ui->platePalette);
    ReleaseObjPalette(ui->chosenPalette);
    ReleaseObjTiles(ui->gloveTiles);
    ReleaseObjPalette(ui->glovePalette);
}

// Draws a plate with its top left corner at x, y. The chosen one stands 8
// pixels out, as in the pause menu. Returns where its text starts.
s16 RogueUiPlate(RogueUi* ui, s16 x, s16 y, u8 chosen) {
    if (chosen) {
        x += 8;
    }

    DrawSprite(x, y, (void*)sPlateFrame, ui->plateTiles, chosen ? ui->chosenPalette : ui->platePalette, 0, 0, 81);
    return x + 14;
}

// Draws the glove pointing at the plate at x, y, gliding to it from where it
// pointed before. Call once a frame.
void RogueUiGlove(RogueUi* ui, s16 x, s16 y) {
    if (ui->gloveY < 0) {
        ui->gloveY = y << 8;
    }

    ApproachValueHalf(&ui->gloveY, y << 8);
    AnimUpdate(&ui->glove);
    DrawSprite(x, ui->gloveY >> 8, AnimGetGfx(&ui->glove), ui->gloveTiles, ui->glovePalette, 0, 1, 40);
}

// The frame the menus stand in: the status screen's, emptied of what that
// screen writes on it. What is left is a list on the left, a window at the
// top right and a plain panel under the window. `out` gets the 32x20 map.
extern u8 gUnk_09847798[];

void RogueUiFrameMap(u16* out) {
    const u16* map = (const u16*)gUnk_09847798;
    u16 plain = map[9 * 32 + 20]; // the panel's own grey
    s32 x;
    s32 y;

    for (x = 0; x < 0x500 / 2; x++) {
        out[x] = map[x];
    }

    // The panel: its captions, figures and rules.
    for (y = 9; y <= 16; y++) {
        for (x = 14; x <= 28; x++) {
            out[y * 32 + x] = plain;
        }
    }

    // The friends' box, which covers the right side of the window: the side
    // is drawn back as the left one mirrored.
    for (y = 3; y <= 7; y++) {
        for (x = 21; x <= 29; x++) {
            out[y * 32 + x] = 0;
        }

        out[y * 32 + 28] = map[y * 32 + 14] ^ 0x400;
    }

    // The bar with the deck's name.
    for (y = 18; y <= 19; y++) {
        for (x = 16; x < 32; x++) {
            out[y * 32 + x] = 0;
        }
    }
}

// The same with only the panel left, for a page that fills the screen with
// something of its own and says what it is at the bottom. The layer is to be
// scrolled with RogueUiPanelScroll so that the panel sits low and centred.
void RogueUiPanelMap(u16* out) {
    s32 x;
    s32 y;

    RogueUiFrameMap(out);

    for (y = 0; y < 20; y++) {
        for (x = 0; x < 32; x++) {
            if (y < 8 || y > 17 || x < 13) {
                out[y * 32 + x] = 0;
            }
        }
    }
}
