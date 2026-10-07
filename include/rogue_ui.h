#ifndef GUARD_ROGUE_UI_H
#define GUARD_ROGUE_UI_H

#include "anim.h"
#include "types.h"

// The pieces the mod's menus are drawn with, see rogue_ui.c.
typedef struct RogueUi {
    void* plateTiles;
    void* platePalette;
    void* chosenPalette;
    void* gloveTiles;
    void* glovePalette;
    AnimState glove;
    s32 gloveY;
} RogueUi;

void RogueUiInit(RogueUi* ui);
void RogueUiExit(RogueUi* ui);
s16 RogueUiPlate(RogueUi* ui, s16 x, s16 y, u8 chosen);
void RogueUiGlove(RogueUi* ui, s16 x, s16 y);
void RogueUiFrameMap(u16* out);
void RogueUiPanelMap(u16* out);
#define ROGUE_UI_PANEL_SCROLL_X 52 // scrolls of the frame layer that centre the lone panel at the bottom
#define ROGUE_UI_PANEL_SCROLL_Y (-32)

#endif
