#include "rogue.h"
#include "battle.h"
#include "gba/keys.h"
#include "msg_api.h"
#include "obj_api.h"
#include "sprite.h"
#include "system_state.h"
#include "taskpool.h"
#include "text.h"

// What the mod adds on top of a battle: the hit counter and its damage
// bonus, hitstop, and the jump buffer.

// Called when an actor is about to take the damage in unk_020.
void RogueOnDamage(BtlObj* p) {
    s32 bonus;

    if (p == gBtlWork->actor) {
        gRogue.combo = 0;
        gRogue.comboTimer = 0;
        return;
    }

    // Each hit of an unbroken string adds 2% damage, up to 30%.
    bonus = gRogue.combo < ROGUE_COMBO_BONUS_HITS ? gRogue.combo : ROGUE_COMBO_BONUS_HITS;
    p->unk_020 += p->unk_020 * bonus / 50;

    if (gRogue.combo < 999) {
        gRogue.combo++;
    }

    gRogue.comboTimer = ROGUE_COMBO_TIME;
}

// A press of the jump button counts for a few frames, so that one made just
// before Sora can jump still does.
u16 RogueBufferJump(u16 pressed) {
    if (pressed & B_BUTTON) {
        gRogue.jumpBuffer = ROGUE_JUMP_BUFFER;
    } else if (gRogue.jumpBuffer != 0) {
        gRogue.jumpBuffer--;
        pressed |= B_BUTTON;
    }

    return pressed;
}

typedef struct RogueHudWork {
    void* tiles;
    void* palette;
} RogueHudWork;

static const u8 sHits[] = "HIT";

static void RogueHud_Init(RogueHudWork* w) {
    w->tiles = LoadSmallFontTiles();
    w->palette = LoadSmallFontPalette();
    gRogue.combo = 0;
    gRogue.comboTimer = 0;
    gRogue.jumpBuffer = 0;
}

static s32 RogueHud_Update(RogueHudWork* w) {
    if (gRogue.comboTimer != 0) {
        gRogue.comboTimer--;

        if (gRogue.comboTimer == 0) {
            gRogue.combo = 0;
        }
    }

    return 1;
}

static void RogueHud_Draw(RogueHudWork* w) {
    u16 text[8];
    u16 digits;
    s16 x;

    if (gRogue.combo < 2) {
        return;
    }

    // The small font has no space: the two words are drawn apart.
    digits = FormatSmallFontDecimal(gRogue.combo, text);
    x = 120 - (digits * 8 + 4 + 24) / 2;
    DrawSmallFontString(x, 30, text, w->tiles, w->palette, 0, digits);
    DrawSmallFontString(x + digits * 8 + 4, 30, text, w->tiles, w->palette, 0, EncodeSmallFontString((u8*)sHits, text));
}

static void RogueHud_Destroy(RogueHudWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

TaskDesc gTaskDescRogueHud = {
    "task_rogue_hud",
    (TaskInitFunc)RogueHud_Init,
    (TaskUpdateFunc)RogueHud_Update,
    (TaskDrawFunc)RogueHud_Draw,
    (TaskDestroyFunc)RogueHud_Destroy,
    sizeof(RogueHudWork),
};
