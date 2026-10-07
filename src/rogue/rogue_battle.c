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
    BtlObj* sora = gBtlWork->actor;
    s32 bonus;
    s32 cap;

    if (p == sora) {
        if (RogueHasRelic(ROGUE_RELIC_GLASS_CANNON)) {
            p->unk_020 += p->unk_020 / 2;
        }

        if (RogueHasRelic(ROGUE_RELIC_SECOND_WIND) && !gRogue.secondWindUsed && p->unk_020 >= p->unk_02C && p->unk_02C > 1) {
            p->unk_020 = p->unk_02C - 1;
            gRogue.secondWindUsed = 1;
        }

        gRogue.combo = 0;
        gRogue.comboTimer = 0;
        return;
    }

    // Each hit of an unbroken string adds 2% damage, up to 30%.
    cap = RogueHasRelic(ROGUE_RELIC_MOMENTUM) ? ROGUE_COMBO_BONUS_HITS * 2 : ROGUE_COMBO_BONUS_HITS;
    bonus = gRogue.combo < cap ? gRogue.combo : cap;
    p->unk_020 += p->unk_020 * bonus / 50;

    if (RogueHasRelic(ROGUE_RELIC_CRITICAL) && RogueRandBelow(7) == 0) {
        p->unk_020 *= 2;
    }

    if (RogueHasRelic(ROGUE_RELIC_GLASS_CANNON)) {
        p->unk_020 += p->unk_020 / 2;
    }

    if (RogueHasRelic(ROGUE_RELIC_VAMPIRE) && sora->unk_02C > 0 && sora->unk_02C < sora->unk_02E) {
        sora->unk_02C++;
    }

    if (gRogue.combo < 999) {
        gRogue.combo++;
    }

    gRogue.comboTimer = ROGUE_COMBO_TIME;
}

u8 RogueReloadRate(u8 slowed) {
    u8 rate = slowed ? ROGUE_RELOAD_RATE_SLOWED : ROGUE_RELOAD_RATE;

    if (RogueHasRelic(ROGUE_RELIC_RELOAD)) {
        rate += rate / 2;
    }

    return rate;
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
    gRogue.secondWindUsed = 0;
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
